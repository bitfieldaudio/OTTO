#pragma once

#include "core/service.hpp"
#include "core/ui/screen.hpp"

namespace otto::services {

  struct Settings : core::Service {

    Settings();

    struct Screen;

    core::ui::Screen& screen();

  private:
    std::unique_ptr<core::ui::Screen> screen_;
  };
}
