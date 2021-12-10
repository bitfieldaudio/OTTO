#pragma once

#include "../services/accessor.hpp"
#include "action.hpp"

namespace otto::itc {

  template<AnAction Action>
  struct Receiver<Action> : private virtual IDomain, Accessor<action_service<Action>> {
    Receiver(Context& ch) : Accessor<action_service<Action>>(ch) {}

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

    Sender<Action>* sender() const noexcept
    {
      return this->provider();
    }

    virtual void receive(Action) noexcept {}

  private:
    friend Sender<Action>;

    /// Called by `send` in `Sender`
    void internal_send(const Action& action) noexcept
    {
      if (exec_ == nullptr) exec_ = &executor();
      exec_->execute([this, action] { receive(std::move(action)); });
    }

    IExecutor* exec_ = nullptr;
  };

  template<AnAction... Actions>
  struct Receiver : Receiver<Actions>... {
    Receiver(Context& ch) : Receiver<Actions>(ch)... {}
  };
} // namespace otto::itc
