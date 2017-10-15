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

int main(int argc, char *argv[]) {
  using namespace top1;

  auto cleanup = [] {
    Globals::events.preExit.runAll();
    Globals::ui.exit();
    Globals::mixer.exit();
    Globals::tapedeck.exit();
    Globals::audio.exit();
    Globals::dataFile.write();
    Globals::events.postExit.runAll();
  };

  try {
    static plog::ConsoleAppender<plog::TxtFormatter> consoleAppender;
    plog::init(plog::debug, (top1::Globals::data_dir / "log.txt").c_str())
      .addAppender(&consoleAppender);
    LOGI << "LOGGING NOW";

    midi::generateFreqTable(440);

    using namespace modules;

    Globals::drums.registerModule<DrumSampler>("Sampler");
    Globals::drums.registerModule<SimpleDrumsModule>("Additive Drums");

    Globals::synth.registerModule<NukeSynth>("Nuke");
    Globals::synth.registerModule<SynthSampler>("Sampler");

    Globals::events.preInit.runAll();
    Globals::init();
    Globals::events.postInit.runAll();

    Globals::audio.start_processing();

    Globals::ui.mainRoutine();

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
    LOGI << "Exception thrown, exitting!";
    cleanup();
    return 1;
  }

  LOGI << "Exitting";
  cleanup();
  return 0;
}
