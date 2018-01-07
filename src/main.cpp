#include "services/audio_manager.hpp"
#include "core/audio/midi.hpp"
#include "services/engine_manager.hpp"
#include "services/preset_manager.hpp"
#include "core/globals.hpp"
#include "core/ui/mainui.hpp"
#include "services/logger.hpp"
#include "services/state.hpp"
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

    presets::load_preset_files();
    engines::init();
    audio::init();

    engines::start();
    audio::start();

    ui::init();
    ui::main_ui_loop();
  } catch (const char* e) {
    return handleException(e);
  } catch (std::exception& e) {
    return handleException(e);
  } catch (...) {
    return handleException();
  }

  LOG_F(INFO, "Exiting");
  cleanup();
  return 0;
}

int handleException(const char* e)
{
  LOGE(e);
  LOGE("Exception thrown, exitting!");
  cleanup();
  return 1;
}

int handleException(std::exception& e)
{
  LOGE(e.what());
  LOGE("Exception thrown, exitting!");
  cleanup();
  return 1;
}

int handleException()
{
  LOGE("Unknown exception thrown, exitting!");
  cleanup();
  return 1;
}

void cleanup()
{
  engines::shutdown();
  audio::shutdown();
  services::state::save();

  util::timer::save_data();
}
