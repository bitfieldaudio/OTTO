#include "led_manager.hpp"

namespace otto::services {
  using drivers::Command;
  using drivers::Packet;

  void LedManager::process(ILedController& controller)
  {
    LEDColorSet res;
    controller.leds(res);
    util::enum_bitset<Led> changed;
    for (auto&& [l, col] : res) {
      changed[l] = col != colors[l];
    }
    colors = res;
    send_colors(changed);
  }

  void LedManager::send_colors(const util::enum_bitset<Led>& do_update)
  {
    // Pack up to 4 LEDs in each packet
    // TODO: Consider packing this even further by reducing color resolution
    // to 6 bits per color.
    int i = 0;
    Packet pack = {Command::leds_buffer};
    pack.data.fill(255);
    for (auto&& [l, col] : colors) {
      if (!do_update[l]) continue;
      if (i == 4) {
        send_(pack);
        pack.data.fill(255);
        i = 0;
      }
      pack.data[i * 4 + 0] = util::enum_integer(l);
      pack.data[i * 4 + 1] = col.r;
      pack.data[i * 4 + 2] = col.g;
      pack.data[i * 4 + 3] = col.b;
      i++;
    }
    if (i != 0) {
      pack.cmd = Command::leds_commit;
      send_(pack);
    }
  }
} // namespace otto::services
