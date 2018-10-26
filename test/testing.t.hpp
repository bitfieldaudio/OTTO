#pragma once

#include <fmt/format.h>
#include <catch.hpp>
#include <chrono>
#include <fstream>
#include <random.hpp>

#include "services/log_manager.hpp"
#include "util/algorithm.hpp"
#include "util/filesystem.hpp"

#include <unordered_map>

using Random = effolkronium::random_static;

namespace otto::test {
  inline fs::path dir = fs::current_path() / "testdir";

  inline void truncateFile(const filesystem::path& p)
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

  /// \private
  struct Benchmark {
    using clock = std::chrono::steady_clock;

    Benchmark(std::string name) : name(std::move(name)) {}

    bool running() noexcept
    {
      return start_time != clock::time_point::min();
    }

    void start()
    {
      if (!running()) start_time = clock::now();
      for (const auto& child : children) {
        if (child->continue_with_parent) {
          child->start();
          child->continue_with_parent = false;
        }
      }
    }

    void reset()
    {
      current = clock::duration::zero();
      start_time = clock::time_point::min();
      for (const auto& child : children) {
        child->reset();
      }
    }

    void restart()
    {
      reset();
      start();
    }

    bool pause()
    {
      for (const auto& child : children) {
        child->continue_with_parent = child->pause();
      }
      if (running()) current += clock::now() - start_time;
      bool res = running();
      start_time = clock::time_point::min();
      return res;
    }

    void stop()
    {
      for (const auto& child : children) {
        child->continue_with_parent = false;
        child->stop();
      }
      if (running()) {
        current += clock::now() - start_time;
        time_sum += current;
        time_min = std::min(time_min, current);
        time_max = std::max(time_max, current);

        current = clock::duration::zero();
        count++;
        start_time = clock::time_point::min();
      }
    }

    Benchmark& child(const std::string& name)
    {
      bool was_running = pause();
      auto iter = util::find_if(children, [&](auto& b) { return b->name == name; });
      if (iter == children.end()) {
        auto& res = *children.emplace_back(std::make_unique<Benchmark>(name));
        if (was_running) start();
        return res;
      }
      if (was_running) start();
      return **iter;
    }

    void report(std::string prefix = "")
    {
      printf(" %s%-*s %12ld ns %12ld ns %12.0f ns\n", prefix.c_str(), 53 - (int) prefix.size() / 2,
             name.c_str(), (long) std::chrono::nanoseconds(time_min).count(),
             (long) std::chrono::nanoseconds(time_max).count(),
             std::chrono::nanoseconds(time_sum).count() / double(count));
      for (int i = 0; i < children.size(); i++) {
        util::string_replace(prefix, "├", "│");
        util::string_replace(prefix, "└", " ");
        if (i < (children.size() - 1)) {
          children[i]->report(prefix + "├ ");
        } else {
          children[i]->report(prefix + "└ ");
        }
      }
    }

    std::string name;
    std::size_t count = 0;
    std::vector<std::unique_ptr<Benchmark>> children = {};
    bool continue_with_parent = false;

    clock::duration current = clock::duration::zero();
    clock::time_point start_time = clock::time_point::min();
    clock::duration time_sum = clock::duration::zero();
    clock::duration time_min = clock::duration::max();
    clock::duration time_max = clock::duration::min();
  };

  /// \private
  struct BenchmarkSection : Benchmark {
    BenchmarkSection(std::string name) : Benchmark(name) {}

    ~BenchmarkSection()
    {
      if (children.size() == 0) return;
      stop();
      std::string header = name + " ";
      for (int i = 43 - header.size(); i > 0; i--) {
        header.append("─");
      }
      printf("─ Bench ─ %s─ ──────── min ── ──────── max ── "
             "──────── avg ──\n",
             header.c_str());
      for (auto& child : children) {
        child->report();
      }
      printf(
        "────────────────────────────────────────────────────── ─────────────── ─────────────── "
        "───────────────\n");
    }
  };

  /// \private
  struct BenchmarkLooper {
    BenchmarkLooper(Benchmark& bench, std::size_t iter_count) : bench(bench), iters_left(iter_count)
    {
      bench.start();
    }

    ~BenchmarkLooper()
    {
      bench.reset();
    }

    operator bool()
    {
      return iters_left > 0;
    }

    void operator++(int)
    {
      bench.stop();
      iters_left--;
      bench.start();
    }

    Benchmark& bench;

    std::size_t iters_left;
  };

  /// \private
  struct BenchmarkScope {
    BenchmarkScope(Benchmark& bench) : bench(bench)
    {
      bench.start();
    }

