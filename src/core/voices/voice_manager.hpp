#pragma once

#include <Gamma/Envelope.h>

#include <deque>
#include <type_traits>
#include <vector>

#include "core/audio/processor.hpp"
#include "core/props/props.hpp"
#include "core/ui/screen.hpp"
#include "core2/prop.hpp"
#include "util/algorithm.hpp"
#include "util/crtp.hpp"
#include "util/dsp/ADSR_lite.hpp"
#include "util/dsp/SegExpBypass.hpp"
#include "util/dsp/dsp.hpp"
#include "util/local_vector.hpp"
#include "util/variant_w_base.hpp"

namespace otto::core::voices {

  /// Tag type for the attack property.
  struct attack_tag {};
  /// Tag type for the decay property.
  struct decay_tag {};
  /// Tag type for the sustain property.
  struct sustain_tag {};
  /// Tag type for the release property.
  struct release_tag {};

  /// Tag type for the play_mode property.
  struct play_mode_tag {};
  /// Tag type for the rand property.
  struct rand_tag {};
  /// Tag type for the sub property.
  struct sub_tag {};
  /// Tag type for the detune property.
  struct detune_tag {};
  /// Tag type for the interval property.
  struct interval_tag {};
  /// Tag type for the portamento property.
  struct portamento_tag {};
  /// Tag type for the legato property.
  struct legato_tag {};
  /// Tag type for the retrig property.
  struct retrig_tag {};

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
    /// freq_target is the target frequency. This allows frequency-specific
    /// calculations to be done even when there is portamento.
    void on_note_on(float freq_target) noexcept;

    /// Implement a handler for note off events
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

    /// Get the volume (typically 1, but might be different for sub-octaves)
    float volume() noexcept;

    /// Is this voice currently triggered?
    ///
    /// Not to be confused with whether it should play. It is not triggered in the
    /// release stage
    bool is_triggered() noexcept;

    /// The current envelope value
    float envelope() noexcept;

  private:
    template<typename T, int N>
    friend struct VoiceManager;

    /// Triggers a new voice. midi_note gives base frequency, detune is multiplied on this.
    /// Legato and jump control legato on envelope + on_note_on and portamento, respectively.
    void trigger(int midi_note, float detune, float velocity, bool legato, bool jump) noexcept;

    void release() noexcept;
    void release_no_env() noexcept;

    float frequency_ = 440.f;
    float velocity_ = 1.f;
    float level = 1.f;
    float aftertouch_ = 0.f;
    int midi_note_ = 0;
    bool triggered_ = false;

