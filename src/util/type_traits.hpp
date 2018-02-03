#pragma once

#include <iterator>
#include <type_traits>
#include <variant.hpp>
#include <variant>

namespace otto::util {

  /// Any arithmetic type except bool
  template<typename T, typename Enable = void>
  struct is_number : std::false_type {
  };

  template<typename T>
  struct is_number<
    T,
    std::enable_if_t<std::is_arithmetic_v<T> && !std::is_same_v<T, bool>>>
    : std::true_type {
  };

  template<typename T>
  constexpr inline bool is_number_v = is_number<T>::value;

  template<typename T, typename Enable = void>
  struct is_number_or_enum : std::false_type {
  };

  template<typename T>
  struct is_number_or_enum<
    T,
    std::enable_if_t<std::is_enum_v<T> || is_number_v<T>>> : std::true_type {
  };

  template<typename T>
  constexpr inline bool is_number_or_enum_v = is_number_or_enum<T>::value;

  /// has member type `type` which is `T1` if b is `true`,
  /// otherwise it is `T2`
  template<bool b, typename T1, typename T2>
  struct select_type;

  template<typename T1, typename T2>
  struct select_type<true, T1, T2> {
    static constexpr bool value = true;
    using type                  = T1;
  };

  template<typename T1, typename T2>
  struct select_type<false, T1, T2> {
    static constexpr bool value = false;
    using type                  = T2;
  };

  template<bool b, typename T1, typename T2>
  using select_type_t = typename select_type<b, T1, T2>::type;

  template<bool b, typename T1, typename T2>
  constexpr bool select_type_v = select_type<b, T1, T2>::value;

  template<typename T, typename... Ts>
  struct is_one_of {
    static constexpr bool value = false;
  };

  template<typename T, typename T1, typename... Ts>
  struct is_one_of<T, T1, Ts...> {
    static const constexpr bool value = std::is_same_v<T, T1> || is_one_of<T, Ts...>::value;
  };

  template<typename T, typename... Ts>
  constexpr bool is_one_of_v = is_one_of<T, Ts...>::value;

  /// Extends `std::true_type` if `iter` is an iterator over `type`,
  /// with category of at least `category`
  ///
  /// Checks `std::iterator_traits`
  template<typename iter,
           typename type,
           typename category,
           typename Enable = void>
  struct is_iterator : std::false_type {
  };

  template<typename iter, typename type, typename category>
  struct is_iterator<
    iter,
    type,
    category,
    std::enable_if_t<
      std::is_same_v<
        std::remove_reference_t<iter>,
        std::iterator_traits<std::remove_reference_t<iter>>::value_type> &&
      std::is_base_of_v<std::remove_reference_t<iter>,
                        std::iterator_traits<
                          std::remove_reference_t<iter>>::iterator_category>>>
    : std::true_type {
  };


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
  struct int_n_bytes {
  };

  template<>
  struct int_n_bytes<1> {
    using type  = std::int8_t;
    using utype = std::uint8_t;
  };

  template<>
  struct int_n_bytes<2> {
    using type  = std::int16_t;
    using utype = std::uint16_t;
  };

  template<>
  struct int_n_bytes<4> {
    using type  = std::int32_t;
    using utype = std::uint32_t;
  };

  template<>
  struct int_n_bytes<8> {
    using type  = std::int64_t;
    using utype = std::uint64_t;
  };

  template<int N>
  using int_n_bytes_t = typename int_n_bytes<N>::type;

  template<int N>
  using int_n_bytes_u_t = typename int_n_bytes<N>::utype;

  // libc++ 5.0 doesnt have these

  template<typename F, typename... Args>
  using is_invocable = mpark::lib::is_invocable<F, Args...>;

  template<typename F, typename... Args>
  constexpr bool is_invocable_v = mpark::lib::is_invocable<F, Args...>::value;

  template<typename R, typename F, typename... Args>
  using is_invocable_r = mpark::lib::is_invocable_r<R, F, Args...>;

  template<typename R, typename F, typename... Args>
  constexpr bool is_invocable_r_v =
    mpark::lib::is_invocable_r<R, F, Args...>::value;

  template<typename F, typename... Args>
  using invoke_result = mpark::lib::invoke_result<F, Args...>;

  template<typename F, typename... Args>
  using invoke_result_t = mpark::lib::invoke_result_t<F, Args...>;


  /// Cast scoped enums to their underlying numeric type
  template<typename E>
  constexpr auto underlying(E e) -> std::underlying_type_t<E>
  {
    return static_cast<std::underlying_type_t<E>>(e);
  }

} // namespace otto::util
