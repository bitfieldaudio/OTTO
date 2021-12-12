#pragma once

#include <array>

#include "lib/util/algorithm.hpp"
#include "lib/util/local_vector.hpp"
#include "lib/util/ranges.hpp"
#include "lib/util/variant_w_base.hpp"
#include "lib/util/with_limits.hpp"

#include "lib/dsp/SegExpBypass.hpp"
#include "lib/engine.hpp"
#include "lib/graphics.hpp"
#include "lib/midi.hpp"
#include "lib/voices/voice_state.hpp"

#include "app/services/audio.hpp"

namespace otto::voices {

  template<AVoice Voice, int N>
  struct VoiceAllocatorBase {
    // Voice volumes are set in individual constructors
    VoiceAllocatorBase(VoiceManager<Voice, N>&) noexcept;
    ~VoiceAllocatorBase() noexcept = default;

    [[nodiscard]] virtual PlayMode play_mode() const noexcept = 0;

    virtual void on_state_change(const VoicesState&) noexcept {}
    virtual void handle(const midi::NoteOn&) noexcept = 0;
    /// Midi off is common to all
    void handle(const midi::NoteOff&) noexcept;

    Voice& get_voice(int key, int note) noexcept;
    void stop_voice(int key) noexcept;

    /// The owning voice manager
    VoiceManager<Voice, N>& vmgr;
  };

  template<PlayMode PM, AVoice Voice, int N>
  struct VoiceAllocator;

  /// CRTP Base class for voices
  template<typename Voice>
  struct VoiceBase : midi::MidiHandler {
    VoiceBase()
    {
      glide_.finish();
    }

    [[nodiscard]] bool is_triggered() const noexcept
    {
      return triggered_;
    }

    [[nodiscard]] std::uint8_t midi_note() const noexcept
    {
      return midi_note_;
    }

    [[nodiscard]] float frequency() const noexcept
    {
      return frequency_;
    }

    [[nodiscard]] float volume() const noexcept
    {
      return volume_;
    }

    void on_note_on() noexcept {}
    void on_note_off() noexcept {}

    /// Calculate the next glide points, envelope etc..
    ///
    /// @note Must be called before calling operator(). VoiceManager::operator() and ::process do this.
    void calc_next() noexcept
    {
      frequency_ = glide_(); /* TODO: * pitch_bend_ */
    }

  private:
    template<AVoice V, std::size_t N>
    friend struct VoiceManager;
    template<AVoice V, int M>
    friend struct VoiceAllocatorBase;
    template<PlayMode PM, AVoice V, int M>
    friend struct VoiceAllocator;

    /// Triggers a new note.
    ///
    /// @param midi_note base frequency.
    /// @param detune is multiplied on frequency
    /// @param legato controls legato on envelope + on_note_on.
    ///        If `true`, `on_note_on` will not be called.
    /// @param jump controls legato for portamento
    ///        If `true`, portamento will not be applied.
    void trigger(int midi_note, float detune, float velocity, bool legato, bool jump) noexcept
    {
      midi_note_ = midi_note;
      triggered_ = true;
      frequency_ = midi::note_freq(midi_note) * detune;
      if (jump || glide_.getEnd() == 1.f) {
        glide_ = frequency_;
        glide_.finish();
      } else {
        glide_ = frequency_;
      }
      velocity_ = velocity;
      if (!legato) static_cast<Voice*>(this)->on_note_on();
    }

    void release() noexcept
    {
      if (is_triggered()) {
        triggered_ = false;
        static_cast<Voice*>(this)->on_note_off();
      }
    }

    /// Set the volume (typically 1 divided by number of voices,
    /// but might be different for sub-octaves or in unison mode)
    void volume(float v) noexcept
    {
      volume_ = v;
    }

    float frequency_ = 1.f;
    float velocity_ = 1.f;
    float level = 1.f;
    float aftertouch_ = 0.f;
    std::int8_t midi_note_ = 1;
    bool triggered_ = false;
    /// Typical value is vm.normal_volume, which is 1/number_of_voices
    float volume_ = 1.f;

