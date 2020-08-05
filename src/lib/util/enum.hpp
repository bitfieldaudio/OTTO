#pragma once

#include <array>
#include <json.hpp>
#include <magic_enum.hpp>

#include "lib/util/concepts.hpp"

namespace otto::lib::util {

  using namespace magic_enum;

  template<AnEnum Enum, semiregular T>
  struct enum_map {
    using value_type = T;
    using iterator = typename std::array<T, enum_count<Enum>()>::iterator;
    using const_iterator = typename std::array<T, enum_count<Enum>()>::const_iterator;

    constexpr enum_map() = default;
    constexpr enum_map(std::initializer_list<std::pair<Enum, T>> init)
    {
      for (auto&& [k, v] : init) {
        (*this)[k] = v;
      }
    }

    static constexpr std::size_t size() noexcept
    {
      return enum_count<Enum>();
    }

    constexpr auto begin() noexcept
    {
      return _data.begin();
    }

    constexpr auto begin() const noexcept
    {
      return _data.begin();
    }

    constexpr auto end() noexcept
    {
      return _data.end();
    }

    constexpr auto end() const noexcept
    {
      return _data.end();
    }

    constexpr value_type& front() noexcept
    {
      return _data.front();
    }

    constexpr const value_type& front() const noexcept
    {
      return _data.front();
    }

    constexpr value_type& back() noexcept
    {
      return _data.back();
    }

    constexpr const value_type& back() const noexcept
    {
      return _data.back();
    }

    constexpr value_type& operator[](Enum e) noexcept
    {
      return _data[enum_index(e).value()];
    }

    constexpr const value_type& operator[](Enum e) const noexcept
    {
      return _data[enum_index(e).value()];
    }

    constexpr value_type& at(Enum e)
    {
      return _data.at(enum_index(e).value());
    }

    constexpr const value_type& at(Enum e) const
    {
      return _data.at(enum_index(e).value());
    }

    constexpr value_type* data() noexcept
    {
      return _data.data();
    }

    constexpr const value_type* data() const noexcept
    {
      return _data.data();
    }

    std::array<T, enum_count<Enum>()> _data = {};
  };
} // namespace otto::lib::util
