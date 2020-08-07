#pragma once

#include <concepts>
#include <functional>
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

} // namespace otto::util
