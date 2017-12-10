#include "timer.hpp"

#include <thread>
#include <sstream>
#include <mutex>

#include "util/exception.hpp"

#define ENABLED OTTO_ENABLE_TIMERS

namespace otto::util::timer {

// otto::util::timer::Timer ///////////////////////////////////////////////////

Timer::Timer(const timer_id& id)
#if ENABLED
  : id(id)
#endif
{}

Timer::Timer(timer_id&& id)
#if ENABLED
  : id(std::move(id))
#endif
{}

void Timer::start()
{
#if ENABLED
  start_time = time_point::clock::now();
  running    = true;
#endif
}

void Timer::stop()
{
#if ENABLED
  data.push_back(time_point::clock::now() - start_time);
  running = false;
#endif
}

void Timer::tick()
{
#if ENABLED
  auto now = time_point::clock::now();
  if (running) {
    data.push_back(now - start_time);
  } else {
    start_time = now;
    running    = true;
  }
#endif
}

nlohmann::json Timer::serialize() const
{
#if ENABLED
  auto arr = nlohmann::json::array();
  for (auto&& dur : data) {
    arr.push_back(dur.count());
  }
  auto json_chldrn = nlohmann::json::object();
  for (auto&& c : children) {
    json_chldrn[c.id] = c.serialize();
  }
  return {{"data", arr}, {"children", json_chldrn}};
#else
  return {};
#endif
}

// otto::util::timer::ScopedTimer /////////////////////////////////////////////

  ScopedTimer::ScopedTimer(Timer& timer) noexcept
#if ENABLED
    : timer (&timer)
#endif
  {}

  ScopedTimer::ScopedTimer(Timer* timer) noexcept
#if ENABLED
    : timer (timer)
#endif
  {}

  ScopedTimer::ScopedTimer(ScopedTimer&& rhs) noexcept
#if ENABLED
    : timer (rhs.timer)
#endif
  {
#if ENABLED
    rhs.timer = nullptr;
#endif
  }

  ScopedTimer::~ScopedTimer()
  {
#if ENABLED
    if (timer != nullptr) stop();
#endif
  }

// otto::util::timer free functions ///////////////////////////////////////////

#if ENABLED
  struct TimerStack {
    Timer root;
    std::vector<Timer*> stack;

    TimerStack(const timer_id& name)
      : root (name),
        stack {&root}
    {}
  };

  /// This owns one vector per thread
  std::vector<TimerStack> thread_stacks;

  static std::mutex mutex;

  static TimerStack* create_timer_stack() {
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
      return &thread_stacks.emplace_back(s.str());
    }
  }

  // Do not access directly! use the function below
  thread_local TimerStack* _timer_stack = nullptr;

  static auto& timer_stack() noexcept
  {
    if (_timer_stack == nullptr) {
      _timer_stack = create_timer_stack();
    }
    return _timer_stack->stack;
  }
#else
  Timer one_timer_to_rule_them_all("");
#endif

  Timer& find_or_make(timer_id id)
  {
#if ENABLED
    if (timer_stack().size() == 0) {
      throw util::exception("Timer stack empty. That shouldnt happen!");
    }
    auto& stack_top = *timer_stack().back();
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
#else
    return one_timer_to_rule_them_all;
#endif
  }

  Timer& start(timer_id id)
  {
    return start(find_or_make(id));
  }

  Timer& start(Timer& timer)
  {
#if ENABLED
    timer_stack().push_back(&timer);
    timer.start();
#endif
    return timer;
  }

  ScopedTimer start_scoped(timer_id id)
  {
    return start_scoped(find_or_make(id));
  }

  ScopedTimer start_scoped(Timer& timer)
  {
#if ENABLED
    timer_stack().push_back(&timer);
    timer.start();
#endif
    return ScopedTimer{timer};
  }

  void stop()
  {
#if ENABLED
    if (timer_stack().size() != 0U) {
      timer_stack().back()->stop();
      timer_stack().pop_back();
    } else {
      throw std::runtime_error("Attempted to stop the last timer");
    }
#endif
  }

  Timer& tick(timer_id id)
  {
    return tick(find_or_make(id));
  }

  Timer& tick(Timer& timer)
  {
#if ENABLED
    if (timer_stack().back() != &timer) {
      timer_stack().push_back(&timer);
    }
    timer.tick();
#endif
    return timer;
  }

  nlohmann::json serialize()
  {
#if ENABLED
    std::lock_guard lock (mutex);
    auto arr = nlohmann::json::object();
    for (auto timer : thread_stacks) {
      arr[timer.root.id] = timer.root.serialize();
    }
    return arr;
#else
    return {};
#endif
  }

}
