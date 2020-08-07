#define LOGURU_IMPLEMENTATION 1

#include "logging.hpp"

#include "lib/util/exception.hpp"

namespace otto::logging {

  using namespace std::literals;

  void init(int argc, char* argv[], bool enable_console, const char* logFilePath)
  {
    // std::string def_path = Application::current().data_dir / "log.txt";
    if (logFilePath == nullptr) {
      // logFilePath = def_path.c_str();
    }

    if (!enable_console) {
      loguru::g_stderr_verbosity = loguru::Verbosity_OFF;
    }

    char exc[] = "otto";
    char* eptr[] = {exc, nullptr};
    if (argc == 0) {
      argc = 1;
      argv = eptr;
    }

    loguru::init(argc, argv);
    if (logFilePath) loguru::add_file(logFilePath, loguru::Append, loguru::Verbosity_MAX);

    loguru::set_fatal_handler([](const loguru::Message& message) {
      if (message.prefix != "Signal: "sv) throw util::exception(std::string(message.prefix) + message.message);
    });

    LOGI("Logging initialized");
  }

  void set_thread_name(const std::string& name)
  {
    pthread_setname_np(pthread_self(), name.c_str());
    loguru::set_thread_name(name.c_str());
  }
}
