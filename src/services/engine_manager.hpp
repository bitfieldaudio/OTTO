#pragma once

#include <unordered_map>

#include "core/service.hpp"
#include "core/engine/engine.hpp"

#include "core/audio/processor.hpp"

#include "services/state_manager.hpp"
#include "services/ui_manager.hpp"
#include "services/application.hpp"

#include "engines/misc/sends/sends.hpp"

namespace otto::services {

  struct EngineManager : core::Service, util::OwnsObservers {
    /// Error codes. Thrown with exceptions
    enum struct ErrorCode {
      no_such_engine,
    };

    /// EngineManager exceptions. Contain an ErrorCode
    using exception = util::as_exception<ErrorCode>;

    /// Initi alize engine manager
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
    virtual core::audio::ProcessData<2> process(core::audio::ProcessData<2> external_in) = 0;

    /// For now, this is the way to get the default EngineManager implementation
    /// 
    /// This is very likely to be changed in the future
    static std::unique_ptr<EngineManager> create_default();

    static EngineManager& current() noexcept {
      return Application::current().engine_manager;
    }
  };

} // namespace otto::services
