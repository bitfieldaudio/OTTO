#pragma once

#include <string>
#include <tl/optional.hpp>

namespace otto::app::services {

  struct LogManager {
    /// Initialize the logger
    LogManager(int argc = 0, char** argv = nullptr, bool enable_console = true, const char* logFilePath = nullptr);

    /// Set how the current thread appears in the log
    void set_thread_name(const std::string& name);

    static LogManager& get()
    {
      return instance_.value();
    }

    static LogManager& init()
    {
      return instance_.emplace();
    }

  private:
    static tl::optional<LogManager> instance_;
  };

} // namespace otto::services

