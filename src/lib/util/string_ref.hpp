#pragma once

#include <string>
#include <string_view>
#include <iosfwd>
#include <iostream>

namespace otto::util {

  /// This class is a non owning reference to a null terminated string.
  struct string_ref {
    /// types
    using  const_iterator = const char*;
    using  const_reverse_iterator = std::reverse_iterator<const_iterator>;

    /// constants
    const static size_t npos;

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

    constexpr operator std::string_view() const noexcept {
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

    constexpr bool starts_with(string_ref x) const
    {
      return length_ >= x.length_ && substr(0, x.size()) == std::string_view(x);
    }

    constexpr bool ends_with(string_ref x) const
    {
      return length_ >= x.length_ && substr(length_ - x.size(), x.size()) == std::string_view(x);
    }

    constexpr size_t find(string_ref s) const
    {
      return std::string_view(*this).find(std::string_view(s));
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

  private:
    const char* data_;
    std::size_t length_;
  };

  inline std::ostream& operator<<(std::ostream& ostream, const string_ref& sr) {
    return ostream << sr.c_str();
  }

  /// Comparison operators
  constexpr bool operator==(string_ref x, string_ref y)
  {
    return x.compare(y) == 0;
  }
  constexpr bool operator!=(string_ref x, string_ref y)
  {
    return x.compare(y) != 0;
  }
  constexpr bool operator<(string_ref x, string_ref y)
  {
    return x.compare(y) < 0;
  }
  constexpr bool operator<=(string_ref x, string_ref y)
  {
    return x.compare(y) <= 0;
  }
  constexpr bool operator>(string_ref x, string_ref y)
  {
    return x.compare(y) > 0;
  }
  constexpr bool operator>=(string_ref x, string_ref y)
  {
    return x.compare(y) >= 0;
  }

} // namespace otto::util
