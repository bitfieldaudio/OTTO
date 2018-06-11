#pragma once

#include "core/ui/screen.hpp"
#include <linux/input-event-codes.h>

namespace otto::board::ui {

  /// Implement in the main board. This will be your keyboard layout
  core::ui::Key translate_key(int key_code, bool ctrl);

}
