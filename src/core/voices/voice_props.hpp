#pragma once

#include "core/input.hpp"
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

  template<typename Sender>
  struct EnvelopeProps : core::input::InputHandler {
    template<typename Val, typename Tag, typename... Mixins>
    using Prop = typename Sender::template Prop<Val, Tag, Mixins...>;

    EnvelopeProps(const Sender& sender) : sender(sender){};

    Sender sender;

    Prop<attack_tag, float> attack = {sender, 0, props::limits(0, 1), props::step_size(0.02)};
    Prop<decay_tag, float> decay = {sender, 0, props::limits(0, 1), props::step_size(0.02)};
    Prop<sustain_tag, float> sustain = {sender, 1, props::limits(0, 1), props::step_size(0.02)};
    Prop<release_tag, float> release = {sender, 0.2, props::limits(0, 1), props::step_size(0.02)};

    // TODO: Move to separate input handler
    void encoder(core::input::EncoderEvent evt)
    {
      auto& props = *this;
      using namespace core::input;
      switch (evt.encoder) {
        case Encoder::blue: props.attack.step(evt.steps); break;
        case Encoder::green: props.decay.step(evt.steps); break;
        case Encoder::yellow: props.sustain.step(evt.steps); break;
        case Encoder::red: props.release.step(evt.steps); break;
      }
    }

    DECL_REFLECTION(EnvelopeProps, attack, decay, sustain, release);
  };

  template<typename Sender>
  struct SettingsProps : core::input::InputHandler, util::OwnsObservers {
    template<typename Val, typename Tag, typename... Mixins>
    using Prop = typename Sender::template Prop<Val, Tag, Mixins...>;

    SettingsProps(const Sender& sender) : sender(sender)
    {
      play_mode.observe_no_imidiate_call(this, [this] {
        rand.send_actions();
        sub.send_actions();
        detune.send_actions();
        interval.send_actions();
      });
    }

    Sender sender;

    Prop<play_mode_tag, PlayMode, props::wrap> play_mode = {sender, PlayMode::poly};
    Prop<rand_tag, float> rand = {sender, 0, props::limits(0, 1), props::step_size(0.01)};
    Prop<sub_tag, float> sub = {sender, 0, props::limits(0.01, 1), props::step_size(0.01)};
    Prop<detune_tag, float> detune = {sender, 0, props::limits(0, 1), props::step_size(0.01)};
    Prop<interval_tag, int> interval = {sender, 0, props::limits(-12, 12)};

    Prop<portamento_tag, float> portamento = {sender, 0, props::limits(0, 1), props::step_size(0.01)};
    Prop<legato_tag, bool> legato = {sender, false};
    Prop<retrig_tag, bool> retrig = {sender, false};

    DECL_REFLECTION(SettingsProps, play_mode, rand, sub, detune, interval, portamento, legato, retrig);

    // TODO: Move to some separate InputHandler
    void encoder(core::input::EncoderEvent ev) override
    {
      using namespace input;
      auto& props = *this;
      switch (ev.encoder) {
        case Encoder::blue: props.play_mode.step(ev.steps); break;
        case Encoder::green: {
          switch (props.play_mode.get()) {
            case PlayMode::poly: props.rand.step(ev.steps); break;
            case PlayMode::mono: props.sub.step(ev.steps); break;
            case PlayMode::unison: props.detune.step(ev.steps); break;
            case PlayMode::interval: props.interval.step(util::math::sgn(ev.steps)); break;
          };
          break;
        }
        case Encoder::yellow: props.portamento.step(ev.steps); break;
        case Encoder::red: {
          // Fuck it. I can do binary logic myself.
          if (ev.steps > 0)
            props.legato = props.legato != props.retrig;
          else
            props.legato = props.legato == props.retrig;
          props.retrig = !props.retrig;
          break;
        }
      }
    }
  };


  template<typename Sender>
  struct SynthPropsBase {
    SynthPropsBase(const Sender& sender) : sender(sender) {}

    Sender sender;
    EnvelopeProps<Sender> envelope = {sender};
    SettingsProps<Sender> settings = {sender};

    DECL_REFLECTION(SynthPropsBase, envelope, settings);
  };

} // namespace otto::core::voices
