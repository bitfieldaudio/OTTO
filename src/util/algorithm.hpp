#pragma once

#include <algorithm>
#include <initializer_list>
#include <functional>
#include <string>
#include "util/type_traits.hpp"

namespace top1 {

  /// Joins a sequence of strings, separating them using `js`
  template<class StrIterator> // Models InputIterator<std::string>
  auto join_strings(StrIterator b, StrIterator e, std::string_view js = ", ") -> std::string {
    std::string result;
    std::for_each(b, e, [&] (auto&& s) {
        if (!result.empty()) {
          result.append(js);
        }
        result.append(s);
      });
    return result;
  }

  namespace detail {
    template<class Func, int... ns>
    constexpr auto generate_sequence_impl(std::integer_sequence<int, ns...>&&, Func&& gen) {
      #pragma clang diagnostic push
      #pragma clang diagnostic ignored "-Wmissing-braces"
      return std::array{std::invoke(std::forward<Func>(gen), ns)...};
      #pragma clang diagnostic pop
    }
  }

  template<int n, class Func>
  constexpr auto generate_sequence(Func&& gen) {
    auto intseq = std::make_integer_sequence<int, n>();
    return detail::generate_sequence_impl(std::move(intseq), std::forward<Func>(gen));
  }


  template<class InputIt, class Size, class UnaryFunction>
  auto for_each_n(InputIt first, Size n, UnaryFunction f) ->
    std::enable_if_t<
      is_iterator_v<InputIt, typename std::iterator_traits<InputIt>::value_type,
        std::input_iterator_tag>
      && std::is_invocable_v<UnaryFunction,
        const typename std::iterator_traits<InputIt>::reference>, InputIt> {
    for (Size i = 0; i < n; ++first, (void) ++i) {
      f(*first);
    }
    return first;
  }
}
