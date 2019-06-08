#include "board/controller.hpp"

#include "util/algorithm.hpp"
#include "util/exception.hpp"
#include "util/utility.hpp"

#include "services/log_manager.hpp"
#include "services/ui_manager.hpp"

#include "board/emulator.hpp"

namespace otto::services {
  using P1SC = PrOTTO1SerialController;
  using Event = P1SC::Event;
  using EventBag = P1SC::EventBag;

  using byte = std::uint8_t;

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

  void P1SC::insert_key_event(Command cmd, Key key)
  {
    switch (cmd) {
      case Command::key_down: {
        keypress(key);
      } break;
      case Command::key_up: {
        keyrelease(key);
      } break;
      default: OTTO_UNREACHABLE("");
    }
  }

  void P1SC::insert_key_or_midi(Command cmd, BytesView args, bool do_send_midi)
  {
    OTTO_ASSERT(args.size() > 0, "Requires > 0 args");
    auto key = Key::_from_integral_unchecked(args.at(0));
    if (!do_send_midi) {
      insert_key_event(cmd, key);
      return;
    }

    auto send_midi = [cmd](int note) {
      if (cmd == +Command::key_down) {
        auto evt = core::midi::NoteOnEvent{note};
        AudioManager::current().send_midi_event(evt);
        LOGI("Press key {}", evt.key);
      } else if (cmd == +Command::key_up) {
        AudioManager::current().send_midi_event(core::midi::NoteOffEvent{note});
        LOGI("Release key {}", note);
      }
    };

    switch (key) {
      case Key::S0: send_midi(47); break;
      case Key::S1: send_midi(48); break;
      case Key::C0: send_midi(49); break;
      case Key::S2: send_midi(50); break;
      case Key::C1: send_midi(51); break;
      case Key::S3: send_midi(52); break;
      case Key::S4: send_midi(53); break;
      case Key::C2: send_midi(54); break;
      case Key::S5: send_midi(55); break;
      case Key::C3: send_midi(56); break;
      case Key::S6: send_midi(57); break;
      case Key::C4: send_midi(58); break;
      case Key::S7: send_midi(59); break;
      case Key::S8: send_midi(60); break;
      case Key::C5: send_midi(61); break;
      case Key::S9: send_midi(62); break;
      case Key::C6: send_midi(63); break;
      case Key::S10: send_midi(64); break;
      case Key::S11: send_midi(65); break;
      case Key::C7: send_midi(66); break;
      case Key::S12: send_midi(67); break;
      case Key::C8: send_midi(68); break;
      case Key::S13: send_midi(69); break;
      case Key::C9: send_midi(70); break;
      case Key::S14: send_midi(71); break;
      case Key::S15: send_midi(72); break;
      default: insert_key_event(cmd, key); break;
    }
  }

  auto make_message(Command cmd)
  {
    return std::vector<byte>{cmd._to_integral()};
  }

  void P1SC::queue_message(BytesView message)
  {
    write_buffer_.outer_locked([&](auto& b) {
      b.reserve(b.size() + message.size());
      util::copy(message, std::back_inserter(b));
    });
  }

  int8_t to_int8(uint8_t x)
  {
    return (x >= 128 ? x - 256 : x);
  }

  void P1SC::handle_message(BytesView bytes)
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
        insert_key_or_midi(command, bytes, send_midi_);
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

  P1SC::PrOTTO1SerialController()
    : read_thread([this](auto should_run) noexcept {
        while (should_run()) {
          serial.read_line()
            .map([&](auto&& bytes) { handle_message(bytes); })
            .map_error([&](auto&& error) {
              if (error.data() != util::Serial::ErrorCode::empty_buffer) {
                LOGE("Error reading serial data {}", error.what());
              }
            });
        }
      })
  {}

  std::unique_ptr<Controller> P1SC::make_or_dummy() {
    try {
      return std::make_unique<P1SC>();
    } catch (std::exception& e) {
      LOGE("Couldn't set up serial controller. Continuing with dummy. ERR: {}", e.what());
      return Controller::make_dummy();
    }
  }

  std::unique_ptr<Controller> P1SC::make_or_emulator() {
    try {
      return std::make_unique<P1SC>();
    } catch (std::exception& e) {
      LOGE("Couldn't set up serial controller. Continuing with dummy. ERR: {}", e.what());
      return std::make_unique<board::Emulator>();
    }
  }

  void P1SC::set_color(LED led, LEDColor color)
  {
    std::array<std::uint8_t, 6> msg = {0xEC, led.key._to_integral(), color.r, color.g, color.b,
                                       '\n'};
    queue_message(msg);
  }

  void P1SC::flush_leds()
  {
    write_buffer_.swap();
    serial.write(write_buffer_.inner());
  }
  void P1SC::clear_leds()
  {
    auto c = LEDColor::Black;
    std::array<std::uint8_t, 5> msg = {0xE0, c.r, c.g, c.b, '\n'};
    queue_message(msg);
  }

} // namespace otto::services

// kak: other_file=../include/board/controller.hpp
