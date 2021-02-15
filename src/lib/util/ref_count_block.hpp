#pragma once

#include <concepts>
#include <mutex>

#include <tl/optional.hpp>

#include "lib/util/utility.hpp"

namespace otto::util {

  // TODO: Implement all of this without locking on each increment/decrement
  // I think it should be possible to do with doubly checked locking, using
  // an atomic<int> for ref_count_, and only locking the mutex when we may actually
  // need to create or destroy the object
  /// Storage for a reference counted object.
  ///
  /// Useful for creating custom handles to reference counted data.
  template<std::default_initializable T>
  requires(std::is_nothrow_constructible_v<T>&& std::is_nothrow_destructible_v<T>) //
    struct RefCountBlock {
    /// Increment the reference count, and construct the object if it wasn't before
    void increment() noexcept
    {
      std::scoped_lock l(mutex_);
      if (!data_.has_value()) {
        data_.emplace();
      }
      ref_count_++;
    }
    /// Decrement the reference count, and destroy the object if the count reaches 0
    void decrement() noexcept
    {
      std::scoped_lock l(mutex_);
      ref_count_--;
      if (ref_count_ == 0) {
        data_ = tl::nullopt;
      }
    }

    /// Access the stored object
    tl::optional<T&> data() noexcept
    {
      return util::opt_ref(data_);
    }

  private:
    std::mutex mutex_;
    int ref_count_ = 0;
    tl::optional<T> data_;
  };
} // namespace otto::util
