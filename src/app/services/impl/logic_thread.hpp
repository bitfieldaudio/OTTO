#pragma once

#include <thread>

#include "app/services/logic_thread.hpp"
#include "app/services/runtime.hpp"

namespace otto::services {

  struct LogicThreadImpl : LogicThread {
    LogicThreadImpl();

    itc::IExecutor& executor() noexcept override;

  private:
    [[no_unique_address]] core::ServiceAccessor<Runtime> runtime;

  protected:
    itc::QueueExecutor executor_;
    std::jthread thread_;
  };
} // namespace otto::services
