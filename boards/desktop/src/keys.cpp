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

    if (mods & Modifier::alt) {
      switch (key) {
      case Key::q:  send_midi(17); return;
      case Key::n2: send_midi(18); return;
      case Key::w:  send_midi(19); return;
      case Key::n3: send_midi(20); return;
      case Key::e:  send_midi(21); return;
      case Key::r:  send_midi(22); return;
      case Key::n5: send_midi(23); return;
      case Key::t:  send_midi(24); return;
      case Key::n6: send_midi(25); return;
      case Key::y:  send_midi(26); return;
      case Key::n7: send_midi(27); return;
      case Key::u:  send_midi(28); return;
      case Key::i:  send_midi(29); return;
      case Key::n9: send_midi(30); return;
      case Key::o:  send_midi(31); return;
      case Key::n0: send_midi(32); return;
      case Key::p:  send_midi(33); return;
      default: break;
      }
    }

    bool ctrl = mods & Modifier::ctrl;
    switch (key) {
      // Rotaries
    case Key::q: send_key(ctrl ? OKey::blue_click  : OKey::blue_up, !ctrl); break;
    case Key::a: send_key(ctrl ? OKey::blue_click  : OKey::blue_down, !ctrl); break;
    case Key::w: send_key(ctrl ? OKey::green_click : OKey::green_up, !ctrl); break;
    case Key::s: send_key(ctrl ? OKey::green_click : OKey::green_down, !ctrl); break;
    case Key::e: send_key(ctrl ? OKey::white_click : OKey::white_up, !ctrl); break;
    case Key::d: send_key(ctrl ? OKey::white_click : OKey::white_down, !ctrl); break;
    case Key::r: send_key(ctrl ? OKey::red_click   : OKey::red_up, !ctrl); break;
    case Key::f: send_key(ctrl ? OKey::red_click   : OKey::red_down, !ctrl); break;

    case Key::left: send_key(OKey::left); break;
    case Key::right: send_key(OKey::right); break;

      // Tapedeck
    case Key::p: send_key(OKey::play); break;
    case Key::z: send_key(OKey::rec); break;
    case Key::f1: send_key(OKey::track_1); break;
    case Key::f2: send_key(OKey::track_2); break;
    case Key::f3: send_key(OKey::track_3); break;
    case Key::f4: send_key(OKey::track_4); break;

      // Numbers
    case Key::t: if (ctrl) send_key(OKey::tape); break;
    case Key::y: if (ctrl) send_key(OKey::mixer); break;
    case Key::u: if (ctrl) send_key(OKey::synth); break;
    case Key::g: if (ctrl) send_key(OKey::metronome); break;
    case Key::h: if (ctrl) send_key(OKey::sequencer); break;
    case Key::j: if (ctrl) send_key(OKey::drums); break;
    case Key::k: if (ctrl) send_key(OKey::envelope); break;

    case Key::l: send_key(OKey::loop); break;
    case Key::i: send_key(OKey::loop_in); break;
    case Key::o: send_key(OKey::loop_out); break;

    case Key::x: send_key(OKey::cut); break;
    case Key::c: if (ctrl) send_key(OKey::lift); 
    case Key::v: if (ctrl) send_key(OKey::drop); break;

    case Key::left_shift: [[fallthrough]];
    case Key::right_shift: send_key(OKey::shift); break;

    default: break;
    }
  }
} // namespace otto::board::ui
