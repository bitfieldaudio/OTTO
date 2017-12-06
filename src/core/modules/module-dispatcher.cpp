#include "core/modules/module-dispatcher.hpp"

#include "core/globals.hpp"

namespace otto::modules {
  namespace detail {
    bool isShiftPressed() {
      return global::ui.keys[ui::K_SHIFT];
    }

    void displayScreen(ui::Screen& ptr) {
      global::ui.display(ptr);
    }
  }
}
