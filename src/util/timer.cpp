#include "timer.hpp"

#include <thread>
#include <sstream>

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
    for (auto dur : data) {
      arr.push_back(dur.count());
    }
    return arr;
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

  ScopedTimer::~ScopedTimer() noexcept
  {
    if (timer != nullptr) stop();
  }

// otto::util::timer free functions ///////////////////////////////////////////

  static std::string get_thread_name() {
    std::ostringstream s;
    s << std::this_thread::get_id();
    return s.str();
  }

  thread_local Timer root_timer {get_thread_name()};
  thread_local std::vector<Timer*> timer_stack = {&root_timer};

  Timer& find_or_make(timer_id id)
  {
    auto& timers = timer_stack.back()->children;
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
    auto arr = nlohmann::json::array();
    for (auto timer : timer_stack) {
      arr.push_back(timer->serialize());
    }
    return arr;
  }

}
