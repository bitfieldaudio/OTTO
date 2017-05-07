#include "testsynth.h"
#include "../globals.h"
#include "testsynth.faust.h"
#include "../ui/utils.h"
#include "../ui/mainui.h"
#include <string>

TestSynth::TestSynth() :
  FaustSynthModule(new testsynth(), {
    {"FREQ", &frequency}
  }),
  screen (new TestSynthScreen(this))
{
  //MainUI::getInstance().currentScreen = screen;
}

TestSynth::~TestSynth() {
  delete fDSP;
  delete screen;
}

void TestSynthScreen::draw(NanoCanvas::Canvas& ctx) {
  using namespace ui;
  using namespace drawing;
}

bool TestSynthScreen::keypress(ui::Key key, bool shift) {
  switch (key) {
  case ui::K_RED_UP:
    *module->frequency += 10;
    return true;
  case ui::K_RED_DOWN:
    *module->frequency -= 10;
    return true;
  default:
    return false;
  }
}
