#pragma once

#include "core/engines/engine.hpp"
#include "core/engines/faust-engine.hpp"

namespace otto::engines {

  using namespace core;
  using namespace core::engines;
  using namespace props;

  struct NukeSynth : FaustSynthEngine {

    struct Props : Properties<> {

      struct : Properties<> {
        Property<float> attack  = {this, "Attack", 0, has_limits::init(0, 2), steppable::init( 0.02)};
        Property<float> decay   = {this, "Decay", 0, has_limits::init(0, 2), steppable::init( 0.02)};
        Property<float> sustain = {this, "Sustain", 1, has_limits::init(0, 1), steppable::init( 0.02)};
        Property<float> release = {this, "Release", 0.2, has_limits::init(0, 2), steppable::init( 0.02)};
        using Properties::Properties;
      } envelope{this, "envelope"};

      struct : Properties<no_serialize> {
        Property<bool> gate  = {this, "gate", false};
        Property<float> freq = {this, "freq", 440};
        Property<float> vel  = {this, "gain", 10, has_limits::init(0, 10), steppable::init(0.01)};
        using Properties::Properties;
      } midi{this, "midi"};

      Property<float> wave     = {this, "Wave", 0, has_limits::init(0, 4), steppable::init(0.01)};
      Property<float> relation = {this, "Relation", 2, has_limits::init(0, 3.01), steppable::init(0.01)};
      Property<float> aux      = {this, "Aux", 0, has_limits::init(0, 3), steppable::init(0.01)};
      Property<float> filter   = {this, "Filter", 20, has_limits::init(0, 99), steppable::init(0.5)};

      int last_key = 0;

    } props;

    NukeSynth();

    audio::ProcessData<1> process(audio::ProcessData<0>) override;
  };
} // namespace otto::engines
