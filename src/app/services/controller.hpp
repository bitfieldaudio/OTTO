#pragma once

#include "lib/util/smart_ptr.hpp"

#include "app/drivers/mcu_port.hpp"
#include "app/input.hpp"
#include "app/leds.hpp"
#include "app/services/config.hpp"
#include "app/services/logic_thread.hpp"

namespace otto::services {
  /// Communicates with the mcu, parsing data etc.
  ///
  /// Does the bulk of the work of {@ref Controller}, but is separated out
  /// to allow usage/testing of the individual methods
  struct MCUCommunicator {
    MCUCommunicator(RuntimeController& rt, util::smart_ptr<drivers::MCUPort>&& port);

    /// Handle received packet, and send events.
    ///
    /// @throws util::exception if the data is invalid.
    void handle_packet(drivers::Packet p);

    util::smart_ptr<IInputHandler> handler = nullptr;

  private:
    friend struct Controller;
    RuntimeController& rt_;
    util::smart_ptr<drivers::MCUPort> port_;
  };

  struct Controller {
    struct Config : otto::Config<Config> {
      chrono::duration wait_time = 1ms;
      DECL_VISIT(wait_time);
    };

    explicit Controller(RuntimeController& rt,
                        Config conf,
                        util::smart_ptr<drivers::MCUPort>&& port = drivers::MCUPort::make_default());

    Controller(const Controller&) = delete;
    Controller& operator=(const Controller&) = delete;

    ~Controller() noexcept
    {
      com_.port_->stop();
    }

    void set_input_handler(IInputHandler& h);

    drivers::MCUPort& port() noexcept
    {
      return *com_.port_;
    }

  private:
    Config conf_;
    MCUCommunicator com_;

    std::mutex queue_mutex_;
    std::vector<drivers::Packet> queue_;
    std::jthread thread_;
  };

} // namespace otto::services
