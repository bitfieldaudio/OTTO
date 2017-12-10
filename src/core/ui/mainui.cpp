#include "mainui.hpp"

#include "core/globals.hpp"

namespace otto::ui {

  // Local vars
  namespace {

    struct EmptyScreen : Screen {

      void draw(vg::Canvas& ctx)
      {}

    } empty_screen;

    Screen* cur_screen = &empty_screen;

    PressedKeys keys;

  }

  bool is_pressed(Key k) noexcept
  {
    return keys[static_cast<unsigned>(k)];
  }

  void display(Screen& screen)
  {
    cur_screen->on_hide();
    cur_screen = &screen;
    cur_screen->on_show();
  }

  namespace impl {

    static bool global_keypress(Key key)
    {
      switch (key) {
      case Key::quit: global::exit(global::ErrorCode::user_exit); break;
      case Key::tape: display(global::tapedeck.screen()); break;
      case Key::mixer: display(global::mixer.screen()); break;
      case Key::synth: display(global::synth->screen()); break;
      case Key::drums: display(global::drums->screen()); break;
      case Key::metronome:
        display(global::metronome.screen());
        break;
      case ui::Key::play:
        if (global::tapedeck.state.playing()) {
          global::tapedeck.state.stop();
        } else {
          global::tapedeck.state.play();
        }
        break;
      default: return false;
      }
      return true;
    }

    void draw_frame(vg::Canvas& ctx)
    {
      ctx.lineWidth(2);
      ctx.lineCap(vg::Canvas::LineCap::ROUND);
      ctx.lineJoin(vg::Canvas::Canvas::LineJoin::ROUND);
      cur_screen->draw(ctx);
    }

    bool keypress(Key key)
    {
      switch (key) {
      case Key::red_up: cur_screen->rotary({Rotary::Red, 1}); break;
      case Key::red_down: cur_screen->rotary({Rotary::Red, -1}); break;
      case Key::blue_up: cur_screen->rotary({Rotary::Blue, 1}); break;
      case Key::blue_down: cur_screen->rotary({Rotary::Blue, -1}); break;
      case Key::white_up: cur_screen->rotary({Rotary::White, 1}); break;
      case Key::white_down: cur_screen->rotary({Rotary::White, -1}); break;
      case Key::green_up: cur_screen->rotary({Rotary::Green, 1}); break;
      case Key::green_down: cur_screen->rotary({Rotary::Green, -1}); break;
      default:
        keys[static_cast<unsigned>(key)] = true;
        if (global_keypress(key)) return true;
        return cur_screen->keypress(key);
      }
      return true;
    }

    bool keyrelease(Key key)
    {
      keys[static_cast<unsigned>(key)] = false;
      return cur_screen->keyrelease(key);
    }

  } // namespace impl

} // namespace otto::ui
