#pragma once

#include "services/audio_manager.hpp"
#include "voice_manager.hpp"

namespace otto::core::voices {

  // PRE BASE //

  template<typename D, typename P>
  PreBase<D, P>::PreBase(Props& props) noexcept : props(props)
  {}

  // VOICE BASE //

  template<typename D, typename P>
  VoiceBase<D, P>::VoiceBase(Pre& pre) noexcept : pre(pre), props(pre.props)
  {
    glide_ = frequency();
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
  void VoiceBase<D, P>::frequency(float freq) noexcept
  {
    frequency_ = freq;
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
    return !env_.released();
  }

  template<typename D, typename P>
  float VoiceBase<D, P>::envelope() noexcept
  {
    return env_.value();
  }

  template<typename D, typename P>
  void VoiceBase<D, P>::trigger(int midi_note, float detune, float velocity, bool legato) noexcept
  {
    // TODO: jump/retrig: non-stolen voices skip portamento.
    midi_note_ = midi_note;
    //Sets target value of portamento to new note
    glide_ = midi::note_freq(midi_note) * detune;
    frequency_ = glide_();
    velocity_ = velocity;
    if (!legato) on_note_on();
    env_.resetSoft();
  }

  template<typename D, typename P>
  void VoiceBase<D, P>::release() noexcept
  {
    if (is_triggered()) {
      env_.release();
      on_note_off();
    }
  }

  // POST BASE //

  template<typename D, typename V>
  PostBase<D, V>::PostBase(Pre& pre) noexcept : pre(pre), props(pre.props)
  {}

  // VOICE ALLOCATORS //
  // INTERFACE //
  template<typename V, int N>
  VoiceManager<V, N>::IVoiceAllocator::IVoiceAllocator(VoiceManager& vm_in) : vm(vm_in) {
    DLOGI("Creating new voiceallocator.");
    // Note. These lines belong in the destructor, but the order of constructing
    // a new allocator vs. destroying the old one is weird.
    util::for_each(vm.voices_, &Voice::release);
    vm.note_stack.clear();
    vm.free_voices.clear();

    for (auto &voice : vm.voices_) vm.free_voices.push_back(&voice);
    DLOGI("FREE VOICES: {}", vm.free_voices.size());
  }

  template<typename V, int N>
  VoiceManager<V, N>::IVoiceAllocator::~IVoiceAllocator() {}

  template<typename V, int N>
  void VoiceManager<V, N>::IVoiceAllocator::handle_midi_off(const otto::core::midi::NoteOffEvent & evt) noexcept {
    auto key = evt.key + vm.settings_props.octave * 12 + vm.settings_props.transpose;
    if (vm.sustain_) {
      auto found = util::find_if(vm.note_stack, [&] (auto& nvp) { return nvp.key == key; });
      if (found != vm.note_stack.end()) {
        found->should_release = true;
      }
    } else {
      stop_voice(key);
    }
  }

  template<typename V, int N>
  auto VoiceManager<V, N>::IVoiceAllocator::get_voice(int key) noexcept -> Voice&
  {
    if (vm.free_voices.size() > 0) {
      // Reuses the voice that last played the note if it exists
      auto it = util::find_if(vm.note_stack, [key](NoteVoicePair& nvp) { return nvp.note == key; });
      auto fvit = it == vm.note_stack.end() ? vm.free_voices.begin() : util::find(vm.free_voices, it->voice);
      auto& v = **fvit;
      vm.free_voices.erase(fvit);
      return v;
    } else {
      auto found = util::find_if(vm.note_stack, [](NoteVoicePair& nvp) { return nvp.has_voice(); });
      if (found != vm.note_stack.end()) {
        DLOGI("Stealing voice {} from key {}", (found->voice - vm.voices_.data()), found->note);
        Voice& v = *found->voice;
        v.release();
        found->voice = nullptr;
        return v;
      } else {
        DLOGE("No voice found. Using voice 0");
        return vm.voices_[0];
      }
    }
  }

  template<typename V, int N>
  void VoiceManager<V, N>::IVoiceAllocator::stop_voice(int key) noexcept {
    auto free_voice = [this](Voice& v) {
        //TODO: this used to be reversed. Does it cause problems in poly?
        auto found = std::find_if(vm.note_stack.begin(), vm.note_stack.end(),
                                  [](auto nvp) { return !nvp.has_voice(); });
        if (found != vm.note_stack.end()) {
          found->voice = &v;
          v.trigger(found->note, found->detune, found->velocity, vm.settings_props.legato);
        } else {
          v.release();
          vm.free_voices.push_back(&v);
        }
    };

    auto it = std::remove_if(vm.note_stack.begin(), vm.note_stack.end(), [&](auto nvp) {
      if (nvp.key == key) {
        if (nvp.has_voice()) {
          free_voice(*nvp.voice);
        }
        return true;
      }
      return false;
    });
    vm.note_stack.erase(it, vm.note_stack.end());
  }

  // PLAYMODE ALLOCATORS //
  // POLY and INTERVAL are dynamically allocated (polyphonic),
  // while MONO and UNISON are statically allocated (monophonic)

  // POLY //
  template<typename V, int N>
  void VoiceManager<V, N>::PolyAllocator::handle_midi_on(const midi::NoteOnEvent& evt) noexcept
  {
    auto& vm = this->vm;
    auto key = evt.key + vm.settings_props.octave * 12 + vm.settings_props.transpose;
    this->stop_voice(key);
    Voice& voice = this->get_voice(key);
    vm.note_stack.push_front({.key = key, .note = key, .detune = 1, .velocity = evt.velocity / 127.f, .voice = &voice});
    voice.trigger(key, 1, evt.velocity / 127.f, false);
  }

  // INTERVAL //
  template<typename V, int N>
  void VoiceManager<V, N>::IntervalAllocator::handle_midi_on(const midi::NoteOnEvent& evt) noexcept
  {
    auto& vm = this->vm;
    auto key = evt.key + vm.settings_props.octave * 12 + vm.settings_props.transpose;
    auto interval = vm.settings_props.interval;
    for (int i = 0; i < 2; ++i) {
      this->stop_voice(key);
      Voice& voice = this->get_voice(key + interval * i);
      vm.note_stack.push_front({.key = key, .note = key + interval * i, .detune = 1, .velocity = evt.velocity / 127.f, .voice = &voice});
      voice.trigger(key + interval * i, 1, evt.velocity / 127.f, false);
    }
  }

  // MONO //
  template<typename V, int N>
  VoiceManager<V, N>::MonoAllocator::MonoAllocator(VoiceManager& vm_in) : IVoiceAllocator(vm_in)
  {
    for (int i = 1; i < 3; ++i) {
    auto& voice = vm_in.voices_[i];
    voice.env_.amp(vm_in.settings_props.sub);
    }
  }

  template<typename V, int N>
  VoiceManager<V, N>::MonoAllocator::~MonoAllocator() {
    for (int i = 0; i < N; ++i) {
      auto& voice = this->vm.voices_[i];
      voice.env_.amp(1.f);
    }
  }

  template<typename V, int N>
  void VoiceManager<V, N>::MonoAllocator::handle_midi_on(const midi::NoteOnEvent& evt) noexcept
  {
    constexpr int num_voices_used = 2;
    auto& vm = this->vm;
    auto key = evt.key + vm.settings_props.octave * 12 + vm.settings_props.transpose;
    this->stop_voice(key);
    if (vm.note_stack.size() > 0) {
      for (int i = 0; i < num_voices_used; ++i) {
        // Every iteration in the loop, a new entry is added to the notestack
        auto& note = *(vm.note_stack.begin() + num_voices_used - 1);
        DLOGI("Stealing voice {} from key {}", (note.voice - vm.voices_.data()), note.note);
        Voice &v = *note.voice;
        v.release();
        note.voice = nullptr;
        vm.note_stack.push_front({.key = key, .note = key - 12 * i, .detune = 1, .velocity = evt.velocity / 127.f, .voice = &v});
        v.trigger(key - 12 * i, 1, evt.velocity * (1 - i + vm.settings_props.sub * (float)i) / 127.f, vm.settings_props.legato);
      }
    }
    else {
      for (int i = 0; i < num_voices_used; ++i) {
        auto fvit = vm.free_voices.begin() + i;
        auto& v = **fvit;
        vm.note_stack.push_front({.key = key, .note = key - 12 * i, .detune = 1, .velocity = evt.velocity / 127.f, .voice = &v});
        v.trigger(key - 12 * i, 1, evt.velocity * (1 - i + vm.settings_props.sub * (float)i) / 127.f, false);
      }
    }

  }

  // UNISON //
  template<typename V, int N>
  void VoiceManager<V, N>::UnisonAllocator::handle_midi_on(const midi::NoteOnEvent& evt) noexcept
  {
    constexpr int num_voices_used = 5;
    auto& vm = this->vm;
    auto key = evt.key + vm.settings_props.octave * 12 + vm.settings_props.transpose;
    this->stop_voice(key);
    if (vm.note_stack.size() > 0) {
      for (int i = 0; i<num_voices_used; i++) {
        auto& note = *(vm.note_stack.begin() + num_voices_used - 1);
        DLOGI("Stealing voice {} from key {}", (note.voice - vm.voices_.data()), note.note);
        Voice &v = *note.voice;
        v.release();
        note.voice = nullptr;
        vm.note_stack.push_front({.key = key, .note = key, .detune = vm.detune_values[i], .velocity = evt.velocity / 127.f, .voice = &v});
        v.trigger(key, vm.detune_values[i], evt.velocity / 127.f, vm.settings_props.legato);
      }
    }
    else {
      for (int i = 0; i < num_voices_used; i++) {
        auto vit = vm.free_voices.begin() + i;
        auto &v = **vit;
        vm.note_stack.push_front({.key = key, .note = key, .detune = vm.detune_values[i], .velocity = evt.velocity / 127.f, .voice = &v});
        v.trigger(key, vm.detune_values[i], evt.velocity / 127.f, false);
      }
    }
  }


  // VOICE MANAGER //

  template<typename V, int N>
  VoiceManager<V, N>::VoiceManager(Props& props) noexcept : props(props)
  {
    for (int i = 0; i < voice_count_v; ++i) {
      auto& voice = voices_[i];
      envelope_props.attack.on_change().connect(
        [&voice](float attack) { voice.env_.attack(8 * attack * attack + 0.02); });
      envelope_props.decay.on_change().connect([&voice](float decay) { voice.env_.decay(decay + 0.02); });
      envelope_props.sustain.on_change().connect(
        [&voice](float sustain) { voice.env_.sustain(sustain); });
      envelope_props.release.on_change().connect(
        [&voice](float release) { voice.env_.release(4 * release * release + 0.02); });

      settings_props.portamento.on_change()
        .connect([&voice](float p) {
          voice.glide_.period(p);
        }).call_now(settings_props.portamento);
    }

    settings_props.detune.on_change().connect([this](float det){
      detune_values.clear();
      detune_values.push_back(1);
      for (int i = 1; i<3; i++) {
        detune_values.push_back(1 + det * 0.015f * i);
        detune_values.push_back(1.f / (1.f + det * 0.015f * (float)i));
      }
    }).call_now(settings_props.detune);

    // The second and third voice are sub voices on mono mode. This sets their volume.
    for (int i = 1; i < 3; ++i) {
      auto& voice = voices_[i];
      settings_props.sub.on_change().connect([&voice](float s){
        voice.env_.amp(s);
      });
    }


    settings_props.play_mode.on_change()
      .connect([this](PlayMode mode) {
        switch (mode) {
          case PlayMode::poly: voice_allocator = std::make_unique<PolyAllocator>(*this); break;
          case PlayMode::mono: voice_allocator = std::make_unique<MonoAllocator>(*this); break;
          case PlayMode::unison: voice_allocator = std::make_unique<UnisonAllocator>(*this); break;
          case PlayMode::interval: voice_allocator = std::make_unique<IntervalAllocator>(*this); break;
          default:break;
        }
      })
      .call_now(settings_props.play_mode);

    sustain_.on_change().connect([this](bool val) {
      if (!val) {
        auto copy = note_stack;
        for (auto&& nvp : copy) {
          if (nvp.should_release) {
            voice_allocator->stop_voice(nvp.note);
            DLOGI("Released note {}", nvp.note);
          }
        }
      }
    });
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
      ///Change frequency if applicable
      voice.frequency(voice.glide_() * pitch_bend_);
      ///Get next sample
      // TODO: The voice could be called inside the envelope. Maybe later.
      voice_sum += voice.env_() * voice();
    }
    return post(voice_sum);
  }

