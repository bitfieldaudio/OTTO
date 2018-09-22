#pragma once

#include <memory>
#include <string>
#include <vector>
#include <functional>

#include "util/exception.hpp"
#include "util/algorithm.hpp"
#include "util/jsonfile.hpp"

#include "core/ui/screen.hpp"
#include "core/audio/processor.hpp"
#include "core/props/props.hpp"

namespace otto::core::engines {

  /// Engine type
  ///
  /// Each engine has a type, which signifies the group it belongs to.
  enum struct EngineType {
    /// Synth engines
    synth,
    /// FX engines
    effect,
    /// Sequencer engines
    sequencer,
    /// Twist engines - Not really engines in the same sense
    twist,

    /// Misc engines - used for stuff like the Master screen.
    misc
  };

  /// Abstract base class for Engines
  ///
  /// Use this when refering to a generic engine
  struct AnyEngine {

    AnyEngine(std::string const& name,
      props::properties_base& props,
      std::unique_ptr<ui::Screen> screen);

    AnyEngine() = delete;
    virtual ~AnyEngine() = default;

    /* Events */

    /// Called when this module is enabled
    ///
    /// The samplers use this to load the sample file.
    ///
    /// TODO: Define "enabled"
    /// \effects None
    virtual void on_enable() {}

    /// Called when this module is disabled
    ///
    /// The samplers use this to load the sample file.
    /// 
    /// TODO: Define "disabled"
    /// \effects None
    virtual void on_disable() {}

    /* Accessors */

    /// The name of this module.
    const std::string& name() const noexcept;

    ui::Screen& screen() noexcept;

    const ui::Screen& screen() const noexcept;

    /// The currently selected preset
    ///
    /// \returns `-1` if no preset has been set
    int current_preset() const noexcept;

    /// Set the current preset
    ///
    /// Should only be called from [presets::apply_preset]()
    /// \returns new_val
    int current_preset(int new_val) noexcept;

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
    nlohmann::json to_json() const;

    /// Deserialize the engine
    ///
    /// \effects
    /// If a preset was set, apply it. Then deserialize the properties.
    ///
    /// \see to_json
    ///
    /// \throws same as [presets::apply_preset(AnyEngine&, const std::string&)]
    /// if the json contains a preset name.
    /// [nlohmann::json::exception](), see it for details.
    void from_json(const nlohmann::json& j);

    props::properties_base& props() noexcept;
    props::properties_base const& props() const noexcept;

  private:
    props::properties_base& _props;
    std::string _name;
    std::unique_ptr<ui::Screen> _screen;
    int _current_preset = -1;
  };

  // Engine class /////////////////////////////////////////////////////////////

  /// Define common functions for the `Engine` specializations below
  /// This macro is undefined a few lines down, and is only used to simplify the
  /// generation of this function.
  /// \exclude
#define OTTO_ENGINE_COMMON_CONTENT(Type)                                       \
protected:                                                                     \
  using AnyEngine::AnyEngine;                                                  \
                                                                               \
public:                                                                        \

  // macro end


  /// Engine base class
  ///
  /// When creating a new engine, extend this class, instantiated with the
  /// appropriate [EngineType]()
  template<EngineType ET>
  struct Engine : AnyEngine {
    OTTO_ENGINE_COMMON_CONTENT(ET)
  };

  // Engine specializations ///////////////////////////////////////////////////

  template<>
  struct Engine<EngineType::synth> : AnyEngine {

    OTTO_ENGINE_COMMON_CONTENT(EngineType::synth)

    virtual audio::ProcessData<1> process(audio::ProcessData<1>) = 0;
  };
  using SynthEngine = Engine<EngineType::synth>;

  template<>
  struct Engine<EngineType::effect> : AnyEngine {

    OTTO_ENGINE_COMMON_CONTENT(EngineType::effect)

    virtual audio::ProcessData<2> process(audio::ProcessData<2>) = 0;
  };
  using EffectEngine = Engine<EngineType::effect>;

  template<>
  struct Engine<EngineType::sequencer> : AnyEngine {

