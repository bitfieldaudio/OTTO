#pragma once

#include "core/engines/engine.hpp"
#include "core/engines/engine-props.hpp"
#include "core/engines/faust-engine.hpp"

namespace otto::engines {

  struct NukeSynth : public FaustSynthEngine {

    struct Props : Properties {
      struct : public Properties {
        Property<float> attack      = {this, "ATTACK",  0,   {0, 2, 0.02}};
        Property<float> decay       = {this, "DECAY",   0,   {0, 2, 0.02}};
        Property<float> sustain     = {this, "SUSTAIN", 1,   {0, 1, 0.02}};
        Property<float> release     = {this, "RELEASE", 0.2, {0, 2, 0.02}};
        using Properties::Properties;
      } envelope {this, "ENVELOPE"};

      Property<int, def, false> key        = {this, "KEY", 69, {0, 127, 1}};
      Property<float, def, false> velocity = {this, "VELOCITY", 1, {0, 1, 0.01}};
      Property<bool, def, false> trigger   = {this, "TRIGGER", false};
    } props;

    NukeSynth();

    audio::ProcessData<1> process(audio::ProcessData<0>) override;
  };
}
