#pragma once

#include <csignal>
#include <functional>
#include <thread>

namespace otto::util {
  struct [[nodiscard]] SignalWaiter {
    SignalWaiter(std::initializer_list<int> signals, std::function<void(int)> handler);
    ~SignalWaiter();

    SignalWaiter(const SignalWaiter&) = delete;
    SignalWaiter& operator=(const SignalWaiter&) = delete;
    SignalWaiter(SignalWaiter&&) noexcept = delete;
    SignalWaiter& operator=(SignalWaiter&&) noexcept = delete;

  private:
    sigset_t prev_sigmask = {};
    int shutdown_signal = 0;
    std::atomic<bool> should_run_handler = true;
    std::jthread thread_;
  };

  /// Sets up a thread to wait for one of the given signals.
  ///
  /// This can be used to run signal handlers that need to call non-signal-safe
  /// functions, like basically anything other than writing to an atomic variable.
  ///
  /// NOTE: This must be called before launching any other threads, otherwise
  /// those threads will receive the signal as normal.
  [[nodiscard]] SignalWaiter handle_signals(std::initializer_list<int> signals,
                                            std::function<void(int)> handler) noexcept;
} // namespace otto::util
