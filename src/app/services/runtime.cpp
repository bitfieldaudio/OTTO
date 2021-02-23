#include "runtime.hpp"

#include "lib/util/unix_signals.hpp"

namespace otto::services {

  RuntimeController::RuntimeController() noexcept
    : sig_wait_({SIGINT}, [this](int sig) {
        LOGI("Got SIGINT, stopping...");
        request_stop();
      })
  {}

  RuntimeController::~RuntimeController() noexcept
  {
    request_stop();
  }

  bool RuntimeController::stop_requested() const noexcept
  {
    return !should_run_;
  }

  void RuntimeController::wait_for_stop(chrono::duration timeout) noexcept
  {
    {
      std::unique_lock lock(mutex_);
      if (timeout == chrono::duration::zero()) {
        cond_.wait(lock, [&] { return !should_run_; });
      } else {
        cond_.wait_for(lock, timeout, [&] { return !should_run_; });
      }
    }
    request_stop();
  }

  void RuntimeController::request_stop(ExitCode) noexcept
  {
    std::unique_lock lock(mutex_);
    should_run_ = false;
    cond_.notify_all();
  }

  bool RuntimeController::should_run() const noexcept
  {
    return should_run_;
  }

  //  RuntimeLock::RuntimeLock(RuntimeController& rc, itc::QueueExecutor& ex) noexcept : rc_(rc), ex_(ex)
  //  {
  //    std::scoped_lock l(rc.mutex_);
  //    is_leader_ = rc.locks_.empty(); // NOLINT
  //    rc.locks_.emplace_back(this);
  //  }
  //
  //  RuntimeLock::~RuntimeLock() noexcept
  //  {
  //    sync_exit();
  //  }
  //
  //  bool RuntimeLock::should_run() noexcept
  //  {
  //    return rc_.should_run();
  //  }
  //
  //  void RuntimeLock::sync_exit(ExitCode ec) noexcept
  //  {
  //    if (should_run()) rc_.request_stop(ec);
  //    while (true) {
  //      {
  //        std::scoped_lock l(mutex_);
  //        if (rc_.exit_is_done_) {
  //          std::scoped_lock l(rc_.mutex_);
  //          std::erase(rc_.locks_, this);
  //          return;
  //        }
  //        did_run_ = did_run_ || ex_.run_queued_functions();
  //        has_tried_running_ = true;
  //      }
  //      if (is_leader_) {
  //        bool all_ready = std::ranges::all_of(rc_.locks_, [](auto& l) { return l->has_tried_running_.load(); });
  //        if (all_ready) {
  //          for (auto& l : rc_.locks_) {
  //            l->mutex_.lock();
  //          }
  //          rc_.exit_is_done_ = std::ranges::none_of(rc_.locks_, [](auto& l) { return l->did_run_; });
  //          for (auto& l : rc_.locks_) {
  //            l->mutex_.unlock();
  //          }
  //        }
  //      }
  //    }
  //  }
} // namespace otto::services