  template<typename V, int N>
  void VoiceManager<V, N>::handle_pitch_bend(const midi::PitchBendEvent& evt) noexcept
  {
    pitch_bend_ = powf(2.f, ((float)evt.value / 8192.f) - 1.f);
  }

  template<typename V, int N>
  void VoiceManager<V, N>::handle_control_change(const otto::core::midi::ControlChangeEvent& evt) noexcept
  {
    switch (evt.controler)
    {
      case 0x40: sustain_ = evt.value > 63;
    }
  }

  template<typename V, int N>
  audio::ProcessData<1> VoiceManager<V, N>::process(audio::ProcessData<1> data) noexcept
  {
    for (auto& evt : data.midi) {
      util::match(evt, [&](midi::NoteOnEvent& evt) { voice_allocator->handle_midi_on(evt); },
                  [&](midi::NoteOffEvent& evt) { voice_allocator->handle_midi_off(evt); },
                  [&](midi::ControlChangeEvent& evt) { handle_control_change(evt); },
                  [&](midi::PitchBendEvent& evt) { handle_pitch_bend(evt); },
                  [](auto&) {});
    }

    auto buf = Application::current().audio_manager->buffer_pool().allocate();
    for (auto& frm : buf) {
      frm = (*this)();
    }
    return data.redirect(buf);
  }


  template<typename V, int N>
  auto VoiceManager<V, N>::voices() -> std::array<Voice, voice_count_v>&
  {
    return voices_;
  }

  namespace details {
    inline std::string to_string(PlayMode pm) noexcept
    {
      switch (pm) {
      case PlayMode::poly: return "poly";
      case PlayMode::mono: return "mono";
      case PlayMode::unison: return "unison";
      case PlayMode::interval: return "interval";
      };
      return "";
    }

    inline std::string aux_setting(PlayMode pm) noexcept
    {
      switch (pm) {
        case PlayMode::poly: return "drift";
        case PlayMode::mono: return "sub";
        case PlayMode::unison: return "detune";
        case PlayMode::interval: return "interval";
      };
      return "";
    }
  } // namespace details

} // namespace otto::core::voices

// kak: other_file=voice_manager.hpp
