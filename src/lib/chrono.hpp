#pragma once

#include <chrono>

namespace otto::chrono {

  using namespace std::chrono;

  using clock = std::chrono::system_clock;
  using duration = clock::duration;
  using time_point = std::chrono::time_point<clock, duration>;

  inline struct timespec to_timespec(time_point t) noexcept
  {
    long secs = duration_cast<seconds>(t.time_since_epoch()).count();
    long nsc = duration_cast<nanoseconds>(t.time_since_epoch() % seconds(1)).count();
    return {secs, nsc};
  }

  inline time_point to_time_point(struct timespec t) noexcept
  {
    return time_point(duration_cast<duration>(seconds(t.tv_sec) + nanoseconds(t.tv_nsec)));
  }

} // namespace otto::chrono

namespace otto {
  using namespace std::literals::chrono_literals;
}
