#include "core/audio/midi.hpp"
#include "core/engines/engine.hpp"
#include "core/globals.hpp"
#include "core/ui/mainui.hpp"
#include "core/audio/audio_manager.hpp"
#include "engines/drums/drum-sampler/drum-sampler.hpp"
#include "engines/drums/simple-drums/simple-drums.hpp"
#include "engines/studio/mixer/mixer.hpp"
#include "engines/studio/tapedeck/tapedeck.hpp"
#include "engines/synths/nuke/nuke.hpp"
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

    midi::generateFreqTable(440);

    using namespace engines;
    register_engine<DrumSampler>();
    register_engine<SimpleDrumsEngine>();
    register_engine<NukeSynth>();

    global::event::pre_init.runAll();
    global::init();

    global::event::post_init.runAll();

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
  global::event::pre_exit.runAll();
  global::mixer.on_disable();
  global::tapedeck.on_disable();

  audio::AudioManager::get().shutdown();

  services::state::save();

  global::event::post_exit.runAll();

  util::timer::save_data();
}
