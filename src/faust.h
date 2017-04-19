#pragma once

#include <map>

#include <faust/gui/UI.h>
#include <faust/gui/meta.h>
#include <faust/dsp/dsp.h>

#include "globals.h"

typedef dsp FaustDSP;

enum OPTTYPE {
  FLOAT,
  BOOL
};

class FaustOptions : public UI {
public:

  // TODO: should this be atomic?
  std::map<const char*, FAUSTFLOAT**> optMap;

  FaustOptions() {};
  FaustOptions(std::map<const char*, FAUSTFLOAT**> optMap) : optMap (optMap) {}

  void openTabBox(const char* label) override {};
  void openHorizontalBox(const char* label) override {};
  void openVerticalBox(const char* label) override {};
  void closeBox() override {};
  void addHorizontalBargraph(
    const char* label, FAUSTFLOAT* zone,
    FAUSTFLOAT min, FAUSTFLOAT max) override {};
  void addVerticalBargraph(
    const char* label, FAUSTFLOAT* zone,
    FAUSTFLOAT min, FAUSTFLOAT max) override {};

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
    OPTTYPE type) {

    // TODO: do something with the rest of this stuff
    bool matched = 0;
    for (auto const &opt : optMap) {
      if (strcmp(label, opt.first) == 0) {
        *opt.second = ptr;
        matched = 1;
        break;
      }
    }
    if (!matched) {
      LOGF << "Unmatched option " << label;
    }
  }
};

// Possibly this should extend Module
class FaustWrapper {

protected:

  FaustOptions opts;

  FAUSTFLOAT **inBuffer;
  FAUSTFLOAT **outBuffer;

public:

  dsp *fDSP;

  FaustWrapper() {};

  ~FaustWrapper() {};

  FaustWrapper(dsp *DSP, std::map<const char*, FAUSTFLOAT**> optMap) :
    opts (optMap),
    fDSP (DSP)
  {
    fDSP->init(GLOB.samplerate);
    fDSP->buildUserInterface(&opts);
    inBuffer =
      (FAUSTFLOAT **) malloc(sizeof(FAUSTFLOAT **) * fDSP->getNumInputs());
    outBuffer =
      (FAUSTFLOAT **) malloc(sizeof(FAUSTFLOAT **) * fDSP->getNumOutputs());
    initBuffers();
    LOGD << "Constructed a FaustWrapper";
  }

  virtual void process(uint nframes) {
    prepBuffers(nframes);
    fDSP->
      compute(nframes, inBuffer, outBuffer);
    postBuffers(nframes);
  }

protected:

  virtual void initBuffers() {
    for (int i = 0; i < fDSP->getNumInputs(); i++) {
      inBuffer[0] = (FAUSTFLOAT *) malloc(sizeof(FAUSTFLOAT) * GLOB.buffersize);
    }
    for (int i = 0; i < fDSP->getNumOutputs(); i++) {
      *outBuffer = (FAUSTFLOAT *) malloc(sizeof(FAUSTFLOAT) * GLOB.buffersize);
    }
  }

  /**
   * Copy the relevant data into inBuffer
   */
  virtual void prepBuffers(uint nframes) {
    if (fDSP->getNumInputs() > 0)
      inBuffer[0] = GLOB.data.proc;
  }

  /**
   * Put the data back into the chain
   */
  virtual void postBuffers(uint nframes) {
    GLOB.data.proc = *outBuffer;
  }
};
