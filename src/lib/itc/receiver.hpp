#pragma once

#include "accessor.hpp"
#include "channel.hpp"
#include "event.hpp"

namespace otto::itc {

  template<AnEvent Event>
  struct Receiver<Event> : private virtual IDomain, Accessor<event_service<Event>> {
    Receiver(Channel& ch) : Accessor<event_service<Event>>(ch) {}

    Receiver(const Receiver&) = delete;
    Receiver& operator=(const Receiver&) = delete;

    virtual ~Receiver() noexcept
    {
      this->unregister();
      // Wait for queued functions to be executed
      // virtual functions dont exist at this point anymore,
      // so we have to do this weird caching of the executor
      // If it's still nullptr, internal_send was never called
      // so no need to sync
      if (exec_ != nullptr) exec_->sync();
    }

    Sender<Event>* sender() const noexcept
    {
      return this->provider();
    }

    virtual void receive(Event) noexcept {}

  private:
    friend Sender<Event>;

    /// Called by `send` in `Sender`
    void internal_send(const Event& event) noexcept
    {
      if (exec_ == nullptr) exec_ = &executor();
      exec_->execute([this, event] { receive(std::move(event)); });
    }

    IExecutor* exec_ = nullptr;
  };

  template<AnEvent... Events>
  struct Receiver : Receiver<Events>... {
    Receiver(Channel& ch) : Receiver<Events>(ch)... {}
  };
} // namespace otto::itc
