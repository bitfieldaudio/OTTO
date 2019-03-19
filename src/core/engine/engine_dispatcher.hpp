#pragma once

#include <foonathan/array/flat_map.hpp>
#include "core/engine/engine.hpp"
#include "core/engine/nullengine.hpp"

#include "util/variant_w_base.hpp"

namespace otto::core::engine {

  /// Interface base class for the EngineDispatcher struct
  struct IEngineDispatcher {
    IEngineDispatcher(bool allow_off) noexcept : allow_off(allow_off) {}
    virtual IEngine& current() = 0;
    virtual const IEngine& current() const = 0;
    virtual int current_idx() const = 0;
    virtual IEngine& select(std::string_view name) = 0;
    virtual IEngine& select(int index) = 0;

    virtual std::vector<std::string_view> make_name_list() const = 0;

    virtual ~IEngineDispatcher() = default;

    /// Is the engine allowed to be in an "OFF" state?
    const bool allow_off = false;
  };

  /// Owns engines of type `ET`, and dispatches to a selected one of them
  template<EngineType ET, typename... Engines>
  struct EngineDispatcher final : IEngineDispatcher {
    enum struct ErrorCode { none = 0, engine_not_found, type_mismatch };

    using exception = util::as_exception<ErrorCode>;

    static constexpr const EngineType engine_type = ET;
    using ITypedEngine = engine::ITypedEngine<ET>;
    using variant = util::variant_w_base<ITypedEngine, Engines...>;
    using DataMap = foonathan::array::flat_map<std::string_view, nlohmann::json>;

    // Initialization
    EngineDispatcher(bool allow_off) : IEngineDispatcher(allow_off) {}

    /// Construct all registered engines
    ///
    /// Only call this after all engines are registered
    void init();

    /// Access the currently selected engine
    ITypedEngine& current() noexcept override;
    const ITypedEngine& current() const noexcept override;
    int current_idx() const noexcept override;

    /// Access the currently selected engine
    ITypedEngine const* operator->() const noexcept;
    /// Access the currently selected engine
    ITypedEngine* operator->() noexcept;

    /// Select engine by name
    ///
    /// \effects Find engine with name `name`, and `select(engine)`
    /// \throws `util::exception` when no matching engine was found
    ITypedEngine& select(std::string_view name) override;

    /// Select engine by index
    /// 
    /// If `index` is < 0, and `allow_off`, select the null engine.
    /// @throws `util::exception` when `index` is out of bounds
    ITypedEngine& select(int index) override;

    std::vector<std::string_view> make_name_list() const override;

    /// Access the screen used to select engines/presets
    ///
    /// The returned screen has the dynamic type [EngineSelectorScreen]()
    /// \preconditions [init]() has previously been called
    ui::Screen& selector_screen() noexcept;

    const DataMap& data_of_engines() const noexcept;

    nlohmann::json to_json() const;
    void from_json(const nlohmann::json&);

  private:
    DataMap _engine_data;
    NullEngine<ET> _null_engine;
    variant _engine_storage = std::in_place_index_t<0>();
    ITypedEngine* _current = &_null_engine;
    std::unique_ptr<ui::Screen> _selector_screen = nullptr;
  };
} // namespace otto::core::engine

// kak: other_file=engine_dispatcher.inl
