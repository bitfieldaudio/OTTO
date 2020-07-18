#include <algorithm>
#include "util/concepts.hpp"

#include "testing.t.hpp"

namespace otto::util {

  /// A numeric type with static limits
  /// Limits are only enforced on assignments, meaning it should behave like a numeric type T in all other respects
  /// (under arithmetic operations, etc.) i.e. the result of a+b can be outside the limits Note that the limits
  /// conceptually SHOULD be of type T, but floats cannot be used in this manner, see:
  /// http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2019/p1907r1.html
  /// Hence, integer limits must be used. If floats are needed, use the types with dynamic limits.
  /// TODO: This should be available in C++20, so we could remove this constraint.
  template<numeric T, int min, int max>
  struct WithStaticLimits {
    // You must initialze with default value
    WithStaticLimits() = delete;
    WithStaticLimits(T init_val)
    {
      value = std::clamp(static_cast<T>(init_val), static_cast<T>(min), static_cast<T>(max));
    };

    T value;

    void operator=(const T in)
    {
      value = std::clamp(in, static_cast<T>(min), static_cast<T>(max));
    }

    operator T() const noexcept
    {
      return value;
    }
  };

  // template<numeric T_lhs, int min_lhs, int max_lhs>
  // auto operator+(const WithStaticLimits<T_lhs, min_lhs, max_lhs> a, const numeric auto b)
  // {
  //   return a.value + b;
  // }

  // template<numeric T_lhs, numeric T_rhs, int min_rhs, int max_rhs>
  // auto operator+(const T_lhs a, const WithStaticLimits<T_rhs, min_rhs, max_rhs> b)
  // {
  //   return a + b.value;
  // }

  // template<numeric T_lhs, int min_lhs, int max_lhs, numeric T_rhs, int min_rhs, int max_rhs>
  // auto operator+(const WithStaticLimits<T_lhs, min_lhs, max_lhs> a, const WithStaticLimits<T_rhs, min_rhs, max_rhs> b)
  // {
  //   return a.value + b.value;
  // }


} // namespace otto::util
