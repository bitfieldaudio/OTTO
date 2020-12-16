#pragma once

#include <condition_variable>
#include <mutex>

#include "lib/util/utility.hpp"

#include "lib/chrono.hpp"
#include "lib/core/service.hpp"

namespace otto::services {

  /// Manages the runtime of the application
  struct Runtime : core::Service<Runtime> {
    enum struct ExitCode { normal };
    enum struct Stage {
      initializing,
      running,
      stopping,
    };
    Stage stage() const noexcept;

    /// The loop variable of all main loops
    ///
    /// When this turns to false, all threads should stop
    bool should_run() const noexcept;

    void request_stop(ExitCode = ExitCode::normal) noexcept;

    [[nodiscard]] bool wait_for_stage(Stage s, chrono::duration timeout = chrono::duration::zero()) noexcept;
    void on_stage_change(std::function<bool(Stage s)> f) noexcept;

    void set_stage(Stage s) noexcept;

    void on_enter_stage(Stage s, std::function<void()> f) noexcept;

    [[nodiscard]] bool wait_for_stage(Stage s) noexcept;

  private:
    std::vector<std::function<bool(Stage)>> hooks_;
    std::atomic<std::underlying_type_t<Stage>> stage_ = util::underlying(Stage::initializing);
    std::mutex mutex_;
    std::condition_variable cond_;
  };
  static_assert(core::AServiceImplOf<Runtime, Runtime>);

  /// Utility type used to manage service lifetimes.
  ///
  /// Start one with `start_app`.
  template<core::AService... Ss>
  struct Application {
    Application(std::tuple<core::ServiceHandle<Ss>...> t) noexcept : services_(std::move(t)) {}

    Application(Application&&) = default;

    ~Application() noexcept
    {
      if (std::get<0>(services_).started()) stop();
    }

    /// Get one of the running services
    template<util::one_of<Ss...> Service>
    Service& service()
    {
      return std::get<core::ServiceHandle<Service>>(services_).service();
    }

    /// Start all services, and set `service<Runtime>().stage()` to `running`
    Application& start() & noexcept
    {
      util::for_each(services_, [](auto& handle) { handle.start(); });
      dynamic_cast<Runtime&>(service<Runtime>()).set_stage(Runtime::Stage::running);
      return *this;
    }

    /// Start all services, and set `service<Runtime>().stage()` to `running`
    Application&& start() && noexcept
    {
      start();
      return std::move(*this);
    }

    /// Set `service<Runtime>().stage()` to `stopping`, and stop (destroy) all services
    ///
    /// Must only be called from main thread
    void stop() noexcept
    {
      dynamic_cast<Runtime&>(service<Runtime>()).set_stage(Runtime::Stage::stopping);
      util::reverse_for_each(services_, [](auto& handle) { handle.stop(); });
    }

    /// Wait for application to be stopped, with an optional timeout
    bool wait_for_stop(chrono::duration timeout = chrono::duration::zero()) noexcept
    {
      return service<Runtime>().wait_for_stage(Runtime::Stage::stopping, timeout);
    }

  private:
    std::tuple<core::ServiceHandle<Ss>...> services_;
  };

  template<core::AService... Ss>
  [[nodiscard("The resulting handle stops the app in the destructor")]] Application<Runtime, Ss...> start_app(
    core::ServiceHandle<Ss>... service_handles)
  {
    auto app = Application{std::tuple(core::make_handle<Runtime>(), std::move(service_handles)...)};
    app.start();
    return app;
  }


} // namespace otto::services
