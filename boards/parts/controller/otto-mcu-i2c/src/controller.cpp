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

  void MSC::queue_message(BytesView message)
  {
    //write_buffer_.outer_locked([&](auto& buf) { nano::copy(message, buf.emplace_back().begin()); });
  }

  void MSC::init_i2c(util::string_ref node)
  {
    unsigned long i2c_funcs = 0;

    i2c_fd = open(node.c_str(), O_RDWR);
    if (i2c_fd < 0) {
      LOGE("Check that the i2c-dev & i2c-bcm2708 kernel modules "
           "are loaded.");
      throw util::exception("Error opening {}", node);
    }

    /*
     * Make sure the driver supports plain I2C I/O:
     */
    int rc = ioctl(i2c_fd, I2C_FUNCS, &i2c_funcs);
    OTTO_ASSERT(rc >= 0);
    OTTO_ASSERT(i2c_funcs & I2C_FUNC_I2C);
  }

  void MSC::send_i2c(gsl::span<std::uint8_t> message)
  {
    ::i2c_msg iomsg = {
      .addr = I2C_SLAVE_ADDR,
      .flags = 0,
      .len = message.size(),
      .buf = message.data(),
    };
    ::i2c_rdwr_ioctl_data msgset = {
      .msgs = &iomsg,
      .nmsgs = 1,
    };
    auto res = ioctl(i2c_fd, I2C_RDWR, &msgset);
    if (res < 0) LOGE("Error sending message to MCU over i2c: {}", strerror(errno));
  }

  void MSC::read_i2c()
  {
    std::array<std::uint8_t, 12> data;

    ::i2c_msg iomsg = {
      .addr = I2C_SLAVE_ADDR,
      .flags = I2C_M_RD,
      .len = data.size(),
      .buf = data.data(),
    };
    ::i2c_rdwr_ioctl_data msgset = {
      .msgs = &iomsg,
      .nmsgs = 1,
    };

    auto res = ioctl(i2c_fd, I2C_RDWR, &msgset);
    if (res < 0) {
      LOGE("Error receiving message from MCU over i2c: {}", strerror(errno));
    } else {
      handle_response(data);
    }
  }

  MSC::MCUI2CController()
  {
    init_i2c("/dev/i2c-1");

    i2c_thread = [this](auto&& should_run) {
      services::LogManager::current().set_thread_name("MCUi2c");
      while (should_run()) {
        write_buffer_.swap();
        auto& wb = write_buffer_.inner();
        if (wb.empty()) {
          wb.push_back({0x00});
        }
        for (auto& message : wb) {
          send_i2c({message.data(), message.size()});
          i2c_thread.sleep_for(chrono::microseconds(200));
          read_i2c();
        }
        i2c_thread.sleep_for(sleep_time);
      }
    };
  }

  MSC::~MCUI2CController() noexcept
  {
    if (i2c_fd >= 0) ::close(i2c_fd);
  }

} // namespace otto::services

// kak: other_file=../include/board/controller.hpp
