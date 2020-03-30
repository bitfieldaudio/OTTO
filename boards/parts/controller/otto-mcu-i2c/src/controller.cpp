#include "board/controller.hpp"

#include "util/algorithm.hpp"
#include "util/exception.hpp"
#include "util/utility.hpp"

#include "services/audio_manager.hpp"
#include "services/log_manager.hpp"
#include "services/ui_manager.hpp"

#include <linux/i2c-dev.h>
#include <linux/i2c.h>
#include <linux/input.h>
#include <linux/uinput.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/types.h>

namespace otto::services {
  using MSC = MCUI2CController;
  using Event = MSC::Event;
  using EventBag = MSC::EventBag;
  using namespace core::input;

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

  std::error_code I2C::open(const fs::path& path)
  {
    unsigned long i2c_funcs = 0;

    i2c_fd = ::open(path.c_str(), O_RDWR);
    if (i2c_fd < 0) {
      LOGE("Check that the i2c-dev & i2c-bcm2708 kernel modules "
           "are loaded.");
      return std::error_code{errno, std::generic_category()};
    }

    /*
     * Make sure the driver supports plain I2C I/O:
     */
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

  std::error_code I2C::write(gsl::span<std::uint8_t> message)
  {
    ::i2c_msg iomsg = {
      .addr = address,
      .flags = 0,
      .len = message.size(),
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

  std::error_code I2C::read_into(gsl::span<std::uint8_t> buffer)
  {
    ::i2c_msg iomsg = {
      .addr = address,
      .flags = I2C_M_RD,
      .len = buffer.size(),
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

  void MSC::queue_message(BytesView message)
  {
    // write_buffer_.outer_locked([&](auto& buf) { nano::copy(message, buf.emplace_back().begin()); });
  }

  void MSC::read_i2c()
  {
    std::array<std::uint8_t, 12> data;
    if (auto err = i2c_obj.read_into(data)) {
      LOGE("Error reading from i2c: {} ", err);
      return;
    }
    handle_response(data);
  }

  MSC::MCUI2CController()
  {
    if (auto err = i2c_obj.open("/dev/i2c-1")) {
      LOGE("Error opening i2c device: {}", err);
      throw std::system_error(err, "Error opening i2c device");
    }

    i2c_thread = [this](auto&& should_run) {
      services::LogManager::current().set_thread_name("MCUi2c");
      while (should_run()) {
        write_buffer_.swap();
        auto& wb = write_buffer_.inner();
        if (wb.empty()) {
          wb.push_back({0x00});
        }
        for (auto& message : wb) {
          if (auto err = i2c_obj.write({message.data(), message.size()})) {
            LOGE("Error writing to i2c: {}", err);
          }
          i2c_thread.sleep_for(chrono::microseconds(200));
          read_i2c();
        }
        i2c_thread.sleep_for(sleep_time);
      }
    };
  }

} // namespace otto::services

// kak: other_file=../include/board/controller.hpp
