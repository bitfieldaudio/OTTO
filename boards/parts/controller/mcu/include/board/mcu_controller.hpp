#pragma once

#include <algorithm>
#include <ranges>
#include <span>
#include <tl/optional.hpp>

#include "app/services/logic_thread.hpp"
#include "lib/chrono.hpp"

#include "app/services/controller.hpp"

#include "hardware_map.hpp"

namespace otto::board::controller {
  using namespace app;
  using namespace lib;

  using app::services::Encoder;
  using app::services::Key;

  using BytesView = std::span<const std::uint8_t>;

  enum struct Command : std::uint8_t {
    read_inputs = 0x00,
    led_set = 0x01,
    leds_clear = 0x02,
  };

  struct InputData {
    std::array<std::uint8_t, 8> rows = {0};
    std::array<std::uint8_t, 4> encoders = {0};

    void for_updated_keys(const InputData&, const HardwareMap&, const util::callable<void(Key, bool)> auto&);
    void for_updated_encoders(const InputData&, const util::callable<void(Encoder, bool)> auto&);
  };

  // TODO: Move
  inline Proto1MCUHardwareMap default_hw_map;

  /// Base class for controllers that communicate with the OTTO MCU over a binary protocol
  ///
  /// Extend this class, implement `queue_message`, and call `handle_response`.
  struct MCUController : services::Controller {
    static constexpr lib::chrono::duration sleep_time = lib::chrono::milliseconds(20);

    void set_input_handler(services::InputHandler& h) override
    {
      handler = &h;
    }

  protected:
    virtual void queue_message(BytesView) = 0;
    void handle_response(BytesView);

  private:
    static constexpr std::uint8_t n_encoders = 4;

    [[no_unique_address]] lib::core::ServiceAccessor<services::LogicThread> logic_thread;
    services::InputHandler* handler = nullptr;
    HardwareMap* hw_map = &default_hw_map;
    InputData last_input_data;
  };

  void InputData::for_updated_keys(const InputData& o,
                                   const HardwareMap& map,
                                   const util::callable<void(Key, bool)> auto& f)
  {
    for (auto r : std::views::iota(0, map.row_count())) {
      for (auto c : std::views::iota(0, map.col_count())) {
        auto mask = 1 << c;
        bool cur = rows[r] & mask;
        bool prev = o.rows[r] & mask;
        if (cur != prev) {
          map.key_at(r, c).map_or_else([&](Key k) { f(k, cur); }, [&] { DLOGI("Invalid key: r{} c{}", r, c); });
        }
      }
    }
  }

  void InputData::for_updated_encoders(const InputData& o, const util::callable<void(Encoder, bool)> auto& f)
  {
    for (int i = 0; i < 4; i++) {
      int cur = encoders[i];
      int prev = o.encoders[i];
      if (cur == prev) continue;
      // auto sc = cur, sp = prev;
      if (cur < prev && (prev - cur) > 128) cur += 256;
      if (cur > prev && (cur - prev) > 128) prev += 256;
      // DLOGI("P: {} C: {} steps: {}", sp, sc, cur - prev);
      if (auto opt = util::enum_cast<app::services::Encoder>(i); opt.has_value()) {
        f(*opt, cur - prev);
      } else {
        LOGE("Got update for non-existant encoder {}", i);
      }
    }
  }

  inline void MCUController::handle_response(BytesView bytes)
  {
    OTTO_ASSERT(bytes.size() > 0);
    auto command = Command::read_inputs;
    // auto command = Command::_from_integral_unchecked(bytes[0]);
    // bytes = bytes.subspan(1, gsl::dynamic_extent);
    auto& executor = logic_thread->executor();
    auto send_event = [&](auto event) {
      executor.execute([event, handler = this->handler] { handler->handle(event); });
    };
    switch (command) {
      case Command::read_inputs: {
        OTTO_ASSERT(bytes.size() == hw_map->row_count() + n_encoders);
        InputData input_data;
        std::ranges::copy(bytes.subspan(0, hw_map->row_count()), input_data.rows.begin());
        std::ranges::copy(bytes.subspan(hw_map->row_count(), n_encoders), input_data.encoders.begin());
        input_data.for_updated_keys(last_input_data, *hw_map, [&](Key k, bool down) {
          if (down) {
            send_event(services::KeyPress{{k}});
          } else {
            send_event(services::KeyRelease{{k}});
          }
        });
        input_data.for_updated_encoders(last_input_data, [&](Encoder e, int steps) {
          send_event(services::EncoderEvent{e, steps});
        });
        last_input_data = input_data;
      } break;
      default: {
        LOGE("Unparsable response");
        break;
      }
    }
  }
} // namespace otto::board::controller
