#pragma once

#include "core/audio/faust.hpp"
#include "core/engines/engine.hpp"
#include "core/audio/processor.hpp"

namespace otto::engines {

  class FaustSynthEngine : public audio::FaustWrapper<0, 1>, public SynthEngine {
  public:

    FaustSynthEngine(std::unique_ptr<dsp>&& fDSP, Properties* props) :
      FaustWrapper(std::move(fDSP), *props), SynthEngine(props) {}

    using audio::FaustWrapper<0, 1>::process;
  };

}
