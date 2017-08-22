#pragma once

#include <fmt/format.h>

#include "core/modules/module.hpp"
#include "core/ui/module-ui.hpp"
#include "core/ui/waveform-widget.hpp"
#include "core/ui/canvas.hpp"

#include "util/dyn-array.hpp"

namespace top1::modules {

  class DrumSampleScreen; // FWDCL

  /**
   * A sampler with 24 individual voices, laid out over the keys.
   */
  class DrumSampler : public modules::SynthModule {
  public:

    size_t maxSampleSize = 0;
    top1::DynArray<float> sampleData;
    int sampleSampleRate = 44100;
    float sampleSpeed = 1;

    std::unique_ptr<DrumSampleScreen> editScreen;

    static const uint nVoices = 24;

    struct Data : public modules::Data {
      modules::Opt<std::string> sampleName = {this, "sample name", ""};

      struct VoiceData : public modules::Data {
        enum Mode {
          Fwd = 0, FwdStop = 1, FwdLoop = 2,
          Bwd = -1, BwdStop = -2, BwdLoop = -3
        };
        modules::Opt<int> in = {this, "in", 0, 0, -1, 100};
        modules::Opt<int> out = {this, "out", 0, 0, -1, 100};
        modules::Opt<float> speed = {this, "speed", 1, 0, 5, 0.01};
        modules::WrapOpt<int> mode = {this, "mode", 0, -3, 2, 1};

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
      };

      std::array<VoiceData, nVoices> voiceData;

      Data() {
        for (uint i = 0; i < nVoices; i++) {
          subGroup(fmt::format("Voice {}", i), voiceData[i]);
        }
      }

      Data(Data&) = delete;
      Data(Data&&) = delete;

    } data;

    uint currentVoiceIdx = 0;

    DrumSampler();

    void process(audio::ProcessData&) override;

    void display() override;

    void load();

    void init() override;

    static std::string samplePath(std::string name) {
      return "samples/drums/" + name + ".wav";
    }
  };

  class DrumSampleScreen : public ui::ModuleScreen<DrumSampler> {
  public:

    std::shared_ptr<audio::Waveform> topWF;
    ui::WaveformWidget<audio::Waveform> topWFW;
    std::shared_ptr<audio::Waveform> mainWF;
    ui::WaveformWidget<audio::Waveform> mainWFW;

    DrumSampleScreen(DrumSampler *);

    void draw(ui::drawing::Canvas&) override;

    bool keypress(ui::Key) override;

  };

}
