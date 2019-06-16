#include "controller.hpp"

#include "util/iterator.hpp"
#include "util/utility.hpp"

#include "services/ui_manager.hpp"
#include "services/audio_manager.hpp"

namespace otto::services {

  using Event = Controller::Event;
  using EventBag = Controller::EventBag;

  static void send_midi_for(Key key, bool press) {
    auto send_midi = [press](int note) {
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
      default: break;
    }
  }

  void Controller::keypress(Key key)
  {
    events.outer().push_back(KeyPressEvent{key});
    send_midi_for(key, true);
  }

  void Controller::encoder(EncoderEvent ev)
  {
    events.outer().push_back(ev);
  }

  void Controller::keyrelease(Key key)
  {
    events.outer().push_back(KeyReleaseEvent{key});
    send_midi_for(key, false);
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

    for (auto&& [key, funcs] : util::sequence(first, last)) {
      auto& func = is_press ? funcs.first : funcs.second;
      if (func) func(key);
    }

    return true;
  }

  void Controller::flush_events()
  {
    events.swap();
    for (auto& event : events.inner()) {
      util::match(event,
                  [this](KeyPressEvent& ev) {
                    keys[ev.key._to_index()] = true;
                    if (handle_global(ev.key)) return;
                    UIManager::current().current_screen().keypress(ev.key);
                  },
                  [this](KeyReleaseEvent& ev) {
                    keys[ev.key._to_index()] = false;
                    if (handle_global(ev.key, false)) return;
                    UIManager::current().current_screen().keyrelease(ev.key);
                  },
                  [](EncoderEvent& ev) {
                    UIManager::current().current_screen().encoder(ev);
                  });
    }
  }


  // DummyController //
  struct DummyController final : Controller {
    void set_color(LED, LEDColor) override {}
    void flush_leds() override {}
    void clear_leds() override {}
  };

  std::unique_ptr<Controller> Controller::make_dummy() {
    return std::make_unique<DummyController>();
  }

} // namespace otto::services
