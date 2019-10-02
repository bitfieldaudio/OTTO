#pragma once

#include "../internal/mixin_macros.hpp"
#include "../internal/property.hpp"

#include "has_limits.hpp"
#include "steppable.hpp"

#include "util/math.hpp"

namespace otto::core::props {

  OTTO_PROPS_MIXIN(wrap, REQUIRES(has_limits));

  OTTO_PROPS_MIXIN_LEAF (wrap) {
    OTTO_PROPS_MIXIN_DECLS(wrap);

    void on_hook(hook<has_limits::hooks::on_exceeded> & hook)
    {
      if constexpr (!std::is_floating_point_v<value_type>) {
        auto& hl = this->as<has_limits>();
        hook.value() = wrap_value(hook.value(), hl.min, hl.max);
      }
    }

    void on_hook(hook<common::hooks::on_set, HookOrder::Early> & hook)
    {
      if constexpr (std::is_floating_point_v<value_type>) {
        auto& hl = this->as<has_limits>();
        hook.value() = wrap_value(hook.value(), hl.min, hl.max);
      }
    }

  private:
    using decayed = util::enum_decay_t<value_type>;

    decayed wrap_value(decayed value, decayed min, decayed max)
    {
      decayed length = max - min;
      if constexpr (!std::is_floating_point_v<value_type>) {
        length += 1;
      }
      if (value < min || value >= max) {
        value = min + util::math::modulo((value - min), length);
      }
      return value;
    }
  };
} // namespace otto::core::props
