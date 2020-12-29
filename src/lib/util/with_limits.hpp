#pragma once
#include <algorithm>
#include <cstddef>

#include "lib/util/concepts.hpp"
#include "lib/util/enum.hpp"

#include "math.hpp"

namespace otto::util {

  namespace bounds_policies {
    struct wrap {
      template<typename T>
      static T check_bounds(T value, T min, T max)
      {
        if (value < min || value > max) {
          T length = (max) - (min);
          if constexpr (std::is_integral_v<T>) length += 1;
          return min + math::modulo(value - min, length);
        }
        return value;
      }
    };
    struct clamp {
      template<typename T>
      static T check_bounds(T value, T min, T max)
      {
        return std::clamp(value, min, max);
      }
    };
  } // namespace bounds_policies

  // clang-format off
  template<typename Policy>
  concept ABoundsPolicy = requires(int val, int min, int max) {
    { Policy::check_bounds(val, min, max) } ->std::same_as<int>;
  };
  // clang-format on

  /// A numeric type with static limits
  /// Limits are only enforced on assignments, meaning it should behave like a numeric type T in all other respects
  /// (under arithmetic operations, etc.) i.e. the result of a+b can be outside the limits.
  /// Note that the limits conceptually SHOULD be of type T, but floats cannot be used in this manner, see:
  /// http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2019/p1907r1.html
  /// Hence, integer limits must be used. If floats are needed, use the types with dynamic limits.
  /// TODO: This should be available in C++20, so we could remove this constraint.
  template<numeric T, int min, int max, ABoundsPolicy BoundsPolicy = bounds_policies::clamp>
  struct StaticallyBounded {
    // You must initialize with default value
    StaticallyBounded() = delete;
    StaticallyBounded(T init_val)
      : value_(std::clamp(static_cast<T>(init_val), static_cast<T>(min), static_cast<T>(max)))
    {}

    StaticallyBounded& operator=(const T in)
    {
      value_ = BoundsPolicy::check_bounds(in, static_cast<T>(min), static_cast<T>(max));
      return *this;
    }

    StaticallyBounded& operator+=(const T in)
    {
      operator=(this->value_ + in);
      return *this;
    }
    StaticallyBounded& operator-=(const T in)
    {
      operator=(this->value_ - in);
      return *this;
    }
    StaticallyBounded& operator*=(const T in)
    {
      operator=(this->value_* in);
      return *this;
    }
    StaticallyBounded& operator/=(const T in)
    {
      operator=(this->value_ / in);
      return *this;
    }
    StaticallyBounded& operator++()
    {
      operator=(this->value_ + static_cast<T>(1));
      return *this;
    }
    StaticallyBounded operator++(int)
    {
      auto tmp = *this;
      operator=(this->value_ + static_cast<T>(1));
      return tmp;
    }
    StaticallyBounded& operator--()
    {
      operator=(this->value_ - static_cast<T>(1));
      return *this;
    }
    StaticallyBounded operator--(int)
    {
      auto tmp = *this;
      operator=(this->value_ - static_cast<T>(1));
      return tmp;
    }
    // If needed, binary operators can be added

    operator T() const noexcept
    {
      return value_;
    }

    [[nodiscard]] float normalize() const noexcept
    {
      return static_cast<float>(value_ - min) / static_cast<float>(max - min);
    }

  private:
    T value_;
  };

  // Comparison
  // Note: I think it is best if we don't allow comparisons with other StaticallyBounded<> with different limits.
  template<numeric T, int min, int max, ABoundsPolicy BP>
  bool operator==(const StaticallyBounded<T, min, max, BP>& lhs, const StaticallyBounded<T, min, max, BP>& rhs)
  {
    return static_cast<T>(lhs) == static_cast<T>(rhs);
  }

  template<numeric T, int min, int max, ABoundsPolicy BP>
  bool operator!=(const StaticallyBounded<T, min, max, BP>& lhs, const StaticallyBounded<T, min, max, BP>& rhs)
  {
    return static_cast<T>(lhs) != static_cast<T>(rhs);
  }

