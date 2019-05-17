#pragma once

#include <gsl/span>
#include <string>

namespace otto::util {

  using ConstBytesView = gsl::span<const std::uint8_t>;
  using BytesView = gsl::span<std::uint8_t>;

  /// Serial port communication
  struct Serial {
    Serial(std::string path);
    ~Serial() noexcept;

    void write(ConstBytesView);
    void read(BytesView dest);
    std::vector<std::uint8_t> read(std::size_t n);
    template<std::size_t N>
    std::array<std::uint8_t, N> read();
    std::uint8_t read_single();
    std::vector<std::uint8_t> read_line(std::uint8_t delim = '\n');


    const std::string& path() noexcept
    {
      return path_;
    }

    int file_descriptor() noexcept
    {
      return fd_;
    }

  private:
    std::string path_;
    int fd_;
  };

  template<std::size_t N>
  std::array<std::uint8_t, N> Serial::read()
  {
    std::array<std::uint8_t, N> res;
    read({res.data(), res.size()});
    return res;
  }
} // namespace otto::util
