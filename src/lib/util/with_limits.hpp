#pragma once
#include <algorithm>
#include <cstddef>

#include "lib/util/concepts.hpp"
#include "lib/util/enum.hpp"
#include "lib/util/serialization.hpp"

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

  struct dyn_bounds {
    template<numeric T>
    struct type {
      constexpr type(T min, T max) noexcept : min_(min), max_(max) {}

      // Getters and setters for limits
      // New limits can be determined run-time.
      constexpr T min() const noexcept
      {
        return min_;
      }
      constexpr void min(const T new_min) noexcept
      {
        if (new_min <= max_) min_ = new_min;
      }
      constexpr T max() const noexcept
      {
        return max_;
      }
      constexpr void max(const T new_max) noexcept
      {
        if (min_ <= new_max) max_ = new_max;
      }

      constexpr bool operator==(const type&) const = default;

    protected:
      void serialize_into(json::value& val, T value) const
      {
        util::serialize_into(val["value"], value);
        util::serialize_into(val["min"], min_);
        util::serialize_into(val["max"], max_);
      }

      void deserialize_from(const json::value& val, T& value)
      {
        util::deserialize_from(val["value"], value);
        util::deserialize_from(val["min"], min_);
        util::deserialize_from(val["max"], max_);
      }

    private:
      T min_ = 0;
      T max_ = 0;
    };
  };

  template<int Min, int Max>
  struct bounds {
    template<numeric T>
    struct type {
      static constexpr T min() noexcept
      {
        return static_cast<T>(Min);
      }
      static constexpr T max() noexcept
      {
        return static_cast<T>(Max);
      }
      constexpr bool operator==(const type&) const = default;

    protected:
      void serialize_into(json::value& json, T value) const
      {
        util::serialize_into(json, value);
      }
      void deserialize_from(const json::value& json, T& val)
      {
        util::deserialize_from(json, val);
      }
    };
  };

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
  template<numeric T, typename BoundsTag = dyn_bounds, ABoundsPolicy BoundsPolicy = bounds_policies::clamp>
  struct Bounded : BoundsTag::template type<T> {
    using Bounds = typename BoundsTag::template type<T>;
    // You must initialize with default value
    Bounded() = delete;

    Bounded(T init_val, auto&&... args)                            //
      requires(std::is_constructible_v<Bounds, decltype(args)...>) //
      : Bounds(FWD(args)...), value_(BoundsPolicy::check_bounds(init_val, Bounds::min(), Bounds::max()))
    {}

    Bounded& operator=(const T in)
    {
      value_ = BoundsPolicy::check_bounds(in, Bounds::min(), Bounds::max());
      return *this;
    }

    Bounded& operator+=(const T in)
    {
      operator=(value_ + in);
      return *this;
    }
    Bounded& operator-=(const T in)
    {
      operator=(value_ - in);
      return *this;
    }
    Bounded& operator*=(const T in)
    {
      operator=(value_* in);
      return *this;
    }
    Bounded& operator/=(const T in)
    {
      operator=(value_ / in);
      return *this;
    }
    Bounded& operator++()
    {
      operator=(value_ + static_cast<T>(1));
      return *this;
    }
    Bounded operator++(int)
    {
      auto tmp = *this;
      operator=(value_ + static_cast<T>(1));
      return tmp;
    }
    Bounded& operator--()
    {
      operator=(value_ - static_cast<T>(1));
      return *this;
    }
    Bounded operator--(int)
    {
      auto tmp = *this;
      operator=(value_ - static_cast<T>(1));
      return tmp;
    }
    // If needed, binary operators can be added

    operator T() const noexcept
    {
      return value_;
    }

    [[nodiscard]] float normalize() const noexcept
    {
      return static_cast<float>(value_ - Bounds::min()) / static_cast<float>(Bounds::max() - Bounds::min());
    }

    void serialize_into(json::value& json) const
    {
      Bounds::serialize_into(json, value_);
    }
    void deserialize_from(const json::value& json)
    {
      Bounds::deserialize_from(json, value_);
    }

    // Comparison
    // Note: I think it is best if we don't allow comparisons with other Bounded<> with different limits.
    bool operator==(const Bounded&) const = default;
    auto operator<=>(const Bounded&) const = default;

    template<typename U>
    requires(!std::is_same_v<std::remove_cvref_t<U>, Bounded> && std::equality_comparable_with<U, T>) //
      bool
      operator==(const U& r) const noexcept
    {
      return value_ == r;
    };
    template<typename U>
    requires(!std::is_same_v<std::remove_cvref_t<U>, Bounded> && util::three_way_comparable_with<U, T>) //
      auto
      operator<=>(const U& r) const noexcept
    {
      return value_ <=> r;
    };

  private:
    T value_;
  };

  template<numeric T, int min, int max, ABoundsPolicy BP = bounds_policies::clamp>
  using StaticallyBounded = Bounded<T, bounds<min, max>, BP>;

  template<numeric T, ABoundsPolicy BP = bounds_policies::clamp>
  using DynamicallyBounded = Bounded<T, dyn_bounds, BP>;

  /// An incrementable, wrappable enum
  template<util::AnEnum Enum, ABoundsPolicy BP = bounds_policies::clamp>
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
        index_ = BP::check_bounds(index_, 0, int(util::enum_count<Enum>() - 1));
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

    SelectableEnum& operator+=(const int inc)
    {
      index_ = BP::check_bounds(index_ + inc, int(0), int(util::enum_count<Enum>() - 1));
      return *this;
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

    [[nodiscard]] std::size_t index() const
    {
      return index_;
    }

    void serialize_into(json::value& val) const
    {
      util::serialize_into(val, operator Enum());
    }

    void deserialize_from(const json::value& val)
    {
      Enum e = operator Enum();
      util::deserialize_from(val, e);
      index_ = util::enum_index(e).value();
    }

  private:
    int index_;
  };

} // namespace otto::util
