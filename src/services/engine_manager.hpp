#pragma once

#include <unordered_map>

#include "core/service.hpp"
#include "core/engine/engine.hpp"
#include "core/engine/engine_dispatcher.hpp"

#include "core/audio/processor.hpp"

#include "util/result.hpp"

#include "services/state_manager.hpp"
#include "services/ui_manager.hpp"
#include "services/application.hpp"


namespace otto::services {

  struct EngineManager : core::Service {
    /// Error codes. Thrown with exceptions
    enum struct ErrorCode {
      no_such_engine,
    };

    /// EngineManager exceptions. Contain an ErrorCode
    using exception = util::as_exception<ErrorCode>;

    /// Initialize engine manager
    ///
    /// \effects
    ///  - register engines.
    ///  - construct engines
    ///  - register key handlers
    ///  - attach state loader/saver
    EngineManager() = default;

    /// Destruct engines
    ///
    /// \effects Invoke AnyEngine::on_disable for all enabled engines
    virtual ~EngineManager() = default;

    /// Mark engines as started
    ///
    /// \effects
    /// Invoke AnyEngine::on_enable for all selected engines
    ///
    /// \requires services::state::load must have been invoked
    virtual void start() = 0;

    /// Process the engine audio chain
    virtual core::audio::ProcessData<2> process(core::audio::ProcessData<1> external_in) = 0;

    /// Get an engine by name
    ///
    /// \returns `nullptr` if no such engine was found
    virtual core::engine::AnyEngine* by_name(const std::string& name) noexcept = 0;
  };

} // namespace otto::services
