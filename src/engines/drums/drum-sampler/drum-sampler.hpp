#pragma once

#include <fmt/format.h>
#include "filesystem.hpp"

#include "core/audio/processor.hpp"
#include "core/engines/engine.hpp"

namespace otto::engines {

  /**
   * A sampler with 24 individual voices, laid out over the keys.
   */
  struct DrumSampler : public engines::DrumsEngine {

    DrumSampler();
    ~DrumSampler();

    audio::ProcessData<1> process(audio::ProcessData<0>) override;

    void load();

    void on_enable() override;

    static fs::path samplePath(std::string name);

    size_t maxSampleSize = 0;
    util::dyn_array<float> sampleData;
    int sampleSampleRate = 44100;
    float sampleSpeed = 1;

    static constexpr int nVoices = 24;

    struct Props : public Properties {
      Property<std::string> sampleName = {this, "sample name", ""};

      struct VoiceData : public Properties {
        enum Mode {
          Fwd = 0,  FwdStop = 1,  FwdLoop = 2,
          Bwd = -1, BwdStop = -2, BwdLoop = -3
        };
        Property<int>          in   = {this, "in",    0, { 0, -1, 100}};
        Property<int>         out   = {this, "out",   0, { 0, -1, 100}};
        Property<float, pow2> pitch = {this, "pitch", 0, { -2,  4, 1/12.f}};
        Property<int, wrap>  mode   = {this, "mode",  0, {-3,  3, 1}};

        bool fwd() const {return mode >= 0;}
        bool bwd() const {return !fwd();}
        bool stop() const {return mode == FwdStop || mode == BwdStop;}
        bool loop() const {return mode == FwdLoop || mode == BwdLoop;}

        float playProgress = -1;
        bool trigger;
        int length() const {
          return out - in;
        }
        void play();
        using Properties::Properties;
      };

      // Construct VoiceData's
      std::array<VoiceData, nVoices> voiceData =
        util::generate_sequence<nVoices>([this] (int n) {
            return VoiceData((Properties*) this, fmt::format("Voice {}", n));
          });

      Props() = default;
      Props(Props&) = delete;
      Props(Props&&) = delete;

    } props;

    int currentVoiceIdx = 0;

  private:
    audio::ProcessBuffer<1> proc_buf;
  };

}  // namespace otto::engines
