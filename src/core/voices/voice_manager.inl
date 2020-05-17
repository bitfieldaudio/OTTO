#pragma once


#include "services/audio_manager.hpp"
#include "services/ui_manager.hpp"
#include "voice_manager.hpp"

#include <nanorange.hpp>

namespace otto::core::voices {

  // VOICE BASE //

  template<typename D>
  VoiceBase<D>::VoiceBase() noexcept
  {
    glide_ = frequency();
    glide_.finish();
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
  void VoiceBase<D>::trigger(int midi_note, float detune, float velocity, bool legato, bool jump) noexcept
  {
    midi_note_ = midi_note;
    triggered_ = true;
    // Sets target value of portamento to new note
    frequency_ = midi::note_freq(midi_note) * detune;
    // So far, jump/retrig only works for MONO and UNISON
    if (jump || glide_.getEnd() == 1.f) {
      glide_ = frequency_;
      glide_.finish();
    }
    glide_ = frequency_;
    velocity_ = velocity;
    /// If legato is true, the voice will NOT be retriggered.
    /// This means only the frequency will be changed and velocity updated.
    if (!legato) {
      this->derived().on_note_on(frequency_);
    }
  }

  template<typename D>
  void VoiceBase<D>::release() noexcept
  {
    if (is_triggered()) {
      triggered_ = false;
      this->derived().on_note_off();
    }
  }

  template<typename D>
  void VoiceBase<D>::next() noexcept
  {
    frequency_ = glide_() * *pitch_bend_;
  }

  template<typename D>
  void VoiceBase<D>::action(portamento_tag::action, float p) noexcept
  {
    glide_ = glide_.getEnd();
    glide_.period(p);
  }

  template<typename D>
  core::audio::ProcessData<1> VoiceBase<D>::process(core::audio::ProcessData<0> data) noexcept
  {
    auto buf = services::AudioManager::current().buffer_pool().allocate();
    for (auto& f : buf) {
      next();
      f = this->derived()() * this->derived().volume();
    }
    return data.with(buf);
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
      // TODO: Make sure ALL entries with this key are set to release, not just the first.
      auto found = nano::find_if(vm.note_stack, [&](auto& nvp) { return nvp.key == key; });
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
      auto it = nano::find_if(vm.voices_, [note](Voice& vp) { return vp.midi_note_ == note; });
      // If there is/was a voice that is playing this note
      if (it != vm.voices_.end()) {
        // It's not currently playing; choose this voice
        if (!it->is_triggered()) fvit = nano::find(vm.free_voices, it);
        // Otherwise, do nothing - That would mean the voice is playing, and we should not steal it.
      }
      auto& v = **fvit;
      vm.free_voices.erase(fvit);
      return v;
    } else {
      // Steal oldest playing note
      auto found = nano::find_if(vm.note_stack, [](NoteStackEntry& nse) { return nse.has_voice(); });
      if (found != vm.note_stack.end()) {
        // DLOGI("Stealing voice {} from key {}", (found->voice - vm.voices_.data()), found->note);
        Voice& v = *found->voice;
        v.release();
        found->voice = nullptr;
        return v;
      } else {
        // DLOGI("No voice found. Using voice 0");
        return vm.voices_[0];
      }
    }
  }

  template<typename V, int N>
  void VoiceManager<V, N>::VoiceAllocatorBase::stop_voice(int key) noexcept
  {
    auto free_voice = [this](Voice& v) {
      auto found =
        std::find_if(vm.note_stack.rbegin(), vm.note_stack.rend(), [](auto&& nse) { return !nse.has_voice(); });
      if (found != vm.note_stack.rend()) {
        found->voice = &v;
        v.trigger(found->note, found->detune, found->velocity, vm.legato_, false);
      } else {
        v.release();
        vm.free_voices.push_back(&v);
      }
    };

    // Remove-erase in reverse since for all other modes than poly, the note_stack has the format
    // [A1 A2 A3 B1 B2 B3 C1 C2 C3] for instance, where A, B, C are different held keys.
    // If only the C's have voices, when we lift that key, we want the voices to go to the B's
    // while the number is kept the same (e.g. C2 -> B2)
    auto reverse_note_stack = nano::views::reverse(vm.note_stack);

    for (auto&& nse : reverse_note_stack | nano::views::filter([&] (auto&& nse) { return nse.key == key; })) {
      if (nse.has_voice()) {
        free_voice(*nse.voice);
      }
      vm.note_stack.erase(&nse);
    }
  }

