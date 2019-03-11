#pragma once

#include <string_view>
#include <tl/expected.hpp>

#include "util/exception.hpp"

namespace otto::util {

  enum struct StringConvErrCode { invalid_input, out_of_range };
  using StringConvErr = util::as_exception<StringConvErrCode>;

  std::string to_lowercase(std::string_view sv) noexcept;
  std::string to_uppercase(std::string_view sv) noexcept;

  std::string to_string(int i) noexcept;
  std::string to_string(long i) noexcept;
  std::string to_string(long long i) noexcept;
  std::string to_string(unsigned int i) noexcept;
  std::string to_string(unsigned long i) noexcept;
  std::string to_string(unsigned long long i) noexcept;

  std::string to_string(float i) noexcept;
  std::string to_string(double i) noexcept;
  std::string to_string(long double i) noexcept;

  std::string_view to_string(bool b) noexcept;
  std::string_view to_string(std::string_view v) noexcept;

  template<typename T>
  tl::expected<T, StringConvErr> from_string(std::string_view) noexcept;
  template<>
  tl::expected<long, StringConvErr> from_string(std::string_view sv) noexcept;
  template<>
  tl::expected<long long, StringConvErr> from_string(std::string_view sv) noexcept;
  template<>
  tl::expected<unsigned int, StringConvErr> from_string(std::string_view sv) noexcept;
  template<>
  tl::expected<unsigned long, StringConvErr> from_string(std::string_view sv) noexcept;
  template<>
  tl::expected<unsigned long long, StringConvErr> from_string(std::string_view sv) noexcept;

  template<>
  tl::expected<float, StringConvErr> from_string(std::string_view sv) noexcept;
  template<>
  tl::expected<double, StringConvErr> from_string(std::string_view sv) noexcept;
  template<>
  tl::expected<double, StringConvErr> from_string(std::string_view sv) noexcept;

  template<>
  tl::expected<bool, StringConvErr> from_string(std::string_view sv) noexcept;
  template<>
  tl::expected<std::string_view, StringConvErr> from_string(std::string_view sv) noexcept;

} // namespace otto::util

// IMPLEMENTATION //

namespace otto::util {

  std::string to_lowercase(std::string_view sv) noexcept
  {
    std::string res;
    res.reserve(sv.size());
    std::transform(sv.begin(), sv.end(), std::back_inserter(res), ::tolower);
    return res;
  }

  std::string to_uppercase(std::string_view sv) noexcept
  {
    std::string res;
    res.reserve(sv.size());
    std::transform(sv.begin(), sv.end(), std::back_inserter(res), ::toupper);
    return res;
  }

  std::string to_string(int i) noexcept
  {
    return std::to_string(i);
  }
  std::string to_string(long i) noexcept
  {
    return std::to_string(i);
  }
  std::string to_string(long long i) noexcept
  {
    return std::to_string(i);
  }
  std::string to_string(unsigned int i) noexcept
  {
    return std::to_string(i);
  }
  std::string to_string(unsigned long i) noexcept
  {
    return std::to_string(i);
  }
  std::string to_string(unsigned long long i) noexcept
  {
    return std::to_string(i);
  }

  std::string to_string(float i) noexcept
  {
    return std::to_string(i);
  }
  std::string to_string(double i) noexcept
  {
    return std::to_string(i);
  }
  std::string to_string(long double i) noexcept
  {
    return std::to_string(i);
  }

  std::string_view to_string(bool b) noexcept
  {
    return b ? "true" : "false";
  }
  std::string_view to_string(std::string_view sv) noexcept
  {
    return sv;
  }

