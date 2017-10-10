#pragma once

#include "core/audio/faust.hpp"
#include "core/modules/module.hpp"
#include "core/audio/processor.hpp"

namespace top1::modules {

  class FaustSynthModule : public audio::FaustWrapper<0, 1>, public SynthModule {
  public:

    FaustSynthModule(std::unique_ptr<dsp>&& fDSP, Properties* props) :
      FaustWrapper(std::move(fDSP), *props), SynthModule(props) {}

    using audio::FaustWrapper<0, 1>::process;
  };

}
