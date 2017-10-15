#include "core/ui/base.hpp"
#include "core/ui/drawing.hpp"

namespace otto::ui {

  void DefaultScreen::draw(drawing::Canvas& ctx) {
    using namespace drawing;

  }

  bool DefaultScreen::keypress(Key key) {
    return false;
  }

}
