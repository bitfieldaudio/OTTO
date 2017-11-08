#pragma once

#include <functional>
#include <type_traits>

namespace otto::util {


  /// A CRTP style cache base class.
  ///
  /// The cached value is imutable, and lazilly refreshed.
  /// This wrapper is not thread safe at invalidation!
  ///
  /// \requires `T` shall be `DefaultConstructible`
  template<typename T>
  struct cache_base {

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
        refresh();
        _valid = true;
      }
      return dynamic_cast<const T&>(*this);
    }

    /// Access the cached value
    ///
    /// Alias to `value()`
    const T* operator->() {
      return &value();
    }

    /// Access the cached value
    ///
    /// Alias to `value()`
    const T& operator*() {
      return value();
    }

  protected:

    /// Refresh the cache
    ///
    /// It should be implemented in the derived class, and it is called by
    /// `value()` when the cache is invalid
    virtual void refresh() = 0;

    bool _valid = false;

  };

  /// A simple wrapper for invalidatable caches.
  ///
  /// If you are writing a separate struct to contain the cache data, use
  /// `cache_base` instead.
  ///
  /// The cached value is imutable, and lazilly refreshed.
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
  struct cached : cache_base<T> {

    template<typename FuncRef>
    cached(FuncRef&& f)
      : generator(make_generator(std::forward<FuncRef>(f)))
    {}

  private:

    void refresh() override {
      generator(cache_base<T>::cache);
    }

    std::function<void(T&)> generator;

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
