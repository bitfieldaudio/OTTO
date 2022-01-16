#pragma once

#include <array>
#include <bitset>

#include <magic_enum.hpp>
#include <nlohmann/json.hpp>
#include <tl/optional.hpp>

#include "lib/util/concepts.hpp"
#include "lib/util/ranges/zip_view.hpp"

namespace otto::util {

  using namespace magic_enum;

  template<AnEnum E, std::predicate<char, char> BP>
  [[nodiscard]] constexpr tl::optional<E> enum_cast(std::string_view value, BP p)
  {
    auto opt = magic_enum::enum_cast<E>(value, p);
    if (opt.has_value()) return opt.value();
    return tl::nullopt;
  }

  template<AnEnum E>
  [[nodiscard]] constexpr tl::optional<E> enum_cast(std::string_view value) noexcept
  {
    auto opt = magic_enum::enum_cast<E>(value);
    if (opt.has_value()) return opt.value();
    return tl::nullopt;
  }

  template<AnEnum E>
  [[nodiscard]] constexpr tl::optional<E> enum_cast(magic_enum::underlying_type_t<E> value) noexcept
  {
    auto opt = magic_enum::enum_cast<E>(value);
    if (opt.has_value()) return opt.value();
    return tl::nullopt;
  }

  template<AnEnum E>
  [[nodiscard]] constexpr tl::optional<std::size_t> enum_index(E value) noexcept
  {
    auto opt = magic_enum::enum_index(value);
    if (opt.has_value()) return opt.value();
    return tl::nullopt;
  }

  template<AnEnum Enum, std::semiregular T>
  struct enum_map {
    using value_type = T;
    using iterator = typename std::array<T, enum_count<Enum>()>::iterator;
    using const_iterator = typename std::array<T, enum_count<Enum>()>::const_iterator;

    constexpr enum_map() = default;
    constexpr enum_map(std::initializer_list<std::pair<Enum, T>> init) noexcept(std::is_nothrow_assignable_v<T, T>)
    {
      for (auto&& [k, v] : init) {
        (*this)[k] = v;
      }
    }

    static constexpr std::size_t size() noexcept
    {
      return enum_count<Enum>();
    }

    constexpr auto begin() noexcept
    {
      return view().begin();
    }

    constexpr auto begin() const noexcept
    {
      return view().begin();
    }

    constexpr auto end() noexcept
    {
      return view().end();
    }

    constexpr auto end() const noexcept
    {
      return view().end();
    }

    constexpr value_type& front() noexcept
    {
      return data_.front();
    }

    constexpr const value_type& front() const noexcept
    {
      return data_.front();
    }

    constexpr value_type& back() noexcept
    {
      return data_.back();
    }

    constexpr const value_type& back() const noexcept
    {
      return data_.back();
    }

    constexpr value_type& operator[](Enum e) noexcept
    {
      return data_[enum_index(e).value()];
    }

    constexpr const value_type& operator[](Enum e) const noexcept
    {
      return data_[enum_index(e).value()];
    }

    constexpr value_type& at(Enum e)
    {
      return data_.at(enum_index(e).value());
    }

    constexpr const value_type& at(Enum e) const
    {
      return data_.at(enum_index(e).value());
    }

    constexpr value_type* data() noexcept
    {
      return data_.data();
    }

    constexpr const value_type* data() const noexcept
    {
      return data_.data();
    }

    constexpr void fill(value_type v)
    {
      data_.fill(v);
    }

  private:
    auto view()
    {
      return util::zip(enum_values<Enum>(), data_);
    }
    auto view() const
    {
      return util::zip(enum_values<Enum>(), data_);
    }
    std::array<T, enum_count<Enum>()> data_ = {};
  };

