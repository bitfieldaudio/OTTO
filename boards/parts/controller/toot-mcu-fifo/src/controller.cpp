#include "board/controller.hpp"

#include "util/algorithm.hpp"
#include "util/exception.hpp"
#include "util/utility.hpp"

#include "services/log_manager.hpp"
#include "services/ui_manager.hpp"

namespace otto::services {
  using TMFC = McuFifoController;
  using Event = TMFC::Event;
  using EventBag = TMFC::EventBag;

  using byte = std::uint8_t;
  using Key = core::input::Key;
  using Encoder = core::input::Encoder;

  BETTER_ENUM(Command,
              std::uint8_t,
              debug_message = 0x23,
              request_alive = 0x0A,
              respond_alive = 0x0B,
              clear_all_leds = 0xE0,
              clear_led_group = 0xE1,
              set_led_color = 0xEC,
              request_key_dump = 0x2A,
              key_down = 0x20,
              key_up = 0x21,
              respond_key_dump = 0x2B,
              blue_enc_step = 0x30,
              green_enc_step = 0x31,
              yellow_enc_step = 0x32,
              red_enc_step = 0x33)

  byte to_byte(Key k)
  {
    return util::underlying(k);
  }
  byte to_byte(LED led)
  {
    return led.key;
  }

  void TMFC::handle_keyevent(Command cmd, BytesView args, bool do_send_midi)
  {
    OTTO_ASSERT(args.size() > 0, "Requires > 0 args");
    auto key = Key::_from_integral_unchecked(args.at(0));
    switch (cmd) {
      case Command::key_down: {
        keypress(key);
      } break;
      case Command::key_up: {
        keyrelease(key);
      } break;
      default: OTTO_UNREACHABLE;
    }
  }

  auto make_message(Command cmd)
  {
    return std::vector<byte>{cmd._to_integral()};
  }

  void TMFC::queue_message(BytesView message)
  {
    write_buffer_.outer_locked([&](auto& b) {
      b.reserve(b.size() + message.size());
      nano::copy(message, nano::back_inserter(b));
    });
  }

  int8_t to_int8(uint8_t x)
  {
    return (x >= 128 ? x - 256 : x);
  }

  void TMFC::handle_message(BytesView bytes)
  {
    assert(bytes.size() > 0);
    auto command = Command::_from_integral_unchecked(bytes[0]);
    bytes = bytes.subspan(1, gsl::dynamic_extent);
    switch (command) {
      case Command::request_alive: {
        queue_message(make_message(Command::respond_alive));
      } break;
      case Command::respond_alive: {
        LOGI("Got alive from MCU");
      } break;
      case Command::key_up: [[fallthrough]];
      case Command::key_down: {
        handle_keyevent(command, bytes, send_midi_);
      } break;
      case Command::blue_enc_step: encoder({Encoder::blue, to_int8(bytes.at(0))}); break;
      case Command::green_enc_step: encoder({Encoder::green, to_int8(bytes.at(0))}); break;
      case Command::yellow_enc_step: encoder({Encoder::yellow, to_int8(bytes.at(0))}); break;
      case Command::red_enc_step: encoder({Encoder::red, to_int8(bytes.at(0))}); break;
      case Command::respond_key_dump: {
      } break;
      case Command::debug_message: {
        DLOGI("MCU DEBUG: {}", std::string(bytes.begin(), bytes.end()));
      } break;
      default: {
        LOGE("Unparsable message");
        break;
      }
    }
  }

  TMFC::McuFifoController()
    : read_thread([this](auto should_run) noexcept {
        while (should_run()) {
          fifo0.read_line()
            .map([&](auto&& bytes) { handle_message(bytes); })
            .map_error([&](auto&& error) {
              if (error.data() != util::FIFO::ErrorCode::empty_buffer) {
                LOGE("Error reading fifo data {}", error.what());
              }
            });
        }
      })
  {}

  std::unique_ptr<Controller> TMFC::make_or_dummy() {
    try {
      return std::make_unique<TMFC>();
    } catch (std::exception& e) {
      LOGE("Couldn't set up fifo controller. Continuing with dummy. ERR: {}", e.what());
      return Controller::make_dummy();
    }
  }

  void TMFC::set_color(LED led, LEDColor color)
  {
    std::array<std::uint8_t, 6> msg = {0xEC, led.key._to_integral(), color.r, color.g, color.b,
                                       '\n'};
    queue_message(msg);
  }
  void TMFC::flush_leds()
  {
    write_buffer_.swap();
    fifo1.write(write_buffer_.inner());
  }
  void TMFC::clear_leds()
  {
    auto c = LEDColor::Black;
    std::array<std::uint8_t, 5> msg = {0xE0, c.r, c.g, c.b, '\n'};
    queue_message(msg);
  }

} // namespace otto::services

// kak: other_file=../include/board/controller.hpp
