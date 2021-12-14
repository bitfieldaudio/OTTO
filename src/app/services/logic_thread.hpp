#pragma once

#include "lib/itc/executor.hpp"
#include "lib/itc/executor_provider.hpp"
#include "lib/itc/itc.hpp"

#include "app/domains/logic.hpp"
#include "app/services/runtime.hpp"

namespace otto::services {

  struct LogicThread : itc::ExecutorProvider<LogicDomain::domain_tag_t> {
    LogicThread();

  private:
    std::jthread thread_;
  };

} // namespace otto::services
