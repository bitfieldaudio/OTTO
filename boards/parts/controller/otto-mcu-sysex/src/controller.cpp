#include "board/controller.hpp"

#include "util/algorithm.hpp"
#include "util/exception.hpp"
#include "util/utility.hpp"

#include "services/audio_manager.hpp"
#include "services/log_manager.hpp"
#include "services/ui_manager.hpp"

#include "board/emulator.hpp"

namespace otto::services {
  using MSC = MCUSysexController;
  using Event = MSC::Event;
  using EventBag = MSC::EventBag;
  using namespace core::input;

  using byte = std::uint8_t;

  constexpr auto NUM_ROWS = 8;
  constexpr auto NUM_COLUMNS = 7;
  constexpr auto NUM_ENCODERS = 4;

  std::array<std::array<tl::optional<Key>, NUM_COLUMNS>, NUM_ROWS> keyCodes = {{
    {Key::C0, Key::C3, Key::C7, Key::shift, Key::sends, tl::nullopt, Key::blue_click},
    {Key::S1, Key::S6, Key::S11, Key::plus, Key::routing, Key::rec, Key::yellow_click},
    {Key::S2, Key::S7, Key::S12, Key::minus, Key::fx2, Key::master, tl::nullopt},
    {Key::C1, Key::C4, Key::C8, Key::S0, Key::fx1, Key::play, Key::red_click},
    {Key::S3, Key::S8, Key::S13, Key::S15, Key::arp, Key::slots, tl::nullopt},
    {Key::S4, Key::S9, Key::S14, Key::twist2, Key::looper, Key::twist1, tl::nullopt},
    {Key::C2, Key::C5, Key::C9, Key::external, Key::sampler, Key::envelope, Key::green_click},
    {Key::S5, Key::C6, Key::S10, Key::settings, Key::sequencer, Key::synth, tl::nullopt},
  }};

  template<typename Callable>
  void InputData::for_updated_keys(const InputData& o, Callable&& f)
  {
    for (auto r : nano::views::iota(0, NUM_ROWS)) {
      for (auto c : nano::views::iota(0, NUM_COLUMNS)) {
        auto mask = 1 << c;
        bool cur = rows[r] & mask;
        bool prev = o.rows[r] & mask;
        if (cur != prev) {
          keyCodes[r][c].map_or_else([&](Key k) { f(k, cur); }, [&] {
            DLOGI("Invalid key: r{} c{}", r, c);
          });
        }
      }
    }
  }

  struct LEDMap {
    unsigned char string;
    unsigned char num;
  };

  util::enum_map<Key, LEDMap> led_map = {{
    {Key::C0, {1, 0}},
    {Key::C3, {1, 3}},
    {Key::C7, {1, 7}},
    {Key::shift, {0, 2}},
    {Key::sends, {0, 3}},
    {Key::blue_click, {0, 25}},
    {Key::S1, {2, 1}},
    {Key::S6, {2, 6}},
    {Key::S11, {2, 11}},
    {Key::plus, {0, 1}},
    {Key::routing, {0, 10}},
    {Key::rec, {0, 11}},
    {Key::yellow_click, {0, 25}},
    {Key::S2, {2, 2}},
    {Key::S7, {2, 7}},
    {Key::S12, {2, 12}},
    {Key::minus, {0, 0}},
    {Key::fx2, {0, 9}},
    {Key::master, {0, 13}},
    {Key::C1, {1, 1}},
    {Key::C4, {1, 4}},
    {Key::C8, {1, 8}},
    {Key::S0, {2, 0}},
    {Key::fx1, {0, 4}},
    {Key::play, {0, 12}},
    {Key::red_click, {0, 25}},
    {Key::S3, {2, 3}},
    {Key::S8, {2, 8}},
    {Key::S13, {2, 13}},
    {Key::S15, {2, 15}},
    {Key::arp, {0, 8}},
    {Key::slots, {0, 14}},
    {Key::S4, {2, 4}},
    {Key::S9, {2, 9}},
    {Key::S14, {2, 14}},
    {Key::twist2, {0, 16}},
    {Key::looper, {0, 5}},
    {Key::twist1, {0, 15}},
    {Key::C2, {1, 2}},
    {Key::C5, {1, 5}},
    {Key::C9, {1, 9}},
    {Key::external, {0, 17}},
    {Key::sampler, {0, 7}},
    {Key::envelope, {0, 18}},
    {Key::green_click, {0, 25}},
    {Key::S5, {2, 5}},
    {Key::C6, {1, 6}},
    {Key::S10, {2, 10}},
    {Key::settings, {0, 20}},
    {Key::sequencer, {0, 6}},
    {Key::synth, {0, 19}},
  }};

