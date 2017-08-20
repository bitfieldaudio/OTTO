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
#include "core/globals.hpp"

int main(int argc, char *argv[]) {
  static plog::ConsoleAppender<plog::TxtFormatter> consoleAppender;
  plog::init(plog::debug, "log.txt").addAppender(&consoleAppender);
  LOGI << "LOGGING NOW";

  using namespace top1;

  midi::generateFreqTable(440);
  std::mutex mut;
  std::unique_lock lock (mut);

  GLOB.drums.registerModule("Sampler", new module::DrumSampler());
  GLOB.drums.registerModule("Additive Drums", new module::SimpleDrumsModule());

  GLOB.synth.registerModule("Super Saw", new module::SuperSawSynth());
  GLOB.synth.registerModule("Sampler", new module::SynthSampler());

  GLOB.events.preInit.runAll();
  GLOB.init();
  GLOB.events.postInit.runAll();

  GLOB.jackAudio.startProcess();

  GLOB.notifyExit.wait(lock);

  LOGI << "Exitting";
  GLOB.events.preExit.runAll();
  GLOB.ui.exit();
  GLOB.mixer.exit();
  GLOB.tapedeck.exit();
  GLOB.jackAudio.exit();
  GLOB.dataFile.write();
  GLOB.events.postExit.runAll();
  return 0;
}
