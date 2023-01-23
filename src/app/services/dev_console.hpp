#pragma once

#include <thread>

#include "app/services/runtime.hpp"

namespace otto::services {

  struct DevConsole {
    DevConsole(RuntimeController& runtime);

  private:
    void run_command(util::string_ref);

    std::jthread thread;
    RuntimeController& rt;
  };
} // namespace otto::services
