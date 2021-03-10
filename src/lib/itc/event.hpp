#pragma once

#include <concepts>
#include <vector>

#include "lib/itc/domain.hpp"

namespace otto::itc {

  template<typename T>
  concept AnEvent = std::copyable<T>;

  template<AnEvent Event>
  struct TypedChannel;
  template<AnEvent... Events>
  struct Sender;
  template<AnEvent... Events>
  struct Receiver;
} // namespace otto::itc
