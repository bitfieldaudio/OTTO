#pragma once

#include "services/audio_manager.hpp"
#include "services/ui_manager.hpp"
#include "voice_manager.hpp"

namespace otto::core::voices {

  // VOICE BASE //

  template<typename D>
  VoiceBase<D>::VoiceBase() noexcept
  {
    glide_ = frequency();
    env_.finish();
  }

  template<typename D>
  void VoiceBase<D>::on_note_on(float freq_target) noexcept
  {}

  template<typename D>
  void VoiceBase<D>::on_note_off() noexcept
  {}

  template<typename D>
  float VoiceBase<D>::frequency() noexcept
  {
    return frequency_;
  }

  template<typename D>
  void VoiceBase<D>::frequency(float freq) noexcept
  {
    frequency_ = freq;
  }

  template<typename D>
  float VoiceBase<D>::volume() noexcept
  {
    return volume_;
  }

  template<typename D>
  void VoiceBase<D>::volume(float volume) noexcept
  {
    volume_ = volume;
    // TODO: This should optionally set envelope amp.
  }

  template<typename D>
  int VoiceBase<D>::midi_note() noexcept
  {
    return midi_note_;
  }

  template<typename D>
  float VoiceBase<D>::velocity() noexcept
  {
    return velocity_;
  }

  template<typename D>
  float VoiceBase<D>::aftertouch() noexcept
  {
    return aftertouch_;
  }

  template<typename D>
  bool VoiceBase<D>::is_triggered() noexcept
  {
    return triggered_;
  }

  template<typename D>
  float VoiceBase<D>::envelope() noexcept
  {
    return env_.value();
  }

  template<typename D>
  void VoiceBase<D>::trigger(int midi_note, float detune, float velocity, bool legato, bool jump) noexcept
  {
    midi_note_ = midi_note;
    triggered_ = true;
    // Sets target value of portamento to new note
    glide_ = midi::note_freq(midi_note) * detune;
    frequency_ = glide_();
    // So far, jump/retrig only works for MONO and UNISON
    if (jump) glide_.finish();
    velocity_ = velocity;
    if (!legato) {
      on_note_on(midi::note_freq(midi_note) * detune);
      env_.resetSoft();
    }
  }

  template<typename D>
  void VoiceBase<D>::release() noexcept
  {
    if (is_triggered()) {
      triggered_ = false;
      env_.release();
      on_note_off();
    }
  }

  template<typename D>
  void VoiceBase<D>::release_no_env() noexcept
  {
    // This method is called when a voice is stolen in the static/monophonic playmodes
    // (mono, unison).
    if (is_triggered()) {
      on_note_off();
    }
  }

  // VOICE ALLOCATORS //
  // INTERFACE //
  template<typename V, int N>
  VoiceManager<V, N>::VoiceAllocatorBase::VoiceAllocatorBase(VoiceManager& vm_in) noexcept : vm(vm_in)
  {}

  template<typename V, int N>
  VoiceManager<V, N>::VoiceAllocatorBase::~VoiceAllocatorBase() noexcept
  {}

  template<typename V, int N>
  void VoiceManager<V, N>::VoiceAllocatorBase::handle_midi_off(const otto::core::midi::NoteOffEvent& evt) noexcept
  {
    auto key = evt.key;
    if (vm.sustain_) {
      auto found = util::find_if(vm.note_stack, [&](auto& nvp) { return nvp.key == key; });
      if (found != vm.note_stack.end()) {
        found->should_release = true;
      }
    } else {
      stop_voice(key);
    }
  }

  template<typename V, int N>
  auto VoiceManager<V, N>::VoiceAllocatorBase::get_voice(int key, int note) noexcept -> Voice&
  {
    if (vm.free_voices.size() > 0) {
      // Usual behaviour is to return the next free voice
      auto fvit = vm.free_voices.begin();
      // Finds the voice that last played the note if it exists
      auto it = util::find_if(vm.voices_, [note](Voice& vp) { return vp.midi_note_ == note; });
      // If there is/was a voice that is playing this note
      if (it != vm.voices_.end()) {
        // It's not currently playing; choose this voice
        if (!it->is_triggered()) fvit = util::find(vm.free_voices, it);
        // Otherwise, do nothing - That would mean the voice is playing, and we should not steal it.
      }
      auto& v = **fvit;
      vm.free_voices.erase(fvit);
      return v;
    } else {
      auto reverse_note_stack = util::view::reverse(vm.note_stack);
      auto found = util::find_if(reverse_note_stack, [](NoteStackEntry& nvp) { return nvp.has_voice(); });
      if (found != reverse_note_stack.end()) {
        DLOGI("Stealing voice {} from key {}", (found->voice - vm.voices_.data()), found->note);
        Voice& v = *found->voice;
        v.release();
        found->voice = nullptr;
        return v;
      } else {
        DLOGI("No voice found. Using voice 0");
        return vm.voices_[0];
      }
    }
  }

