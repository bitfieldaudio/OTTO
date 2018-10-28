#pragma once

#include "core/engines/engine.hpp"

#include "core/audio/faust.hpp"
#include "core/audio/voice_manager.hpp"

namespace otto::engines {

  using namespace core;
  using namespace core::engines;
  using namespace props;

  struct DXOTTOSynth : SynthEngine, EngineWithEnvelope {

    struct Props : Properties<> {

      Property<int> preset      = {this, "preset",    1,   has_limits::init(1, 20),    steppable::init(1)};
      Property<float> variable1      = {this, "variable1",    0,   has_limits::init(0, 1),    steppable::init(0.01)};
      Property<float> variable2      = {this, "variable2",    0,   has_limits::init(0, 1),    steppable::init(0.01)};
      Property<float> variable3       = {this, "variable3",      0.3, has_limits::init(0, 1),    steppable::init(0.01)};

      Property<int,no_serialize> algN    =  {this, "algN",     0,    has_limits::init(0, 31),    steppable::init(1)};
      Property<int,no_serialize> feedback = {this, "feedback", 0,    has_limits::init(0, 99),    steppable::init(0)};

      Property<int,no_serialize> opRateScale_0 = {this, "opRateScale_0", 1,    has_limits::init(0, 99),    steppable::init(1)};
      Property<int,no_serialize> opRateScale_1 = {this, "opRateScale_1", 1,    has_limits::init(0, 99),    steppable::init(1)};
      Property<int,no_serialize> opRateScale_2 = {this, "opRateScale_2", 1,    has_limits::init(0, 99),    steppable::init(1)};
      Property<int,no_serialize> opRateScale_3 = {this, "opRateScale_3", 1,    has_limits::init(0, 99),    steppable::init(1)};
      Property<int,no_serialize> opRateScale_4 = {this, "opRateScale_4", 1,    has_limits::init(0, 99),    steppable::init(1)};
      Property<int,no_serialize> opRateScale_5 = {this, "opRateScale_5", 1,    has_limits::init(0, 99),    steppable::init(1)};

      Property<int,no_serialize> opDetune_0 = {this, "opDetune_0", 1,    has_limits::init(0, 99),    steppable::init(1)};
      Property<int,no_serialize> opDetune_1 = {this, "opDetune_1", 1,    has_limits::init(0, 99),    steppable::init(1)};
      Property<int,no_serialize> opDetune_2 = {this, "opDetune_2", 1,    has_limits::init(0, 99),    steppable::init(1)};
      Property<int,no_serialize> opDetune_3 = {this, "opDetune_3", 1,    has_limits::init(0, 99),    steppable::init(1)};
      Property<int,no_serialize> opDetune_4 = {this, "opDetune_4", 1,    has_limits::init(0, 99),    steppable::init(1)};
      Property<int,no_serialize> opDetune_5 = {this, "opDetune_5", 1,    has_limits::init(0, 99),    steppable::init(1)};

      Property<int,no_serialize> opFreq_0 = {this, "opFreq_0", 1,    has_limits::init(0, 99),    steppable::init(1)};
      Property<int,no_serialize> opFreq_1 = {this, "opFreq_1", 1,    has_limits::init(0, 99),    steppable::init(1)};
      Property<int,no_serialize> opFreq_2 = {this, "opFreq_2", 1,    has_limits::init(0, 99),    steppable::init(1)};
      Property<int,no_serialize> opFreq_3 = {this, "opFreq_3", 1,    has_limits::init(0, 99),    steppable::init(1)};
      Property<int,no_serialize> opFreq_4 = {this, "opFreq_4", 1,    has_limits::init(0, 99),    steppable::init(1)};
      Property<int,no_serialize> opFreq_5 = {this, "opFreq_5", 1,    has_limits::init(0, 99),    steppable::init(1)};

      Property<int,no_serialize> opMode_0 = {this, "opMode_0", 1,    has_limits::init(0, 99),    steppable::init(1)};
      Property<int,no_serialize> opMode_1 = {this, "opMode_1", 1,    has_limits::init(0, 99),    steppable::init(1)};
      Property<int,no_serialize> opMode_2 = {this, "opMode_2", 1,    has_limits::init(0, 99),    steppable::init(1)};
      Property<int,no_serialize> opMode_3 = {this, "opMode_3", 1,    has_limits::init(0, 99),    steppable::init(1)};
      Property<int,no_serialize> opMode_4 = {this, "opMode_4", 1,    has_limits::init(0, 99),    steppable::init(1)};
      Property<int,no_serialize> opMode_5 = {this, "opMode_5", 1,    has_limits::init(0, 99),    steppable::init(1)};

