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

bool MainUI::keypress(ui::Key key) {
  if (globKeyPre(key)) return true;
  if (currentScreen->keypress(key)) return true;
  return globKeyPost(key);
}

bool MainUI::keyrelease(ui::Key key) {
  return currentScreen->keyrelease(key);
}

bool MainUI::globKeyPost(ui::Key key) {
  return false;
}

bool MainUI::globKeyPre(ui::Key key) {
  using namespace ui;
  switch (key) {
  case K_QUIT:
    GLOB.running = false;
    break;
  default:
    return false;
  }
  return true;
}
