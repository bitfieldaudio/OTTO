#pragma once

#include <better_enum.hpp>
#include <cerrno>
#include <cstdlib>
#include <string_view>
#include <tl/expected.hpp>
#include <tl/optional.hpp>

#include "util/exception.hpp"
#include "util/string_ref.hpp"
#include "util/type_traits.hpp"

namespace otto::util {

  enum struct StringConvErrCode { invalid_input, out_of_range };
  using StringConvErr = util::as_exception<StringConvErrCode>;


  [[nodiscard]] std::string to_lowercase(std::string_view sv) noexcept;
  [[nodiscard]] std::string to_uppercase(std::string_view sv) noexcept;

  [[nodiscard]] std::string to_string(int i) noexcept;
  [[nodiscard]] std::string to_string(long i) noexcept;
  [[nodiscard]] std::string to_string(long long i) noexcept;
  [[nodiscard]] std::string to_string(unsigned int i) noexcept;
  [[nodiscard]] std::string to_string(unsigned long i) noexcept;
  [[nodiscard]] std::string to_string(unsigned long long i) noexcept;

  [[nodiscard]] std::string to_string(float i) noexcept;
  [[nodiscard]] std::string to_string(double i) noexcept;
  [[nodiscard]] std::string to_string(long double i) noexcept;

  [[nodiscard]] constexpr util::string_ref to_string(bool b) noexcept;
  [[nodiscard]] constexpr std::string_view to_string(std::string_view v) noexcept;
  [[nodiscard]] std::string& to_string(std::string& v) noexcept;
  [[nodiscard]] const std::string& to_string(const std::string& v) noexcept;

  template<typename T, typename = std::enable_if_t<BetterEnum::is<T>>>
  [[nodiscard]] constexpr util::string_ref to_string(T e) noexcept;

  template<typename T>
  [[nodiscard]] tl::expected<T, StringConvErr> from_string(std::string_view) noexcept;
  template<>
  [[nodiscard]] tl::expected<long, StringConvErr> from_string(std::string_view sv) noexcept;
  template<>
  [[nodiscard]] tl::expected<long long, StringConvErr> from_string(std::string_view sv) noexcept;
  template<>
  [[nodiscard]] tl::expected<unsigned int, StringConvErr> from_string(std::string_view sv) noexcept;
  template<>
  [[nodiscard]] tl::expected<unsigned long, StringConvErr> from_string(std::string_view sv) noexcept;
  template<>
  [[nodiscard]] tl::expected<unsigned long long, StringConvErr> from_string(std::string_view sv) noexcept;

  template<>
  [[nodiscard]] tl::expected<float, StringConvErr> from_string(std::string_view sv) noexcept;
  template<>
  [[nodiscard]] tl::expected<double, StringConvErr> from_string(std::string_view sv) noexcept;
  template<>
  [[nodiscard]] tl::expected<double, StringConvErr> from_string(std::string_view sv) noexcept;

  template<>
  [[nodiscard]] tl::expected<bool, StringConvErr> from_string(std::string_view sv) noexcept;
  template<>
  [[nodiscard]] tl::expected<std::string_view, StringConvErr> from_string(std::string_view sv) noexcept;

} // namespace otto::util

// IMPLEMENTATION //

namespace otto::util {

  inline std::string to_lowercase(std::string_view sv) noexcept
  {
    std::string res;
    res.reserve(sv.size());
    std::transform(sv.begin(), sv.end(), std::back_inserter(res), ::tolower);
    return res;
  }

  inline std::string to_uppercase(std::string_view sv) noexcept
  {
    std::string res;
    res.reserve(sv.size());
    std::transform(sv.begin(), sv.end(), std::back_inserter(res), ::toupper);
    return res;
  }

  inline std::string to_string(int i) noexcept
  {
    return std::to_string(i);
  }
  inline std::string to_string(long i) noexcept
  {
    return std::to_string(i);
  }
  inline std::string to_string(long long i) noexcept
  {
    return std::to_string(i);
  }
  inline std::string to_string(unsigned int i) noexcept
  {
    return std::to_string(i);
  }
  inline std::string to_string(unsigned long i) noexcept
  {
    return std::to_string(i);
  }
  inline std::string to_string(unsigned long long i) noexcept
  {
    return std::to_string(i);
  }

  inline std::string to_string(float i) noexcept
  {
    return std::to_string(i);
  }
  inline std::string to_string(double i) noexcept
  {
    return std::to_string(i);
  }
  inline std::string to_string(long double i) noexcept
  {
    return std::to_string(i);
  }

  constexpr util::string_ref to_string(bool b) noexcept
  {
    return b ? "true" : "false";
  }
  constexpr std::string_view to_string(std::string_view sv) noexcept
  {
    return sv;
  }
  inline std::string& to_string(std::string& s) noexcept
  {
    return s;
  }
  inline const std::string& to_string(const std::string& s) noexcept
  {
    return s;
  }

  template<typename T, typename EnableIfTisEnum>
  constexpr util::string_ref to_string(T e) noexcept
  {
    if (!T::_is_valid(e._to_integral())) return util::string_ref("");
    return util::string_ref(e._to_string());
  }

  template<>
  inline tl::expected<int, StringConvErr> from_string(std::string_view sv) noexcept
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
  inline tl::expected<long, StringConvErr> from_string(std::string_view sv) noexcept
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
  inline tl::expected<long long, StringConvErr> from_string(std::string_view sv) noexcept
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
  inline tl::expected<unsigned int, StringConvErr> from_string(std::string_view sv) noexcept
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
  inline tl::expected<unsigned long, StringConvErr> from_string(std::string_view sv) noexcept
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
  inline tl::expected<unsigned long long, StringConvErr> from_string(std::string_view sv) noexcept
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
  inline tl::expected<float, StringConvErr> from_string(std::string_view sv) noexcept
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
  inline tl::expected<double, StringConvErr> from_string(std::string_view sv) noexcept
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
  inline tl::expected<long double, StringConvErr> from_string(std::string_view sv) noexcept
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
  inline tl::expected<bool, StringConvErr> from_string(std::string_view sv) noexcept
  {
    if (to_lowercase(sv) == "true") return true;
    if (to_lowercase(sv) == "false") return false;
    return tl::make_unexpected(StringConvErr{StringConvErrCode::out_of_range});
  }

  template<>
  inline tl::expected<std::string_view, StringConvErr> from_string(std::string_view sv) noexcept
  {
    return sv;
  }

  template<>
  inline tl::expected<std::string, StringConvErr> from_string(std::string_view sv) noexcept
  {
    return std::string{sv};
  }

} // namespace otto::util
