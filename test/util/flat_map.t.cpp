#include <type_traits>

#include "testing.t.hpp"
#include "util/flat_map.hpp"
#include "util/string_conversions.hpp"

namespace otto::test {

  using namespace util::view;
  // Used to test transparent comparisons
  struct StringLikeType {
    StringLikeType(std::string s) : s(s) {}
    StringLikeType(const StringLikeType&) = delete;

    std::string s;

    friend bool operator==(const StringLikeType& l, const std::string& r)
    {
      return l.s == r;
    }

    friend bool operator==(const std::string& l, const StringLikeType& r)
    {
      return l == r.s;
    }
  };

  TEST_CASE ("util::flat_map") {
    using StringIntMap = util::flat_map<std::string, int>;

    static_assert(std::is_same_v<StringIntMap::key_type, std::string>);
    static_assert(std::is_same_v<StringIntMap::mapped_type, int>);
    static_assert(std::is_same_v<StringIntMap::value_type, std::pair<std::string, int>>);

    StringIntMap map;

    SECTION ("Upon construction, size() is zero") {
      REQUIRE(map.size() == 0);
    }

    SECTION ("Insertion of element increases size") {
      auto res = map.insert("test", 5);
      REQUIRE(res == std::pair(map.begin(), true));
      REQUIRE(map.size() == 1);
    }

    SECTION ("Inserting existing element returns iterator to that and false") {
      auto res = map.insert("test", 5);
      REQUIRE(res == std::pair(map.begin(), true));
      res = map.insert("test", 5);
      REQUIRE(res == std::pair(map.begin(), false));
    }

    map.insert("0", 0);
    map.insert("1", 1);
    map.insert("2", 2);
    map.insert("3", 3);
    map.insert("4", 4);

    const auto& cmap = map;

    SECTION ("Iteration") {
      int i = 0;
      for (auto&& [k, v] : map) {
        REQUIRE(k == util::to_string(i));
        REQUIRE(v == i);
        i++;
      }
      REQUIRE(i == 5);
    }

    SECTION ("Lookup of existing value") {
      REQUIRE(map["0"] == 0);
      REQUIRE(map["2"] == 2);
      REQUIRE(map["4"] == 4);
    }

    SECTION ("Lookup of nonexistant value returns nullopt") {
      REQUIRE(map["10"] == tl::nullopt);
    }

    SECTION ("find existing value") {
      REQUIRE(map.find("0") == map.begin());
      REQUIRE(map.find("2") == map.begin() + 2);
      REQUIRE(map.find("4") == map.begin() + 4);
      REQUIRE(cmap.find("0") == cmap.begin());
      REQUIRE(cmap.find("2") == cmap.begin() + 2);
      REQUIRE(cmap.find("4") == cmap.begin() + 4);
    }

    SECTION ("find nonexistant value") {
      REQUIRE(map.find("nope") == map.end());
      REQUIRE(cmap.find("nope") == cmap.end());
    }

    SECTION ("Erase by key") {
      REQUIRE(map.erase("2") == true);
      REQUIRE_THAT(to_vec(map),
                   Catch::Equals(std::vector<StringIntMap::value_type>{{"0", 0}, {"1", 1}, {"3", 3}, {"4", 4}}));
    }

    SECTION ("Erase by nonexistant key") {
      REQUIRE(map.erase("nope") == false);
      REQUIRE_THAT(to_vec(map), Catch::Equals(std::vector<StringIntMap::value_type>{
                                  {"0", 0}, {"1", 1}, {"2", 2}, {"3", 3}, {"4", 4}}));
    }

    SECTION ("Erase by single iterator") {
      SECTION ("first element") {
        auto erase_result = map.erase(map.begin());
        REQUIRE(erase_result == map.begin());
        REQUIRE_THAT(to_vec(map),
                     Catch::Equals(std::vector<StringIntMap::value_type>{{"1", 1}, {"2", 2}, {"3", 3}, {"4", 4}}));
      }
      SECTION ("middle element") {
        auto erase_result = map.erase(map.begin() + 2);
        REQUIRE(erase_result == map.begin() + 2);
        REQUIRE_THAT(to_vec(map),
                     Catch::Equals(std::vector<StringIntMap::value_type>{{"0", 0}, {"1", 1}, {"3", 3}, {"4", 4}}));
      }
      SECTION ("last element") {
        auto erase_result = map.erase(map.begin() + 4);
        REQUIRE(erase_result == map.begin() + 4);
        REQUIRE_THAT(to_vec(map),
                     Catch::Equals(std::vector<StringIntMap::value_type>{{"0", 0}, {"1", 1}, {"2", 2}, {"3", 3}}));
      }
    }

    SECTION ("Transparent comparisons") {
      StringLikeType key = {"2"};
      SECTION( "find") {
        REQUIRE(map.find(key) == map.begin() + 2);
      }
      SECTION( "contains") {
        REQUIRE(map.contains(key));
      }
      SECTION( "erase") {
        REQUIRE(map.erase(key));
        REQUIRE_THAT(to_vec(map),
                     Catch::Equals(std::vector<StringIntMap::value_type>{{"0", 0}, {"1", 1}, {"3", 3}, {"4", 4}}));
      }
    }
  }

} // namespace otto::test
