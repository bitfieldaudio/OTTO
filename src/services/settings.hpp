#pragma once

#include "core/service.hpp"
#include "core/ui/screen.hpp"
#include "util/local_vector.hpp"
#include "util/ptr_vec.hpp"

namespace otto::services {

  struct Settings : core::Service {

    Settings();

    struct Screen;
    struct Menu {
      struct Entry {
        std::function<std::string(int steps)> on_step_;
        std::string name_;
      };

      util::unique_ptr_vec<Entry> entries;
    };
    core::ui::Screen& screen();

  private:
    std::unique_ptr<core::ui::Screen> screen_;
    Menu main_menu = {};
    Menu& current_menu = main_menu;
  };
}
