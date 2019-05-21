#pragma once

#include <array>

namespace otto::util {

  template<typename T, std::size_t Capacity>
  struct local_vector {
    using value_type = T;
    using iterator = typename std::array<T, Capacity>::iterator;
    using const_iterator = typename std::array<T, Capacity>::const_iterator;

    constexpr local_vector(std::initializer_list<value_type> il) : _data(il), _size(il.size()) {}

    // Queries

    static constexpr std::size_t capacity() noexcept
    {
      return Capacity;
    }

    constexpr std::size_t size() const noexcept
    {
      return _size;
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

    constexpr const value_type& operator[](std::size_t idx)
    {
      return _data[idx];
    }

  private:
    std::array<value_type, capacity()> _data;
    std::size_t _size;
  };
} // namespace otto::util
