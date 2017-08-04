#include "faust.h"
#include "module.h"

class FaustSynthModule : public module::SynthModule, public FaustWrapper {
public:

  FaustSynthModule(dsp *fDSP, module::Data *opts) :
    FaustWrapper (fDSP, opts), module::SynthModule(opts) {}

  void process(uint nframes) override {
    FaustWrapper::process(nframes);
  }

};
