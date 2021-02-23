#pragma once

#include <condition_variable>
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

  //  struct RuntimeLock {
  //    bool should_run() noexcept;
  //    void sync_exit(ExitCode = ExitCode::normal) noexcept;
  //
  //  private:
  //    friend RuntimeController;
  //    RuntimeLock(RuntimeController& rc, itc::QueueExecutor& ex) noexcept;
  //    ~RuntimeLock() noexcept;
  //
  //    std::mutex mutex_;
  //    RuntimeController& rc_;
  //    itc::QueueExecutor& ex_;
  //    bool is_leader_;
  //    std::atomic<bool> has_tried_running_ = false;
  //    bool did_run_ = true;
  //  };

  /// Manages the runtime of the application
  struct RuntimeController {
    RuntimeController() noexcept;
    ~RuntimeController() noexcept;

    void request_stop(ExitCode = ExitCode::normal) noexcept;

    /// Wait for application to be stopped, with an optional timeout
    ///
    /// After the timeout, request_stop() will be called.
    void wait_for_stop(chrono::duration timeout = chrono::duration::zero()) noexcept;
    [[nodiscard]] bool stop_requested() const noexcept;
    [[nodiscard]] bool should_run() const noexcept;

    //    RuntimeLock acquire(itc::QueueExecutor& ex) {
    //      return {*this, ex};
    //    }

  private:
    //    friend RuntimeLock;
    std::atomic<bool> should_run_ = true;
    //    std::atomic<bool> exit_is_done_ = false;
    std::mutex mutex_;
    std::condition_variable cond_;
    //    std::vector<RuntimeLock*> locks_;
    util::SignalWaiter sig_wait_;
  };
} // namespace otto::services
