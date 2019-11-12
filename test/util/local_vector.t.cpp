#include "testing.t.hpp"

#include "util/local_vector.hpp"

namespace otto::test {

  using util::local_vector;

  template<typename... Args>
  std::vector<int> vec(Args&&... args)
  {
    return {FWD(args)...};
  }

  TEST_CASE ("local_vector") {
    using LvInt = local_vector<int, 5>;
    LvInt lv;

    REQUIRE(lv.empty());

    REQUIRE(lv.push_back(0).value() == &lv.front());
    REQUIRE(lv.size() == 1);
    REQUIRE(&lv.front() == &lv.back());

    auto v = lv.push_back(1).value();
    REQUIRE(v == &lv.back());
    v = lv.push_back(2).value();
    REQUIRE(v == &lv.back());
    v = lv.push_back(3).value();
    REQUIRE(v == &lv.back());
    v = lv.push_back(4).value();
    REQUIRE(v == &lv.back());

    REQUIRE(lv.size() == 5);

    REQUIRE_NOTHROW(lv.push_back(5).error() == LvInt::error::full);

    REQUIRE(vec(lv.begin(), lv.end()) == vec(0, 1, 2, 3, 4));

    auto pos = lv.begin() + 2;
    REQUIRE_NOTHROW(lv.insert_before(pos, 10).error() == LvInt::error::full);
    REQUIRE_THROWS(lv.insert(pos, 10), tl::bad_expected_access(LvInt::error::full));

    REQUIRE(lv.pop_back().has_value());
    REQUIRE_NOTHROW(lv.insert_before(pos, 10).value() == lv.begin() + 2);

    REQUIRE(vec(lv.begin(), lv.end()) == vec(0, 1, 10, 2, 3));

    lv.pop_back();

    REQUIRE_NOTHROW(lv.insert_before(lv.end(), 11).value() == lv.begin() + 4);
    REQUIRE(vec(lv.begin(), lv.end()) == vec(0, 1, 10, 2, 11));
    lv.pop_back();
    REQUIRE_NOTHROW(lv.insert_before(lv.begin(), 12).value() == lv.begin());
    REQUIRE(vec(lv.begin(), lv.end()) == vec(12, 0, 1, 10, 2));

    SECTION ("Erase") {
      using LvInt = local_vector<int, 10>;
      using namespace util::view;
      LvInt lv = {{0, 1, 2, 3, 4, 5, 6, 7, 8, 9}};
      REQUIRE_THAT(to_vec(lv), Catch::Equals(vec(0, 1, 2, 3, 4, 5, 6 ,7 , 8, 9)));

      SECTION("range-based (front)") {
        auto endp = lv.erase(lv.begin(), lv.begin() + 2);
        REQUIRE_THAT(to_vec(lv), Catch::Equals(vec(2, 3, 4, 5, 6 ,7 , 8, 9)));
        REQUIRE(*endp == 2);
      }

      SECTION("range-based (middle)") {
        auto endp = lv.erase(lv.begin() + 2, lv.begin() + 5);
        REQUIRE_THAT(to_vec(lv), Catch::Equals(vec(0, 1, 5, 6 ,7 , 8, 9)));
        REQUIRE(*endp == 5);
      }

      SECTION("range-based (end)") {
        auto endp = lv.erase(lv.begin() + 4, lv.end());
        REQUIRE_THAT(to_vec(lv), Catch::Equals(vec(0, 1, 2, 3)));
        REQUIRE(endp == lv.end());
      }

      SECTION("range-based (no-op)") {
        auto endp = lv.erase(lv.begin() + 4, lv.begin() + 4);
        REQUIRE_THAT(to_vec(lv), Catch::Equals(vec(0, 1, 2, 3, 4, 5, 6, 7, 8, 9)));
        REQUIRE(*endp == 4);
      }

      SECTION("Remove-Erase"){
        auto it = util::remove_if(lv, [](int i) { return i%2 == 0; });
        auto endp = lv.erase(it, lv.end());
        REQUIRE_THAT(to_vec(lv), Catch::Equals(vec(1, 3, 5, 7, 9)));
      }

    }
  }

} // namespace otto::test
