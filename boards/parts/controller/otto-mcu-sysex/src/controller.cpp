#include "board/controller.hpp"

#include "board/emulator.hpp"
#include "services/audio_manager.hpp"
#include "services/log_manager.hpp"
#include "services/ui_manager.hpp"
#include "util/algorithm.hpp"
#include "util/exception.hpp"
#include "util/utility.hpp"

namespace otto::services {
  using MSC = MCUSysexController;
  using Event = MSC::Event;
  using EventBag = MSC::EventBag;
  using namespace core::input;

  void MSC::queue_message(BytesView message)
  {
    write_buffer_.outer_locked([&](auto& buf) {
      buf.reserve(buf.size() + message.size() + 4);
      buf.push_back(0xF0);
      buf.push_back(0x7D);
      buf.push_back(0x07);
      for (auto& b : message) {
        buf.push_back(std::min(b, (std::uint8_t) 0x7F));
      }
      buf.push_back(0xF7);
    });
  }

  void MSC::parse_midi_response(gsl::span<std::uint8_t> resp)
  {
    if (resp.size() < 3) return;
    if (resp[0] != 0xF0) return;
    if (resp[1] != 0x7D) return;
    if (resp[2] != 0x07) return;
    auto output = resp.begin();
    int i = 3;
    for (; i < resp.size() - 1; i += 2) {
      std::uint8_t b = resp[i];
      *(output++) = (resp[i] << 4) | (resp[i + 1] & 0x0F);
      if (b == 0xF7) break;
    };
    handle_response({resp.data(), static_cast<std::size_t>(output - resp.begin())});
    if (i < resp.size()) {
      parse_midi_response(resp.subspan(i, gsl::dynamic_extent));
    }
  }

  MSC::MCUSysexController(int in_port, int out_port)
  {
    auto ninports = midi_in.getPortCount();

    LOGI("Midi input ports: ");
    for (int i = 0; i < ninports; i++) {
      auto name = midi_in.getPortName(i);
      LOGI("  {} - {}", i, name);
    }

    if (in_port < 0) {
      throw util::exception(
        "No input midi port specified. Use --sysex-ctl-in-device=X to select one of the listed ports");
    }

    midi_in.openPort(in_port);
    // Don't ignore sysex messages
    midi_in.ignoreTypes(false, true, true);
    // I have no idea on which thread this callback is called, but apparently getMesssage
    // doesn't work with sysex messages.
    midi_in.setCallback([](double deltatime, std::vector<std::uint8_t>* message,
                           void* self) { static_cast<MSC*>(self)->parse_midi_response(*message); },
                        this);

    auto noutports = midi_out.getPortCount();
    LOGI("Midi output ports: ");
    for (int i = 0; i < noutports; i++) {
      auto name = midi_out.getPortName(i);
      LOGI("  {} - {}", i, name);
    }

    if (out_port < 0) {
      throw util::exception(
        "No output midi port specified. Use --sysex-ctl-out-device=X to select one of the listed ports");
    }

    midi_out.openPort(out_port);

    midi_thread = [this](auto&& should_run) {
      services::LogManager::current().set_thread_name("MCUSysexController");
      while (should_run()) {
        write_buffer_.swap();
        auto& wb = write_buffer_.inner();
        if (wb.empty()) {
          wb.push_back(0xF0);
          wb.push_back(0x7D);
          wb.push_back(0x07);
          wb.push_back(0x00);
          wb.push_back(0xF7);
        }
        auto first = wb.begin();
        while (first != wb.end()) {
          if (*first == 0xF0) {
            auto last = first + 1;
            while (last != wb.end() && *last != 0xF7) last++;
            midi_out.sendMessage(&*first, last - first + 1);
            first = last;
          }
          first++;
        }
        // midi_in.getMessage(&wb);
        // parse_midi_response(wb);
        midi_thread.sleep_for(sleep_time);
      }
    };
  }

  std::unique_ptr<Controller> MSC::make_or_dummy(int in_port, int out_port)
  {
    try {
      return std::make_unique<MSC>(in_port, out_port);
    } catch (const std::exception& e) {
      LOGW("Couldn't set up sysex controller. Continuing with dummy. ERR: {}", e.what());
      return Controller::make_dummy();
    }
  }

  std::unique_ptr<Controller> MSC::make_or_emulator(int in_port, int out_port)
  {
    try {
      return std::make_unique<MSC>(in_port, out_port);
    } catch (const std::exception& e) {
      LOGW("Couldn't set up sysex controller. Continuing with dummy. ERR: {}", e.what());
      return std::make_unique<board::Emulator>();
    }
  }
} // namespace otto::services

// kak: other_file=../include/board/controller.hpp
