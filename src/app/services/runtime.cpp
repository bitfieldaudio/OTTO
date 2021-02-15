#include "runtime.hpp"

namespace otto::services {

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
} // namespace otto::services
