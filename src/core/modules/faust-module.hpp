#include "core/audio/faust.hpp"
#include "core/modules/module.hpp"
#include "core/audio/processor.hpp"

namespace top1::module {

  class FaustSynthModule : public module::SynthModule, public audio::FaustWrapper {
  public:

    FaustSynthModule(dsp *fDSP, module::Data *opts) :
      FaustWrapper (fDSP, opts), module::SynthModule(opts) {}

    void process(audio::ProcessData& data) override {
      FaustWrapper::process(data);
    }

  };

}
