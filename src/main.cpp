#include <plog/Log.h>
#include <plog/Appenders/ConsoleAppender.h>
#include "audio/jack.h"
#include "ui/mainui.h"
#include "modules/tape.h"
#include "modules/testsynth.h"
#include "globals.h"

int main(int argc, char *argv[]) {
  static plog::ConsoleAppender<plog::TxtFormatter> consoleAppender;
  plog::init(plog::debug, "log.txt").addAppender(&consoleAppender);
  LOGI << "LOGGING NOW";

  GLOB.project = new Project();

  TapeModule::init();
  TestSynth::init();
  audio::jack::init();
  MainUI::init();
  audio::jack::exit();
  return 0;
}
