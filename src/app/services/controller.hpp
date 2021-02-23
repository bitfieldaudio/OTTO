#pragma once

#include "lib/util/at_exit.hpp"
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

  struct Controller : LogicDomain {
    struct Config : otto::Config<Config> {
      chrono::duration wait_time = 1ms;
      DECL_VISIT(wait_time);
    };

    explicit Controller(RuntimeController& rt, ConfigManager& confman, util::smart_ptr<drivers::MCUPort>&& port);
    explicit Controller(RuntimeController& rt, ConfigManager& confman)
      : Controller(rt, confman, drivers::MCUPort::make_default(confman))
    {}

    Controller(const Controller&) = delete;
    Controller& operator=(const Controller&) = delete;

    ~Controller() noexcept
    {
      com_.port_->stop();
    }

    util::at_exit set_input_handler(IInputHandler& h);

    auto port_writer() noexcept
    {
      return [this](const drivers::Packet& p) { queue_.enqueue(p); };
    }

  private:
    Config conf_;
    MCUCommunicator com_;

    moodycamel::ConcurrentQueue<drivers::Packet> queue_;
    std::jthread thread_;
  };

} // namespace otto::services