  /// A numeric type with dynamic limits
  /// Limits are only enforced on assignments, meaning it should behave like a numeric type T in all other respects
  /// (under arithmetic operations, etc.) i.e. the result of a+b can be outside the limits.
  template<numeric T, ABoundsPolicy BoundsPolicy = bounds_policies::clamp>
  struct DynamicallyBounded {
    // You must initialize with default value and limits
    DynamicallyBounded() = delete;
    // For construction, max is changed if min is largest.
    DynamicallyBounded(T init_val, T min, T max)
      : value_(std::clamp(init_val, min, max)), min_(min), max_(std::max(min, max))
    {}

    // Getters and setters for limits
    // New limits can be determined run-time.
    T min() const
    {
      return min_;
    }
    void min(const T new_min)
    {
      if (new_min <= max_) min_ = new_min;
    }
    T max() const
    {
      return max_;
    }
    void max(const T new_max)
    {
      if (min_ <= new_max) max_ = new_max;
    }

    [[nodiscard]] float normalize() const noexcept
    {
      return static_cast<float>(value_ - min_) / static_cast<float>(max_ - min_);
    }

    DynamicallyBounded& operator=(const T in)
    {
      value_ = BoundsPolicy::check_bounds(in, min_, max_);
      return *this;
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
      operator=(this->value_* in);
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
  template<numeric T, ABoundsPolicy BP>
  bool operator==(const DynamicallyBounded<T, BP>& lhs, const DynamicallyBounded<T, BP>& rhs)
  {
    return static_cast<T>(lhs) == static_cast<T>(rhs) && lhs.min() == rhs.min() && lhs.max() == rhs.max();
  }

  template<numeric T, ABoundsPolicy BP>
  bool operator!=(const DynamicallyBounded<T, BP>& lhs, const DynamicallyBounded<T, BP>& rhs)
  {
    return static_cast<T>(lhs) != static_cast<T>(rhs) || lhs.min() != rhs.min() || lhs.max() != rhs.max();
  }

  /// An incrementable, wrappable enum
  template<util::AnEnum Enum, ABoundsPolicy BP>
  struct SelectableEnum {
    SelectableEnum(Enum e) : index_(util::enum_index(e).value()) {}

    operator Enum() const
    {
      return util::enum_value<Enum>(index_);
    }

    SelectableEnum& operator++()
    {
      index_++;
      if (index_ >= util::enum_count<Enum>()) {
        index_ = BP::check_bounds(index_, static_cast<std::size_t>(0), util::enum_count<Enum>() - 1);
      }
      return *this;
    }

    SelectableEnum operator++(int)
    {
      auto tmp = *this;
      index_++;
      if (index_ >= util::enum_count<Enum>()) {
        index_ = BP::check_bounds(index_, static_cast<std::size_t>(0), util::enum_count<Enum>() - 1);
      }
      return tmp;
    }

    SelectableEnum& operator--()
    {
      if (index_ == 0) {
        index_ = BP::check_bounds(-1, 0, static_cast<int>(util::enum_count<Enum>() - 1));
      } else {
        index_--;
      }
      return *this;
    }

    SelectableEnum operator--(int)
    {
      auto tmp = *this;
      if (index_ == 0) {
        index_ = BP::check_bounds(-1, 0, static_cast<int>(util::enum_count<Enum>() - 1));
      } else {
        index_--;
      }
      return tmp;
    }

    SelectableEnum& operator=(const Enum in)
    {
      index_ = util::enum_index(in).value();
      return *this;
    }

    bool operator==(const Enum in)
    {
      return in == util::enum_value<Enum>(index_);
    }

    bool operator!=(const Enum in)
    {
      return !(operator==(in));
    }

    const std::size_t index() const
    {
      return index_;
    }

  private:
    std::size_t index_;
  };

} // namespace otto::util