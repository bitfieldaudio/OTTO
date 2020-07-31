#pragma once

#include <atomic>
#include "app/services/runtime.hpp"

#include "lib/util/utility.hpp"

namespace otto::app::services {

  struct RuntimeImpl : Runtime {
    Stage stage() const noexcept override;

    /// The loop variable of all main loops
    ///
    /// When this turns to false, all threads should stop
    bool should_run() const noexcept override;

    void set_stage(Stage s) noexcept;

  private:
    std::atomic<std::underlying_type_t<Stage>> stage_ = lib::util::underlying(Stage::initializing);
  };
  static_assert(lib::core::AServiceImplOf<RuntimeImpl, Runtime>);


  /// Utility type used to manage service lifetimes.
  /// 
  /// Start one with `start_app`.
  template<lib::core::AService... Ss>
  struct Application {
    Application(std::tuple<lib::core::ServiceHandle<Ss>...> t) noexcept : services_(std::move(t)) {}

    Application(Application&&) = default;

    ~Application() noexcept
    {
      if (std::get<0>(services_).started()) stop();
    }

    /// Get one of the running services
    template<lib::util::one_of<Ss...> Service>
    Service& service()
    {
      return std::get<lib::core::ServiceHandle<Service>>(services_).service();
    }

    /// Start all services, and set `service<Runtime>().stage()` to `running`
    Application& start() & noexcept
    {
      lib::util::for_each(services_, [this](auto& handle) { handle.start(); });
      dynamic_cast<RuntimeImpl&>(service<Runtime>()).set_stage(Runtime::Stage::running);
      return *this;
    }

    /// Start all services, and set `service<Runtime>().stage()` to `running`
    Application&& start() && noexcept
    {
      start();
      return std::move(*this);
    }

    /// Set `service<Runtime>().stage()` to `stopping`, and stop all services
    void stop() noexcept
    {
      dynamic_cast<RuntimeImpl&>(service<Runtime>()).set_stage(Runtime::Stage::stopping);
      lib::util::reverse_for_each(services_, [this](auto& handle) { handle.stop(); });
    }

  private:
    std::tuple<lib::core::ServiceHandle<Ss>...> services_;
  };

  template<lib::core::AService... Ss>
  Application<Runtime, Ss...> start_app(lib::core::ServiceHandle<Ss>... service_handles)
  {
    auto app = Application{std::tuple(lib::core::make_handle<RuntimeImpl>(), std::move(service_handles)...)};
    app.start();
    return app;
  }

} // namespace otto::app::services
