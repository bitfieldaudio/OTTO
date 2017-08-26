#pragma once

#include <type_traits>
#include <variant>

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

  /// Matching for std::variant

  template<class Var, class... Lambdas>
  decltype(auto) match(Var&& v, Lambdas... ls) {
    auto matcher = overloaded<Lambdas...>(ls...);
    return matcher(v);
  }

}
