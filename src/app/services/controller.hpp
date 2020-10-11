#pragma once

#include "app/services/logic_thread.hpp"
#include "lib/core/service.hpp"
#include "lib/util/any_ptr.hpp"

#include "app/drivers/mcu_port.hpp"
#include "app/input.hpp"
#include "app/leds.hpp"
#include "app/services/config.hpp"

namespace otto::services {
  /// Communicates with the mcu, parsing data etc.
  ///
  /// Does the bulk of the work of {@ref Controller}, but is separated out
  /// to allow usage/testing of the individual methods
  struct MCUCommunicator {
    MCUCommunicator(util::any_ptr<drivers::MCUPort>&& port);

    /// Handle received packet, and send events.
    ///
    /// @throws util::exception if the data is invalid.
    void handle_packet(drivers::Packet p);

    util::any_ptr<IInputHandler> handler = nullptr;

  private:
    friend struct Controller;
    util::any_ptr<drivers::MCUPort> port_;
  };

  struct Controller : core::Service<Controller> {
    struct Config : otto::Config<Config> {
      chrono::duration wait_time = 20ms;
      DECL_VISIT(wait_time);
    };

    explicit Controller(util::any_ptr<drivers::MCUPort>::factory&& make_com = drivers::MCUPort::make_default,
                        Config::Handle conf = {});

    ~Controller() noexcept
    {
      com_.port_->stop();
    }

    void set_input_handler(IInputHandler& h);
    void set_led_color(LED led, LEDColor c);

  private:
    [[no_unique_address]] core::ServiceAccessor<services::Runtime> runtime;
    [[no_unique_address]] core::ServiceAccessor<services::LogicThread> logic_thread;

    Config::Handle conf_;
    MCUCommunicator com_;

    std::mutex queue_mutex_;
    std::vector<drivers::Packet> queue_;
    std::jthread thread_;
  };

} // namespace otto::services
