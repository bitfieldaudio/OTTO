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

    REQUIRE(lv.push_back(5).error() == LvInt::error::full);

    REQUIRE(vec(lv.begin(), lv.end()) == vec(0, 1, 2, 3, 4));

    auto pos = lv.begin() + 2;
    REQUIRE(lv.insert_before(pos, 10).error() == LvInt::error::full);
    REQUIRE_THROWS_AS(lv.insert(pos, 10), tl::bad_expected_access<LvInt::error>);

    REQUIRE(lv.pop_back().has_value());
    REQUIRE(lv.insert_before(pos, 10).value() == lv.begin() + 2);

    REQUIRE(vec(lv.begin(), lv.end()) == vec(0, 1, 10, 2, 3));

    lv.pop_back();

    REQUIRE(lv.insert_before(lv.end(), 11).value() == lv.begin() + 4);
    REQUIRE(vec(lv.begin(), lv.end()) == vec(0, 1, 10, 2, 11));
    lv.pop_back();
    REQUIRE(lv.insert_before(lv.begin(), 12).value() == lv.begin());
    REQUIRE(vec(lv.begin(), lv.end()) == vec(12, 0, 1, 10, 2));

    SUBCASE ("Erase") {
      using LvInt = local_vector<int, 10>;
      using namespace util::view;
      LvInt lv = {{0, 1, 2, 3, 4, 5, 6, 7, 8, 9}};
      REQUIRE(to_vec(lv) == vec(0, 1, 2, 3, 4, 5, 6 ,7 , 8, 9));

      SUBCASE("range-based (front)") {
        auto endp = lv.erase(lv.begin(), lv.begin() + 2);
        REQUIRE(to_vec(lv) == vec(2, 3, 4, 5, 6 ,7 , 8, 9));
        REQUIRE(*endp == 2);
      }

      SUBCASE("range-based (middle)") {
        auto endp = lv.erase(lv.begin() + 2, lv.begin() + 5);
        REQUIRE(to_vec(lv) == vec(0, 1, 5, 6 ,7 , 8, 9));
        REQUIRE(*endp == 5);
      }

      SUBCASE("range-based (end)") {
        auto endp = lv.erase(lv.begin() + 4, lv.end());
        REQUIRE(to_vec(lv) == vec(0, 1, 2, 3));
        REQUIRE(endp == lv.end());
      }

      SUBCASE("range-based (no-op)") {
        auto endp = lv.erase(lv.begin() + 4, lv.begin() + 4);
        REQUIRE(to_vec(lv) == vec(0, 1, 2, 3, 4, 5, 6, 7, 8, 9));
        REQUIRE(*endp == 4);
      }

      SUBCASE("Remove-Erase"){
        auto it = nano::remove_if(lv, [](int i) { return i%2 == 0; });
        auto endp = lv.erase(it, lv.end());
        REQUIRE(to_vec(lv) == vec(1, 3, 5, 7, 9));
      }

    }
  }

} // namespace otto::test