    OTTO_ENGINE_COMMON_CONTENT(EngineType::sequencer)

    virtual audio::ProcessData<0> process(audio::ProcessData<0>) = 0;
  };
  using SequencerEngine = Engine<EngineType::sequencer>;

  template<>
  struct Engine<EngineType::twist> : AnyEngine {

    OTTO_ENGINE_COMMON_CONTENT(EngineType::twist)

    virtual audio::ProcessData<0> process(audio::ProcessData<0>) = 0;
  };
  using TwistEngine = Engine<EngineType::twist>;


  #undef OTTO_ENGINE_COMMON_CONTENT

  namespace internal {
    template<EngineType ET>
    struct engine_type_impl {
      static constexpr EngineType value = ET;
    };

    template<EngineType ET>
    engine_type_impl<ET> engine_type_impl_func(const Engine<ET>&);
  } // namespace internal

  /// Type trait to get engine type.
  ///
  /// SFINAE friendly, and will match any type that inherits from [Engine]()
  template<typename E>
  constexpr EngineType engine_type_v =
    decltype(internal::engine_type_impl_func(std::declval<E>()))::value;


  // Engine Registry ///////////////////////////////////////////////////////////

  /// Register an engine.
  ///
  /// \effects Store a function which constructs an `REngine` in a
  /// [std::unique_ptr]() with `args` forwarded.
  template<typename REngine, typename... Args>
  void register_engine(Args&&... args);


  /// Construct all registered engines of type `ET`
  ///
  /// This is mostly useful for [EngineDispatcher<ET>]()
  ///
  /// \effects Call all the stored constructors for type `ET`, and move the
  /// resulting `unique_ptr`s into a vector, which is returned.
  template<EngineType ET>
  std::vector<std::unique_ptr<Engine<ET>>> create_engines();


  // EngineScreen /////////////////////////////////////////////////////////////

  /// A [ui::Screen]() with a reference to the engine it belongs to.
  ///
  /// Screens for engines should inherit from this. They can then access the
  /// engine from the `engine` reference.
  template<typename Engine>
  struct EngineScreen : ui::Screen {

    EngineScreen(Engine* engine)
      : Screen(), engine(*engine)
    {}

    virtual ~EngineScreen() {}

  protected:
    Engine& engine;
  };

  struct EngineWithEnvelope {
    virtual ui::Screen& envelope_screen() = 0;
    virtual ui::Screen& voices_screen() = 0;
  };

} // namespace otto::core::engines



// ////////////////////////////////////////////////////////////////////////////
// Template definitions ///////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////

namespace otto::core::engines {
  // EngineDispatcher Implementations ///////////////////////////////////////////

  /// \exclude
  namespace internal {
    template<EngineType ET>
    inline std::vector<std::function<std::unique_ptr<Engine<ET>>()>> engines {};

    /// Wrapper for capturing parameter packs by forwarding
    template<typename T>
    struct wrapper {

      T value;

      template<typename X, typename = std::enable_if_t<std::is_convertible_v<T, X>>>
      wrapper(X&& x) : value(std::forward<X>(x))
      {}

      T get() const
      {
        return std::move(value);
      }
    };

    template<class T>
    auto make_wrapper(T&& x)
    {
      return wrapper<T>(std::forward<T>(x));
    }
  } // namespace internal

  /// \exclude
  template<typename Eg, typename... Args>
  void register_engine(Args&&... args)
  {
    // trickery to forward capture args
    auto lambda = [] (auto... args) {
        return [=]()
        {
          // This is the actual lambda thats registered
          return std::make_unique<Eg>(args.get()...);
        };
      } (make_wrapper(std::forward<Args>(args))...);
    internal::engines<engine_type_v<Eg>>.push_back(lambda);
  }

  /// \exclude
  template<EngineType ET>
  std::vector<std::unique_ptr<Engine<ET>>> create_engines()
  {
    std::vector<std::unique_ptr<Engine<ET>>> res;
    res.reserve(internal::engines<ET>.size());
    for (auto&& func : internal::engines<ET>) {
      res.emplace_back(func());
    }
    return res;
  }
}
