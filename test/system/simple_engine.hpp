#pragma once

#include "lib/util/with_limits.hpp"

namespace otto::engines::simple {
  struct [[otto::reflect]] State {
    util::StaticallyBounded<float, 11, 880> freq = 340;
  };
} // namespace otto::engines::simple
