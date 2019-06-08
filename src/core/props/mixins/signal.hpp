#pragma once

#include <vector>

#include "util/utility.hpp"

#include "../internal/mixin_macros.hpp"
#include "../internal/property.hpp"

#include "services/log_manager.hpp"
#include "util/algorithm.hpp"

#include "util/signals.hpp"

namespace otto::core::props {

  OTTO_PROPS_MIXIN(signal);

  OTTO_PROPS_MIXIN_LEAF (signal) {
    OTTO_PROPS_MIXIN_DECLS(signal);

    void on_hook(hook<common::hooks::after_set, HookOrder::After> & hook)
    {
      _on_change.emit(as_prop().get());
    }

    util::Signal<value_type, value_type>& on_change()
    {
      return _on_change;
    }

  private:
    util::Signal<value_type, value_type> _on_change;
  };

} // namespace otto::core::props
