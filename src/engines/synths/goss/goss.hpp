#pragma once

#include "core/engine/engine.hpp"

#include "core/voices/voice_manager.hpp"

#include <Gamma/Filter.h>
#include <Gamma/Oscillator.h>

#include "util/reflection.hpp"

namespace otto::engines {

  using namespace core;
  using namespace core::engine;
  using namespace props;

  struct GossSynth final : SynthEngine<GossSynth> {
    static constexpr util::string_ref name = "Goss";

    struct Props {
      Property<float> drawbar1 = {1, limits(0, 1), step_size(0.01)};
      Property<float> drawbar2 = {0.5, limits(0, 1), step_size(0.01)};
      Property<float> click = {0.5, limits(0, 1), step_size(0.01)};
      Property<float> leslie = {0.3, limits(0, 1), step_size(0.01)};

      float rotation_value;

      DECL_REFLECTION(Props, drawbar1, drawbar2, click, leslie);
    } props;

    GossSynth();

    audio::ProcessData<1> process(audio::ProcessData<1>) override;

    voices::IVoiceManager& voice_mgr() override
    {
      return voice_mgr_;
    }

    DECL_REFLECTION(GossSynth, props, ("voice_manager", &GossSynth::voice_mgr_));

  private:
    struct Pre : voices::PreBase<Pre, Props> {
      float leslie_speed_hi = 0.f;
      float leslie_speed_lo = 0.f;
      float leslie_amount_hi = 0.f;
      float leslie_amount_lo = 0.f;

      gam::LFO<> leslie_filter_hi;
      gam::LFO<> leslie_filter_lo;
      gam::LFO<> pitch_modulation_lo;
      gam::LFO<> pitch_modulation_hi;

      gam::AccumPhase<> rotation;

      Pre(Props&) noexcept;

      void operator()() noexcept;
    };

    struct Voice : voices::VoiceBase<Voice, Pre> {
      std::array<gam::Osc<>, 4> pipes;
      gam::Osc<> percussion;
      gam::Decay<> perc_env;

      Voice(Pre&) noexcept;

      float operator()() noexcept;

      void on_note_on() noexcept;
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
