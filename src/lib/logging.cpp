#include "logging.hpp"

#include <spdlog/async.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include "lib/util/exception.hpp"

namespace otto::log {

  using namespace std::literals;

  void init(const char* logFilePath)
  {
    auto async_logger = spdlog::create_async<spdlog::sinks::stdout_color_sink_mt>("otto-core");
    async_logger->sinks()[0]->set_pattern("[%H:%M:%S.%e] %^[%l]%$ [thread %t] [%s:%#] %v");

    if (logFilePath != nullptr) {
      auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(logFilePath, true);
      async_logger->sinks().push_back(file_sink);
    }

    spdlog::set_default_logger(async_logger);
    spdlog::set_error_handler([](const std::string& message) { throw util::exception("{}", message); });

    LOGI("Logging initialized");
  }

  void set_thread_name(const std::string& name)
  {
    pthread_setname_np(pthread_self(), name.c_str());
  }
} // namespace otto::log
