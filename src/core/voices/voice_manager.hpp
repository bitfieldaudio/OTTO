#pragma once

#include <deque>
#include <type_traits>
#include <vector>

#include <Gamma/Envelope.h>
#include "util/dsp/ADSR_lite.hpp"
#include "util/dsp/SegExpBypass.hpp"

#include "core/props/props.hpp"
#include "core/ui/screen.hpp"

#include "core/audio/processor.hpp"

#include "util/crtp.hpp"
#include "util/algorithm.hpp"

namespace otto::core::voices {

  template<typename PostT, int NumberOfVoices>
  struct VoiceManager;

  template<typename DerivedT, typename PropsT>
  struct PreBase : util::crtp<DerivedT, PreBase<DerivedT, PropsT>> {
    using Props = PropsT;

    void operator()() noexcept {};

    /// Constructor
    PreBase(Props& p) noexcept;

    /// The engine properties.
    Props& props;
  };

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
  template<typename DerivedT, typename PreT>
  struct VoiceBase : util::crtp<DerivedT, VoiceBase<DerivedT, PreT>> {
    using Pre = PreT;

    static_assert(std::is_base_of_v<PreBase<Pre, typename Pre::PreBase::Props>, Pre>,
                  "VoiceBase<Derived, Pre>: Pre must inherit from PreBase<Pre, Props>");
    static_assert(util::is_invocable_r_v<void, Pre>, "Pre must have a `void operator()()` defined");

    using Props = typename Pre::PreBase::Props;

    VoiceBase(Pre& p) noexcept;
    VoiceBase(const VoiceBase&) = delete;

    /// Implement a handler for note on events
    virtual void on_note_on() noexcept;

    /// Implement a handler for note off events
    virtual void on_note_off() noexcept;

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

    Pre& pre;
    Props& props;

  private:
    template<typename T, int N>
    friend struct VoiceManager;

    void trigger(int midi_note, float mult, float velocity) noexcept;
    void release() noexcept;

    float frequency_ = 440.f;
    float velocity_ = 1.f;
    float level = 1.f;
    float aftertouch_ = 0.f;
    int midi_note_ = 0;

    //HERE IS THE ERROR. At this point, the voice doesn't know it has a call operator
    ADSR_lite<> env_{(*this)()};
    gam::SegExp<> glide_{0.f};
  };

  template<typename DerivedT, typename VoiceT>
  struct PostBase : util::crtp<DerivedT, PostBase<DerivedT, VoiceT>> {
    using Voice = VoiceT;
    static_assert(std::is_base_of_v<VoiceBase<Voice, typename Voice::VoiceBase::Pre>, Voice>,
                  "PostBase<Derived, Voice>: Voice must inherit from VoiceBase<Voice, Pre>");

    static_assert(util::is_invocable_r_v<float, Voice>,
                  "Voice must have a `float operator()()` defined");


    using Pre = typename Voice::VoiceBase::Pre;
    using Props = typename Voice::VoiceBase::Props;

    float operator()(float f) noexcept { return f; }

    /// Constructor
    PostBase(Pre& p) noexcept;

    Pre& pre;
    Props& props;
  };

  namespace details {
    /// The way the voicemanager handles voices
    enum struct PlayMode : char {
      /// Multiple voices at once, each playing a note
      poly,
      /// Only a single voice in use, always playing the latest note
      mono,
      /// All voices in use, all playing the latest note (possibly with detune)
      unison,
      /// Plays a given interval
      interval,
    };

    /// Convert a playmode to string
    ///
    /// @return an all-lowercase string corresponding to the enum name
    std::string to_string(PlayMode) noexcept;
    /// Returns the name of the corresponding extra setting
    std::string aux_setting(PlayMode pm) noexcept;

    struct EnvelopeProps {
      props::Property<float> attack = {0, props::limits(0, 1), props::step_size(0.02)};
      props::Property<float> decay = {0, props::limits(0, 1), props::step_size(0.02)};
      props::Property<float> sustain = {1, props::limits(0, 1), props::step_size(0.02)};
      props::Property<float> release = {0.2, props::limits(0, 1), props::step_size(0.02)};

      DECL_REFLECTION(EnvelopeProps, attack, decay, sustain, release);
    };

    struct SettingsProps {
      props::Property<PlayMode, props::wrap> play_mode = {
        PlayMode::poly, props::limits(PlayMode::poly, PlayMode::interval)};
      props::Property<float> drift = {0, props::limits(0, 1), props::step_size(0.01)};
      props::Property<float> sub = {0, props::limits(0, 1), props::step_size(0.01)};
      props::Property<float> detune = {0, props::limits(0, 1), props::step_size(0.01)};
      props::Property<int> interval = {0, props::limits(-12, 12)};

      props::Property<float> portamento = {0, props::limits(0, 1),
                                                             props::step_size(0.01)};

      props::Property<bool> legato = {false};
      props::Property<bool> retrig = {false};

      props::Property<int, props::no_signal> octave = {0, props::limits(-2, 7)};
      props::Property<int, props::no_signal> transpose = {0, props::limits(-12, 12)};

      DECL_REFLECTION(SettingsProps, play_mode, drift, sub, detune, interval,
              portamento, legato, retrig, octave, transpose);
    };

    std::unique_ptr<ui::Screen> make_envelope_screen(EnvelopeProps& props);
    std::unique_ptr<ui::Screen> make_settings_screen(SettingsProps& props);

  } // namespace details

