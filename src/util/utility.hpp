#pragma once

#include <utility>

/// \file
/// General purpose utilities. Mostly lambda magic

namespace otto::util {

  // overloaded ///////////////////////////////////////////////////////////////

  /// Overload lambdas
  template<typename... Ls>
  struct overloaded : Ls... {
    overloaded(Ls... ls) : Ls(ls)... {}
    using Ls::operator()...;
  };

  template<typename... Ls>
  overloaded(Ls...) -> overloaded<std::decay_t<Ls>...>;

  // match ////////////////////////////////////////////////////////////////////

  /// Pattern matching for std::variant.
  ///
  /// One of `Lambdas` is required to match
  template<typename Var, typename... Lambdas>
  decltype(auto) match(Var&& v, Lambdas&&... ls)
  {
    auto&& matcher = overloaded<Lambdas...>(std::forward<Lambdas>(ls)...);
    // ADL to use std::visit or mpark::visit
    // TODO: Remove this when the standard is adapted
    return visit(std::move(matcher), std::forward<Var>(v));
  }

  /// Match any type, do nothing with it
  const constexpr auto nullmatch = [](const auto&&) {};

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
  auto capture_this(Ret (Type::*func)(Args...), Type* object) {
    return [object, func] (Args... args) -> Ret { return (object->*func)(args...);};
  }
  template<typename Type, typename Ret, typename... Args>
  auto capture_this(Ret (Type::*func)(Args...), Type& object) {
    return [&object, func] (Args... args) -> Ret { return (object.*func)(args...);};
  }

} // namespace otto::util
