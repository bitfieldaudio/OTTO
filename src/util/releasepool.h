#pragma once

#include <memory>
#include <vector>
#include <mutex>
#include <thread>
#include <atomic>


/**
 * A reusable timer.
 *
 * @note Allways start & stop from the same thread
 * @todo Fix that^
 */
class Timer {
public:
  uint time;

  Timer() : exit(0) {};
  void startTimer(uint time);
  void stopTimer();
protected:
  virtual void timerCallback();
  std::thread thread;
private:
  std::atomic_bool exit;
  std::timed_mutex mutex;
  static void runTimerCallback(Timer *self);
};

/**
 * Extremely crude GC.
 */
class ReleasePool : private Timer {
public:
  ReleasePool() { startTimer(1000); }
  ~ReleasePool() { stopTimer(); }

  template<typename T> void add (const std::shared_ptr<T>& object);
private:
  void timerCallback() override;
  std::vector<std::shared_ptr<void>> pool;
  std::mutex m;
};
