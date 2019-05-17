#pragma once

#include <gsl/span>

#include "util/locked.hpp"
#include "util/thread.hpp"

#include "services/controller.hpp"
#include "util/serial.hpp"

namespace otto::services {

  using BytesView = gsl::span<const std::uint8_t>;

  /**
   * # RPI -> MCU Messages
   *
   * | Byte | Function         | Args        |
   * |-----:|------------------|-------------|
   * | 0x0A | Request alive    |             |
   * | 0x0B | Respond alive    |             |
   * | 0xE0 | Clear all LEDs   | COLOR       |
   * | 0xE1 | Clear LED group  | GROUP,COLOR |
   * | 0xEC | Set LED color    | LED,COLOR   |
   * | 0x2A | Request key dump |             |
   * 
   * # MCU -> RPI Messages
   * 
   * | Byte | Function         | Args     |
   * |-----:|------------------|----------|
   * | 0x0A | Request alive    |          |
   * | 0x0B | Respond alive    |          |
   * | 0x20 | Key down         | KEY      |
   * | 0x21 | Key up           | KEY      |
   * | 0x2B | Respond Key dump | KEY_DUMP |
   * | 0x30 | Blue ENC step    | STEPS    |
   * | 0x31 | Green ENC step   | STEPS    |
   * | 0x32 | Yellow ENC step  | STEPS    |
   * | 0x33 | Red ENC step     | STEPS    |
   * 
   * # Encoding of Colors
   * Colors are simply encoded as 3-byte sequences in RGB order.
   * 
   * ### Example
   * ```
   * 0xFA34D2 -> R = 0xFA, G = 0x34, B = 0xD2
   * ```
   * 
   * # Encoding of Steps
   * Encoder steps are encoded as signed single bytes.
   * 
   * # Encoding of Keys/LEDs
   *
   * Leftmost two bits denote group (enc = 0, funcs = 1, channels = 3, seq = 4), and the remaining 6
   * bits denote the number (as taken from the @ref FuncKey, @ref ChannelKey @ref SeqKey @ref
   * Encoder enums).
   *
   * ### Example
   *
   * ```
   * 0b01000011 -> Channel 3
   * ```
   * 
   * # Encoding of Key dump
   * ???
   */
  struct PrOTTO1SerialController : Controller {
    PrOTTO1SerialController();

    EventBag get_events() override;

    void set_color(LED, LEDColor) override;
    void flush_leds() override;
    void clear_leds() override;

  private:
    void handle_message(BytesView);
    void queue_message(BytesView);

    util::Serial serial = {"/dev/ttyACM0"};
    util::double_buffered<EventBag, util::clear_inner> events_;
    util::thread read_thread;
    bool send_midi_ = true;
  };

} // namespace otto::services

// kak: other_file=../../src/controller.cpp
