#include "core/audio/faust.hpp"

#include "core/globals.hpp"

namespace top1::audio {

  FaustWrapper::FaustWrapper(dsp *DSP, module::Data *data) :
    opts (data),
    fDSP (DSP)
  {
    inBuffer = (FAUSTFLOAT **) malloc(sizeof(FAUSTFLOAT **)
                                      * fDSP->getNumInputs());
    outBuffer = (FAUSTFLOAT **) malloc(sizeof(FAUSTFLOAT **)
                                       * fDSP->getNumOutputs());
    Globals::events.preInit.add([&]() {
        fDSP->init(Globals::samplerate);
        fDSP->buildUserInterface(&opts);
      });
    Globals::events.samplerateChanged.add([&](uint sr) {
        fDSP->instanceInit(sr);
      });
    Globals::events.bufferSizeChanged.add([this](uint bs) {
        initBuffers();
      });
    Globals::events.postInit.add([&]() {
        initBuffers();
      });
  }

  void FaustWrapper::initBuffers() {
    for (int i = 0; i < fDSP->getNumInputs(); i++) {
      inBuffer[0] = (FAUSTFLOAT *) malloc(sizeof(FAUSTFLOAT) * Globals::jackAudio.bufferSize);
    }
    for (int i = 0; i < fDSP->getNumOutputs(); i++) {
      *outBuffer = (FAUSTFLOAT *) malloc(sizeof(FAUSTFLOAT) * Globals::jackAudio.bufferSize);
    }
    for (auto f : opts.data->fields) {
      if (!f.second->preserve) f.second->reset();
    }
  }

  void FaustWrapper::prepBuffers(ProcessData& data) {
    if (fDSP == nullptr) {
      return;
    }
    if (fDSP->getNumInputs() > 0) {
      std::copy(data.audio.proc.begin(), data.audio.proc.end(), inBuffer[0]);
    }
    outBuffer[0] = data.audio.proc.data();
  }

  void FaustWrapper::postBuffers(ProcessData& data) {}

} // top1::audio
