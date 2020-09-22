#include "runtime.hpp"

namespace otto::services {

  using Stage = Runtime::Stage;

  Stage RuntimeImpl::stage() const noexcept
  {
    return static_cast<Stage>(stage_.load());
  }

  bool RuntimeImpl::should_run() const noexcept
  {
    auto s = stage();
    return s == Stage::running || s == Stage::initializing;
  }

  void RuntimeImpl::set_stage(Stage s) noexcept
  {
    stage_.store(static_cast<std::underlying_type_t<Stage>>(s));
    std::erase_if(hooks_, [s](auto& f) { return f(s); });
    cond_.notify_all();
  }

  void RuntimeImpl::request_stop(ExitCode) noexcept
  {
    set_stage(Stage::stopping);
  }

  bool RuntimeImpl::wait_for_stage(Stage s, chrono::duration timeout) noexcept
  {
    std::unique_lock lock(mutex_);
    if (timeout == chrono::duration::zero()) {
      cond_.wait(lock, [&] { return stage_ >= util::underlying(s); });
    } else {
      cond_.wait_for(lock, timeout, [&] { return stage_ >= util::underlying(s); });
    }
    return stage_ == util::underlying(s);
  }
} // namespace otto::services
