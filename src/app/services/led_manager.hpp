#pragma once

#include "lib/skia/color.hpp"

#include "app/leds.hpp"
#include "app/services/config.hpp"
#include "app/services/controller.hpp"

namespace otto::services {

  struct LedManager {
    using Sender = util::FuncInterface<&drivers::MCUPort::write>;

    LedManager(Sender sender) : send_(std::move(sender)) {}

    void process(ILedController& controller);

    void send_colors(const util::enum_bitset<Led>& do_update = util::enum_bitset<Led>::make_with_all(true));

    LEDColorSet colors;

  private:
    Sender send_ = nullptr;
  };
} // namespace otto::services
