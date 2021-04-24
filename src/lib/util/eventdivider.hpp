#pragma once

#include <chrono>
#include <ratio>

#include "app/input.hpp"

namespace otto::util {
  /// Utility object for dividing down a stream of events
  /// N: number of steps to divide by
  template<int N>
  struct EventDivider {
    EventDivider() = default;

    int operator()(int& i)
    {
      count += i;
      auto res = static_cast<int>(count >= N) - static_cast<int>(count <= -N);
      count %= N;
      return res;
    }
    int operator()(EncoderEvent& e)
    {
      return operator()(e.steps);
    }

  private:
    int count = 0;
  };

  // Event divider with a timeout to reset
  template<int N, int timeout_ms>
  struct EventDividerWithTimeout {
    EventDividerWithTimeout() : last_time(std::chrono::system_clock::now()) {}

    int operator()(EncoderEvent& e)
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
