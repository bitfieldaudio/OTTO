#include "base.h"
#include "utils.h"
#include "../globals.h"

#include <pangomm/layout.h>

namespace ui {

bool DefaultScreen::draw(const ContextPtr& cr) {
  using namespace drawing;

  auto text1 = Pango::Layout::create(cr);
  text1->set_text("TOP-1");
  text1->set_font_description(FONT_TITLE);
  int tw1, th1;
  text1->get_pixel_size(tw1, th1);

  auto text2 = Pango::Layout::create(cr);
  text2->set_text("Totally Original Project");
  text2->set_font_description(FONT_SUBTITLE);
  int tw2, th2;
  text2->get_pixel_size(tw2, th2);

  cr->set_source(COLOUR_WHITE);

  cr->move_to((WIDTH - tw1) / 2, (HEIGHT - th1 - th2) / 2);
  text1->show_in_cairo_context(cr);

  cr->move_to((WIDTH - tw2) / 2, (HEIGHT - th2 + th1) / 2);
  text2->show_in_cairo_context(cr);
  return true;
}

bool DefaultScreen::keypress(Key key) {
  return false;
}

}