  // -- VOICE MANAGER INTERFACE -- //

  struct IVoiceManager {
    using PlayMode = details::PlayMode;
    using EnvelopeProps = details::EnvelopeProps;
    using SettingsProps = details::SettingsProps;

    virtual ~IVoiceManager() = default;
    virtual int voice_count() noexcept = 0;

    virtual ui::Screen& envelope_screen() noexcept = 0;
    virtual ui::Screen& settings_screen() noexcept = 0;
  };

  // -- VOICE MANAGER -- //

  template<typename PostT, int NumberOfVoices>
  struct VoiceManager : IVoiceManager {
    /// PostProcessor
    using Post = PostT;

    static_assert(std::is_base_of_v<PostBase<Post, typename Post::PostBase::Voice>, Post>,
                  "PostBase<Derived, Post>: Post must inherit from PostBase<Post, Voice>");
    static_assert(util::is_invocable_r_v<float, Post, float>,
                  "Post must have a `float operator()(float)` defined");

    using Voice = typename Post::PostBase::Voice;
    using Props = typename Post::PostBase::Props;
    using Pre = typename Post::PostBase::Pre;

    /// The number of voices
    static constexpr int voice_count_v = NumberOfVoices;

    int voice_count() noexcept override
    {
      return NumberOfVoices;
    }

    // Assert requirements met
    static_assert(std::is_base_of_v<VoiceBase<Voice, Pre>, Voice>,
                  "VoiceManager<Voice, N>: Voice must derive from VoiceBase<Voice, Pre>");

    using PlayMode = details::PlayMode;
    using EnvelopeProps = details::EnvelopeProps;
    using SettingsProps = details::SettingsProps;

    /// Constructor
    VoiceManager(Props& props) noexcept;

    ui::Screen& envelope_screen() noexcept override;
    ui::Screen& settings_screen() noexcept override;

    /// Process audio, applying Preprocessing, each voice and then postprocessing
    float operator()() noexcept;

    //Voice& handle_midi_on(const midi::NoteOnEvent&) noexcept;
    //Voice* handle_midi_off(const midi::NoteOffEvent&) noexcept;
    void handle_pitch_bend(const midi::PitchBendEvent&) noexcept;
    void handle_control_change(const midi::ControlChangeEvent&) noexcept;

    /// Process audio, applying Preprocessing, each voice and then postprocessing
    audio::ProcessData<1> process(audio::ProcessData<1> data) noexcept;

    /// Return list of voices
    std::array<Voice, voice_count_v>& voices();

    DECL_REFLECTION(VoiceManager,
                    ("envelope", &VoiceManager::envelope_props),
                    ("voice_settings", &VoiceManager::settings_props));

  private:
    std::vector<float> detune_values;

    struct NoteVoicePair {
      /// Which physical key is activating this note
      int key = 0;
      /// Which note this voice is playing.
      int note = 0;
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
    struct IVoiceAllocator {
      VoiceManager& vm;
      /// Constructor
      IVoiceAllocator(VoiceManager& vm_in);
      /// Deleter. Should flush all playing notes
      virtual ~IVoiceAllocator();
      virtual void handle_midi_on(const midi::NoteOnEvent&) noexcept = 0;
      /// Midi off is common to all
      void handle_midi_off(const midi::NoteOffEvent&) noexcept;

      Voice& get_voice(int key) noexcept;
      void stop_voice(int key) noexcept;
    };

    struct PolyAllocator : IVoiceAllocator {
        PolyAllocator(VoiceManager& vm_in) : IVoiceAllocator(vm_in) {}
        void handle_midi_on(const midi::NoteOnEvent&) noexcept override;
    };

    struct MonoAllocator : IVoiceAllocator {
        MonoAllocator(VoiceManager& vm_in) : IVoiceAllocator(vm_in) {}
        void handle_midi_on(const midi::NoteOnEvent&) noexcept override;
    };

    struct UnisonAllocator : IVoiceAllocator {
        UnisonAllocator(VoiceManager& vm_in) : IVoiceAllocator(vm_in) {}
        void handle_midi_on(const midi::NoteOnEvent&)noexcept override;

    };

    struct IntervalAllocator : IVoiceAllocator {
        IntervalAllocator(VoiceManager& vm_in) : IVoiceAllocator(vm_in) {}
        void handle_midi_on(const midi::NoteOnEvent&) noexcept override;
    };


    float pitch_bend_ = 1;

    props::Property<bool> sustain_ = {false};

    std::deque<Voice*> free_voices;
    std::vector<NoteVoicePair> note_stack;

    Props& props;
    Pre pre = {props};
    std::array<Voice, voice_count_v> voices_ =
      util::generate_array<voice_count_v>([this](auto) { return Voice{pre}; });
    Post post = {pre};

    EnvelopeProps envelope_props;
    SettingsProps settings_props;

    std::unique_ptr<IVoiceAllocator> voice_allocator;

    std::unique_ptr<ui::Screen> envelope_screen_ = details::make_envelope_screen(envelope_props);
    std::unique_ptr<ui::Screen> settings_screen_ = details::make_settings_screen(settings_props);

  }; // namespace otto::core::voices

} // namespace otto::core::voices

// Implementation
#include "voice_manager.inl"

// kak: other_file=voice_manager.inl
