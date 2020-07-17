#pragma once
#include <ctype.h>
#include <fcntl.h>
#include <fmt/format.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

[[maybe_unused]] static bool debuggerIsAttached()
{
  char buf[4096];

  const int status_fd = ::open("/proc/self/status", O_RDONLY);
  if (status_fd == -1) return false;

  const ssize_t num_read = ::read(status_fd, buf, sizeof(buf) - 1);
  if (num_read <= 0) return false;

  buf[num_read] = '\0';
  constexpr char tracerPidString[] = "TracerPid:";
  const auto tracer_pid_ptr = ::strstr(buf, tracerPidString);
  if (!tracer_pid_ptr) return false;

  for (const char* characterPtr = tracer_pid_ptr + sizeof(tracerPidString) - 1; characterPtr <= buf + num_read;
       ++characterPtr) {
    if (::isspace(*characterPtr))
      continue;
    else
      return ::isdigit(*characterPtr) != 0 && *characterPtr != '0';
  }

  return false;
}

[[maybe_unused]] static bool doctestDebuggerCheck()
{
  static bool res = debuggerIsAttached();
  return res;
}

#include "debugbreak.h"

#include <doctest/doctest.h>
#undef DOCTEST_BREAK_INTO_DEBUGGER
#define DOCTEST_BREAK_INTO_DEBUGGER() debug_break();
#define DOCTEST_IS_DEBUGGER_ACTIVE() doctestDebuggerCheck();

#include <chrono>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <filesystem>

#include "util/algorithm.hpp"
#include "util/type_traits.hpp"
#include "util/utility.hpp"

namespace fs = std::filesystem;

namespace otto::test {
  inline fs::path dir = fs::current_path() / "testdir";

  inline void truncateFile(const fs::path& p)
  {
    std::fstream fstream;
    fstream.open(p.c_str(), std::ios::trunc | std::ios::out | std::ios::binary);
    fstream.close();
  }

  struct measure {
    using TimeT = std::chrono::nanoseconds;

    template<typename F, typename... Args>
    static auto execution(F&& func, Args&&... args)
    {
      auto start = std::chrono::steady_clock::now();
      std::forward<decltype(func)>(func)(std::forward<Args>(args)...);
      return std::chrono::duration_cast<TimeT>(std::chrono::steady_clock::now() - start);
    }
  };

  inline auto float_cmp(float margin)
  {
    return [margin](float a, float b) { return std::abs(a - b) < margin; };
  }

  struct approx {
    approx(float v) noexcept : value_(v) {}

    approx& margin(float m) noexcept
    {
      margin_ = m;
      return *this;
    };

    bool operator==(float rhs) const noexcept
    {
      return std::abs(value_ - rhs) < margin_;
    }

    friend bool operator==(float lhs, const approx& rhs)
    {
      return (rhs == lhs);
    }

    bool operator!=(float rhs) const noexcept
    {
      return !(*this == rhs);
    }

    friend bool operator!=(float lhs, const approx& rhs)
    {
      return rhs != lhs;
    }

    friend std::ostream& operator<<(std::ostream& os, const approx& a)
    {
      os << "approx(" << a.value_ << ", ±" << a.margin_ << ")";
      return os;
    }

  private:
    float value_;
    float margin_ = 0.0001;
  };

//  template<typename Cont, typename Proj>
//  auto sort(Cont&& c, Proj&& projection)
//  {
//    auto vec = util::view::to_vec(c);
//    nano::sort(vec, [&](auto&& a, auto&& b) { return projection(a) < projection(b); });
//    return vec;
//  }
//
//  template<typename Cont>
//  auto sort(Cont&& c)
//  {
//    return test::sort(c, util::identity);
//  }

} // namespace otto::test

namespace doctest {
  template<typename... Args>
  struct StringMaker<std::tuple<Args...>> {
    static doctest::String convert(std::tuple<Args...> const& value) requires(requires {
      StringMaker<std::decay_t<Args>>::convert(std::declval<Args>());
    } && ...)
    {
      if constexpr (sizeof...(Args) == 0) return "{}";
      std::ostringstream o;
      o << "{";
      otto::util::for_each(value,
                           [&](const auto& a) { o << StringMaker<std::decay_t<decltype(a)>>::convert(a) << ", "; });
      auto str = o.str();
      // Chop the extra ", "
      str.resize(str.size() - 2);
      return (str + "}").c_str();
    }
  };
} // namespace doctest
