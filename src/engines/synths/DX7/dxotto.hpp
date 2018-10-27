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

      Property<int> preset      = {this, "preset",    1,   has_limits::init(1, 32),    steppable::init(1)};
      Property<float> variable1      = {this, "variable1",    0,   has_limits::init(0, 1),    steppable::init(0.01)};
      Property<float> variable2      = {this, "variable2",    0,   has_limits::init(0, 1),    steppable::init(0.01)};
      Property<float> variable3       = {this, "variable3",      0.3, has_limits::init(0, 1),    steppable::init(0.01)};

      Property<int> algN    =  {this, "algN",     0,    has_limits::init(0, 31),    steppable::init(1)};
      Property<int> feedback = {this, "feedback", 0,    has_limits::init(0, 99),    steppable::init(0)};

      Property<int> opRateScale_0 = {this, "opRateScale_0", 1,    has_limits::init(0, 99),    steppable::init(1)};
      Property<int> opRateScale_1 = {this, "opRateScale_1", 1,    has_limits::init(0, 99),    steppable::init(1)};
      Property<int> opRateScale_2 = {this, "opRateScale_2", 1,    has_limits::init(0, 99),    steppable::init(1)};
      Property<int> opRateScale_3 = {this, "opRateScale_3", 1,    has_limits::init(0, 99),    steppable::init(1)};
      Property<int> opRateScale_4 = {this, "opRateScale_4", 1,    has_limits::init(0, 99),    steppable::init(1)};
      Property<int> opRateScale_5 = {this, "opRateScale_5", 1,    has_limits::init(0, 99),    steppable::init(1)};



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
