#include "base.h"
#include "mainui.h"
#include "utils.h"
#include "../globals.h"

#include <thread>

void MainUI::init() {
  auto& self = getInstance();

  self.uiThread = std::thread(MainUI::mainRoutine);
  self.uiThread.join();
}

void MainUI::draw(NanoCanvas::Canvas& ctx) {
  using namespace drawing;
  currentScreen->draw(ctx);
}

bool MainUI::keypress(ui::Key key, bool shift) {
  if (globKeyPre(key)) return true;
  if (currentScreen->keypress(key, shift)) return true;
  return globKeyPost(key);
}

bool MainUI::keyrelease(ui::Key key, bool shift) {
  return currentScreen->keyrelease(key, shift);
}

bool MainUI::globKeyPost(ui::Key key) {
  switch (key) {
  case ui::K_PLAY:
    if (GLOB.tapedeck->playing) {
      GLOB.tapedeck->stop();
    } else {
      GLOB.tapedeck->play(1);
    }
    return true;
  }
  return false;
}

bool MainUI::globKeyPre(ui::Key key) {
  using namespace ui;
  switch (key) {
  case K_QUIT:
    GLOB.running = false;
    break;
  case K_TAPE:
    currentScreen = GLOB.tapedeck->tapeScreen;
    break;
  case K_MIXER:
    currentScreen = GLOB.mixer->screen;
    break;
  default:
    return false;
  }
  return true;
}
