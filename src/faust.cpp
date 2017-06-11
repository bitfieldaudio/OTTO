#include "faust.h"

#include "globals.h"

FaustWrapper::FaustWrapper(dsp *DSP, module::Data *data) :
  opts (data),
  fDSP (DSP)
{
  GLOB.events.preInit.add([&]() {
     fDSP->init(GLOB.samplerate);
     fDSP->buildUserInterface(&opts);
   });
  GLOB.events.postInit.add([&]() {
     inBuffer =
       (FAUSTFLOAT **) malloc(sizeof(FAUSTFLOAT **) * fDSP->getNumInputs());
     outBuffer =
       (FAUSTFLOAT **) malloc(sizeof(FAUSTFLOAT **) * fDSP->getNumOutputs());
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
    inBuffer[0] = GLOB.audioData.proc;
}

void FaustWrapper::postBuffers(uint nframes) {
  if (fDSP->getNumInputs() > 0)
    GLOB.audioData.proc = *outBuffer;
  else
    for (uint i = 0; i < nframes; i++) {
      GLOB.audioData.proc[i] += outBuffer[0][i];
    }
}