    ~BenchmarkScope()
    {
      bench.stop();
    }
    Benchmark& bench;
  };

  /// \private
  struct BenchmarkSkipScope {
    BenchmarkSkipScope(Benchmark& bench) : bench(bench), was_running(bench.running())
    {
      bench.pause();
    }

    ~BenchmarkSkipScope()
    {
      if (was_running) bench.start();
    }

    bool was_running;
    Benchmark& bench;
  };

} // namespace otto::test


/// \cond
#define _OBENCH_GET_1(X, ...) X
#define _OBENCH_GET_2(IGNORE, X, ...) X
#define _OBENCH_GET_3(IGNORE, IGNORE2, X, ...) X
#define _OBENCH_APPLY(MACRO, ...) MACRO(__VA_ARGS__)

#define _OBENCH_UNIQUE_NAME_LINE2(name, line) name##line
#define _OBENCH_UNIQUE_NAME_LINE(name, line) _OBENCH_UNIQUE_NAME_LINE2(name, line)
#define _OBENCH_UNIQUE_NAME(name) _OBENCH_UNIQUE_NAME_LINE(name, __LINE__)

#define _OBENCH_CHILD_INTERN(name, unique_id)                                                      \
  auto& unique_id = obench;                                                                        \
  if (::otto::test::Benchmark& obench = unique_id.child(name); true)

#define _OBENCH_SCOPE_INTERN(unused_name)                                                          \
  if (::otto::test::BenchmarkScope _obench_scope(obench); true)

#define _OBENCH_LOOP_INTERN(unused_name, count)                                                    \
  for (::otto::test::BenchmarkLooper _obench_looper(obench, count); _obench_looper;                \
       _obench_looper++)

/// \endcond

/// A Catch2 section of benchmarks.
///
/// `OBENCH` is a small addition to Catch2, adding nested and more powerful microbenchmmarks.
/// Benchmarks are created using the macro @ref OBENCH inside a `OBENCH_SECTION`.
///
/// @par Example
/// @parblock
///
/// Here is a benchmark section measuring our @ref util::string_replace() vs @ref
/// std::regex_replace().
///
/// ```cpp
/// OBENCH_SECTION ("string_replace vs regex::replace") {
///   std::string local;
///   std::regex regex;
///   OBENCH ("string_replace", 1000) {
///     OBENCH_SKIP {
///       local = long_str;
///     }
///     string_replace(local, "string", "another string");
///   }
///   OBENCH ("regex_replace", 1000) {
///     OBENCH_SKIP {
///       local = long_str;
///     }
///     OBENCH ("construct regex") {
///       regex = std::regex("string");
///     }
///     OBENCH ("replace") {
///       std::regex_replace(local, regex, "another string");
///     }
///   }
/// }
/// ```
///
/// The above benchmarks are reported to the terminal like this:
///
/// ```unparsed
/// ─ OBENCH ─ string_replace vs regex::replace ── ──────── min ── ──────── max ── ──────── avg ──
///  string_replace                                        1743 ns        14799 ns         1926 ns
///  regex_replace                                        96349 ns       172518 ns       106355 ns
///  ├ construct regex                                     8998 ns        45579 ns        10267 ns
///  └ replace                                            84227 ns       158643 ns        92788 ns
/// ────────────────────────────────────────────── ─────────────── ─────────────── ───────────────
/// ```
/// @endparblock
///
/// @param name the name of the section
///
/// @hideinitializer
#define OBENCH_SECTION(name)                                                                       \
  if (::otto::test::BenchmarkSection obench(name);                                                 \
      Catch::Section const& _OBENCH_UNIQUE_NAME(catch_internal_Section) =                          \
        Catch::SectionInfo(CATCH_INTERNAL_LINEINFO, std::string(" Benchmark ") + name))

/// Run a benchmark for the following block
///
/// @param name the name of the benchmark.
/// @param count Optional. If this argument is included, the benchmark will be run in a loop `count`
/// times.
/// @hideinitializer
#define OBENCH(...)                                                                                \
  _OBENCH_CHILD_INTERN(_OBENCH_GET_1(__VA_ARGS__, NOPE), _OBENCH_UNIQUE_NAME(_obench_parent))      \
  _OBENCH_APPLY(_OBENCH_GET_3(__VA_ARGS__, _OBENCH_LOOP_INTERN, _OBENCH_SCOPE_INTERN, NOPE),       \
                __VA_ARGS__)

/// Pause the current benchmark while executing the follow block
///
/// @hideinitializer
#define OBENCH_SKIP if (::otto::test::BenchmarkSkipScope _obench_skip_scope(obench); true)
