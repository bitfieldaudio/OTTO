#include "util/timer.hpp"

#include "core/audio/midi.hpp"
#include "core/globals.hpp"

#include "services/engines.hpp"
#include "services/presets.hpp"
#include "services/ui.hpp"
#include "services/logger.hpp"
#include "services/state.hpp"
#include "services/audio.hpp"

using namespace otto;

void cleanup();
int handleException(const char* e);
int handleException(std::exception& e);
int handleException();

int main(int argc, char* argv[])
{
  try {
    service::logger::init(argc, argv);
    service::state::load();

    service::presets::init();
    service::engines::init();
    service::audio::init();

    service::engines::start();
    service::audio::start();

    service::ui::init();
    service::ui::main_ui_loop();
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
  service::engines::shutdown();
  service::audio::shutdown();
  service::state::save();

  util::timer::save_data();
}
