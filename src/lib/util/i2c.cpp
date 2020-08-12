#include "i2c.hpp"
#include <fcntl.h>
#include <linux/i2c-dev.h>
#include <linux/i2c.h>
#include <linux/input.h>
#include <linux/uinput.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "lib/logging.hpp"

namespace otto::util {

  using byte = std::uint8_t;

  I2C::I2C(std::uint16_t address) : address(address) {}

  I2C::~I2C() noexcept
  {
    if (is_open()) (void) close();
  }

  bool I2C::is_open() const noexcept
  {
    return i2c_fd > 0;
  }

  std::error_code I2C::open(const std::filesystem::path& path)
  {
    unsigned long i2c_funcs = 0;

    i2c_fd = ::open(path.c_str(), O_RDWR);
    if (i2c_fd < 0) {
      LOGE("Check that the i2c-dev & i2c-bcm2708 kernel modules "
           "are loaded.");
      return std::error_code{errno, std::generic_category()};
    }

    // Make sure the driver supports plain I2C I/O:
    int rc = ioctl(i2c_fd, I2C_FUNCS, &i2c_funcs);
    OTTO_ASSERT(i2c_funcs & I2C_FUNC_I2C);
    if (rc) return std::error_code{errno, std::generic_category()};
    return {};
  }

  std::error_code I2C::close()
  {
    if (::close(i2c_fd)) return std::error_code{errno, std::generic_category()};
    return {};
  }

  std::error_code I2C::write(std::span<std::uint8_t> message)
  {
    ::i2c_msg iomsg = {
      .addr = address,
      .flags = 0,
      .len = static_cast<std::uint16_t>(message.size()),
      .buf = message.data(),
    };
    ::i2c_rdwr_ioctl_data msgset = {
      .msgs = &iomsg,
      .nmsgs = 1,
    };
    auto res = ioctl(i2c_fd, I2C_RDWR, &msgset);
    if (res < 0) return std::error_code{errno, std::generic_category()};
    return {};
  }

  std::error_code I2C::read_into(std::span<std::uint8_t> buffer)
  {
    ::i2c_msg iomsg = {
      .addr = address,
      .flags = I2C_M_RD,
      .len = static_cast<std::uint16_t>(buffer.size()),
      .buf = buffer.data(),
    };
    ::i2c_rdwr_ioctl_data msgset = {
      .msgs = &iomsg,
      .nmsgs = 1,
    };

    auto res = ioctl(i2c_fd, I2C_RDWR, &msgset);
    if (res < 0) return std::error_code{errno, std::generic_category()};
    return {};
  }

} // namespace otto::util
