#pragma once

#include "core/engine/engine.hpp"

namespace otto::core::engine {

  // Implementation is in engine_dispatcher.cpp, with explicit instantiations at
  // the bottom.

  /// Owns engines of type `ET`, and dispatches to a selected one of them
  template<EngineType ET>
  struct EngineDispatcher {
    enum struct ErrorCode { none = 0, engine_not_found, type_mismatch };

    using exception = util::as_exception<ErrorCode>;

    static constexpr const EngineType type = ET;

    // Initialization

    /// Construct all registered engines
    ///
    /// Only call this after all engines are registered
    /// \effects
    ///  - construct [_engines]() using [otto::engines:create_engines<ET>]()
    ///  - instantiate [_selector_screen]() with a new [EngineSelectorScreen<ET>]()
    void init();

    /// Access the currently selected engine
    Engine<ET>& current() noexcept;
    const Engine<ET>& current() const noexcept;

    /// Access the currently selected engine
    Engine<ET>& operator*() noexcept;
    /// Access the currently selected engine
    const Engine<ET>& operator*() const noexcept;

    /// Access the currently selected engine
    Engine<ET> const* operator->() const noexcept;
    /// Access the currently selected engine
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

    /// Access the screen used to select engines/presets
    ///
    /// The returned screen has the dynamic type [EngineSelectorScreen]()
    /// \preconditions [init]() has previously been called
    ui::Screen& selector_screen() noexcept;

    const std::vector<std::unique_ptr<Engine<ET>>>& engines() const noexcept;

    nlohmann::json to_json() const;
    void from_json(const nlohmann::json&);

  private:
    std::vector<std::unique_ptr<Engine<ET>>> _engines;
    std::unique_ptr<ui::Screen> _selector_screen = nullptr;
    Engine<ET>* _current = nullptr;
  };

} // namespace otto::core::engines
