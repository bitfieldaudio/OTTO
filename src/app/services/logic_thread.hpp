#pragma once

#include "lib/core/service.hpp"
#include "lib/itc/executor.hpp"

namespace otto::app::services {

  struct LogicThread : lib::core::Service<LogicThread> {
    virtual lib::itc::IExecutor& executor() noexcept = 0;

    static lib::core::ServiceHandle<LogicThread> make_default();
  };
}
