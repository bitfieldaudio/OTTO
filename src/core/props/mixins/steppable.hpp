#pragma once

#include <vector>

#include "util/utility.hpp"

#include "../internal/mixin_macros.hpp"
#include "../internal/property.hpp"

namespace otto::core::props {

  OTTO_PROPS_MIXIN(steppable);

  OTTO_PROPS_MIXIN_LEAF (steppable) {
    OTTO_PROPS_MIXIN_DECLS(steppable);

    static_assert(util::is_number_or_enum_v<value_type> || std::is_same_v<value_type, bool>,
                  "The 'steppable' mixin requires a number, bool or enum type");

    void init(value_type p_step_size = value_type{1})
    {
      // unwrap enums
      step_size = util::underlying(p_step_size);
    }

    void step(int n = 1)
    {
      auto& prop = dynamic_cast<property_type&>(*this);
      if constexpr (std::is_same_v<bool, value_type>) {
        prop.set((prop.get() + n) % 2);
      } else if constexpr (std::is_enum_v<value_type>) {
        prop.set(static_cast<value_type>(util::underlying(prop.get()) + n * step_size));
      } else {
        prop.set(prop.get() + n * step_size);
      }
    }

    util::enum_decay_t<value_type> step_size = 1;
  };

} // namespace otto::core::props
