#include "mainui.hpp"

#include "core/globals.hpp"

#include <thread>

namespace top1::ui {

  void MainUI::display(Screen& screen) {
    currentScreen->exit();
    currentScreen = &screen;
    currentScreen->init();
  }

  void MainUI::init() {
    uiThread = std::thread(MainUI::mainRoutine);
  }

  void MainUI::exit() {
    uiThread.join();
  }

  void MainUI::draw(drawing::Canvas& ctx) {
    currentScreen->draw(ctx);
  }

  bool MainUI::keypress(ui::Key key) {
    keys[key] = true;
    if (globKeyPre(key)) return true;
    if (currentScreen->keypress(key)) return true;
    return globKeyPost(key);
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

} // top1::ui
