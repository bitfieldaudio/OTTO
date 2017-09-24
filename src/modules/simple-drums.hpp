#pragma once

#include <array>

#include "core/modules/module.hpp"
#include "core/audio/faust.hpp"
#include "core/ui/canvas.hpp"
#include "core/ui/module-ui.hpp"

namespace top1::modules {

  struct SimpleDrumVoice : audio::FaustWrapper {
    struct Props : Properties {
      struct Osc : Properties {
        Property<float> freq        = {this, "FREQ", 80, {5, 500, 4.95}};
        Property<float> noiseLvl    = {this, "NOISE", 0.5, {0, 1, 0.01}};
        Property<float> toneDecay   = {this, "TONE_DECAY", 0, {-1, 1, 0.02}};
        Property<float> cutoff      = {this, "CUTOFF", 7000, {10, 7000, 1.3}};
        Property<bool> filterSwitch = {this, "FILTER_SWITCH", true};
        Property<float, def,
                 false> decayGraph  = {this, "DECAY_GRAPH", 0, {-1, 1, 0}};
        using Properties::Properties;
      } D1 {this, "D1"}, D2 {this, "D2"};

      struct : Properties {
        Property<float> attack      = {this, "ATTACK",    0, {0, 2, 0.02}};
        Property<float> sustain     = {this, "SUSTAIN",   1, {0, 2, 0.02}};
        Property<float> release     = {this, "RELEASE", 0.2, {0, 2, 0.02}};
        using Properties::Properties;
      } envelope {this, "ENVELOPE"};

      Property<bool, def, false> trigger = {this, "TRIGGER", false};
    } props;

    SimpleDrumVoice();
  };


  class SimpleDrumsModule : public modules::SynthModule {
    audio::RTBuffer<float> buf;
  public:
    std::array<SimpleDrumVoice, 24> voices;

    uint currentVoiceIdx = 0 ;

    ui::ModuleScreen<SimpleDrumsModule>::ptr screen;

    SimpleDrumsModule();
    ~SimpleDrumsModule();

    void process(const audio::ProcessData&) override;

    void display() override;

    top1::tree::Node makeNode() override;
    void readNode(top1::tree::Node) override;
  };

  class SimpleDrumsScreen : public ui::ModuleScreen<SimpleDrumsModule> {
    void drawOsc(ui::drawing::Canvas& ctx, SimpleDrumVoice::Props::Osc &osc);
    void drawKbd(ui::drawing::Canvas& ctx);
  private:
    void draw(ui::drawing::Canvas& ctx) override;

    bool keypress(ui::Key key) override;
    void rotary(ui::RotaryEvent) override;

  public:

    SimpleDrumsScreen(SimpleDrumsModule *module) :
      ui::ModuleScreen<SimpleDrumsModule>(module) {}
  };

}
