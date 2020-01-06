#include "controller.hpp"

#include "services/audio_manager.hpp"
#include "services/ui_manager.hpp"
#include "util/iterator.hpp"
#include "util/utility.hpp"

namespace otto::services {

  using Event = Controller::Event;
  using EventBag = Controller::EventBag;
  using namespace core::input;

  static bool send_midi_for(Key key, bool press)
  {
    if (UIManager::current().state.key_mode != KeyMode::midi) return false;
    auto send_midi = [press](int note) {
      note += 12 * UIManager::current().state.octave;
      if (press) {
        auto evt = core::midi::NoteOnEvent{note};
        AudioManager::current().send_midi_event(evt);
        DLOGI("Press key {}", evt.key);
      } else {
        AudioManager::current().send_midi_event(core::midi::NoteOffEvent{note});
        DLOGI("Release key {}", note);
      }
    };
    switch (key) {
      case Key::S0: send_midi(47); return true;
      case Key::S1: send_midi(48); return true;
      case Key::C0: send_midi(49); return true;
      case Key::S2: send_midi(50); return true;
      case Key::C1: send_midi(51); return true;
      case Key::S3: send_midi(52); return true;
      case Key::S4: send_midi(53); return true;
      case Key::C2: send_midi(54); return true;
      case Key::S5: send_midi(55); return true;
      case Key::C3: send_midi(56); return true;
      case Key::S6: send_midi(57); return true;
      case Key::C4: send_midi(58); return true;
      case Key::S7: send_midi(59); return true;
      case Key::S8: send_midi(60); return true;
      case Key::C5: send_midi(61); return true;
      case Key::S9: send_midi(62); return true;
      case Key::C6: send_midi(63); return true;
      case Key::S10: send_midi(64); return true;
      case Key::S11: send_midi(65); return true;
      case Key::C7: send_midi(66); return true;
      case Key::S12: send_midi(67); return true;
      case Key::C8: send_midi(68); return true;
      case Key::S13: send_midi(69); return true;
      case Key::C9: send_midi(70); return true;
      case Key::S14: send_midi(71); return true;
      case Key::S15: send_midi(72); return true;
      default: return false;
    }
  }

  bool Controller::keypress(Key key)
  {
    if (!send_midi_for(key, true)) events_.outer().push_back(KeyPressEvent{key});
    key_handler_thread.trigger();
    return true;
  }

  void Controller::encoder(EncoderEvent ev)
  {
    events_.outer().push_back(ev);
    key_handler_thread.trigger();
  }

  bool Controller::keyrelease(Key key)
  {
    if (!send_midi_for(key, false)) events_.outer().push_back(KeyReleaseEvent{key});
    key_handler_thread.trigger();
    return true;
  }

  bool Controller::is_pressed(Key k) noexcept
  {
    return keys[k._to_index()];
  }

  void Controller::register_key_handler(Key k, KeyHandler press_handler, KeyHandler release_handler)
  {
    key_handlers.emplace(k, std::pair{std::move(press_handler), std::move(release_handler)});
  }

  bool Controller::handle_global(Key key, bool is_press)
  {
    auto [first, last] = key_handlers.equal_range(key);
    if (first == last) return false;

    for (auto&& [key, funcs] : nano::subrange(first, last)) {
      auto& func = is_press ? funcs.first : funcs.second;
      if (func) func(key);
    }

    return true;
  }

  Controller::Controller()
    : key_handler_thread([this](auto&& should_run) {
        while ((!events_.inner().empty() || !action_queue_.empty()) || should_run()) {
          events_.swap();
          for (auto& event : events_.inner()) {
            signals.on_input.emit(event);
            util::match(
              event,
              [this](KeyPressEvent& ev) {
                keys[ev.key._to_index()] = true;
                if (handle_global(ev.key)) return;
                UIManager::current().current_input_handler().keypress(ev.key);
              },
              [this](KeyReleaseEvent& ev) {
                keys[ev.key._to_index()] = false;
                if (handle_global(ev.key, false)) return;
                UIManager::current().current_input_handler().keyrelease(ev.key);
              },
              [](EncoderEvent& ev) { UIManager::current().current_input_handler().encoder(ev); });
          }
          action_queue_.pop_call_all();
        }
      })
  {}

  // DummyController //
  struct DummyController final : Controller {
    void set_color(LED, LEDColor) override {}
    void flush_leds() override {}
    void clear_leds() override {}
  };

  std::unique_ptr<Controller> Controller::make_dummy()
  {
    return std::make_unique<DummyController>();
  }

} // namespace otto::services