      Property<int,no_serialize> ampModSens_0 = {this, "ampModSens_0", 1,    has_limits::init(0, 99),    steppable::init(1)};
      Property<int,no_serialize> ampModSens_1 = {this, "ampModSens_1", 1,    has_limits::init(0, 99),    steppable::init(1)};
      Property<int,no_serialize> ampModSens_2 = {this, "ampModSens_2", 1,    has_limits::init(0, 99),    steppable::init(1)};
      Property<int,no_serialize> ampModSens_3 = {this, "ampModSens_3", 1,    has_limits::init(0, 99),    steppable::init(1)};
      Property<int,no_serialize> ampModSens_4 = {this, "ampModSens_4", 1,    has_limits::init(0, 99),    steppable::init(1)};
      Property<int,no_serialize> ampModSens_5 = {this, "ampModSens_5", 1,    has_limits::init(0, 99),    steppable::init(1)};

      Property<int,no_serialize> keyVelSens_0 = {this, "keyVelSens_0", 1,    has_limits::init(0, 99),    steppable::init(1)};
      Property<int,no_serialize> keyVelSens_1 = {this, "keyVelSens_1", 1,    has_limits::init(0, 99),    steppable::init(1)};
      Property<int,no_serialize> keyVelSens_2 = {this, "keyVelSens_2", 1,    has_limits::init(0, 99),    steppable::init(1)};
      Property<int,no_serialize> keyVelSens_3 = {this, "keyVelSens_3", 1,    has_limits::init(0, 99),    steppable::init(1)};
      Property<int,no_serialize> keyVelSens_4 = {this, "keyVelSens_4", 1,    has_limits::init(0, 99),    steppable::init(1)};
      Property<int,no_serialize> keyVelSens_5 = {this, "keyVelSens_5", 1,    has_limits::init(0, 99),    steppable::init(1)};

      Property<int,no_serialize> outLevel_0 = {this, "outLevel_0", 1,    has_limits::init(0, 99),    steppable::init(1)};
      Property<int,no_serialize> outLevel_1 = {this, "outLevel_1", 1,    has_limits::init(0, 99),    steppable::init(1)};
      Property<int,no_serialize> outLevel_2 = {this, "outLevel_2", 1,    has_limits::init(0, 99),    steppable::init(1)};
      Property<int,no_serialize> outLevel_3 = {this, "outLevel_3", 1,    has_limits::init(0, 99),    steppable::init(1)};
      Property<int,no_serialize> outLevel_4 = {this, "outLevel_4", 1,    has_limits::init(0, 99),    steppable::init(1)};
      Property<int,no_serialize> outLevel_5 = {this, "outLevel_5", 1,    has_limits::init(0, 99),    steppable::init(1)};

      Property<int,no_serialize> egR1_0 = {this, "egR1_0", 1,    has_limits::init(0, 99),    steppable::init(1)};
      Property<int,no_serialize> egR1_1 = {this, "egR1_1", 1,    has_limits::init(0, 99),    steppable::init(1)};
      Property<int,no_serialize> egR1_2 = {this, "egR1_2", 1,    has_limits::init(0, 99),    steppable::init(1)};
      Property<int,no_serialize> egR1_3 = {this, "egR1_3", 1,    has_limits::init(0, 99),    steppable::init(1)};
      Property<int,no_serialize> egR1_4 = {this, "egR1_4", 1,    has_limits::init(0, 99),    steppable::init(1)};
      Property<int,no_serialize> egR1_5 = {this, "egR1_5", 1,    has_limits::init(0, 99),    steppable::init(1)};

      Property<int,no_serialize> egR2_0 = {this, "egR2_0", 1,    has_limits::init(0, 99),    steppable::init(1)};
      Property<int,no_serialize> egR2_1 = {this, "egR2_1", 1,    has_limits::init(0, 99),    steppable::init(1)};
      Property<int,no_serialize> egR2_2 = {this, "egR2_2", 1,    has_limits::init(0, 99),    steppable::init(1)};
      Property<int,no_serialize> egR2_3 = {this, "egR2_3", 1,    has_limits::init(0, 99),    steppable::init(1)};
      Property<int,no_serialize> egR2_4 = {this, "egR2_4", 1,    has_limits::init(0, 99),    steppable::init(1)};
      Property<int,no_serialize> egR2_5 = {this, "egR2_5", 1,    has_limits::init(0, 99),    steppable::init(1)};

      Property<int,no_serialize> egR3_0 = {this, "egR3_0", 1,    has_limits::init(0, 99),    steppable::init(1)};
      Property<int,no_serialize> egR3_1 = {this, "egR3_1", 1,    has_limits::init(0, 99),    steppable::init(1)};
      Property<int,no_serialize> egR3_2 = {this, "egR3_2", 1,    has_limits::init(0, 99),    steppable::init(1)};
      Property<int,no_serialize> egR3_3 = {this, "egR3_3", 1,    has_limits::init(0, 99),    steppable::init(1)};
      Property<int,no_serialize> egR3_4 = {this, "egR3_4", 1,    has_limits::init(0, 99),    steppable::init(1)};
      Property<int,no_serialize> egR3_5 = {this, "egR3_5", 1,    has_limits::init(0, 99),    steppable::init(1)};

