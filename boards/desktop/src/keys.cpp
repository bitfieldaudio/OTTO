#include "board/ui/keys.hpp"

#include "services/ui.hpp"
#include "services/audio.hpp"

namespace otto::board::ui {

  void handle_keyevent(Action action, Modifiers mods, Key key)
  {
    using OKey = core::ui::Key;
    OKey k = [key, mods]() {
      switch (key) {
        // Rotaries
      case Key::q:
        if (mods & Modifier::ctrl) return OKey::blue_click;
        return OKey::blue_up;
      case Key::a:
        if (mods & Modifier::ctrl) return OKey::blue_click;
        return OKey::blue_down;
      case Key::w:
        if (mods & Modifier::ctrl) return OKey::green_click;
        return OKey::green_up;
      case Key::s:
        if (mods & Modifier::ctrl) return OKey::green_click;
        return OKey::green_down;
      case Key::e:
        if (mods & Modifier::ctrl) return OKey::white_click;
        return OKey::white_up;
      case Key::d:
        if (mods & Modifier::ctrl) return OKey::white_click;
        return OKey::white_down;
      case Key::r:
        if (mods & Modifier::ctrl) return OKey::red_click;
        return OKey::red_up;
      case Key::f:
        if (mods & Modifier::ctrl) return OKey::red_click;
        return OKey::red_down;

      case Key::left: return OKey::left;
      case Key::right:
        return OKey::right;

        // Tapedeck
      case Key::space: return OKey::play;
      case Key::z: return OKey::rec;
      case Key::f1: return OKey::track_1;
      case Key::f2: return OKey::track_2;
      case Key::f3: return OKey::track_3;
      case Key::f4:
        return OKey::track_4;

        // Numbers
      case Key::t:
        if (mods & Modifier::ctrl)
          return OKey::tape;
        else
          break;
      case Key::y:
        if (mods & Modifier::ctrl)
          return OKey::mixer;
        else
          break;
      case Key::u:
        if (mods & Modifier::ctrl)
          return OKey::synth;
        else
          break;
      case Key::g:
        if (mods & Modifier::ctrl)
          return OKey::metronome;
        else
          break;
      case Key::h:
        if (mods & Modifier::ctrl)
          return OKey::sampler;
        else
          break;
      case Key::j:
        if (mods & Modifier::ctrl)
          return OKey::drums;
        else
          break;
      case Key::k:
        if (mods & Modifier::ctrl)
          return OKey::envelope;
        else
          break;

      case Key::l: return OKey::loop;
      case Key::i: return OKey::loop_in;
      case Key::o: return OKey::loop_out;

      case Key::x: return OKey::cut;
      case Key::c:
        if (mods & Modifier::ctrl)
          return OKey::lift;
        else
          break;
      case Key::v:
        if (mods & Modifier::ctrl) return OKey::drop;

      case Key::left_shift:
      case Key::right_shift: return OKey::shift;

      default: return OKey::none;
      }
      return OKey::none;
    }();

    int note;

    namespace midi = core::midi;

    if (mods & Modifier::alt) {
      note = [key] () {
        switch (key) {
          case Key::q:  return midi::note_number("C0");
          case Key::n2: return midi::note_number("C#0");
          case Key::w:  return midi::note_number("D0");
          case Key::n3: return midi::note_number("D#0");
          case Key::e:  return midi::note_number("E0");
          case Key::r:  return midi::note_number("F0");
          case Key::n5: return midi::note_number("F#0");
          case Key::t:  return midi::note_number("G0");
          case Key::n6: return midi::note_number("G#0");
          case Key::y:  return midi::note_number("A1");
          case Key::n7: return midi::note_number("A#1");
          case Key::u:  return midi::note_number("B1");
          case Key::i:  return midi::note_number("C1");
          case Key::n9: return midi::note_number("C#1");
          case Key::o:  return midi::note_number("D1");
          case Key::n0: return midi::note_number("D#1");
          case Key::p:  return midi::note_number("E1");
          default: return -1;
        }
      }();
    }

    if (action == Action::press)
    {
      if (note >= 0) service::audio::send_midi_event(midi::NoteOnEvent{note});
      else if (k != OKey::none) service::ui::impl::keypress(k);
    }
    else if (action == Action::repeat)
    {
      switch (k) {
      case OKey::red_up:
      case OKey::red_down:
      case OKey::blue_up:
      case OKey::blue_down:
      case OKey::white_up:
      case OKey::white_down:
      case OKey::green_up:
      case OKey::green_down:
      case OKey::left:
      case OKey::right: service::ui::impl::keypress(k);
      default: break;
      }
    }
    else if (action == Action::release)
    {
      if (note >= 0) service::audio::send_midi_event(midi::NoteOffEvent{note});
      else if (k != OKey::none) service::ui::impl::keyrelease(k);
    }
  }
} // namespace otto::board::ui
