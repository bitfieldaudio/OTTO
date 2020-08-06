#pragma once

#include <span>
#include <filesystem>

#include <tl/optional.hpp>

#include "lib/util/thread.hpp"

#include "app/services/controller.hpp"

#include "board/hardware_map.hpp"
#include "board/mcu_controller.hpp"

namespace otto::services {

  using namespace otto::board::controller;

  struct I2C {
    I2C() = default;
    I2C(std::uint16_t address);
    ~I2C() noexcept;

    bool is_open() const noexcept;
    [[nodiscard]] std::error_code open(const fs::path&);
    [[nodiscard]] std::error_code close();

    [[nodiscard]] std::error_code write(gsl::span<std::uint8_t> message);
    [[nodiscard]] std::error_code read_into(gsl::span<std::uint8_t> buffer);

  private:
    int i2c_fd = -1;
    std::uint16_t address = 0;
  };

  /// Communicates with the OTTO MCU over midi sysex
  ///
  /// Useful mainly for development
  struct MCUI2CController final : MCUController {
    using HardwareMap = board::controller::Proto1MCUHardwareMap;
    static constexpr auto I2C_SLAVE_ADDR = 0x77;
    static constexpr chrono::duration sleep_time = chrono::milliseconds(10);

    MCUI2CController();

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

    void read_i2c();

    util::double_buffered<std::vector<util::local_vector<std::uint8_t, 24>>, util::clear_outer> write_buffer_;
    util::sleeper_thread i2c_thread;
    I2C i2c_obj = {I2C_SLAVE_ADDR};
  };

} // namespace otto::services

// kak: other_file=../../src/controller.cpp
