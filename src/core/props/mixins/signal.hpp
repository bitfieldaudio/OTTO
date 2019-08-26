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

    struct Signal : util::Signal<value_type, value_type> {
      using Super = util::Signal<value_type, value_type>;

      struct SlotRef : Super::SlotRef {
        using SuperSR = typename Super::SlotRef;

        SlotRef(SuperSR&& s, Signal& owner) : SuperSR(s), owner(owner){};

        using SuperSR::call_now;
        void call_now(value_type new_val)
        {
          call_now(new_val, new_val);
        }
        void call_now()
        {
          call_now(owner.owner.as_prop().get());
        }

      private:
        Signal& owner;
      };

      Signal(self_type& owner) : owner(owner) {}

      using Super::connect;
      SlotRef connect(std::function<void(value_type)> f)
      {
        return {connect([f = std::move(f)](value_type new_val, value_type old_val) { return f(new_val); }), *this};
      }

      SlotRef connect(std::function<void()> f)
      {
        return {connect([f = std::move(f)](value_type new_val, value_type old_val) { return f(); }), *this};
      }

      self_type& owner;
    };

    void on_hook(hook<common::hooks::after_set, HookOrder::After> & hook)
    {
      _on_change.emit(as_prop().get(), hook.value());
    }

    Signal& on_change()
    {
      return _on_change;
    }

  private:
    Signal _on_change{*this};
  };

} // namespace otto::core::props
