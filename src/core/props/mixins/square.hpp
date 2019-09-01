#pragma once

#include "../internal/property.hpp"
#include "../internal/mixin_macros.hpp"

#include <cmath>

#include "steppable.hpp"

namespace otto::core::props {

  OTTO_PROPS_MIXIN(has_square, REQUIRES(steppable)) {
    OTTO_PROPS_MIXIN_DECLS(has_square);

    value_type square() const
    {
      return square_;
    }

    void on_hook(hook<common::hooks::on_set, HookOrder::After> const hook)
    {
      square_ = hook.value() * hook.value();
    }

  private:
    value_type square_;
  };

}
