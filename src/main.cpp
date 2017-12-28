#include "core/audio/midi.hpp"
#include "core/engines/engine.hpp"
#include "core/globals.hpp"
#include "core/ui/mainui.hpp"
#include "engines/drums/drum-sampler/drum-sampler.hpp"
#include "engines/drums/simple-drums/simple-drums.hpp"
#include "engines/studio/mixer/mixer.hpp"
#include "engines/studio/tapedeck/tapedeck.hpp"
#include "engines/synths/nuke/nuke.hpp"
#include "util/logger.hpp"
#include "util/timer.hpp"

using namespace otto;

void cleanup();

int main(int argc, char* argv[])
{
  try {
    util::logger::init();

    midi::generateFreqTable(440);

    using namespace engines;

    engines::register_engine<DrumSampler>();
    engines::register_engine<SimpleDrumsEngine>();
    engines::register_engine<NukeSynth>();

    global::event::pre_init.runAll();
    global::init();
    global::event::post_init.runAll();

    global::audio.start_processing();

    ui::init();
    ui::main_ui_loop();

  } catch (const char* e) {
    LOGF << e;
    LOGI << "Exception thrown, exitting!";
    cleanup();
    return 1;
  } catch (std::exception& e) {
    LOGF << e.what();
    LOGI << "Exception thrown, exitting!";
    cleanup();
    return 1;
  } catch (...) {
    LOGI << "Unknown exception thrown, exitting!";
    cleanup();
    return 1;
  }

  LOGI << "Exitting";
  cleanup();
  return 0;
}

void cleanup()
{
  global::event::pre_exit.runAll();
  global::mixer.on_disable();
  global::tapedeck.on_disable();
  global::audio.exit();
  global::save_data();
  global::event::post_exit.runAll();

  util::timer::save_data();
}
