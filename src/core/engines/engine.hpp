#pragma once

#include <memory>
#include <string>
#include <vector>
#include <functional>

#include "util/exception.hpp"
#include "util/algorithm.hpp"
#include "util/jsonfile.hpp"

#include "core/ui/widget.hpp"
#include "core/audio/processor.hpp"
#include "core/engines/engine-props.hpp"

namespace otto::engines {

  /// Engine type
  ///
  /// Each engine has a type, which signifies the group it belongs to.
  enum struct EngineType {
    /// Drum engines
    drums,
    /// Synth engines
    synth,
    /// FX engines
    effect,
    /// Sequencer engines
    sequencer,
    /// Modulation engines
    modulation,
    /// Studio engines
    studio,
    /// System engines
    system,
    /// Uncategorized
    other
  };

  /// An engine type and name, along with its json-serialized data.
  ///
  /// For applying patches, take a look at [otto::engines::EngineDispatcher]()
  struct EnginePatch {
    EngineType type;
    std::string name;
    nlohmann::json data;
  };

  /// Abstract base class for Engines
  ///
  /// Use this when refering to a generic engine
  struct AnyEngine {

    AnyEngine(std::string name,
      Properties& props,
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

    /// The module properties.
    Properties& props() noexcept;

    /// The module properties.
    const Properties& props() const noexcept;

    ui::Screen& screen() noexcept;

    const ui::Screen& screen() const noexcept;

    /* Serialization */

    /// Serialize the properties
    virtual nlohmann::json to_json() const;

    /// Deserialize the properties
    virtual void from_json(const nlohmann::json& j);

    /// Construct an [EnginePatch]() with the serialized data.
    ///
    /// This is implemented in the [Engine]() specializations, so you don't have
    /// to worry about it when writing your own engine.
    virtual EnginePatch make_patch() const = 0;

  private:
    const std::string _name;
    Properties& _props;
    std::unique_ptr<ui::Screen> _screen;
  };

  /// Serialization
  ///
  /// This function is detected by nlohmann::json using adl
  /// \effects `j = e.to_json()`
  void to_json(nlohmann::json& j, const AnyEngine& e);

  /// Deserialization
  ///
  /// This function is detected by nlohmann::json using adl
  /// \effects `e.from_json(j)`
  void from_json(const nlohmann::json& j, AnyEngine& e);

  // Engine class /////////////////////////////////////////////////////////////

  /// Define common functions for the `Engine` specializations below
  /// This macro is undefined a few lines down, and is only used to simplify the
  /// generation of this function. Do not try to use it outside this file.
  /// \exclude
#define OTTO_ENGINE_COMMON_CONTENT(Type)                                       \
protected:                                                                     \
  using AnyEngine::AnyEngine;                                                  \
                                                                               \
public:                                                                        \
  EnginePatch make_patch() const override                                      \
  {                                                                            \
    return EnginePatch{Type, name(), to_json()};                               \
  }

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
  struct Engine<EngineType::drums> : AnyEngine {

    OTTO_ENGINE_COMMON_CONTENT(EngineType::drums)

    virtual audio::ProcessData<1> process(audio::ProcessData<0>) = 0;
  };
  using DrumsEngine = Engine<EngineType::drums>;

  template<>
  struct Engine<EngineType::synth> : AnyEngine {

    OTTO_ENGINE_COMMON_CONTENT(EngineType::synth)

    virtual audio::ProcessData<1> process(audio::ProcessData<0>) = 0;
  };
  using SynthEngine = Engine<EngineType::synth>;

  template<>
  struct Engine<EngineType::effect> : AnyEngine {

    OTTO_ENGINE_COMMON_CONTENT(EngineType::effect)

    virtual audio::ProcessData<1> process(audio::ProcessData<1>) = 0;
  };
  using EffectEngine = Engine<EngineType::effect>;

  template<>
  struct Engine<EngineType::sequencer> : AnyEngine {

    OTTO_ENGINE_COMMON_CONTENT(EngineType::sequencer)

    virtual audio::ProcessData<0> process(audio::ProcessData<0>) = 0;
  };
  using SequencerEngine = Engine<EngineType::sequencer>;

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

  // Presets //////////////////////////////////////////////////////////////////

  /// # OTTO Preset format
  ///
  /// OTTO Presets are defined in a json file with the following layout:
  ///
  /// ```json
  /// {
  ///   "OTTO Preset": {
  ///     "Version": 0,
  ///     "Name": "/* Name */"
  ///   },
  ///   "Engines": {
  ///     "/* Type */": {
  ///       "Engine": "/* Engine */",
  ///       "Data": "/* Engine specific data */"
  ///     },
  ///     "/* Type */": {
  ///       "Engine": "/* Engine */",
  ///       "Data": "/* Engine specific data */"
  ///     },
  ///   }
  /// }
  /// ```
  ///
  ///  - `Version` is a file format version number, currently at `0`
  ///  - `Type` is one of the types `"Drums"`, `"Synth"` or `"Effect"`. Each
  ///  - preset can define one engine in each group
  ///  - `Engine` is an engine id string, as if by [AnyEngine::name()]()
  ///  - `Data` is the serialized data for the engine, as if by
  ///    [AnyEngine::to_json()]() 
  ///
  /// At some point it will be possible to embed similar data in a sample file,
  /// but currently you need to supply both a sample file and a preset file
  struct PresetFile : util::JsonFile {
    using util::JsonFile::ErrorCode;
    using util::JsonFile::OpenOptions;
    using util::JsonFile::exception;

    /// Constructor
    ///
    /// \effects delegate to `util::JsonFile(p)`
    /// \postconditions as `util::JsonFile(p)`, and `validate() ==
    /// ErrorCode::none` \remarks remember to `read()` after construction
    explicit PresetFile(const fs::path& p);

    /// Confirm the presence of the header and `Engines` section, as well as the
    /// version number.
    ErrorCode validate() const noexcept override;

    /// Get the name of this preset
    std::string name() const;

    /// Get a json object refering to the `Engines` section.
    nlohmann::json& json_engines();

    /// Get a json object refering to the `Engines` section.
    std::vector<EnginePatch> engines() const;

    /// Get a json object with an engine, defined by its group
    EnginePatch engine(EngineType group);

    /// Get a json object with an engine, defined by its group
    const nlohmann::json& engine(const std::string& group) const;

    /// Get a json object with an engine, defined by its group
    nlohmann::json& operator[](const std::string& group);

    /// Get a json object with an engine, defined by its group
    const nlohmann::json& operator[](const std::string& group) const;
  };

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

} // namespace otto::engines



// ////////////////////////////////////////////////////////////////////////////
// Template definitions ///////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////

namespace otto::engines {
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
