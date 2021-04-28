#pragma once

#include "lib/util/with_limits.hpp"

#include "lib/engine.hpp"
#include "lib/graphics.hpp"
#include "lib/itc/producer.hpp"

namespace otto::engines::slots {

  struct SoundSlotsState {
    util::Bounded<int, util::bounds<0, 9>> active_slot = 0;
    DECL_VISIT(active_slot);
  };

  struct SoundSlots {
    std::unique_ptr<ILogic> logic;
    ScreenWithHandler overlay_screen;

    static SoundSlots make(itc::Context& ctx);
  };

} // namespace otto::engines::slots
