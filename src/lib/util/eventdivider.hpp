#pragma once

#include <chrono>
#include <ratio>

#include "app/input.hpp"

namespace otto::util {
  /// Utility object for dividing down a stream of events
  /// N: number of steps to divide by
  /// duration: timeout in milliseconds
  template<int N, int timeout_ms>
  struct EventDivider {
    EventDivider() : last_time(std::chrono::system_clock::now()) {}

    int operator()(EncoderEvent e)
    {
      auto steps = e.steps;
      auto now = e.timestamp;
      if (now - last_time > timeout) count = 0; // NOLINT
      last_time = now;
      count += steps;
      auto res = static_cast<int>(count >= N) - static_cast<int>(count <= -N);
      count %= N;
      return res;
    }

  private:
    int count = 0;
    otto::chrono::time_point last_time;
    otto::chrono::duration timeout = chrono::milliseconds(timeout_ms);
  };
} // namespace otto::util
