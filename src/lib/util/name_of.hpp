#pragma once

#include <array>
#include <string_view>

#include "string_ref.hpp"

namespace otto::util {
  // name_of

  namespace detail {
    template<typename T>
    constexpr std::string_view qualified_name_of_impl()
    {
      std::string_view sv;
#if __clang__
      sv = __PRETTY_FUNCTION__;
      sv = sv.substr(sv.find_last_of('=') + 2);
      sv = sv.substr(0, sv.size() - 1);
#elif __GNUC__
      sv = __PRETTY_FUNCTION__;
      sv = sv.substr(sv.find_first_of('=') + 2);
      sv = sv.substr(0, sv.find_first_of(';'));
#else
#error "name_of not implemented on this platform"
#endif
      return sv;
    }

    template<typename T>
    constexpr auto qualified_name_of_buffer = [] {
      constexpr auto qual = qualified_name_of_impl<T>();
      std::array<char, qual.size() + 1> buffer = {0};
      std::copy(qual.begin(), qual.end(), buffer.begin());
      return buffer;
    }();

    template<typename T>
    constexpr auto name_of_impl()
    {
      constexpr auto qual = qualified_name_of_impl<T>();
      std::array<char, qual.size() + 1> buffer = {0};
      auto biter = buffer.begin();
      std::size_t last_word_start = 0;
      for (int i = 0; i < qual.size(); i++) {
        const auto c = qual[i];
        if (c == ':') last_word_start = i + 1;
        if (c == '<' || c == ',' || c == ' ') {
          biter = std::copy(qual.begin() + last_word_start, qual.begin() + i + 1, biter);
          last_word_start = i + 1;
        }
      }
      if (last_word_start < qual.size()) std::copy(qual.begin() + last_word_start, qual.end(), biter);
      return buffer;
    }

    template<typename T>
    constexpr auto name_of_buffer = name_of_impl<T>();
  } // namespace detail

  /// Compile time fully qualified name of a type.
  /// 
  /// Guarantees that `qualified_name_of<T> == qualified_name_of<U>` is equivalent
  /// to `T == U`, which also applies to `qualified_name_of.c_str()`. Hence, comparing
  /// the `const char*` is enough to determine equality of the types.
  template<typename T>
  constexpr string_ref qualified_name_of = detail::qualified_name_of_buffer<T>.data();

  /// Compile time name of a type with qualifiers removed.
  ///
  /// Also removes qualifiers of nested template parameters
  /// 
  /// Does not guarantee that `name_of<T> == name_of<U>` is equivalent to `T == U`,
  /// but comparing the pointers `name_of.c_str()` does. Hence, comparing
  /// the `const char*` is determines equality of the types.
  template<typename T>
  constexpr string_ref name_of = detail::name_of_buffer<T>.data();
} // namespace otto::util

namespace otto::test {

  struct TestType {};

  template<typename T, typename U>
  struct TestType2 {};

  static_assert(util::qualified_name_of<TestType> == "otto::test::TestType");
  static_assert(util::qualified_name_of<TestType2<TestType, int>> ==
                "otto::test::TestType2<otto::test::TestType, int>");
  static_assert(util::name_of<TestType> == "TestType");
  static_assert(util::name_of<TestType2<TestType, int>> == "TestType2<TestType, int>");
} // namespace otto::test
