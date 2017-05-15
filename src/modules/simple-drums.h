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

  uint currentVoiceIdx;

  ui::ModuleScreen<SimpleDrumsModule> *screen;

  SimpleDrumsModule();
  ~SimpleDrumsModule();

  void process(uint nframes) override;
};

class SimpleDrumsScreen : public ui::ModuleScreen<SimpleDrumsModule> {
private:
  virtual void draw(NanoCanvas::Canvas& ctx) override;

  virtual bool keypress(ui::Key key) override;

public:

  SimpleDrumsScreen(SimpleDrumsModule *module) :
    ui::ModuleScreen<SimpleDrumsModule>(module) {}
};
