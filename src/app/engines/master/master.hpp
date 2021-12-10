#pragma once

#include "lib/util/with_limits.hpp"

#include "lib/engine.hpp"
#include "lib/graphics.hpp"
#include "lib/itc/state/producer.hpp"

#include "app/drivers/audio_driver.hpp"

namespace otto::engines::master {

  struct MasterState {
    util::Bounded<float, util::bounds<0, 1>> volume = 0;
    DECL_VISIT(volume);
  };

  struct Master {
    std::unique_ptr<ILogic> logic;
    ScreenWithHandler screen;

    static Master make(itc::Context& ctx, drivers::IAudioMixer&);
  };

} // namespace otto::engines::master
