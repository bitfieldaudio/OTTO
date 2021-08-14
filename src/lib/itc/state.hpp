#pragma once

#include <concepts>

namespace otto::itc {

  /// The concept that state types need to fulfill.
  ///
  /// Semiregular means copyable and default constructible
  template<typename T>
  concept AState = std::semiregular<T>;

  // Forward Declarations

  /// Sends state to multiple Consumers through a Channel
  template<AState... States>
  struct Producer;

  /// Receives state from a single producer through a Channel
  template<AState... States>
  struct Consumer;

  template<AState State>
  struct state_service {
    using provider_t = Producer<State>;
    using accessor_t = Consumer<State>;
  };
} // namespace otto::itc
