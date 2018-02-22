#pragma once

#include "../internal/property.hpp"
#include "../internal/mixin_macros.hpp"

#include "has_limits.hpp"

namespace otto::core::props {

  OTTO_PROPS_MIXIN(wrap, REQUIRES(has_limits));

  OTTO_PROPS_MIXIN_LEAF(wrap) {
    OTTO_PROPS_MIXIN_DECLS(wrap);

    void on_hook(hook<has_limits::hooks::on_exceeded> hook) {
      auto& hl = this->as<has_limits>();
      if (hook.value() < hl.min) {
        hook.value() = hl.max - (hl.min - hook.value());
      } else if (hook.value() > hl.max) {
        hook.value() = hl.min + (hook.value() - hl.max);
      }
    }
  };
}
