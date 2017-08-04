#pragma once

#include <fmt/format.h>

#include "../module.h"
#include "../ui/base.h"
#include "../ui/waveform-widget.h"

#include "../util/dyn-array.h"

namespace module {

class SynthSampleScreen; // FWDCL

/**
 * Drum sampler for now
 */
class SynthSampler : public module::SynthModule {
public:

  size_t maxSampleSize = 0;
  top1::DynArray<float> sampleData;
  int sampleSampleRate = 44100;
  float sampleSpeed = 1;

  std::shared_ptr<SynthSampleScreen> editScreen;

  static const uint nVoices = 24;

  struct Data : public module::Data {
    module::Opt<std::string> sampleName = {this, "sample name", ""};

    enum Mode {
      Fwd = 0, FwdStop = 1, FwdLoop = 2,
      Bwd = -1, BwdStop = -2, BwdLoop = -3
    };
    module::Opt<int> in = {this, "in", 0, 0, -1, 100};
    module::Opt<int> out = {this, "out", 0, 0, -1, 100};
    module::Opt<float> speed = {this, "speed", 1, 0, 5, 0.01};
    module::WrapOpt<int> mode = {this, "mode", 0, -3, 2, 1};

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

    Data() {}
    Data(Data&) = delete;
    Data(Data&&) = delete;

  } data;

  SynthSampler();

  void process(uint nframes) override;

  void display() override;

  void load();

  void init() override;

  static std::string samplePath(std::string name) {
    return "samples/synth/" + name + ".wav";
  }
};

class SynthSampleScreen : public ui::ModuleScreen<SynthSampler> {
public:

  std::shared_ptr<Waveform> topWF;
  WaveformWidget<Waveform> topWFW;
  std::shared_ptr<Waveform> mainWF;
  WaveformWidget<Waveform> mainWFW;

  SynthSampleScreen(SynthSampler *);

  void draw(drawing::Canvas&) override;

  bool keypress(ui::Key) override;

};

}
