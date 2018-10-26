#include <atomic>
#include <condition_variable>
#include "application.hpp"

namespace otto::services {

  Application::Application(AudioManager& audio_manager,
                           EngineManager& engine_manager,
                           LogManager& log_manager,
                           PresetManager& preset_manager,
                           UIManager& ui_manager,
                           StateManager& state_manager)
    : audio_manager(audio_manager),
      engine_manager(engine_manager),
      log_manager(log_manager),
      preset_manager(preset_manager),
      ui_manager(ui_manager),
      state_manager(state_manager)
  {
    _current = this;
  }

  void Application::exit(ErrorCode ec) noexcept
  {
    _is_running = false;
    _error_code = ec;
  }

  bool Application::running() noexcept
  {
    return _is_running;
  }

  Application::ErrorCode Application::error() noexcept
  {
    return _error_code;
  }

  void Application::handle_signal(int signal) noexcept
  {
    _is_running = false;
    _error_code = ErrorCode::signal_recieved;
  }

  Application& Application::current() noexcept
  {
    return *_current;
  }
} // namespace otto::services
