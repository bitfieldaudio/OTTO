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

void TestSynthScreen::draw(const ui::ContextPtr& cr) {
  using namespace ui;
  using namespace drawing;

  auto text1 = Pango::Layout::create(cr);
  text1->set_text(std::to_string(*module->frequency));
  text1->set_font_description(FONT_BIG_NUM);
  int tw, th;
  text1->get_pixel_size(tw, th);

  cr->set_source(COLOR_RED);

  cr->move_to((WIDTH - tw) / 2, (HEIGHT - th) / 2);
  text1->show_in_cairo_context(cr);
}

bool TestSynthScreen::keypress(ui::Key key) {
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
