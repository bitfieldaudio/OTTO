#pragma once

#include <string>
#include <vector>
#include <utility>
#include <map>
#include <chrono>
#include <numeric>
#include <algorithm>
#include <fstream>

#include <plog/Log.h>
#include <json.hpp>

namespace top1::timer {

  struct Timer {
    using Duration = std::chrono::nanoseconds;
    using Clock = std::chrono::steady_clock;
    using TimePoint = std::chrono::time_point<Clock, Duration>;

    std::vector<Duration> times;
    TimePoint start;

    Timer() = default;
    Timer(Timer&&) noexcept = default;

    void startTimer() {
      start = Clock::now();
    }

    void stopTimer() {
      times.push_back(Clock::now() - start);
    }

    Duration calcAvg() const {
      Duration sum = std::accumulate(times.begin(), times.end(),
                                     Duration(0), std::plus());
      return sum / times.size();
    }

    Duration calcMin() const {
      return *std::min_element(times.begin(), times.end());
    }

    Duration calcMax() const {
      return *std::max_element(times.begin(), times.end());
    }

    nlohmann::json jsonSerialize() const {
      auto ret = nlohmann::json::object();
      ret["count"] = times.size();
      ret["avg"] = calcAvg().count();
      ret["min"] = calcMin().count();
      ret["max"] = calcMax().count();
      auto tms = nlohmann::json::array();
      for (auto&& t : times) {
        tms.push_back(t.count());
      }
      ret["measurements"] = tms;
      return ret;
    }
  };

  /// RAII based timer. Times from creation until destruction.
  struct ScopeTimer {

    Timer& timer;

    ScopeTimer(Timer& t) : timer (t) {
      timer.startTimer();
    }

    ~ScopeTimer() {
      timer.stopTimer();
    }
  };

  struct TimerDispatcher {
    std::unordered_map<std::string, Timer> timers;
    std::string path = "data/timers.json";

    virtual ~TimerDispatcher() {}

    /// Time a call to function `f`
    template<typename Callable, typename... Args>
    auto timedCall(const std::string& name, Callable&& f, Args... args) {
      Timer& timer = timers[name];
      timer.startTimer();
      auto&& ret = std::invoke(std::forward<Callable>(f), std::forward<Args>(args)...);
      timer.stopTimer();
      return ret;
    }

    ScopeTimer timeScope(const std::string& name) {
      return ScopeTimer(timers[name]);
    }

    nlohmann::json jsonSerialize() {
      nlohmann::json output = nlohmann::json::object();
      for (auto&& [n, t] : timers) {
        output[n] = t.jsonSerialize();
        LOGD << "Timer: " << t.jsonSerialize().dump();
      }
      return output;
    }

    void writeToFile() {
      std::ofstream stream(path, std::ios::trunc);
      stream << std::setw(2) << jsonSerialize() << std::endl;
      stream.close();
    }
  };

  /// Writes to file on destruction. 
  struct GlobalTimerDispatcher : public TimerDispatcher {

    GlobalTimerDispatcher() : TimerDispatcher() {
      timers["Program time"].startTimer();
    }

    ~GlobalTimerDispatcher() {
      timers["Program time"].stopTimer();
      writeToFile();
    }
  };

  inline GlobalTimerDispatcher dispatcher {};

#define TIME_SCOPE(name) auto timer = top1::timer::dispatcher.timeScope(name);

} // top1::timer
