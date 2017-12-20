#pragma once

#include <string>
#include <chrono>
#include <json.hpp>

/// A simple stack-based library used to time nested parts of a program.
namespace otto::util::timer {
  using timer_id = std::string;
  using time_point = std::chrono::time_point<
    std::chrono::steady_clock, std::chrono::nanoseconds>;
  using time_duration = time_point::duration::rep;

#if OTTO_ENABLE_TIMERS
  struct TimerData {
    timer_id id;
    time_duration duration;
    std::vector<TimerData> children;

    nlohmann::json to_json() const
    {
      auto obj = nlohmann::json::object();
      obj["id"] = id;
      obj["duration"] = duration;

      if (!this->children.empty()) {
        auto children = nlohmann::json::array();
        for (auto const& timer_data : this->children) {
          children.push_back(timer_data.to_json());
        }
        obj["children"] = children;
      }

      return obj;
    }  
  };

  struct ScopedTimer {
    ScopedTimer(timer_id id);
    ~ScopedTimer();

    private:
      timer_id id;
      time_point start;
      std::vector<TimerData> children;
      ScopedTimer *parent;
  };

  /// Start a timer with id `id`, and push it to the stack.
  ScopedTimer start(timer_id id);

  void save_data();
#else
  void start(timer_id id);
  void save_data();
#endif

} // otto::util::timer
