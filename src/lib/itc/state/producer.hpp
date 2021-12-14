#pragma once

#include "lib/util/local_vector.hpp"

#include "lib/itc/domain.hpp"
#include "lib/itc/services/provider.hpp"

#include "consumer.hpp"

namespace otto::itc {

  template<AState State>
  struct Producer<State> : StateAccessor<State> {
    Producer(Context& ctx) : StateAccessor<State>(ctx) {}

    /// Modify the state, and commit the changes
    decltype(auto) commit(std::invocable<State&> auto&& f) noexcept
    {
      StateAccessor<State>::ensure_state();
      // When f returns void, we cannot save it in a variable, since void
      if constexpr (std::is_void_v<std::invoke_result_t<decltype(f), State&>>) {
        std::invoke(f, *StateAccessor<State>::state_);
        this->provider()->commit();
      } else {
        decltype(auto) res = std::invoke(f, *StateAccessor<State>::state_);
        this->provider()->commit();
        return FWD(res);
      }
    }

    using StateAccessor<State>::state;

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
      commit(FWD(f));
    }
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
