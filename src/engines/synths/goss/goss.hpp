#pragma once

#include <Gamma/Filter.h>
#include <Gamma/Oscillator.h>

#include "core/engine/engine.hpp"
#include "core/ui/screen.hpp"
#include "core/voices/voice_manager.hpp"
#include "itc/prop.hpp"
#include "util/reflection.hpp"

namespace otto::engines::goss {

  using namespace core;
  using namespace core::engine;
  using namespace props;

  struct GossScreen;
  using GraphicsSndr = itc::ActionSender<GossScreen>;

  using Sndr = GraphicsSndr;

  struct Actions {
    /// Publish the rotation variable, which is shared between the audio and screen
    using rotation_variable = itc::Action<struct rotation_variable_tag, std::atomic<float>&>;
  };

  struct Props {
    Sndr* sndr;

    Sndr::Prop<struct drawbar1_tag, float> drawbar1 = {sndr, 1, limits(0, 1), step_size(0.01)};
    Sndr::Prop<struct drawbar2_tag, float> drawbar2 = {sndr, 0.5, limits(0, 1), step_size(0.01)};
    Sndr::Prop<struct click_tag, float> click = {sndr, 0.5, limits(0, 1), step_size(0.01)};
    Sndr::Prop<struct leslie_tag, float> leslie = {sndr, 0.3, limits(0, 1), step_size(0.01)};

    DECL_REFLECTION(Props, drawbar1, drawbar2, click, leslie);
  };

  struct GossEngine {
    GossEngine();

  private:
    std::unique_ptr<GossScreen> screen_;
    GraphicsSndr graphics_sndr_;
    Sndr sndr_ = {graphics_sndr_};

    std::atomic<float> rotation_ = 0;
  };

#if false
  struct GossSynth final : SynthEngine<GossSynth> {
    static constexpr util::string_ref name = "Goss";

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
      std::array<gam::Osc<>, 3> pipes;
      gam::Osc<> percussion;
      gam::AD<> perc_env{0.001, 0.2};

      Voice(Pre&) noexcept;

      float operator()() noexcept;

      void on_note_on(float freq_target) noexcept;
    };

    struct Post : voices::PostBase<Post, Voice> {
      gam::Biquad<> lpf;
      gam::Biquad<> hpf;

      Post(Pre&) noexcept;

      float operator()(float) noexcept;
    };

    voices::VoiceManager<Post, 6> voice_mgr_;
  };
#endif

} // namespace otto::engines::goss
