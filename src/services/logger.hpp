#pragma once

#include <filesystem.hpp>

#define LOGURU_USE_FMTLIB 1
#include <loguru.hpp>

namespace otto::services::logger {

  /// Initialize the logger
  void init(int argc,
            char* argv[],
            bool enable_console     = true,
            const char* logFilePath = nullptr);

  /// Set how the current thread appears in the log
  void set_thread_name(const std::string& name);

} // namespace otto::services::logger

/// Shorthand to the loguru macro LOG_F(INFO, ...)
#define LOGI(...) LOG_F(INFO, __VA_ARGS__)

/// Shorthand to the loguru macro LOG_F(WARNING, ...)
#define LOGW(...) LOG_F(WARNING, __VA_ARGS__)

/// Shorthand to the loguru macro LOG_F(ERROR, ...)
#define LOGE(...) LOG_F(ERROR, __VA_ARGS__)

/// Shorthand to the loguru macro LOG_F(FATAL, ...)
#define LOGF(...) LOG_F(FATAL, __VA_ARGS__)

/// Shorthand to the loguru macro DLOG_F(INFO, ...)
#define DLOGI(...) DLOG_F(INFO, __VA_ARGS__)

/// Shorthand to the loguru macro DLOG_F(WARNING, ...)
#define DLOGW(...) DLOG_F(WARNING, __VA_ARGS__)

/// Shorthand to the loguru macro DLOG_F(ERROR, ...)
#define DLOGE(...) DLOG_F(ERROR, __VA_ARGS__)

/// Shorthand to the loguru macro DLOG_F(FATAL, ...)
#define DLOGF(...) DLOG_F(FATAL, __VA_ARGS__)

/// Shorthand to the loguru macro LOG_IF_F(INFO, ...)
#define LOGI_IF(...) LOG_IF_F(INFO, __VA_ARGS__)

/// Shorthand to the loguru macro LOG_IF_F(WARNING, ...)
#define LOGW_IF(...) LOG_IF_F(WARNING, __VA_ARGS__)

/// Shorthand to the loguru macro LOG_IF_F(ERROR, ...)
#define LOGE_IF(...) LOG_IF_F(ERROR, __VA_ARGS__)

/// Shorthand to the loguru macro LOG_IF_F(FATAL, ...)
#define LOGF_IF(...) LOG_IF_F(FATAL, __VA_ARGS__)

/// Shorthand to the loguru macro DLOG_IF_F(INFO, ...)
#define DLOGI_IF(...) DLOG_IF_F(INFO, __VA_ARGS__)

/// Shorthand to the loguru macro DLOG_IF_F(WARNING, ...)
#define DLOGW_IF(...) DLOG_IF_F(WARNING, __VA_ARGS__)

/// Shorthand to the loguru macro DLOG_IF_F(ERROR, ...)
#define DLOGE_IF(...) DLOG_IF_F(ERROR, __VA_ARGS__)

/// Shorthand to the loguru macro DLOG_IF_F(FATAL, ...)
#define DLOGF_IF(...) DLOG_IF_F(FATAL, __VA_ARGS__)

/// Shorthand to the loguru macro LOG_SCOPE_F(INFO, ...)
#define LOGI_SCOPE(...) LOG_SCOPE_F(INFO, __VA_ARGS__)

/// Shorthand to the loguru macro LOG_SCOPE_F(WARNING, ...)
#define LOGW_SCOPE(...) LOG_SCOPE_F(WARNING, __VA_ARGS__)

/// Shorthand to the loguru macro LOG_SCOPE_F(ERROR, ...)
#define LOGE_SCOPE(...) LOG_SCOPE_F(ERROR, __VA_ARGS__)

/// Shorthand to the loguru macro LOG_SCOPE_F(FATAL, ...)
#define LOGF_SCOPE(...) LOG_SCOPE_F(FATAL, __VA_ARGS__)

/// Shorthand to the loguru macro DLOG_SCOPE_F(INFO, ...)
#define DLOGI_SCOPE(...) DLOG_SCOPE_F(INFO, __VA_ARGS__)

/// Shorthand to the loguru macro DLOG_SCOPE_F(WARNING, ...)
#define DLOGW_SCOPE(...) DLOG_SCOPE_F(WARNING, __VA_ARGS__)

/// Shorthand to the loguru macro DLOG_SCOPE_F(ERROR, ...)
#define DLOGE_SCOPE(...) DLOG_SCOPE_F(ERROR, __VA_ARGS__)

/// Shorthand to the loguru macro DLOG_SCOPE_F(FATAL, ...)
#define DLOGF_SCOPE(...) DLOG_SCOPE_F(FATAL, __VA_ARGS__)
