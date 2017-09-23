#pragma once

#include <string>
#include <vector>
#include <utility>
#include <map>
#include <chrono>
#include <numeric>
#include <algorithm>
#include <fstream>
#include <functional>

#include <json.hpp>
#include "filesystem.hpp"
#include "core/globals.hpp"

namespace top1::timer {

  struct Timer {
    using Duration = std::chrono::nanoseconds;
    using Clock = std::chrono::steady_clock;
    using TimePoint = std::chrono::time_point<Clock, Duration>;

    static double numSecs(Duration d) {
      return std::chrono::duration<double>(d).count();
    }

    bool running;
    std::vector<Duration> times;
    TimePoint start;

    Timer() = default;
    Timer(Timer&&) noexcept = default;

    void startTimer() {
      running = true;
      start = Clock::now();
    }

    void stopTimer() {
      times.push_back(Clock::now() - start);
      running = false;
    }

    Duration calcAvg() const {
      Duration sum = std::accumulate(times.begin(), times.end(),
                                     Duration(0), std::plus<Duration>());
      return sum / times.size();
    }

    Duration calcMed() const {
      auto vec = times;
      auto iter = vec.begin() + vec.size() / 2;
      std::nth_element(vec.begin(), vec.end(), iter);
      return *iter;
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
      ret["Average"] = numSecs(calcAvg());
      ret["Median"] = numSecs(calcMed());
      ret["min"] = numSecs(calcMin());
      ret["max"] = numSecs(calcMax());
      // auto tms = nlohmann::json::array();
      // for (auto&& t : times) {
      //   tms.push_back(t.count());
      // }
      // ret["measurements"] = tms;
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
    fs::path path = Globals::data_dir / "timers.json";

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

#define TIME_SCOPE(name) auto timer = ::top1::timer::dispatcher.timeScope(name);

} // top1::timer
