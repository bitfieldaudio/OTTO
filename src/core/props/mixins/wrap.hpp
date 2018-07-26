#pragma once

#include "../internal/mixin_macros.hpp"
#include "../internal/property.hpp"

#include "has_limits.hpp"
#include "steppable.hpp"

namespace otto::core::props {

  OTTO_PROPS_MIXIN(wrap, REQUIRES(has_limits));

  OTTO_PROPS_MIXIN_LEAF (wrap) {
    OTTO_PROPS_MIXIN_DECLS(wrap);

    void on_hook(hook<has_limits::hooks::on_exceeded> & hook)
    {
      auto& hl = this->as<has_limits>();
      if (hook.value() < hl.min) {
        hook.value() =
          hl.max - ((hl.min - (is<steppable>() ? as<steppable>().step_size : 1)) - hook.value());
      } else if (hook.value() > hl.max) {
        hook.value() =
          hl.min + (hook.value() - (hl.max + (is<steppable>() ? as<steppable>().step_size : 1)));
      }
    }
  };
} // namespace otto::core::props
