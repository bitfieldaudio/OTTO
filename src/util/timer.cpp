#include "timer.hpp"

#include <thread>
#include <sstream>
#include <mutex>

#include "util/exception.hpp"

namespace otto::util::timer {

// otto::util::timer::Timer ///////////////////////////////////////////////////

  Timer::Timer(const timer_id& id)
    : id (id)
  {}

  Timer::Timer(timer_id&& id)
    : id (std::move(id))
  {}

  void Timer::start()
  {
    start_time = time_point::clock::now();
    running = true;
  }

  void Timer::stop()
  {
    data.push_back(time_point::clock::now() - start_time);
    running = false;
  }

  void Timer::tick()
  {
    auto now = time_point::clock::now();
    if (running) {
      data.push_back(now - start_time);
    } else {
      start_time = now;
      running = true;
    }
  }

  nlohmann::json Timer::serialize() const
  {
    auto arr = nlohmann::json::array();
    for (auto&& dur : data) {
      arr.push_back(dur.count());
    }
    auto json_chldrn = nlohmann::json::object();
    for (auto&& c : children) {
      json_chldrn[c.id] = c.serialize();
    }
    return {
      {"data", arr},
      {"children", json_chldrn}
    };
  }

// otto::util::timer::ScopedTimer /////////////////////////////////////////////

  ScopedTimer::ScopedTimer(Timer& timer) noexcept
    : timer (&timer)
  {}

  ScopedTimer::ScopedTimer(Timer* timer) noexcept
    : timer (timer)
  {}

  ScopedTimer::ScopedTimer(ScopedTimer&& rhs) noexcept
    : timer (rhs.timer)
  {
    rhs.timer = nullptr;
  }

  ScopedTimer::~ScopedTimer()
  {
    if (timer != nullptr) stop();
  }

// otto::util::timer free functions ///////////////////////////////////////////

  /// This owns one vector per thread
  std::vector<Timer> thread_timers;

  static std::mutex mutex;

  static Timer& create_thread_timer() {
    std::ostringstream s;
    s << "Thread ";
#if defined (__unix__) || (defined (__APPLE__) && defined (__MACH__))
    char buf[256];
    s << pthread_getname_np(pthread_self(), buf, 256);
#else
    s << std::this_thread::get_id();
#endif
    {
      std::lock_guard lock (mutex);
      return thread_timers.emplace_back(s.str());
    }
  }

  thread_local std::vector<Timer*> timer_stack = {&create_thread_timer()};

  Timer& find_or_make(timer_id id)
  {
    if (timer_stack.size() == 0) {
      throw util::exception("Timer stack empty. That shouldnt happen!");
    }
    auto& stack_top = *timer_stack.back();
    if (stack_top.id == id) {
      return stack_top;
    }
    auto& timers = stack_top.children;
    auto iter = std::find_if(timers.begin(), timers.end(),
      [id] (const Timer& t) {
        return t.id == id;
      });
    if (iter != timers.end()) {
      return *iter;
    } else {
      return timers.emplace_back(id);
    }
  }

  Timer& start(timer_id id)
  {
    return start(find_or_make(id));
  }

  Timer& start(Timer& timer)
  {
    timer_stack.push_back(&timer);
    timer.start();
    return timer;
  }

  ScopedTimer start_scoped(timer_id id)
  {
    return start_scoped(find_or_make(id));
  }

  ScopedTimer start_scoped(Timer& timer)
  {
    timer_stack.push_back(&timer);
    timer.start();
    return ScopedTimer{timer};
  }

  void stop()
  {
    if (timer_stack.size() != 0U) {
      timer_stack.back()->stop();
      timer_stack.pop_back();
    } else {
      throw std::runtime_error("Attempted to stop the last timer");
    }
  }

  Timer& tick(timer_id id)
  {
    return tick(find_or_make(id));
  }

  Timer& tick(Timer& timer)
  {
    if (timer_stack.back() != &timer) {
      timer_stack.push_back(&timer);
    }
    timer.tick();
    return timer;
  }

  nlohmann::json serialize()
  {
    std::lock_guard lock (mutex);
    auto arr = nlohmann::json::object();
    for (auto timer : thread_timers) {
      arr[timer.id] = timer.serialize();
    }
    return arr;
  }

}