    dsp::SegExpBypass<> glide_;
  };

  // Voice allocators - Corresponds to different playmodes //

  template<AVoice Voice, int N>
  struct VoiceAllocator<PlayMode::poly, Voice, N> final : VoiceAllocatorBase<Voice, N> {
    // Random values. 100% random, organic and fresh
    static constexpr std::array rand_max = {
      -0.06f, -0.001f, 0.03f,  0.06f, -0.08f, 0.01f,  0.02f, -0.02f,
      0.f,    0.09f,   -0.06f, 0.05f, -0.03f, -0.08f, 0.01f, -0.09f,
    };

    VoiceAllocator(VoiceManager<Voice, N>& owner);
    void handle(const midi::NoteOn&) noexcept final;

    [[nodiscard]] PlayMode play_mode() const noexcept final
    {
      return PlayMode::poly;
    }

  private:
    std::uint8_t rand_idx_ = 0;

    float next_rand() noexcept
    {
      ++rand_idx_ %= rand_max.size();
      return 1.f + rand_max[rand_idx_] * this->vmgr.state().rand;
    }
  };

  template<AVoice Voice, int N>
  struct VoiceAllocator<PlayMode::duo, Voice, N> final : VoiceAllocatorBase<Voice, N> {
    VoiceAllocator(VoiceManager<Voice, N>& vmgr);
    void handle(const midi::NoteOn&) noexcept final;

    [[nodiscard]] PlayMode play_mode() const noexcept final
    {
      return PlayMode::duo;
    }
  };

  template<AVoice Voice, int N>
  struct VoiceAllocator<PlayMode::mono, Voice, N> final : VoiceAllocatorBase<Voice, N> {
    static constexpr int sub_voice_count_v = 2;
    static constexpr int num_voices_used = 3;

    VoiceAllocator(VoiceManager<Voice, N>& vm_in);
    void handle(const midi::NoteOn&) noexcept final;
    void on_state_change(const VoicesState&) noexcept final;
    [[nodiscard]] PlayMode play_mode() const noexcept final
    {
      return PlayMode::mono;
    }
  };

  template<AVoice Voice, int N>
  struct VoiceAllocator<PlayMode::unison, Voice, N> final : VoiceAllocatorBase<Voice, N> {
    /// Largest odd number less or equal to number of voices
    constexpr static int num_voices_used = N - (N + 1) % 2;
    VoiceAllocator(VoiceManager<Voice, N>& vm_in);

    void handle(const midi::NoteOn&) noexcept final;
    void on_state_change(const VoicesState&) noexcept final;
    void set_detune(float detune) noexcept;
    [[nodiscard]] PlayMode play_mode() const noexcept final
    {
      return PlayMode::unison;
    }

  private:
    util::local_vector<float, 7> detune_values;
    util::local_vector<float, 7> detune_values_max;
  };

  template<AVoice Voice>
  struct NoteStackEntry {
    /// Which physical key is activating this note
    int key = 0;
    /// Which note this voice is playing.
    int note = 0;
    /// Detune value from note
    float detune = 0;
    /// Velocity
    float velocity = 0;
    /// Reference to voice that is playing this note
    Voice* voice = nullptr;

    /// Whether a physical key is not holding this note down
    ///
    /// When using a sustain pedal, this will be set to false on note off
    bool should_release = false;

    [[nodiscard]] bool has_voice() const noexcept
    {
      return voice != nullptr;
    }
  };

  template<AVoice Voice, std::size_t N>
  struct VoiceManager : midi::MidiHandler, itc::Consumer<VoicesState>, AudioDomain {
    static constexpr std::size_t voice_count_v = N;
    /// Voice range is approximately -1 to 1. This ensures the synth range is
    /// approximately the same.
    static constexpr float normal_volume = 1.f / float(voice_count_v);

