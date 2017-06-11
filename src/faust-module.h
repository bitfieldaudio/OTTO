#include "faust.h"
#include "module.h"

class FaustSynthModule : public module::SynthModule, public FaustWrapper {
public:

  FaustSynthModule(dsp *fDSP, module::Data *opts) :
    FaustWrapper (fDSP, opts), module::SynthModule(opts) {}

  using FaustWrapper::process;

};
