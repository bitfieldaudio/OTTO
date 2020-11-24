#pragma once

#include <atomic>

namespace otto::util {

  /// A simple spin lock. Works with `std::scoped_lock` etc
  struct spin_lock {
    void lock() noexcept
    {
      while (flag.test_and_set(std::memory_order_acquire))
        ;
    }

    bool try_lock() noexcept
    {
      return !flag.test_and_set(std::memory_order_acquire);
    }

    void unlock() noexcept
    {
      flag.clear(std::memory_order_release);
    }

  private:
    std::atomic_flag flag = ATOMIC_FLAG_INIT;
  };

} // namespace otto::util
