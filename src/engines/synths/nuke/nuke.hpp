#pragma once

#include "core/engines/engine.hpp"

#include "core/audio/faust.hpp"
#include "core/audio/voice_manager.hpp"

namespace otto::engines {

  using namespace core;
  using namespace core::engines;
  using namespace props;

  struct NukeSynth : SynthEngine, EngineWithEnvelope {

    struct Props : Properties<> {

      Property<float> wave     = {this, "Wave",     0,  has_limits::init(0, 4),    steppable::init(0.01)};
      Property<float> relation = {this, "Relation", 2,  has_limits::init(0, 3.01), steppable::init(0.01)};
      Property<float> aux      = {this, "Aux",      0,  has_limits::init(0, 3),    steppable::init(0.01)};
      Property<float> filter   = {this, "Filter",   20, has_limits::init(0, 99),   steppable::init(0.5)};

    } props;

    NukeSynth();

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