    gam::ADSR<> env_;
    SegExpBypass<> glide_{0.f};
  };

  /// The way the voicemanager handles voices
  BETTER_ENUM(PlayMode,
              // Needs signed int for props::wrap to work
              std::int8_t,
              /// Multiple voices at once, each playing a note
              poly,
              /// Only a single voice in use, always playing the latest note
              mono,
              /// All voices in use, all playing the latest note (possibly with detune)
              unison,
              /// Plays a given interval
              interval);

  // -- VOICE MANAGER -- //

  template<typename VoiceT, int NumberOfVoices>
  struct VoiceManager {
    using Voice = VoiceT;

    static_assert(std::is_base_of_v<VoiceBase<Voice>, Voice>,
                  "VoiceManager<Voice, N>: Voice must derive from VoiceBase<Voice>");

    /// The number of voices
    static constexpr int voice_count_v = NumberOfVoices;
    static constexpr int sub_voice_count_v = 2;

    /// Constructor
    VoiceManager() noexcept;


    /// Process audio, applying Preprocessing, each voice and then postprocessing
    audio::ProcessData<1> process(audio::ProcessData<1> data) noexcept;

    /// Process audio, applying Preprocessing, each voice and then postprocessing
    float operator()() noexcept;

    void handle_midi(const midi::AnyMidiEvent&) noexcept;
    void handle_pitch_bend(const midi::PitchBendEvent&) noexcept;
    void handle_control_change(const midi::ControlChangeEvent&) noexcept;

    /// Return list of voices
    std::array<Voice, voice_count_v>& voices();

    // -- PROPERTY SETTERS -- //

    void action(core2::prop_tag_change<play_mode_tag, PlayMode>, PlayMode) noexcept;
    void action(core2::prop_tag_change<legato_tag, bool>, bool) noexcept;
    void action(core2::prop_tag_change<retrig_tag, bool>, bool) noexcept;

    // -- GETTERS -- //

    PlayMode play_mode() noexcept;

    // -- PRIVATE FIELDS -- //
  private:

    util::local_vector<float, 7> detune_values;
    util::local_vector<float, voice_count_v> rand_values;
    // Random values. 100% random, organic and fresh. Works for up to 12 voices.
    static inline std::array<float, 12> rand_max = {0.94, 0.999, 1.03, 1.06, 0.92, 1.01,
                                                    1.02, 0.98,  1.0,  1.09, 0.94, 1.05};

    bool legato_ = false;
    bool retrig_ = false;
    int interval_ = 0;
    float sub_ = 0.f;

    struct NoteVoicePair {
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
      PolyAllocator(VoiceManager& vm_in) : VoiceAllocatorBase(vm_in){};
      void handle_midi_on(const midi::NoteOnEvent&) noexcept override;
    };

    struct MonoAllocator final : VoiceAllocatorBase {
      MonoAllocator(VoiceManager& vm_in);
      ~MonoAllocator();
      void handle_midi_on(const midi::NoteOnEvent&) noexcept override;
    };

    struct UnisonAllocator final : VoiceAllocatorBase {
      UnisonAllocator(VoiceManager& vm_in);
      ~UnisonAllocator();
      void handle_midi_on(const midi::NoteOnEvent&) noexcept override;
    };

    struct IntervalAllocator final : VoiceAllocatorBase {
      IntervalAllocator(VoiceManager& vm_in) : VoiceAllocatorBase(vm_in) {}
      void handle_midi_on(const midi::NoteOnEvent&) noexcept override;
    };


    float pitch_bend_ = 1;

    bool sustain_ = false;

    std::deque<Voice*> free_voices;
    std::deque<NoteVoicePair> note_stack;

    std::array<Voice, voice_count_v> voices_ = util::generate_array<voice_count_v>([](auto) { return Voice{}; });

    util::variant_w_base<VoiceAllocatorBase, PolyAllocator, MonoAllocator, UnisonAllocator, IntervalAllocator>
      voice_allocator = {std::in_place_type<PolyAllocator>, *this};

  }; // namespace otto::core::voices

  /// Convert a playmode to string
  ///
  /// @return an all-lowercase string corresponding to the enum name
  std::string to_string(PlayMode) noexcept;
  /// Returns the name of the corresponding extra setting
  std::string aux_setting(PlayMode pm) noexcept;

  template<typename Aqh>
  struct EnvelopeProps {
    template<typename Val, typename Tag, typename... Mixins>
    using Prop = typename Aqh::template Prop<Val, Tag, Mixins...>;

    Aqh* aqh;

    Prop<attack_tag, float> attack = {aqh, 0, props::limits(0, 1), props::step_size(0.02)};
    Prop<decay_tag, float> decay = {aqh, 0, props::limits(0, 1), props::step_size(0.02)};
    Prop<sustain_tag, float> sustain = {aqh, 1, props::limits(0, 1), props::step_size(0.02)};
    Prop<release_tag, float> release = {aqh, 0.2, props::limits(0, 1), props::step_size(0.02)};

    DECL_REFLECTION(EnvelopeProps, attack, decay, sustain, release);
  };

  template<typename Aqh>
  struct SettingsProps {
    template<typename Val, typename Tag, typename... Mixins>
    using Prop = typename Aqh::template Prop<Val, Tag, Mixins...>;

    Aqh* aqh;

    Prop<play_mode_tag, PlayMode, props::wrap> play_mode = {aqh, PlayMode::poly};
    Prop<rand_tag, float> rand = {aqh, 0, props::limits(0, 1), props::step_size(0.01)};
    Prop<sub_tag, float> sub = {aqh, 1, props::limits(0.01, 1), props::step_size(0.01)};
    Prop<detune_tag, float> detune = {aqh, 0, props::limits(0, 1), props::step_size(0.01)};
    Prop<interval_tag, int> interval = {aqh, 0, props::limits(-12, 12)};

    Prop<portamento_tag, float> portamento = {aqh, 0, props::limits(0, 1), props::step_size(0.01)};
    Prop<legato_tag, bool> legato = {aqh, false};
    Prop<retrig_tag, bool> retrig = {aqh, false};

    DECL_REFLECTION(SettingsProps, play_mode, rand, sub, detune, interval, portamento, legato, retrig);
  };

  // std::unique_ptr<ui::Screen> make_envelope_screen(EnvelopeProps& props);
  // std::unique_ptr<ui::Screen> make_settings_screen(SettingsProps& props);

} // namespace otto::core::voices

// Implementation
#include "voice_manager.inl"
