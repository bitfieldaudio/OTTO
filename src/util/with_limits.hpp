#include <algorithm>
#include "util/concepts.hpp"

#include "testing.t.hpp"

namespace otto::util {

  /// A numeric type with static limits
  /// Limits are only enforced on assignments, meaning it should behave like a numeric type T in all other respects
  /// (under arithmetic operations, etc.) i.e. the result of a+b can be outside the limits.
  /// Note that the limits conceptually SHOULD be of type T, but floats cannot be used in this manner, see:
  /// http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2019/p1907r1.html
  /// Hence, integer limits must be used. If floats are needed, use the types with dynamic limits.
  /// TODO: This should be available in C++20, so we could remove this constraint.
  template<numeric T, int min, int max>
  struct StaticallyBounded {
    // You must initialize with default value
    StaticallyBounded() = delete;
    StaticallyBounded(T init_val)
    {
      value_ = std::clamp(static_cast<T>(init_val), static_cast<T>(min), static_cast<T>(max));
    };

    void operator=(const T in)
    {
      value_ = std::clamp(in, static_cast<T>(min), static_cast<T>(max));
    }
    void operator+=(const T in)
    {
      operator=(this->value_ + in);
    }
    void operator-=(const T in)
    {
      operator=(this->value_ - in);
    }
    void operator*=(const T in)
    {
      operator=(this->value_ * in);
    }
    void operator/=(const T in)
    {
      operator=(this->value_ / in);
    }
    void operator++()
    {
      operator=(this->value_ + static_cast<T>(1));
    }
    void operator--()
    {
      operator=(this->value_ - static_cast<T>(1));
    }
    // If needed, binary operators can be added

    operator T() const noexcept
    {
      return value_;
    }

  private:
    T value_;
  };

  // Comparison
  // Note: I think it is best if we don't allow comparisons with other StaticallyBounded<> with different limits.
  template<numeric T, int min, int max>
  bool operator==(const StaticallyBounded<T, min, max>& lhs, 
                  const StaticallyBounded<T, min, max>& rhs)
                  {
                    return static_cast<T>(lhs) == static_cast<T>(rhs);
                  };

  template<numeric T, int min, int max>
  bool operator!=(const StaticallyBounded<T, min, max>& lhs, 
                  const StaticallyBounded<T, min, max>& rhs)
                  {
                    return static_cast<T>(lhs) != static_cast<T>(rhs);
                  };                 

  /// A numeric type with dynamic limits
  /// Limits are only enforced on assignments, meaning it should behave like a numeric type T in all other respects
  /// (under arithmetic operations, etc.) i.e. the result of a+b can be outside the limits.
  template<numeric T>
  struct DynamicallyBounded {
    // You must initialize with default value and limits
    DynamicallyBounded() = delete;
    // For construction, max is changed if min is largest.
    DynamicallyBounded(T init_val, T min, T max) : min_(min), max_(max) {
      max_ = std::max(min_, max_);
      value_ = std::clamp(init_val, min, max);
    } 

    // Getters and setters for limits
    // New limits can be determined run-time.
    T min() const {return min_;};
    void min(const T new_min){
      if (new_min <= max_) min_ = new_min;
    }
    T max() const {return max_;};
    void max(const T new_max){
      if (min_ <= new_max) max_ = new_max;
    }

    void operator=(const T in)
    {
      value_ = std::clamp(in, min_, max_);
    }
    void operator+=(const T in)
    {
      operator=(this->value_ + in);
    }
    void operator-=(const T in)
    {
      operator=(this->value_ - in);
    }
    void operator*=(const T in)
    {
      operator=(this->value_ * in);
    }
    void operator/=(const T in)
    {
      operator=(this->value_ / in);
    }
    void operator++()
    {
      operator=(this->value_ + static_cast<T>(1));
    }
    void operator--()
    {
      operator=(this->value_ - static_cast<T>(1));
    }

    operator T() const noexcept
    {
      return value_;
    }

  private:
    T value_;
    T min_;
    T max_;
  };

  // Comparison
  template<numeric T>
  bool operator==(const DynamicallyBounded<T>& lhs, 
                  const DynamicallyBounded<T>& rhs)
                  {
                    return static_cast<T>(lhs) == static_cast<T>(rhs) && lhs.min() == rhs.min() && lhs.max() == rhs.max();
                  };

  template<numeric T>
  bool operator!=(const DynamicallyBounded<T>& lhs, 
                  const DynamicallyBounded<T>& rhs)
                  {
                    return static_cast<T>(lhs) != static_cast<T>(rhs) || lhs.min() != rhs.min() || lhs.max() != rhs.max();
                  };

} // namespace otto::util
