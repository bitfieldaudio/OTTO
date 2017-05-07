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

  audio::jack::init();
  GLOB.tapedeck = new TapeModule();
  GLOB.mixer = new MixerModule();
  //GLOB.synth.registerModule(new TestSynth());
  MainUI::init();
  audio::jack::exit();

  delete GLOB.tapedeck;
  delete GLOB.mixer;
  return 0;
}
