#pragma once

#include "channel.hpp"
#include "event.hpp"
#include "provider.hpp"

namespace otto::itc {

  template<AnEvent Event>
  struct Sender<Event> : Provider<event_service<Event>> {
    using Provider<event_service<Event>>::Provider;

    /// The receivers this producer is currently linked to
    const std::vector<Receiver<Event>*>& receivers() const noexcept
    {
      return Provider<event_service<Event>>::accessors();
    }

    /// Send an event to all linked consumers
    void send(Event event) noexcept
    {
      for (Receiver<Event>* r : receivers()) r->internal_send(std::move(event));
    }
  };

  template<AnEvent... Events>
  struct Sender : Sender<Events>... {
    Sender(Channel& ch) : Sender<Events>(ch)... {}

    /// Send an event to all linked consumers
    template<util::one_of<Events...> Event>
    void send(Event event) noexcept
    {
      Sender<Event>::send(std::move(event));
    }
  };

} // namespace otto::itc
