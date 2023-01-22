#pragma once

#include <condition_variable>
#include <functional>
#include <mutex>
#include <vector>

#include <concurrentqueue.h>
#include <function2/function2.hpp>

#include "lib/util/utility.hpp"

namespace otto::itc {

  struct IExecutor {
    virtual ~IExecutor() = default;
    using Function = fu2::unique_function<void()>;

    // TODO: Allocator for the std::function object
    /// Execute a function on this executor
    ///
    /// Most likely adds it to some queue or calls it directly.
    /// Guarantees:
    /// - Functions will be executed exactly once
    /// - Functions will be executed in order
    virtual void execute(Function) = 0;

    /// Wait for all functions queued before this one to be executed
    void sync() noexcept;

    /// Execute a function, and wait for its result
    template<typename F, typename... Args>
    std::invoke_result_t<F, Args...> block_on(F&& f, Args&&... args)
    {
      tl::optional<std::invoke_result_t<F, Args...>> res;
      this->execute([&] { res = f(std::forward<Args>(args)...); });
      this->sync();
      return std::move(res.value());
    }
  };

  /// An executor that immediately calls the function
  struct ImmediateExecutor final : IExecutor {
    void execute(Function f) override
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
    void execute(Function) noexcept override;

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
    moodycamel::ConcurrentQueue<Function> queue_;
    std::condition_variable cond_;
    std::mutex mutex_;
  };

} // namespace otto::itc
