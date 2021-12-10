#pragma once

#include "../services/context.hpp"
#include "../services/provider.hpp"
#include "action.hpp"

namespace otto::itc {

  template<AnAction Action>
  struct Sender<Action> : Provider<action_service<Action>> {
    using Provider<action_service<Action>>::Provider;

    /// The receivers this producer is currently linked to
    const std::vector<Receiver<Action>*>& receivers() const noexcept
    {
      return Provider<action_service<Action>>::accessors();
    }

    /// Send an action to all linked consumers
    void send(Action action) noexcept
    {
      for (Receiver<Action>* r : receivers()) r->internal_send(std::move(action));
    }
  };

  template<AnAction... Actions>
  struct Sender : Sender<Actions>... {
    Sender(Context& ch) : Sender<Actions>(ch)... {}

    /// Send an action to all linked consumers
    template<util::one_of<Actions...> Action>
    void send(Action action) noexcept
    {
      Sender<Action>::send(std::move(action));
    }
  };

} // namespace otto::itc
