#pragma once

#include "lib/core/service.hpp"
#include "lib/itc/executor.hpp"
#include "lib/itc/executor_provider.hpp"
#include "lib/itc/itc.hpp"

#include "app/services/runtime.hpp"

namespace otto::services {

  namespace detail {
    struct logic_domain_tag;
  }

  struct LogicThread : core::Service<LogicThread>, itc::ExecutorProvider<detail::logic_domain_tag> {
    LogicThread();

  private:
    [[no_unique_address]] core::ServiceAccessor<Runtime> runtime;
    std::jthread thread_;
  };

} // namespace otto::services

namespace otto {
  struct LogicDomain : itc::StaticDomain<services::detail::logic_domain_tag> {};
} // namespace otto
