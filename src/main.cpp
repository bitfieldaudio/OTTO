#include "core/audio/midi.hpp"
#include "core/globals.hpp"
#include "core/ui/mainui.hpp"
#include "core/audio/audio_manager.hpp"
#include "core/engines/engine_manager.hpp"
#include "services/logger.hpp"
#include "services/state.hpp"
#include "services/event_manager.hpp"
#include "util/timer.hpp"

using namespace otto;

void cleanup();
int handleException(const char* e);
int handleException(std::exception& e);
int handleException();

int main(int argc, char* argv[])
{
  try {
    services::logger::init(argc, argv);
    services::state::load();

    midi::generateFreqTable(440);

    services::EventManager::get().pre_init.fire();
    engines::EngineManager::get().init();
    audio::AudioManager::get().init();
    services::EventManager::get().post_init.fire();

    engines::EngineManager::get().start();
    audio::AudioManager::get().start();

    ui::init();
    ui::main_ui_loop();
  }
  catch (const char* e) { return handleException(e); }
  catch (std::exception& e) { return handleException(e); }
  catch (...) { return handleException(); }

  LOG_F(INFO, "Exiting");
  cleanup();
  return 0;
}

int handleException(const char* e)
{
  LOG_F(FATAL, e);
  LOG_F(INFO, "Exception thrown, exitting!");
  cleanup();
  return 1;
}

int handleException(std::exception& e)
{
  LOG_F(FATAL, e.what());
  LOG_F(INFO, "Exception thrown, exitting!");
  cleanup();
  return 1;
}

int handleException()
{
  LOG_F(INFO, "Unknown exception thrown, exitting!");
  cleanup();
  return 1;
}

void cleanup()
{
  services::EventManager::get().pre_exit.fire();
  engines::EngineManager::get().shutdown();
  audio::AudioManager::get().shutdown();
  services::state::save();
  services::EventManager::get().post_exit.fire();

  util::timer::save_data();
}
