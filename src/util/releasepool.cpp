#include <algorithm>
#include <thread>
#include <chrono>

#include "releasepool.h"

// #############################################
// ## Timer Implementation
// #############################################

void Timer::runTimerCallback(Timer *self) {
  while (self->exit) {
    self->timerCallback();
    if (self->mutex.try_lock_for(std::chrono::seconds(self->time))) {
      self->mutex.unlock();
      return;
    }
  }
}

void Timer::startTimer(uint newTime) {
  stopTimer();
  time = newTime;
  mutex.lock();
  thread = std::thread(Timer::runTimerCallback, this);
}

void Timer::stopTimer() {
  exit = 0;
  mutex.unlock();
  thread.join();
}

// #############################################
// ## ReleasePool Implementation
// #############################################

template<typename T>
  void ReleasePool::add (const std::shared_ptr<T>& object) {
  if (object.empty())
    return;
  std::lock_guard<std::mutex> lock (m);
  pool.emplace_back (object);
}

void ReleasePool::timerCallback() {
  std::lock_guard<std::mutex> lock (m);
  pool.erase(
    std::remove_if (
      pool.begin(), pool.end(),
      [] (auto& object) { return object.use_count() <= 1; } ),
    pool.end());
}
