#pragma once

#include "core/engines/engine.hpp"


namespace otto::engines {

  // Implementation is in engine_dispatcher.cpp, with explicit instantiations at
  // the bottom.

  template<EngineType ET>
  struct EngineDispatcher {
    enum struct ErrorCode { none = 0, engine_not_found, type_mismatch };

    using exception = util::as_exception<ErrorCode>;

    static constexpr const EngineType type = ET;

    // Initialization

    /// Construct an EngineDispatcher
    ///
    /// \effects None
    EngineDispatcher();

    /// Construct the engines
    ///
    /// Only call this after all engines are registered
    /// \effects construct [_engines]() using [create_engines]()
    void init();

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
    ///
    /// \effects If `_current` is not null, `_current->on_disable()`. Then,
    /// assign `ptr` to `_current`, and invoke `ptr->on_enable()`
    ///
    /// \postconditions `current() == *ptr`
    ///
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
    /// \effects If `p.type == type`, find an engine ´e´ for which `e.name() ==
    /// p.name`, and apply the patch (`e.from_json(p.data)`).
    ///
    /// \throws If no matching engine was found, [exception]() is thrown, with
    /// the appropriate error code.
    ///
    /// \returns A reference to the engine that matched the patch
    Engine<ET>& apply_patch(const EnginePatch& seq);

  private:
    std::vector<std::unique_ptr<Engine<ET>>> _engines;
    Engine<ET>* _current;
  };

  template<EngineType ET>
  void to_json(nlohmann::json& j,
               const otto::engines::EngineDispatcher<ET>& er);

  template<EngineType ET>
  void from_json(const nlohmann::json& j,
                 otto::engines::EngineDispatcher<ET>& er);

  // Serialization implementations

  template<EngineType ET>
  void to_json(nlohmann::json& j, const EngineDispatcher<ET>& er)
  {
    j      = nlohmann::json::object();
    auto v = er.make_patches();
    for (auto&& patch : v) {
      j[patch.name] = patch.data;
    }
  }

  template<EngineType ET>
  void from_json(const nlohmann::json& j, EngineDispatcher<ET>& er)
  {
    if (j.is_object()) {
      for (auto iter = j.begin(); iter != j.end(); iter++) {
        er.apply_patch({ET, iter.key(), iter.value()});
      }
    }
  }

} // namespace otto::engines