  template<AnEnum Enum>
  struct enum_bitset {
    enum_bitset() noexcept = default;
    enum_bitset(const std::bitset<enum_count<Enum>()>& bs) noexcept : data_(bs) {}
    // NOLINTNEXTLINE
    enum_bitset(util::range_of<Enum> auto&& init) noexcept
    {
      for (Enum e : init) set(e);
    }
    enum_bitset(std::initializer_list<Enum> init) noexcept
    {
      for (Enum e : init) set(e);
    }

    static enum_bitset make_with_all(bool v = true) noexcept
    {
      enum_bitset res;
      if (v) {
        res.set();
      } else {
        res.reset();
      }
      return res;
    }

    static std::size_t size() noexcept
    {
      return enum_count<Enum>();
    }

    auto operator[](Enum e) noexcept
    {
      return data_[enum_index(e).value()];
    }

    bool operator[](Enum e) const noexcept
    {
      return data_[enum_index(e).value()];
    }

    auto at(Enum e) noexcept
    {
      return data_.at(enum_index(e).value());
    }

    bool at(Enum e) const noexcept
    {
      return data_.at(enum_index(e).value());
    }

    void flip(Enum e) noexcept
    {
      data_.flip(enum_index(e).value());
    }

    void set(Enum e, bool v = true) noexcept
    {
      data_.set(enum_index(e).value(), v);
    }

    void reset(Enum e) noexcept
    {
      data_.set(enum_index(e).value(), false);
    }

    void set() noexcept
    {
      data_.set();
    }

    void reset() noexcept
    {
      data_.reset();
    }

    bool test(Enum e) const noexcept
    {
      return data_.test(enum_index(e).value());
    }

    [[nodiscard]] bool all() const noexcept
    {
      return data_.all();
    }

    [[nodiscard]] bool any() const noexcept
    {
      return data_.any();
    }

    [[nodiscard]] bool none() const noexcept
    {
      return data_.none();
    }

    [[nodiscard]] std::size_t count() const noexcept
    {
      return data_.count();
    }

    enum_bitset& operator+=(Enum e) noexcept
    {
      set(e);
      return *this;
    }

    enum_bitset& operator-=(Enum e) noexcept
    {
      reset(e);
      return *this;
    }

    enum_bitset& operator&=(const enum_bitset& rhs) noexcept
    {
      data_ &= rhs.data_;
      return *this;
    }

    enum_bitset& operator|=(const enum_bitset& rhs) noexcept
    {
      data_ |= rhs.data_;
      return *this;
    }

    enum_bitset& operator^=(const enum_bitset& rhs) noexcept
    {
      data_ ^= rhs.data_;
      return *this;
    }

    enum_bitset operator~() const noexcept
    {
      return ~data_;
    }

    friend enum_bitset operator+(const enum_bitset& lhs, Enum e) noexcept
    {
      auto res = lhs;
      res += e;
      return res;
    }

    friend enum_bitset operator-(const enum_bitset& lhs, Enum e) noexcept
    {
      auto res = lhs;
      res -= e;
      return res;
    }

    friend enum_bitset operator&(const enum_bitset& lhs, const enum_bitset& rhs) noexcept
    {
      auto res = lhs;
      res &= rhs;
      return res;
    }

    friend enum_bitset operator|(const enum_bitset& lhs, const enum_bitset& rhs) noexcept
    {
      auto res = lhs;
      res |= rhs;
      return res;
    }

    friend enum_bitset operator^(const enum_bitset& lhs, const enum_bitset& rhs) noexcept
    {
      auto res = lhs;
      res ^= rhs;
      return res;
    }

    friend std::ostream& operator<<(std::ostream& os, const enum_bitset& bs) noexcept
    {
      return os << bs.data_;
    }

    friend std::istream& operator>>(std::istream& is, enum_bitset& bs) noexcept
    {
      return is >> bs.data_;
    }

    auto operator<=>(const enum_bitset&) const noexcept = default;
    bool operator==(const enum_bitset&) const noexcept = default;

  private:
    std::bitset<enum_count<Enum>()> data_ = {};
  };

} // namespace otto::util
