#pragma once

#include "core/engine/engine.hpp"

namespace otto::core::engine {

  // Implementation is in engine_dispatcher.cpp, with explicit instantiations at
  // the bottom.

  /// Interface base class for the EngineDispatcher struct
  struct IEngineDispatcher {
      virtual AnyEngine* current() = 0;
      virtual const AnyEngine* current() const = 0;

      virtual ~IEngineDispatcher() = default;
  };

  /// Owns engines of type `ET`, and dispatches to a selected one of them
  template<EngineType ET>
  struct EngineDispatcher final : IEngineDispatcher {
    enum struct ErrorCode { none = 0, engine_not_found, type_mismatch };

    using exception = util::as_exception<ErrorCode>;

    static constexpr const EngineType type = ET;

    struct EngineFactory {
      std::string name;
      std::function<std::unique_ptr<Engine<ET>>()> construct;
      nlohmann::json data;
    };

    // Initialization

    /// Construct all registered engines
    ///
    /// Only call this after all engines are registered
    /// \effects
    ///  - construct [_engines]() using [otto::engines:create_engines<ET>]()
    ///  - instantiate [_selector_screen]() with a new [EngineSelectorScreen<ET>]()
    void init();

    /// Access the currently selected engine
    Engine<ET>* current() noexcept override;
    const Engine<ET>* current() const noexcept override;

    /// Access the currently selected engine
    Engine<ET> const* operator->() const noexcept;
    /// Access the currently selected engine
    Engine<ET>* operator->() noexcept;

    /// Get the index of the currently selected engine.
    int current_idx() const noexcept;

    /// Create an engine and select it by factory
    /// 
    /// If the name is the same as the already selected engine, that engine is returned instead.
    Engine<ET>& select(const EngineFactory&);

    /// Select engine by index
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

    void register_factory(EngineFactory factory);

    template<typename Eg>
    void register_engine(std::string name);

    const std::vector<EngineFactory>& engine_factories() const noexcept;

    nlohmann::json to_json() const;
    void from_json(const nlohmann::json&);


  private:
    std::vector<EngineFactory> _factories;
    const EngineFactory* _current_factory = nullptr;
    std::shared_ptr<Engine<ET>> _current = nullptr;
    std::unique_ptr<ui::Screen> _selector_screen = nullptr;
  };

  template<EngineType Et>
  template<typename Eg>
  void EngineDispatcher<Et>::register_engine(std::string name)
  {
    register_factory({std::move(name), [] { return std::make_unique<Eg>(); }});    
  }

} // namespace otto::core::engine
