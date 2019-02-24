#pragma once

#include <atomic>
#include <condition_variable>
#include <functional>
#include <mutex>
#include <thread>

namespace otto::util {

  struct thread {
    template<typename Func>
    thread(Func&& func) : std_thread(std::forward<Func>(func), [this] { return should_run(); })
    {}

    ~thread()
    {
      join();
    }

    void join()
    {
      _should_run = false;
      std_thread.join();
    }

  private:
    bool should_run() const noexcept
    {
      return _should_run;
    }

    std::atomic_bool _should_run = true;
    std::thread std_thread;
  };

  struct triggered_thread {
    template<typename Func>
    triggered_thread(Func&& func)
      : std_thread(std::forward<Func>(func), [this] { return should_run(); })
    {}

    ~triggered_thread()
    {
      join();
    }

    void trigger() {
      _trigger.notify_all();
    }

    void join()
    {
      _should_run = false;
      _trigger.notify_all();
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

} // namespace otto::util
