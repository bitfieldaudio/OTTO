#include <csignal>

#include <lyra.hpp>

#include "core/audio/midi.hpp"

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


using namespace otto;
using namespace otto::services;

int handle_exception(const char* e);
int handle_exception(std::exception& e);
int handle_exception();

int main(int argc, char* argv[])
{
  try {
    int sysex_in_port = -1;
    int sysex_out_port = -1;
    int audio_in = -1;
    int audio_out = -1;

    bool show_help = false;

    auto cli = lyra::cli_parser();

    cli |= lyra::opt(sysex_in_port, "device number") //
      ["--sysex-ctl-in-device"]                      //
      ("Number of the input midi device to use as a controller over sysex");
    cli |= lyra::opt(sysex_out_port, "device number") //
      ["--sysex-ctl-out-device"]                      //
      ("Number of the output midi device to use as a controller over sysex");

    cli |= lyra::opt(audio_in, "input device")["--audio-in"]("The input device number");
    cli |= lyra::opt(audio_out, "output device")["--audio-out"]("The output device number");
    cli |= lyra::help(show_help);

    auto parse_result = cli.parse({argc, argv});

    if (show_help || !parse_result) {
      std::cout << cli << '\n';
      return 0;
    }

    Application app = {
      [&] { return std::make_unique<LogManager>(argc, argv); },
      StateManager::create_default,
      PresetManager::create_default,
      [&] { return std::make_unique<RTAudioAudioManager>(audio_in, audio_out); },
      ClockManager::create_default,
      std::make_unique<GLFWUIManager>,
      [&] { return MCUSysexController::make_or_emulator(sysex_in_port, sysex_out_port); },
      EngineManager::create_default,
    };

    RTAudioAudioManager::current().log_devices();

    Settings settings;

    // Overwrite the logger signal handlers
    std::signal(SIGABRT, Application::handle_signal);
    std::signal(SIGTERM, Application::handle_signal);
    std::signal(SIGINT, Application::handle_signal);

    app.audio_manager->start();
    app.engine_manager->start();
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
  LOGE("{}", e);
  LOGE("Exception thrown, exitting!");
  return 1;
}

int handle_exception(std::exception& e)
{
  LOGE("{}", e.what());
  LOGE("Exception thrown, exitting!");
  return 1;
}

int handle_exception()
{
  LOGE("Unknown exception thrown, exitting!");
  return 1;
}
