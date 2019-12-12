#pragma once

#include <tuple>
#include <utility>

/// \file
/// General purpose utilities. Mostly lambda magic

namespace otto::util {

  template<typename Ret, typename... Args>
  using function_ptr = Ret (*)(Args...);

  template<typename Class, typename Ret, typename... Args>
  using member_func_ptr = Ret (Class::*)(Args...);

  template<typename Class, typename T>
  using member_ptr = T Class::*;

  // overloaded ///////////////////////////////////////////////////////////////

  /// Overload lambdas
  template<typename... Ls>
  struct overloaded : Ls... {
    overloaded(Ls... ls) : Ls(ls)... {}
    using Ls::operator()...;
  };

  template<typename... Ls>
  overloaded(Ls...)->overloaded<std::decay_t<Ls>...>;

  // match ////////////////////////////////////////////////////////////////////

  /// Pattern matching for std::variant.
  ///
  /// One of `Lambdas` is required to match
  template<typename Var, typename... Lambdas>
  decltype(auto) match(Var&& v, Lambdas&&... ls)
  {
    auto&& matcher = overloaded(std::forward<Lambdas>(ls)...);
    // ADL to use std::visit or mpark::visit
    // TODO: Remove this when the standard is adapted
    return visit(std::move(matcher), std::forward<Var>(v));
  }

  /// Match any type, do nothing with it
  const constexpr auto nullmatch = [](auto&&) {};

  /// Pattern matching for std::variant.
  ///
  /// Does not require all states of `v` to be matched, and defaults to no
  /// action.
  template<typename Var, typename... Lambdas>
  decltype(auto) partial_match(Var&& v, Lambdas&&... ls)
  {
    return match(std::forward<Var>(v), std::forward<Lambdas>(ls)..., nullmatch);
  }

  // capture_this /////////////////////////////////////////////////////////////

  /// Get a callable from a member pointer and an object.
  template<typename Type, typename Ret, typename... Args>
  auto capture_this(Ret (Type::*func)(Args...), Type* object)
  {
    return [object, func](Args... args) -> Ret { return (object->*func)(args...); };
  }
  template<typename Type, typename Ret, typename... Args>
  auto capture_this(Ret (Type::*func)(Args...), Type& object)
  {
    return [&object, func](Args... args) -> Ret { return (object.*func)(args...); };
  }

  template<typename T>
  auto does_equal(T&& obj)
  {
    return [obj = std::forward<T>(obj)](auto&& lhs) { return lhs == obj; };
  }

  // Tuple for_each ///////////////////////////////////////////////////////////

  namespace details {
    template<typename T, typename F, std::size_t... Is>
    void tuple_for_each_impl(T&& t, F&& f, std::integer_sequence<std::size_t, Is...> is)
    {
      (f(std::get<Is>(t)), ...);
    }

    template<typename T, typename F, std::size_t... Is>
    void tuple_for_each_i_impl(T&& t, F&& f, std::integer_sequence<std::size_t, Is...> is)
    {
      (f(Is, std::get<Is>(t)), ...);
    }
  } // namespace details

  template<typename F, typename... Args>
  void for_each(const std::tuple<Args...>& tuple, F&& f)
  {
    details::tuple_for_each_impl(tuple, FWD(f),
                                 std::make_index_sequence<std::tuple_size<std::tuple<Args...>>::value>());
  }

  template<typename F, typename... Args>
  void for_each(std::tuple<Args...>& tuple, F&& f)
  {
    details::tuple_for_each_impl(tuple, FWD(f),
                                 std::make_index_sequence<std::tuple_size<std::tuple<Args...>>::value>());
  }

  template<typename F, typename... Args>
  void for_each(std::tuple<Args...>&& tuple, F&& f)
  {
    details::tuple_for_each_impl(tuple, FWD(f),
                                 std::make_index_sequence<std::tuple_size<std::tuple<Args...>>::value>());
  }

  /// Call `f(idx, element)` for each `element` in `tuple`
  template<typename F, typename... Args>
  void indexed_for_each(const std::tuple<Args...>& tuple, F&& f)
  {
    details::tuple_for_each_i_impl(tuple, FWD(f),
                                   std::make_index_sequence<std::tuple_size<std::tuple<Args...>>::value>());
  }

  /// Call `f(idx, element)` for each `element` in `tuple`
  template<typename F, typename... Args>
  void indexed_for_each(std::tuple<Args...>& tuple, F&& f)
  {
    details::tuple_for_each_i_impl(tuple, FWD(f),
                                   std::make_index_sequence<std::tuple_size<std::tuple<Args...>>::value>());
  }

  /// Call `f(idx, element)` for each `element` in `tuple`
  template<typename F, typename... Args>
  void indexed_for_each(std::tuple<Args...>&& tuple, F&& f)
  {
    details::tuple_for_each_i_impl(tuple, FWD(f),
                                   std::make_index_sequence<std::tuple_size<std::tuple<Args...>>::value>());
  }

  inline namespace tuple {
    namespace detail {
      template<class X>
      constexpr auto remove_last_impl(X&& x)
      {
        return std::tuple<>();
      }

      template<class X, class... Xs>
      constexpr auto remove_last_impl(X&& x, Xs&&... xs);

      constexpr auto tuple_remove_last = [](auto&&... args) { return remove_last_impl(FWD(args)...); };

      template<class X, class... Xs>
      constexpr auto remove_last_impl(X&& x, Xs&&... xs)
      {
        return std::tuple_cat(std::tuple<X>(FWD(x)), std::apply(tuple_remove_last, std::tuple<Xs...>(FWD(xs)...)));
      }
    } // namespace detail

    template<class T, class... Args>
    constexpr auto remove_last(const std::tuple<T, Args...>& t)
    {
      return std::apply(detail::tuple_remove_last, t);
    }
  } // namespace tuple
} // namespace otto::util
