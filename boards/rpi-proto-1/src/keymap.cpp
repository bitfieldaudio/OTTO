#include <cstdlib>

#include "board/ui/keys.hpp"

#include "services/audio.hpp"
#include "services/ui.hpp"

namespace otto::board::ui {

  void handle_keyevent(Action action, Modifiers mods, Key key)
  {
    auto send_midi = [action](int note) {
      note += 36;
      if (action == Action::press) {
        auto evt = core::midi::NoteOnEvent{note};
        service::audio::send_midi_event(evt);
        LOGI("Press key {}", evt.key);
      } else if (action == Action::release) {
        service::audio::send_midi_event(core::midi::NoteOffEvent{note});
        LOGI("Release key {}", note);
      }
    };

    using OKey = otto::core::ui::Key;

    auto send_key = [action](OKey k, bool repeat = false) {
      if (action == Action::press || (action == Action::repeat && repeat))
        service::ui::impl::keypress(k);
      else if (action == Action::release)
        service::ui::impl::keyrelease(k);
    };

    auto shutdown = [action] {
      if (action == Action::press) std::system("halt");
    };

    // The function key
    static bool func = false;

    switch (key) {
    // Midi
    case Key::a: send_midi(17); break;
    case Key::b: send_midi(18); break;
    case Key::c: send_midi(19); break;
    case Key::d: send_midi(20); break;
    case Key::e: send_midi(21); break;
    case Key::f: send_midi(22); break;
    case Key::g: send_midi(23); break;
    case Key::h: send_midi(24); break;
    case Key::i: send_midi(25); break;
    case Key::j: send_midi(26); break;
    case Key::k: send_midi(27); break;
    case Key::l: send_midi(28); break;
    case Key::m: send_midi(29); break;
    case Key::n: send_midi(30); break;
    case Key::o: send_midi(31); break;
    case Key::p: send_midi(32); break;
    case Key::q: send_midi(33); break;
    case Key::r: send_midi(34); break;
    case Key::s: send_midi(35); break;
    case Key::t: send_midi(36); break;
    case Key::u: send_midi(37); break;
    case Key::v: send_midi(38); break;
    case Key::w: send_midi(39); break;
    case Key::x: send_midi(40); break;

    // Modifiers
    case Key::period: send_key(OKey::shift); break;
    case Key::comma: func = (action != Action::release); break;

    // Rotary emulation
    case Key::f1: send_key(func ? OKey::blue_click : OKey::blue_up, !func); break;
    case Key::f2: send_key(func ? OKey::green_click : OKey::green_up, !func); break;
    case Key::f3: send_key(func ? OKey::white_click : OKey::white_up, !func); break;
    case Key::f4: send_key(func ? OKey::red_click : OKey::red_up, !func); break;
    case Key::f5: send_key(func ? OKey::blue_click : OKey::blue_down, !func); break;
    case Key::f6: send_key(func ? OKey::green_click : OKey::green_down, !func); break;
    case Key::f7: send_key(func ? OKey::white_click : OKey::white_down, !func); break;
    case Key::f8: send_key(func ? OKey::red_click : OKey::red_down, !func); break;

    case Key::space: send_key(OKey::synth); break;
    case Key::left_control: send_key(OKey::drums); break;
    case Key::left_shift: send_key(OKey::envelope); break;

    case Key::enter: func ? shutdown() : send_key(OKey::tape); break;
    case Key::y: send_key(OKey::mixer); break;
    case Key::z: send_key(OKey::metronome); break;

    case Key::n1: send_key(OKey::rec); break;
    case Key::n2: send_key(OKey::play); break;
    case Key::n3: send_key(OKey::loop); break;
    case Key::n4: send_key(OKey::ret); break;

    case Key::n5: send_key(OKey::left); break;
    case Key::n6: send_key(OKey::right); break;
    case Key::n7: send_key(OKey::lift); break;
    case Key::n8: send_key(OKey::drop); break;

    default: break;
    }
  }

} // namespace otto::board::ui
