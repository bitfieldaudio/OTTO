#pragma once

#include <map>
#include <vector>
#include <string>
#include <memory>
#include <algorithm>
#include <gsl/span>

#include <faust/gui/UI.h>
#include <faust/gui/meta.h>
#include <faust/dsp/dsp.h>

#include <plog/Log.h>

#include "util/type_traits.hpp"
#include "util/algorithm.hpp"

#include "core/modules/module.hpp"
#include "core/modules/module-props.hpp"

namespace top1::audio {

  using FaustDSP = dsp;

  class FaustOptions : public UI {

    std::vector<std::string> boxes;
    bool atRoot = true;

  public:

    enum OPTTYPE {
      FLOAT,
      BOOL
    };

    modules::Properties *props;

    FaustOptions() {}
    FaustOptions(modules::Properties* props) : props (props) {}

    void openTabBox(const char* label) override {
      if (atRoot) {
        atRoot = false;
      } else {
        boxes.push_back(label);
      }
    }

    void openHorizontalBox(const char* label) override {
      if (atRoot) {
        atRoot = false;
      } else {
        boxes.push_back(label);
      }
    }
    void openVerticalBox(const char* label) override {
      if (atRoot) {
        atRoot = false;
      } else {
        boxes.push_back(label);
      }
    }
    void closeBox() override {
      if (!boxes.empty()) boxes.pop_back();
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

      boxes.emplace_back(label);

      auto lookingFor = boxes.begin();
      auto b = props->begin();
      auto e = props->end();
      while (true) {
        auto it = std::find_if(b, e,
          [&](auto&& p) {
            return p->name == *lookingFor;
          });
        if (it != e) {
          if (++lookingFor == boxes.end()) { // Found
            (*it)->linkToFaust(ptr, output);
            break;
          } else {
            if (auto* p = dynamic_cast<modules::Properties*>(*it); p != nullptr) {
              b = p->begin();
              e = p->end();
            }
          }
        } else {
          LOGE << "Couldn't find property matching " << join_strings(boxes.begin(), boxes.end(), "/").c_str();
          break;
        }
      }

      boxes.pop_back();
    }
  };


  class FaustWrapper {

    float* inBufs;
    float* outBufs;
  protected:

    FaustOptions opts;

  public:

    std::unique_ptr<dsp> fDSP;

    FaustWrapper() {};

    virtual ~FaustWrapper() {};

    FaustWrapper(std::unique_ptr<dsp>&&, modules::Properties& data);

    void process(gsl::span<float> inBuffer, gsl::span<float> outBuffer) {
      inBufs = inBuffer.data();
      outBufs = outBuffer.data();
      fDSP->compute(inBuffer.size(), &inBufs, &outBufs);
    }

    void process(gsl::span<float> buffer) {
      inBufs = buffer.data();
      outBufs = buffer.data();
      fDSP->compute(buffer.size(), &inBufs, &outBufs);
    }

  };

} // top1
