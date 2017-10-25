#include "core/ui/base.hpp"
#include "core/ui/drawing.hpp"

namespace otto::ui {

  void DefaultScreen::draw(vg::Canvas& ctx) {
    using namespace vg;

  }

  bool DefaultScreen::keypress(Key key) {
    return false;
  }

}
