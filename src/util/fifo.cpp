#include "fifo.hpp"

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
  using expected = tl::expected<T, FIFO::exception>;

  FIFO::FIFO(std::string path)
    : path_(std::move(path))
  {
    fd_ = open(path_.c_str(), O_RDWR);
    try {
      if (fd_ < 0) {
        throw util::exception("Couldn't open fifo device '{}'. ERR {}: {}", path_, errno,
                              strerror(errno));
      }
      DLOGI("Initialized fifo");
    } catch (...) {
      close(fd_);
      throw;
    }
  }

  FIFO::~FIFO() noexcept
  {
    close(fd_);
  }

  expected<void> FIFO::write(ConstBytesView data)
  {
    auto res = ::write(fd_, data.data(), data.size());
    if (res != data.size()) {
      return tl::make_unexpected(exception(ErrorCode::error,
        "Error writing {} bytes to fifo {}, write returned {}. ERR {}: {}", data.size(),
        path_, res, errno, strerror(errno)));
    }
    return {};
  }

  expected<void> FIFO::read(BytesView dest) noexcept
  {
    auto res = ::read(fd_, dest.data(), dest.size());
    if (res == 0) {
      return tl::make_unexpected(exception(ErrorCode::empty_buffer, "No data avaliable on fifo"));
    }
    if (res != dest.size()) {
      return tl::make_unexpected(exception(ErrorCode::error,
        "Error reading {} bytes from fifo {}, write returned {}. ERR {}: {}", dest.size(),
        path_, res, errno, strerror(errno)));
    }
    return {};
  }

  expected<std::vector<std::uint8_t>> FIFO::read(std::size_t n) noexcept
  {
    std::vector<std::uint8_t> res;
    res.reserve(n);
    return read(res).map([&] { return res; });
  }

  expected<std::uint8_t> FIFO::read_single() noexcept
  {
    std::uint8_t dst = 0;
    return read({&dst, 1}).map([&] { return dst; });
  }

  expected<std::vector<std::uint8_t>> FIFO::read_line(std::uint8_t delim) noexcept
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
