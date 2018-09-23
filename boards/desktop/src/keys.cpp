#include "board/ui/keys.hpp"

#include "services/audio.hpp"
#include "services/ui.hpp"

#include "services/logger.hpp"

namespace otto::board::ui {

  void handle_keyevent(Action action, Modifiers mods, Key key)
  {
    auto send_midi = [action](int note) {
      if (action == Action::press) {
        auto evt = core::midi::NoteOnEvent{note};
        service::audio::send_midi_event(evt);
        LOGI("Press key {}", evt.key);
      } else if (action == Action::release) {
        service::audio::send_midi_event(core::midi::NoteOffEvent{note});
        LOGI("Release key {}", note);
      }
    };

    using OKey = core::ui::Key;

    auto send_key = [action](OKey k, bool repeat = false) {
      if (action == Action::press || (action == Action::repeat && repeat))
        service::ui::impl::keypress(k);
      else if (action == Action::release)
        service::ui::impl::keyrelease(k);
    };

    auto send_rotary = [action](core::ui::Rotary rot, int n) {
      if (action == Action::press || (action == Action::repeat))
        service::ui::impl::rotary({rot, n});
    };


    if (mods & Modifier::alt) {
      switch (key) {
      case Key::q: send_midi(17); return;
      case Key::n2: send_midi(18); return;
      case Key::w: send_midi(19); return;
      case Key::n3: send_midi(20); return;
      case Key::e: send_midi(21); return;
      case Key::r: send_midi(22); return;
      case Key::n5: send_midi(23); return;
      case Key::t: send_midi(24); return;
      case Key::n6: send_midi(25); return;
      case Key::y: send_midi(26); return;
      case Key::n7: send_midi(27); return;
      case Key::u: send_midi(28); return;
      case Key::i: send_midi(29); return;
      case Key::n9: send_midi(30); return;
      case Key::o: send_midi(31); return;
      case Key::n0: send_midi(32); return;
      case Key::p: send_midi(33); return;
      default: break;
      }
    }

    bool ctrl = mods & Modifier::ctrl;
    switch (key) {
      // Rotaries
    case Key::q:
      if (ctrl)
        send_key(OKey::blue_click);
      else
        send_rotary(core::ui::Rotary::Blue, 1);
      break;
    case Key::a:
      if (ctrl)
        send_key(OKey::blue_click);
      else
        send_rotary(core::ui::Rotary::Blue, -1);
      break;
    case Key::w:
      if (ctrl)
        send_key(OKey::green_click);
      else
        send_rotary(core::ui::Rotary::Green, 1);
      break;
    case Key::s:
      if (ctrl)
        send_key(OKey::green_click);
      else
        send_rotary(core::ui::Rotary::Green, -1);
      break;
    case Key::e:
      if (ctrl)
        send_key(OKey::white_click);
      else
        send_rotary(core::ui::Rotary::White, 1);
      break;
    case Key::d:
      if (ctrl)
        send_key(OKey::white_click);
      else
        send_rotary(core::ui::Rotary::White, -1);
      break;
    case Key::r:
      if (ctrl)
        send_key(OKey::red_click);
      else
        send_rotary(core::ui::Rotary::Red, 1);
      break;
    case Key::f:
      if (ctrl)
        send_key(OKey::red_click);
      else
        send_rotary(core::ui::Rotary::Red, -1);
      break;

    // Engines
    case Key::n1: send_key(OKey::sequencer); break;
    case Key::n2: send_key(OKey::synth); break;
    case Key::n3: send_key(OKey::envelope); break;
    case Key::n4: send_key(OKey::voices); break;
    case Key::n5: send_key(OKey::fx1); break;

    case Key::p: send_key(OKey::play); break;
    case Key::m: send_key(OKey::master); break;

    case Key::left_shift: [[fallthrough]];
    case Key::right_shift: send_key(OKey::shift); break;

    default: break;
    }
  }
} // namespace otto::board::ui
