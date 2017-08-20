#include "core/modules/module-dispatcher.hpp"

#include "core/globals.hpp"

namespace top1::module {
  namespace detail {
    bool isShiftPressed() {
      return Globals::ui.keys[ui::K_SHIFT];
    }

    void displayScreen(ui::Screen::ptr ptr) {
      Globals::ui.display(ptr);
    }
  }
}
