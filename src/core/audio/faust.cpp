#include "core/audio/faust.hpp"

#include "core/globals.hpp"

namespace top1::audio {

  FaustWrapper::FaustWrapper(dsp *DSP, modules::Properties& props) :
    opts (&props),
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
      outBuffer[0] = (FAUSTFLOAT *) malloc(sizeof(FAUSTFLOAT) * Globals::jackAudio.bufferSize);
    }
    for (auto&& p : *opts.props) {
      if (!p->store) p->reset();
    }
  }

  void FaustWrapper::prepBuffers(const ProcessData& data) {
    if (fDSP == nullptr) {
      return;
    }
    if (fDSP->getNumInputs() > 0) {
      std::copy(data.audio.proc.begin(), data.audio.proc.end(), inBuffer[0]);
    }
    outBuffer[0] = data.audio.proc.data();
  }

  void FaustWrapper::postBuffers(const ProcessData& data) {
    indexed_for_n(outBuffer[0], data.nframes, [&,data] (float f, int i) {
        data.audio.proc[i] += f;
      });
  }

} // top1::audio