  // PLAYMODE ALLOCATORS //
  // POLY and INTERVAL are dynamically allocated (polyphonic),
  // while MONO and UNISON are statically allocated (monophonic)

  // POLY //
  template<typename V, int N>
  VoiceManager<V, N>::PolyAllocator::PolyAllocator(VoiceManager& vm_in) : VoiceAllocatorBase(vm_in)
  {
    for (auto& voice : this->vm.voices()) {
      voice.volume(this->vm.normal_volume);
    }
    set_rand(0);
  };
  template<typename V, int N>
  void VoiceManager<V, N>::PolyAllocator::handle_midi_on(const midi::NoteOnEvent& evt) noexcept
  {
    auto& vm = this->vm;
    auto key = evt.key;
    this->stop_voice(key);
    Voice& voice = this->get_voice(key, key);
    auto res =
      vm.note_stack.push_back({.key = key, .note = key, .detune = 1, .velocity = evt.fvelocity(), .voice = &voice});
    if (res) voice.trigger(key, vm.rand_values[(&voice - vm.voices_.data())], evt.fvelocity(), false, false);
  }

  template<typename V, int N>
  void VoiceManager<V, N>::PolyAllocator::set_rand(float r) noexcept
  {
    auto& vm = this->vm;
    vm.rand_values.clear();
    for (int i = 0; i < voice_count_v; i++) {
      vm.rand_values.push_back(vm.rand_max[i] * r - r + 1.f);
    }
  }

  // INTERVAL //
  template<typename V, int N>
  VoiceManager<V, N>::IntervalAllocator::IntervalAllocator(VoiceManager& vm_in) : VoiceAllocatorBase(vm_in)
  {
    for (auto& voice : this->vm.voices()) {
      voice.volume(this->vm.normal_volume / 2.f);
    }
  };

