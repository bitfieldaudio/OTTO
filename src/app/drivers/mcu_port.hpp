#pragma once

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>

#include <blockingconcurrentqueue.h>

#include "lib/util/mutex.hpp"

#include "app/input.hpp"
#include "app/leds.hpp"
#include "app/services/config.hpp"

namespace otto::drivers {
  enum struct Command : std::uint8_t {
    none = 0,
    leds_buffer = 1,
    leds_commit = 2,
    key_events = 3,
    encoder_events = 4,
    shutdown = 5,
    heartbeat = 6,
  };

  struct Packet {
    Command cmd = Command::none;
    std::array<std::uint8_t, 16> data = {0};

    [[nodiscard]] std::array<std::uint8_t, 17> to_array() const
    {
      std::array<std::uint8_t, 17> res = {};
      res[0] = util::enum_integer(cmd);
      std::ranges::copy(data, res.begin() + 1);
      return res;
    }

    bool operator==(const Packet&) const noexcept = default;
  };

  struct MCUPort {
    virtual ~MCUPort() = default;

    virtual void write(const Packet& p) = 0;

    /// Return a packet if it is ready
    virtual tl::optional<Packet> read() = 0;

    /// Signal stop to kill a blocking call to read
    virtual void stop() = 0;

    static std::unique_ptr<MCUPort> make_default(services::ConfigManager&);
  };

  struct LocalMCUPort : MCUPort, IInputHandler {
    void write(const Packet& p) override
    {
      if (p.cmd == Command::leds_buffer || p.cmd == Command::leds_commit) {
        for (int i = 0; i < 4; i++) {
          auto l = p.data[i * 4 + 0];
          auto r = p.data[i * 4 + 1];
          auto g = p.data[i * 4 + 2];
          auto b = p.data[i * 4 + 3];

          auto optled = util::enum_cast<Led>(l);
          if (!optled) break;
          auto led = *optled;

          uncommitted_led_colors[led] = {r, g, b};
        }

        if (p.cmd == Command::leds_commit) {
          *led_colors.lock() = uncommitted_led_colors;
        }
      }
    };

    /// Return a packet if it is ready
    tl::optional<Packet> read() override
    {
      Packet res;
      if (packets.try_dequeue(res)) {
        return res;
      }
      return tl::nullopt;
    }

    void stop() override
    {
      packets.enqueue(Packet());
      packets.enqueue(Packet());
    }

    void handle(KeyPress e) noexcept override
    {
      Packet p;
      p.cmd = Command::key_events;
      std::span<std::uint8_t> presses = {p.data.data(), 8};
      util::set_bit(presses, util::enum_integer(e.key), true);
      packets.enqueue(p);
    }

    void handle(KeyRelease e) noexcept override
    {
      Packet p;
      p.cmd = Command::key_events;
      std::span<std::uint8_t> releases = {p.data.data() + 8, 8};
      util::set_bit(releases, util::enum_integer(e.key), true);
      packets.enqueue(p);
    }

    void handle(EncoderEvent e) noexcept override
    {
      Packet p;
      p.cmd = Command::encoder_events;
      p.data[util::enum_integer(e.encoder)] = static_cast<std::uint8_t>(e.steps);
      packets.enqueue(p);
    }

    moodycamel::BlockingConcurrentQueue<Packet> packets;
    util::mutex<LEDColorSet> led_colors;

  private:
    LEDColorSet uncommitted_led_colors;
  };


} // namespace otto::drivers
