#pragma once

#include <concepts>
#include <vector>

#include "lib/itc/domain.hpp"

namespace otto::itc {

  template<typename T>
  concept AnAction = std::copyable<T>;

  template<AnAction... Actions>
  struct Sender;
  template<AnAction... Actions>
  struct Receiver;

  template<AnAction Action>
  struct action_service {
    using provider_t = Sender<Action>;
    using accessor_t = Receiver<Action>;
  };
} // namespace otto::itc
