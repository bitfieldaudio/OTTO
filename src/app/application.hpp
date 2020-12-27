#pragma once

#include "app/services/runtime.hpp"

namespace otto {

  namespace detail {
    struct start_on_construction_t {};
  } // namespace detail

  /// Utility type used to manage service lifetimes.
  ///
  /// Start one with `start_app`.
  template<core::AService... Ss>
  struct Application {
    Application(std::tuple<core::ServiceHandle<Ss>...> t) noexcept //
      : signal_waiter_(util::handle_signals({SIGINT},
                                            [this](int sig) {
                                              LOGI("Got SIGINT, stopping...");
                                              service<services::Runtime>().request_stop();
                                            })),
        services_(std::move(t))
    {}

    Application(detail::start_on_construction_t, std::tuple<core::ServiceHandle<Ss>...> t) noexcept
      : Application(std::move(t))
    {
      start();
    }

    Application(const Application&) = delete;
    Application& operator=(const Application&) = delete;

    Application(Application&&) noexcept = delete;
    Application& operator=(Application&&) noexcept = delete;

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
      service<services::Runtime>().set_stage(services::Runtime::Stage::running);
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
      service<services::Runtime>().set_stage(services::Runtime::Stage::stopping);
      util::reverse_for_each(services_, [](auto& handle) { handle.stop(); });
    }

    /// Wait for application to be stopped, with an optional timeout
    bool wait_for_stop(chrono::duration timeout = chrono::duration::zero()) noexcept
    {
      return service<services::Runtime>().wait_for_stage(services::Runtime::Stage::stopping, timeout);
    }

  private:
    util::SignalWaiter signal_waiter_;
    std::tuple<core::ServiceHandle<Ss>...> services_;
  };

  template<core::AService... Ss>
  [[nodiscard("The resulting handle stops the app in the destructor")]] //
  Application<services::Runtime, Ss...>
  start_app(core::ServiceHandle<Ss>... service_handles)
  {
    return Application<services::Runtime, Ss...>{
      detail::start_on_construction_t(),
      std::tuple(core::make_handle<services::Runtime>(), std::move(service_handles)...)};
  }

} // namespace otto
