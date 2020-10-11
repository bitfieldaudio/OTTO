#include "logic_thread.hpp"

namespace otto::services {

  LogicThread::LogicThread()
    : thread_([this] {
        while (runtime->should_run()) {
          executor().run_queued_functions_blocking(std::chrono::milliseconds(100));
        }
        // TODO: propper shutdown!
      })
  {}
} // namespace otto::services
