#pragma once

#include "core/engine/engine_dispatcher.hpp"

namespace otto::core::engine {

  struct EngineSelectorScreen : ui::Screen {
    void draw(nvg::Canvas& ctx) override;

  private:
    std::vector<std::string> engines = {"Rhodes", "OTTO.FM", "Goss", "Potion", "Subtraction"};
  };

  void EngineSelectorScreen::draw(nvg::Canvas& ctx) {

  }

} // namespace otto::core::engine
