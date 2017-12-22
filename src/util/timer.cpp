#include "timer.hpp"

#include <mutex>
#include <thread>
#include <memory>
#include <fstream>
#include <plog/Log.h>
#include "core/globals.hpp"

namespace otto::util::timer {
#if OTTO_ENABLE_TIMERS
  struct ThreadTimer {
    ThreadTimer(std::string id) : id(id), active_timer(nullptr) {}

    std::string id;
    std::vector<TimerData> history;
    ScopedTimer * active_timer;

    nlohmann::json to_json() const
    {
      auto obj = nlohmann::json::object();

      if (!this->history.empty()) {
        auto history = nlohmann::json::array();

        for (auto const& timer_data : this->history) {
          history.push_back(timer_data.to_json());
        }

        obj["history"] = history;
      }

      return obj;
    }  
  };

  static std::mutex mutex;
  static std::map<std::string, ThreadTimer> thread_timers;

  static std::string get_thread_id() {
    static thread_local std::string thread_id;
    if (thread_id.empty()) {
      std::ostringstream s;
      s << "Thread " << std::this_thread::get_id();
      thread_id = s.str();
    }

    return thread_id;
  }

  static ThreadTimer& get_thread_timer() {
    static thread_local ThreadTimer* thread_timer = nullptr;

    std::lock_guard lock(mutex);

    if (thread_timer == nullptr) {
      auto thread_id = get_thread_id();
      auto [iter, created] = thread_timers.emplace(thread_id, thread_id);
      thread_timer = &(iter->second);
    }

    return *thread_timer;
  }

  ScopedTimer::ScopedTimer(std::string id)
    : id(id), start(time_point::clock::now())
  {
    auto& thread_timer = get_thread_timer();
    parent = thread_timer.active_timer;
    thread_timer.active_timer = this;
  }

  ScopedTimer::~ScopedTimer() {
    auto duration = (time_point::clock::now() - start).count();

    auto& thread_timer = get_thread_timer();

    auto& target = (parent == nullptr)
      ? thread_timer.history
      : parent->children;

    target.emplace_back(TimerData{id, duration, children});
    thread_timer.active_timer = parent;
  }

  ScopedTimer start(std::string id)
  {
    return ScopedTimer{id};
  }

  static nlohmann::json to_json()
  {
    std::lock_guard lock(mutex);

    auto obj = nlohmann::json::object();

    for (auto const& [key, thread_timer] : thread_timers) {
      obj[thread_timer.id] = thread_timer.to_json();
    }

    return obj;
  }

  void save_data() {
    auto filepath = (global::data_dir / "timers.json").string();
    auto f = std::ofstream(filepath, std::ios::trunc);
    f << std::setw(2) << to_json() << '\n';
    f.close();
  }
#else
  void start(timer_id id)
  {
  }

  void save_data()
  {
  }
#endif
}
