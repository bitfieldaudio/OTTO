#pragma once

#include "core/audio/faust.hpp"
#include "core/modules/module.hpp"
#include "core/audio/processor.hpp"

namespace top1::modules {

  class FaustSynthModule : public audio::FaustWrapper, public SynthModule {
  public:

    FaustSynthModule(dsp *fDSP, Properties *propsPtr) :
      FaustWrapper(fDSP, *propsPtr), SynthModule(propsPtr) {}

    void process(const audio::ProcessData& data) override {
      FaustWrapper::process(data);
    }

  };

}
