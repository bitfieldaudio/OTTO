#include "logging.hpp"

#include <spdlog/async.h>
#include <spdlog/pattern_formatter.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <unistd.h>

#include "lib/util/exception.hpp"
#include "lib/util/mutex.hpp"

namespace otto::log {

  using namespace std::literals;

  static util::shared_mutex<std::unordered_map<std::size_t, std::string>> thread_names;

  struct thread_name_formatter : spdlog::custom_flag_formatter {
    void format(const spdlog::details::log_msg& msg, const std::tm&, spdlog::memory_buf_t& dest) override
    {
      auto name = std::string();
      auto names = thread_names.lock_shared();
      auto found = names->find(msg.thread_id);
      if (found == names->end()) {
        name = std::to_string(msg.thread_id);
      } else {
        name = found->second;
      }
      dest.append(name.data(), name.data() + name.size());
    }

    std::unique_ptr<custom_flag_formatter> clone() const override
    {
      return spdlog::details::make_unique<thread_name_formatter>();
    }
  };

  static auto make_formatter()
  {
    auto formatter = std::make_unique<spdlog::pattern_formatter>();
    formatter->add_flag<thread_name_formatter>('*');
    // Only use colors if stdout is a tty
    if (::isatty(1) == 1) {
      formatter->set_pattern("\e[90m[%H:%M:%S.%e] [\e[0m%^%l%$\e[90m] [%*] [%s:%#]\e[0m %v");
    } else {
      formatter->set_pattern("[%H:%M:%S.%e] [%l] [%*] [%s:%#] %v");
    }
    return formatter;
  }


  void init(const char* logFilePath)
  {
    set_thread_name("main");
    auto async_logger = spdlog::create_async<spdlog::sinks::stdout_color_sink_mt>("otto-core");
    async_logger->sinks()[0]->set_formatter(make_formatter());

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
    auto names = thread_names.lock();
    names->insert_or_assign(spdlog::details::os::thread_id(), name);
  }
} // namespace otto::log
