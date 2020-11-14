#pragma once

namespace otto::stubs {
  struct [[otto::reflect]] State {
    int i1 = 0;
    int i2 = 0;
    struct [[otto::reflect]] SubState {
      int subi1 = 0;
    } substate;
  };
} // namespace otto::stubs
