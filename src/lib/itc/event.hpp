#pragma once

#include <concepts>
#include <vector>

#include "lib/itc/domain.hpp"

namespace otto::itc {

  template<typename T>
  concept AnEvent = std::copyable<T>;

  template<AnEvent... Events>
  struct Sender;
  template<AnEvent... Events>
  struct Receiver;

  template<AnEvent Event>
  struct event_service {
    using provider_t = Sender<Event>;
    using accessor_t = Receiver<Event>;
  };
} // namespace otto::itc
