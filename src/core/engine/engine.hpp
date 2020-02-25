#pragma once

#include <functional>
#include <memory>
#include <string>
#include <vector>

#include "core/audio/processor.hpp"
#include "core/props/props.hpp"
#include "core/ui/icons.hpp"
#include "core/ui/screen.hpp"
#include "services/audio_manager.hpp"
#include "services/ui_manager.hpp"
#include "util/algorithm.hpp"
#include "util/crtp.hpp"
#include "util/exception.hpp"
#include "util/jsonfile.hpp"
#include "util/serialize.hpp"

namespace otto::core::engine {

  /// Engine type
  ///
  /// Each engine has a type, which signifies the group it belongs to.
  enum struct EngineType {
    /// Synth engines
    synth,
    /// FX engines
    effect,
    /// Sequencer engines
    arpeggiator,
    /// Twist engines - Not really engines in the same sense
    twist,
    /// Misc engines - used for stuff like the Master screen.
    misc
  };

  /// Abstract base class for Engines
  ///
  /// Use this when refering to a generic engine
  struct IEngine : core::input::InputHandler {
    IEngine() noexcept;

    virtual ~IEngine() = default;

    /* Accessors */

    /// The name of this module.
    virtual util::string_ref name() const noexcept = 0;

    /// The currently selected preset
    ///
    /// \returns `-1` if no preset has been set
    int current_preset() const noexcept;

    /// Set the current preset
    ///
    /// Should only be called from [presets::apply_preset]()
    /// \returns new_val
    int current_preset(int new_val) noexcept;

    virtual ui::ScreenAndInput screen() = 0;

    /* Serialization */

    /// Serialize the engine
    ///
    /// ## Format
    ///
    /// ```json
    /// {
    ///   "preset": "<preset_name>",
    ///   "props": "<props.to_json()>"
    /// }
    /// ```
    ///
    /// `"preset"` is omitted if `presets::name_of_idx(current_preset())`
    /// throws an exception.
    /// `<props.to_json()>` is the serialized properties
    ///
    /// \throws [nlohmann::json::exception](), see it for details.
    virtual nlohmann::json to_json() const = 0;

    /// Deserialize the engine
    ///
    /// \effects
    /// If a preset was set, apply it. Then deserialize the properties.
    ///
    /// \see to_json
    ///
    /// \throws same as [presets::apply_preset(IEngine&, const std::string&)]
    /// if the json contains a preset name.
    /// [nlohmann::json::exception](), see it for details.
    virtual void from_json(const nlohmann::json& j) = 0;

  private:
    int _current_preset = -1;
  };

  /// An extended engine interface including the engine type
  template<EngineType ET>
  struct ITypedEngine : IEngine {
    using IEngine::IEngine;
  };

  template<>
  struct ITypedEngine<EngineType::synth> : IEngine {
    using IEngine::IEngine;
    virtual core::ui::ScreenAndInput envelope_screen() = 0;
    virtual core::ui::ScreenAndInput voices_screen() = 0;
  };

  template<>
  struct ITypedEngine<EngineType::effect> : IEngine {
    using IEngine::IEngine;
  };
  template<>
  struct ITypedEngine<EngineType::arpeggiator> : IEngine {
    using IEngine::IEngine;
  };
  template<>
  struct ITypedEngine<EngineType::twist> : IEngine {
    using IEngine::IEngine;
  };

  /// Get the name of an engine.
  ///
  /// Must be defined for every engine.
  ///
  /// Prefer using the alias {@ref name_of_engine_v}
  template<typename Engine>
  struct name_of_engine {
    static constexpr util::string_ref value = Engine::name;
  };

  /// Get the name of an engine.
  ///
  /// Alias of name_of_engine::value
  template<typename Engine>
  constexpr util::string_ref name_of_engine_v = name_of_engine<Engine>::value;

  // Engine class /////////////////////////////////////////////////////////////

  namespace detail {
    template<EngineType ET, typename Derived>
    struct EngineImpl : util::crtp<Derived, EngineImpl<ET, Derived>>, ITypedEngine<ET> {
      util::string_ref name() const noexcept override
      {
        return name_of_engine_v<Derived>;
      }
      nlohmann::json to_json() const final
      {
        return util::serialize(this->derived());
      }
      void from_json(const nlohmann::json& j) final
      {
        util::deserialize(this->derived(), j);
      }

      static constexpr auto reflect_name()
      {
        return name_of_engine_v<Derived>;
      }

      static constexpr auto reflect_members()
      {
        return reflect::members(reflect::member<EngineImpl>(
          "props", [](auto& obj) -> auto& { return obj.derived().props; }));
      }

    protected:
      using ITypedEngine<ET>::ITypedEngine;
      using util::crtp<Derived, EngineImpl<ET, Derived>>::derived;
    };
  } // namespace detail

  /// CRTP Engine base class
  ///
  /// When creating a new engine, extend this class, instantiated with the
  /// appropriate [EngineType]()
  template<EngineType ET, typename Derived>
  struct Engine : detail::EngineImpl<ET, Derived> {
  protected:
    using detail::EngineImpl<ET, Derived>::EngineImpl;
  };

  // Engine specializations ///////////////////////////////////////////////////

  template<typename Derived>
  using SynthEngine = Engine<EngineType::synth, Derived>;

  template<typename Derived>
  using EffectEngine = Engine<EngineType::effect, Derived>;

  template<typename Derived>
  using ArpeggiatorEngine = Engine<EngineType::arpeggiator, Derived>;

  template<typename Derived>
  using TwistEngine = Engine<EngineType::twist, Derived>;

  template<typename Derived>
  using MiscEngine = Engine<EngineType::misc, Derived>;

  namespace detail {
    template<EngineType ET, typename Derived>
    meta::c<ET> engine_type_impl_func(const Engine<ET, Derived>&);
  } // namespace detail

  /// Type trait to get engine type.
  ///
  /// SFINAE friendly, and will match any type that inherits from [Engine]()
  template<typename E>
  constexpr EngineType engine_type_v = meta::_v<decltype(detail::engine_type_impl_func(std::declval<E>()))>;

  // EngineScreen /////////////////////////////////////////////////////////////

  template<typename Audio, typename... Screens>
  struct EngineSender : itc::JoinedActionSender<services::AudioSender<Audio>, services::UISender<Screens...>> {
    EngineSender(Audio& audio, Screens&... screens) noexcept
      : itc::JoinedActionSender<services::AudioSender<Audio>, services::UISender<Screens...>>(audio, {screens...})
    {}
  };
} // namespace otto::core::engine
