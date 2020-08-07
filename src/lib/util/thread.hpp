#pragma once

#include <atomic>
#include <condition_variable>
#include <ctime>
#include <functional>
#include <mutex>
#include <thread>

#include "lib/chrono.hpp"

namespace otto::util {

  struct triggered_thread {
    triggered_thread() = default;

    template<typename Func>
    triggered_thread(Func&& func) : std_thread(std::forward<Func>(func), [this] { return should_run(); })
    {}

    triggered_thread(const triggered_thread&) = delete;
    triggered_thread(triggered_thread&&) = delete;

    template<typename Func>
    triggered_thread& operator=(Func&& func)
    {
      std_thread = std::thread{std::forward<Func>(func), [this] { return should_run(); }};
      return *this;
    }

    ~triggered_thread()
    {
      if (!std_thread.joinable()) return;
      join();
    }

    void trigger()
    {
      _trigger.notify_all();
    }

    void join()
    {
      {
        std::unique_lock lock{_mutex};
        _should_run = false;
      }
      trigger();
      std_thread.join();
    }

  private:
    bool should_run() noexcept
    {
      std::unique_lock lock{_mutex};
      if (!_should_run) return false;
      _trigger.wait(lock);
      return _should_run;
    }
    std::atomic_bool _should_run = true;
    std::mutex _mutex;
    std::condition_variable _trigger;
    std::thread std_thread;
  };

  struct sleeper_thread {
    sleeper_thread() = default;
    template<typename Func>
    sleeper_thread(Func&& func) : std_thread(std::forward<Func>(func), [this] { return should_run(); })
    {}

    sleeper_thread(const sleeper_thread&) = delete;
    sleeper_thread(sleeper_thread&&) = delete;

    template<typename Func>
    sleeper_thread& operator=(Func&& func)
    {
      std_thread = std::thread{std::forward<Func>(func), [this] { return should_run(); }};
      return *this;
    }

    ~sleeper_thread()
    {
      if (std_thread.joinable()) join();
    }

    void trigger()
    {
      _trigger.notify_all();
    }

    void join()
    {
      {
        std::unique_lock lock{_mutex};
        _should_run = false;
      }
      _trigger.notify_all();
      std_thread.join();
    }

    bool should_run() noexcept
    {
      return _should_run;
    }

    auto sleep_for(chrono::duration dur)
    {
      auto lock = std::unique_lock(_mutex);
      return _trigger.wait_for(lock, dur);
    }

    auto sleep_until(chrono::time_point time)
    {
      auto lock = std::unique_lock(_mutex);
      return _trigger.wait_until(lock, time);
    }

    auto wait()
    {
      auto lock = std::unique_lock(_mutex);
      _trigger.wait(lock);
    }

    auto wake_up() noexcept
    {
      _trigger.notify_all();
    }

    auto running() noexcept -> bool
    {
      return _should_run;
    }

  private:
    std::atomic_bool _should_run = true;
    std::mutex _mutex;
    std::condition_variable _trigger;
    std::thread std_thread;
  };

} // namespace otto::util
