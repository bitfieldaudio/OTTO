#include "unix_signals.hpp"

#include <csignal>
#include <utility>

namespace otto::util {

  SignalWaiter::SignalWaiter(std::initializer_list<int> signals, std::function<void(int)> handler)
  {
    // block signals in this thread and subsequently
    // spawned threads
    sigset_t sigset;
    sigemptyset(&sigset);
    for (int signal : signals) {
      shutdown_signal = signal;
      sigaddset(&sigset, signal);
    }
    pthread_sigmask(SIG_BLOCK, &sigset, &prev_sigmask);

    auto func = [this, sigset, handler = std::move(handler)] {
      int signum = 0;
      sigwait(&sigset, &signum);
      if (should_run_handler) handler(signum);
    };
    thread_ = std::jthread(func);
  }

  SignalWaiter::~SignalWaiter()
  {
    should_run_handler = false;
    std::raise(shutdown_signal);
    pthread_sigmask(SIG_SETMASK, &prev_sigmask, nullptr);
  }

  SignalWaiter wait_for_signal(std::initializer_list<int> signals, std::function<void(int)> handler) noexcept
  {
    return {signals, std::move(handler)};
  }
} // namespace otto::util
