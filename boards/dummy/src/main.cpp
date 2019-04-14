#include <csignal>

#include "core/audio/midi.hpp"

#include "services/audio_manager.hpp"
#include "services/engine_manager.hpp"
#include "services/log_manager.hpp"
#include "services/preset_manager.hpp"
#include "services/state_manager.hpp"
#include "services/ui_manager.hpp"
#include "services/clock_manager.hpp"

using namespace otto;
using namespace otto::services;

int handle_exception(const char* e);
int handle_exception(std::exception& e);
int handle_exception();

struct DummyUIManager final : UIManager {
  DummyUIManager() = default;

  void main_ui_loop() override {}
};

int main(int argc, char* argv[])
{
  try {
    Application app{[&] { return std::make_unique<LogManager>(argc, argv); },
                    StateManager::create_default,
                    std::make_unique<PresetManager>,
                    std::make_unique<AudioManager>,
                    ClockManager::create_default,
                    std::make_unique<DummyUIManager>,
                    EngineManager::create_default};

    // Overwrite the logger signal handlers
    std::signal(SIGABRT, Application::handle_signal);
    std::signal(SIGTERM, Application::handle_signal);
    std::signal(SIGINT, Application::handle_signal);

    app.engine_manager->start();
    app.audio_manager->start();
    app.ui_manager->main_ui_loop();

  } catch (const char* e) {
    return handle_exception(e);
  } catch (std::exception& e) {
    return handle_exception(e);
  } catch (...) {
    return handle_exception();
  }

  LOG_F(INFO, "Exiting");
  return 0;
}

int handle_exception(const char* e)
{
  LOGE(e);
  LOGE("Exception thrown, exitting!");
  return 1;
}

int handle_exception(std::exception& e)
{
  LOGE(e.what());
  LOGE("Exception thrown, exitting!");
  return 1;
}

int handle_exception()
{
  LOGE("Unknown exception thrown, exitting!");
  return 1;
}