  BETTER_ENUM(Command, std::uint8_t, read_inputs = 0x00, led_set = 0x01, leds_clear = 0x02);

  byte to_byte(Key k)
  {
    return util::underlying(k);
  }
  byte to_byte(LED led)
  {
    return led.key;
  }

  auto make_message(Command cmd)
  {
    return std::vector<byte>{cmd._to_integral()};
  }

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

  int8_t to_int8(uint8_t x)
  {
    return (x >= 128 ? x - 256 : x);
  }

  void MSC::handle_response(BytesView bytes)
  {
    assert(bytes.size() > 0);
    auto command = Command::read_inputs;
    // auto command = Command::_from_integral_unchecked(bytes[0]);
    // bytes = bytes.subspan(1, gsl::dynamic_extent);
    switch (command) {
      case Command::read_inputs: {
        OTTO_ASSERT(bytes.size() == NUM_ROWS + NUM_ENCODERS);
        InputData input_data;
        nano::copy(bytes.subspan(0, NUM_ROWS), input_data.rows.begin());
        nano::copy(bytes.subspan(NUM_ROWS, NUM_ENCODERS), input_data.encoders.begin());
        input_data.for_updated_keys(last_input_data, [this](Key k, bool down) {
          if (down) {
            keypress(k);
          } else {
            keyrelease(k);
          }
        });
        last_input_data = input_data;
      } break;
      default: {
        LOGE("Unparsable response");
        break;
      }
    }
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
      byte b = resp[i];
      *(output++) = (resp[i] << 4) | (resp[i + 1] & 0x0F);
      if (b == 0xF7) break;
    };
    handle_response({resp.data(), output - resp.begin()});
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
    midi_in.setCallback([] (double deltatime, std::vector<std::uint8_t>* message, void* self) {
      static_cast<MSC*>(self)->parse_midi_response(*message);
    }, this);

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
        //midi_in.getMessage(&wb);
        //parse_midi_response(wb);
        midi_thread.sleep_for(sleep_time);
      }
    };
  }

  std::unique_ptr<Controller> MSC::make_or_dummy(int in_port, int out_port)
  {
    try {
      return std::make_unique<MSC>(in_port, out_port);
    } catch (const std::exception& e) {
      LOGE("Couldn't set up sysex controller. Continuing with dummy. ERR: {}", e.what());
      return Controller::make_dummy();
    }
  }

  std::unique_ptr<Controller> MSC::make_or_emulator(int in_port, int out_port)
  {
    try {
      return std::make_unique<MSC>(in_port, out_port);
    } catch (const std::exception& e) {
      LOGE("Couldn't set up sysex controller. Continuing with dummy. ERR: {}", e.what());
      return std::make_unique<board::Emulator>();
    }
  }

  void MSC::set_color(LED led, LEDColor color)
  {
    auto& [old_c, updated] = led_colors[led.key];
    if (old_c != color) {
      old_c = color;
      updated = true;
    }
  }

  void MSC::flush_leds()
  {
    for (auto key : Key::_values()) {
      auto& [color, has_changed] = led_colors[key];
      if (has_changed) {
        auto lm = led_map[key];
        std::array<std::uint8_t, 6> msg = {0x01, lm.string, lm.num, color.r, color.g, color.b};
        queue_message(msg);
        has_changed = false;
      }
    }
  }

  void MSC::clear_leds()
  {
    // auto c = LEDColor::Black;
    // std::array<std::uint8_t, 5> msg = {0xE0, c.r, c.g, c.b, '\n'};
    // queue_message(msg);
  }

} // namespace otto::services

// kak: other_file=../include/board/controller.hpp
