#pragma once

#include "lib/itc/executor.hpp"
#include "lib/itc/executor_provider.hpp"
#include "lib/itc/itc.hpp"

#include "app/services/runtime.hpp"

namespace otto {
  struct LogicDomain : itc::StaticDomain<struct logic_domain_tag_t> {};
} // namespace otto

namespace otto::services {

  struct LogicThread : itc::ExecutorProvider<LogicDomain::domain_tag_t> {
    LogicThread();

  private:
    std::jthread thread_;
  };

} // namespace otto::services
