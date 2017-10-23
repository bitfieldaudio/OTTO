#pragma once

#include <exception>
#include <string>
#include <string_view>

#include <fmt/format.h>

namespace otto::util {

  class exception : public std::exception {

    std::string message;

  public:

    /// String formatting constructor. Models `fmt::format`
    ///
    /// \param message Error message with optional fmtlib style format specifiers
    /// \param args Optional format arguments.
    ///
    /// \effects Constructs with message `fmt::format(message, args...)`
    template<typename... Args>
    exception(std::string message, Args&&... args)
      : message {fmt::format(message, std::forward<Args>(args)...)}
    {}

    const char* what() const noexcept override {
      return message.c_str();
    }
  };
}
