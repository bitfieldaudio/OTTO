#include "executor.hpp"

#include <yamc_semaphore.hpp>

#include "lib/logging.hpp"

namespace otto::itc {
  void IExecutor::sync() noexcept
  {
    auto sem = yamc::binary_semaphore(0);
    execute([&sem] { sem.release(); });
    sem.acquire();
  }

  // QueueExecutor

  void QueueExecutor::execute(Function f) noexcept
  {
    queue_.enqueue(std::move(f));
    notify();
  }
  bool QueueExecutor::run_queued_functions() noexcept
  {
    bool res = false;
    Function f;
    while (queue_.try_dequeue(f)) {
      f();
      res = true;
    }
    return res;
  }
  bool QueueExecutor::has_queued() noexcept
  {
    return queue_.size_approx() > 0;
  }

  void QueueExecutor::notify() noexcept
  {
    cond_.notify_all();
  }

  void QueueExecutor::run_queued_functions_blocking(std::chrono::system_clock::duration timeout) noexcept
  {
    std::unique_lock lock(mutex_);
    cond_.wait_for(lock, timeout, [this] { return run_queued_functions(); });
  }

} // namespace otto::itc
