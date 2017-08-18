#include "faust.hpp"

#include "core/globals.hpp"

namespace top1 {

FaustWrapper::FaustWrapper(dsp *DSP, module::Data *data) :
  opts (data),
  fDSP (DSP)
{
  inBuffer =
    (FAUSTFLOAT **) malloc(sizeof(FAUSTFLOAT **) * fDSP->getNumInputs());
  outBuffer =
    (FAUSTFLOAT **) malloc(sizeof(FAUSTFLOAT **) * fDSP->getNumOutputs());
  GLOB.events.preInit.add([&]() {
     fDSP->init(GLOB.samplerate);
     fDSP->buildUserInterface(&opts);
   });
  GLOB.events.samplerateChanged.add([&](uint sr) {
     fDSP->instanceInit(sr);
   });
  GLOB.events.bufferSizeChanged.add([this](uint bs) {
     initBuffers();
   });
  GLOB.events.postInit.add([&]() {
     initBuffers();
   });
}

void FaustWrapper::initBuffers() {
  for (int i = 0; i < fDSP->getNumInputs(); i++) {
    inBuffer[0] = (FAUSTFLOAT *) malloc(sizeof(FAUSTFLOAT) * GLOB.jackAudio.bufferSize);
  }
  for (int i = 0; i < fDSP->getNumOutputs(); i++) {
    *outBuffer = (FAUSTFLOAT *) malloc(sizeof(FAUSTFLOAT) * GLOB.jackAudio.bufferSize);
  }
  for (auto f : opts.data->fields) {
    if (!f.second->preserve) f.second->reset();
  }
}

void FaustWrapper::prepBuffers(uint nframes) {
  if (fDSP == nullptr) {
    return;
  }
  if (fDSP->getNumInputs() > 0)
    inBuffer[0] = GLOB.audioData.proc.data();
}

void FaustWrapper::postBuffers(uint nframes) {
  if (fDSP->getNumInputs() > 0)
    GLOB.audioData.proc.copyFrom(*outBuffer, nframes);
  else
    for (uint i = 0; i < nframes; i++) {
      GLOB.audioData.proc[i] += outBuffer[0][i];
    }
}

} // top1
