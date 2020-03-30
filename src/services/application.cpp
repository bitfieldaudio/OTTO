#include <atomic>
#include <condition_variable>
#include "application.hpp"

#include "services/audio_manager.hpp"
#include "services/engine_manager.hpp"
#include "services/log_manager.hpp"
#include "services/preset_manager.hpp"
#include "services/state_manager.hpp"
#include "services/ui_manager.hpp"
#include "services/clock_manager.hpp"
#include "services/controller.hpp"

namespace otto::services {

  Application::Application(ServiceStorage<LogManager>::Factory log_fact,
                           ServiceStorage<StateManager>::Factory state_fact,
                           ServiceStorage<PresetManager>::Factory preset_fact,
                           ServiceStorage<AudioManager>::Factory audio_fact,
                           ServiceStorage<ClockManager>::Factory clock_fact,
                           ServiceStorage<UIManager>::Factory ui_fact,
                           ServiceStorage<Controller>::Factory controller_fact,
                           ServiceStorage<EngineManager>::Factory engine_fact)
    : log_manager(std::move(log_fact)),
      state_manager(std::move(state_fact)),
      preset_manager(std::move(preset_fact)),
      audio_manager(std::move(audio_fact)),
      clock_manager(std::move(clock_fact)),
      ui_manager(std::move(ui_fact)),
      controller(std::move(controller_fact)),
      engine_manager(std::move(engine_fact))
  {
    _current = this;

    log_manager.construct();
    state_manager.construct();
    preset_manager.construct();
    audio_manager.construct();
    clock_manager.construct();
    ui_manager.construct();
    controller.construct();
    engine_manager.construct();

    events.post_init.emit();
  }

  Application::~Application()
  {
    DLOGI("~Application");
    events.pre_exit.emit();
  }

  void Application::exit(ErrorCode ec) noexcept
  {
    _is_running = false;
    _error_code = ec;
    LOGI("Exit called with code {}", util::underlying(ec));
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
    Application::current()._is_running = false;
    Application::current()._error_code = ErrorCode::signal_received;
  }

  Application& Application::current() noexcept
  {
    return static_cast<Application&>(*_current);
  }

  bool Application::has_current() noexcept
  {
    return _current != nullptr;
  }
} // namespace otto::services
