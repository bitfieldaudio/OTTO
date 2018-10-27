#include "log_manager.hpp"
#include "services/application.hpp"

#define LOGURU_IMPLEMENTATION 1
#include <loguru.hpp>

namespace otto::services {

  LogManager::LogManager(int argc, char* argv[], bool enable_console, const char* logFilePath)
  {
    std::string def_path = Application::current().data_dir / "log.txt";
    if (logFilePath == nullptr) {
      logFilePath = def_path.c_str();
    }

    if (!enable_console) {
      loguru::g_stderr_verbosity = loguru::Verbosity_OFF;
    }

    loguru::init(argc, argv);
    loguru::add_file(logFilePath, loguru::Append, loguru::Verbosity_MAX);

    loguru::set_fatal_handler([](const loguru::Message& message) {
      throw Application::exception(Application::ErrorCode::none,
                                   std::string(message.prefix) + message.message);
    });

    LOGI("LOGGING NOW");
  }

  void LogManager::set_thread_name(const std::string& name)
  {
    loguru::set_thread_name(name.c_str());
  }
} // namespace otto::services
