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
      auto& hl = this->as<has_limits>();
      auto length = hl.max - hl.min + 1;
      if (hook.value() < hl.min || hook.value() > hl.max) {
        // hl.min + (hook.value() - (hl.max + step_size));
        hook.value() = hl.min + util::math::modulo((hook.value() - hl.min), length);
      }
    }
  };
} // namespace otto::core::props
