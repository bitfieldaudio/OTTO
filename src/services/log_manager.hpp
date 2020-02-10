#pragma once

#include "util/filesystem.hpp"

#include "core/service.hpp"

#define LOGURU_USE_FMTLIB 1
#include <debug_assert.hpp>
#include <loguru.hpp>

#include "util/macros.hpp"
#include "services/application.hpp"

namespace otto::services {

  struct LogManager : core::Service {
    /// Initialize the logger
    LogManager(int argc = 0,
               char** argv = nullptr,
               bool enable_console = true,
               const char* logFilePath = nullptr);

    /// Set how the current thread appears in the log
    void set_thread_name(const std::string& name);
  };

} // namespace otto::services

/// Shorthand to the loguru macro LOG_F(INFO, ...)
#define LOGI(...) VLOG_F(loguru::Verbosity_INFO, __VA_ARGS__)

/// Shorthand to the loguru macro LOG_F(WARNING, ...)
#define LOGW(...) VLOG_F(loguru::Verbosity_WARNING, __VA_ARGS__)

/// Shorthand to the loguru macro LOG_F(ERROR, ...)
#define LOGE(...) VLOG_F(loguru::Verbosity_ERROR, __VA_ARGS__)

/// Shorthand to the loguru macro LOG_F(FATAL, ...)
#define LOGF(...) VLOG_F(loguru::Verbosity_FATAL, __VA_ARGS__)

/// Shorthand to the loguru macro DLOG_F(INFO, ...)
#define DLOGI(...) DVLOG_F(loguru::Verbosity_INFO, __VA_ARGS__)

/// Shorthand to the loguru macro DLOG_F(WARNING, ...)
#define DLOGW(...) DVLOG_F(loguru::Verbosity_WARNING, __VA_ARGS__)

/// Shorthand to the loguru macro DLOG_F(ERROR, ...)
#define DLOGE(...) DVLOG_F(loguru::Verbosity_ERROR, __VA_ARGS__)

/// Shorthand to the loguru macro DLOG_F(FATAL, ...)
#define DLOGF(...) DVLOG_F(loguru::Verbosity_FATAL, __VA_ARGS__)

/// Shorthand to the loguru macro LOG_IF_F(INFO, ...)
#define LOGI_IF(...) VLOG_IF_F(loguru::Verbosity_INFO, __VA_ARGS__)

/// Shorthand to the loguru macro LOG_IF_F(WARNING, ...)
#define LOGW_IF(...) VLOG_IF_F(loguru::Verbosity_WARNING, __VA_ARGS__)

/// Shorthand to the loguru macro LOG_IF_F(ERROR, ...)
#define LOGE_IF(...) VLOG_IF_F(loguru::Verbosity_ERROR, __VA_ARGS__)

/// Shorthand to the loguru macro LOG_IF_F(FATAL, ...)
#define LOGF_IF(...) VLOG_IF_F(loguru::Verbosity_FATAL, __VA_ARGS__)

/// Shorthand to the loguru macro DLOG_IF_F(INFO, ...)
#define DLOGI_IF(...) DVLOG_IF_F(loguru::Verbosity_INFO, __VA_ARGS__)

/// Shorthand to the loguru macro DLOG_IF_F(WARNING, ...)
#define DLOGW_IF(...) DVLOG_IF_F(loguru::Verbosity_WARNING, __VA_ARGS__)

/// Shorthand to the loguru macro DLOG_IF_F(ERROR, ...)
#define DLOGE_IF(...) DVLOG_IF_F(loguru::Verbosity_ERROR, __VA_ARGS__)

/// Shorthand to the loguru macro DLOG_IF_F(FATAL, ...)
#define DLOGF_IF(...) DVLOG_IF_F(loguru::Verbosity_FATAL, __VA_ARGS__)

/// Shorthand to the loguru macro LOG_SCOPE_F(INFO, ...)
#define LOGI_SCOPE(...) VLOG_SCOPE_F(loguru::Verbosity_INFO, __VA_ARGS__)

/// Shorthand to the loguru macro LOG_SCOPE_F(WARNING, ...)
#define LOGW_SCOPE(...) VLOG_SCOPE_F(loguru::Verbosity_WARNING, __VA_ARGS__)

/// Shorthand to the loguru macro LOG_SCOPE_F(ERROR, ...)
#define LOGE_SCOPE(...) VLOG_SCOPE_F(loguru::Verbosity_ERROR, __VA_ARGS__)

/// Shorthand to the loguru macro LOG_SCOPE_F(FATAL, ...)
#define LOGF_SCOPE(...) VLOG_SCOPE_F(loguru::Verbosity_FATAL, __VA_ARGS__)

/// Shorthand to the loguru macro DLOG_SCOPE_F(INFO, ...)
#define DLOGI_SCOPE(...) DVLOG_SCOPE_F(loguru::Verbosity_INFO, __VA_ARGS__)

/// Shorthand to the loguru macro DLOG_SCOPE_F(WARNING, ...)
#define DLOGW_SCOPE(...) DVLOG_SCOPE_F(loguru::Verbosity_WARNING, __VA_ARGS__)

/// Shorthand to the loguru macro DLOG_SCOPE_F(ERROR, ...)
#define DLOGE_SCOPE(...) DVLOG_SCOPE_F(loguru::Verbosity_ERROR, __VA_ARGS__)

/// Shorthand to the loguru macro DLOG_SCOPE_F(FATAL, ...)
#define DLOGF_SCOPE(...) DVLOG_SCOPE_F(loguru::Verbosity_FATAL, __VA_ARGS__)

namespace otto {
  struct assert_module : debug_assert::set_level<999> {
    template<typename... Args>
    static void handle(const debug_assert::source_location& loc,
                       const char* expression,
                       Args&&... args) noexcept
    {
      if constexpr (sizeof...(args) > 0) {
        LOGE("Assertion failed at {}:{}: {} {}", loc.file_name, loc.line_number, expression, fmt::format(args...));
      } else {
        LOGE("Assertion failed at {}:{}: {}", loc.file_name, loc.line_number, expression);
      }
    }
  };
} // namespace otto

#define OTTO_ASSERT_NM(Expr) DEBUG_ASSERT(Expr, ::otto::assert_module{})
#define OTTO_ASSERT_M(Expr, ...) DEBUG_ASSERT(Expr, ::otto::assert_module{}, __VA_ARGS__)
#define OTTO_ASSERT(...) SWITCH_FOR_VARARGS_1(OTTO_ASSERT_NM, OTTO_ASSERT_M, __VA_ARGS__)

#define OTTO_UNREACHABLE \
 (DEBUG_UNREACHABLE(::otto::assert_module{}), DEBUG_ASSERT_MARK_UNREACHABLE)
#define OTTO_UNREACHABLE_M(...) (DEBUG_UNREACHABLE(::otto::assert_module{}, __VA_ARGS__), DEBUG_ASSERT_MARK_UNREACHABLE)
