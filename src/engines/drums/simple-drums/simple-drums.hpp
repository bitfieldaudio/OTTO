#pragma once

#include <array>

#include "core/engines/engine.hpp"
#include "core/audio/faust.hpp"
#include "core/ui/canvas.hpp"

namespace otto::engines {

  using namespace core;
  using namespace core::engines;
  using namespace props;

  struct SimpleDrumVoice : audio::FaustWrapper<0, 1> {
    struct Props : props::Properties<> {
      struct Osc : props::Properties<> {
        props::Property<float> freq        = {this, "FREQ", 80, has_limits::init(5, 500), steppable::init(4.95)};
        props::Property<float> noiseLvl    = {this, "NOISE", 0.5, has_limits::init(0, 1), steppable::init(0.01)};
        props::Property<float> toneDecay   = {this, "TONE_DECAY", 0, has_limits::init(-1, 1), steppable::init(0.02)};
        props::Property<float> cutoff      = {this, "CUTOFF", 7000, has_limits::init(10, 7000), steppable::init(1.3)};
        props::Property<bool> filterSwitch = {this, "FILTER_SWITCH", true};
        props::Property<float, props::no_serialize> decayGraph  = {this, "DECAY_GRAPH", 0, has_limits::init(-1, 1), steppable::init(0)};
        using Properties::Properties;
      } D1 {this, "D1"}, D2 {this, "D2"};

      struct : Properties {
        props::Property<float> attack      = {this, "ATTACK",    0, has_limits::init(0, 2), steppable::init(0.02)};
        props::Property<float> sustain     = {this, "SUSTAIN",   1, has_limits::init(0, 2), steppable::init(0.02)};
        props::Property<float> release     = {this, "RELEASE", 0.2, has_limits::init(0, 2), steppable::init(0.02)};
        using Properties::Properties;
      } envelope {this, "ENVELOPE"};

      props::Property<bool, props::no_serialize> trigger = {this, "TRIGGER", false};
    } props;

    SimpleDrumVoice();
  };

  struct SimpleDrumsEngine : DrumsEngine {

    struct Props : props::Properties<> {
      nlohmann::json to_json() const override;
      void from_json(const nlohmann::json&) override;

      SimpleDrumsEngine& engine;
      Props(SimpleDrumsEngine* eg) : Properties(), engine(*eg) {}
    } props {this};

    SimpleDrumsEngine();
    ~SimpleDrumsEngine();

    audio::ProcessData<1> process(audio::ProcessData<0>) override;
    
    std::array<SimpleDrumVoice, 24> voices;

    int currentVoiceIdx = 0;

  private:
    audio::ProcessBuffer<1> proc_buf;
    audio::ProcessBuffer<1> voice_buf;
  };

}
