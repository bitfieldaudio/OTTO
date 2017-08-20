#include "core/modules/module-dispatcher.hpp"

#include "core/globals.hpp"

namespace top1::module {
  namespace detail {
    bool isShiftPressed() {
      return GLOB.ui.keys[ui::K_SHIFT];
    }

    void displayScreen(ui::Screen::ptr ptr) {
      GLOB.ui.display(ptr);
    }
  }
}
