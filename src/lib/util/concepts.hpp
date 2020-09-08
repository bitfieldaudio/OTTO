#pragma once

#include <concepts>
#include <functional>
#include <ranges>
#include <type_traits>
#include <utility>

#include "lib/util/type_traits.hpp"

namespace otto::util {

  /// Any arithmetic type except bool
  template<typename T>
  concept numeric = std::is_arithmetic_v<T> && !std::same_as<T, bool>;

  namespace detail {
    template<typename F, typename Shape>
    struct is_callable_impl;

    template<typename F, typename Ret, typename... Args>
    struct is_callable_impl<F, Ret(Args...)> {
      static constexpr bool value = requires(F f, Args... args)
      {
        {
          std::invoke(f, args...)
        }
        ->std::same_as<Ret>;
      };
    };

    template<typename Shape>
    struct is_function_shape : std::false_type {};

    template<typename Ret, typename... Args>
    struct is_function_shape<Ret(Args...)> : std::true_type {};
  } // namespace detail

  template<typename T>
  concept function_shape = detail::is_function_shape<T>::value;

  template<typename F, typename Shape>
  concept callable = function_shape<Shape>&& detail::is_callable_impl<F, Shape>::value;

  template<typename T, typename... Ts>
  concept one_of = is_one_of_v<T, Ts...>;

  template<typename T>
  concept AnEnum = std::is_enum_v<T>;

  template<typename R, typename V>
  concept range_of = std::ranges::range<R>&& std::common_reference_with<std::ranges::range_value_t<R>, V>;
  template<typename R, typename V>
  concept sized_range_of = std::ranges::sized_range<R>&& std::common_reference_with<std::ranges::range_value_t<R>, V>;
  template<typename R, typename V>
  concept view_of = std::ranges::view<R>&& std::common_reference_with<std::ranges::range_value_t<R>, V>;
  template<typename R, typename V>
  concept input_range_of = std::ranges::input_range<R>&& std::common_reference_with<std::ranges::range_value_t<R>, V>;
  template<typename R, typename V>
  concept output_range_of =
    std::ranges::output_range<R, V>&& std::common_reference_with<std::ranges::range_value_t<R>, V>;
  template<typename R, typename V>
  concept forward_range_of =
    std::ranges::forward_range<R>&& std::common_reference_with<std::ranges::range_value_t<R>, V>;
  template<typename R, typename V>
  concept bidirectional_range_of =
    std::ranges::bidirectional_range<R>&& std::common_reference_with<std::ranges::range_value_t<R>, V>;
  template<typename R, typename V>
  concept random_access_range_of =
    std::ranges::random_access_range<R>&& std::common_reference_with<std::ranges::range_value_t<R>, V>;
  template<typename R, typename V>
  concept contiguous_range_of =
    std::ranges::contiguous_range<R>&& std::common_reference_with<std::ranges::range_value_t<R>, V>;
  template<typename R, typename V>
  concept common_range_of = std::ranges::common_range<R>&& std::common_reference_with<std::ranges::range_value_t<R>, V>;
  template<typename R, typename V>
  concept viewable_range_of =
    std::ranges::viewable_range<R>&& std::common_reference_with<std::ranges::range_value_t<R>, V>;
} // namespace otto::util
