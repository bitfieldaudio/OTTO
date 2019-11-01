#pragma once

#include "itc/prop.hpp"

namespace otto::core::voices {

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

  /// Tag type for the attack property.
  struct attack_tag {
    using action = itc::Action<attack_tag, float>;
  };
  /// Tag type for the decay property.
  struct decay_tag {
    using action = itc::Action<decay_tag, float>;
  };
  /// Tag type for the sustain property.
  struct sustain_tag {
    using action = itc::Action<sustain_tag, float>;
  };
  /// Tag type for the release property.
  struct release_tag {
    using action = itc::Action<release_tag, float>;
  };

  /// Tag type for the play_mode property.
  struct play_mode_tag {
    using action = itc::Action<play_mode_tag, PlayMode>;
  };
  /// Tag type for the rand property.
  struct rand_tag {
    using action = itc::Action<rand_tag, float>;
  };
  /// Tag type for the sub property.
  struct sub_tag {
    using action = itc::Action<sub_tag, float>;
  };
  /// Tag type for the detune property.
  struct detune_tag {
    using action = itc::Action<detune_tag, float>;
  };
  /// Tag type for the interval property.
  struct interval_tag {
    using action = itc::Action<interval_tag, int>;
  };
  /// Tag type for the portamento property.
  struct portamento_tag {
    using action = itc::Action<portamento_tag, float>;
  };
  /// Tag type for the legato property.
  struct legato_tag {
    using action = itc::Action<legato_tag, bool>;
  };
  /// Tag type for the retrig property.
  struct retrig_tag {
    using action = itc::Action<retrig_tag, bool>;
  };

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

} // namespace otto::core::voices
