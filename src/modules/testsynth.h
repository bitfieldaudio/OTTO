#pragma once

#include "../module.h"
#include "../globals.h"
#include "../faust-module.h"
#include "../ui.h"

/**
 * Generates a square wave
 */
class TestSynth : public FaustSynthModule {
  ui::ModuleScreen<TestSynth> *screen;
public:
  float *frequency;

  TestSynth();
  ~TestSynth();
};

class TestSynthScreen : public ui::ModuleScreen<TestSynth> {
private:
  virtual void draw(const ui::ContextPtr& cr) override;

  virtual bool keypress(ui::Key key) override;

public:

  TestSynthScreen(TestSynth *module) : ui::ModuleScreen<TestSynth>(module) {}
};
