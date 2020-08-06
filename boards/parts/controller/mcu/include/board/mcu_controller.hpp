#pragma once

#include <gsl/span>
#include <tl/optional.hpp>

#include "app/services/controller.hpp"
#include "lib/util/serial.hpp"

#include "RtMidi.h"

#include "hardware_map.hpp"

namespace otto::services {

  using BytesView = gsl::span<const std::uint8_t>;

  enum struct Command : std::uint8_t {
    read_inputs = 0x00,
    led_set = 0x01,
    leds_clear = 0x02,
  };

  using HardwareMap = board::controller::Proto1MCUHardwareMap;

  struct InputData {
    std::array<std::uint8_t, 8> rows = {0};
    std::array<std::uint8_t, 4> encoders = {0};

    /// @param Callable: `void(Key, bool down_now)`
    template<typename Callable>
    void for_updated_keys(const InputData&, Callable&&);


    /// @param Callable: `void(Encoder, int steps)`
    template<typename Callable>
    void for_updated_encoders(const InputData&, Callable&&);
  };

  /// Base class for controllers that communicate with the OTTO MCU over a binary protocol
  ///
  /// Extend this class, implement `queue_message`, and call `handle_response`.
  struct MCUController : Controller {
    static constexpr chrono::duration sleep_time = chrono::milliseconds(20);

    template<typename Parser>
    void add_args(Parser& cli);

    void set_color(LED, LEDColor) override;
    void flush_leds() override;
    void clear_leds() override;

    static MCUController& current()
    {
      return dynamic_cast<MCUController&>(Controller::current());
    }

  protected:
    virtual void queue_message(BytesView) = 0;
    void handle_response(BytesView);

  private:
    static constexpr std::uint8_t n_encoders = 4;

    InputData last_input_data;
    util::enum_map<Key, std::pair<LEDColor, bool>> led_colors;
  };

  template<typename Callable>
  void InputData::for_updated_keys(const InputData& o, Callable&& f)
  {
    for (auto r : nano::views::iota(0, HardwareMap::n_rows)) {
      for (auto c : nano::views::iota(0, HardwareMap::n_cols)) {
        auto mask = 1 << c;
        bool cur = rows[r] & mask;
        bool prev = o.rows[r] & mask;
        if (cur != prev) {
          HardwareMap::keyCodes[r][c].map_or_else([&](core::input::Key k) { f(k, cur); },
                                                  [&] { DLOGI("Invalid key: r{} c{}", r, c); });
        }
      }
    }
  }

  template<typename Callable>
  void InputData::for_updated_encoders(const InputData& o, Callable&& f)
  {
    for (int i = 0; i < 4; i++) {
      int cur = encoders[i];
      int prev = o.encoders[i];
      if (cur == prev) continue;
      // auto sc = cur, sp = prev;
      if (cur < prev && (prev - cur) > 128) cur += 256;
      if (cur > prev && (cur - prev) > 128) prev += 256;
      // DLOGI("P: {} C: {} steps: {}", sp, sc, cur - prev);
      f(core::input::Encoder::_from_index(i), cur - prev);
    }
  }

  inline void MCUController::handle_response(BytesView bytes)
  {
    OTTO_ASSERT(bytes.size() > 0);
    auto command = Command::read_inputs;
    // auto command = Command::_from_integral_unchecked(bytes[0]);
    // bytes = bytes.subspan(1, gsl::dynamic_extent);
    switch (command) {
      case Command::read_inputs: {
        OTTO_ASSERT(bytes.size() == HardwareMap::n_rows + n_encoders);
        InputData input_data;
        nano::copy(bytes.subspan(0, HardwareMap::n_rows), input_data.rows.begin());
        nano::copy(bytes.subspan(HardwareMap::n_rows, n_encoders), input_data.encoders.begin());
        input_data.for_updated_keys(last_input_data, [this](Key k, bool down) {
          if (down) {
            keypress(k);
          } else {
            keyrelease(k);
          }
        });
        input_data.for_updated_encoders(last_input_data, [this](core::input::Encoder e, int steps) {
          encoder({e, steps});
        });
        last_input_data = input_data;
      } break;
      default: {
        LOGE("Unparsable response");
        break;
      }
    }
  }

  inline void MCUController::set_color(LED led, LEDColor color)
  {
    auto& [old_c, updated] = led_colors[led.key];
    if (old_c != color) {
      old_c = color;
      updated = true;
    }
  }

  inline void MCUController::flush_leds()
  {
    for (auto key : Key::_values()) {
      auto& [color, has_changed] = led_colors[key];
      if (has_changed) {
        auto lm = HardwareMap::led_map[key];
        std::array<std::uint8_t, 6> msg = {
          static_cast<std::uint8_t>(Command::led_set), lm.string, lm.num, color.r, color.g, color.b};
        queue_message(msg);
        has_changed = false;
      }
    }
  }

  inline void MCUController::clear_leds()
  {
    queue_message(std::array{static_cast<std::uint8_t>(Command::leds_clear)});
  }

} // namespace otto::services
