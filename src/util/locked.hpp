#pragma once

#include <mutex>
#include <functional>

namespace otto::util {

  /// Wrap any type in a mutex, and guarantee that it is locked on every access.
  template<typename T>
  class locked {

    T contents;

  public:

    template<typename... Args>
    locked(Args&&... args)
      : contents {std::forward<Args>(args)...}
    {}

    /// Direct access to the mutex to do manual locking
    std::mutex mutex;

    /// Use the wrapped value while locked
    /// Invoke `f` with the wrapped value as the only parameter
    ///
    /// \param f Invocable as `f(T)`
    /// \returns The result of calling `f(t)`
    /// \requires `Func` is invocable as `Func(T&)`
    template<typename Func>
    auto apply(Func&& f)
    {
      auto lock = std::unique_lock(mutex);
      return std::invoke(std::forward<Func>(f), contents);
    }

    /// Use the wrapped value while locked
    /// Invoke `f` with the wrapped value as the only parameter
    ///
    /// \param f Invocable as `f(T)`
    /// \returns The result of calling `f(t)`
    /// \requires `Func` is invocable as `Func(const T&)`
    template<typename Func>
    auto apply(Func&& f) const
    {
      auto lock = std::unique_lock(mutex);
      return std::invoke(std::forward<Func>(f), contents);
    }

    /// Get a non-locked reference to the value.
    ///
    /// This is of course highly unsafe, and defeats the purpose of the wrapper
    T& unsafe_access() {
      return contents;
    }


    /// Get a non-locked reference to the value.
    ///
    /// This is of course highly unsafe, and defeats the purpose of the wrapper
    const T& unsafe_access() const {
      return contents;
    }
  };

}

//  LocalWords:  util
