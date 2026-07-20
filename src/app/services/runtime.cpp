#include "runtime.hpp"

#include "lib/util/unix_signals.hpp"

#if defined(__APPLE__)
#include <dispatch/dispatch.h>
#include <csignal>
#endif

namespace otto::services {

#if defined(__APPLE__)
  namespace {
    RuntimeController* g_rt = nullptr;
    dispatch_source_t g_sigint_src = nullptr;
    dispatch_source_t g_sigterm_src = nullptr;

    void on_dispatch_signal(void* ctx)
    {
      const int signo = static_cast<int>(reinterpret_cast<intptr_t>(ctx));
      if (g_rt == nullptr) return;
      LOGI("Got signal {}, stopping...", signo);
      g_rt->request_stop();
      g_rt->wake();
    }

    void install_dispatch_signal(int signo, dispatch_source_t& slot)
    {
      ::signal(signo, SIG_IGN);
      slot = dispatch_source_create(DISPATCH_SOURCE_TYPE_SIGNAL, static_cast<uintptr_t>(signo), 0,
                                    dispatch_get_global_queue(QOS_CLASS_USER_INITIATED, 0));
      dispatch_set_context(slot, reinterpret_cast<void*>(static_cast<intptr_t>(signo)));
      dispatch_source_set_event_handler_f(slot, &on_dispatch_signal);
      dispatch_resume(slot);
    }
  } // namespace
#endif

  RuntimeController::RuntimeController() noexcept
#if !defined(__APPLE__)
    : sig_wait_({SIGINT, SIGTERM}, [this](int sig) {
        LOGI("Got signal {}, stopping...", sig);
        request_stop();
        if (wake_cb_) wake_cb_();
      })
#endif
  {
#if defined(__APPLE__)
    g_rt = this;
    // sigwait-based SignalWaiter is unreliable on macOS once CoreAudio/MIDI
    // threads reset the process signal mask. GCD signal sources are not.
    install_dispatch_signal(SIGINT, g_sigint_src);
    install_dispatch_signal(SIGTERM, g_sigterm_src);
#endif
  }

  RuntimeController::~RuntimeController() noexcept
  {
#if defined(__APPLE__)
    if (g_sigint_src) {
      dispatch_source_cancel(g_sigint_src);
      g_sigint_src = nullptr;
    }
    if (g_sigterm_src) {
      dispatch_source_cancel(g_sigterm_src);
      g_sigterm_src = nullptr;
    }
    if (g_rt == this) g_rt = nullptr;
#endif
    request_stop();
  }

  void RuntimeController::set_wake_callback(std::function<void()> cb) noexcept
  {
    wake_cb_ = std::move(cb);
  }

  void RuntimeController::wake() noexcept
  {
    if (wake_cb_) wake_cb_();
  }

  bool RuntimeController::stop_requested() const noexcept
  {
    return !should_run_;
  }

  void RuntimeController::wait_for_stop(chrono::duration timeout) noexcept
  {
    {
      std::unique_lock lock(mutex_);
      if (timeout == chrono::duration::zero()) {
        cond_.wait(lock, [&] { return !should_run_; });
      } else {
        cond_.wait_for(lock, timeout, [&] { return !should_run_; });
      }
    }
    request_stop();
  }

  void RuntimeController::request_stop(ExitCode) noexcept
  {
    std::unique_lock lock(mutex_);
    should_run_ = false;
    cond_.notify_all();
  }

  bool RuntimeController::should_run() const noexcept
  {
    return should_run_;
  }

  //  RuntimeLock::RuntimeLock(RuntimeController& rc, itc::QueueExecutor& ex) noexcept : rc_(rc), ex_(ex)
  //  {
  //    std::scoped_lock l(rc.mutex_);
  //    is_leader_ = rc.locks_.empty(); // NOLINT
  //    rc.locks_.emplace_back(this);
  //  }
  //
  //  RuntimeLock::~RuntimeLock() noexcept
  //  {
  //    sync_exit();
  //  }
  //
  //  bool RuntimeLock::should_run() noexcept
  //  {
  //    return rc_.should_run();
  //  }
  //
  //  void RuntimeLock::sync_exit(ExitCode ec) noexcept
  //  {
  //    if (should_run()) rc_.request_stop(ec);
  //    while (true) {
  //      {
  //        std::scoped_lock l(mutex_);
  //        if (rc_.exit_is_done_) {
  //          std::scoped_lock l(rc_.mutex_);
  //          std::erase(rc_.locks_, this);
  //          return;
  //        }
  //        did_run_ = did_run_ || ex_.run_queued_functions();
  //        has_tried_running_ = true;
  //      }
  //      if (is_leader_) {
  //        bool all_ready = std::ranges::all_of(rc_.locks_, [](auto& l) { return l->has_tried_running_.load(); });
  //        if (all_ready) {
  //          for (auto& l : rc_.locks_) {
  //            l->mutex_.lock();
  //          }
  //          rc_.exit_is_done_ = std::ranges::none_of(rc_.locks_, [](auto& l) { return l->did_run_; });
  //          for (auto& l : rc_.locks_) {
  //            l->mutex_.unlock();
  //          }
  //        }
  //      }
  //    }
  //  }
} // namespace otto::services
