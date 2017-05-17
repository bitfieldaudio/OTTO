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

  GLOB.running = true;
  GLOB.synth.registerModule(new SimpleDrumsModule());
  GLOB.events.preInit();
  GLOB.jackAudio.init();
  GLOB.tapedeck.init();
  GLOB.mixer.init();
  GLOB.ui.init();
  GLOB.events.postInit();
  while(GLOB.running == true);

  LOGI << "Exitting";
  GLOB.events.preExit();
  GLOB.ui.exit();
  GLOB.mixer.exit();
  GLOB.tapedeck.exit();
  GLOB.jackAudio.exit();
  GLOB.events.preExit();
  return 0;
}
