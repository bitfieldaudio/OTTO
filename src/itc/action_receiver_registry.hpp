#pragma once

#include "action.hpp"
#include "itc/action_bus.hpp"
#include "util/flat_map.hpp"

namespace otto::itc {

  template<typename Action>
  struct ActionReceiverRegistry;

  /// A registry of action receivers
  template<typename Tag, typename... Args>
  struct ActionReceiverRegistry<Action<Tag, Args...>> {
    using Action = Action<Tag, Args...>;

    std::size_t size() const noexcept
    {
      return receivers.size();
    }

    /// Add to the registry.
    ///
    /// Precondition: Registry must not contain `rec` already
    void add(itc::ActionChannel channel, ActionReceiver<Action>* rec) noexcept
    {
      receivers.insert(channel, {}).first->insert(rec);
    }

    /// Removes an ActionReceiver from all channels
    void remove_all(ActionReceiver<Action>* rec) noexcept
    {
      // Note that empty sets are being left. They can be deleted afterwards if needed
      for (auto& channel : receivers.values()) {
        channel.erase(rec);
      }
    }

    void call_all(typename Action::args_tuple args) noexcept
    {
      for (auto& channel : receivers) {
        for (auto& actrec : channel) {
          std::apply([&](Args... args) { actrec->action(Action(), args...); }, args);  
        }
      }
    }

  private:
    util::flat_map<itc::ActionChannel, util::flat_set<ActionReceiver<Action>*>> receivers;
  };

} // namespace otto::itc
