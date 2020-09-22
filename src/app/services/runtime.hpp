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

    /// Queue a function for execution whenever the stage changes
    ///
    /// The function takes the new stage as an argument, and returns true if it wants to
    /// be removed from the list, and not be called on the next stage change.
    virtual void on_stage_change(std::function<bool(Stage s)>) noexcept = 0;

    void on_enter_stage(Stage s, std::function<void()> f) noexcept
    {
      on_stage_change([s, f = std::move(f)](Stage new_s) {
        if (new_s == s) f();
        return new_s == s;
      });
    }

    [[nodiscard]] bool wait_for_stage(Stage s) noexcept
    {
      return wait_for_stage(s, chrono::duration::zero());
    }
  };

} // namespace otto::services
