#pragma once

#include "core/engines/engine.hpp"
#include "core/engines/engine_props.hpp"
#include "core/engines/faust-engine.hpp"

namespace otto::engines {

  using namespace core;
  using namespace core::engines;

  struct NukeSynth : FaustSynthEngine {

    struct Props : Properties {

      struct : Properties {
        Property<float> attack  = {this, "Attack", 0, {0, 2, 0.02}};
        Property<float> decay   = {this, "Decay", 0, {0, 2, 0.02}};
        Property<float> sustain = {this, "Sustain", 1, {0, 1, 0.02}};
        Property<float> release = {this, "Release", 0.2, {0, 2, 0.02}};
        using Properties::Properties;
      } envelope{this, "envelope"};

      struct : Properties {
        Property<bool, def, false> gate  = {this, "gate", false};
        Property<float, def, false> freq = {this, "freq", 440};
        Property<float, def, false> vel  = {this, "gain", 10, {0, 10, 0.01}};
        using Properties::Properties;
      } midi{this, "midi"};

      Property<float> wave     = {this, "Wave", 0, {0, 4, 0.01}};
      Property<float> relation = {this, "Relation", 2, {0, 3.01, 0.01}};
      Property<float> aux      = {this, "Aux", 0, {0, 3, 0.01}};
      Property<float> filter   = {this, "Filter", 20, {0, 99, 0.5}};

      int last_key = 0;

    } props;

    NukeSynth();

    audio::ProcessData<1> process(audio::ProcessData<0>) override;
  };
} // namespace otto::engines
