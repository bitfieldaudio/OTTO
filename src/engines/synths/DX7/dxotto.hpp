#pragma once

#include "core/engine/engine.hpp"

#include "core/audio/faust.hpp"
#include "core/audio/voice_manager.hpp"

namespace otto::engines {

  using namespace core;
  using namespace core::engine;
  using namespace props;

  struct DXOTTOSynth : SynthEngine, EngineWithEnvelope {

    struct Props : Properties<> {

      Property<float> preset      = {this, "drawbar1",    1,   has_limits::init(0, 1),    steppable::init(0.01)};
      Property<float> variable1      = {this, "drawbar2",    0,   has_limits::init(0, 1),    steppable::init(0.01)};
      Property<float> variable2      = {this, "drawbar3",    0,   has_limits::init(0, 1),    steppable::init(0.01)};
      Property<float> variable3       = {this, "leslie",      0.3, has_limits::init(0, 1),    steppable::init(0.01)};

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
