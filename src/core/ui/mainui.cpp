#include "mainui.hpp"

#include "core/globals.hpp"

#include <thread>

namespace otto::ui {

  void MainUI::display(Screen& screen) {
    currentScreen->exit();
    currentScreen = &screen;
    currentScreen->init();
  }

  void MainUI::init() {
  }

  void MainUI::exit() {
  }

  void MainUI::draw(vg::Canvas& ctx) {
    ctx.lineWidth(2);
    ctx.lineCap(vg::Canvas::LineCap::ROUND);
    ctx.lineJoin(vg::Canvas::Canvas::LineJoin::ROUND);
    currentScreen->draw(ctx);
  }

  bool MainUI::keypress(ui::Key key) {
    switch (key) {
    case K_RED_UP:
      currentScreen->rotary({Rotary::Red, 1}); break;
    case K_RED_DOWN:
      currentScreen->rotary({Rotary::Red, -1}); break;
    case K_BLUE_UP:
      currentScreen->rotary({Rotary::Blue, 1}); break;
    case K_BLUE_DOWN:
      currentScreen->rotary({Rotary::Blue, -1}); break;
    case K_WHITE_UP:
      currentScreen->rotary({Rotary::White, 1}); break;
    case K_WHITE_DOWN:
      currentScreen->rotary({Rotary::White, -1}); break;
    case K_GREEN_UP:
      currentScreen->rotary({Rotary::Green, 1}); break;
    case K_GREEN_DOWN:
      currentScreen->rotary({Rotary::Green, -1}); break;
    default:
      keys[key] = true;
      if (globKeyPre(key)) return true;
      if (currentScreen->keypress(key)) return true;
      return globKeyPost(key);
    }
    return true;
  }

  bool MainUI::keyrelease(ui::Key key) {
    keys[key] = false;
    return currentScreen->keyrelease(key);
  }

  bool MainUI::globKeyPost(ui::Key key) {
    switch (key) {
    case ui::K_PLAY:
      if (Globals::tapedeck.state.playing()) {
        Globals::tapedeck.state.stop();
      } else {
        Globals::tapedeck.state.play();
      }
      return true;
    default:
      return false;
    }
  }

  bool MainUI::globKeyPre(ui::Key key) {
    using namespace ui;
    switch (key) {
    case K_QUIT:
      Globals::exit();
      break;
    case K_TAPE:
      Globals::tapedeck.display();
      break;
    case K_MIXER:
      Globals::mixer.display();
      break;
    case K_SYNTH:
      Globals::synth.display();
      break;
    case K_DRUMS:
      Globals::drums.display();
      break;
    case K_METRONOME:
      Globals::metronome.display();
      break;
    default:
      return false;
    }
    return true;
  }

} // otto::ui
