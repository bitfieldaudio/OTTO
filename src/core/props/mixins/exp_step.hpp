#pragma once

#include "util/utility.hpp"
#include "../internal/property.hpp"
#include "../internal/mixin_macros.hpp"

#include "has_limits.hpp"

#include <cmath>

#include "steppable.hpp"

namespace otto::core::props {

    /// exp_steppable implements a way of stepping that has lower step size
    /// at the bottom of the has_limits interval

    OTTO_PROPS_MIXIN(exp_steppable, REQUIRES(has_limits), HOOKS((on_step, value_type)));

    /// Shorthand for exp_steppable::init(ss)
    template<typename VT>
    auto exp_step_size(const VT& ss) {
      return exp_steppable::init(ss);
    }

    OTTO_PROPS_MIXIN_LEAF (exp_steppable) {
        OTTO_PROPS_MIXIN_DECLS(exp_steppable);

        static_assert(std::is_same_v<value_type, float> || std::is_same_v<value_type, int>,
                      "The 'exp_steppable' mixin requires a float or int type");

        // The underlying step_size.
        void init(value_type p_step_size = value_type{1})
        {
          // unwrap enums
          step_size = util::underlying(p_step_size);
        }

        void exp_step(int n = 1)
        {
          auto& prop = static_cast<property_type&>(*this);
          auto new_value = run_hook<hooks::on_step>([&] () -> value_type {
            auto& hl = this->as<has_limits>();
            return std::pow( std::sqrt(prop.get() - hl.min) + n * step_size, 2 ) + hl.min;
            // For true exponential behaviour. This grows too fast though, methinks
            return  (prop.get() - hl.min + 1) * exp( n * step_size ) + hl.min - 1;
          }());
          prop.set(new_value);
        }

        util::enum_decay_t<value_type> step_size = 1;
    };

} // namespace otto::core::props
