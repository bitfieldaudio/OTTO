#pragma once

#include <algorithm>
#include <array>

#include "lib/util/string_ref.hpp"

#include "lib/meta.hpp"

namespace otto::util::cxpr {

  namespace detail {
    template<std::size_t I>
    constexpr auto to_string_buff = []() constexpr
    {
      if constexpr (I < 10) {
        constexpr std::array<char, 2> buff = {'0' + I, '\0'};
        return buff;
      } else {
        constexpr auto impl = []<std::size_t J>(meta::c<J>, auto prev_buff, auto impl) {
          if constexpr (J > 0) {
            std::array<char, prev_buff.size() + 1> buff;
            std::ranges::copy(prev_buff, buff.begin() + 1);
            buff[0] = '0' + (J % 10);
            return impl(meta::c<J / 10>(), buff, impl);
          } else {
            return prev_buff;
          }
        };
        return impl(meta::c<I>(), std::array<char, 1>{0}, impl);
      }
    }
    ();
  } // namespace detail

  template<std::size_t I>
  constexpr util::string_ref to_string = detail::to_string_buff<I>.data();

  static_assert(to_string<0> == "0");
  static_assert(to_string<1> == "1");
  static_assert(to_string<10> == "10");
  static_assert(to_string<983> == "983");
} // namespace otto::util::cxpr