    template<typename... Args>
    requires std::is_constructible_v<Voice, Args...> //
    VoiceManager(itc::Context& c, Args&&... args)
      : Consumer(c),
        voices_(util::make_array<Voice, N>(FWD(args)...)),
        free_voices_(util::transform(voices_, util::addressof))
    {}

    void on_state_change(const VoicesState& state) noexcept override
    {
      if (state.play_mode != voice_alloc->play_mode()) {
        switch (state.play_mode) {
          case PlayMode::poly: voice_alloc.template emplace<VoiceAllocator<PlayMode::poly, Voice, N>>(*this); break;
          case PlayMode::mono: voice_alloc.template emplace<VoiceAllocator<PlayMode::mono, Voice, N>>(*this); break;
          case PlayMode::unison: voice_alloc.template emplace<VoiceAllocator<PlayMode::unison, Voice, N>>(*this); break;
          case PlayMode::duo: voice_alloc.template emplace<VoiceAllocator<PlayMode::duo, Voice, N>>(*this); break;
          default: break;
        }
        std::ranges::for_each(voices_, &Voice::release);
        note_stack_.clear();
        free_voices_.clear();
        std::ranges::transform(voices_, std::back_inserter(free_voices_), util::addressof);
      }
      // Portamento
      if (state.portamento != old_portamento) {
        for (auto& v : voices_) {
          v.glide_.period(state.portamento * state.portamento * 4 + 0.001);
        }
        old_portamento = state.portamento;
      }
      voice_alloc->on_state_change(state);
    }

    using midi::MidiHandler::handle;
    void handle(midi::NoteOn e) noexcept override
    {
      voice_alloc->handle(e);
    }

    void handle(midi::NoteOff e) noexcept override
    {
      voice_alloc->handle(e);
    }

    // COLLECTION FUNCTIONS //

    constexpr static std::size_t size()
    {
      return N;
    }

    auto begin() noexcept
    {
      return voices_.begin();
    }

    auto begin() const noexcept
    {
      return voices_.begin();
    }

    auto end() noexcept
    {
      return voices_.end();
    }

    auto end() const noexcept
    {
      return voices_.end();
    }

    Voice& operator[](std::size_t i) noexcept
    {
      return voices_[i];
    }

    const Voice& operator[](std::size_t i) const noexcept
    {
      return voices_[i];
    }

    Voice& last_triggered_voice() noexcept
    {
      return *last_triggered_voice_;
    }

    [[nodiscard]] PlayMode play_mode() const noexcept
    {
      return PlayMode(state().play_mode);
    }

    float operator()(auto&&... args) noexcept // requires util::callable<Voice, float(decltype(args)...)>
    {
      float res = 0;
      for (Voice& v : voices_) {
        v.calc_next();
        res += v(args...) * v.volume();
      }
      return res;
    }

  private:
    template<AVoice V, int M>
    friend struct VoiceAllocatorBase;
    template<PlayMode PM, AVoice V, int M>
    friend struct VoiceAllocator;

    /// The actual voices
    std::array<Voice, N> voices_;
    /// Contains the currently untriggered voices
    util::local_vector<Voice*, size()> free_voices_;
    /// Contains informatins about the currently held keys/playing voices.
    /// One key pushes more than one entry in other playmodes than poly
    util::local_vector<NoteStackEntry<Voice>, 12 * N> note_stack_;

    util::variant_w_base<VoiceAllocatorBase<Voice, N>,
                         VoiceAllocator<PlayMode::poly, Voice, N>,
                         VoiceAllocator<PlayMode::mono, Voice, N>,
                         VoiceAllocator<PlayMode::unison, Voice, N>,
                         VoiceAllocator<PlayMode::duo, Voice, N>>
      voice_alloc = {std::in_place_index_t<0>(), *this};

    Voice* last_triggered_voice_ = &voices_[0];
    float old_portamento = 0;
  };

  std::unique_ptr<ILogic> make_voices_logic(itc::Context&);
  ScreenWithHandler make_voices_screen(itc::Context&);

} // namespace otto::voices

