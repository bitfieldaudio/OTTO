#pragma once

#include <concepts>

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
  struct state_change_event {
    using State = State_;
    // TODO: Obviously dont copy the entire state
    State state;
  };

  template<typename T>
  concept AStateEvent = std::is_same_v<T, state_change_event<typename T::State>>;

} // namespace otto::itc
