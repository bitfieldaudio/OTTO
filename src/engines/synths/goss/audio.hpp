#pragma once

#include <Gamma/Envelope.h>
#include <Gamma/Filter.h>
#include <Gamma/Oscillator.h>
#include <Gamma/Noise.h>
#include "util/dsp/overdrive.hpp"

#include "core/voices/voice_manager.hpp"
#include "goss.hpp"

//TODO: draw model

namespace otto::engines::goss {

  struct Voice : voices::VoiceBase<Voice> {
    Voice(Audio& a) noexcept;

    float operator()() noexcept;

    void on_note_on(float) noexcept;
    void on_note_off() noexcept;

    /// Use actions from base class
    using VoiceBase::action;

    void action(itc::prop_change<&Props::click>, float c) noexcept;

    void action(itc::prop_change<&Props::model>, int m) noexcept;

    void action(voices::attack_tag::action, float a) noexcept
    {
      env_.attack(a * a * 8.f + 0.01f);
    }
    void action(voices::decay_tag::action, float d) noexcept
    {
      env_.decay(d * d * 4.f + 0.01f);
    }
    void action(voices::sustain_tag::action, float s) noexcept
    {
      env_.sustain(s);
    }
    void action(voices::release_tag::action, float r) noexcept
    {
      env_.release(r * r * 8.f + 0.01f);
    }

  private:
    Audio& audio;

    /// Does not allocate tables. Reads from models in Audio.
    gam::Osc<> voice_player;
    gam::Osc<> percussion_player;

    gam::NoiseBrown<> noise;
    gam::AD<> perc_env{0.01, 0.08};
    gam::ADSR<> env_ = {0.1f, 0.1f, 0.7f, 2.0f, 1.f, -4.f};
  };

  struct Audio {
    Audio(itc::Shared<float>) noexcept;

    void action(itc::prop_change<&Props::drive>, float d) noexcept;

    void action(itc::prop_change<&Props::leslie>, float l) noexcept;

    template<typename Tag, typename... Args>
    auto action(itc::Action<Tag, Args...> a, Args... args) noexcept
      -> std::enable_if_t<itc::ActionReceiver::is<voices::VoiceManager<Voice, 6>, itc::Action<Tag, Args...>>>
    {
      voice_mgr_.action(a, args...);
    }

    float operator()() noexcept;

    audio::ProcessData<1> process(audio::ProcessData<1>) noexcept;

  private:
    friend Voice;

    itc::Shared<float> shared_rotation_;

    void generate_model(gam::Osc<>&, model_type);

    std::array<gam::Osc<>, number_of_models> models;

    gam::Osc<> percussion = {1, 0, 2048};

    float gain = 0.f;
    float output_scaling = 0.f;

    float leslie = 0.f;

    float leslie_speed_hi = 0.f;
    float leslie_speed_lo = 0.f;
    float leslie_amount_hi = 0.f;
    float leslie_amount_lo = 0.f;

    gam::LFO<> leslie_filter_hi;
    gam::LFO<> leslie_filter_lo;
    gam::LFO<> pitch_modulation_hi;

    gam::AccumPhase<> rotation;

    gam::Biquad<> lpf;
    gam::Biquad<> hpf;

    voices::VoiceManager<Voice, 6> voice_mgr_ = {*this};
  };
} // namespace otto::engines::goss
