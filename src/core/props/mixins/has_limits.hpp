#pragma once

#include "services/log_manager.hpp"

#include "../internal/mixin_macros.hpp"
#include "../internal/property.hpp"

namespace otto::core::props {

  OTTO_PROPS_MIXIN(has_limits);

  template<>
  struct mixin::hooks<has_limits> {
    struct on_exceeded {
      template<typename HookTag, typename Val, ::otto::core::props::HookOrder HO>
      using type = typename hook<util::enum_decay_t<Val>>::template type<HookTag, util::enum_decay_t<Val>, HO>;
    };
  };

  /// Shorthand for has_limits::init
  template<typename Min, typename Max>
  auto limits(const Min& min, const Max& max) {
    return has_limits::init(min, max);
  }

  OTTO_PROPS_MIXIN_LEAF (has_limits) {
    OTTO_PROPS_MIXIN_DECLS(has_limits);

    static_assert(std::is_enum_v<value_type> || util::is_less_than_comparable_v<value_type>,
                  "Property type must be less than comparable for has_limits");

    static_assert(std::is_enum_v<value_type> || util::is_greater_than_comparable_v<value_type>,
                  "Property type must be greater than comparable for has_limits");

    void init(const value_type& pmin, const value_type& pmax)
    {
      min = util::underlying(pmin);
      max = util::underlying(pmax);
    }

    void on_hook(hook<common::hooks::on_set, HookOrder::Early> & hook)
    {
      auto& val = hook.value();
      if (util::underlying(val) < min) {
        auto hv = run_hook<hooks::on_exceeded>(util::underlying(val));
        hook.value() = static_cast<value_type>(hv == util::underlying(val) ? min : hv);
      } else if (util::underlying(val) > max) {
        auto hv = run_hook<hooks::on_exceeded>(util::underlying(val));
        hook.value() = static_cast<value_type>(hv == util::underlying(val) ? max : hv);
      }
    }

    value_type normalize() const
    {
      static_assert(!std::is_enum_v<value_type>,
                    "has_limits::normalize() is unavaliable for enums");
      auto& prop = static_cast<property_type const&>(*this);
      return (prop.get() - min) / (max - min);
    }

    util::enum_decay_t<value_type> min = std::numeric_limits<util::enum_decay_t<value_type>>::min();
    util::enum_decay_t<value_type> max = std::numeric_limits<util::enum_decay_t<value_type>>::max();
  };

} // namespace otto::core::props
