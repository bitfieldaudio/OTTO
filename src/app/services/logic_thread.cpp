#include "logic_thread.hpp"

namespace otto::services {

  LogicThread::LogicThread()
    : ExecutorProvider("logic"), thread_([this](const std::stop_token& token) {
        log::set_thread_name("logic");
        while (!token.stop_requested()) {
          executor().run_queued_functions_blocking(std::chrono::milliseconds(100));
        }
        // TODO: propper shutdown!
      })
  {}
} // namespace otto::services
