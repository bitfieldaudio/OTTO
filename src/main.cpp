#include <plog/Log.h>
#include <plog/Appenders/ConsoleAppender.h>
#include "audio/jack.h"
#include "ui/mainui.h"
#include "modules/tape.h"
#include "modules/mixer.h"
#include "modules/testsynth.h"
#include "globals.h"

int main(int argc, char *argv[]) {
  static plog::ConsoleAppender<plog::TxtFormatter> consoleAppender;
  plog::init(plog::debug, "log.txt").addAppender(&consoleAppender);
  LOGI << "LOGGING NOW";

  GLOB.project = new Project();

  GLOB.running = true;
  GLOB.jackAudio.init();
  GLOB.tapedeck.init();
  GLOB.mixer.init();
  GLOB.mainUI.init();
  while(GLOB.running == true);

  LOGI << "Exitting";

  GLOB.mainUI.exit();
  GLOB.mixer.exit();
  GLOB.tapedeck.exit();
  GLOB.jackAudio.exit();
  return 0;
}
