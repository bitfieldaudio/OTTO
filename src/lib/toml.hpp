#pragma once

#include <toml.hpp>
#include "lib/util/string_ref.hpp"

namespace otto::toml {

  using value = ::toml::basic_value<::toml::preserve_comments>;
  using table = value::table_type;
  using array = value::array_type;
  using namespace ::toml;

  struct TomlSerializable {
    virtual void to_toml(toml::value&) const = 0;
    virtual void from_toml(const toml::value&) = 0;
    toml::value into_toml() const
    {
      toml::value res;
      to_toml(res);
      return res;
    }
  };

  inline namespace literals {
    inline value operator"" _toml(const char* str, std::size_t len)
    {
      ::toml::detail::location<std::vector<char>> loc(
        /* filename = */ std::string("TOML literal encoded in a C++ code"),
        /* contents = */ std::vector<char>(str, str + len));

      // if there are some comments or empty lines, skip them.
      using skip_line = ::toml::detail::repeat<
        ::toml::detail::sequence<::toml::detail::maybe<::toml::detail::lex_ws>, ::toml::detail::lex_newline>,
        ::toml::detail::at_least<1>>;
      skip_line::invoke(loc);

      // if there are some whitespaces before a value, skip them.
      using skip_ws = ::toml::detail::repeat<::toml::detail::lex_ws, ::toml::detail::at_least<1>>;
      skip_ws::invoke(loc);

      // to distinguish arrays and tables, first check it is a table or not.
      //
      // "[1,2,3]"_toml;   // this is an array
      // "[table]"_toml;   // a table that has an empty table named "table" inside.
      // "[[1,2,3]]"_toml; // this is an array of arrays
      // "[[table]]"_toml; // this is a table that has an array of tables inside.
      //
      // "[[1]]"_toml;     // this can be both... (currently it becomes a table)
      // "1 = [{}]"_toml;  // this is a table that has an array of table named 1.
      // "[[1,]]"_toml;    // this is an array of arrays.
      // "[[1],]"_toml;    // this also.

      const auto the_front = loc.iter();

      const bool is_table_key = ::toml::detail::lex_std_table::invoke(loc);
      loc.reset(the_front);

      const bool is_aots_key = ::toml::detail::lex_array_table::invoke(loc);
      loc.reset(the_front);

      // If it is neither a table-key or a array-of-table-key, it may be a value.
      if (!is_table_key && !is_aots_key) {
        if (auto data = ::toml::detail::parse_value<value>(loc)) {
          return data.unwrap();
        }
      }

      // Note that still it can be a table, because the literal might be something
      // like the following.
      // ```cpp
      // R"( // c++11 raw string literals
      //   key = "value"
      //   int = 42
      // )"_toml;
      // ```
      // It is a valid toml file.
      // It should be parsed as if we parse a file with this content.

      if (auto data = ::toml::detail::parse_toml_file<value>(loc)) {
        return data.unwrap();
      } else // none of them.
      {
        throw syntax_error(data.unwrap_err(), source_location(std::addressof(loc)));
      }
    }

  } // namespace literals

  inline toml::value from_str(util::string_ref str)
  {
    return literals::operator""_toml(str.c_str(), str.size());
  }
} // namespace otto::toml

namespace toml {

  template<>
  struct into<std::filesystem::path> {
    static toml::string into_toml(const std::filesystem::path& v)
    {
      return toml::string(v.c_str());
    }
  };
} // namespace toml
