#pragma once

#include "../internal/property.hpp"
#include "../internal/mixin_macros.hpp"

#include <cmath>

namespace otto::core::props {

  OTTO_PROPS_MIXIN(pow2);

  OTTO_PROPS_MIXIN_LEAF(pow2) {
    OTTO_PROPS_MIXIN_DECLS(pow2);

    value_type pow2() const
    {
      return pow2_;
    }

    void on_hook(hook<common::hooks::on_set, HookOrder::After> const hook)
    {
      pow2_ = std::pow(2, hook.value());
    }

  private:
    value_type pow2_;
  };
};
