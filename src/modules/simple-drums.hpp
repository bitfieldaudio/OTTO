#pragma once

#include <array>

#include "core/modules/module.hpp"
#include "core/audio/faust.hpp"
#include "core/ui/canvas.hpp"
#include "core/ui/module-ui.hpp"

namespace top1::modules {
  class SimpleDrumVoice : public audio::FaustWrapper {
  public:
    struct Data : public modules::Data {
      struct Osc : modules::Data {
        modules::Opt<float> freq        = {this, "FREQ", 80, 5, 500, 4.95};
        modules::Opt<float> noiseLvl    = {this, "NOISE", 0.5, 0, 1, 0.01};
        modules::Opt<float> toneDecay   = {this, "TONE_DECAY", 0, -1, 1, 0.02};
        modules::ExpOpt cutoff          = {this, "CUTOFF", 7000, 10, 7000, 1.3};
        modules::Opt<bool> filterSwitch = {this, "FILTER_SWITCH", true};
        modules::Opt<float> decayGraph  = {this, "DECAY_GRAPH", 0, -1, 1, 0,false};
      } D1, D2;

      struct : modules::Data {
        modules::Opt<float> attack      = {this, "ATTACK", 0, 0, 2, 0.02};
        modules::Opt<float> sustain     = {this, "SUSTAIN", 1, 0, 2, 0.02};
        modules::Opt<float> release     = {this, "RELEASE", 0.2, 0, 2, 0.02};
      } envelope;

      modules::Opt<bool> trigger = {this, "TRIGGER", false, false};

      Data() {
        subGroup("D1", D1);
        subGroup("D2", D2);
        subGroup("ENVELOPE", envelope);
      }

      Data(Data&) = delete;
      Data(Data&&) = delete;
    } data;

    SimpleDrumVoice();
  };


  class SimpleDrumsModule : public modules::SynthModule {
  public:
    std::array<SimpleDrumVoice, 24> voices;

    uint currentVoiceIdx = 0 ;

    ui::ModuleScreen<SimpleDrumsModule>::ptr screen;

    SimpleDrumsModule();
    ~SimpleDrumsModule();

    void process(audio::ProcessData&) override;

    void display() override;

    top1::tree::Node serialize() override;
    void deserialize(top1::tree::Node) override;
  };

  class SimpleDrumsScreen : public ui::ModuleScreen<SimpleDrumsModule> {
    void drawOsc(ui::drawing::Canvas& ctx, SimpleDrumVoice::Data::Osc &osc);
    void drawKbd(ui::drawing::Canvas& ctx);
  private:
    void draw(ui::drawing::Canvas& ctx) override;

    bool keypress(ui::Key key) override;

  public:

    SimpleDrumsScreen(SimpleDrumsModule *module) :
      ui::ModuleScreen<SimpleDrumsModule>(module) {}
  };

}
