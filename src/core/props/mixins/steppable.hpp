#pragma once

#include <vector>
#include <tuple>

#include "util/utility.hpp"

#include "../internal/mixin_macros.hpp"
#include "../internal/property.hpp"

namespace otto::core::props {

  OTTO_PROPS_MIXIN(steppable, HOOKS((on_step, value_type)));

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
      _current_step_count = n;
      auto new_value = run_hook<hooks::on_step>([&] () -> value_type {
        if constexpr (std::is_same_v<bool, value_type>) {
          return (prop.get() + n) % 2;
        } else if constexpr (std::is_enum_v<value_type>) {
          return static_cast<value_type>(util::underlying(prop.get()) + n * step_size);
        } else {
          return prop.get() + n * step_size;
        }
      }());
      prop.set(new_value);
    }

    util::enum_decay_t<value_type> step_size = 1;
    int _current_step_count;
  };

} // namespace otto::core::props
