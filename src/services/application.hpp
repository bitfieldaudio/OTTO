#pragma once

#include <atomic>
#include <functional>
#include <memory>

#include "util/signals.hpp"
#include "util/exception.hpp"
#include "util/filesystem.hpp"

namespace otto::services {

  struct AudioManager;
  struct EngineManager;
  struct LogManager;
  struct PresetManager;
  struct UIManager;
  struct StateManager;
  struct ClockManager;
  struct Controller;

  struct Application;

  template<typename Service>
  struct ServiceStorage {
    using Factory = std::function<std::unique_ptr<Service>()>;

    ServiceStorage(Factory f) : factory_(f) {}

    Service& construct() {
      _storage = factory_();
      return *_storage;
    }

    Service* operator->() noexcept
    {
      return _storage.get();
    }

    Service& operator*() noexcept
    {
      return *_storage;
    }

    operator Service&() noexcept
    {
      return *_storage;
    }

    Factory factory_;
    std::unique_ptr<Service> _storage;
  };

  struct ApplicationHandler {
    static inline ApplicationHandler* _current = nullptr;

    ApplicationHandler() {
      _current = this;
    }

    ~ApplicationHandler() {
      _current = nullptr;
    }
  };

  struct Application : private ApplicationHandler {
    enum struct ErrorCode {
      none = 0,
      ui_closed,
      user_exit,
      audio_error,
      graphics_error,
      input_error,
      signal_received
    };

    using exception = util::as_exception<ErrorCode>;
    const filesystem::path data_dir{"data"};

    /// The current Application.
    ///
    /// When an Application is constructed, this function will be pointed to it. The one who
    /// constructs the application still has to destruct it when done with it.
    ///
    /// There should obviously only ever be one Application instance in the process.
    static Application& current() noexcept;

    static bool has_current() noexcept;

    Application(ServiceStorage<LogManager>::Factory log_factory,
                ServiceStorage<StateManager>::Factory state_factory,
                ServiceStorage<PresetManager>::Factory preset_factory,
                ServiceStorage<AudioManager>::Factory audio_factory,
                ServiceStorage<ClockManager>::Factory clock_factory,
                ServiceStorage<UIManager>::Factory ui_factory,
                ServiceStorage<Controller>::Factory controller,
                ServiceStorage<EngineManager>::Factory engine_factory);

    virtual ~Application();

    void exit(ErrorCode ec) noexcept;

    bool running() noexcept;

    ErrorCode error() noexcept;

    static void handle_signal(int signal) noexcept;

    struct Events {
      util::Signal<> post_init;
      util::Signal<> pre_exit;
    } events;

    ServiceStorage<LogManager> log_manager;
    ServiceStorage<StateManager> state_manager;
    ServiceStorage<PresetManager> preset_manager;
    ServiceStorage<AudioManager> audio_manager;
    ServiceStorage<ClockManager> clock_manager;
    ServiceStorage<UIManager> ui_manager;
    ServiceStorage<Controller> controller;
    ServiceStorage<EngineManager> engine_manager;

  private:
    std::atomic_bool _is_running{true};
    std::atomic<ErrorCode> _error_code;
  };

} // namespace otto::services

namespace otto {
  using Application = services::Application;
}
