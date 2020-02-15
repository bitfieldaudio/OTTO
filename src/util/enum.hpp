#pragma once

#include <array>
#include <better_enum.hpp>
#include <json.hpp>

#include "util/type_traits.hpp"

namespace otto::util {

  template<typename Enum, typename T>
  struct enum_map {
    using value_type = T;
    using iterator = typename std::array<T, Enum::_size()>::iterator;
    using const_iterator = typename std::array<T, Enum::_size()>::const_iterator;

    constexpr enum_map() = default;
    constexpr enum_map(std::initializer_list<std::pair<Enum, T>> init)
    {
      for (auto&& [k, v] : init) {
        (*this)[k] = v;
      }
    }

    static constexpr std::size_t size() noexcept
    {
      return Enum::_size();
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
      return _data[e._to_index()];
    }

    constexpr const value_type& operator[](Enum e) const noexcept
    {
      return _data[e._to_index()];
    }

    constexpr value_type& at(Enum e)
    {
      return _data.at(e._to_index());
    }

    constexpr const value_type& at(Enum e) const
    {
      return _data.at(e._to_index());
    }

    constexpr value_type* data() noexcept
    {
      return _data.data();
    }

    constexpr const value_type* data() const noexcept
    {
      return _data.data();
    }

    std::array<T, Enum::_size()> _data;
  };
} // namespace otto::util

/// Serialize a BetterEnum to json
template<typename Enum>
inline auto serialize(const Enum& e) -> std::enable_if_t<otto::util::BetterEnum::is<Enum>, nlohmann::json>
{
  return serialize(e._to_string());
}

/// Deserialize a BetterEnum from json
template<typename Enum>
inline auto deserialize(Enum& p, const nlohmann::json& j)
  -> std::enable_if_t<otto::util::BetterEnum::is<Enum>, nlohmann::json>
{
  p = Enum::_from_string(j.get<std::string>().c_str());
}
