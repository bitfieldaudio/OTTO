#include <mutex>
#include <plog/Log.h>
#include <plog/Appenders/ConsoleAppender.h>

#include "core/audio/midi.hpp"
#include "core/ui/mainui.hpp"
#include "core/engines/engine.hpp"
#include "engines/studio/tapedeck/tapedeck.hpp"
#include "engines/studio/mixer/mixer.hpp"
#include "engines/drums/simple-drums/simple-drums.hpp"
#include "engines/drums/drum-sampler/drum-sampler.hpp"
#include "engines/synths/nuke/nuke.hpp"
#include "core/globals.hpp"
#include "util/timer.hpp"

int main(int argc, char *argv[]) {
  using namespace otto;

  auto cleanup = [] {
    global::event::pre_exit.runAll();
    global::mixer.on_disable();
    global::tapedeck.on_disable();
    global::audio.exit();
    global::save_data();
    global::event::post_exit.runAll();
    auto f = std::ofstream(
      (global::data_dir / "timers.json").string(), std::ios::trunc);
    f << std::setw(2) << util::timer::serialize() << std::endl;
    f.close();
  };

  try {
    static plog::ConsoleAppender<plog::TxtFormatter> consoleAppender;
    plog::init(plog::debug, (otto::global::data_dir / "log.txt").c_str())
      .addAppender(&consoleAppender);
    LOGI << "LOGGING NOW";
#if (RPI)
  LOGI << "On RPI";
#endif

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
