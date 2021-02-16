#pragma once

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>

#include <blockingconcurrentqueue.h>

#include "app/input.hpp"
#include "app/services/config.hpp"

namespace otto::drivers {
  enum struct Command : std::uint8_t {
    none = 0,
    leds_buffer = 1,
    leds_commit = 2,
    key_events = 3,
    encoder_events = 4,
    shutdown = 5,
  };

  struct Packet {
    Command cmd = Command::none;
    std::array<std::uint8_t, 16> data = {0};

    [[nodiscard]] std::array<std::uint8_t, 17> to_array() const
    {
      std::array<std::uint8_t, 17> res = {};
      res[0] = util::narrow(cmd);
      std::ranges::copy(data, res.begin() + 1);
      return res;
    }

    bool operator==(const Packet&) const noexcept = default;
  };

  struct MCUPort {
    virtual ~MCUPort() = default;

    virtual void write(const Packet& p) = 0;

    /// Block until the next packet is ready
    virtual Packet read() = 0;

    /// Signal stop to kill a blocking call to read
    virtual void stop() = 0;

    static std::unique_ptr<MCUPort> make_default(services::ConfigManager&);
  };

  struct LocalMCUPort : MCUPort, IInputHandler {
    // UNIMPLEMENTED
    void write(const Packet& p) override{};

    /// Block until the next packet is ready
    Packet read() override
    {
      Packet res;
      packets.wait_dequeue(res);
      return res;
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
  };


} // namespace otto::drivers
