#pragma once

#include <fmt/format.h>

#include "filesystem.hpp"
#include "core/modules/module.hpp"
#include "core/ui/canvas.hpp"
#include "core/ui/module-ui.hpp"
#include "core/ui/waveform-widget.hpp"

#include "util/dyn-array.hpp"

namespace top1::modules {

  class SynthSampleScreen; // FWDCL

  class SynthSampler : public modules::SynthModule {
  public:

    size_t maxSampleSize = 0;
    top1::DynArray<float> sampleData;
    int sampleSampleRate = 44100;
    float sampleSpeed = 1;

    std::unique_ptr<SynthSampleScreen> editScreen;

    static const uint nVoices = 24;

    struct Props : public Properties {
      Property<std::string> sampleName = {this, "sample name"};

      enum Mode {
        Fwd = 0, FwdStop = 1, FwdLoop = 2,
        Bwd = -1, BwdStop = -2, BwdLoop = -3
      };
      Property<int> in         = {this, "in",    0, { 0, -1, 100}};
      Property<int> out        = {this, "out",   0, { 0, -1, 100}};
      Property<float> speed    = {this, "speed", 1, { 0,  5, 0.01}};
      Property<int, wrap> mode = {this, "mode",  0, {-3,  2, 1}};

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

    } props;

    SynthSampler();

    void process(const audio::ProcessData&) override;

    void display() override;

    void load();

    void init() override;

    static fs::path samplePath(std::string name);
  };

  class SynthSampleScreen : public ui::ModuleScreen<SynthSampler> {
  public:

    std::shared_ptr<audio::Waveform> topWF;
    ui::WaveformWidget<audio::Waveform> topWFW;
    std::shared_ptr<audio::Waveform> mainWF;
    ui::WaveformWidget<audio::Waveform> mainWFW;

    SynthSampleScreen(SynthSampler *);

    void draw(ui::drawing::Canvas&) override;

    bool keypress(ui::Key) override;
    void rotary(ui::RotaryEvent) override;

  };

}
