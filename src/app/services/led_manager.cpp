#include "led_manager.hpp"

namespace otto::services {

  void LedManager::process(ILedController& controller)
  {
    LEDColorSet res;
    controller.leds(res);
    for (auto&& [l, col] : res) {
      set(l, col, false);
    }
  }

  void LedManager::set(Led led, LEDColor color, bool force)
  {
    auto& ref = colors_[led];
    if (!force && ref == color) return;
    ref = color;
    auto b = config_->brightness;
    auto min = config_->min_color;
    LEDColor adjcol = {
      std::clamp(static_cast<std::uint8_t>(static_cast<float>(color.r) * b), min.r, std::uint8_t(0xFF)),
      std::clamp(static_cast<std::uint8_t>(static_cast<float>(color.g) * b), min.g, std::uint8_t(0xFF)),
      std::clamp(static_cast<std::uint8_t>(static_cast<float>(color.b) * b), min.b, std::uint8_t(0xFF)),
    };
    send(led, adjcol);
  }

  void LedManager::send(Led led, LEDColor color)
  {
    service<services::Controller>().send_led_color(led, color);
  }

  LedManager::LedManager()
  {
    for (auto l : util::enum_values<Led>()) {
      set(l, config_->min_color, true);
    }
  };
} // namespace otto::services
