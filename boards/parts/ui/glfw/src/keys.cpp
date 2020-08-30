#include "board/ui/keys.hpp"

#include "app/services/controller.hpp"

namespace otto::board {

  void handle_keyevent(glfw::Action action,
                       glfw::Modifiers mods,
                       glfw::Key key,
                       itc::IExecutor& executor,
                       InputHandler& handler)
  {
    using glfw::Action;
    using glfw::Key;
    using glfw::Modifier;
    using OKey = otto::Key;

    auto send_event = [&](auto event) { executor.execute([event, &handler] { handler.handle(event); }); };

    auto send_key = [&, action](OKey k, bool repeat = false) {
      if (action == Action::press || (action == Action::repeat && repeat))
        send_event(KeyPress{k});
      else if (action == Action::release)
        send_event(KeyRelease{k});
    };

    auto send_encoder = [&, action](Encoder rot, int n) {
      if (action == Action::press || (action == Action::repeat)) send_event(EncoderEvent{rot, n});
    };


    if (mods & Modifier::alt) {
      switch (key) {
        // TODO: case Key::space: send_sustain(); return;
        case Key::q: send_key(OKey::seq0); return;
        case Key::w: send_key(OKey::seq1); return;
        case Key::e: send_key(OKey::seq2); return;
        case Key::r: send_key(OKey::seq3); return;
        case Key::t: send_key(OKey::seq4); return;
        case Key::y: send_key(OKey::seq5); return;
        case Key::u: send_key(OKey::seq6); return;
        case Key::i: send_key(OKey::seq7); return;
        case Key::o: send_key(OKey::seq8); return;
        case Key::p: send_key(OKey::seq9); return;
        case Key::z: send_key(OKey::seq8); return;
        case Key::x: send_key(OKey::seq9); return;
        case Key::c: send_key(OKey::seq10); return;
        case Key::v: send_key(OKey::seq11); return;
        case Key::b: send_key(OKey::seq12); return;
        case Key::n: send_key(OKey::seq13); return;
        case Key::m: send_key(OKey::seq14); return;
        case Key::comma: send_key(OKey::seq15); return;
        case Key::n3: send_key(OKey::channel0); return;
        case Key::n4: send_key(OKey::channel1); return;
        case Key::n6: send_key(OKey::channel2); return;
        case Key::n7: send_key(OKey::channel3); return;
        case Key::n8: send_key(OKey::channel4); return;
        case Key::n0: send_key(OKey::channel5); return;
        case Key::s: send_key(OKey::channel5); return;
        case Key::d: send_key(OKey::channel6); return;
        case Key::g: send_key(OKey::channel7); return;
        case Key::h: send_key(OKey::channel8); return;
        case Key::j: send_key(OKey::channel9); return;
        default: return;
      }
    }

    bool ctrl = mods & Modifier::ctrl;
    switch (key) {
        // Rotaries
      case Key::q:
        if (ctrl)
          send_key(OKey::blue_enc_click);
        else
          send_encoder(Encoder::blue, 1);
        break;
      case Key::a:
        if (ctrl)
          send_key(OKey::blue_enc_click);
        else
          send_encoder(Encoder::blue, -1);
        break;
      case Key::w:
        if (ctrl)
          send_key(OKey::green_enc_click);
        else
          send_encoder(Encoder::green, 1);
        break;
      case Key::s:
        if (ctrl)
          send_key(OKey::green_enc_click);
        else
          send_encoder(Encoder::green, -1);
        break;
      case Key::e:
        if (ctrl)
          send_key(OKey::yellow_enc_click);
        else
          send_encoder(Encoder::yellow, 1);
        break;
      case Key::d:
        if (ctrl)
          send_key(OKey::yellow_enc_click);
        else
          send_encoder(Encoder::yellow, -1);
        break;
      case Key::r:
        if (ctrl)
          send_key(OKey::red_enc_click);
        else
          send_encoder(Encoder::red, 1);
        break;
      case Key::f:
        if (ctrl)
          send_key(OKey::red_enc_click);
        else
          send_encoder(Encoder::red, -1);
        break;

        // Engines
        // case Key::n1: send_key(OKey::arp); break;
        // case Key::n2: send_key(OKey::synth); break;
        // case Key::n3: send_key(OKey::envelope); break;
        // case Key::n4: send_key(OKey::voices); break;
        // case Key::n5: send_key(OKey::fx1); break;
        // case Key::n6: send_key(OKey::fx2); break;
        // case Key::n8: send_key(OKey::sequencer); break;
        // case Key::p: send_key(OKey::play); break;
        // case Key::m: send_key(OKey::master); break;

        // case Key::up: send_key(OKey::plus); break;
        // case Key::down: send_key(OKey::minus); break;

        // case Key::n7: send_key(OKey::sends); break;

        // case Key::left_shift: [[fallthrough]];
        // case Key::right_shift: send_key(OKey::shift); break;

      default: break;
    }
  }
} // namespace otto::board

// kak: other_file=../include/board/ui/keys.hpp
