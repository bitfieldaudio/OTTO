#pragma once

#include "lib/util/smart_ptr.hpp"
#include "lib/util/visitor.hpp"
#include "lib/util/with_limits.hpp"

#include "app/drivers/midi_driver.hpp"
#include "app/input.hpp"
#include "app/layers.hpp"

namespace otto {
  /// Key handler that sends midi events for the keyboard keys
  struct PianoKeyLayer final : IInputLayer, ILEDLayer {
    struct State {
      util::StaticallyBounded<int, -4, 4> octave = 0;
      DECL_VISIT(octave);
    };

    PianoKeyLayer(drivers::MidiController& midi) : midi_(midi) {}

    [[nodiscard]] KeySet key_mask() const noexcept override
    {
      return key_groups::piano + Key::plus + Key::minus;
    }

    [[nodiscard]] LedSet led_mask() const noexcept override
    {
      return led_groups::piano + Led::plus + Led::minus;
    }

    void leds(LEDColorSet& output) noexcept override;

    void handle(EncoderEvent) noexcept override {}
    void handle(KeyPress e) noexcept override;
    void handle(KeyRelease e) noexcept override;

  private:
    drivers::MidiController& midi_;
    std::array<std::uint8_t, 26> key_notes_ = {};
    State state_;
  };
} // namespace otto
