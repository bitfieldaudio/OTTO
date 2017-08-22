#pragma once

#include "core/modules/module.hpp"
#include "core/modules/faust-module.hpp"
#include "core/ui/canvas.hpp"
#include "core/ui/module-ui.hpp"

namespace top1::modules {
  class SuperSawSynth : public FaustSynthModule {
    ui::ModuleScreen<SuperSawSynth>::ptr screen;
  public:

    struct Data : modules::Data {

      struct : modules::Data {
        modules::Opt<float> attack      = {this, "ATTACK", 0, 0, 2, 0.02};
        modules::Opt<float> decay       = {this, "DECAY", 0, 0, 2, 0.02};
        modules::Opt<float> sustain     = {this, "SUSTAIN", 1, 0, 1, 0.02};
        modules::Opt<float> release     = {this, "RELEASE", 0.2, 0, 2, 0.02};
      } envelope;

      modules::Opt<int> key           = {this, "KEY", 69, 0, 127, 1, false};
      modules::Opt<float> velocity    = {this, "VELOCITY", 1, 0, 1, 0.01, false};
      modules::Opt<bool> trigger      = {this, "TRIGGER", false, false};

      Data() {
        subGroup("ENVELOPE", envelope);
      }

      Data(Data&) = delete;
      Data(Data&&) = delete;
    } data;

    SuperSawSynth();

    void process(audio::ProcessData&) override;

    void display() override;
  };

} // top1::modules
