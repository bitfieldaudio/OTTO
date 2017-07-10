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
class Sampler : module::Module {
public:

  top1::DynArray<float> sampleData;

  ui::ModuleScreen<Sampler>::ptr editScreen;
  ui::ModuleScreen<Sampler>::ptr recordScreen;

  static const uint nVoices = 24;

  struct Data : public module::Data {
    module::Opt<std::string> sampleName = {this, "sample name", ""};

    struct VoiceData : public module::Data {
      module::Opt<int> in = {this, "in", 0, 0, -1, 1};
      module::Opt<int> out = {this, "out", 0, 0, -1, 1};
      module::Opt<int> loopIn = {this, "loopIn", 0, 0, -1, 1};
      module::Opt<int> loopOut = {this, "loopOut", 0, 0, -1, 1};
    } voiceData[nVoices];

    Data() {
      for (uint i = 0; i < nVoices; i++) {
        subGroup(fmt::format("Voice {}", i), voiceData[i]);
      }
    }

  } data;

  Sampler();

  void process(uint nframes);

  void display() override;
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
