#pragma once

#include "concurrentqueue.h"
#include "itc.hpp"
#include "util/utility.hpp"

namespace otto::itc {

  struct QueueExecutor final : IExecutor {
    void execute(std::function<void()> f) noexcept override
    {
      queue_.enqueue(std::move(f));
    }

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
