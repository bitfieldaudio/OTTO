#pragma once

#include "../internal/property.hpp"
#include "../internal/mixin_macros.hpp"

#include <cmath>

#include "steppable.hpp"

namespace otto::core::props {

  OTTO_PROPS_MIXIN(pow2, REQUIRES(steppable));

  OTTO_PROPS_MIXIN_LEAF(pow2) {
    OTTO_PROPS_MIXIN_DECLS(pow2);

    value_type pow_2() const
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

  OTTO_PROPS_MIXIN(exp_step);

  OTTO_PROPS_MIXIN_LEAF(exp_step) {
    OTTO_PROPS_MIXIN_DECLS(exp_step);

    auto on_hook(hook<steppable::hooks::on_step, HookOrder::After> const & hook)
    {
      auto& prop = dynamic_cast<property_type&>(*this);
      return prop.get() * std::pow((float) as<steppable>().step_size, (float) as<steppable>()._current_step_count);
    }

  };}
