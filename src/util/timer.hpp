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


/// A simple stack-based library used to time nested parts of a program.
///
/// if !OTTO_ENABLE_TIMERS, all implementations are empty
namespace otto::util::timer {

  /// The type used to identify timers
  using timer_id = std::string;

  /// Contains the actual timing data.
  ///
  /// Should only very rarely be interacted with directly by the user.
  struct Timer {

    /// A `std::chrono::time_point` used to measure timings.
    using time_point = std::chrono::time_point<
      std::chrono::steady_clock, std::chrono::nanoseconds>;

    /// Construct a new timer with id `id`
    ///
    /// \effects set member variable `id` to `id`
    /// \remarks at this point, `start_time` is undefined.
    Timer(const timer_id& id);

    /// Construct a new timer with id `id`
    ///
    /// \effects set member variable `id` to `id`
    /// \remarks at this point, `start_time` is undefined.
    Timer(timer_id&& id);

    /// Start the timer
    ///
    /// \effects sets `start_time` to `time_point::clock::now()`
    /// \postconditions `running == true`
    /// \remarks Do *not* use this function. In most cases you want the free
    /// function which also pushes and pops from/to the stack
    void start();

    /// Stop the timer
    ///
    /// \requires `running == true`
    /// \effects pushes `time_point::clock::now() - start_time` to the back of `data`.
    /// \postconditions `running == false`
    /// \remarks Do *not* use this function. In most cases you want the free
    /// function which also pushes and pops from/to the stack
    void stop();

    /// Tick the timer
    ///
    /// \effects if `running == false`, same as `start()`. Otherwise, push
    /// `time_point::clock::now() - start_time` to the back of `data`, and
    /// assign `time_point::clock::now()` to `start_time`
    /// \postconditions `running == true`
    /// \complexity `time_point::clock::now()` is only called once.
    /// \remarks Do *not* use this function. In most cases you want the free
    /// function which also pushes and pops from/to the stack
    void tick();

    /// Simple serialization of the Timer data, with all the children nested.
    nlohmann::json serialize() const;

    timer_id id;
    std::vector<Timer> children;
    std::vector<time_point::duration> data;
    time_point start_time;
    bool running {false};
  };

  /// A pointer to a timer, which stops and pops the timer upon destruction.
  ///
  /// This is useful for scope timers, and must always be moved from
  struct ScopedTimer {

    /// Move only
    ScopedTimer(const ScopedTimer& rhs) = delete;

    /// Move construct this handler
    ///
    /// \postconditions `this->timer == rhs.timer` and also,
    /// `rhs.timer == nullptr`
    ScopedTimer(ScopedTimer&& rhs) noexcept;

    /// Destruct the handler and stop the timer.
    ///
    /// \effects if `timer != nullptr`, call `stop(*this)`.
    /// Otherwise, do nothing
    ~ScopedTimer();

  private:

    /// Construct a handle to the provided timer
    ///
    /// \postconditions `this->timer == &timer`
    explicit ScopedTimer(Timer& timer) noexcept;

    /// Construct a handle to the provided timer
    ///
    /// \note `timer` can be null
    /// \postconditions `this->timer == timer`
    explicit ScopedTimer(Timer* timer) noexcept;

    Timer* timer;

    friend ScopedTimer start_scoped(timer_id);
    friend ScopedTimer start_scoped(Timer&);
  };

  /// Find or create a child of the current top of the stack, which matches id
  /// `id`.
  Timer& find_or_make(timer_id id);

  /// Start a timer with id `id`, and push it to the stack.
  Timer& start(timer_id id);

  /// Start `timer` and push it onto the stack.
  Timer& start(Timer& timer);

  /// Start a timer with id `id`, and push it to the stack.
  ScopedTimer start_scoped(timer_id id);

  /// Start the timer pointed to by `TimerHandle`
  ScopedTimer start_scoped(Timer&);

  /// Stop the current timer, and pop it off the stack
  void stop();

  /// Stop the timer, and pop it off the stack if it is there.
  ///
  /// \effects `timer.stop()` and, if `&timer` is in `timer_stack`, stop and pop
  /// it and everything after it.
  // void stop(Timer& timer);

  /// Tick a timer with id `id`, and push it to the back of the stack if it is
  /// not there already.
  Timer& tick(timer_id id);

  /// Tick `timer`
  ///
  /// \effects `timer.tick()` and, if `timer_stack.back() != &timer`, push it to
  /// the stack.
  Timer& tick(Timer& timer);

  nlohmann::json serialize();

} // otto::util::timer

// M A C R O S /////////////////////////////////////////////////////////////////

#if OTTO_ENABLE_TIMERS
#define TIME_SCOPE(name) auto scope_timer = ::otto::util::timer::start_scoped(name);
#else
#define TIME_SCOPE(name)
#endif

