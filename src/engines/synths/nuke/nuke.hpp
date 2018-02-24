#pragma once

#include "core/engines/engine.hpp"

#include "core/audio/faust.hpp"
#include "core/audio/voice_manager.hpp"

namespace otto::engines {

  using namespace core;
  using namespace core::engines;
  using namespace props;

  struct NukeSynth : SynthEngine {

    struct Props : Properties<> {

      struct : Properties<> {
        Property<float> attack  = {this, "Attack",  0,   has_limits::init(0, 2), steppable::init( 0.02)};
        Property<float> decay   = {this, "Decay",   0,   has_limits::init(0, 2), steppable::init( 0.02)};
        Property<float> sustain = {this, "Sustain", 1,   has_limits::init(0, 1), steppable::init( 0.02)};
        Property<float> release = {this, "Release", 0.2, has_limits::init(0, 2), steppable::init( 0.02)};
        using Properties::Properties;
      } envelope{this, "envelope"};

      Property<float> wave     = {this, "Wave",     0,  has_limits::init(0, 4),    steppable::init(0.01)};
      Property<float> relation = {this, "Relation", 2,  has_limits::init(0, 3.01), steppable::init(0.01)};
      Property<float> aux      = {this, "Aux",      0,  has_limits::init(0, 3),    steppable::init(0.01)};
      Property<float> filter   = {this, "Filter",   20, has_limits::init(0, 99),   steppable::init(0.5)};

    } props;

    NukeSynth();

    audio::ProcessData<1> process(audio::ProcessData<0>) override;

  private:
    audio::VoiceManager<6> voice_mgr_;
    audio::FaustWrapper<0, 1> faust_;
  };
} // namespace otto::engines
