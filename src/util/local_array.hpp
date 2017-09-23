#pragma once

#include <cstddef>
#include <iterator>
#include <utility>
#include <algorithm>

namespace top1 {

  /// A simple array on the stack
  ///
  /// A wrapper around a C-style array `T[N]` Provides default initialization
  /// for elements.
  template<typename T, std::size_t N>
  class local_array {
  public:

    static constexpr std::size_t length = N;
    using value_type = T;
    using iterator = value_type*;
    using reverse_iterator = std::reverse_iterator<iterator>;

    /* Initialization */

    /// Default construct all values
    constexpr local_array()
      : storage {}
    {}

    /// Initialize individual members
    constexpr local_array(std::initializer_list<T> init)
    {
      std::copy(init.begin(), init.end(), storage);
    }

    /// Initialize all members
    constexpr local_array(T init)
    {
      std::fill(std::begin(storage), std::end(storage), std::move(init));
    }

    /// Copy construct all values
    constexpr local_array(const local_array& o)
    {
      std::copy(o.begin(), o.end(), begin());
    }

    /// Move construct all values
    constexpr local_array(local_array&& o)
    {
      std::move(o.begin(), o.end(), begin());
    }

    constexpr local_array& operator=(local_array o)
    {
      using std::swap;
      swap(*this, o);
      return *this;
    }

    friend void swap(local_array& l, local_array& r) noexcept
    {
      std::swap_ranges(l.begin(), l.end(), r.begin());
    }

    /* Get iterators */

    constexpr iterator begin()
    {
      return storage;
    }

    constexpr iterator end()
    {
      return storage + N;
    }

    constexpr const iterator begin() const
    {
      return iterator(storage);
    }

    constexpr const iterator end() const
    {
      return iterator(storage);
    }

    constexpr iterator rbegin()
    {
      return reverse_iterator(begin());
    }

    constexpr iterator rend()
    {
      return reverse_iterator(end());
    }

    constexpr const iterator rbegin() const
    {
      return reverse_iterator(begin());
    }

    constexpr const iterator rend() const
    {
      return reverse_iterator(end());
    }

    constexpr std::size_t size() const {
      return N;
    }

    /// An alias to `begin()`
    constexpr value_type* data()
    {
      return storage;
    }

    constexpr value_type& operator[](std::size_t i)
    {
      return storage[i];
    }

    constexpr value_type operator[](std::size_t i) const
    {
      return storage[i];
    }

  private:
    /* Member variables */

    value_type storage[N];
  };
}
