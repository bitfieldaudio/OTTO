#pragma once

#include "services/debug_ui.hpp"
#include "services/ui_manager.hpp"

#include "board/ui/keys.hpp"
#include "core/ui/canvas.hpp"

namespace otto::services {

  struct EGLUIManager final : UIManager {
    EGLUIManager() = default;

    void main_ui_loop() override;

  private:

    void read_encoders();
    void read_keyboard();
  };

} // namespace otto::services

// kak: other_file=../../../src/egl_ui.cpp
