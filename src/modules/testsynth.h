#pragma once

#include "../module.h"
#include "../globals.h"
#include "../faust-module.h"
#include "../ui.h"

/**
 * Generates a square wave
 */
class TestSynth : public FaustSynthModule {
  ui::ModuleScreen<TestSynth>::ptr screen;
public:

  struct Data : module::Data {

    struct : module::Data {
      module::Opt<float> attack      = {this, "ATTACK", 0, 0, 2, 0.02};
      module::Opt<float> decay       = {this, "DECAY", 0, 0, 2, 0.02};
      module::Opt<float> sustain     = {this, "SUSTAIN", 1, 0, 1, 0.02};
      module::Opt<float> release     = {this, "RELEASE", 0.2, 0, 2, 0.02};
    } envelope;

    module::Opt<int> key           = {this, "KEY", 69, 0, 127, 1, false};
    module::Opt<float> velocity    = {this, "VELOCITY", 1, 0, 1, 0.01, false};
    module::Opt<bool> trigger      = {this, "TRIGGER", false, false};

    Data() {
      subGroup("ENVELOPE", envelope);
    }

    Data(Data&) = delete;
    Data(Data&&) = delete;
  } data;

  TestSynth();
  ~TestSynth();

  void process(uint nframes) override;

  void display() override;
};

class TestSynthScreen : public ui::ModuleScreen<TestSynth> {
private:
  virtual void draw(drawing::Canvas& ctx) override;

  virtual bool keypress(ui::Key key) override;

public:

  using ui::ModuleScreen<TestSynth>::ModuleScreen;
};
