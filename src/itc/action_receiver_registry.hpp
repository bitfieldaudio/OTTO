#pragma once

#include "action.hpp"

namespace otto::itc {

  template<typename Action>
  struct ActionReceiverRegistry;

  /// A registry of action receivers
  template<typename Tag, typename... Args>
  struct ActionReceiverRegistry<Action<Tag, Args...>> {
    using Action = Action<Tag, Args...>;

    /// Add to the registry.
    ///
    /// Precondition: Registry must not contain `rec` already
    void add(ActionReceiver<Action>* rec) noexcept
    {
      receivers.push_back(rec);
    }

    void remove(ActionReceiver<Action>* rec) noexcept
    {
      util::erase(receivers, rec);
    }

    bool contains(ActionReceiver<Action>* rec) noexcept
    {
      return nano::find(receivers, rec) != receivers.end();
    }

    void call_all(typename Action::args_tuple args) noexcept
    {
      for (auto& receiver : receivers) {
        std::apply([&](Args... args) { receiver->action(Action(), args...); }, args);
      }
    }

  private:
    std::vector<ActionReceiver<Action>*> receivers;
  };

} // namespace otto::itc
