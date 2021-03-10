#pragma once

#include "channel.hpp"
#include "event.hpp"

namespace otto::itc {

  template<AnEvent Event>
  struct Sender<Event> {
    Sender(TypedChannel<Event>& ch)
    {
      ch.set_sender(this);
    }

    Sender(ChannelGroup& channels) : Sender(channels.get<Event>()) {}

    // Non-copyable
    Sender(const Sender&) = delete;
    Sender& operator=(const Sender&) = delete;

    ~Sender() noexcept
    {
      for (TypedChannel<Event>* ch : channels_) {
        ch->set_sender(nullptr);
      }
    }

    /// The channels this producer is currently linked to
    const std::vector<TypedChannel<Event>*>& channels() const noexcept
    {
      return channels_;
    }

    /// Send an event to all linked consumers
    void send(Event event) noexcept
    {
      for (TypedChannel<Event>* ch : channels_) ch->internal_send(std::move(event));
    }

  private:
    friend TypedChannel<Event>;

    /// Called only from set_producer in TypedChannel
    void internal_add_channel(TypedChannel<Event>& ch)
    {
      channels_.push_back(ch);
    }

    /// Called only from Channel destructor
    void internal_remove_channel(TypedChannel<Event>& ch)
    {
      std::erase(channels_, &ch);
    }

    std::vector<TypedChannel<Event>*> channels_;
  };

  template<AnEvent... Events>
  struct Sender : Sender<Events>... {
    Sender(ChannelGroup& ch) : Sender<Events>(ch)... {}

    /// Send an event to all linked consumers
    template<util::one_of<Events...> Event>
    void send(Event event) noexcept
    {
      Sender<Event>::send(std::move(event));
    }
  };

} // namespace otto::itc
