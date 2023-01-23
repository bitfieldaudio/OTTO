#pragma once

#include <iosfwd>
#include <iostream>
#include <string>
#include <string_view>

namespace otto::util {

  /// This class is a non owning reference to a null terminated string.
  struct string_ref {
    /// types
    using const_iterator = const char*;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    /// constants
    const static size_t npos = std::string_view::npos;

    /// construct/copy.
    constexpr string_ref() : data_(""), length_(0) {}
    constexpr string_ref(const string_ref& other) : data_(other.data_), length_(other.length_) {}
    constexpr string_ref& operator=(const string_ref& rhs)
    {
      data_ = rhs.data_;
      return *this;
    }

    constexpr string_ref(const char* s) : data_(s), length_(0)
    {
      for (auto c = s; *c != '\0'; c++) length_++;
    }
    string_ref(const std::string& s) : data_(s.data()), length_(s.length()) {}

    constexpr operator std::string_view() const noexcept
    {
      return {data_, length_};
    }

    /// iterators
    constexpr const_iterator begin() const
    {
      return data_;
    }
    constexpr const_iterator end() const
    {
      return data_ + length_;
    }
    constexpr const_iterator cbegin() const
    {
      return data_;
    }
    constexpr const_iterator cend() const
    {
      return data_ + length_;
    }
    constexpr const_reverse_iterator rbegin() const
    {
      return const_reverse_iterator(end());
    }
    constexpr const_reverse_iterator rend() const
    {
      return const_reverse_iterator(begin());
    }
    constexpr const_reverse_iterator crbegin() const
    {
      return const_reverse_iterator(end());
    }
    constexpr const_reverse_iterator crend() const
    {
      return const_reverse_iterator(begin());
    }

    /// capacity
    constexpr size_t size() const
    {
      return length_;
    }
    constexpr size_t length() const
    {
      return length_;
    }
    constexpr size_t max_size() const
    {
      return length_;
    }
    constexpr bool empty() const
    {
      return length_ == 0;
    }

    /// element access
    constexpr const char* data() const
    {
      return data_;
    }

    /// string operations
    constexpr int compare(string_ref x) const
    {
      return std::string_view(*this).compare(std::string_view(x));
    }

    constexpr bool starts_with(std::string_view x) const
    {
      return length_ >= x.length() && substr(0, x.size()) == x;
    }

    constexpr bool ends_with(std::string_view x) const
    {
      return length_ >= x.length() && substr(length_ - x.size(), x.size()) == x;
    }

    constexpr size_t find(std::string_view s) const
    {
      return std::string_view(*this).find(s);
    }

    constexpr size_t find(char c) const
    {
      return std::string_view(*this).find(c);
    }

    constexpr std::string_view substr(size_t pos, size_t n = npos) const
    {
      return std::string_view(*this).substr(pos, n);
    }

    constexpr const char* c_str() const noexcept
    {
      return data_;
    }

    constexpr std::strong_ordering operator<=>(string_ref rhs) const noexcept
    {
      return std::string_view(*this) <=> std::string_view(rhs);
    }

    constexpr bool operator==(const string_ref& rhs) const noexcept
    {
      if (!std::is_constant_evaluated()) {
        // This pointer comparison is not allowed in a constant expression
        if (data_ == rhs.data_) return true;
      }
      return std::string_view(*this) == std::string_view(rhs);
    }

  private:
    const char* data_;
    std::size_t length_;
  };

  inline std::ostream& operator<<(std::ostream& ostream, string_ref sr)
  {
    return ostream << static_cast<std::string_view>(sr);
  }

} // namespace otto::util

namespace std {

  template<>
  struct hash<otto::util::string_ref> {
    std::size_t operator()(const otto::util::string_ref& sr) const
    {
      return std::hash<std::string_view>()(std::string_view(sr));
    }
  };
} // namespace std
