#include "serial.hpp"

#include <cstdio>
#include <gsl/gsl_util>

// Linux headers
#include <errno.h>   // Error integer and strerror() function
#include <fcntl.h>   // Contains file controls like O_RDWR
#include <termios.h> // Contains POSIX terminal control definitions
#include <unistd.h>  // write(), read(), close()

#include "util/exception.hpp"

#include "services/log_manager.hpp"

namespace otto::util {

  template<typename T>
  using expected = tl::expected<T, Serial::exception>;

  Serial::Serial(std::string path, int vtime, int vmin)
    : path_(std::move(path))
  {
    fd_ = open(path_.c_str(), O_RDWR);
    try {
      if (fd_ < 0) {
        throw util::exception("Couldn't open serial device '{}'. ERR {}: {}", path_, errno,
                              strerror(errno));
      }

      termios tty;
      memset(&tty, 0, sizeof tty);

      if (tcgetattr(fd_, &tty) != 0) {
        throw util::exception("Error getting attributes of serial port {}. ERR {}: {}", path_,
                              errno, strerror(errno));
      }

      tty.c_lflag &= ~ICANON;
      tty.c_lflag &= ~ECHO;                   // Disable echo
      tty.c_lflag &= ~ECHOE;                  // Disable erasure
      tty.c_lflag &= ~ECHONL;                 // Disable new-line echo
      tty.c_lflag &= ~ISIG;                   // Disable interpretation of INTR, QUIT and SUSP
      tty.c_iflag &= ~(IXON | IXOFF | IXANY); // Turn off s/w flow ctrl
      tty.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR |
                       ICRNL); // Disable any special handling of received bytes

      tty.c_oflag &= ~OPOST; // Prevent special interpretation of output bytes (e.g. newline chars)
      tty.c_oflag &= ~ONLCR; // Prevent conversion of newline to carriage return/line feed

      tty.c_cc[VTIME] = vtime; // No read timeout
      tty.c_cc[VMIN] = vmin;  // Wait until one byte has been recieved

      // Set baud rate
      cfsetispeed(&tty, B9600);
      cfsetospeed(&tty, B9600);

      if (tcsetattr(fd_, TCSANOW, &tty) != 0) {
        throw util::exception("Error setting attributes of serial port {}. ERR {}: {}", path_,
                              errno, strerror(errno));
      }
      DLOGI("Initialized serial port");
    } catch (...) {
      close(fd_);
      throw;
    }
  }

  Serial::~Serial() noexcept
  {
    close(fd_);
  }

  expected<void> Serial::write(ConstBytesView data)
  {
    auto res = ::write(fd_, data.data(), data.size());
    if (res != data.size()) {
      return tl::make_unexpected(exception(ErrorCode::error,
        "Error writing {} bytes to serial port {}, write returned {}. ERR {}: {}", data.size(),
        path_, res, errno, strerror(errno)));
    }
    return {};
  }

  expected<void> Serial::read(BytesView dest) noexcept
  {
    auto res = ::read(fd_, dest.data(), dest.size());
    if (res == 0) {
      return tl::make_unexpected(exception(ErrorCode::empty_buffer, "No data avaliable on serial port"));
    }
    if (res != dest.size()) {
      return tl::make_unexpected(exception(ErrorCode::error,
        "Error reading {} bytes from serial port {}, write returned {}. ERR {}: {}", dest.size(),
        path_, res, errno, strerror(errno)));
    }
    return {};
  }

  expected<std::vector<std::uint8_t>> Serial::read(std::size_t n) noexcept
  {
    std::vector<std::uint8_t> res;
    res.reserve(n);
    return read(res).map([&] { return res; });
  }

  expected<std::uint8_t> Serial::read_single() noexcept
  {
    std::uint8_t dst = 0;
    return read({&dst, 1}).map([&] { return dst; });
  }

  expected<std::vector<std::uint8_t>> Serial::read_line(std::uint8_t delim) noexcept
  {
    std::vector<std::uint8_t> res;
    std::uint8_t c;
    do {
      auto ec = read_single();
      if (!ec) return tl::make_unexpected(ec.error());
      c = *ec;
      res.push_back(c);
    } while (c != delim);
    return res;
  }

} // namespace otto::util
