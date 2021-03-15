#pragma once

#include <concepts>

#include "lib/itc/action.hpp"

namespace otto::itc {

  /// The concept that state types need to fulfill.
  template<typename T>
  concept AState = std::semiregular<T>;

  // Forward Declarations

  /// Sends state to multiple Consumers through a Channel
  template<AState... States>
  struct Producer;

  /// Receives state from a single producer through a Channel
  template<AState... States>
  struct Consumer;

  template<AState State_>
  struct state_change_action {
    using State = State_;
    // TODO: Obviously dont copy the entire state
    State state;
  };

  template<typename T>
  concept AStateEvent = std::is_same_v<T, state_change_action<typename T::State>>;

  template<AState State>
  using state_service = action_service<state_change_action<State>>;

} // namespace otto::itc
