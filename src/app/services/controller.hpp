#pragma once

#include "app/services/logic_thread.hpp"
#include "lib/core/service.hpp"
#include "lib/util/any_ptr.hpp"

#include "app/input.hpp"
#include "app/leds.hpp"
#include "app/services/config.hpp"

namespace otto::services {
  enum struct Command : std::uint8_t {
    none = 0,
    led_set = 1,
    leds_clear = 2,
    key_events = 3,
    encoder_events = 4,
  };

  struct Packet {
    Command cmd = Command::none;
    std::array<std::uint8_t, 16> data = {0};

    std::array<std::uint8_t, 17> to_array() const
    {
      std::array<std::uint8_t, 17> res;
      res[0] = static_cast<std::uint8_t>(cmd);
      std::ranges::copy(data, res.begin() + 1);
      return res;
    }
  };

  struct MCUPort {
    virtual ~MCUPort() = default;

    virtual void write(const Packet& p) = 0;

    /// Block until the next packet is ready
    virtual Packet read() = 0;

    /// Signal stop to kill a blocking call to read
    virtual void stop() = 0;

    static std::unique_ptr<MCUPort> make_default();
  };

  /// Communicates with the mcu, parsing data etc.
  ///
  /// Does the bulk of the work of {@ref Controller}, but is separated out
  /// to allow usage/testing of the individual methods
  struct MCUCommunicator {
    MCUCommunicator(util::any_ptr<MCUPort>&& port);

    /// Handle received packet, and send events.
    ///
    /// @throws util::exception if the data is invalid.
    void handle_packet(Packet p);

    util::any_ptr<IInputHandler> handler = nullptr;

  private:
    friend struct Controller;
    util::any_ptr<MCUPort> port_;
  };

  struct Controller : core::Service<Controller> {
    struct Config : otto::Config<Config> {
      chrono::duration wait_time = 20ms;
      DECL_VISIT(wait_time);
    };

    explicit Controller(util::any_ptr<MCUPort>&& com = MCUPort::make_default(), Config::Handle conf = {});

    ~Controller() noexcept
    {
      com_.port_->stop();
    }

    void set_input_handler(InputHandler& h);
    void set_led_color(LED led, LEDColor c);

  private:
    [[no_unique_address]] core::ServiceAccessor<services::Runtime> runtime;
    [[no_unique_address]] core::ServiceAccessor<services::LogicThread> logic_thread;

    Config::Handle conf_;
    MCUCommunicator com_;

    std::mutex queue_mutex_;
    std::vector<Packet> queue_;
    std::jthread thread_;
  };

} // namespace otto::services
