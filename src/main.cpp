#include <mutex>
#include <plog/Log.h>
#include <plog/Appenders/ConsoleAppender.h>

#include "core/audio/midi.hpp"
#include "core/ui/mainui.hpp"
#include "modules/studio/tapedeck/tapedeck.hpp"
#include "modules/studio/mixer/mixer.hpp"
#include "modules/drums/simple-drums/simple-drums.hpp"
#include "modules/drums/drum-sampler/drum-sampler.hpp"
#include "modules/synths/synth-sampler/synth-sampler.hpp"
#include "modules/synths/nuke/nuke.hpp"
#include "core/globals.hpp"
#include "util/timer.hpp"

int main(int argc, char *argv[]) {
  using namespace otto;

  auto cleanup = [] {
      global::event::pre_exit.runAll();
    global::ui.exit();
    global::mixer.exit();
    global::tapedeck.exit();
    global::audio.exit();
    global::save_data();
    global::event::post_exit.runAll();
    auto f = std::ofstream((global::data_dir / "timers.json").string(), std::ios::trunc);
    f << std::setw(2) << util::timer::serialize() << std::endl;
    f.close();
  };

  try {
    static plog::ConsoleAppender<plog::TxtFormatter> consoleAppender;
    plog::init(plog::debug, (otto::global::data_dir / "log.txt").c_str())
      .addAppender(&consoleAppender);
    LOGI << "LOGGING NOW";

    midi::generateFreqTable(440);

    using namespace modules;

    global::drums.registerModule<DrumSampler>("Sampler");
    global::drums.registerModule<SimpleDrumsModule>("Additive Drums");

    global::synth.registerModule<NukeSynth>("Nuke");
    global::synth.registerModule<SynthSampler>("Sampler");

    global::event::pre_init.runAll();
    global::init();
    global::event::post_init.runAll();

    global::audio.start_processing();

    global::ui.mainRoutine();

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
