#include "core/audio/faust.hpp"

#include "core/globals.hpp"
#include <exception>

namespace top1::audio {

  FaustWrapper::FaustWrapper(std::unique_ptr<dsp>&& d,
    modules::Properties& props) : opts (&props), fDSP (std::move(d))
  {
    if (fDSP->getNumInputs() > 1 || fDSP->getNumOutputs() > 1) {
      throw std::runtime_error("FaustWrapper doesnt handle multiple channels");
    }
    Globals::events.preInit.add([&]() {
        fDSP->init(Globals::samplerate);
        fDSP->buildUserInterface(&opts);
      });
    Globals::events.samplerateChanged.add([&](uint sr) {
        fDSP->instanceInit(sr);
        opts.props->updateFaust();
      });
  }
} // top1::audio
