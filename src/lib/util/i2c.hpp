#pragma once

#include <span>
#include <cstdint>
#include <filesystem>
#include <system_error>

namespace otto::util {

  struct I2C {
    I2C() = default;
    I2C(std::uint16_t address);
    ~I2C() noexcept;

    bool is_open() const noexcept;
    [[nodiscard]] std::error_code open(const std::filesystem::path&);
    [[nodiscard]] std::error_code close();

    [[nodiscard]] std::error_code write(std::span<std::uint8_t> message);
    [[nodiscard]] std::error_code read_into(std::span<std::uint8_t> buffer);

  private:
    int i2c_fd = -1;
    std::uint16_t address = 0;
  };

}
