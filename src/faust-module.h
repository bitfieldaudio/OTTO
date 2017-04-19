#include "faust.h"
#include "module.h"

class FaustSynthModule : public SynthModule, public FaustWrapper {

public:

  FaustSynthModule(dsp *fDSP, std::map<const char*, FAUSTFLOAT**> opts) :
    FaustWrapper (fDSP, opts) {}

  void process(uint nframes) override {
    FaustWrapper::process(nframes);
  }
};
