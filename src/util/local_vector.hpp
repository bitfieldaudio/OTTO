#pragma once

#include <array>

namespace otto::util {

  template<typename T, std::size_t Capacity>
  struct local_vector {
    using value_type = T;
    using iterator = typename std::array<T, Capacity>::iterator;
    using const_iterator = typename std::array<T, Capacity>::const_iterator;

    constexpr local_vector() : _data(), _size(0) {}

    template<std::size_t N, std::enable_if_t<N <= Capacity>>
    constexpr local_vector(std::array<T, N> il) : _data(il), _size(il.size()) {}

    // Queries

    static constexpr std::size_t capacity() noexcept
    {
      return Capacity;
    }

    constexpr std::size_t size() const noexcept
    {
      return _size;
    }

    constexpr bool empty() const noexcept
    {
      return size() == 0;
    }

    constexpr auto begin()
    {
      return _data.begin();
    }

    constexpr auto begin() const
    {
      return _data.begin();
    }

    constexpr auto end()
    {
      return _data.begin() + _size;
    }

    constexpr auto end() const
    {
      return _data.begin() + _size;
    }

    constexpr value_type& front()
    {
      return _data.front();
    }

    constexpr const value_type& front() const
    {
      return _data.front();
    }

    constexpr value_type& back()
    {
      return _data[_size - 1];
    }

    constexpr const value_type& back() const
    {
      return _data[_size - 1];
    }

    constexpr value_type& operator[](std::size_t idx)
    {
      return _data[idx];
    }

    constexpr value_type* data()
    {
      return _data.data();
    }

    constexpr const value_type* data() const
    {
      return _data.data();
    }


    constexpr value_type& push_back(const value_type& e) {
      _data.at(_size) = e;
      _size++;
      return back();
    }

    constexpr iterator insert(iterator pos, const value_type& e) {
      _data.at(_size) = e;
      _size++;
      return end() - 1;
    }

    constexpr const_iterator& insert(const_iterator pos, const value_type& e) {
      _data.at(_size) = e;
      _size++;
      return end() - 1;
    }

    constexpr void pop_back() {
      // TODO: Actually destroy elements;
      _size--;
    }

    constexpr void clear() {
      _size = 0;
    }

  private:
    std::array<value_type, capacity()> _data;
    std::size_t _size;
  };
} // namespace otto::util
