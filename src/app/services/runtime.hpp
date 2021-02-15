#pragma once

#include <condition_variable>
#include <mutex>

#include "lib/util/type_traits.hpp"
#include "lib/util/unix_signals.hpp"
#include "lib/util/utility.hpp"

#include "lib/chrono.hpp"
#include "lib/logging.hpp"

namespace otto::services {

  /// Access the runtime of the application
  struct Runtime {};

  /// Manages the runtime of the application
  struct RuntimeController : Runtime {
    RuntimeController() noexcept //
      : signal_waiter_(util::handle_signals({SIGINT}, [this](int sig) {
          LOGI("Got SIGINT, stopping...");
          request_stop();
        }))
    {}

    ~RuntimeController() noexcept
    {
      request_stop();
    }

    enum struct ExitCode { normal };
    void request_stop(ExitCode = ExitCode::normal) noexcept;

    /// Wait for application to be stopped, with an optional timeout
    ///
    /// After the timeout, request_stop() will be called.
    void wait_for_stop(chrono::duration timeout = chrono::duration::zero()) noexcept;

    [[nodiscard]] bool stop_requested() const noexcept;

  private:
    std::atomic<bool> should_run_ = true;
    util::SignalWaiter signal_waiter_;
    std::mutex mutex_;
    std::condition_variable cond_;
  };
} // namespace otto::services
