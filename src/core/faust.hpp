#pragma once

#include <map>
#include <vector>
#include <string>
#include <cstring>
#include <memory>

#include <faust/gui/UI.h>
#include <faust/gui/meta.h>
#include <faust/dsp/dsp.h>

#include <plog/Log.h>

#include "core/modules/module.hpp"

namespace top1 {

using FaustDSP = dsp;

class FaustOptions : public UI {

  std::string boxPrefix;
  bool atRoot = true;

public:

  enum OPTTYPE {
    FLOAT,
    BOOL
  };

  module::Data *data;

  FaustOptions() {}
  FaustOptions(module::Data *data) : data (data) {}

  void openTabBox(const char* label) override {
    if (atRoot) {
      atRoot = false;
    } else {
      boxPrefix.append(label).append("/");
    }
  }

  void openHorizontalBox(const char* label) override {
    if (atRoot) {
      atRoot = false;
    } else {
      boxPrefix.append(label).append("/");
    }
  }
  void openVerticalBox(const char* label) override {
    if (atRoot) {
      atRoot = false;
    } else {
      boxPrefix.append(label).append("/");
    }
  }
  void closeBox() override {
    uint last = 0;
    uint secLast = 0;
    std::string::size_type found = 0;
    while (found != std::string::npos) {
      secLast = last;
      last = found;
      found = boxPrefix.find("/", last + 1);
    }
    boxPrefix.erase(boxPrefix.begin() + secLast, boxPrefix.end());
  }
  void addHorizontalBargraph(
    const char* label, FAUSTFLOAT* zone,
    FAUSTFLOAT min, FAUSTFLOAT max) override {
    registerOption(label, zone, 0, min, max, 0, FLOAT, true);
  }

  void addVerticalBargraph(
    const char* label, FAUSTFLOAT* zone,
    FAUSTFLOAT min, FAUSTFLOAT max) override {
    addHorizontalBargraph(label, zone, min, max);
  }

  void addButton(const char* label, FAUSTFLOAT* zone) override {
    this->registerOption(label, zone, 0, 0, 1, 1, BOOL);
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
    bool output = false) {

    bool matched = false;
    std::string fullLabel = boxPrefix + label;
    for (auto &&opt : data->fields) {
      auto visitor = module::FieldPtr::makeVisitor(
        [&] (module::Opt<bool> *f) {
          assert(type == BOOL);
          if (output) f->addChangeHandler([ptr] (auto *f) { f->setRaw(*ptr); });
          else f->addChangeHandler([ptr] (auto *f) { *ptr = f->get(); });
        },
        [&] (module::Opt<float> *f) {
          assert(type == FLOAT);
          if (output)
            f->addChangeHandler([ptr] (auto *f) { f->setRaw(*ptr); });
          else
            f->addChangeHandler([ptr] (auto *f) { *ptr = f->get(); });
        },
        [&] (module::Opt<int> *f) {
          assert(type == FLOAT);
          if (output) f->addChangeHandler([ptr] (auto *f) { f->setRaw(*ptr); });
          else f->addChangeHandler([ptr] (auto *f) { *ptr = f->get(); });
        },
        [&] (auto *) {
          LOGE << "Unrecognized Opt type";
        });
      if (opt.first == fullLabel) {
        opt.second.visit(visitor);
        opt.second->changed();
        matched = true;
        break;
      } else {
        // TODO: Traverse the module data as a tree
      }
    }
    if (!matched) {
      LOGF << "Unmatched option " << fullLabel;
    }
  }
};

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

  FaustWrapper(dsp *DSP, module::Data *data);

  virtual void process(uint nframes) {
    prepBuffers(nframes);
    fDSP->
      compute(nframes, inBuffer, outBuffer);
    postBuffers(nframes);
  }

protected:

  virtual void initBuffers();

  /**
   * Copy the relevant data into inBuffer
   */
  virtual void prepBuffers(uint nframes);

  /**
   * Put the data back into the chain
   */
  virtual void postBuffers(uint nframes);
};

} // top1
