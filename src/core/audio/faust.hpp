#pragma once

#include <algorithm>
#include <gsl/span>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <faust/dsp/dsp.h>
#include <faust/gui/UI.h>
#include <faust/gui/meta.h>

#include "util/algorithm.hpp"
#include "util/type_traits.hpp"

#include "core/audio/processor.hpp"

#include "core/props/mixins/faust_link.hpp"

namespace otto::service::audio {
  using core::audio::AudioBufferPool;
  AudioBufferPool& buffer_pool() noexcept;
}

namespace otto::core::audio {

  using props::FaustLink;

  using FaustClient = props::mixin::branch<props::faust_link>;

  using FaustDSP = dsp;

  struct FaustOptions : UI {
    FaustOptions(FaustClient& client) : client(client) {}

    void openTabBox(const char* label) override
    {
      if (atRoot) {
        atRoot = false;
      } else {
        boxes.push_back(label);
      }
    }

    void openHorizontalBox(const char* label) override
    {
      if (atRoot) {
        atRoot = false;
      } else {
        boxes.push_back(label);
      }
    }
    void openVerticalBox(const char* label) override
    {
      if (atRoot) {
        atRoot = false;
      } else {
        boxes.push_back(label);
      }
    }
    void closeBox() override
    {
      if (!boxes.empty()) boxes.pop_back();
    }
    void addHorizontalBargraph(const char* label,
                               FAUSTFLOAT* zone,
                               FAUSTFLOAT min,
                               FAUSTFLOAT max) override
    {
      registerOption(label, zone, 0, min, max, 0, FaustLink::Type::FromFaust);
    }

    void addVerticalBargraph(const char* label,
                             FAUSTFLOAT* zone,
                             FAUSTFLOAT min,
                             FAUSTFLOAT max) override
    {
      addHorizontalBargraph(label, zone, min, max);
    }

    void addButton(const char* label, FAUSTFLOAT* zone) override
    {
      this->registerOption(label, zone, 0, 0, 1, 1);
    }

    void addCheckButton(const char* label, FAUSTFLOAT* zone) override
    {
      this->registerOption(label, zone, 0, 0, 1, 1);
    }

    void addVerticalSlider(const char* label,
                           FAUSTFLOAT* zone,
                           FAUSTFLOAT init,
                           FAUSTFLOAT min,
                           FAUSTFLOAT max,
                           FAUSTFLOAT step) override
    {
      this->registerOption(label, zone, init, min, max, step);
    }

    void addHorizontalSlider(const char* label,
                             FAUSTFLOAT* zone,
                             FAUSTFLOAT init,
                             FAUSTFLOAT min,
                             FAUSTFLOAT max,
                             FAUSTFLOAT step) override
    {
      this->registerOption(label, zone, init, min, max, step);
    }

    void addNumEntry(const char* label,
                     FAUSTFLOAT* zone,
                     FAUSTFLOAT init,
                     FAUSTFLOAT min,
                     FAUSTFLOAT max,
                     FAUSTFLOAT step) override
    {
      this->registerOption(label, zone, init, min, max, step);
    }

    void registerOption(const char* label,
                        FAUSTFLOAT* ptr,
                        FAUSTFLOAT init,
                        FAUSTFLOAT min,
                        FAUSTFLOAT max,
                        FAUSTFLOAT step,
                        FaustLink::Type type = FaustLink::Type::ToFaust)
    {
      boxes.emplace_back(label);
      client.register_link(std::begin(boxes), std::end(boxes), FaustLink{ptr, type});
      boxes.pop_back();
    }

    FaustClient& client;

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
  struct FaustWrapper {
    FaustOptions opts;

    std::unique_ptr<dsp> fDSP;

    FaustWrapper(){};

    FaustWrapper(std::unique_ptr<dsp>&& d, FaustClient& client) : opts(client), fDSP(std::move(d))
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
      auto out = service::audio::buffer_pool().allocate_multi<Cout>();
      auto in_bufs = data.audio.data();
      auto out_bufs = out.data();
      fDSP->compute(data.nframes, in_bufs.data(), out_bufs.data());
      return data.redirect(out);
    }
  };

} // namespace otto::core::audio
