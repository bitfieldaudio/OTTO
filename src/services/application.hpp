#pragma once

#include <memory>
#include <atomic>

#include "util/exception.hpp"
#include "util/filesystem.hpp"

namespace otto::services {

  struct AudioManager;
  struct EngineManager;
  struct LogManager;
  struct PresetManager;
  struct UIManager;
  struct StateManager;

  struct Application {
    enum struct ErrorCode {
      none = 0,
      ui_closed,
      user_exit,
      audio_error,
      graphics_error,
      input_error,
      signal_recieved
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

    void exit(ErrorCode ec) noexcept;

    bool running() noexcept;

    ErrorCode error() noexcept;

    void handle_signal(int signal) noexcept;

    AudioManager& audio_manager;
    EngineManager& engine_manager;
    LogManager& log_manager;
    PresetManager& preset_manager;
    UIManager& ui_manager;
    StateManager& state_manager;

  protected:
    Application(AudioManager& audio_manager,
                EngineManager& engine_manager,
                LogManager& log_manager,
                PresetManager& preset_manager,
                UIManager& ui_manager,
                StateManager& state_manager);

    virtual ~Application();

  private:
    std::atomic_bool _is_running{true};
    std::atomic<ErrorCode> _error_code;
    static Application* _current;
  };

} // namespace otto::services

namespace otto {
  using Application = services::Application;
}
