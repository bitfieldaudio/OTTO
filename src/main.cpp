#include <plog/Log.h>
#include <plog/Appenders/ConsoleAppender.h>
#include "audio/jack.h"

int main(int argc, char *argv[]) {
  static plog::ConsoleAppender<plog::TxtFormatter> consoleAppender;
  plog::init(plog::debug, "log.txt").addAppender(&consoleAppender);
  LOGI << "LOGGING NOW";
  audio::jack::init(argc, argv);
  return 0;
}
