#pragma once

#include <filesystem.hpp>

#define LOGURU_USE_FMTLIB 1
#include <loguru.hpp>

namespace otto::util::logger {
    void init(int argc, char * argv[], bool enable_console = true, const char * logFilePath = nullptr);
}
