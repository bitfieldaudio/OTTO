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
  }

} // namespace otto::test
