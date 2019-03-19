#pragma once

#include "core/engine/engine.hpp"
#include "core/voices/voice_manager.hpp"

#include <Gamma/Filter.h>
#include <Gamma/Noise.h>
#include <Gamma/Oscillator.h>

namespace otto::engines {

  using namespace core;
  using namespace core::engine;
  using namespace props;

  struct RhodesSynth : SynthEngine<RhodesSynth>, EngineWithEnvelope {
    static constexpr std::string_view name = "Rhodes";
    struct Props {
      Property<float> aggro = {1, limits(0.5, 1), step_size(0.01)};
      Property<float> asymmetry = {1, limits(1, 3), step_size(0.05)};
      Property<float> lfo_speed = {0.1, limits(0, 1), step_size(0.01)};
      Property<float> lfo_depth = {0.1, limits(0, 1), step_size(0.01)};

      DECL_REFLECTION(Props, aggro, asymmetry, lfo_speed, lfo_depth);
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

    DECL_REFLECTION(RhodesSynth, props, ("voice_manager", &RhodesSynth::voice_mgr_));

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
      gam::Biquad<> pickup_lpf;
      gam::Biquad<> pickup_hpf;

      gam::Osc<> overtones;
      gam::Decay<> env;

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
