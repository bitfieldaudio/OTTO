#pragma once

#include <cstdlib>
#include <cassert>
#include <functional>
#include <limits>
#include <map>
#include <memory>
#include <string>
#include <type_traits>
#include <vector>

#include <plog/Log.h>
#include <json.hpp>

#include "core/audio/processor.hpp"
#include "core/engines/engine-props.hpp"
#include "util/exception.hpp"
#include "util/algorithm.hpp"

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
    const EngineType type;
    const std::string name;
    nlohmann::json data;
  };

  /// Abstract base class for Engines
  ///
  /// Use this when refering to a generic engine
  struct AnyEngine {

    AnyEngine(std::string name, Properties& props);

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
  using AnyEngine::AnyEngine;                                                  \
  EnginePatch make_patch() const override                                      \
  {                                                                            \
    return EnginePatch{Type, name(), to_json()};                               \
  }


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

    using Engine = Engine<ET>;

    template<typename Engine, typename... Args>
    void register_engine(Args&&...);

    /// Access the currently selected engine
    Engine& current() noexcept;
    const Engine& current() const noexcept;

    /// Access the currently selected engine
    Engine& operator*() noexcept;
    const Engine& operator*() const noexcept;

    /// Access the currently selected engine
    Engine const* operator->() const noexcept;
    Engine* operator->() noexcept;

    /// Select engine
    ///
    /// \requires `ptr >= _engines.begin() && ptr < _engines.end()`
    /// \postconditions `current() == *ptr`
    /// \returns `current()`
    Engine& select(Engine* ptr);

    /// Select engine
    ///
    /// \effects `select(&ref)`
    Engine& select(Engine& ref);

    /// Select engine by index
    ///
    /// \effects `select(_engines.begin() + idx)`
    Engine& select(std::size_t idx);

    /// Select engine by name
    ///
    /// \effects Find engine with name `name`, and `select(engine)`
    /// \throws `util::exception` when no matching engine was found
    Engine& select(const std::string& name);

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
    Engine& apply_patch(const EnginePatch& seq);

  private:
    std::vector<std::unique_ptr<Engine>> _engines;
    Engine* _current;
  };

  // EngineRegistry Implementations ///////////////////////////////////////////

  template<EngineType ET>
  template<typename Eg, typename... Args>
  void EngineRegistry<ET>::register_engine(Args&&... args)
  {
    _engines.push_back(std::make_unique<Eg>(std::forward<Args>(args)...));
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
      _current = iter.base();
    } else {
      throw util::exception("Engine '{}' not found", name);
    }
    return _current;
  }

  template<EngineType ET>
  Engine<ET>& EngineRegistry<ET>::select(Engine* ptr)
  {
    assert(ptr >= _engines.begin().base() && ptr < _engines.end().base());
    _current = ptr;
    return *_current;
  }

  template<EngineType ET>
  Engine<ET>& EngineRegistry<ET>::select(Engine& ref)
  {
    return select(&ref);
  }
  
  template<EngineType ET>
  Engine<ET>& EngineRegistry<ET>::select(std::size_t idx)
  {
    return select(_engines.begin().base() + idx);
  }

  template<EngineType ET>
  std::vector<EnginePatch> EngineRegistry<ET>::make_patches() const
  {
    std::vector<EnginePatch> res;
    res.reserve(_engines.size());
    util::transform(_engines, res.begin(),
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
        eptr->name() == patch.name;
      });
    if (iter == _engines.end()) {
      throw exception(ErrorCode::engine_not_found);
    }
    (*iter)->from_json(patch.data);
    return **iter;
  }

}  // namespace otto::engines
