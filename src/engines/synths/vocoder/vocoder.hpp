#pragma once

#include "core/engines/engine.hpp"

#include "core/audio/faust.hpp"
#include "core/audio/voice_manager.hpp"

namespace otto::engines {

  using namespace core;
  using namespace core::engines;
  using namespace props;

  struct VocoderSynth : SynthEngine, EngineWithEnvelope {

    struct Props : Properties<> {

      Property<float> attTime      = {this, "attTime",    0,   has_limits::init(0, 1),    steppable::init(0.01)};
      Property<float> decTime      = {this, "decTime",    0,   has_limits::init(0, 1),    steppable::init(0.01)};
      Property<float> ratio        = {this, "ratio",      0.1,   has_limits::init(0.1, 2),  steppable::init(0.01)};
      Property<float> gateamount     = {this, "gateamount",   0.3, has_limits::init(0, 1),    steppable::init(0.01)};

    } props;

    VocoderSynth();

    audio::ProcessData<1> process(audio::ProcessData<1>) override;

    ui::Screen& envelope_screen() override {
      return voice_mgr_.envelope_screen();
    }

    ui::Screen& voices_screen() override {
      return voice_mgr_.settings_screen();
    }

  private:
    audio::VoiceManager<6> voice_mgr_;
    audio::FaustWrapper<1, 1> faust_;
  };
} // namespace otto::engines
