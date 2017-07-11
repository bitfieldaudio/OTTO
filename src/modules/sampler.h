#pragma once

#include <fmt/format.h>

#include "../module.h"
#include "../ui/base.h"
#include "../ui/waveform-widget.h"

#include "../util/dyn-array.h"

namespace module {
/**
 * Drum sampler for now
 */
class Sampler : public module::SynthModule {
public:

  size_t maxSampleSize = 0;
  top1::DynArray<float> sampleData;

  ui::ModuleScreen<Sampler>::ptr editScreen;
  ui::ModuleScreen<Sampler>::ptr recordScreen;

  static const uint nVoices = 24;

  struct Data : public module::Data {
    module::Opt<std::string> sampleName = {this, "sample name", ""};

    struct VoiceData : public module::Data {
      module::Opt<int> in = {this, "in", 0};
      module::Opt<int> out = {this, "out", 0};
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

  Sampler();

  void process(uint nframes) override;

  void display() override;

  void load();

  void init() override;

  static std::string samplePath(std::string name) {
    return "samples/" + name + ".wav";
  }

protected:
  uint currentVoiceIdx = 0;
};

class SampleRecordScreen : public ui::ModuleScreen<Sampler> {
public:

  using ui::ModuleScreen<Sampler>::ModuleScreen;

  void draw(NanoCanvas::Canvas&) override {}
};

class SampleEditScreen : public ui::ModuleScreen<Sampler> {
public:

  std::shared_ptr<Waveform> topWF;
  WaveformWidget topWFW;

  SampleEditScreen(Sampler *);

  void draw(NanoCanvas::Canvas&) override;

};

}
