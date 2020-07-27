#pragma once

#include <concurrentqueue.h>

#include "lib/util/utility.hpp"

namespace otto::lib::itc {

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

    /// Enqueue a function
    /// 
    /// Can be called from any thread. Functions queued from one thread
    /// will be executed in order, but not necessarily in order with
    /// functions enqueued from other threads.
    void execute(std::function<void()> f) noexcept override
    {
      queue_.enqueue(std::move(f));
    }

    /// Run functions from the queue until none are available
    void run_queued_functions() noexcept
    {
      std::function<void()> f;
      while (queue_.try_dequeue(f)) {
        f();
      }
    }

  private:
    moodycamel::ConcurrentQueue<std::function<void()>> queue_;
  };

} // namespace otto::itc
