#pragma once

#include <iterator>
#include <tuple>
#include <type_traits>
#include <variant>

#include "lib/util/macros.hpp"

namespace otto::util {
  /// Any arithmetic type except bool
  template<typename T, typename Enable = void>
  struct is_number : std::false_type {};

  template<typename T>
  struct is_number<T, std::enable_if_t<std::is_arithmetic_v<T> && !std::is_same_v<T, bool>>> : std::true_type {};

  template<typename T>
  constexpr inline bool is_number_v = is_number<T>::value;

  /// this type casts implicitly to anything,
  /// thus, it can represent an arbitrary type.
  struct arbitrary_t {
    template<typename T>
    operator T&&();

    template<typename T>
    operator T&();
  };

  template<typename T, typename Enable = void>
  struct is_number_or_enum : std::false_type {};

  template<typename T>
  struct is_number_or_enum<T, std::enable_if_t<std::is_enum_v<T> || is_number_v<T>>> : std::true_type {};


  template<typename T>
  constexpr inline bool is_number_or_enum_v = is_number_or_enum<T>::value;

  /// Check if a type is equal comparable to another type (or itself)
  template<typename T1, typename T2 = T1, typename Enable = void>
  struct is_equal_comparable : std::false_type {};

  template<typename T1, typename T2>
  struct is_equal_comparable<T1, T2, std::void_t<decltype(std::declval<T1>() == std::declval<T2>())>> : std::true_type {
  };

  template<typename T1>
  struct is_equal_comparable<T1, T1> : std::true_type {};

  template<typename T1, typename T2 = T1>
  constexpr bool is_equal_comparable_v = is_equal_comparable<T1, T2>::value;

  /// Check if a type is less than comparable to another type (or itself)
  template<typename T1, typename T2 = T1, typename Enable = void>
  struct is_less_than_comparable : std::false_type {};

  template<typename T1, typename T2>
  struct is_less_than_comparable<T1, T2, std::void_t<decltype(std::declval<T1>() < std::declval<T2>())>>
    : std::true_type {};

  template<typename T1>
  struct is_less_than_comparable<T1, T1> : std::true_type {};

  template<typename T1, typename T2 = T1>
  constexpr bool is_less_than_comparable_v = is_less_than_comparable<T1, T2>::value;

  /// Check if a type is greater than comparable to another type (or itself)
  template<typename T1, typename T2 = T1, typename Enable = void>
  struct is_greater_than_comparable : std::false_type {};

  template<typename T1, typename T2>
  struct is_greater_than_comparable<T1, T2, std::void_t<decltype(std::declval<T1>() > std::declval<T2>())>>
    : std::true_type {};

  template<typename T1>
  struct is_greater_than_comparable<T1, T1> : std::true_type {};

  template<typename T1, typename T2 = T1>
  constexpr bool is_greater_than_comparable_v = is_greater_than_comparable<T1, T2>::value;

  /// Get the underlying type if T is an enum, otherwise just T
  template<typename T, typename Enable = void>
  struct enum_decay {
    using type = T;
  };

  template<typename T>
  struct enum_decay<T, std::enable_if_t<std::is_enum_v<T>>> {
    using type = std::underlying_type_t<T>;
  };

  template<typename T>
  using enum_decay_t = typename enum_decay<T>::type;

  /// has member type `type` which is `T1` if b is `true`,
  /// otherwise it is `T2`
  template<bool b, typename T1, typename T2>
  struct select_type;

  template<typename T1, typename T2>
  struct select_type<true, T1, T2> {
    static constexpr bool value = true;
    using type = T1;
  };

  template<typename T1, typename T2>
  struct select_type<false, T1, T2> {
    static constexpr bool value = false;
    using type = T2;
  };

  template<bool b, typename T1, typename T2>
  using select_type_t = typename select_type<b, T1, T2>::type;

  template<bool b, typename T1, typename T2>
  constexpr bool select_type_v = select_type<b, T1, T2>::value;

  template<typename T, typename... Ts>
  struct is_one_of {
    static constexpr const bool value = (std::is_same_v<T, Ts> || ...);
  };

  template<typename T, typename... Ts>
  constexpr bool is_one_of_v = (std::is_same_v<T, Ts> || ...);

  /// Extends `std::true_type` if `iter` is an iterator over `type`,
  /// with category of at least `category`
  ///
  /// Checks `std::iterator_traits`
  template<typename iter, typename type, typename category, typename Enable = void>
  struct is_iterator : std::false_type {};

  /// \privatesection
  template<typename iter, typename type, typename category>
  struct is_iterator<
    iter,
    type,
    category,
    std::enable_if_t<
      std::is_same_v<std::remove_reference_t<iter>,
                     typename std::iterator_traits<std::remove_reference_t<iter>>::value_type> &&
      std::is_base_of_v<std::remove_reference_t<iter>,
                        typename std::iterator_traits<std::remove_reference_t<iter>>::iterator_category>>>
    : std::true_type {};


  /// `true` if `iter` is an iterator over `type`,
  /// with category of at least `category`
  ///
  /// Checks `std::iterator_traits`
  template<typename iter, typename type, typename category>
  constexpr bool is_iterator_v = is_iterator<iter, type, category>::value;



  /// Get an integer with `N` bytes
  ///
  /// If possible, has member types `type` and `utype`,
  /// Corresponding to the signed and unsigned ints of size `N`
  template<int N>
  struct int_n_bytes {};

  template<>
  struct int_n_bytes<1> {
    using type = std::int8_t;
    using utype = std::uint8_t;
  };

  template<>
  struct int_n_bytes<2> {
    using type = std::int16_t;
    using utype = std::uint16_t;
  };

  template<>
  struct int_n_bytes<4> {
    using type = std::int32_t;
    using utype = std::uint32_t;
  };

  template<>
  struct int_n_bytes<8> {
    using type = std::int64_t;
    using utype = std::uint64_t;
  };

  template<int N>
  using int_n_bytes_t = typename int_n_bytes<N>::type;

  template<int N>
  using int_n_bytes_u_t = typename int_n_bytes<N>::utype;

  /// Cast scoped enums to their underlying numeric type
  template<typename E>
  constexpr auto underlying(E e) noexcept
  {
    if constexpr (std::is_enum_v<E>) {
      return static_cast<std::underlying_type_t<E>>(e);
    } else {
      return e;
    }
  }
} // namespace otto::util
