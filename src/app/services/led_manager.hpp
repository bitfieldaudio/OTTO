#pragma once

#include "lib/skia/color.hpp"

#include "app/leds.hpp"
#include "app/services/config.hpp"
#include "app/services/controller.hpp"

namespace otto::services {

  struct LedManager : core::ServiceAccessor<services::Controller> {
    struct Config : otto::Config<Config> {
      float brightness = 0.5f;
      LEDColor min_color = {0x08, 0x08, 0x08};
      DECL_VISIT(brightness, min_color);
    };

    LedManager();
    void process(ILedController& controller);
    void set(Led led, LEDColor color, bool force = false);

  private:
    void send(Led led, LEDColor);
    Config::Handle config_;
    LEDColorSet colors_;
  };
} // namespace otto::services
