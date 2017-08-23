#pragma once

#include <type_traits>

namespace top1 {

  /// Any arithmetic type except bool
  template<typename T, typename Enable = void>
  struct is_number : std::false_type {};

  template<typename T>
  struct is_number<T, std::enable_if_t<
                        std::is_arithmetic_v<T> && !std::is_same_v<T, bool>>>
    : std::true_type {};

  template<typename T>
  constexpr inline bool is_number_v = is_number<T>::value;
}
