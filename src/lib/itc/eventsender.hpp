#pragma once

#include "reducer.hpp"

namespace otto::itc {

  /// Converts input events to actions
  template<AnEvent... Events>
  struct EventSender;

  template<AnEvent Event>
  struct EventSender<Event> : private Sender<Event>, IEventHandler<Event> {
    using Sender<Event>::Sender;
    void handle(Event e) override
    {
      this->send(std::move(e));
    }
  };

  template<AnEvent... Events>
  struct EventSender : EventSender<Events>... {
    EventSender(Channel& ch) : EventSender<Events>(ch)... {}
    using EventSender<Events>::handle...;
  };
} // namespace otto::itc