  template<typename V, int N>
  void VoiceManager<V, N>::VoiceAllocatorBase::stop_voice(int key) noexcept
  {
    auto free_voice = [this](Voice& v) {
      // TODO: this used to be reversed. Does it cause problems in poly?
      auto found = std::find_if(vm.note_stack.begin(), vm.note_stack.end(), [](auto nvp) { return !nvp.has_voice(); });
      if (found != vm.note_stack.end()) {
        found->voice = &v;
        v.trigger(found->note, found->detune, found->velocity, vm.legato_, false);
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
    auto key = evt.key;
    this->stop_voice(key);
    Voice& voice = this->get_voice(key, key);
    vm.note_stack.push_front({.key = key, .note = key, .detune = 1, .velocity = evt.fvelocity(), .voice = &voice});
    voice.trigger(key, vm.rand_values[(&voice - vm.voices_.data())], evt.fvelocity(), false, false);
  }

  template<typename V, int N>
  void VoiceManager<V, N>::PolyAllocator::set_rand(float rand) noexcept
  {}

  // INTERVAL //
  template<typename V, int N>
  void VoiceManager<V, N>::IntervalAllocator::handle_midi_on(const midi::NoteOnEvent& evt) noexcept
  {
    auto& vm = this->vm;
    auto key = evt.key;

    this->stop_voice(key);
    for (int i = 0; i < 2; ++i) {
      Voice& voice = this->get_voice(key, key + interval_ * i);
      vm.note_stack.push_front(
        {.key = key, .note = key + interval_ * i, .detune = 1, .velocity = evt.fvelocity(), .voice = &voice});
      voice.trigger(key + interval_ * i, 1, evt.fvelocity(), false, false);
    }
  }

  template<typename V, int N>
  void VoiceManager<V, N>::IntervalAllocator::set_interval(float interval) noexcept
  {
    interval_ = interval;
  }

  // MONO //
  template<typename V, int N>
  VoiceManager<V, N>::MonoAllocator::MonoAllocator(VoiceManager& vm_in) : VoiceAllocatorBase(vm_in)
  {
    // Note that after allocation, a prop_change of sub property should be sent.
  }

  template<typename V, int N>
  VoiceManager<V, N>::MonoAllocator::~MonoAllocator()
  {
    // Restore the volumes
    for (auto& voice : this->vm.voices()) {
      voice.volume(1);
    }
  }

  template<typename V, int N>
  void VoiceManager<V, N>::MonoAllocator::set_sub(float sub) noexcept
  {
    // The second and third voice are sub voices on mono mode. This sets their volume.
    int sub_number = 1;
    for (auto& voice : util::view::subrange(this->vm.voices(), 1, 3)) {
      voice.volume(sub / (float)sub_number);
      sub_number++;
    }
  }

  template<typename V, int N>
  void VoiceManager<V, N>::MonoAllocator::handle_midi_on(const midi::NoteOnEvent& evt) noexcept
  {
    auto& vm = this->vm;
    auto key = evt.key;
    this->stop_voice(key);
    if (vm.note_stack.size() > 0) {
      for (int i = 0; i < num_voices_used; ++i) {
        int sv = i > 0; // Are we dispatching a subvoice?
        // Every iteration in the loop, a new entry is added to the notestack
        auto& note = *(vm.note_stack.begin() + num_voices_used - 1);
        DLOGI("Stealing voice {} from key {}", (note.voice - vm.voices_.data()), note.note);
        Voice& v = *note.voice;
        // release_no_env calls on_note_off. Don't do this if legato is engaged, since we are stealing the voice
        // and will note call on_note_on again.
        if (!vm.legato_) v.release_no_env();
        note.voice = nullptr;
        vm.note_stack.push_front(
          {.key = key, .note = key - 12 * i, .detune = 1, .velocity = evt.fvelocity(), .voice = &v});
        v.trigger(key - 12 * sv, 1, evt.fvelocity(), vm.legato_, false);
      }
    } else {
      for (int i = 0; i < num_voices_used; ++i) {
        int sv = i > 0; // Are we dispatching a subvoice?
        auto fvit = vm.free_voices.begin() + i;
        auto& v = **fvit;
        vm.note_stack.push_front(
          {.key = key, .note = key - 12 * sv, .detune = 1, .velocity = evt.fvelocity(), .voice = &v});
        v.trigger(key - 12 * sv, 1, evt.fvelocity(), false, vm.retrig_);
      }
    }
  }

  // UNISON //
  template<typename V, int N>
  VoiceManager<V, N>::UnisonAllocator::UnisonAllocator(VoiceManager& vm_in) : VoiceAllocatorBase(vm_in)
  {
    for (int i = 0; i < N; ++i) {
      auto& voice = this->vm.voices_[i];
      voice.env_.amp(1.f / ((float) voice_count_v) - 1.f);
    }
  }

  template<typename V, int N>
  VoiceManager<V, N>::UnisonAllocator::~UnisonAllocator()
  {
    for (int i = 0; i < N; ++i) {
      auto& voice = this->vm.voices_[i];
      voice.env_.amp(1.f);
    }
  }

  template<typename V, int N>
  void VoiceManager<V, N>::UnisonAllocator::set_detune(float detune) noexcept
  {}

  template<typename V, int N>
  void VoiceManager<V, N>::UnisonAllocator::handle_midi_on(const midi::NoteOnEvent& evt) noexcept
  {
    auto& vm = this->vm;
    auto key = evt.key;
    this->stop_voice(key);
    if (vm.note_stack.size() > 0) {
      for (int i = 0; i < num_voices_used; i++) {
        auto& note = *(vm.note_stack.begin() + num_voices_used - 1);
        DLOGI("Stealing voice {} from key {}", (note.voice - vm.voices_.data()), note.note);
        Voice& v = *note.voice;
        // release_no_env calls on_note_off. Don't do this if legato is engaged, since we are stealing the voice
        // and will note call on_note_on again.
        if (!vm.legato_) v.release_no_env();
        note.voice = nullptr;
        vm.note_stack.push_front(
          {.key = key, .note = key, .detune = vm.detune_values[i], .velocity = evt.fvelocity(), .voice = &v});
        v.trigger(key, vm.detune_values[i], evt.fvelocity(), vm.legato_, false);
      }
    } else {
      for (int i = 0; i < num_voices_used; i++) {
        auto vit = vm.free_voices.begin() + i;
        auto& v = **vit;
        vm.note_stack.push_front(
          {.key = key, .note = key, .detune = vm.detune_values[i], .velocity = evt.fvelocity(), .voice = &v});
        v.trigger(key, vm.detune_values[i], evt.fvelocity(), false, vm.retrig_);
      }
    }
  }


  // VOICE MANAGER //

  template<typename V, int N>
  template<typename... Args>
  VoiceManager<V, N>::VoiceManager(Args&&... args) noexcept
    : voices_(util::generate_array<voice_count_v>([&] (int i) { return Voice{args...}; }))
  {

    for (int i = 0; i < voice_count_v; ++i) {
      // auto& voice = voices_[i];
      // envelope_props.attack.on_change().connect(
      //   [&voice](float attack) { voice.env_.attack(8 * attack * attack + 0.02); });
      // envelope_props.decay.on_change().connect([&voice](float decay) { voice.env_.decay(decay + 0.02); });
      // envelope_props.sustain.on_change().connect(
      //   [&voice](float sustain) { voice.env_.sustain(sustain); });
      // envelope_props.release.on_change().connect(
      //   [&voice](float release) { voice.env_.release(4 * release * release + 0.02); });

      // settings_props.portamento.on_change()
      //   .connect([&voice](float p) {
      //     voice.glide_ = voice.glide_.getEnd();
      //     voice.glide_.period(p);
      //   }).call_now(settings_props.portamento);
    }

    // settings_props.detune.on_change().connect([this](float det){
    //   detune_values.clear();
    //   detune_values.push_back(1);
    //   for (int i = 1; i<3; i++) {
    //     detune_values.push_back(1 + det * 0.015f * i);
    //     detune_values.push_back(1.f / (1.f + det * 0.015f * (float)i));
    //   }
    //   for (auto&& [v, d] : util::zip(voices_, detune_values)) v.glide_ = midi::note_freq(v.midi_note_) * d;
    // }).call_now(settings_props.detune);

    // settings_props.rand.on_change().connect([this](float r){
    //   rand_values.clear();
    //     for (int i = 0; i<voice_count_v; i++) {
    //       rand_values.push_back(rand_max[i] * r - r + 1.f);
    //     }
    // }).call_now(settings_props.rand);

    // settings_props.play_mode.on_change()
    //   .connect([this](PlayMode mode) {
    //     switch (mode) {
    //       case PlayMode::poly: voice_allocator = std::make_unique<PolyAllocator>(*this); break;
    //       case PlayMode::mono: voice_allocator = std::make_unique<MonoAllocator>(*this); break;
    //       case PlayMode::unison: voice_allocator = std::make_unique<UnisonAllocator>(*this); break;
    //       case PlayMode::interval: voice_allocator = std::make_unique<IntervalAllocator>(*this); break;
    //       default:break;
    //     }
    //   })
    //   .call_now(settings_props.play_mode);

    // sustain_.on_change().connect([this](bool val) {
    //   if (!val) {
    //     auto copy = note_stack;
    //     for (auto&& nvp : copy) {
    //       if (nvp.should_release) {
    //         voice_allocator->stop_voice(nvp.note);
    //         DLOGI("Released note {}", nvp.note);
    //       }
    //     }
    //   }
    // });
  }

  template<typename V, int N>
  float VoiceManager<V, N>::operator()() noexcept
  {
    float voice_sum = 0.f;
    for (auto& voice : voices_) {
      /// Change frequency if applicable
      voice.frequency(voice.glide_() * pitch_bend_);
      /// Get next sample
      // TODO: The voice could be called inside the envelope. Maybe later.
      voice_sum += voice.env_() * voice();
    }
    return voice_sum;
  }

  template<typename V, int N>
  void VoiceManager<V, N>::handle_pitch_bend(const midi::PitchBendEvent& evt) noexcept
  {
    pitch_bend_ = powf(2.f, ((float) evt.value / 8192.f) - 1.f);
  }

  template<typename V, int N>
  void VoiceManager<V, N>::handle_control_change(const otto::core::midi::ControlChangeEvent& evt) noexcept
  {
    switch (evt.controler) {
      case 0x40: sustain_ = evt.value > 63;
    }
  }

  template<typename V, int N>
  audio::ProcessData<1> VoiceManager<V, N>::process(audio::ProcessData<1> data) noexcept
  {
    for (auto& event : data.midi) handle_midi(event);

    auto buf = Application::current().audio_manager->buffer_pool().allocate();
    for (auto& frm : buf) {
      frm = (*this)();
    }
    return data.with(buf);
  }

  template<typename V, int N>
  void VoiceManager<V, N>::handle_midi(const midi::AnyMidiEvent& event) noexcept
  {
    util::match(
      event, //
      [&](const midi::NoteOnEvent& evt) { voice_allocator->handle_midi_on(evt); },
      [&](const midi::NoteOffEvent& evt) { voice_allocator->handle_midi_off(evt); },
      [&](const midi::ControlChangeEvent& evt) { handle_control_change(evt); },
      [&](const midi::PitchBendEvent& evt) { handle_pitch_bend(evt); }, //
      [](auto&&) {});
  }

  template<typename V, int N>
  auto VoiceManager<V, N>::voices() -> std::array<Voice, voice_count_v>&
  {
    return voices_;
  }

  template<typename V, int N>
  void VoiceManager<V, N>::action(itc::prop_tag_change<play_mode_tag, PlayMode>, PlayMode new_value) noexcept
  {
    switch (new_value) {
      case PlayMode::poly: voice_allocator.template emplace<PolyAllocator>(*this); break;
      case PlayMode::mono: voice_allocator.template emplace<MonoAllocator>(*this); break;
      case PlayMode::unison: voice_allocator.template emplace<UnisonAllocator>(*this); break;
      case PlayMode::interval: voice_allocator.template emplace<IntervalAllocator>(*this); break;
    }
    util::for_each(voices(), &Voice::release);
    note_stack.clear();
    free_voices.clear();
    for (auto&& voice : voices()) {
      free_voices.push_back(&voice);
      voice.env_.amp(1.f);
    }
  }


  template<typename V, int N>
  void VoiceManager<V, N>::action(itc::prop_tag_change<rand_tag, float>, float rand) noexcept
  {
    util::partial_match(voice_allocator, [&](PolyAllocator& a) { a.set_rand(rand); });
  }
  template<typename V, int N>
  void VoiceManager<V, N>::action(itc::prop_tag_change<sub_tag, float>, float sub) noexcept
  {
    util::partial_match(voice_allocator, [&](MonoAllocator& a) { a.set_sub(sub); });
  }
  template<typename V, int N>
  void VoiceManager<V, N>::action(itc::prop_tag_change<detune_tag, float>, float detune) noexcept
  {
    util::partial_match(voice_allocator, [&](UnisonAllocator& a) { a.set_detune(detune); });
  }
  template<typename V, int N>
  void VoiceManager<V, N>::action(itc::prop_tag_change<interval_tag, int>, int interval) noexcept
  {
    util::partial_match(voice_allocator, [&](IntervalAllocator& a) { a.set_interval(interval); });
  }

  template<typename V, int N>
  auto VoiceManager<V, N>::play_mode() noexcept -> PlayMode
  {
    return util::match(
      voice_allocator,                                        //
      [](PolyAllocator&) { return PlayMode::poly; },          //
      [](MonoAllocator&) { return PlayMode::mono; },          //
      [](UnisonAllocator&) { return PlayMode::unison; },      //
      [](IntervalAllocator&) { return PlayMode::interval; }); //
  }

} // namespace otto::core::voices
