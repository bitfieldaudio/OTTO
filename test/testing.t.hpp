#pragma once

// include before catch, because loguru undefines INFO
#include "lib/logging.hpp"

#define CATCH_CONFIG_ENABLE_ALL_STRINGMAKERS
#include <chrono>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <unordered_map>

#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_all.hpp>

#include "lib/util/algorithm.hpp"
#include "lib/util/name_of.hpp"
#include "lib/util/type_traits.hpp"
#include "lib/util/utility.hpp"

#include "fmt/core.h"
#include "fmt/ostream.h"
#include "magic_enum.hpp"

namespace fs = std::filesystem;

using namespace Catch::literals;

namespace otto::test {
  fs::path temp_file(std::string_view name);

  inline void truncateFile(const fs::path& p)
  {
    std::fstream fstream;
    fstream.open(p.c_str(), std::ios::trunc | std::ios::out | std::ios::binary);
    fstream.close();
  }

  struct measure {
    using TimeT = std::chrono::nanoseconds;

    template<typename F, typename... Args>
    static auto execution(F&& func, Args&&... args)
    {
      auto start = std::chrono::steady_clock::now();
      std::forward<decltype(func)>(func)(std::forward<Args>(args)...);
      return std::chrono::duration_cast<TimeT>(std::chrono::steady_clock::now() - start);
    }
  };

  inline auto float_cmp(float margin)
  {
    return [margin](float a, float b) { return std::abs(a - b) < margin; };
  }

  struct approx {
    approx(float v) noexcept : value_(v) {}

    approx& margin(float m) noexcept
    {
      margin_ = m;
      return *this;
    };

    bool operator==(float rhs) const noexcept
    {
      return std::abs(value_ - rhs) < margin_;
    }

    friend bool operator==(float lhs, const approx& rhs)
    {
      return (rhs == lhs);
    }

    bool operator!=(float rhs) const noexcept
    {
      return !(*this == rhs);
    }

    friend bool operator!=(float lhs, const approx& rhs)
    {
      return rhs != lhs;
    }

    friend std::ostream& operator<<(std::ostream& os, const approx& a)
    {
      os << a.value_ << "±" << a.margin_;
      return os;
    }

  private:
    float value_;
    float margin_ = 0.0001;
  };

  //  template<typename Cont, typename Proj>
  //  auto sort(Cont&& c, Proj&& projection)
  //  {
  //    auto vec = util::view::to_vec(c);
  //    nano::sort(vec, [&](auto&& a, auto&& b) { return projection(a) < projection(b); });
  //    return vec;
  //  }
  //
  //  template<typename Cont>
  //  auto sort(Cont&& c)
  //  {
  //    return test::sort(c, util::identity);
  //  }

} // namespace otto::test

namespace Catch {

  template<typename E>
  requires(std::is_enum_v<E>) //
    struct StringMaker<E> {
    static std::string convert(E const& value)
    {
      using namespace std::literals;
      std::string_view name = magic_enum::enum_name(value);
      if (name.data() != nullptr) return std::string(name);
      return fmt::format("{{index: {}}}", magic_enum::enum_integer(value));
    }
  };

} // namespace Catch
