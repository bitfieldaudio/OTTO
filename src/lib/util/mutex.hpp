#pragma once

#include <concepts>
#include <mutex>
#include <shared_mutex>

#include <tl/optional.hpp>

#include "macros.hpp"

namespace otto::util {

  template<typename T, typename Lock>
  struct scoped_lock {
    scoped_lock(T& value, Lock lock) : value(value), lock(std::move(lock)) {}

    T& operator*()
    {
      return value;
    }

    const T& operator*() const
    {
      return value;
    }

    T* operator->()
    {
      return &value;
    }

    const T* operator->() const
    {
      return &value;
    }
    
    void unlock() && {
      lock.unlock();
    }

  private:
    T& value;
    Lock lock;
  };

  /// A value hidden behind a mutex.
  /// This design forces the mutex to be locked before accessing the value.
  /// Similar to rusts mutexes.
  template<typename T>
  struct mutex {
    mutex() = default;
    mutex(T value) : value(value) {}

    using lock_t = scoped_lock<T, std::unique_lock<std::mutex>>;
    using const_lock_t = scoped_lock<const T, std::unique_lock<std::mutex>>;

    lock_t lock()
    {
      return lock_t(value, std::unique_lock(m));
    }

    tl::optional<lock_t> try_lock()
    {
      if (m.try_lock()) {
        return lock_t(value, std::unique_lock(m, std::adopt_lock));
      }
      return tl::nullopt;
    }

    const_lock_t lock_const() const
    {
      return lock_t(value, std::unique_lock(m));
    }

    tl::optional<const_lock_t> try_lock_const() const
    {
      if (m.try_lock()) {
        return lock_t(value, std::unique_lock(m, std::adopt_lock));
      }
      return tl::nullopt;
    }

  private:
    mutable std::mutex m;
    T value;
  };

  /// A value hidden behind a shared_mutex.
  /// This design forces the mutex to be locked before accessing the value.
  /// Similar to rusts mutexes.
  template<typename T>
  struct shared_mutex {
    shared_mutex() = default;
    shared_mutex(T value) : value(value) {}

    using lock_t = scoped_lock<T, std::unique_lock<std::shared_mutex>>;
    using shared_lock_t = scoped_lock<const T, std::shared_lock<std::shared_mutex>>;

    lock_t lock()
    {
      return lock_t(value, std::unique_lock(m));
    }

    tl::optional<lock_t> try_lock()
    {
      if (m.try_lock()) {
        return lock_t(value, std::unique_lock(m, std::adopt_lock));
      }
      return tl::nullopt;
    }

    shared_lock_t lock_shared() const
    {
      return shared_lock_t(value, std::shared_lock(m));
    }

    tl::optional<shared_lock_t> try_lock_shared() const
    {
      if (m.try_lock_shared()) {
        return shared_lock_t(value, std::shared_lock(m, std::adopt_lock));
      }
      return tl::nullopt;
    }

  private:
    mutable std::shared_mutex m;
    T value;
  };
} // namespace otto::util
