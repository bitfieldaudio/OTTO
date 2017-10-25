#pragma once

#include <fmt/format.h>

#include "filesystem.hpp"

#include "core/modules/module.hpp"
#include "core/ui/module-ui.hpp"
#include "core/ui/waveform_widget.hpp"
#include "core/ui/canvas.hpp"

#include "util/algorithm.hpp"
#include "util/dyn-array.hpp"

namespace otto::modules {

  class DrumSampleScreen; // FWDCL

  /**
   * A sampler with 24 individual voices, laid out over the keys.
   */
  class DrumSampler : public modules::SynthModule {
    audio::ProcessBuffer<1> proc_buf;
  public:

    size_t maxSampleSize = 0;
    util::dyn_array<float> sampleData;
    int sampleSampleRate = 44100;
    float sampleSpeed = 1;

    std::unique_ptr<DrumSampleScreen> editScreen;

    static constexpr int nVoices = 24;

    struct Props : public Properties {
      Property<std::string> sampleName = {this, "sample name", ""};

      struct VoiceData : public Properties {
        enum Mode {
          Fwd = 0,  FwdStop = 1,  FwdLoop = 2,
          Bwd = -1, BwdStop = -2, BwdLoop = -3
        };
        Property<int>          in = {this, "in",    0, { 0, -1, 100}};
        Property<int>         out = {this, "out",   0, { 0, -1, 100}};
        Property<float>     speed = {this, "speed", 1, { 0,  5, 0.01}};
        Property<int, wrap>  mode = {this, "mode",  0, {-3,  2, 1}};

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

    DrumSampler();

    audio::ProcessData<1> process(audio::ProcessData<0>) override;

    void display() override;

    void load();

    void init() override;

    static fs::path samplePath(std::string name);
  };

  class DrumSampleScreen : public ui::ModuleScreen<DrumSampler> {
  public:

    ui::widgets::Waveform<util::dyn_array<float>> topWFW;
    ui::widgets::Waveform<util::dyn_array<float>> mainWFW;

    DrumSampleScreen(DrumSampler *);

    void draw(ui::vg::Canvas&) override;

    bool keypress(ui::Key) override;
    void rotary(ui::RotaryEvent) override;
  };

}
