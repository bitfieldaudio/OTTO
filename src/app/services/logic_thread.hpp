#pragma once

#include "lib/core/service.hpp"
#include "lib/itc/executor.hpp"

namespace otto::services {

  struct LogicThread : core::Service<LogicThread> {
    virtual itc::IExecutor& executor() noexcept = 0;

    static core::ServiceHandle<LogicThread> make_default();
  };
}
