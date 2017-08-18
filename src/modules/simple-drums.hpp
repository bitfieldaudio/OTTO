#pragma once

#include <array>

#include "../module.h"
#include "../globals.h"
#include "../faust.h"
#include "../ui.h"

class SimpleDrumVoice : public FaustWrapper {
public:
  struct Data : public module::Data {
    struct Osc : module::Data {
      module::Opt<float> freq        = {this, "FREQ", 80, 5, 500, 4.95};
      module::Opt<float> noiseLvl    = {this, "NOISE", 0.5, 0, 1, 0.01};
      module::Opt<float> toneDecay   = {this, "TONE_DECAY", 0, -1, 1, 0.02};
      module::ExpOpt cutoff          = {this, "CUTOFF", 7000, 10, 7000, 1.3};
      module::Opt<bool> filterSwitch = {this, "FILTER_SWITCH", true};
      module::Opt<float> decayGraph  = {this, "DECAY_GRAPH", 0, -1, 1, 0,false};
    } D1, D2;

    struct : module::Data {
      module::Opt<float> attack      = {this, "ATTACK", 0, 0, 2, 0.02};
      module::Opt<float> sustain     = {this, "SUSTAIN", 1, 0, 2, 0.02};
      module::Opt<float> release     = {this, "RELEASE", 0.2, 0, 2, 0.02};
    } envelope;

    module::Opt<bool> trigger = {this, "TRIGGER", false, false};

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


class SimpleDrumsModule : public module::SynthModule {
public:
  std::array<SimpleDrumVoice, 24> voices;

  uint currentVoiceIdx = 0 ;

  ui::ModuleScreen<SimpleDrumsModule>::ptr screen;

  SimpleDrumsModule();
  ~SimpleDrumsModule();

  void process(uint nframes) override;

  void display() override {
    GLOB.ui.display(screen);
  }

  top1::tree::Node serialize() override;
  void deserialize(top1::tree::Node) override;
};

class SimpleDrumsScreen : public ui::ModuleScreen<SimpleDrumsModule> {
  void drawOsc(drawing::Canvas& ctx, SimpleDrumVoice::Data::Osc &osc);
  void drawKbd(drawing::Canvas& ctx);
private:
  void draw(drawing::Canvas& ctx) override;

  bool keypress(ui::Key key) override;

public:

  SimpleDrumsScreen(SimpleDrumsModule *module) :
    ui::ModuleScreen<SimpleDrumsModule>(module) {}
};
