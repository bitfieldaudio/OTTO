#pragma once

#include "util/utility.hpp"
#include "../internal/property.hpp"
#include "../internal/mixin_macros.hpp"

#include <cmath>

#include "steppable.hpp"

namespace otto::core::props {

    /// special_value gives precedence to a single value. If this is hit,
    /// it takes a number of steps to move further
    // TODO: Finish it!

    OTTO_PROPS_MIXIN(special_value, REQUIRES(steppable), HOOKS((on_step, value_type)));

    /// Shorthand for special_value::init(ss)
    template<typename VT>
    auto special_value(const VT& ss) {
      return special_value::init(ss);
    }

    OTTO_PROPS_MIXIN_LEAF (special_value) {
        OTTO_PROPS_MIXIN_DECLS(special_value);

       /// Necessary assertions have been done in the required 'steppable' mixin

        // The special value.
        void init(value_type p_value = value_type{0}, int p_strength)
        {
          // unwrap enums
          value = util::underlying(p_value);
          strength = p_strength;
        }

        void on_hook(hook<steppable::hooks::on_step> & hook)
        {
          auto& prop = static_cast<property_type&>(*this);
          // For float values, this should be within some threshold?
          if (prop.get() == value && !caught) {
            counts = strength;
            caught = true;
            prop.set(value);
          }

          if (caught && counts > 0) {
            counts--;
            prop.set(value);
          }

          if (caught && counts = 0) {
            caught = false;

          }

        }

        util::enum_decay_t<value_type> value = 1;
        int strength = 0;
        int counts = 0;
        bool caught = false;
    };

} // namespace otto::core::props
