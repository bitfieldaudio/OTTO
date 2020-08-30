#pragma once

#include "app/input.hpp"

namespace otto {

  struct LED {
    Key key;
  };

  struct LEDColor {
    uint8_t r = 0, g = 0, b = 0;
  };
} // namespace otto
