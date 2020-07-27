#pragma once

#define LOGURU_USE_FMTLIB 1
#include <loguru.hpp>

#include "lib/util/macros.hpp"

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

namespace otto::lib::detail {
  template<typename... Args>
  inline void handle_assert(const char* file,
                            int line_number,
                            const char* expression,
                            bool assertion,
                            Args&&... args) noexcept
  {
    if (assertion) return;
    if constexpr (sizeof...(args) > 0) {
      LOGF("Assertion failed at {}:{}: {} {}", file, line_number, expression, fmt::format(FWD(args)...));
    } else {
      LOGF("Assertion failed at {}:{}: {}", file, line_number, expression);
    }
  }

  template<typename... Args>
  inline void handle_unreachable(const char* file, int line_number, Args&&... args) noexcept
  {
    if constexpr (sizeof...(args) > 0) {
      LOGF("Unreachable code reached at {}:{}: {}", file, line_number, fmt::format(FWD(args)...));
    } else {
      LOGF("Unreachable code reached at {}:{}", file, line_number);
    }
  }
} // namespace otto::lib::detail

#ifdef NDEBUG
#define OTTO_ASSERT(Expr, ...) (void)
#define OTTO_UNREACHABLE(...) (void)
#else
#define OTTO_ASSERT(Expr, ...)                                                                                         \
  ::otto::lib::detail::handle_assert(__FILE__, __LINE__, #Expr, Expr __VA_OPT__(, ) __VA_ARGS__)
#define OTTO_UNREACHABLE(...)                                                                                          \
  (::otto::lib::detail::handle_unreachable(__FILE__, __LINE__ __VA_OPT__(, ) __VA_ARGS__), __builtin_unreachable())
#endif
