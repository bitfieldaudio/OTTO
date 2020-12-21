#include "led_manager.hpp"

namespace otto::services {

  LedManager::LedManager()
  {
    for (auto l : util::enum_values<Led>()) {
      send(l, config_->off_color);
    }
  }

  void LedManager::set(Led led, skia::Color color)
  {
    auto& ref = colors_[led];
    if (ref == color) return;
    ref = color;
    auto adjcol = color.brighten(config_->brightness);
    LEDColor lc = {adjcol.red(), adjcol.green(), adjcol.blue()};
    send(led, lc);
  }

  void LedManager::send(Led led, LEDColor color)
  {
    service<services::Controller>().send_led_color(led, color);
  }
} // namespace otto::services
