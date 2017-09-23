#pragma once

#include "core/modules/module.hpp"
#include "core/modules/module-props.hpp"
#include "core/modules/faust-module.hpp"
#include "core/ui/module-ui.hpp"

namespace top1::modules {

  class NukeSynth : public FaustSynthModule {

    ui::ModuleScreen<NukeSynth>::ptr screen;

  public:

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

    void process(const audio::ProcessData&) override;

    void display() override;
  };
}
