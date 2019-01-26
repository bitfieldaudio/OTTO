#pragma once

#include "core/engine/engine.hpp"

#include "core/audio/faust.hpp"
#include "core/audio/voice_manager.hpp"

namespace otto::engines {

  using namespace core;
  using namespace core::engine;
  using namespace props;

  struct PotionSynth : SynthEngine, EngineWithEnvelope {

    struct WavetableOscillator : Properties<> {
      using Properties::Properties;
      Property<float> lfo_speed     = {this, "lfo_speed",     0,  has_limits::init(0, 1),    steppable::init(0.01)};
      Property<float> volume        = {this, "volume",        1,  has_limits::init(0, 1),    steppable::init(0.01)};
      Property<int> remap_type      = {this, "remap_type",    0,  has_limits::init(0, 4),    steppable::init(1)};
      Property<float> remap_amount  = {this, "remap_amt",     0,  has_limits::init(0, 4),    steppable::init(0.01)};

      Property<int> numSamples = {this, "numSamples", 600};
    };

    struct Props : Properties<> {

        std::array<WavetableOscillator,2> oscillators = {{{this, "osc1"}, {this, "osc2"}}};

    } props;

    PotionSynth();

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
