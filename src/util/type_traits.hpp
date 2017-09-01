#pragma once

#include <type_traits>
#include <variant>
#include <iterator>

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

  /// Overload lambdas
  template<typename L1, typename... Ls>
  struct overloaded : L1, overloaded<Ls...> {
    overloaded(L1 l1, Ls... ls) : L1(l1), overloaded<Ls...>(ls...) {}
    using L1::operator();
    using overloaded<Ls...>::operator();
  };

  template<typename L1>
  struct overloaded<L1> : L1 {
    explicit overloaded(L1 l1) : L1(l1) {}
    using L1::operator();
  };

  template<typename... Ls>
  overloaded(Ls...) -> overloaded<Ls...>;

  /// Pattern matching for std::variant
  template<class Var, class... Lambdas>
  decltype(auto) match(Var&& v, Lambdas... ls) {
    auto&& matcher = overloaded<Lambdas...>(std::forward<Lambdas>(ls)...);
    return std::visit(std::move(matcher), std::forward<Var>(v));
  }

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


  /// Extends `std::true_type` if `iter` is an iterator over `type`,
  /// with category of at least `category`
  ///
  /// Checks `std::iterator_traits`
  template<typename iter,
           typename type,
           typename category,
           typename Enable = void>
  struct is_iterator : std::false_type {};

  template<typename iter, typename type, typename category>
  struct is_iterator<iter, type, category,
    std::enable_if_t<std::is_same_v<type,
                       std::iterator_traits<iter>::value_type>
      && std::is_base_of_v<category,
                       std::iterator_traits<iter>::iterator_category>
      >>: std::true_type {};


  /// `true` if `iter` is an iterator over `type`,
  /// with category of at least `category`
  ///
  /// Checks `std::iterator_traits`
  template<typename iter, typename type, typename category>
  constexpr bool is_iterator_v = is_iterator<iter, type, category>::value;
}
