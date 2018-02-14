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

#include "core/audio/processor.hpp"

namespace otto::core::audio {

  struct FaustLink {
    float* const faust_var_;
    enum struct Type { ToFaust, FromFaust } const type;
  };

  struct FaustClient {
    using RegisterFunc = std::function<void(
      const std::vector<std::string>&, FaustLink)>;
    using RefreshFunc = std::function<void()>;

    RegisterFunc register_link;
    RefreshFunc refresh_links;
  };

  using FaustDSP = dsp;

  struct FaustOptions : UI {

    FaustOptions(const FaustClient& client) : client(client) {}
    FaustOptions(FaustClient&& client) : client(std::move(client)) {}

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
      registerOption(label, zone, 0, min, max, 0, FaustLink::Type::FromFaust);
    }

    void addVerticalBargraph(
      const char* label, FAUSTFLOAT* zone,
      FAUSTFLOAT min, FAUSTFLOAT max) override {
      addHorizontalBargraph(label, zone, min, max);
    }

    void addButton(const char* label, FAUSTFLOAT* zone) override {
      this->registerOption(label, zone, 0, 0, 1, 1);
    }

    void addCheckButton(const char* label, FAUSTFLOAT* zone) override {
      this->registerOption(label, zone, 0, 0, 1, 1);
    }

    void addVerticalSlider(
      const char* label,
      FAUSTFLOAT* zone,
      FAUSTFLOAT init,
      FAUSTFLOAT min,
      FAUSTFLOAT max,
      FAUSTFLOAT step) override {
      this->registerOption(label, zone, init, min, max, step);
    }

    void addHorizontalSlider(
      const char* label,
      FAUSTFLOAT* zone,
      FAUSTFLOAT init,
      FAUSTFLOAT min,
      FAUSTFLOAT max,
      FAUSTFLOAT step) override {
      this->registerOption(label, zone, init, min, max, step);
    }

    void addNumEntry(
      const char* label,
      FAUSTFLOAT* zone,
      FAUSTFLOAT init,
      FAUSTFLOAT min,
      FAUSTFLOAT max,
      FAUSTFLOAT step) override {
      this->registerOption(label, zone, init, min, max, step);
    }

    void registerOption(
      const char* label,
      FAUSTFLOAT* ptr,
      FAUSTFLOAT init,
      FAUSTFLOAT min,
      FAUSTFLOAT max,
      FAUSTFLOAT step,
      FaustLink::Type type = FaustLink::Type::ToFaust) {

      boxes.emplace_back(label);
      client.register_link(boxes, FaustLink{ptr, type});
      boxes.pop_back();
    }

    const FaustClient client;

  private:

    std::vector<std::string> boxes;
    bool atRoot = true;
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

    FaustWrapper(std::unique_ptr<dsp>&& d, FaustClient client)
      : opts (std::move(client)), fDSP (std::move(d))
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
        util::generate_array<Cin>([&](int n) { return raw_pb + n * size; });
      for (int i = 0; i < Cin; i++) {
        for (int j = 0; j < size; j++) {
          in_bufs[i][j] = data.audio[j][i];
        }
      }
      std::array<float*, Cout> out_bufs = util::generate_array<Cout>(
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