namespace otto::voices {

  // VOICE ALLOCATORS //
  // INTERFACE //
  template<AVoice Voice, int N>
  VoiceAllocatorBase<Voice, N>::VoiceAllocatorBase(VoiceManager<Voice, N>& owner) noexcept : vmgr(owner)
  {}

  template<AVoice Voice, int N>
  void VoiceAllocatorBase<Voice, N>::handle(const midi::NoteOff& evt) noexcept
  {
    auto note = evt.note;
    // TODO:
    // if (vm.sustain_) {
    //  // TODO: Make sure ALL entries with this key are set to release, not just the first.
    //  auto found = nano::find_if(vm.note_stack_, [&](auto& nvp) { return nvp.key == key; });
    //  if (found != vm.note_stack_.end()) {
    //    found->should_release = true;
    //  }
    //} else {
    stop_voice(note);
    //}
  }

  template<AVoice Voice, int N>
  auto VoiceAllocatorBase<Voice, N>::get_voice(int key, int note) noexcept -> Voice&
  {
    if (vmgr.free_voices_.size() > 0) {
      // Usual behaviour is to return the next free voice
      auto fvit = vmgr.free_voices_.begin();
      // Finds the voice that last played the note if it exists
      auto it = std::ranges::find_if(vmgr.voices_, [note](Voice& vp) { return vp.midi_note_ == note; });
      // If there is/was a voice that is playing this note
      if (it != vmgr.voices_.end()) {
        // It's not currently playing; choose this voice
        if (!it->is_triggered()) fvit = std::ranges::find(vmgr.free_voices_, it);
        // Otherwise, do nothing - That would mean the voice is playing, and we should not steal it.
      }
      auto& v = **fvit;
      vmgr.free_voices_.erase(fvit);
      vmgr.last_triggered_voice_ = &v;
      return v;
    }
    // Steal oldest playing note
    auto found = std::ranges::find_if(vmgr.note_stack_, [](NoteStackEntry<Voice>& nse) { return nse.has_voice(); });
    if (found != vmgr.note_stack_.end()) {
      // DLOGI("Stealing voice {} from key {}", (found->voice - vmgr.voices_.data()), found->note);
      Voice& v = *found->voice;
      v.release();
      found->voice = nullptr;
      vmgr.last_triggered_voice_ = &v;
      return v;
    }
    // DLOGI("No voice found. Using voice 0");
    vmgr.last_triggered_voice_ = &vmgr.voices_[0];
    return vmgr.voices_[0];
  }

  template<AVoice Voice, int N>
  void VoiceAllocatorBase<Voice, N>::stop_voice(int key) noexcept
  {
    auto free_voice = [this](Voice& v) {
      auto found =
        std::find_if(vmgr.note_stack_.rbegin(), vmgr.note_stack_.rend(), [](auto&& nse) { return !nse.has_voice(); });
      if (found != vmgr.note_stack_.rend()) {
        found->voice = &v;
        v.trigger(found->note, found->detune, found->velocity, vmgr.state().legato, false);
      } else {
        v.release();
        vmgr.free_voices_.push_back(&v);
      }
    };

    // Remove-erase in reverse since for all other modes than poly, the note_stack_ has the format
    // [A1 A2 A3 B1 B2 B3 C1 C2 C3] for instance, where A, B, C are different held keys.
    // If only the C's have voices, when we lift that key, we want the voices to go to the B's
    // while the number is kept the same (e.g. C2 -> B2)
    auto reverse_note_stack_ = util::reverse(vmgr.note_stack_);

    for (auto&& nse : util::filter(reverse_note_stack_, [&](auto&& nse) { return nse.key == key; })) {
      if (nse.has_voice()) {
        free_voice(*nse.voice);
      }
      vmgr.note_stack_.erase(&nse);
    }
  }

  // PLAYMODE ALLOCATORS //
  // POLY and DUO are dynamically allocated (polyphonic),
  // while MONO and UNISON are statically allocated (monophonic)

