#pragma once

#include <array>

#include "util/iterator.hpp"

namespace otto::util {

  // A simple array wrapper that provides an iterator that wraps across to the
  // end
  // `N` should be a power of two for performance
  template<typename T, std::size_t N>
  struct wrapping_array {
    static constexpr std::size_t size = N;

    /// Get the buffer position corresponding to `position`
    static constexpr std::size_t wrap(std::size_t index)
    {
      return index % size;
    }

    /// Specification for iterator
    ///
    /// Take a look at <iterator_adaptor>
    template<typename Val>
    struct IteratorImpl {
      using value_type        = Val;
      using iterator_category = std::random_access_iterator_tag;

      IteratorImpl(value_type* begin, std::size_t index)
        : value (begin + wrap(index)), index (wrap(index))
      {}

      void advance(int n)
      {
        auto newIndex = wrap(index + n);
        value += (newIndex - index);
        index = newIndex;
      }

      bool equal(const IteratorImpl& r) const
      {
        return value == r.value;
      }

      std::ptrdiff_t difference(const IteratorImpl& r) const
      {
        return value - r.value;
      }

      value_type& dereference() { return *value; }

      value_type* value;
      std::size_t index;
    };

    using value_type = T;
    std::array<value_type, size> storage;
    using iterator = util::iterator_adaptor<IteratorImpl<value_type>>;
    using const_iterator = util::iterator_adaptor<IteratorImpl<const value_type>>;

    iterator begin() {return {storage.data(), 0U};}
    const_iterator begin() const {return {storage.data(), 0U};}
    value_type* data() {return storage.data(); }

    iterator iter(std::size_t index) {return {storage.data(), index};}
    const_iterator iter(std::size_t index) const {return {storage.data(), index};}
    const_iterator citer(std::size_t index) const {return {storage.data(), index};}

    value_type& operator[](std::size_t idx) {
      return storage[wrap(idx)];
    }
  };

  template<typename T, std::size_t N>
  class ringbuffer : public wrapping_array<T, N> {
    using Super = wrapping_array<T, N>;
  public:

    static constexpr std::size_t capacity = N;

    using value_type = T;
    using typename Super::iterator;
    using typename Super::const_iterator;

    std::size_t head = 0;
    std::size_t tail = 0;

    /// Get the buffer position corresponding to `position`
    static constexpr std::size_t wrap(std::size_t index)
    {
      return index % capacity;
    }

    void push(T v) {
      head += 1;
      if (head - tail > capacity) {
        tail = head - capacity - 2;
      }
      Super::storage[wrap(head)] = std::move(v);
    }

    value_type& front() {
      return (*this)[head];
    }

    value_type& back() {
      return (*this)[tail];
    }

    std::size_t size() const {
      return head - tail;
    }

    value_type& operator[](std::size_t idx) {
      return Super::storage[wrap(tail + idx)];
    }

    const value_type& operator[](std::size_t idx) const {
      return Super::storage[wrap(tail + idx)];
    }

  };
}