      Property<int,no_serialize> egR4_0 = {this, "egR4_0", 1,    has_limits::init(0, 99),    steppable::init(1)};
      Property<int,no_serialize> egR4_1 = {this, "egR4_1", 1,    has_limits::init(0, 99),    steppable::init(1)};
      Property<int,no_serialize> egR4_2 = {this, "egR4_2", 1,    has_limits::init(0, 99),    steppable::init(1)};
      Property<int,no_serialize> egR4_3 = {this, "egR4_3", 1,    has_limits::init(0, 99),    steppable::init(1)};
      Property<int,no_serialize> egR4_4 = {this, "egR4_4", 1,    has_limits::init(0, 99),    steppable::init(1)};
      Property<int,no_serialize> egR4_5 = {this, "egR4_5", 1,    has_limits::init(0, 99),    steppable::init(1)};

      Property<int,no_serialize> egL1_0 = {this, "egL1_0", 1,    has_limits::init(0, 99),    steppable::init(1)};
      Property<int,no_serialize> egL1_1 = {this, "egL1_1", 1,    has_limits::init(0, 99),    steppable::init(1)};
      Property<int,no_serialize> egL1_2 = {this, "egL1_2", 1,    has_limits::init(0, 99),    steppable::init(1)};
      Property<int,no_serialize> egL1_3 = {this, "egL1_3", 1,    has_limits::init(0, 99),    steppable::init(1)};
      Property<int,no_serialize> egL1_4 = {this, "egL1_4", 1,    has_limits::init(0, 99),    steppable::init(1)};
      Property<int,no_serialize> egL1_5 = {this, "egL1_5", 1,    has_limits::init(0, 99),    steppable::init(1)};

      Property<int,no_serialize> egL2_0 = {this, "egL2_0", 1,    has_limits::init(0, 99),    steppable::init(1)};
      Property<int,no_serialize> egL2_1 = {this, "egL2_1", 1,    has_limits::init(0, 99),    steppable::init(1)};
      Property<int,no_serialize> egL2_2 = {this, "egL2_2", 1,    has_limits::init(0, 99),    steppable::init(1)};
      Property<int,no_serialize> egL2_3 = {this, "egL2_3", 1,    has_limits::init(0, 99),    steppable::init(1)};
      Property<int,no_serialize> egL2_4 = {this, "egL2_4", 1,    has_limits::init(0, 99),    steppable::init(1)};
      Property<int,no_serialize> egL2_5 = {this, "egL2_5", 1,    has_limits::init(0, 99),    steppable::init(1)};

      Property<int,no_serialize> egL3_0 = {this, "egL3_0", 1,    has_limits::init(0, 99),    steppable::init(1)};
      Property<int,no_serialize> egL3_1 = {this, "egL3_1", 1,    has_limits::init(0, 99),    steppable::init(1)};
      Property<int,no_serialize> egL3_2 = {this, "egL3_2", 1,    has_limits::init(0, 99),    steppable::init(1)};
      Property<int,no_serialize> egL3_3 = {this, "egL3_3", 1,    has_limits::init(0, 99),    steppable::init(1)};
      Property<int,no_serialize> egL3_4 = {this, "egL3_4", 1,    has_limits::init(0, 99),    steppable::init(1)};
      Property<int,no_serialize> egL3_5 = {this, "egL3_5", 1,    has_limits::init(0, 99),    steppable::init(1)};

      Property<int,no_serialize> egL4_0 = {this, "egL4_0", 1,    has_limits::init(0, 99),    steppable::init(1)};
      Property<int,no_serialize> egL4_1 = {this, "egL4_1", 1,    has_limits::init(0, 99),    steppable::init(1)};
      Property<int,no_serialize> egL4_2 = {this, "egL4_2", 1,    has_limits::init(0, 99),    steppable::init(1)};
      Property<int,no_serialize> egL4_3 = {this, "egL4_3", 1,    has_limits::init(0, 99),    steppable::init(1)};
      Property<int,no_serialize> egL4_4 = {this, "egL4_4", 1,    has_limits::init(0, 99),    steppable::init(1)};
      Property<int,no_serialize> egL4_5 = {this, "egL4_5", 1,    has_limits::init(0, 99),    steppable::init(1)};

    } props;

    DXOTTOSynth();

    audio::ProcessData<1> process(audio::ProcessData<1>) override;

    ui::Screen& envelope_screen() override {
      return voice_mgr_.envelope_screen();
    }

    ui::Screen& voices_screen() override {
      return voice_mgr_.settings_screen();
    }

  private:
    audio::VoiceManager<6> voice_mgr_;
    audio::FaustWrapper<0, 1> faust_;
  };
} // namespace otto::engines
