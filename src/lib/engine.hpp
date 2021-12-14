#pragma once

#include "app/domains/logic.hpp"
#include "app/input.hpp"

namespace otto {
  struct ILogic : LogicDomain {
    virtual ~ILogic() = default;
  };
} // namespace otto
