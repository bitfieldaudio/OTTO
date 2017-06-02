#include <mutex>
#include <plog/Log.h>
#include <plog/Appenders/ConsoleAppender.h>

#include "audio/jack.h"
#include "audio/midi.h"
#include "ui/mainui.h"
#include "modules/tape.h"
#include "modules/mixer.h"
#include "modules/testsynth.h"
#include "modules/simple-drums.h"
#include "globals.h"

int main(int argc, char *argv[]) {
  static plog::ConsoleAppender<plog::TxtFormatter> consoleAppender;
  plog::init(plog::debug, "log.txt").addAppender(&consoleAppender);
  LOGI << "LOGGING NOW";

  GLOB.project = new Project();

  midi::generateFreqTable(440);
  std::mutex mut;
  std::unique_lock<std::mutex> lock (mut);

  GLOB.synth.registerModule('SDRM', new SimpleDrumsModule());
  GLOB.events.preInit();
  GLOB.dataFile.open("data.top1");
  GLOB.jackAudio.init();
  GLOB.tapedeck.init();
  GLOB.mixer.init();
  GLOB.ui.init();
  GLOB.events.postInit();
  GLOB.jackAudio.startProcess();

  GLOB.notifyExit.wait(lock);

  LOGI << "Exitting";
  GLOB.events.preExit();
  GLOB.ui.exit();
  GLOB.mixer.exit();
  GLOB.tapedeck.exit();
  GLOB.jackAudio.exit();
  GLOB.events.preExit();
  return 0;
}