  template<typename V, int N>
  void VoiceManager<V, N>::IntervalAllocator::handle_midi_on(const midi::NoteOnEvent& evt) noexcept
  {
    auto& vm = this->vm;
    auto key = evt.key;

    this->stop_voice(key);
    for (int i = 0; i < 2; ++i) {
      Voice& voice = this->get_voice(key, key + interval_ * i);
      auto res = vm.note_stack.push_back(
        {.key = key, .note = key + interval_ * i, .detune = 1, .velocity = evt.fvelocity(), .voice = &voice});
      if (res) voice.trigger(key + interval_ * i, 1, evt.fvelocity(), false, false);
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
    // Set all normal voices
    for (auto& voice : this->vm.voices()) {
      voice.volume(this->vm.normal_volume);
    }
    // Note that after allocation, a prop_change of sub property
    // should be sent, to change sub voice volume
  }

  template<typename V, int N>
  void VoiceManager<V, N>::MonoAllocator::set_sub(float sub) noexcept
  {
    // The second and third voice are sub voices on mono mode. This sets their volume.
    int sub_number = 1;
    for (auto& voice : util::view::subrange(this->vm.voices(), 1, 3)) {
      voice.volume(this->vm.normal_volume * sub / (float) sub_number);
      sub_number++;
    }
  }

  template<typename V, int N>
  void VoiceManager<V, N>::MonoAllocator::handle_midi_on(const midi::NoteOnEvent& evt) noexcept
  {
    auto& vm = this->vm;
    auto key = evt.key;
    this->stop_voice(key);
    /// If there is already a note playing that we must steal
    if (vm.note_stack.size() > 0) {
      for (int i = 0; i < num_voices_used; ++i) {
        int sv = i > 0; // Are we dispatching a subvoice?
        // Find the correct voice to steal
        // Every iteration in the loop, a new entry is added to the notestack.
        auto& note = *(vm.note_stack.end() - num_voices_used);
        // DLOGI("Stealing voice {} from key {}", (note.voice - vm.voices_.data()), note.note);
        Voice& v = *note.voice;
        // v.release calls on_note_off. Don't do this if legato is engaged.
        if (!vm.legato_) v.release();
        note.voice = nullptr;
        auto res = vm.note_stack.push_back(
          {.key = key, .note = key - 12 * i, .detune = 1, .velocity = evt.fvelocity(), .voice = &v});
        if (res) v.trigger(key - 12 * sv, 1, evt.fvelocity(), vm.legato_, false);
      }
    } else {
      for (int i = 0; i < num_voices_used; ++i) {
        int sv = i > 0; // Are we dispatching a subvoice?
        auto fvit = vm.free_voices.begin() + i;
        auto& v = **fvit;
        auto res = vm.note_stack.push_back(
          {.key = key, .note = key - 12 * sv, .detune = 1, .velocity = evt.fvelocity(), .voice = &v});
        if (res) v.trigger(key - 12 * sv, 1, evt.fvelocity(), false, vm.retrig_);
      }
    }
  }

  // UNISON //
  template<typename V, int N>
  VoiceManager<V, N>::UnisonAllocator::UnisonAllocator(VoiceManager& vm_in) : VoiceAllocatorBase(vm_in)
  {
    for (int i = 0; i < N; ++i) {
      auto& voice = this->vm.voices_[i];
      voice.volume(this->vm.normal_volume / (float) num_voices_used);
    }
  }

  template<typename V, int N>
  void VoiceManager<V, N>::UnisonAllocator::set_detune(float detune) noexcept
  {
    auto& vm = this->vm;
    vm.detune_values.clear();
    vm.detune_values.push_back(1);
    for (int i = 1; i < 3; i++) {
      vm.detune_values.push_back(1 + detune * 0.015f * i);
      vm.detune_values.push_back(1.f / (1.f + detune * 0.015f * (float) i));
    }
    for (auto&& [v, d] : util::zip(vm.voices(), vm.detune_values)) v.glide_ = midi::note_freq(v.midi_note_) * d;
  }

  template<typename V, int N>
  void VoiceManager<V, N>::UnisonAllocator::handle_midi_on(const midi::NoteOnEvent& evt) noexcept
  {
    auto& vm = this->vm;
    auto key = evt.key;
    this->stop_voice(key);
    if (vm.note_stack.size() > 0) {
      for (int i = 0; i < num_voices_used; i++) {
        // Find the correct voice to steal
        // Every iteration in the loop, a new entry is added to the notestack.
        auto& note = *(vm.note_stack.end() - num_voices_used);
        // DLOGI("Stealing voice {} from key {}", (note.voice - vm.voices_.data()), note.note);
        Voice& v = *note.voice;
        // v.release calls on_note_off. Don't do this if legato is engaged.
        if (!vm.legato_) v.release();
        note.voice = nullptr;
        auto res = vm.note_stack.push_back(
          {.key = key, .note = key, .detune = vm.detune_values[i], .velocity = evt.fvelocity(), .voice = &v});
        if (res) v.trigger(key, vm.detune_values[i], evt.fvelocity(), vm.legato_, false);
      }
    } else {
      for (int i = 0; i < num_voices_used; i++) {
        auto vit = vm.free_voices.begin() + i;
        auto& v = **vit;
        auto res = vm.note_stack.push_back(
          {.key = key, .note = key, .detune = vm.detune_values[i], .velocity = evt.fvelocity(), .voice = &v});
        if (res) v.trigger(key, vm.detune_values[i], evt.fvelocity(), false, vm.retrig_);
      }
    }
  }


  // VOICE MANAGER //

  template<typename V, int N>
  template<typename... Args, typename>
  VoiceManager<V, N>::VoiceManager(Args&&... args) noexcept
    : voices_(util::generate_array<voice_count_v>([&](int i) { return Voice{args...}; }))
  {
    for (auto& v : voices_) {
      v.pitch_bend_ = &pitch_bend_;
    }
    set_playmode(PlayMode::poly);
    for (int i = 0; i < voice_count_v; ++i) {
      // auto& voice = voices_[i];
      // envelope_props.attack.on_change().connect(
      //   [&voice](float attack) { voice.env_.attack(8 * attack * attack + 0.02); });
      // envelope_props.decay.on_change().connect([&voice](float decay) { voice.env_.decay(decay + 0.02); });
      // envelope_props.sustain.on_change().connect(
      //   [&voice](float sustain) { voice.env_.sustain(sustain); });
      // envelope_props.release.on_change().connect(
      //   [&voice](float release) { voice.env_.release(4 * release * release + 0.02); });
    }

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
      voice.next();
      voice_sum += voice() * voice.volume();
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
      case 0x40: set_sustain(evt.value > 63);
    }
  }

