#pragma once

#include <array>

#include "../module.h"
#include "../globals.h"
#include "../faust.h"
#include "../ui.h"

class SimpleDrumVoice : public FaustWrapper {
public:
  struct Osc {
    float *freq;
    float *noiseLvL;
    float *toneDecay;
    float *cutoff;
    float *filterSwitch;

    float *decayGraph;
  } D1, D2;

  struct {
    float *attack;
    float *sustain;
    float *decay;
  } envelope;

  float *trigger;

  SimpleDrumVoice();
};


class SimpleDrumsModule : public SynthModule {
public:
  std::array<SimpleDrumVoice, 24> voices;

  uint currentVoiceIdx = 0 ;

  ui::ModuleScreen<SimpleDrumsModule> *screen;

  SimpleDrumsModule();
  ~SimpleDrumsModule();

  void process(uint nframes) override;

  void display() override {
    GLOB.ui.display(screen);
  }
};

class SimpleDrumsScreen : public ui::ModuleScreen<SimpleDrumsModule> {
  void drawOsc(NanoCanvas::Canvas& ctx, SimpleDrumVoice::Osc &osc);
  void drawKbd(NanoCanvas::Canvas& ctx);
private:
  void draw(NanoCanvas::Canvas& ctx) override;

  bool keypress(ui::Key key) override;

public:

  SimpleDrumsScreen(SimpleDrumsModule *module) :
    ui::ModuleScreen<SimpleDrumsModule>(module) {}
};
