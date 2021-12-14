#pragma once

#include "lib/util/concepts.hpp"
#include "lib/util/spin_lock.hpp"

#include "../domain.hpp"
#include "../services/accessor.hpp"
#include "provider.hpp"
#include "state.hpp"

namespace otto::itc {
  // Declarations

  template<AState State>
  struct Consumer<State> : StateAccessor<State> {
    Consumer(Context& ctx) : StateAccessor<State>(ctx) {}

    using StateAccessor<State>::state;

    // FOR UNIFORMITY WITH Consumer<State...>

    /// Access the newest state available.
    template<std::same_as<State> S>
    const S& state() const noexcept
    {
      return state();
    }
  };


  template<AState... States>
  struct Consumer : Consumer<States>... {
    Consumer(Context& ctx) : Consumer<States>(ctx)... {}

    template<util::one_of<States...> S>
    const S& state() const noexcept
    {
      return Consumer<S>::state();
    }
  };

} // namespace otto::itc
