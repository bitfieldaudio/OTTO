#pragma once

#include "lib/util/local_vector.hpp"

#include "../services/provider.hpp"
#include "state.hpp"

namespace otto::itc {

  template<AState State>
  struct Producer<State> : Provider<state_service<State>>, util::ISerializable {
    Producer(Context& ctx) : Provider<state_service<State>>(ctx) {}

    /// Commit the current `state()`, notifying consumers
    void commit()
    {
      for (Consumer<State>* c : Provider<state_service<State>>::accessors()) {
        c->internal_commit(state());
      }
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

    /// Calls Executor::sync for the executor of each consumer
    void sync()
    {
      util::local_set<IExecutor*, 8> executors;
      for (Consumer<State>* c : Provider<state_service<State>>::accessors()) {
        executors.insert(c->exec_);
      }
      for (auto* e : executors) {
        e->sync();
      }
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
    Producer(Context& ctx) : Producer<States>(ctx)... {}

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

    /// Sync specific state
    template<util::one_of<States...>... S>
    void sync()
    {
      (Producer<S>::sync(), ...);
    }
  };

} // namespace otto::itc
