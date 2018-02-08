#pragma once

#include "../internal/property.hpp"
#include "../internal/mixin_macros.hpp"

#include "has_value.hpp"

namespace otto::core::props::mixins {

  OTTO_PROPS_MIXIN(has_limits)
  {
    OTTO_PROPS_MIXIN_DECLS(has_limits);

    void init(const value_type& pmin, const value_type& pmax)
    {
      min = pmin;
      max = pmax;
    }

    void on_hook(hook<has_value::hooks::on_set, HookOrder::Early> & hook)
    {
      hook.value() = std::clamp(hook.value(), min, max);
    }

    value_type min;
    value_type max;
  };

}
