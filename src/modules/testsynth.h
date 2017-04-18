#pragma once

#include "../module.h"
#include "../globals.h"
#include "../faust.h"
#include "../ui.h"
/**
 * Generates a square wave
 */
class TestSynth : public SynthModule {

  ui::ModuleScreen<TestSynth> *screen;

  FaustWrapper faust;

public:
  TestSynth();
  ~TestSynth();

  float *frequency;
  int cur;

  void process(uint nframes) override {
    faust.process(nframes);
  }
};

class TestSynthScreen : public ui::ModuleScreen<TestSynth> {
private:
  virtual void draw(const ui::ContextPtr& cr) override;

  virtual bool keypress(ui::Key key) override;

public:

  TestSynthScreen(TestSynth *module) : ui::ModuleScreen<TestSynth>(module) {}
};
