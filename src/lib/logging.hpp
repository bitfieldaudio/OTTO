#pragma once

#include <concepts>
#include <span>

#include <fmt/format.h>
#include <fmt/ostream.h>

#ifndef SPDLOG_ACTIVE_LEVEL
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
#endif
#include <spdlog/spdlog.h>

#include "lib/util/concepts.hpp"
#include "lib/util/macros.hpp"

namespace otto::log {
  void init(const char* logFilePath = nullptr);

  /// Set how the current thread appears in the log
  void set_thread_name(const std::string& name);

  using namespace spdlog;
} // namespace otto::log

#define LOGT(...) SPDLOG_TRACE(__VA_ARGS__)
#define LOGD(...) SPDLOG_DEBUG(__VA_ARGS__)
#define LOGI(...) SPDLOG_INFO(__VA_ARGS__)
#define LOGW(...) SPDLOG_WARN(__VA_ARGS__)
#define LOGE(...) SPDLOG_ERROR(__VA_ARGS__)
#define LOGC(...) SPDLOG_CRITICAL(__VA_ARGS__)

namespace otto::detail {
  template<typename... Args>
  inline void handle_assert(const char* file, int line_number, const char* expression, bool assertion) noexcept
  {
    if (assertion) return;
    LOGE("Assertion failed at {}:{}: {}", file, line_number, expression);
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
    LOGE("Assertion failed at {}:{}: {} {}", file, line_number, expression, fmt::format(fs, FWD(args)...));
  }

  template<typename... Args>
  inline void handle_unreachable(const char* file, int line_number) noexcept
  {
    LOGE("Unreachable code reached at {}:{}", file, line_number);
  }

  template<typename... Args>
  inline void handle_unreachable(const char* file,
                                 int line_number,
                                 fmt::format_string<Args...> fs,
                                 Args&&... args) noexcept
  {
    LOGE("Unreachable code reached at {}:{}: {}", file, line_number, fmt::format(fs, FWD(args)...));
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
