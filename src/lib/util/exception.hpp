#pragma once

#include <exception>
#include <string>
#include <string_view>

#include <fmt/format.h>

namespace otto::lib::util {

  struct exception : public std::exception {
    /// String formatting constructor. Models `fmt::format`
    ///
    /// \param message Error message with optional fmtlib style format specifiers
    /// \param args Optional format arguments.
    ///
    /// \effects Constructs with message `fmt::format(message, args...)`
    template<typename... Args>
    exception(std::string message, Args&&... args) : message{fmt::format(message, std::forward<Args>(args)...)}
    {}

    const char* what() const noexcept override
    {
      return message.c_str();
    }

    /// Create a new `exception` with `v` appended to the message
    [[nodiscard]] exception append(std::string_view v) const
    {
      exception e = *this;
      e.message.append("\n");
      e.message.append(v);
      return e;
    }

    std::string message;
  };

  /// A wrapper for throwing arbitrary data
  ///
  /// Always use this instead of throwing an error code.
  ///
  /// ## Prefered usage (error codes):
  ///
  /// Define an `ErrorCode` enum, and a type alias to `as_exception<ErrorCode>`
  /// as member types in your class. You may also want to write a
  /// `to_string(ErrorCode)` function, which will be appended to the exception
  /// message.
  ///
  /// ```cpp
  /// enum struct ErrorCode {
  ///   none = 0,
  ///   not_found,
  ///   invalid
  /// }
  /// using exception = util::as_exception<ErrorCode>;
  /// ```
  template<typename Data>
  struct as_exception : exception {
    using data_type = Data;

    template<typename DataRef, typename... Args>
    as_exception(DataRef&& dr, const std::string& m, Args&&... args)
      : exception(m, std::forward<Args>(args)...), _data(std::forward<DataRef>(dr))
    {
      using namespace std::literals;
      auto str_data = to_str_or_empty(_data);
      if (!str_data.empty()) {
        message.append("\nData: ");
        message.append(str_data);
      }
    }

    template<typename DataRef>
    as_exception(DataRef&& dr) : as_exception(std::forward<DataRef>(dr), "")
    {}

    data_type& data() noexcept
    {
      return _data;
    }

    const data_type& data() const noexcept
    {
      return _data;
    }

  private:
    data_type _data;

    template<typename T>
    static auto to_str_or_empty(T&& t) -> std::enable_if_t<std::is_constructible_v<std::string, T>, std::string>
    {
      return std::string(std::forward<T>(t));
    }

    template<typename T>
    static auto to_str_or_empty(T&& t) -> std::string
    {
      return {};
    }
  };


  template<typename DataRef, typename... Args>
  as_exception(DataRef&& dr, const std::string& message, Args&&... args) -> as_exception<std::decay_t<DataRef>>;
} // namespace otto::lib::util
