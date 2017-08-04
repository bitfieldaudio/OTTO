#include "module-dispatcher.h"

#include "globals.h"

namespace module {
namespace detail {
bool isShiftPressed() {
  return GLOB.ui.keys[ui::K_SHIFT];
}

void displayScreen(ui::Screen::ptr ptr) {
  GLOB.ui.display(ptr);
}
}
}
