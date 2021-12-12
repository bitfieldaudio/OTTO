#pragma once

#include <concepts>
#include <span>

#include <fmt/format.h>
#include <fmt/ostream.h>
#include <spdlog/spdlog.h>

#include "lib/util/concepts.hpp"
#include "lib/util/macros.hpp"

namespace otto::logging {
  void init(const char* logFilePath = nullptr);

  /// Set how the current thread appears in the log
  void set_thread_name(const std::string& name);
} // namespace otto::logging

/// Shorthand to the loguru macro LOG_F(INFO, ...)
#define LOGI(...) spdlog::info(__VA_ARGS__)

/// Shorthand to the loguru macro LOG_F(WARNING, ...)
#define LOGW(...) spdlog::warn(__VA_ARGS__)

/// Shorthand to the loguru macro LOG_F(ERROR, ...)
#define LOGE(...) spdlog::error(__VA_ARGS__)

/// Shorthand to the loguru macro LOG_F(FATAL, ...)
#define LOGF(...) spdlog::critical(__VA_ARGS__)

/// Shorthand to the loguru macro DLOG_F(INFO, ...)
#define DLOGI(...) spdlog::debug(__VA_ARGS__)

namespace otto::detail {
  template<typename... Args>
  inline void handle_assert(const char* file, int line_number, const char* expression, bool assertion) noexcept
  {
    if (assertion) return;
    LOGF("Assertion failed at {}:{}: {}", file, line_number, expression);
  }

  template<typename... Args>
  inline void handle_assert(const char* file,
                            int line_number,
                            const char* expression,
                            bool assertion,
                            fmt::format_string<Args...> fs,
                            Args&&... args) noexcept
  {
    if (assertion) return;
    LOGF("Assertion failed at {}:{}: {} {}", file, line_number, expression, fmt::format(fs, FWD(args)...));
  }

  template<typename... Args>
  inline void handle_unreachable(const char* file, int line_number) noexcept
  {
    LOGF("Unreachable code reached at {}:{}", file, line_number);
  }

  template<typename... Args>
  inline void handle_unreachable(const char* file,
                                 int line_number,
                                 fmt::format_string<Args...> fs,
                                 Args&&... args) noexcept
  {
    LOGF("Unreachable code reached at {}:{}: {}", file, line_number, fmt::format(fs, FWD(args)...));
  }
} // namespace otto::detail

#ifdef NDEBUG
#define OTTO_ASSERT(Expr, ...) ((void) 0)
#define OTTO_UNREACHABLE(...) (__builtin_unreachable())
#else
#define OTTO_ASSERT(Expr, ...) ::otto::detail::handle_assert(__FILE__, __LINE__, #Expr, Expr __VA_OPT__(, ) __VA_ARGS__)
#define OTTO_UNREACHABLE(...)                                                                                          \
  (::otto::detail::handle_unreachable(__FILE__, __LINE__ __VA_OPT__(, ) __VA_ARGS__), __builtin_unreachable())
#endif
