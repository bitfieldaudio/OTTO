#pragma once

#include "channel.hpp"
#include "event.hpp"

namespace otto::itc {

  template<AnEvent Event>
  struct Receiver<Event> : private virtual IDomain, detail::ReceiverBase {
    Receiver(Channel& ch) : channel_(&ch)
    {
      ch.register_receiver(this);
    }

    Receiver(const Receiver&) = delete;
    Receiver& operator=(const Receiver&) = delete;

    virtual ~Receiver() noexcept
    {
      channel_->unregister_receiver(this);
      // Wait for queued functions to be executed
      // virtual functions dont exist at this point anymore,
      // so we have to do this weird caching of the executor
      // If it's still nullptr, internal_send was never called
      // so no need to sync
      if (exec_ != nullptr) exec_->sync();
    }

    /// The channel this receiver is registered on
    [[nodiscard]] Channel& channel() const noexcept
    {
      return *channel_;
    }

    Sender<Event>* sender() const noexcept
    {
      return sender_;
    }

    virtual void handle(Event) noexcept {}

  private:
    friend Sender<Event>;
    friend struct linker;

    /// Called by `send` in `Sender`
    void internal_send(const Event& event) noexcept
    {
      if (exec_ == nullptr) exec_ = &executor();
      exec_->execute([this, event] { handle(std::move(event)); });
    }

    Channel* channel_;
    Sender<Event>* sender_ = nullptr;
    IExecutor* exec_ = nullptr;
  };

  template<AnEvent... Events>
  struct Receiver : Receiver<Events>... {
    Receiver(Channel& ch) : Receiver<Events>(ch)... {}
  };
} // namespace otto::itc
