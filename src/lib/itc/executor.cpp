#include "executor.hpp"

#include "testing.t.hpp"

#include "lib/logging.hpp"

// Disable debug logging in this file
// Can be reenabled for development
#undef DLOGI
#define DLOGI(...)

namespace otto::itc {

  // QueueExecutor

  void QueueExecutor::execute(std::function<void()> f) noexcept
  {
    queue_.enqueue(std::move(f));
    notify();
  }
  bool QueueExecutor::run_queued_functions() noexcept
  {
    bool res = false;
    std::function<void()> f;
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

  // ExecutorLockable

  ExecutorLockable::Lock ExecutorLockable::acquire()
  {
    return Lock(this);
  }

  ExecutorLockable::Lock::Lock(ExecutorLockable* l) noexcept : lockable_(l)
  {
    {
      std::unique_lock lock(lockable_->mutex_);
      idx = lockable_->locks_.size();
      lockable_->locks_.push_back(this);
      DLOGI("{}: REGISTED", char('A' + idx));
    }
    lockable_->notify_next();
  }

  void ExecutorLockable::Lock::release() noexcept
  {
    std::unique_lock lock(lockable_->mutex_);
    std::erase(lockable_->locks_, this);
    lockable_ = nullptr;
  }

  void ExecutorLockable::Lock::exit_synchronized(QueueExecutor& e) noexcept
  {
    while (!attempt_sync_exit(e)) {
      lockable_->notify_next();
    }
    lockable_->notify_next();
    std::unique_lock lock(lockable_->mutex_);
    DLOGI("{}: has exited!", char('A' + idx));
    std::erase(lockable_->locks_, this);
    lockable_ = nullptr;
  }

  bool ExecutorLockable::Lock::attempt_sync_exit(QueueExecutor& e) noexcept
  {
    auto& owner = *lockable_;
    auto lock = std::unique_lock(lockable_->mutex_);
    owner.cond_.wait(lock, [&] { return owner.next_up_ == this; });
    bool was_done = is_done_;
    if (was_done) DLOGI("{}: was done", char('A' + idx));
    bool did_run = e.run_queued_functions();
    if (did_run) {
      DLOGI("{}: did_run", char('A' + idx));
      for (auto& l : lockable_->locks_) {
        l->is_done_ = false;
      }
    }
    is_done_ = true;
    DLOGI("{}: is_done", char('A' + idx));
    if (!was_done) return false;
    for (auto* l : lockable_->locks_) {
      if (!l->is_done_) {
        DLOGI("{}: {} is not done", char('A' + idx), char('A' + l->idx));
        return false;
      }
    }
    return true;
  } // namespace otto::itc

  void ExecutorLockable::notify_next()
  {
    {
      std::unique_lock lock(mutex_);
      auto next = std::find(locks_.begin(), locks_.end(), next_up_);
      if (next == locks_.end()) next = locks_.begin();
      next++;
      if (next == locks_.end()) next = locks_.begin();
      next_up_ = *next;
      DLOGI("Next up: {}", char('A' + next_up_->idx));
      cond_.notify_all();
    }
  }

} // namespace otto::itc
