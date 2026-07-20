#pragma once

#include <condition_variable>
#include <functional>
#include <mutex>

#include "lib/util/type_traits.hpp"
#include "lib/util/unix_signals.hpp"
#include "lib/util/utility.hpp"

#include "lib/chrono.hpp"
#include "lib/itc/executor.hpp"
#include "lib/logging.hpp"

namespace otto::services {

  struct RuntimeController;
  enum struct ExitCode { normal };

  /// Manages the runtime of the application
  struct RuntimeController {
    RuntimeController() noexcept;
    ~RuntimeController() noexcept;

    void request_stop(ExitCode = ExitCode::normal) noexcept;

    /// Optional wake hook (e.g. glfwPostEmptyEvent) called after SIGINT/SIGTERM.
    void set_wake_callback(std::function<void()> cb) noexcept;
    void wake() noexcept;

    /// Wait for application to be stopped, with an optional timeout
    ///
    /// After the timeout, request_stop() will be called.
    void wait_for_stop(chrono::duration timeout = chrono::duration::zero()) noexcept;
    [[nodiscard]] bool stop_requested() const noexcept;
    [[nodiscard]] bool should_run() const noexcept;

  private:
    std::atomic<bool> should_run_ = true;
    std::mutex mutex_;
    std::condition_variable cond_;
#if !defined(__APPLE__)
    util::SignalWaiter sig_wait_;
#endif
    std::function<void()> wake_cb_;
  };
} // namespace otto::services
