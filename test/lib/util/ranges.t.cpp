#include "testing.t.hpp"

#include "lib/util/ranges.hpp"

using namespace otto;

TEST_CASE ("otto::util::zip") {
  std::vector ints = {1, 2, 3, 4, 5};
  std::vector<std::string> strings = {"1", "2", "3", "4", "5"};
  std::vector<int> no_ints = {};
  std::vector more_ints = {1, 2, 3, 4, 5, 6};

  SUBCASE ("util::zip_view basic") {
    std::vector<int> expi;
    std::vector<std::string> exps;
    for (auto [i, s] : util::zip_view(util::all(ints), util::all(strings))) {
      expi.push_back(i);
      exps.push_back(s);
    }
    REQUIRE(ints == expi);
    REQUIRE(strings == exps);
  }

  SUBCASE ("same length") {
    std::vector<int> expi;
    std::vector<std::string> exps;
    for (auto [i, s] : util::zip(ints, strings)) {
      expi.push_back(i);
      exps.push_back(s);
    }
    REQUIRE(ints == expi);
    REQUIRE(strings == exps);
  }

  SUBCASE ("different lengths") {
    std::vector<int> v1;
    std::vector<int> v2;
    for (auto [i1, i2] : util::zip(ints, more_ints)) {
      v1.push_back(i1);
      v2.push_back(i2);
    }
    REQUIRE(v1 == ints);
    REQUIRE(v2 == ints);
  }

  SUBCASE ("empty") {
    REQUIRE(util::zip(no_ints, strings, ints).empty());
  }
}
