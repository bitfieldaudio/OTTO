#pragma once

#include "core/engine/engine.hpp"

#include "core/audio/faust.hpp"
#include "core/voices/voice_manager.hpp"

#include <Gamma/Filter.h>
#include <Gamma/Oscillator.h>

namespace otto::engines {

  using namespace core;
  using namespace core::engine;
  using namespace props;

  struct GossSynth : SynthEngine, EngineWithEnvelope {
    struct Props : Properties<> {
      Property<float> drawbar1 = {this, "drawbar1", 1, has_limits::init(0, 1),
                                  steppable::init(0.01)};
      Property<float> drawbar2 = {this, "drawbar2", 0.2, has_limits::init(0, 1),
                                  steppable::init(0.01)};
      Property<float> drawbar3 = {this, "drawbar3", 0.2, has_limits::init(0, 1),
                                  steppable::init(0.01)};
      Property<float> leslie = {this, "leslie", 0.3, has_limits::init(0, 1), steppable::init(0.01)};

      float rotation = 0;

    } props;

    GossSynth();

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
      float leslie_speed_hi = 0.f;
      float leslie_speed_lo = 0.f;
      float leslie_amount_hi = 0.f;
      float leslie_amount_lo = 0.f;

      gam::LFO<> leslie_filter_hi;
      gam::LFO<> leslie_filter_lo;
      gam::LFO<> pitch_modulation;

      Pre(Props&) noexcept;

      void operator()() noexcept;
    };

    struct Voice : voices::VoiceBase<Voice, Pre> {
      std::array<gam::Sine<>, 3> pipes;

      float operator()() noexcept;
    };

    struct Post : voices::PostBase<Post, Voice> {
      gam::Biquad<> lpf;
      gam::Biquad<> hpf;

      Post(Pre&) noexcept;

      float operator()(float) noexcept;
    };

    voices::VoiceManager<Post, 6> voice_mgr_;
  };
} // namespace otto::engines
