#pragma once

#include "../internal/mixin_macros.hpp"
#include "../internal/property.hpp"

#include "util/observable.hpp"

namespace otto::core::props {

  OTTO_PROPS_MIXIN(observable);

  OTTO_PROPS_MIXIN_LEAF (observable) : util::Observable<ValueType> {
    OTTO_PROPS_MIXIN_DECLS(observable);

    void on_hook(hook<common::hooks::after_set, HookOrder::After> & hook)
    {
      this->notify_observers();
    }

  private:
    value_type get_value() final {
      return as_prop().get();
    }
  };

} // namespace otto::core::props
