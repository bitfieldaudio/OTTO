#pragma once

#include <Gamma/Envelope.h>
#include <Gamma/Filter.h>
#include <Gamma/Oscillator.h>

#include "core/voices/voice_manager.hpp"
#include "goss.hpp"

namespace otto::engines::goss {

  struct Voice : voices::VoiceBase<Voice> {
    Voice(Audio& a) noexcept;

    float operator()() noexcept;

    void on_note_on(float) noexcept;
    void on_note_off() noexcept;

    void action(itc::prop_change<&Props::click>, float c) noexcept;

  private:
    Audio& audio;
    std::array<gam::Osc<>, 3> pipes;
    gam::Osc<> percussion;
    gam::AD<> perc_env{0.001, 0.2};
    gam::ADSR<> env_;
  };

  struct Audio {
    Audio() noexcept;

    void action(Actions::rotation_variable, std::atomic<float>&) noexcept;
    void action(itc::prop_change<&Props::leslie>, float l) noexcept;
    void action(itc::prop_change<&Props::drawbar1>, float d1) noexcept;
    void action(itc::prop_change<&Props::drawbar2>, float d2) noexcept;

    template<typename Tag, typename... Args>
    auto action(itc::Action<Tag, Args...> a, Args... args) noexcept
      -> std::enable_if_t<itc::ActionReciever::is<voices::VoiceManager<Voice, 6>, itc::Action<Tag, Args...>>>
    {
      voice_mgr_.action(a, args...);
    }

    float operator()() noexcept;

    audio::ProcessData<1> process(audio::ProcessData<1>) noexcept;

  private:
    friend Voice;

    std::atomic<float>* shared_rotation = nullptr;

    float leslie = 0.f;
    float drawbar1 = 0.f;
    float drawbar2 = 0.f;

    float leslie_speed_hi = 0.f;
    float leslie_speed_lo = 0.f;
    float leslie_amount_hi = 0.f;
    float leslie_amount_lo = 0.f;

    gam::LFO<> leslie_filter_hi;
    gam::LFO<> leslie_filter_lo;
    gam::LFO<> pitch_modulation_lo;
    gam::LFO<> pitch_modulation_hi;

    gam::AccumPhase<> rotation;

    gam::Biquad<> lpf;
    gam::Biquad<> hpf;

    voices::VoiceManager<Voice, 6> voice_mgr_ = {*this};
  };
} // namespace otto::engines::goss