  // POLY //
  template<AVoice Voice, int N>
  VoiceAllocator<PlayMode::poly, Voice, N>::VoiceAllocator(VoiceManager<Voice, N>& owner)
    : VoiceAllocatorBase<Voice, N>(owner)
  {
    for (auto& voice : this->vmgr) {
      voice.volume(this->vmgr.normal_volume);
    }
  };

  template<AVoice Voice, int N>
  void VoiceAllocator<PlayMode::poly, Voice, N>::handle(const midi::NoteOn& evt) noexcept
  {
    auto& vmgr = this->vmgr;
    auto note = evt.note;
    this->stop_voice(note);
    Voice& voice = this->get_voice(note, note);
    auto res =
      vmgr.note_stack_.push_back({.key = note, .note = note, .detune = 1, .velocity = evt.velocity, .voice = &voice});
    if (res) voice.trigger(note, next_rand(), evt.velocity, false, false);
  }

  // DUO //
  template<AVoice Voice, int N>
  VoiceAllocator<PlayMode::duo, Voice, N>::VoiceAllocator(VoiceManager<Voice, N>& vmgr)
    : VoiceAllocatorBase<Voice, N>(vmgr)
  {
    for (auto& voice : this->vmgr) {
      voice.volume(this->vmgr.normal_volume);
    }
  }

  template<AVoice Voice, int N>
  void VoiceAllocator<PlayMode::duo, Voice, N>::handle(const midi::NoteOn& evt) noexcept
  {
    auto& vmgr = this->vmgr;
    auto note = evt.note;
    auto interval = this->vmgr.state().interval;

    this->stop_voice(note);
    for (int i = 0; i < 2; ++i) {
      Voice& voice = this->get_voice(note, note + interval * i);
      auto res = vmgr.note_stack_.push_back(
        {.key = note, .note = note + interval * i, .detune = 1, .velocity = evt.velocity, .voice = &voice});
      if (res) voice.trigger(note + interval * i, 1, evt.velocity, false, false);
    }
  }

  // MONO //
  template<AVoice Voice, int N>
  VoiceAllocator<PlayMode::mono, Voice, N>::VoiceAllocator(VoiceManager<Voice, N>& vm_in)
    : VoiceAllocatorBase<Voice, N>(vm_in)
  {
    // Set all normal voices
    for (auto& voice : this->vmgr) {
      voice.volume(this->vmgr.normal_volume);
    }
    // Note that after allocation, a prop_change of sub property
    // should be sent, to change sub voice volume
  }

  template<AVoice Voice, int N>
  void VoiceAllocator<PlayMode::mono, Voice, N>::on_state_change(const VoicesState& diff) noexcept
  {
    // The second and third voice are sub voices on mono mode. This sets their volume.
    for (int i = 1; i < N; i++) {
      this->vmgr[i].volume(this->vmgr.normal_volume * diff.sub / (float) i);
    }
  }

  template<AVoice Voice, int N>
  void VoiceAllocator<PlayMode::mono, Voice, N>::handle(const midi::NoteOn& evt) noexcept
  {
    VoiceManager<Voice, N>& vmgr = this->vmgr;
    auto key = evt.note;
    this->stop_voice(key);
    /// If there is already a note playing that we must steal
    if (vmgr.note_stack_.size() > 0) {
      for (int i = 0; i < num_voices_used; ++i) {
        int sv = static_cast<int>(i > 0); // Are we dispatching a subvoice?
        // Find the correct voice to steal
        // Every iteration in the loop, a new entry is added to the notestack.
        auto& note = *(vmgr.note_stack_.end() - num_voices_used);
        // DLOGI("Stealing voice {} from key {}", (note.voice - vmgr.voices_.data()), note.note);
        Voice& v = *note.voice;
        // v.release calls on_note_off. Don't do this if legato is engaged.
        if (!vmgr.state().legato) v.release();
        note.voice = nullptr;
        auto res = vmgr.note_stack_.push_back(
          {.key = key, .note = key - 12 * sv, .detune = 1, .velocity = evt.velocity, .voice = &v});
        if (res) v.trigger(key - 12 * sv, 1, evt.velocity, vmgr.state().legato, false);
      }
    } else {
      for (int i = 0; i < num_voices_used; ++i) {
        int sv = static_cast<int>(i > 0); // Are we dispatching a subvoice?
        auto fvit = vmgr.free_voices_.begin() + i;
        auto& v = **fvit;
        auto res = vmgr.note_stack_.push_back(
          {.key = key, .note = key - 12 * sv, .detune = 1, .velocity = evt.velocity, .voice = &v});
        if (res) v.trigger(key - 12 * sv, 1, evt.velocity, false, vmgr.state().retrig);
      }
    }
  }


