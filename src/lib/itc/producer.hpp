#pragma once

#include "sender.hpp"
#include "state.hpp"

namespace otto::itc {

  template<AState State>
  struct Producer<State> : Sender<state_change_action<State>>, util::ISerializable {
    using Action = state_change_action<State>;
    Producer(Channel& channels) : Sender<Action>(channels) {}

    /// Commit the current `state()`, notifying consumers
    void commit()
    {
      // TODO: Do not send state along as action
      Sender<Action>::send(Action{state()});
      on_state_change(state());
    }

    State& state() noexcept
    {
      return state_;
    }

    const State& state() const noexcept
    {
      return state_;
    }

    // FOR UNIFORMITY WITH Producer<State...>

    /// Access the stored state of the given type
    template<std::same_as<State> S>
    S& state() noexcept
    {
      return state();
    }

    /// Access the stored state of the given type
    template<std::same_as<State> S>
    const S& state() const noexcept
    {
      return state();
    }

    /// Commit the current states of the given types, notifying all consumers
    template<std::same_as<State> S>
    void commit() noexcept
    {
      commit();
    }

    void commit_all() noexcept
    {
      commit();
    }

    void serialize_into(json::value& json) const override
    {
      if constexpr (util::ASerializable<State>) {
        util::serialize_into(json, state_);
      }
    }
    void deserialize_from(const json::value& json) override
    {
      if constexpr (util::ASerializable<State>) {
        util::deserialize_from(json, state_);
        commit();
      }
    }

    virtual void on_state_change(const State&) {}

  private:
    State state_;
  };

  template<AState... States>
  struct Producer : Producer<States>... {
    Producer(Channel& channels) : Producer<States>(channels)... {}

    /// Access the stored state of the given type
    template<util::one_of<States...> S>
    S& state() noexcept
    {
      return Producer<S>::state();
    }

    /// Access the stored state of the given type
    template<util::one_of<States...> S>
    const S& state() const noexcept
    {
      return Producer<S>::state();
    }

    /// Commit the current states of the given types, notifying all consumers
    template<util::one_of<States...>... S>
    void commit() noexcept
    {
      (Producer<S>::commit(), ...);
    }

    void commit_all() noexcept
    {
      commit<States...>();
    }
  };

} // namespace otto::itc
