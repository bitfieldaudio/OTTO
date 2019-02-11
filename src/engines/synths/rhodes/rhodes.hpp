#pragma once

#include "core/engine/engine.hpp"

#include "core/audio/faust.hpp"
#include "core/voices/voice_manager.hpp"

#include <Gamma/Filter.h>
#include <Gamma/Oscillator.h>
#include <Gamma/Noise.h>

namespace otto::engines {

  using namespace core;
  using namespace core::engine;
  using namespace props;

  struct RhodesSynth : SynthEngine, EngineWithEnvelope {
    struct Props : Properties<> {
        Property<float> lfo_speed = {this, "lfo_speed", 0.1, has_limits::init(0, 1),
                                     steppable::init(0.01)};
        Property<float> lfo_depth = {this, "lfo_depth", 0.1, has_limits::init(0, 1),
                                     steppable::init(0.01)};

    } props;

    RhodesSynth();

    audio::ProcessData<1> process(audio::ProcessData<1>) override;

    ui::Screen& envelope_screen() override
    {
      return voice_mgr_.envelope_screen();
    }

    ui::Screen& voices_screen() override
    {
      return voice_mgr_.settings_screen();
    }

  private:
    struct Pre : voices::PreBase<Pre, Props> {

      Pre(Props&) noexcept;

      void operator()() noexcept;
    };

    struct Voice : voices::VoiceBase<Voice, Pre> {
      gam::Biquad<> reson;
      gam::AD<> exciter;
      gam::NoiseWhite<> noise;

      gam::Biquad<> lpf;
      gam::Biquad<> hpf1;
      gam::Biquad<> hpf2;

      float hammer_strength;

      Voice(Pre&) noexcept;

      float operator()() noexcept;
      void on_note_on() noexcept;
    };

    struct Post : voices::PostBase<Post, Voice> {
      gam::LFO<> lfo;
      float lfo_amount;

      Post(Pre&) noexcept;

      float operator()(float) noexcept;
    };

    voices::VoiceManager<Post, 6> voice_mgr_;
  };
} // namespace otto::engines
