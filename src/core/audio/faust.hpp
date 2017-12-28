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

#include "util/type_traits.hpp"
#include "util/algorithm.hpp"

#include "core/engines/engine.hpp"
#include "core/engines/engine-props.hpp"

namespace otto::audio {

  using FaustDSP = dsp;

  class FaustOptions : public UI {

    std::vector<std::string> boxes;
    bool atRoot = true;

  public:

    enum OPTTYPE {
      FLOAT,
      BOOL
    };

    engines::Properties *props;

    FaustOptions() {}
    FaustOptions(engines::Properties* props) : props (props) {}

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
            if (auto* p = dynamic_cast<engines::Properties*>(*it); p != nullptr) {
              b = p->begin();
              e = p->end();
            }
          }
        } else {
          LOGE << "Couldn't find property matching " << util::join_strings(boxes.begin(), boxes.end(), "/").c_str();
          break;
        }
      }

      boxes.pop_back();
    }
  };

  namespace detail {
    void register_faust_wrapper_events(dsp&, FaustOptions&);
  }

  ///
  /// A Wrapper for faust scripts
  /// All interactions with faust should go through this wrapper
  ///
  /// \tparam Cin The number of input audio channels.
  /// Make sure this corresponds with the actually called faust script
  ///
  /// \tparam Cout The number of output audio channels
  /// Make sure this corresponds with the actually called faust script
  ///
  template<int Cin, int Cout>
  class FaustWrapper {
    // Needed to convert from faust's deinterleaved data to interleaved
    audio::RTBuffer<float, std::max(Cin, Cout)> faustbuf;
  protected:

    audio::ProcessBuffer<Cout> proc_buf;

    FaustOptions opts;

  public:

    std::unique_ptr<dsp> fDSP;

    FaustWrapper() {};

    FaustWrapper(std::unique_ptr<dsp>&& d, engines::Properties& props)
      : opts (&props), fDSP (std::move(d))
    {
      if (fDSP->getNumInputs() != Cin || fDSP->getNumOutputs() != Cout) {
        throw std::runtime_error("A faustwrapper was instantiated with a "
                                 "non-matching faust dsp instance");
      }

      detail::register_faust_wrapper_events(*fDSP, opts);
    }

    virtual ~FaustWrapper() {}

    audio::ProcessData<Cout> process(audio::ProcessData<Cin> data)
    {
      // Convert interleaved to deinterleaved and back
      auto size   = data.nframes;
      auto raw_pb = reinterpret_cast<float*>(proc_buf.data() + data.offset);
      std::array<float*, Cin> in_bufs =
        util::generate_sequence<Cin>([&](int n) { return raw_pb + n * size; });
      for (int i = 0; i < Cin; i++) {
        for (int j = 0; j < size; j++) {
          in_bufs[i][j] = data.audio[j][i];
        }
      }
      std::array<float*, Cout> out_bufs = util::generate_sequence<Cout>(
        [&](int n) { return faustbuf.data() + n * size; });

      fDSP->compute(data.nframes, in_bufs.data(), out_bufs.data());

      for (int i = 0; i < Cout; i++) {
        for (int j = 0; j < size; j++) {
          proc_buf[j + data.offset][i] = out_bufs[i][j];
        }
      }

      return data.redirect(proc_buf);
    }
  };

} // otto
