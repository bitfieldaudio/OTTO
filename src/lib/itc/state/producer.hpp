#pragma once

#include "lib/util/local_vector.hpp"

#include "lib/itc/domain.hpp"
#include "lib/itc/services/provider.hpp"

#include "state.hpp"

namespace otto::itc {

  template<AState State>
  struct Producer<State> : Provider<state_service<State>>, util::ISerializable {
    Producer(Context& ctx) : Provider<state_service<State>>(ctx) {}

    const State& state() const noexcept
    {
      return state_;
    }

    // FOR UNIFORMITY WITH Producer<State...>

    /// Access the stored state of the given type
    template<std::same_as<State> S>
    const S& state() const noexcept
    {
      return state();
    }

    /// Commit the current states of the given types, notifying all consumers
    template<std::same_as<State> S>
    decltype(auto) commit(std::invocable<State&> auto&& f) noexcept
    {
      return commit(FWD(f));
    }

    /// Modify the state, and commit the changes
    decltype(auto) commit(std::invocable<State&> auto&& f) noexcept
    {
      // When f returns void, we cannot save it in a variable
      if constexpr (std::is_void_v<std::invoke_result_t<decltype(f), State&>>) {
        std::invoke(f, state_);
        for (Consumer<State>* c : Provider<state_service<State>>::accessors()) {
          c->internal_commit(state());
        }
        on_state_change(state());
      } else {
        decltype(auto) res = std::invoke(f, state_);
        for (Consumer<State>* c : Provider<state_service<State>>::accessors()) {
          c->internal_commit(state());
        }
        on_state_change(state());
        return FWD(res);
      }
    }

    void serialize_into(json::value& json) const override
    {
      if constexpr (util::ASerializable<State>) {
        util::serialize_into(json, state());
      }
    }
    void deserialize_from(const json::value& json) override
    {
      if constexpr (util::ASerializable<State>) {
        commit([&](auto& state) { util::deserialize_from(json, state); });
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
    const S& state() const noexcept
    {
      return Producer<S>::state();
    }

    /// Commit the current states of the given types, notifying all consumers
    template<util::one_of<States...> S>
    decltype(auto) commit(std::invocable<S&> auto&& f) noexcept
    {
      Producer<S>::commit(FWD(f));
    }
  };

} // namespace otto::itc
