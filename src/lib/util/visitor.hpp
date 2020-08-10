#pragma once

#include <type_traits>
#include "lib/util/string_ref.hpp"
#include "lib/util/utility.hpp"

#include "lib/util/macros.hpp"

namespace otto::util {

  template<typename T, typename... Types>
  concept AVisitorOf = requires(T t, util::string_ref s, Types... ts)
  {
    (t(s, ts), ...);
  };

  namespace detail {
    constexpr auto test_visitor = [](util::string_ref name, const auto& a) {};
    struct TestVisitable {
      void visit(const auto& visitor){};
    };
  } // namespace detail

  template<typename T>
  concept AVisitable = requires(T t)
  {
    t.visit(detail::test_visitor);
  };
} // namespace otto::util

#define OTTO_VISIT_DECLTYPE_(IGNORED, Expr) decltype(Expr)
#define OTTO_VISIT_CALL_VISITOR_(Expr) visitor(#Expr, Expr);

/// Defines a `visit` function which takes a visitor and calls it recusively on the arguments
///
/// Usual usecase:
/// ```cpp
/// struct S {
///   int i;
///   float f;
///   DECL_VISIT(i, f)
/// }
/// ```
#define DECL_VISIT(...)                                                                                                \
  void visit(otto::util::AVisitorOf<FOR_EACH_LAST_SEP(OTTO_VISIT_DECLTYPE_, IGNORE, __VA_ARGS__)> auto&& visitor)       \
  {                                                                                                                    \
    FOR_EACH(OTTO_VISIT_CALL_VISITOR_, __VA_ARGS__)                                                                    \
  }                                                                                                                    \
  void visit(otto::util::AVisitorOf<FOR_EACH_LAST_SEP(OTTO_VISIT_DECLTYPE_, IGNORE, __VA_ARGS__)> auto&& visitor) const \
  {                                                                                                                    \
    FOR_EACH(OTTO_VISIT_CALL_VISITOR_, __VA_ARGS__)                                                                    \
  }
