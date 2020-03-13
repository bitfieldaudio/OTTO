#pragma once

#include <gsl/span>
#include <tl/optional.hpp>

#include "util/local_vector.hpp"
#include "util/locked.hpp"
#include "util/string_ref.hpp"
#include "util/thread.hpp"

#include "services/controller.hpp"
#include "util/serial.hpp"

#include "hardware_map.hpp"
#include "mcu_controller.hpp"

namespace otto::services {

  using namespace otto::board::controller;

  /// Communicates with the OTTO MCU over midi sysex
  ///
  /// Useful mainly for development
  struct MCUI2CController final : MCUController {
    using HardwareMap = board::controller::Proto1MCUHardwareMap;
    static constexpr auto I2C_SLAVE_ADDR = 0x77;
    static constexpr chrono::duration sleep_time = chrono::milliseconds(20);

    MCUI2CController();
    ~MCUI2CController() noexcept;

    template<typename Parser>
    void add_args(Parser& cli);

    static MCUI2CController& current()
    {
      return dynamic_cast<MCUI2CController&>(Controller::current());
    }

  protected:
    void queue_message(BytesView) override;

  private:
    void parse_midi_response(gsl::span<std::uint8_t>);

    void init_i2c(util::string_ref node);
    void send_i2c(gsl::span<std::uint8_t> message);
    void read_i2c();

    util::double_buffered<std::vector<util::local_vector<std::uint8_t, 24>>, util::clear_outer> write_buffer_;
    int i2c_fd = -1;
    util::sleeper_thread i2c_thread;
  };

} // namespace otto::services

// kak: other_file=../../src/controller.cpp
