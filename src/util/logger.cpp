#include "logger.hpp"
#include "core/globals.hpp"

#include <plog/Appenders/ConsoleAppender.h>

namespace otto::util::logger {
  namespace {
    plog::ConsoleAppender<plog::TxtFormatter> consoleAppender;
  } // namespace

  void init()
  {
    auto logFilePath = global::data_dir / "log.txt";
    auto& logger      = plog::init(plog::debug, logFilePath.c_str());
    logger.addAppender(&consoleAppender);

    LOGI << "LOGGING NOW";
  }
} // namespace otto::util::logger
