#pragma once

#include <foonathan/array/flat_map.hpp>

#include "core/engine/engine.hpp"
#include "core/service.hpp"
#include "services/application.hpp"

namespace otto::services {

  struct PresetManager : core::Service {
    /// Error codes. Thrown with exceptions
    enum struct ErrorCode {
      no_such_engine,
      no_such_preset,
    };

    /// EngineManager exceptions. Contain an @ref ErrorCode
    using exception = util::as_exception<ErrorCode>;

    /// Get the names of presets for an engine
    ///
    /// These presets can be applied using @ref apply_preset(AnyEngine&, const std::string_view) or
    /// @ref apply_preset(AnyEngine&, int)
    ///
    /// \throws @ref exception with @ref ErrorCode::no_such_engine if no matching
    /// engine was found.
    ///
    /// \remarks This design is chosen so the engine manager has complete control
    /// over the actual preset data. Also it makes sense for the
    /// @ref otto::engines::EngineSelectorScreen, which is probably the only place
    /// that really needs access
    virtual const std::vector<std::string>& preset_names(util::string_ref engine_name) = 0;

    /// Get the name of preset with indx `idx`
    ///
    /// \throws @ref exception with @ref ErrorCode::no_such_preset if no matching
    /// preset was found, or @ref ErrorCode::no_such_engine if no matching engine
    /// was found
    virtual const std::string& name_of_idx(util::string_ref engine_name, int idx) = 0;

    /// Get the index of preset with name `name`
    ///
    /// \throws @ref exception with @ref ErrorCode::no_such_preset if no matching
    /// preset was found, or @ref ErrorCode::no_such_engine if no matching engine
    /// was found
    virtual int idx_of_name(util::string_ref engine_name, std::string_view name) = 0;

    /// Apply preset to engine
    ///
    /// \effects Apply preset identified by `name` to `engine`
    ///
    /// \throws @ref exception with @ref ErrorCode::no_such_preset if no matching
    /// preset was found.
    virtual void apply_preset(core::engine::IEngine& engine,
                              std::string_view name,
                              bool no_enable_callback = false) = 0;

    /// Apply preset to engine
    ///
    /// \effects Apply preset identified by `idx` to `engine`
    ///
    /// \throws @ref exception with @ref ErrorCode::no_such_preset if no matching
    /// preset was found.
    virtual void apply_preset(core::engine::IEngine& engine, int idx, bool no_enable_callback = false) = 0;

    virtual void create_preset(util::string_ref engine_name,
                               std::string_view preset_name,
                               const nlohmann::json& preset_data) = 0;

    static std::unique_ptr<PresetManager> create_default();

    static PresetManager& current() {
      return *Application::current().preset_manager;
    }

  };

} // namespace otto::services
