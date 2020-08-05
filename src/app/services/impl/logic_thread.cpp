#include "logic_thread.hpp"

namespace otto::app::services {

  lib::itc::IExecutor& LogicThreadImpl::executor() noexcept
  {
    return executor_;
  }

  LogicThreadImpl::LogicThreadImpl()
    : thread_([this](auto should_run) {
        while (runtime->should_run() && should_run()) {
          executor_.run_queued_functions_blocking(std::chrono::milliseconds(100));
        }
        // TODO: propper shutdown!
      })
  {}

  lib::core::ServiceHandle<LogicThread> LogicThread::make_default() {
    return lib::core::make_handle<LogicThreadImpl>();
  }
} // namespace otto::app::services
