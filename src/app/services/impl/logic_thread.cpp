#include "logic_thread.hpp"

namespace otto::services {

  itc::IExecutor& LogicThreadImpl::executor() noexcept
  {
    return executor_;
  }

  LogicThreadImpl::LogicThreadImpl()
    : thread_([this] {
        while (runtime->should_run()) {
          executor_.run_queued_functions_blocking(std::chrono::milliseconds(100));
        }
        // TODO: propper shutdown!
      })
  {}

  core::ServiceHandle<LogicThread> LogicThread::make_default() {
    return core::make_handle<LogicThreadImpl>();
  }
} // namespace otto::services
