#pragma once

//#include "voice_manager.hpp"
#include "services/audio_manager.hpp"

namespace otto::core::voices {

  // PRE BASE //

  template<typename D, typename P>
  PreBase<D, P>::PreBase(Props& props) noexcept : props(props)
  {}

  // VOICE BASE //

  template<typename D, typename P>
  VoiceBase<D, P>::VoiceBase(Pre& pre) noexcept : pre(pre), props(pre.props)
  {
    env_.finish();
  }

  template<typename D, typename P>
  void VoiceBase<D, P>::on_note_on() noexcept
  {}

  template<typename D, typename P>
  void VoiceBase<D, P>::on_note_off() noexcept
  {}

  template<typename D, typename P>
  float VoiceBase<D, P>::frequency() noexcept
  {
    return frequency_;
  }

  template<typename D, typename P>
  float VoiceBase<D, P>::velocity() noexcept
  {
    return velocity_;
  }

  template<typename D, typename P>
  float VoiceBase<D, P>::aftertouch() noexcept
  {
    return aftertouch_;
  }

  template<typename D, typename P>
  bool VoiceBase<D, P>::is_triggered() noexcept
  {
    return trigger_;
  }

  template<typename D, typename P>
  float VoiceBase<D, P>::envelope() noexcept
  {
    return env_.value();
  }


  // POST BASE //

  template<typename D, typename V>
  PostBase<D, V>::PostBase(Pre& pre) noexcept : pre(pre), props(pre.props)
  {}

  // VOICE MANAGER //

  template<typename V, int N>
  VoiceManager<V, N>::VoiceManager(Props& props) noexcept : props(props)
  {
    for (int i = 0; i < voice_count; ++i) {
      free_voices.push_back(i);
      auto& voice = voices_[i];
      envelope_props.attack.on_change().connect([&voice] (float attack) { voice.env_.attack(attack); });
      envelope_props.decay.on_change().connect([&voice] (float decay) { voice.env_.decay(decay); });
      envelope_props.sustain.on_change().connect([&voice] (float sustain) { voice.env_.sustain(sustain); });
      envelope_props.release.on_change().connect([&voice] (float release) { voice.env_.release(release); });
    }
  }

  template<typename V, int N>
  ui::Screen& VoiceManager<V, N>::envelope_screen() noexcept
  {
    return *envelope_screen_;
  }

  template<typename V, int N>
  ui::Screen& VoiceManager<V, N>::settings_screen() noexcept
  {
    return *settings_screen_;
  }

  template<typename V, int N>
  float VoiceManager<V, N>::operator()() noexcept
  {
    pre();
    float voice_sum = 0.f;
    for (auto& voice : voices_) {
      voice_sum += voice.env_() * voice();
    }
    return post(voice_sum);
  }

  template<typename V, int N>
  auto VoiceManager<V, N>::handle_midi_on(const midi::NoteOnEvent& evt) noexcept -> Voice&
  {
    Voice* voice = &voices_[0];
    switch (play_mode) {
    case PlayMode::mono: voice = &voices_[0]; break;
    case PlayMode::unison: break;
    case PlayMode::poly: break;
    }

    voice->frequency_ =
      midi::note_freq(evt.key + settings_props.octave * 12 + settings_props.transpose);
    voice->velocity_ = evt.velocity / 127.f;
    voice->trigger_ = true;
    voice->env_.resetSoft();
    return *voice;
  }

  template<typename V, int N>
  auto VoiceManager<V, N>::handle_midi_off(const midi::NoteOffEvent& evt) noexcept -> Voice*
  {
    voices_[0].trigger_ = false;
    voices_[0].env_.release();
    return &voices_[0];
  }

  template<typename V, int N>
  audio::ProcessData<1> VoiceManager<V, N>::process(audio::ProcessData<1> data) noexcept
  {
    for (auto& evt : data.midi) {
      util::match(evt, [&](midi::NoteOnEvent& evt) { handle_midi_on(evt); },
                  [&](midi::NoteOffEvent& evt) { handle_midi_off(evt); },
                  [] (auto&) {});
    }
    auto buf = Application::current().audio_manager->buffer_pool().allocate_multi<1>();
    for (auto&& [frm] : buf) {
      frm = (*this)();
    }
    return data.redirect(buf);
  }

  namespace details {
    inline std::string to_string(PlayMode pm) noexcept
    {
      switch (pm) {
      case PlayMode::poly: return "poly";
      case PlayMode::mono: return "mono";
      case PlayMode::unison: return "unison";
      };
      return "";
    }
  } // namespace details

} // namespace otto::core::voices

// kak: other_file=voice_manager.hpp
