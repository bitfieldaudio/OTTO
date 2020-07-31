#pragma once

#include "lib/core/service.hpp"

namespace otto::app::services {

  /// Manages the runtime of the application
  struct Runtime : lib::core::Service<Runtime> {
    enum struct Stage {
      initializing,
      running,
      stopping,
    };

    virtual Stage stage() const noexcept = 0;

    /// The loop variable of all main loops
    /// 
    /// When this turns to false, all threads should stop
    virtual bool should_run() const noexcept = 0;
  };

} // namespace otto::app::services
