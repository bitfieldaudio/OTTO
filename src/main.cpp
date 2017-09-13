#include <mutex>
#include <plog/Log.h>
#include <plog/Appenders/ConsoleAppender.h>

#include "core/audio/jack.hpp"
#include "core/audio/midi.hpp"
#include "core/ui/mainui.hpp"
#include "modules/tapedeck.hpp"
#include "modules/mixer.hpp"
#include "modules/super-saw-synth.hpp"
#include "modules/simple-drums.hpp"
#include "modules/drum-sampler.hpp"
#include "modules/synth-sampler.hpp"
#include "modules/nuke.hpp"
#include "core/globals.hpp"

int main(int argc, char *argv[]) {
  static plog::ConsoleAppender<plog::TxtFormatter> consoleAppender;
  plog::init(plog::debug, (top1::Globals::data_dir / "log.txt").c_str())
    .addAppender(&consoleAppender);
  LOGI << "LOGGING NOW";

  using namespace top1;

  midi::generateFreqTable(440);
  std::mutex mut;
  std::unique_lock lock (mut);

  using namespace modules;

  Globals::drums.registerModule<DrumSampler>("Sampler");
  Globals::drums.registerModule<SimpleDrumsModule>("Additive Drums");

  Globals::synth.registerModule<NukeSynth>("Nuke");
  Globals::synth.registerModule<SuperSawSynth>("Super Saw");
  Globals::synth.registerModule<SynthSampler>("Sampler");

  Globals::events.preInit.runAll();
  Globals::init();
  Globals::events.postInit.runAll();

  Globals::jackAudio.startProcess();

  Globals::notifyExit.wait(lock);

  LOGI << "Exitting";
  Globals::events.preExit.runAll();
  Globals::ui.exit();
  Globals::mixer.exit();
  Globals::tapedeck.exit();
  Globals::jackAudio.exit();
  Globals::dataFile.write();
  Globals::events.postExit.runAll();
  return 0;
}
