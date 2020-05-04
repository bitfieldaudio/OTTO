#include "testing.t.hpp"

#include "services/audio_manager.hpp"
#include "services/clock_manager.hpp"
#include "services/controller.hpp"
#include "services/engine_manager.hpp"
#include "services/log_manager.hpp"
#include "services/preset_manager.hpp"
#include "services/settings.hpp"
#include "services/state_manager.hpp"
#include "services/ui_manager.hpp"

#include "board/audio_driver.hpp"
#include "board/controller.hpp"
#include "board/ui/glfw_ui_manager.hpp"

#include "dummy_services.hpp"

#include "engines/synths/goss/goss.hpp"
#include "engines/synths/goss/screen.hpp"
#include "engines/synths/goss/audio.hpp"

namespace otto::test {
  using namespace otto::core::engine;
  using namespace otto::services;

  template<typename Engine>
  void run_single_engine()
  {
    Application app = {
      std::make_unique<LogManager>,
      std::make_unique<DummyStateManager>,
      std::make_unique<DummyPresetManager>,
      std::make_unique<RTAudioAudioManager>,
      ClockManager::create_default,
      std::make_unique<GLFWUIManager>,
      [&] { return MCUSysexController::make_or_emulator(); },
      std::make_unique<DummyEngineManager>,
    };

    Engine eg = {itc::ActionChannel::instrument};
    UIManager::current().register_screen_selector(ScreenEnum::synth, [&eg] { return eg.screen(); });
    UIManager::current().display(ScreenEnum::synth);

    RTAudioAudioManager::current().log_devices();

    app.audio_manager->start();
    app.ui_manager->main_ui_loop();
  }

  TEST_CASE("goss" * doctest::skip()) {
    run_single_engine<engines::goss::GossEngine>();
  }
} // namespace otto::test