  // UNISON //
  template<AVoice Voice, int N>
  VoiceAllocator<PlayMode::unison, Voice, N>::VoiceAllocator(VoiceManager<Voice, N>& vm_in)
    : VoiceAllocatorBase<Voice, N>(vm_in)
  {
    const float detune_strength = 0.15f;
    detune_values_max.clear();
    detune_values_max.push_back(1);
    for (int i = 1; i < 3; i++) {
      detune_values_max.push_back(1 + detune_strength * static_cast<float>(i));
      detune_values_max.push_back(1.f / (1.f + detune_strength * static_cast<float>(i)));
    }
    for (int i = 0; i < 7; i++) {
      detune_values.push_back(1);
    }
    for (int i = 0; i < N; ++i) {
      auto& voice = this->vmgr.voices_[i];
      voice.volume(this->vmgr.normal_volume);
    }
    set_detune(0.f);
  }

  template<AVoice Voice, int N>
  void VoiceAllocator<PlayMode::unison, Voice, N>::on_state_change(const VoicesState& diff) noexcept
  {
    set_detune(diff.detune);
  }

  template<AVoice Voice, int N>
  void VoiceAllocator<PlayMode::unison, Voice, N>::set_detune(float detune) noexcept
  {
    auto& vmgr = this->vmgr;
    for (auto&& [d, m] : util::zip(detune_values, detune_values_max)) d = 1 * (1 - detune) + detune * m;
    for (auto&& [v, d] : util::zip(vmgr.voices_, detune_values)) v.glide_ = midi::note_freq(v.midi_note_) * d;
  }

  template<AVoice Voice, int N>
  void VoiceAllocator<PlayMode::unison, Voice, N>::handle(const midi::NoteOn& evt) noexcept
  {
    auto& vmgr = this->vmgr;
    auto key = evt.note;
    this->stop_voice(key);
    if (vmgr.note_stack_.size() > 0) {
      for (int i = 0; i < num_voices_used; i++) {
        // Find the correct voice to steal
        // Every iteration in the loop, a new entry is added to the notestack.
        auto& note = *(vmgr.note_stack_.end() - num_voices_used);
        // DLOGI("Stealing voice {} from key {}", (note.voice - vmgr.voices_.data()), note.note);
        Voice& v = *note.voice;
        // v.release calls on_note_off. Don't do this if legato is engaged.
        if (!vmgr.state().legato) v.release();
        note.voice = nullptr;
        auto res = vmgr.note_stack_.push_back(
          {.key = key, .note = key, .detune = detune_values[i], .velocity = evt.velocity, .voice = &v});
        if (res) v.trigger(key, detune_values[i], evt.velocity, vmgr.state().legato, false);
      }
    } else {
      for (int i = 0; i < num_voices_used; i++) {
        auto vit = vmgr.free_voices_.begin() + i;
        auto& v = **vit;
        auto res = vmgr.note_stack_.push_back(
          {.key = key, .note = key, .detune = detune_values[i], .velocity = evt.velocity, .voice = &v});
        if (res) v.trigger(key, detune_values[i], evt.velocity, false, vmgr.state().retrig);
      }
    }
  }

} // namespace otto::voices
