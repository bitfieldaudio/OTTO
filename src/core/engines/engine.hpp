#pragma once

#include <memory>
#include <string>
#include <vector>

#include <plog/Log.h>

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
  /// For applying patches, take a look at [otto::engines::EngineRegistry]()
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
    /// TODO: Define "enabled"
    /// \effects None
    /// \example The samplers use this to load the sample file.
    virtual void on_enable() {}

    /// Called when this module is disabled
    ///
    /// TODO: Define "disabled"
    /// \effects None
    /// \example The samplers use this to unload the sample file.
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


  /// Type trait to get engine type.
  ///
  /// If `E` is an [Engine](), this struct has a member `value` which is the
  /// type of that engine.
  template<typename E>
  struct engine_type {};

  /// \exclude
  template<EngineType ET>
  struct engine_type<Engine<ET>> {
    constexpr static EngineType value = ET;
  };

  /// Shorthand for `engine_type<E>::value`
  template<typename E>
  constexpr EngineType engine_type_v = engine_type<E>::value;


  // EngineRegistry ///////////////////////////////////////////////////////////

  template<EngineType ET>
  struct EngineRegistry {

    enum struct ErrorCode {
      none = 0,
      engine_not_found,
      type_mismatch
    };

    using exception = util::as_exception<ErrorCode>;

    static constexpr const EngineType type = ET;

    /// Create an engine, and add it to the registry
    ///
    /// \effects Construct `REngine` with `args` forwarded, and push this new
    /// object to the back of `_engines`.
    /// \returns a reference to the new object.
    template<typename REngine, typename... Args>
    REngine& register_engine(Args&&... args);

    /// Access the currently selected engine
    Engine<ET>& current() noexcept;
    const Engine<ET>& current() const noexcept;

    /// Access the currently selected engine
    Engine<ET>& operator*() noexcept;
    const Engine<ET>& operator*() const noexcept;

    /// Access the currently selected engine
    Engine<ET> const* operator->() const noexcept;
    Engine<ET>* operator->() noexcept;

    /// Select engine
    ///
    /// \requires `ptr >= _engines.begin() && ptr < _engines.end()`
    /// \effects
    /// If `_current` is not null, `_current->on_disable()`. Then, assign `ptr`
    /// to `_current`, and invoke `ptr->on_enable()`
    /// \postconditions `current() == *ptr`
    /// \returns `current()`
    Engine<ET>& select(Engine<ET>* ptr);

    /// Select engine
    ///
    /// \effects `select(&ref)`
    Engine<ET>& select(Engine<ET>& ref);

    /// Select engine by index
    ///
    /// \effects `select(_engines.begin() + idx)`
    Engine<ET>& select(std::size_t idx);

    /// Select engine by name
    ///
    /// \effects Find engine with name `name`, and `select(engine)`
    /// \throws `util::exception` when no matching engine was found
    Engine<ET>& select(const std::string& name);

    /// Construct patches to get all the engines into the current state.
    ///
    /// \returns A vector of the results of `e.make_patch()` for each engine `e`
    std::vector<EnginePatch> make_patches() const;

    /// Apply an [EnginePatch]() to a matching engine.
    ///
    /// \effects
    /// If `p.type == type`, find an engine ´e´ for which `e.name() == p.name`,
    /// and apply the patch (`e.from_json(p.data)`). 
    ///
    /// \throws
    /// If no matching engine was found, [exception]() is thrown, with the
    /// appropriate error code.
    ///
    /// \returns
    /// A reference to the engine that matched the patch
    Engine<ET>& apply_patch(const EnginePatch& seq);

  private:
    std::vector<std::unique_ptr<Engine<ET>>> _engines;
    Engine<ET>* _current;
  };

  template<EngineType ET>
  void to_json(nlohmann::json& j, const otto::engines::EngineRegistry<ET>& er);

  template<EngineType ET>
  void from_json(const nlohmann::json& j, otto::engines::EngineRegistry<ET>& er);

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
  // EngineRegistry Implementations ///////////////////////////////////////////

  template<EngineType ET>
  template<typename Eg, typename... Args>
  Eg& EngineRegistry<ET>::register_engine(Args&&... args)
  {
    auto uptr = std::make_unique<Eg>(std::forward<Args>(args)...);
    Eg& eg    = *uptr;
    _engines.push_back(std::move(uptr));
    return eg;
  }

  template<EngineType ET>
  Engine<ET>& EngineRegistry<ET>::current() noexcept
  {
    return *_current;
  }

  template<EngineType ET>
  const Engine<ET>& EngineRegistry<ET>::current() const noexcept
  {
    return *_current;
  }

  template<EngineType ET>
  Engine<ET>& EngineRegistry<ET>::operator*() noexcept
  {
    return *_current;
  }

  template<EngineType ET>
  const Engine<ET>& EngineRegistry<ET>::operator*() const noexcept
  {
    return *_current;
  }

  template<EngineType ET>
  Engine<ET>* EngineRegistry<ET>::operator->() noexcept
  {
    return _current;
  }

  template<EngineType ET>
  const Engine<ET>* EngineRegistry<ET>::operator->() const noexcept
  {
    return _current;
  }

  template<EngineType ET>
  Engine<ET>& EngineRegistry<ET>::select(const std::string& name)
  {
    auto iter = util::find_if(_engines,
      [&name] (auto&& eg) {
        return eg.name() == name;
      });
    if (iter != _engines.end()) {
      select(iter.base());
    } else {
      throw util::exception("Engine '{}' not found", name);
    }
    return _current;
  }

  template<EngineType ET>
  Engine<ET>& EngineRegistry<ET>::select(Engine<ET>* ptr)
  {
    if (_current != nullptr) _current->on_disable();
    _current = ptr;
    _current->on_enable();
    return *_current;
  }

  template<EngineType ET>
  Engine<ET>& EngineRegistry<ET>::select(Engine<ET>& ref)
  {
    return select(&ref);
  }
  
  template<EngineType ET>
  Engine<ET>& EngineRegistry<ET>::select(std::size_t idx)
  {
    return select((_engines.begin().base() + idx)->get());
  }

  template<EngineType ET>
  std::vector<EnginePatch> EngineRegistry<ET>::make_patches() const
  {
    std::vector<EnginePatch> res;
    res.reserve(_engines.size());
    util::transform(_engines, std::back_inserter(res),
      [] (auto&& eptr) {
        return eptr->make_patch();
      });
    return res;
  }

  template<EngineType ET>
  Engine<ET>& EngineRegistry<ET>::apply_patch(const EnginePatch& patch)
  {
    if (patch.type != type) {
      throw exception(ErrorCode::type_mismatch);
    }
    auto iter = util::find_if(_engines,
      [&patch] (auto&& eptr) {
        return eptr->name() == patch.name;
      });
    if (iter == _engines.end()) {
      throw exception(ErrorCode::engine_not_found);
    }
    (*iter)->from_json(patch.data);
    return **iter;
  }

  template<EngineType ET>
  void to_json(nlohmann::json& j, const otto::engines::EngineRegistry<ET>& er)
  {
    j = nlohmann::json::object();
    auto v = er.make_patches();
    for (auto&& patch : v) {
      j[patch.name] = patch.data;
    }
  }

  template<EngineType ET>
  void from_json(const nlohmann::json& j, otto::engines::EngineRegistry<ET>& er)
  {
    if (j.is_object()) {
      for (auto iter = j.begin(); iter != j.end(); iter++) {
        er.apply_patch({ET, iter.key(), iter.value()});
      }
    }
  }

} // namespace otto::engines
