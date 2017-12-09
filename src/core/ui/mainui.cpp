#include "mainui.hpp"

#include "core/globals.hpp"

#include <thread>

namespace otto::ui {

  void MainUI::display(Screen& screen)
  {
    currentScreen->exit();
    currentScreen = &screen;
    currentScreen->init();
  }

  void MainUI::init()
  {}

  void MainUI::exit()
  {}

  void MainUI::draw(vg::Canvas& ctx)
  {
    ctx.lineWidth(2);
    ctx.lineCap(vg::Canvas::LineCap::ROUND);
    ctx.lineJoin(vg::Canvas::Canvas::LineJoin::ROUND);
    currentScreen->draw(ctx);
  }

  bool MainUI::keypress(ui::Key key)
  {
    switch (key) {
    case Key::red_up:
      currentScreen->rotary({Rotary::Red, 1}); break;
    case Key::red_down:
      currentScreen->rotary({Rotary::Red, -1}); break;
    case Key::blue_up:
      currentScreen->rotary({Rotary::Blue, 1}); break;
    case Key::blue_down:
      currentScreen->rotary({Rotary::Blue, -1}); break;
    case Key::white_up:
      currentScreen->rotary({Rotary::White, 1}); break;
    case Key::white_down:
      currentScreen->rotary({Rotary::White, -1}); break;
    case Key::green_up:
      currentScreen->rotary({Rotary::Green, 1}); break;
    case Key::green_down:
      currentScreen->rotary({Rotary::Green, -1}); break;
    default:
      keys[key] = true;
      if (globKeyPre(key)) return true;
      if (currentScreen->keypress(key)) return true;
      return globKeyPost(key);
    }
    return true;
  }

  bool MainUI::keyrelease(ui::Key key)
  {
    keys[key] = false;
    return currentScreen->keyrelease(key);
  }

  bool MainUI::globKeyPost(ui::Key key)
  {
    switch (key) {
    case ui::Key::play:
      if (global::tapedeck.state.playing()) {
        global::tapedeck.state.stop();
      } else {
        global::tapedeck.state.play();
      }
      return true;
    default:
      return false;
    }
  }

  bool MainUI::globKeyPre(ui::Key key)
  {
    using namespace ui;
    switch (key) {
    case Key::quit:
      global::exit(global::ErrorCode::user_exit);
      break;
    case Key::tape:
      global::ui.display(global::tapedeck.screen());
      break;
    case Key::mixer:
      global::ui.display(global::mixer.screen());
      break;
    case Key::synth:
      global::ui.display(global::synth->screen());
      break;
    case Key::drums:
      global::ui.display(global::drums->screen());
      break;
    case Key::metronome:
      global::ui.display(global::metronome.screen());
      break;
    default:
      return false;
    }
    return true;
  }

} // otto::ui
