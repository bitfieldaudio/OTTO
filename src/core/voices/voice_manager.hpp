#pragma once

#include <deque>
#include <type_traits>
#include <vector>

#include <Gamma/Envelope.h>

#include "core/props/props.hpp"
#include "core/ui/screen.hpp"

#include "core/audio/processor.hpp"

#include "util/crtp.hpp"

namespace otto::core::voices {

  template<typename PostT, int NumberOfVoices>
  struct VoiceManager;

  template<typename DerivedT, typename PropsT>
  struct PreBase : util::crtp<DerivedT, PreBase<DerivedT, PropsT>> {
    using Props = PropsT;

    static_assert(std::is_base_of_v<props::properties_base, Props>,
                  "PreBase<Derived, Props>: Props must be a Properties<> subclass");

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
    ///
    /// Needs to be applied seperately for each sample to handle for example glide.
    float frequency() noexcept;

    /// Get the velocity value
    float velocity() noexcept;

    /// Get the velocity value
    float aftertouch() noexcept;

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

    void trigger(int midi_note, float velocity) noexcept;
    void release() noexcept;

    float frequency_ = 440.f;
    float velocity_ = 1.f;
    float aftertouch_ = 0.f;
    int midi_note_ = 0;

    gam::ADSR<> env_;
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

    /// Constructor
    PostBase(Pre& p) noexcept;

    Pre& pre;
    Props& props;
  };

  namespace details {
    /// The way the voicemanager handles voices
    enum struct PlayMode {
      /// Multiple voices at once, each playing a note
      poly,
      /// Only a single voice in use, allways playing the latest note
      mono,
      /// All voices in use, all playing the latest note (posibly with detune)
      unison
    };

    /// Convert a playmode to string
    ///
    /// @return an all-lowercase string corresponding to the enum name
    std::string to_string(PlayMode) noexcept;

    struct EnvelopeProps : props::Properties<> {
      props::Property<float> attack = {this, "Attack", 0, props::has_limits::init(0, 1),
                                       props::steppable::init(0.02)};

      props::Property<float> decay = {this, "Decay", 0, props::has_limits::init(0, 1),
                                      props::steppable::init(0.02)};

      props::Property<float> sustain = {this, "Sustain", 1, props::has_limits::init(0, 1),
                                        props::steppable::init(0.02)};

      props::Property<float> release = {this, "Release", 0.2, props::has_limits::init(0, 1),
                                        props::steppable::init(0.02)};

      using Properties::Properties;
      DECL_REFLECTION(EnvelopeProps, attack, decay, sustain, release);
    };

    struct SettingsProps : props::Properties<> {
      props::Property<PlayMode, props::wrap> play_mode = {
        this, "Play Mode", PlayMode::poly,
        props::has_limits::init(PlayMode::poly, PlayMode::unison)};

      props::Property<float> portamento = {this, "Portamento", 0, props::has_limits::init(0, 1),
                                           props::steppable::init(0.01)};

      props::Property<int> octave = {this, "Octave", 0, props::has_limits::init(-2, 7)};

      props::Property<int> transpose = {this, "Transpose", 0, props::has_limits::init(-12, 12)};
      using Properties::Properties;

      DECL_REFLECTION(SettingsProps, play_mode, portamento, octave, transpose);
    };

    std::unique_ptr<ui::Screen> make_envelope_screen(EnvelopeProps& props);
    std::unique_ptr<ui::Screen> make_settings_screen(SettingsProps& props);

  } // namespace details


  // -- VOICE MANAGER -- //

  template<typename PostT, int NumberOfVoices>
  struct VoiceManager {
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
    static constexpr int voice_count = NumberOfVoices;

    // Assert requirements met
    static_assert(std::is_base_of_v<VoiceBase<Voice, Pre>, Voice>,
                  "VoiceManager<Voice, N>: Voice must derive from VoiceBase<Voice, Pre>");

    using PlayMode = details::PlayMode;
    using EnvelopeProps = details::EnvelopeProps;
    using SettingsProps = details::SettingsProps;

    /// Constructor
    VoiceManager(Props& props) noexcept;

    ui::Screen& envelope_screen() noexcept;
    ui::Screen& settings_screen() noexcept;

    /// Process audio, applying Preprocessing, each voice and then postprocessing
    float operator()() noexcept;

    Voice& handle_midi_on(const midi::NoteOnEvent&) noexcept;
    Voice* handle_midi_off(const midi::NoteOffEvent&) noexcept;

    /// Process audio, applying Preprocessing, each voice and then postprocessing
    audio::ProcessData<1> process(audio::ProcessData<1> data) noexcept;

    DECL_REFLECTION(VoiceManager, ("envelope", &VoiceManager::envelope_props), ("voice_settings", &VoiceManager::settings_props));
  private:
    Voice& get_voice(int key) noexcept;
    Voice* stop_voice(int key) noexcept;

    struct NoteVoicePair {
      int note = 0;
      Voice* voice = nullptr;

      bool has_voice() const noexcept
      {
        return voice != nullptr;
      }
    };

    std::deque<Voice*> free_voices;
    std::vector<NoteVoicePair> note_stack;

    Props& props;
    Pre pre = {props};
    std::array<Voice, voice_count> voices_ =
      util::generate_array<voice_count>([this](auto) { return Voice{pre}; });
    Post post = {pre};

    EnvelopeProps envelope_props = {&props, "envelope"};
    SettingsProps settings_props = {&props, "voice_settings"};

    std::unique_ptr<ui::Screen> envelope_screen_ = details::make_envelope_screen(envelope_props);
    std::unique_ptr<ui::Screen> settings_screen_ = details::make_settings_screen(settings_props);
    PlayMode play_mode = PlayMode::mono;

  }; // namespace otto::core::voices

} // namespace otto::core::voices

// Implementation
#include "voice_manager.impl.hpp"

// kak: other_file=voice_manager.impl.hpp
