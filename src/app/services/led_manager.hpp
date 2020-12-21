#pragma once

#include "lib/skia/color.hpp"

#include "app/leds.hpp"
#include "app/services/config.hpp"
#include "app/services/controller.hpp"

namespace otto::services {

  struct LedManager : core::ServiceAccessor<services::Controller> {
    struct Config : otto::Config<Config> {
      LEDColor off_color = {0x02, 0x02, 0x02};
      float brightness = 0.5f;
      DECL_VISIT(off_color, brightness);
    };

    LedManager();

    void set(Led led, skia::Color color);

  private:
    void send(Led led, LEDColor);
    Config::Handle config_;
    util::enum_map<Led, skia::Color> colors_;
  };
} // namespace otto::services
