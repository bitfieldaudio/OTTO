#pragma once

#include "services/logger.hpp"

#include "../internal/mixin_macros.hpp"
#include "../internal/property.hpp"

namespace otto::core::props {

  OTTO_PROPS_MIXIN(has_limits);

  template<>
  struct mixin::hooks<has_limits> {
    struct on_exceeded : hook<value_type> {};
  };

  OTTO_PROPS_MIXIN_LEAF (has_limits) {
    OTTO_PROPS_MIXIN_DECLS(has_limits);

    void init(const value_type& pmin, const value_type& pmax)
    {
      min = pmin;
      max = pmax;
    }

    void on_hook(hook<common::hooks::on_set, HookOrder::Early> & hook)
    {
      auto& val = hook.value();
      if (val < min) {
        auto hv      = run_hook<hooks::on_exceeded>(val);
        hook.value() = hv == val ? min : hv;
      } else if (val > max) {
        auto hv      = run_hook<hooks::on_exceeded>(val);
        hook.value() = hv == val ? max : hv;
      }
    }

    value_type normalize() const
    {
      auto& prop = dynamic_cast<property_type const&>(*this);
      return (prop.get() - min) / (max - min);
    }

    value_type min;
    value_type max;
  };

} // namespace otto::core::props
