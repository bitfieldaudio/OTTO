#pragma once

#include <functional>

#include "util/meta.hpp"
#include "util/type_traits.hpp"
#include "util/utility.hpp"
#include "util/algorithm.hpp"

namespace otto::util {
  namespace detail {
    template<typename... Args, typename Callable>
    decltype(auto) with_opt_args_impl(Callable&& callable, meta::list<Args...>)
    {
      if constexpr (std::is_invocable_v<Callable, Args...>) {
        return std::forward<Callable>(callable);
      } else {
        return [c = std::forward<Callable>(callable)](Args... args) { 
          std::apply(with_opt_args_impl(c, meta::pop_back_t<meta::list<Args...>>()), util::tuple) };
      }
    }
  } // namespace detail

  template<typename... Args, typename Callable>
  decltype(auto) with_opt_args(Callable&& callable)
  {}

  template<typename Signature>
  struct opt_arg_func;

  /// A @ref std::function like object where args are optional upon construction.
  template<typename Ret, typename... Args>
  struct opt_arg_func<Ret(Args...)> {
    template<typename Callable>
    opt_arg_func(Callable&& callable) : function_(with_opt_args<Args...>(callable))
    {}



  private:
    std::function<Ret(Args...)> function_;
  };
} // namespace otto::util
