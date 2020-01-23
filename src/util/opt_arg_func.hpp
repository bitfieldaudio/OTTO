#pragma once

#include <functional>

#include "util/algorithm.hpp"
#include "util/meta.hpp"
#include "util/type_traits.hpp"
#include "util/utility.hpp"

namespace otto::util {
  namespace detail {
    template<typename Func, typename Tuple>
    struct can_apply;

    template<typename Func, typename... Ts>
    struct can_apply<Func, std::tuple<Ts...>> : std::is_invocable<Func, Ts...> {};
  } // namespace detail

  /// Make a callable that lets the input callable be callable with `Args...`
  /// 
  /// `Callable` must be callable with a prefix of `Args...`.
  /// When calling the resulting callable, the remaining args will be discarded
  template<typename... Args, typename Callable>
  decltype(auto) with_opt_args(Callable&& callable)
  {
    return [func = FWD(callable)](Args... args) {
      auto impl = [&](auto&& impl, auto&& tuple) {
        if constexpr (detail::can_apply<Callable, std::decay_t<decltype(tuple)>>::value) {
          return std::apply(func, FWD(tuple));
        } else {
          return impl(impl, util::tuple::remove_last(tuple));
        }
      };
      // Pass impl as a parameter to facilitate recursion
      return impl(impl, std::tuple<Args...>(args...));
    };
  }

  template<typename Signature>
  struct opt_arg_func;

  /// A @ref std::function like object where args are optional upon construction.
  ///
  /// I.e. an `opt_arg_func<void(int, float)>` can also be constructed with a 
  /// `void(int)` or `void()` function, and the remaining arguments will simply
  /// be discarded.
  template<typename Ret, typename... Args>
  struct opt_arg_func<Ret(Args...)> {
    template<typename Callable>
    opt_arg_func(Callable&& callable) : function_(with_opt_args<Args...>(callable))
    {}

    Ret operator()(Args... args) const
    {
      return function_(FWD(args)...);
    }

  private:
    std::function<Ret(Args...)> function_;
  };
} // namespace otto::util
