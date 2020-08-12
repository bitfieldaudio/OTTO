#pragma once

#include <concurrentqueue.h>
#include <condition_variable>
#include <functional>
#include <mutex>
#include <vector>

#include "lib/util/utility.hpp"

namespace otto::itc {

  struct IExecutor {
    virtual ~IExecutor() = default;

    // TODO: Allocator for the std::function object
    /// Execute a function on this executor
    ///
    /// Most likely adds it to some queue or calls it directly.
    /// Guarantees:
    /// - Functions will be executed exactly once
    /// - Functions will be executed in order
    virtual void execute(std::function<void()>) = 0;
  };

  /// An executor that immediately calls the function
  struct ImmediateExecutor final : IExecutor {
    void execute(std::function<void()> f) override
    {
      std::move(f)();
    }
  };

  /// An executor that enqueues functions on a concurrent queue
  ///
  /// Can be used with multiple producing and multiple consuming threads.
  ///
  /// @NOTE Requires synchronization upon destruction. The last call to
  /// {@ref run_queued_functions} _must_ be started strictly _after_ the last
  /// call to {@ref execute} to ensure that the function will indeed be called.
  /// This is nowhere near as trivial as it sounds!
  struct QueueExecutor final : IExecutor {
    ~QueueExecutor() noexcept
    {
      notify();
    }
    /// Enqueue a function
    ///
    /// Can be called from any thread. Functions queued from one thread
    /// will be executed in order, but not necessarily in order with
    /// functions enqueued from other threads.
    void execute(std::function<void()> f) noexcept override;

    /// Run functions from the queue until none are available
    ///
    /// @return true if any functions were run
    bool run_queued_functions() noexcept;

    /// Run functions from the queue until none are available.
    ///
    /// If none are available initially, block and wait for `notify()`
    /// or `execute` to be called.
    void run_queued_functions_blocking(std::chrono::system_clock::duration timeout) noexcept;

    /// Check if the queue contains any functions.
    ///
    /// If this returns true, `run_queued_functions` will have functions to run
    /// If it returns false, you learned basically nothing.
    bool has_queued() noexcept;


    /// Wake up the thread waiting on `run_queued_functions_blocking`
    void notify() noexcept;

  private:
    moodycamel::ConcurrentQueue<std::function<void()>> queue_;
    std::condition_variable cond_;
    std::mutex mutex_;
  };

  /// Synchronize the exit of multiple threads running `QueueExecutor`s
  ///
  /// This facilitates multiple threads which mutually enqueue functions onto
  /// eachother to shut down correctly.
  struct ExecutorLockable {
    struct Lock {
      Lock(ExecutorLockable* l) noexcept;
      ~Lock() noexcept
      {
        if (lockable_) release();
      }

      Lock(const Lock&) = delete;
      Lock(Lock&&) = delete;
      Lock& operator=(const Lock&) = delete;
      Lock& operator=(Lock&&) = delete;

      /// Run the functions that remain in the queue until all queues are done.
      void exit_synchronized(QueueExecutor& e) noexcept;

    private:
      void release() noexcept;
      bool attempt_sync_exit(QueueExecutor& e) noexcept;

      int idx = -1;
      ExecutorLockable* lockable_ = nullptr;
      bool is_done_ = false;
      friend ExecutorLockable;
    };

    /// Acquire a scoped lock
    Lock acquire();

  private:
    /// Notify the next lock in the list
    void notify_next();

    std::mutex mutex_;
    std::condition_variable cond_;
    Lock* next_up_ = nullptr;
    std::vector<Lock*> locks_;
  };

} // namespace otto::itc
