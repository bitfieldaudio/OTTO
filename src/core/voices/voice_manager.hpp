#pragma once

#include <Gamma/Envelope.h>

#include <deque>
#include <type_traits>
#include <vector>

#include "core/audio/processor.hpp"
#include "core/props/props.hpp"
#include "core/ui/screen.hpp"
#include "itc/prop.hpp"
#include "util/algorithm.hpp"
#include "util/crtp.hpp"
#include "util/dsp/ADSR_lite.hpp"
#include "util/dsp/SegExpBypass.hpp"
#include "util/dsp/dsp.hpp"
#include "util/local_vector.hpp"
#include "util/variant_w_base.hpp"
#include "voice_props.hpp"

namespace otto::core::voices {

  template<typename PostT, int NumberOfVoices>
  struct VoiceManager;

  /// Base class for voices
  ///
  /// To be used CRTP-style, meaning the derived class is passed as the template parameter.
  /// This lets VoiceBase upcast itself to the derived voice, and call its functions.
  ///
  /// ```cpp
  /// struct Voice : VoiceBase<Voice, Props> {
  ///
  /// };
  /// ```
  ///
  /// This base class holds a few functions accessor functions for frequency, velocity, and
  /// aftertouch, along with some other relevant data, including the current envelope value.
  ///
  /// It also lets the user implement handlers for note_on and note_off events, along with
  /// the main process call {@ref operator()}, which processes one sample at a time.
  ///
  /// @tparam Derived the derived voice type
  /// @tparam Props the Props type of the engine.
  template<typename DerivedT>
  struct VoiceBase : util::crtp<DerivedT, VoiceBase<DerivedT>> {
    VoiceBase() noexcept;
    VoiceBase(const VoiceBase&) = delete;

    /// Implement a handler for note on events
    /// Main use for this is resetting the amp envelope
    /// freq_target is the target frequency. This allows frequency-specific
    /// calculations to be done even when there is portamento.
    /// During a note steal, if legato is engaged, this is not called
    void on_note_on(float freq_target) noexcept;

    /// Implement a handler for note off events
    /// Main use is to release the amp envelope.
    void on_note_off() noexcept;

    /// Get the midi note this voice is currently attached to
    int midi_note() noexcept;

    /// Get the current frequency this voice should play
    /// Needs to be applied separately for each sample to handle for example glide.
    float frequency() noexcept;
    /// Change the current frequency
    void frequency(float) noexcept;

    /// Get the velocity value
    float velocity() noexcept;

    /// Get the aftertouch value
    float aftertouch() noexcept;

    /// Get the volume (typically 1, but might be different for sub-octaves) or in unison mode
    float volume() noexcept;

    /// Is this voice currently triggered?
    ///
    /// Not to be confused with whether it should play. It is not triggered in the
    /// release stage
    bool is_triggered() noexcept;

    /// Calculate the next glide points, envelope etc..
    /// 
    /// @note Must be called before calling operator(). VoiceManager::operator() and ::process do this.
    void next() noexcept;

    void action(portamento_tag::action, float p) noexcept;

    /// This should multiply by volume_. If you write you own, remember to do that!
    core::audio::ProcessData<1> process(core::audio::ProcessData<1>) noexcept;

  private:
    template<typename T, int N>
    friend struct VoiceManager;

    /// Triggers a new voice. 
    /// 
    /// @param midi_note base frequency.
    /// @param detune is multiplied on frequency
    /// @param legato controls legato on envelope + on_note_on. 
    ///        If `true`, `on_note_on` will not be called.
    /// @param jump controls legato for portamento
    ///        If `true`, portamento will not be applied.
    void trigger(int midi_note, float detune, float velocity, bool legato, bool jump) noexcept;

    void release() noexcept;

    /// Set the volume (typically 1 divided by number of voices, 
    /// but might be different for sub-octaves or in unison mode)
    void volume(float) noexcept;

    float frequency_ = 1.f;
    float velocity_ = 1.f;
    float level = 1.f;
    float aftertouch_ = 0.f;
    int midi_note_ = 0;
    bool triggered_ = false;
    /// Typical value is vm.normal_volume, which is 1/number_of_voices
    float volume_ = 1.f;
    /// Points to the VoiceManager pitch_bend variable.
    float* pitch_bend_ = nullptr;

    util::dsp::SegExpBypass<> glide_{1.f};

    // Note that the voicemanager does not contain the envelope of the voice by default
  };

  // -- VOICE MANAGER -- //

  template<typename VoiceT, int NumberOfVoices>
  struct VoiceManager {
    using Voice = VoiceT;

    static_assert(std::is_base_of_v<VoiceBase<Voice>, Voice>,
                  "VoiceManager<Voice, N>: Voice must derive from VoiceBase<Voice>");

    /// The number of voices
    static constexpr int voice_count_v = NumberOfVoices;
    static constexpr int sub_voice_count_v = 2;
    /// Voice range is approximately -1 to 1. This ensures the synth range is
    /// approximately the same.
    static constexpr float normal_volume = 1.f/(float)NumberOfVoices;

    /// Constructor
    ///
    /// Any parameters passed to this will be passed to the constructors of the voices
    template<typename... Args, typename = std::enable_if_t<std::is_constructible_v<Voice, Args...>>>
    VoiceManager(Args&&... args) noexcept;


