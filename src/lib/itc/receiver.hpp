#pragma once

#include "channel.hpp"
#include "event.hpp"

namespace otto::itc {

  template<AnEvent Event>
  struct Receiver<Event> : private virtual IDomain {
    Receiver(TypedChannel<Event>& ch) : channel_(&ch)
    {
      ch.internal_add_receiver(this);
    }

    Receiver(ChannelGroup& channels) : Receiver(channels.get<Event>()) {}

    Receiver(const Receiver&) = delete;
    Receiver& operator=(const Receiver&) = delete;

    virtual ~Receiver() noexcept
    {
      if (channel_) std::erase(channel_->receivers_, this);
      // Wait for queued functions to be executed
      // virtual functions dont exist at this point anymore,
      // so we have to do this weird caching of the executor
      // If it's still nullptr, internal_send was never called
      // so no need to sync
      if (exec_ != nullptr) exec_->sync();
    }

    /// The channel this receiver is registered on
    TypedChannel<Event>* channel() const noexcept
    {
      return channel_;
    }

    virtual void handle(Event) noexcept {}

  private:
    template<AnEvent>
    friend struct TypedChannel;

    void internal_send(const Event& event) noexcept
    {
      if (exec_ == nullptr) exec_ = &executor();
      exec_->execute([this, event] { handle(std::move(event)); });
    }

    TypedChannel<Event>* channel_;
    IExecutor* exec_ = nullptr;
  };

  template<AnEvent... Events>
  struct Receiver : Receiver<Events>... {
    Receiver(ChannelGroup& ch) : Receiver<Events>(ch)... {}
  };
} // namespace otto::itc
