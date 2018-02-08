#pragma once

#include <vector>

#include "util/utility.hpp"

#include "../internal/mixin_macros.hpp"
#include "../internal/property.hpp"

#include "has_value.hpp"

namespace otto::core::props::mixins {

  OTTO_PROPS_MIXIN(steppable, REQUIRES(steppable, has_value))
  {
    OTTO_PROPS_MIXIN_DECLS(steppable);

    static_assert(util::is_number_or_enum_v<value_type>,
                  "The 'steppable' mixin requires a number or enum type");

    void init(value_type p_step_size = value_type{1})
    {
      step_size = p_step_size;
    }

    void step(int n)
    {
      as<has_value>().set(as<has_value>().get() + n * step_size);
    }

    value_type step_size;
  };

} // namespace otto::core::props::mixins
