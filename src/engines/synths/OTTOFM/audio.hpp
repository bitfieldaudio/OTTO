#pragma once

#include <Gamma/Envelope.h>
#include <Gamma/Filter.h>
#include <Gamma/Oscillator.h>
#include <Gamma/Noise.h>

#include "core/voices/voice_manager.hpp"
#include "ottofm.hpp"

namespace otto::engines::ottofm {

  struct Voice : voices::VoiceBase<Voice> {
    Voice(Audio& a) noexcept;

    // Not private because we need to show activity levels on screen
    std::array<util::dsp::FMOperator, 4> operators;
    gam::ADSR<> env_ = {0.1f, 0.1f, 0.7f, 2.0f, 1.f, -4.f};

    // These voices only have process calls.
    // This saves us from checking the current algorithm every sample.
    core::audio::ProcessData<1> process(core::audio::ProcessData<1> data) noexcept;

    void on_note_on(float) noexcept;
    void on_note_off() noexcept;

    void reset_envelopes() noexcept;
    void release_envelopes() noexcept;

    void set_frequencies() noexcept;

    /// Use actions from base class
    using VoiceBase::action;

    // Here are declarations for actionhandlers for the voice.
    // It's all of the properties since nothing is being done in postprocessing.
    /// TODO!

    void action(voices::attack_tag::action, float a) noexcept
    {
      env_.attack(a * a * 8.f + 0.005f);
    }
    void action(voices::decay_tag::action, float d) noexcept
    {
      env_.decay(d * d * 4.f + 0.005f);
    }
    void action(voices::sustain_tag::action, float s) noexcept
    {
      env_.sustain(s);
    }
    void action(voices::release_tag::action, float r) noexcept
    {
      env_.release(r * r * 8.f + 0.005f);
    }

  private:
    Audio& audio;
  };

  struct Audio {
    Audio() noexcept;

    float get_activity_level(int op) noexcept;

    // Here goes actionhandler declarations for the engine that the voices doesn't need to know about.
    // In this case, none.

    template<typename Tag, typename... Args>
    auto action(itc::Action<Tag, Args...> a, Args... args) noexcept
      -> std::enable_if_t<itc::ActionReciever::is<voices::VoiceManager<Voice, 6>, itc::Action<Tag, Args...>>>
    {
      voice_mgr_.action(a, args...);
    }

    // Only a process call, since this sums the process calls of the voices.
    audio::ProcessData<1> process(audio::ProcessData<1>) noexcept;

  private:
    friend Voice;

    // Only used internally. At the end of the buffer, 
    // update activity values of operators from last triggered voice
    Voice* last_voice = nullptr;

    std::atomic<float>* shared_activity0 = nullptr;
    std::atomic<float>* shared_activity1 = nullptr;
    std::atomic<float>* shared_activity2 = nullptr;
    std::atomic<float>* shared_activity3 = nullptr;

    voices::VoiceManager<Voice, 6> voice_mgr_ = {*this};
  };

}