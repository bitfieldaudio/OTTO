#pragma once

#include <array>

#include "core/engines/engine.hpp"
#include "core/audio/faust.hpp"
#include "core/ui/canvas.hpp"
#include "core/ui/engine-ui.hpp"

namespace otto::engines {

  struct SimpleDrumVoice : audio::FaustWrapper<0, 1> {
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

  class SimpleDrumsEngine : public engines::SynthEngine {
    audio::ProcessBuffer<1> proc_buf;
    audio::ProcessBuffer<1> voice_buf;
  public:
    std::array<SimpleDrumVoice, 24> voices;

    int currentVoiceIdx = 0 ;

    ui::EngineScreen<SimpleDrumsEngine>::ptr screen;

    SimpleDrumsEngine();
    ~SimpleDrumsEngine();

    audio::ProcessData<1> process(audio::ProcessData<0>) override;

    void display() override;

    nlohmann::json to_json() const override;
    void from_json(const nlohmann::json&) override;
  };

  class SimpleDrumsScreen : public ui::EngineScreen<SimpleDrumsEngine> {
    void drawOsc(ui::vg::Canvas& ctx, SimpleDrumVoice::Props::Osc &osc);
    void drawKbd(ui::vg::Canvas& ctx);
  private:
    void draw(ui::vg::Canvas& ctx) override;

    bool keypress(ui::Key key) override;
    void rotary(ui::RotaryEvent) override;

  public:

    SimpleDrumsScreen(SimpleDrumsEngine *engine) :
      ui::EngineScreen<SimpleDrumsEngine>(engine) {}
  };

}