    /// Process audio, applying Preprocessing, each voice and then postprocessing
    audio::ProcessData<1> process(audio::ProcessData<1> data) noexcept;

    /// Process audio, applying Preprocessing, each voice and then postprocessing.
    /// Individual volume of voices are applied here.
    float operator()() noexcept;

    void handle_midi(const midi::AnyMidiEvent&) noexcept;
    void handle_pitch_bend(const midi::PitchBendEvent&) noexcept;
    void handle_control_change(const midi::ControlChangeEvent&) noexcept;

    /// Return list of voices
    std::array<Voice, voice_count_v>& voices() noexcept;

    Voice& last_triggered_voice() noexcept;

    // -- PROPERTY SETTERS -- //

    void action(play_mode_tag::action, PlayMode) noexcept;
    void action(legato_tag::action, bool) noexcept;
    void action(retrig_tag::action, bool) noexcept;
    void action(rand_tag::action, float rand) noexcept;
    void action(sub_tag::action, float sub) noexcept;
    void action(detune_tag::action, float detune) noexcept;
    void action(interval_tag::action, int interval) noexcept;

    /// If avaliable, call the action receivers in the voices for all other actions.
    template<typename Action, typename... Args>
    auto action(Action a, Args&&... args) noexcept -> std::enable_if_t<itc::ActionReceiver::is<Voice, Action>, void>
    {
      fwd_action_to_voices(a, args...);
    }

    // -- GETTERS -- //

    PlayMode play_mode() noexcept;

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

      bool has_voice() const noexcept
      {
        return voice != nullptr;
      }
    };

    /// Voice allocators - Corresponds to different playmodes
    struct VoiceAllocatorBase {
      // Voice volumes are set in individual constructors
      VoiceAllocatorBase(VoiceManager& vm_in) noexcept;
      ~VoiceAllocatorBase() noexcept;

      virtual void handle_midi_on(const midi::NoteOnEvent&) noexcept = 0;
      /// Midi off is common to all
      void handle_midi_off(const midi::NoteOffEvent&) noexcept;

      Voice& get_voice(int key, int note) noexcept;
      void stop_voice(int key) noexcept;

      /// Owner
      VoiceManager& vm;
    };

    struct PolyAllocator final : VoiceAllocatorBase {
      float rand_ = 0;

      PolyAllocator(VoiceManager& vm_in);
      
      void handle_midi_on(const midi::NoteOnEvent&) noexcept override;
      void set_rand(float rand) noexcept;
    };

    struct IntervalAllocator final : VoiceAllocatorBase {
      int interval_ = 0;

      IntervalAllocator(VoiceManager& vm_in);
      void handle_midi_on(const midi::NoteOnEvent&) noexcept override;
      void set_interval(float interval) noexcept;
    };

    struct MonoAllocator final : VoiceAllocatorBase {
      constexpr static int num_voices_used = 3;

      MonoAllocator(VoiceManager& vm_in);
      void handle_midi_on(const midi::NoteOnEvent&) noexcept override;
      void set_sub(float sub) noexcept;
    };

    struct UnisonAllocator final : VoiceAllocatorBase {
      /// Largest odd number less or equal to number of voices
      constexpr static int num_voices_used = voice_count_v - (voice_count_v + 1) % 2;
      float detune_ = 0;

      UnisonAllocator(VoiceManager& vm_in);

      void handle_midi_on(const midi::NoteOnEvent&) noexcept override;
      void set_detune(float detune) noexcept;
    };

    // -- PRIVATE FIELDS -- //
  private:
    template<typename Action, typename... Args>
    void fwd_action_to_voices(Action a, Args&&... args)
    {
      if constexpr (itc::ActionReceiver::is<Voice, Action>) {
        for (auto& v : voices_) {
          v.action(a, args...);
        }
      }
    }

    void set_playmode(PlayMode pm) noexcept;

    void set_sustain(bool s) noexcept;

    util::local_vector<float, 7> detune_values;
    util::local_vector<float, voice_count_v> rand_values;
    // Random values. 100% random, organic and fresh. Works for up to 12 voices.
    static inline std::array<float, 12> rand_max = {0.94, 0.999, 1.03, 1.06, 0.92, 1.01,
                                                    1.02, 0.98,  1.0,  1.09, 0.94, 1.05};

    bool legato_ = false;
    bool retrig_ = false;

    float pitch_bend_ = 1;
    bool sustain_ = false;

    // The actual voices
    std::array<Voice, voice_count_v> voices_;
    // Contains the currently untriggered voices
    util::local_vector<Voice*, voice_count_v> free_voices;
    // Contains informatins about the currently held keys/playing voices.
    // One key pushes more than one entry in other playmodes than poly 
    util::local_vector<NoteStackEntry, 12 * voice_count_v> note_stack;
    

    util::variant_w_base<VoiceAllocatorBase, PolyAllocator, MonoAllocator, UnisonAllocator, IntervalAllocator>
      voice_allocator = {std::in_place_type<PolyAllocator>, *this};

  }; // namespace otto::core::voices

} // namespace otto::core::voices

// Implementation
#include "voice_manager.inl"
