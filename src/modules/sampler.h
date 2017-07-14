#pragma once

#include <fmt/format.h>

#include "../module.h"
#include "../ui/base.h"
#include "../ui/waveform-widget.h"

#include "../util/dyn-array.h"

namespace module {

class SampleEditScreen; // FWDCL
/**
 * Drum sampler for now
 */
class Sampler : public module::SynthModule {
public:

  size_t maxSampleSize = 0;
  top1::DynArray<float> sampleData;

  std::shared_ptr<SampleEditScreen> editScreen;

  static const uint nVoices = 24;

  struct Data : public module::Data {
    module::Opt<std::string> sampleName = {this, "sample name", ""};

    struct VoiceData : public module::Data {
      module::Opt<int> in = {this, "in", 0, 0, -1, 100};
      module::Opt<int> out = {this, "out", 0, 0, -1, 100};
      module::Opt<int> mode = {this, "mode", 1, -2, 2, 1};

      int playProgress = -1;
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

  Sampler();

  void process(uint nframes) override;

  void display() override;

  void load();

  void init() override;

  static std::string samplePath(std::string name) {
    return "samples/" + name + ".wav";
  }
};

class SampleEditScreen : public ui::ModuleScreen<Sampler> {
public:

  std::shared_ptr<Waveform> topWF;
  WaveformWidget<Waveform> topWFW;
  std::shared_ptr<Waveform> mainWF;
  WaveformWidget<Waveform> mainWFW;

  SampleEditScreen(Sampler *);

  void draw(drawing::Canvas&) override;

  bool keypress(ui::Key) override;

};

}
