#include <csignal>

#include "core/audio/midi.hpp"

#include "services/audio_manager.hpp"
#include "services/engine_manager.hpp"
#include "services/log_manager.hpp"
#include "services/preset_manager.hpp"
#include "services/state_manager.hpp"
#include "services/ui_manager.hpp"

using namespace otto;

void cleanup();
int handle_exception(const char* e);
int handle_exception(std::exception& e);
int handle_exception();

int main(int argc, char* argv[])
{
  try {
    service::logger::init(argc, argv);

    // Overwrite the logger signal handlers
    std::signal(SIGABRT, global::handle_signal);
    std::signal(SIGTERM, global::handle_signal);
    std::signal(SIGINT, global::handle_signal);

    service::state::load();

    service::presets::init();
    service::engines::init();
    service::audio::init();

    service::engines::start();
    service::audio::start();

    service::ui::init();
    service::ui::main_ui_loop();
  } catch (const char* e) {
    return handle_exception(e);
  } catch (std::exception& e) {
    return handle_exception(e);
  } catch (...) {
    return handle_exception();
  }

  LOG_F(INFO, "Exiting");
  cleanup();
  return 0;
}

int handle_exception(const char* e)
{
  LOGE(e);
  LOGE("Exception thrown, exitting!");
  cleanup();
  return 1;
}

int handle_exception(std::exception& e)
{
  LOGE(e.what());
  LOGE("Exception thrown, exitting!");
  cleanup();
  return 1;
}

int handle_exception()
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