  template<typename V, int N>
  audio::ProcessData<1> VoiceManager<V, N>::process(audio::ProcessData<0> data) noexcept
  {
    for (auto& event : data.midi) handle_midi(event);
    auto buf = services::AudioManager::current().buffer_pool().allocate_clear();
    for (auto& v : voices()) {
      auto v_out = v.process(data);
      for (auto&& [vf, b] : util::zip(v_out.audio, buf)) {
        b += vf;
      }
      v_out.audio.release();
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
  auto VoiceManager<V, N>::voices() noexcept -> std::array<Voice, voice_count_v>&
  {
    return voices_;
  }

  template<typename V, int N>
  auto VoiceManager<V, N>::last_triggered_voice() noexcept -> Voice&
  {
    if (note_stack.empty()) return voices_[0];
    auto v = note_stack.back().voice;
    if (v == nullptr) return voices_[0];
    return *v;
  }

  template<typename V, int N>
  void VoiceManager<V, N>::action(itc::prop_tag_change<play_mode_tag, PlayMode> a, PlayMode pm) noexcept
  {
    set_playmode(pm);
    fwd_action_to_voices(a, pm);
  }

  template<typename V, int N>
  void VoiceManager<V, N>::set_playmode(PlayMode pm) noexcept
  {
    switch (pm) {
      case PlayMode::poly: voice_allocator.template emplace<PolyAllocator>(*this); break;
      case PlayMode::mono: voice_allocator.template emplace<MonoAllocator>(*this); break;
      case PlayMode::unison: voice_allocator.template emplace<UnisonAllocator>(*this); break;
      case PlayMode::interval: voice_allocator.template emplace<IntervalAllocator>(*this); break;
    }
    nano::for_each(voices(), &Voice::release);
    note_stack.clear();
    free_voices.clear();
    for (auto&& voice : voices()) {
      free_voices.push_back(&voice);
    }
  }

  template<typename V, int N>
  void VoiceManager<V, N>::set_sustain(bool s) noexcept
  {
    sustain_ = s;
    if (!s) {
      auto copy = note_stack;
      for (auto&& nvp : copy) {
        if (nvp.should_release) {
          voice_allocator->stop_voice(nvp.note);
          // DLOGI("Released note {}", nvp.note);
        }
      }
    }
  }

  template<typename V, int N>
  void VoiceManager<V, N>::action(legato_tag::action a, bool l) noexcept
  {
    legato_ = l;
    fwd_action_to_voices(a, l);
  }
  template<typename V, int N>
  void VoiceManager<V, N>::action(retrig_tag::action a, bool r) noexcept
  {
    retrig_ = r;
    fwd_action_to_voices(a, r);
  }

  template<typename V, int N>
  void VoiceManager<V, N>::action(rand_tag::action a, float rand) noexcept
  {
    util::partial_match(voice_allocator, [&](PolyAllocator& a) { a.set_rand(rand); });
    fwd_action_to_voices(a, rand);
  }
  template<typename V, int N>
  void VoiceManager<V, N>::action(sub_tag::action a, float sub) noexcept
  {
    util::partial_match(voice_allocator, [&](MonoAllocator& a) { a.set_sub(sub); });
    fwd_action_to_voices(a, sub);
  }
  template<typename V, int N>
  void VoiceManager<V, N>::action(detune_tag::action a, float detune) noexcept
  {
    util::partial_match(voice_allocator, [&](UnisonAllocator& a) { a.set_detune(detune); });
    fwd_action_to_voices(a, detune);
  }
  template<typename V, int N>
  void VoiceManager<V, N>::action(interval_tag::action a, int interval) noexcept
  {
    util::partial_match(voice_allocator, [&](IntervalAllocator& a) { a.set_interval(interval); });
    fwd_action_to_voices(a, interval);
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
