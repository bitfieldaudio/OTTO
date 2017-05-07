#include "base.h"
#include "utils.h"
#include "../globals.h"

namespace ui {

void DefaultScreen::draw(NanoCanvas::Canvas& ctx) {
  using namespace drawing;

}

bool DefaultScreen::keypress(Key key, bool shift) {
  return false;
}

}
