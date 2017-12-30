#pragma once

#include <filesystem.hpp>

#define LOGURU_USE_FMTLIB 1
#include <loguru.hpp>

namespace otto::services::logger {
  void init(int argc,
            char* argv[],
            bool enable_console     = true,
            const char* logFilePath = nullptr);
  void set_thread_name(const std::string& name);
} // namespace otto::services::logger
