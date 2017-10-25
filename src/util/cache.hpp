#pragma once

#include <functional>
#include <type_traits>

namespace otto::util {

  /// A simple wrapper for invalidatable caches
  ///
  /// The cached value is imutable
  /// This wrapper is not thread safe at invalidation!
  ///
  /// It is constructed with a generator function, which can take two forms:
  ///
  ///   1. `void(T& cache)`, which is expected to update the `cache` parameter
  ///      it is supplied with.
  ///   2. `T()`, which will return the new value.
  ///
  /// Both can be very useful in different contexts.
  ///
  /// \requires `T` shall be `DefaultConstructible`
  template<typename T>
  struct cached {

    template<typename FuncRef>
    cached(FuncRef&& fr)
      : generator {make_generator(std::forward<FuncRef>(fr))}
    {}

    /// Invalidate the cache
    void invalidate()
    {
      _valid = false;
    }

    /// Check if the cache is valid
    bool valid() const
    {
      return _valid;
    }

    /// Access the cached value
    const T& value()
    {
      if (!_valid) {
        std::invoke(generator, cache);
        _valid = true;
      }
      return cache;
    }

  private:

    std::function<void(T&)> generator;
    T cache;
    bool _valid = false;

    /// Creates the apropriate generator function from the two valid signatures
    ///
    /// Used in the constructor
    template<typename Fr>
    static auto make_generator(Fr&& fr) {
      if constexpr (std::is_invocable_v<Fr, T&>) {
        return fr;
      } else if constexpr (std::is_same_v<std::invoke_result_t<Fr>, T>) {
        return [fr = std::forward<Fr>(fr)] (T& cache) {
          cache = std::invoke(fr);
        };
      }
    }

  };

}
