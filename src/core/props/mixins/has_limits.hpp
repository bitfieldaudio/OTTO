#pragma once

#include <better_enum.hpp>

#include "util/algorithm.hpp"
#include <nanorange.hpp>

#include "services/log_manager.hpp"

#include "../internal/mixin_macros.hpp"
#include "../internal/property.hpp"


namespace otto::core::props {

  namespace detail {
    template<typename T>
    T from_integral(const util::enum_decay_t<T>& t)
    {
      if constexpr (util::BetterEnum::is<T>) {
        return T::_from_integral(t);
      } else {
        return t;
      }
    }

    template<typename T>
    struct limits {
      static constexpr auto min()
      {
        if constexpr (util::BetterEnum::is<T>) {
          auto vals = T::_values();
          auto iter = nano::min_element(vals);
          if (iter == vals.end()) return T::_values()[0]._to_integral();
          return util::underlying(*iter);
        } else {
          return std::numeric_limits<T>::min();
        }
      }
      static constexpr auto max()
      {
        if constexpr (util::BetterEnum::is<T>) {
          auto vals = T::_values();
          auto iter = nano::max_element(vals);
          if (iter == vals.end()) return T::_values()[T::_size() - 1]._to_integral();
          return util::underlying(*iter);
        } else {
          return std::numeric_limits<T>::max();
        }
      }
    };

  } // namespace detail

  OTTO_PROPS_MIXIN(has_limits);

  template<>
  struct mixin::hooks<has_limits> {
    struct on_exceeded {
      template<typename HookTag, typename Val, ::otto::core::props::HookOrder HO>
      using type =
        typename hook<util::enum_decay_t<Val>>::template type<HookTag, util::enum_decay_t<Val>, HO>;
    };
  };

  /// Shorthand for has_limits::init
  template<typename Min, typename Max>
  auto limits(const Min& min, const Max& max)
  {
    return has_limits::init(min, max);
  }

  OTTO_PROPS_MIXIN_LEAF (has_limits) {
    OTTO_PROPS_MIXIN_DECLS(has_limits);

    static_assert(util::is_less_than_comparable_v<value_type>,
                  "Property type must be less than comparable for has_limits");

    static_assert(util::is_greater_than_comparable_v<value_type>,
                  "Property type must be greater than comparable for has_limits");

    void init(const value_type& pmin, const value_type& pmax)
    {
      min = util::underlying(pmin);
      max = util::underlying(pmax);
    }

    void on_hook(hook<common::hooks::on_set, HookOrder::Middle> & hook)
    {
      auto& val = hook.value();
      if (util::underlying(val) < min) {
        auto hv = run_hook<hooks::on_exceeded>(util::underlying(val));
        hook.value() = detail::from_integral<value_type>(hv == util::underlying(val) ? min : hv);
      } else if (util::underlying(val) > max) {
        auto hv = run_hook<hooks::on_exceeded>(util::underlying(val));
        hook.value() = detail::from_integral<value_type>(hv == util::underlying(val) ? max : hv);
      }
    }

    float normalize() const
    {
      auto& prop = static_cast<property_type const&>(*this);
      return (prop.get() - min) / float(max - min);
    }

    util::enum_decay_t<value_type> min = detail::limits<value_type>::min();
    util::enum_decay_t<value_type> max = detail::limits<value_type>::max();
  };

} // namespace otto::core::props
