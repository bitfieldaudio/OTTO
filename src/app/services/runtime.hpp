#pragma once

#include <condition_variable>
#include <mutex>

#include "lib/util/unix_signals.hpp"
#include "lib/util/utility.hpp"

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

    [[nodiscard]] Stage stage() const noexcept;

    /// The loop variable of all main loops
    ///
    /// When this turns to false, all threads should stop
    [[nodiscard]] bool should_run() const noexcept;

    void request_stop(ExitCode = ExitCode::normal) noexcept;

    [[nodiscard]] bool wait_for_stage(Stage s, chrono::duration timeout = chrono::duration::zero()) noexcept;
    void on_stage_change(std::function<bool(Stage s)> f) noexcept;

    void set_stage(Stage s) noexcept;

    void on_enter_stage(Stage s, std::function<void()> f) noexcept;

    [[nodiscard]] bool wait_for_stage(Stage s) noexcept;

  private:
    std::vector<std::function<bool(Stage)>> hooks_;
    std::atomic<std::underlying_type_t<Stage>> stage_ = util::underlying(Stage::initializing);
    std::mutex mutex_;
    std::condition_variable cond_;
  };

  struct RuntimeObserver {
  protected:
    static Runtime& runtime();
  };
} // namespace otto::services
