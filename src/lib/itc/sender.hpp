#pragma once

#include "channel.hpp"
#include "event.hpp"

namespace otto::itc {

  template<AnEvent Event>
  struct Sender<Event> : detail::SenderBase {
    Sender(Channel& channel) : channel_(&channel)
    {
      channel.register_sender(this);
    }

    // Non-copyable
    Sender(const Sender&) = delete;
    Sender& operator=(const Sender&) = delete;

    ~Sender() noexcept
    {
      channel_->unregister_sender(this);
    }

    /// The receivers this producer is currently linked to
    const std::vector<Receiver<Event>*>& receivers() const noexcept
    {
      return receivers_;
    }

    /// Send an event to all linked consumers
    void send(Event event) noexcept
    {
      for (Receiver<Event>* r : receivers_) r->internal_send(std::move(event));
    }

    void serialize_into(json::value&) const override {}
    void deserialize_from(const json::value&) override {}

  private:
    friend linker;

    Channel* channel_;
    std::vector<Receiver<Event>*> receivers_;
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
