#pragma once

#include "core/audio/faust.hpp"
#include "core/engines/engine.hpp"
#include "core/audio/processor.hpp"

namespace otto::core::engines {

  struct FaustSynthEngine : audio::FaustWrapper<0, 1>, SynthEngine {
    FaustSynthEngine(std::string name,
                     Properties& props,
                     std::unique_ptr<ui::Screen>&& screen,
                     std::unique_ptr<dsp>&& fDSP)
      : FaustWrapper(std::move(fDSP), props), SynthEngine(name, props, std::move(screen))
    {}

    using audio::FaustWrapper<0, 1>::process;
  };

}
