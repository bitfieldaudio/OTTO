#pragma once

#include <faust/gui/UI.h>
#include <faust/gui/meta.h>
#include <faust/dsp/dsp.h>

#include "globals.h"

enum OPTTYPE {
  FLOAT,
  BOOL
};

class FaustOptions : public UI {

  void openTabBox(const char* label) override {};
  void openHorizontalBox(const char* label) override {};
  void openVerticalBox(const char* label) override {};
  void closeBox() override {};

  void addButton(const char* label, FAUSTFLOAT* zone) override {
    this->registerOption(label, zone, 0, 0, 1, 1, BOOL);
  };

  void addCheckButton(const char* label, FAUSTFLOAT* zone) override {
    this->registerOption(label, zone, 0, 0, 1, 1, BOOL);
  };

  void addVerticalSlider(
    const char* label,
    FAUSTFLOAT* zone,
    FAUSTFLOAT init,
    FAUSTFLOAT min,
    FAUSTFLOAT max,
    FAUSTFLOAT step) override {
    this->registerOption(label, zone, init, min, max, step, FLOAT);
  };

  void addHorizontalSlider(
    const char* label,
    FAUSTFLOAT* zone,
    FAUSTFLOAT init,
    FAUSTFLOAT min,
    FAUSTFLOAT max,
    FAUSTFLOAT step) override {
    this->registerOption(label, zone, init, min, max, step, FLOAT);
  };

  void addNumEntry(
    const char* label,
    FAUSTFLOAT* zone,
    FAUSTFLOAT init,
    FAUSTFLOAT min,
    FAUSTFLOAT max,
    FAUSTFLOAT step) override {
    this->registerOption(label, zone, init, min, max, step, FLOAT);
  };

  virtual void registerOption(
    const char* label,
    FAUSTFLOAT* ptr,
    FAUSTFLOAT init,
    FAUSTFLOAT min,
    FAUSTFLOAT max,
    FAUSTFLOAT step,
    OPTTYPE type);
};

// Possibly this should extend Module
class FaustWrapper {

  dsp *fDSP;

  FAUSTFLOAT **inBuffer;
  FAUSTFLOAT **outBuffer;

public:

  FaustWrapper(dsp * fDSP) :
    fDSP (fDSP) {
    
  }

  virtual void processAudio(jack_nframes_t nframes) {
    prepBuffers(nframes);
    fDSP->compute(nframes, inBuffer, outBuffer);
    postBuffers(nframes);
  }

protected:

  /**
   * Copy the relevant data into inBuffer
   */
  virtual void prepBuffers(jack_nframes_t nframes) {
    inBuffer[0] = GLOB.data.proc;
  }

  /**
   * Put the data back into the chain
   */
  virtual void postBuffers(jack_nframes_t nframes) {
    GLOB.data.proc = outBuffer[0];
  }
};
