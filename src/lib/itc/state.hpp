#pragma once

#include <concepts>

namespace otto::itc {

  /// The concept that state types need to fulfill.
  template<typename T>
  concept AState = std::semiregular<T>;

  // Forward Declarations

  /// A Channel through which a single Producer can send state to multiple consumers
  template<AState State>
  struct TypedChannel;

  /// Sends state to multiple Consumers through a Channel
  template<AState... States>
  struct Producer;

  /// Receives state from a single producer through a Channel
  template<AState... States>
  struct Consumer;

} // namespace otto::itc