  template<>
  tl::expected<int, StringConvErr> from_string(std::string_view sv) noexcept
  {
    char* end;
    errno = 0;
    int res = std::strtol(&sv.front(), &end, 0);
    if (errno == ERANGE) {
      errno = 0;
      return tl::make_unexpected(StringConvErr{StringConvErrCode::out_of_range});
    }
    if (res == 0 && end == &sv.front()) {
      return tl::make_unexpected(StringConvErr{StringConvErrCode::invalid_input});
    }
    return res;
  }
  template<>
  tl::expected<long, StringConvErr> from_string(std::string_view sv) noexcept
  {
    char* end;
    errno = 0;
    long res = std::strtol(&sv.front(), &end, 0);
    if (errno == ERANGE) {
      errno = 0;
      return tl::make_unexpected(StringConvErr{StringConvErrCode::out_of_range});
    }
    if (res == 0 && end == &sv.front()) {
      return tl::make_unexpected(StringConvErr{StringConvErrCode::invalid_input});
    }
    return res;
  }
  template<>
  tl::expected<long long, StringConvErr> from_string(std::string_view sv) noexcept
  {
    char* end;
    errno = 0;
    long long res = std::strtoll(&sv.front(), &end, 0);
    if (errno == ERANGE) {
      errno = 0;
      return tl::make_unexpected(StringConvErr{StringConvErrCode::out_of_range});
    }
    if (res == 0 && end == &sv.front()) {
      return tl::make_unexpected(StringConvErr{StringConvErrCode::invalid_input});
    }
    return res;
  }
  template<>
  tl::expected<unsigned int, StringConvErr> from_string(std::string_view sv) noexcept
  {
    char* end;
    errno = 0;
    unsigned res = std::strtoul(&sv.front(), &end, 0);
    if (errno == ERANGE) {
      errno = 0;
      return tl::make_unexpected(StringConvErr{StringConvErrCode::out_of_range});
    }
    if (res == 0 && end == &sv.front()) {
      return tl::make_unexpected(StringConvErr{StringConvErrCode::invalid_input});
    }
    return res;
  }
  template<>
  tl::expected<unsigned long, StringConvErr> from_string(std::string_view sv) noexcept
  {
    char* end;
    errno = 0;
    unsigned long res = std::strtoul(&sv.front(), &end, 0);
    if (errno == ERANGE) {
      errno = 0;
      return tl::make_unexpected(StringConvErr{StringConvErrCode::out_of_range});
    }
    if (res == 0 && end == &sv.front()) {
      return tl::make_unexpected(StringConvErr{StringConvErrCode::invalid_input});
    }
    return res;
  }
  template<>
  tl::expected<unsigned long long, StringConvErr> from_string(std::string_view sv) noexcept
  {
    char* end;
    errno = 0;
    unsigned long long res = std::strtoull(&sv.front(), &end, 0);
    if (errno == ERANGE) {
      errno = 0;
      return tl::make_unexpected(StringConvErr{StringConvErrCode::out_of_range});
    }
    if (res == 0 && end == &sv.front()) {
      return tl::make_unexpected(StringConvErr{StringConvErrCode::invalid_input});
    }
    return res;
  }

  template<>
  tl::expected<float, StringConvErr> from_string(std::string_view sv) noexcept
  {
    char* end;
    errno = 0;
    float res = std::strtof(&sv.front(), &end);
    if (errno == ERANGE) {
      errno = 0;
      return tl::make_unexpected(StringConvErr{StringConvErrCode::out_of_range});
    }
    if (res == 0 && end == &sv.front()) {
      return tl::make_unexpected(StringConvErr{StringConvErrCode::invalid_input});
    }
    return res;
  }

  template<>
  tl::expected<double, StringConvErr> from_string(std::string_view sv) noexcept
  {
    char* end;
    errno = 0;
    double res = std::strtod(&sv.front(), &end);
    if (errno == ERANGE) {
      errno = 0;
      return tl::make_unexpected(StringConvErr{StringConvErrCode::out_of_range});
    }
    if (res == 0 && end == &sv.front()) {
      return tl::make_unexpected(StringConvErr{StringConvErrCode::invalid_input});
    }
    return res;
  }
  template<>
  tl::expected<long double, StringConvErr> from_string(std::string_view sv) noexcept
  {
    char* end;
    errno = 0;
    long double res = std::strtold(&sv.front(), &end);
    if (errno == ERANGE) {
      errno = 0;
      return tl::make_unexpected(StringConvErr{StringConvErrCode::out_of_range});
    }
    if (res == 0 && end == &sv.front()) {
      return tl::make_unexpected(StringConvErr{StringConvErrCode::invalid_input});
    }
    return res;
  }

  template<>
  tl::expected<bool, StringConvErr> from_string(std::string_view sv) noexcept
  {
    if (to_lowercase(sv) == "true") return true;
    if (to_lowercase(sv) == "false") return false;
    return tl::make_unexpected(StringConvErr{StringConvErrCode::out_of_range});
  }

  template<>
  tl::expected<std::string_view, StringConvErr> from_string(std::string_view sv) noexcept
  {
    return sv;
  }

} // namespace otto::util
