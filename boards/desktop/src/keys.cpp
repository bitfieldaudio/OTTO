#include "board/ui/keys.hpp"

#include "services/audio_manager.hpp"
#include "services/controller.hpp"
#include "services/ui_manager.hpp"

#include "services/log_manager.hpp"

namespace otto::board::ui {

  void handle_keyevent(Action action, Modifiers mods, Key key, core::input::InputHandler& input)
  {
    /*    auto send_midi = [action](int note) {
          if (action == Action::press) {
            auto evt = core::midi::NoteOnEvent{note};
            Application::current().audio_manager->send_midi_event(evt);
            LOGI("Press key {}", evt.key);
          } else if (action == Action::release) {
            Application::current().audio_manager->send_midi_event(core::midi::NoteOffEvent{note});
            LOGI("Release key {}", note);
          }
        };
    */
    auto send_sustain = [action] {
      if (!Application::has_current()) return;
      if (action == Action::press) {
        Application::current().audio_manager->send_midi_event(core::midi::ControlChangeEvent{0x40, 64});
        LOGI("Sustain down");
      } else if (action == Action::release) {
        Application::current().audio_manager->send_midi_event(core::midi::ControlChangeEvent{0x40, 0});
        LOGI("Sustain released");
      }
    };

    using OKey = core::input::Key;
    using Encoder = core::input::Encoder;

    auto send_key = [&, action](OKey k, bool repeat = false) {
      if (action == Action::press || (action == Action::repeat && repeat))
        input.keypress(k);
      else if (action == Action::release)
        input.keyrelease(k);
    };

    auto send_encoder = [&, action](core::input::Encoder rot, int n) {
      if (action == Action::press || (action == Action::repeat)) input.encoder({rot, n});
    };


    if (mods & Modifier::alt) {
      switch (key) {
        case Key::space: send_sustain(); return;
        case Key::q: send_key(OKey::S0); return;
        case Key::w: send_key(OKey::S1); return;
        case Key::e: send_key(OKey::S2); return;
        case Key::r: send_key(OKey::S3); return;
        case Key::t: send_key(OKey::S4); return;
        case Key::y: send_key(OKey::S5); return;
        case Key::u: send_key(OKey::S6); return;
        case Key::i: send_key(OKey::S7); return;
        case Key::o: send_key(OKey::S8); return;
        case Key::p: send_key(OKey::S9); return;
        case Key::z: send_key(OKey::S8); return;
        case Key::x: send_key(OKey::S9); return;
        case Key::c: send_key(OKey::S10); return;
        case Key::v: send_key(OKey::S11); return;
        case Key::b: send_key(OKey::S12); return;
        case Key::n: send_key(OKey::S13); return;
        case Key::m: send_key(OKey::S14); return;
        case Key::comma: send_key(OKey::S15); return;
        case Key::n3: send_key(OKey::C0); return;
        case Key::n4: send_key(OKey::C1); return;
        case Key::n6: send_key(OKey::C2); return;
        case Key::n7: send_key(OKey::C3); return;
        case Key::n8: send_key(OKey::C4); return;
        case Key::n0: send_key(OKey::C5); return;
        case Key::s: send_key(OKey::C5); return;
        case Key::d: send_key(OKey::C6); return;
        case Key::g: send_key(OKey::C7); return;
        case Key::h: send_key(OKey::C8); return;
        case Key::j: send_key(OKey::C9); return;
        default: return;
      }
    }

    bool ctrl = mods & Modifier::ctrl;
    switch (key) {
        // Rotaries
      case Key::q:
        if (ctrl)
          send_key(OKey::blue_click);
        else
          send_encoder(Encoder::blue, 1);
        break;
      case Key::a:
        if (ctrl)
          send_key(OKey::blue_click);
        else
          send_encoder(Encoder::blue, -1);
        break;
      case Key::w:
        if (ctrl)
          send_key(OKey::green_click);
        else
          send_encoder(Encoder::green, 1);
        break;
      case Key::s:
        if (ctrl)
          send_key(OKey::green_click);
        else
          send_encoder(Encoder::green, -1);
        break;
      case Key::e:
        if (ctrl)
          send_key(OKey::yellow_click);
        else
          send_encoder(Encoder::yellow, 1);
        break;
      case Key::d:
        if (ctrl)
          send_key(OKey::yellow_click);
        else
          send_encoder(Encoder::yellow, -1);
        break;
      case Key::r:
        if (ctrl)
          send_key(OKey::red_click);
        else
          send_encoder(Encoder::red, 1);
        break;
      case Key::f:
        if (ctrl)
          send_key(OKey::red_click);
        else
          send_encoder(Encoder::red, -1);
        break;

      // Engines
      case Key::n1: send_key(OKey::arp); break;
      case Key::n2: send_key(OKey::synth); break;
      case Key::n3: send_key(OKey::envelope); break;
      // case Key::n4: send_key(OKey::voices); break;
      case Key::n5: send_key(OKey::fx1); break;
      case Key::n6: send_key(OKey::fx2); break;
      case Key::n8: send_key(OKey::sequencer); break;
      case Key::p: send_key(OKey::play); break;
      case Key::m: send_key(OKey::master); break;

      case Key::up: send_key(OKey::plus); break;
      case Key::down: send_key(OKey::minus); break;

      case Key::n7: send_key(OKey::sends); break;

      case Key::left_shift: [[fallthrough]];
      case Key::right_shift: send_key(OKey::shift); break;

      default: break;
    }
  }
} // namespace otto::board::ui
