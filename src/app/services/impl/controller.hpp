#pragma once

#include <ranges>
#include <span>
#include <tl/optional.hpp>

#include "app/services/runtime.hpp"
#include "lib/util/any_ptr.hpp"
#include "lib/util/exception.hpp"
#include "lib/util/local_vector.hpp"

#include "app/services/config.hpp"
#include "app/services/controller.hpp"
#include "app/services/logic_thread.hpp"

namespace otto::services {

  enum struct Command {
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
  };

  /// Communicates with the mcu, parsing data etc.
  ///
  /// Does the bulk of the work of {@ref MCUController}, but is separated out
  /// to allow usage/testing of the individual methods
  struct MCUCommunicator {
    MCUCommunicator(util::any_ptr<MCUPort>&& port);

    /// Handle received packet, and send events.
    ///
    /// @throws util::exception if the data is invalid.
    void handle_packet(Packet p);

    util::any_ptr<InputHandler> handler = nullptr;

  private:
    friend struct MCUController;
    util::any_ptr<MCUPort> port_;
  };

  struct MCUController final : Controller {
    struct Config : otto::Config<Config> {
      chrono::duration wait_time = 20ms;
      DECL_VISIT(wait_time);
    };

    explicit MCUController(util::any_ptr<MCUPort>&& com, Config::Handle conf = {});

    void set_input_handler(InputHandler& h) override;
    void set_led_color(LED led, LEDColor c) override;

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
