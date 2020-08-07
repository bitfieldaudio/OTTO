#pragma once

#include "lib/chrono.hpp"
#include "lib/core/service.hpp"

namespace otto::services {

  /// Manages the runtime of the application
  struct Runtime : core::Service<Runtime> {
    enum struct ExitCode { normal };
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

    virtual void request_stop(ExitCode = ExitCode::normal) noexcept = 0;

    /// Block calling thread until we enter the given stage
    ///
    /// Returns false if we are in a stage past the given one, and will
    /// thus never enter it.
    [[nodiscard]] virtual bool wait_for_stage(Stage s, chrono::duration timeout) noexcept = 0;

    [[nodiscard]] bool wait_for_stage(Stage s) noexcept
    {
      return wait_for_stage(s, chrono::duration::zero());
    }
  };

} // namespace otto::services
