#pragma once

#include "engine.hpp"
#include "engine_dispatcher.hpp"

#include "core/ui/widget.hpp"

namespace otto::engines {

  template<EngineType ET>
  struct EngineSelectorScreen : ui::Screen {

    constexpr static EngineType engine_type = ET;

    void rotary(ui::RotaryEvent) override;

    void draw(ui::vg::Canvas&) override;

    void on_show() override;
    void on_hide() override;

  };

}
