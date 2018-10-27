#pragma once

#include "services/ui_manager.hpp"
#include "services/debug_ui.hpp"

namespace otto::services {

  struct GLFWUIManager final : UIManager {
    GLFWUIManager() = default;

    void main_ui_loop() override;

  };

}
