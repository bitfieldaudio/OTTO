#pragma once

#include "lib/util/with_limits.hpp"

#include "lib/engine.hpp"
#include "lib/graphics.hpp"
#include "lib/itc/producer.hpp"

namespace otto::engines::slots {

  struct SlotState {
    util::StaticallyBounded<float, 0, 1, util::bounds_policies::wrap> selected_color_f = 0.5f;
    DECL_VISIT(selected_color_f);
  };

  struct SoundSlotsState {
    util::StaticallyBounded<int, 0, 9> active_idx = 0;
    std::array<SlotState, 10> slot_states;
    DECL_VISIT(active_idx, slot_states);
  };

  struct SoundSlots {
    std::unique_ptr<ILogic> logic;
    ScreenWithHandler overlay_screen;

    static SoundSlots make(itc::Context& ctx);
  };

} // namespace otto::engines::slots
