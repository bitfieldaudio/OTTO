#include "runtime.hpp"

namespace otto::services {

  using Stage = Runtime::Stage;

  Stage Runtime::stage() const noexcept
  {
    return static_cast<Stage>(stage_.load());
  }

  bool Runtime::should_run() const noexcept
  {
    auto s = stage();
    return s == Stage::running || s == Stage::initializing;
  }

  void Runtime::set_stage(Stage s) noexcept
  {
    std::unique_lock lock(mutex_);
    stage_.store(static_cast<std::underlying_type_t<Stage>>(s));
    std::erase_if(hooks_, [s](auto& f) { return f(s); });
    cond_.notify_all();
  }

  void Runtime::request_stop(ExitCode) noexcept
  {
    set_stage(Stage::stopping);
  }

  bool Runtime::wait_for_stage(Stage s, chrono::duration timeout) noexcept
  {
    std::unique_lock lock(mutex_);
    if (timeout == chrono::duration::zero()) {
      cond_.wait(lock, [&] { return stage_ >= util::underlying(s); });
    } else {
      cond_.wait_for(lock, timeout, [&] { return stage_ >= util::underlying(s); });
    }
    return stage_ == util::underlying(s);
  }

  void Runtime::on_stage_change(std::function<bool(Stage s)> f) noexcept
  {
    hooks_.emplace_back(std::move(f));
  }

  bool Runtime::wait_for_stage(Stage s) noexcept
  {
    return wait_for_stage(s, chrono::duration::zero());
  }

  void Runtime::on_enter_stage(Stage s, std::function<void()> f) noexcept
  {
    on_stage_change([s, f = std::move(f)](Stage new_s) {
      if (new_s == s) f();
      return new_s == s;
    });
  }
} // namespace otto::services
