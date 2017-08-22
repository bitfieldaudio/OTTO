#include "core/audio/faust.hpp"
#include "core/modules/module.hpp"
#include "core/audio/processor.hpp"

namespace top1::modules {

  class FaustSynthModule : public modules::SynthModule, public audio::FaustWrapper {
  public:

    FaustSynthModule(dsp *fDSP, modules::Data *opts) :
      FaustWrapper (fDSP, opts), modules::SynthModule(opts) {}

    void process(audio::ProcessData& data) override {
      FaustWrapper::process(data);
    }

  };

}
