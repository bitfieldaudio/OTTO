#pragma once

#include <map>
#include <vector>
#include <string>

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

  std::string boxPrefix;

public:

  std::map<std::string, FAUSTFLOAT**> optMap;
  std::vector<FAUSTFLOAT*> resets;

  FaustOptions() {}
  FaustOptions(std::map<std::string, FAUSTFLOAT**> optMap) : optMap (optMap) {}

  void openTabBox(const char* label) override {
    if (strcmp(label, "0x00") != 0)
      boxPrefix.append(label).append("/");
  }
  void openHorizontalBox(const char* label) override {
    if (strcmp(label, "0x00") != 0)
      boxPrefix.append(label).append("/");
  }
  void openVerticalBox(const char* label) override {
    if (strcmp(label, "0x00") != 0)
      boxPrefix.append(label).append("/");
  }
  void closeBox() override {
    boxPrefix.erase(boxPrefix.begin() + boxPrefix.find_last_of("/"), boxPrefix.end());
  }
  void addHorizontalBargraph(
    const char* label, FAUSTFLOAT* zone,
    FAUSTFLOAT min, FAUSTFLOAT max) override {
    registerOption(label, zone, 0, min, max, 0, FLOAT);
  }

  void addVerticalBargraph(
    const char* label, FAUSTFLOAT* zone,
    FAUSTFLOAT min, FAUSTFLOAT max) override {
    addHorizontalBargraph(label, zone, min, max);
  }

  void addButton(const char* label, FAUSTFLOAT* zone) override {
    this->registerOption(label, zone, 0, 0, 1, 1, BOOL, true);
  }

  void addCheckButton(const char* label, FAUSTFLOAT* zone) override {
    this->registerOption(label, zone, 0, 0, 1, 1, BOOL);
  }

  void addVerticalSlider(
    const char* label,
    FAUSTFLOAT* zone,
    FAUSTFLOAT init,
    FAUSTFLOAT min,
    FAUSTFLOAT max,
    FAUSTFLOAT step) override {
    this->registerOption(label, zone, init, min, max, step, FLOAT);
  }

  void addHorizontalSlider(
    const char* label,
    FAUSTFLOAT* zone,
    FAUSTFLOAT init,
    FAUSTFLOAT min,
    FAUSTFLOAT max,
    FAUSTFLOAT step) override {
    this->registerOption(label, zone, init, min, max, step, FLOAT);
  }

  void addNumEntry(
    const char* label,
    FAUSTFLOAT* zone,
    FAUSTFLOAT init,
    FAUSTFLOAT min,
    FAUSTFLOAT max,
    FAUSTFLOAT step) override {
    this->registerOption(label, zone, init, min, max, step, FLOAT);
  }

  virtual void registerOption(
    const char* label,
    FAUSTFLOAT* ptr,
    FAUSTFLOAT init,
    FAUSTFLOAT min,
    FAUSTFLOAT max,
    FAUSTFLOAT step,
    OPTTYPE type,
    bool reset = false) {

    // TODO: do something with the rest of this stuff
    bool matched = 0;
    std::string fullLabel = boxPrefix + label;
    for (auto &opt : optMap) {
      if (opt.first == fullLabel) {
        *opt.second = ptr;
        matched = 1;
        break;
      }
    }
    if (!matched) {
      LOGF << "Unmatched option " << fullLabel;
    }
    if (reset) resets.push_back(ptr);
  }

  void resetOptions() {
    for (auto &opt : resets) {
      *opt = 0;
    }
  };
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

  virtual ~FaustWrapper() {
    delete fDSP;
  };

  FaustWrapper(dsp *DSP, std::map<std::string, FAUSTFLOAT**> optMap) :
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
    opts.resetOptions();
    postBuffers(nframes);
  }

protected:

  virtual void initBuffers() {
    for (int i = 0; i < fDSP->getNumInputs(); i++) {
      inBuffer[0] = (FAUSTFLOAT *) malloc(sizeof(FAUSTFLOAT) * GLOB.jackAudio.bufferSize);
    }
    for (int i = 0; i < fDSP->getNumOutputs(); i++) {
      *outBuffer = (FAUSTFLOAT *) malloc(sizeof(FAUSTFLOAT) * GLOB.jackAudio.bufferSize);
    }
  }

  /**
   * Copy the relevant data into inBuffer
   */
  virtual void prepBuffers(uint nframes) {
    if (fDSP->getNumInputs() > 0)
      inBuffer[0] = GLOB.audioData.proc;
  }

  /**
   * Put the data back into the chain
   */
  virtual void postBuffers(uint nframes) {
    GLOB.audioData.proc = *outBuffer;
  }
};
