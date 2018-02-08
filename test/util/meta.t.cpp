#include "testing.t.hpp"

#include "util/meta.hpp"

namespace otto {

  using var = meta::list<int,
                          double,
                          meta::list<float, int>,
                          meta::list<meta::list<long, unsigned>, char>,
                          bool>;

  // meta::concat /////////////////////////////////////////////////////////////
  namespace test_concat {
    using tl1 = meta::list<int, bool, char>;
    using tl2 = meta::list<long, long, char>;
    using tl3 = meta::list<>;
    using tl4 = meta::list<bool>;

    OTTO_META_ASSERT_EQUAL(meta::_t<meta::concat<tl1, tl2>>, meta::list<int, bool, char, long, long, char>);
    OTTO_META_ASSERT_EQUAL(meta::_t<meta::concat<tl1, tl2, tl3>>, meta::list<int, bool, char, long, long, char>);
    OTTO_META_ASSERT_EQUAL(meta::_t<meta::concat<tl4, tl4, tl4>>, meta::list<bool, bool, bool>);

    OTTO_META_ASSERT_EQUAL(meta::_t<meta::concat<tl3>>, meta::list<>);
    OTTO_META_ASSERT_EQUAL(meta::_t<meta::concat<tl4>>, meta::list<bool>);
    OTTO_META_ASSERT_EQUAL(meta::_t<meta::concat<tl3, tl3>>, meta::list<>);
  }

  // meta::flatten ////////////////////////////////////////////////////////////
  namespace test_flatten {
    using flattened =
      meta::list<int, double, float, int, long, unsigned, char, bool>;
    OTTO_META_ASSERT_EQUAL(meta::_t<meta::flatten<var>>, flattened);

    // flatten<NonListType> == list<NonListType>
    OTTO_META_ASSERT_EQUAL(meta::_t<meta::flatten<int>>, meta::list<int>);

    // flatten<list<Args...>> == list<Args...>
    OTTO_META_ASSERT_EQUAL(
      meta::_t<meta::flatten<meta::list<float, char, int>>>,
      meta::list<float, char, int>);

    // flatten<list<>> == list<>
    OTTO_META_ASSERT_EQUAL(meta::_t<meta::flatten<meta::list<>>>,
                           meta::list<>);
  }

  // meta::contains ///////////////////////////////////////////////////////////
  namespace test_contains {
    static_assert(meta::_v<meta::contains<var, int>>);
    static_assert(meta::_v<meta::contains<var, bool>>);
    static_assert(!meta::_v<meta::contains<var, long>>);
    static_assert(meta::_v<meta::contains<var, meta::list<float, int>>>);

    static_assert(!meta::_v<meta::contains<meta::list<>, int>>);
  }

  // meta::uniquify ///////////////////////////////////////////////////////////
  namespace test_uniquify {
    using a_list = meta::list<int, double, float, int, char, double>;
    using expects = meta::list<float, int, char, double>;

    OTTO_META_ASSERT_EQUAL(meta::_t<meta::uniquify<a_list>>, expects);
  }

  // meta::sort ///////////////////////////////////////////////////////////////

  template<int... vals>
  using c_list = meta::list<meta::c<vals>...>;

  namespace test_sort {

    template<int... vals>
    using sorted = meta::_t<meta::sort<c_list<vals...>>>;

    OTTO_META_ASSERT_EQUAL(sorted<4, 2, 5, 7, 1, 3, 6>,
                           c_list<1, 2, 3, 4, 5, 6, 7>);

    OTTO_META_ASSERT_EQUAL(sorted<1, 1, 1, 1, 1>, c_list<1, 1, 1, 1, 1>);
    OTTO_META_ASSERT_EQUAL(sorted<1>, c_list<1>);
    OTTO_META_ASSERT_EQUAL(sorted<>, c_list<>);
  }

  // meta::for_each ///////////////////////////////////////////////////////////

  TEST_CASE("meta::for_each", "[util], [meta]")
  {
    std::vector<int> values;

    SECTION("With values")
    {
      meta::for_each<c_list<1, 2, 3, 4, 5>>(
        [&values](auto type) { values.push_back(meta::_tv<decltype(type)>); });

      REQUIRE_THAT(values, Catch::Matchers::Equals(std::vector{1, 2, 3, 4, 5}));
    }

    SECTION("Empty list")
    {
      meta::for_each<c_list<>>(
        [&values](auto type) { values.push_back(meta::_tv<decltype(type)>); });

      REQUIRE_THAT(values, Catch::Matchers::Equals(std::vector<int>{}));
    }

    SECTION("One item")
    {
      meta::for_each<c_list<100>>(
        [&values](auto type) { values.push_back(meta::_tv<decltype(type)>); });

      REQUIRE_THAT(values, Catch::Matchers::Equals(std::vector<int>{100}));
    }
  }

  // meta::transform_to_tuple /////////////////////////////////////////////////

  TEST_CASE("meta::transform_to_tuple", "[util], [meta]")
  {
    auto res = meta::transform_to_tuple<c_list<1, 2, 3, 4, 5>>([](auto type) {
      constexpr int val = meta::_tv<decltype(type)>;
      if constexpr (val % 2 == 0) {
        return int(val);
      } else {
        return float(val) / 2.f;
      }
    });

    REQUIRE(std::get<0>(res) == 0.5f);
    REQUIRE(std::get<1>(res) == 2);
    REQUIRE(std::get<2>(res) == 1.5f);
    REQUIRE(std::get<3>(res) == 4);
    REQUIRE(std::get<4>(res) == 2.5f);
  }

} // namespace otto
