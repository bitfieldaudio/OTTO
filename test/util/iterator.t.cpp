#include "testing.t.hpp"

#include "util/iterator.hpp"

namespace top1 {

  TEST_CASE("Float step iterator: Different Speeds through big array", "[iterator] [util]") {

    constexpr std::size_t someSize = 10;
    std::array<int, someSize> iterData;
    std::generate(std::begin(iterData), std::end(iterData),
      [n = -someSize/2] () mutable { return n++;});

    SECTION("Step = 1") {

      auto first = float_step_iterator(std::begin(iterData), 1);
      auto last = float_step_iterator(std::end(iterData), 1);

      REQUIRE(std::equal(std::begin(iterData), std::end(iterData), first, last));
    }

    SECTION("Step = -1") {

      auto first = float_step_iterator(std::end(iterData)-1, -1);
      auto last = float_step_iterator(std::begin(iterData)-1, -1);

      REQUIRE(std::equal(std::rbegin(iterData), std::rend(iterData), first, last));
    }

    SECTION("Step = 0.5") {

      auto first = float_step_iterator(std::begin(iterData), 0.5);

      std::vector<int> expected;
      for (int i = 0; i < std::size_t(someSize/0.5); i++) {
        expected.push_back(iterData.at(i * 0.5));
      }

      std::vector<int> actual;
      std::copy_n(first, expected.size(), std::back_inserter(actual));
      REQUIRE_THAT(actual, Catch::Matchers::Equals(expected));
    }

    SECTION("Step = -0.5") {

      auto first = float_step_iterator(std::end(iterData)-1, -0.5);

      std::vector<int> expected;
      for (int i = 0; i < int((someSize - 1) / 0.5); i++) {
        expected.push_back(iterData.at(someSize - 1 - i * 0.5));
      }

      std::vector<int> actual;
      std::copy_n(first, expected.size(), std::back_inserter(actual));
      REQUIRE_THAT(actual, Catch::Matchers::Equals(expected));
    }

    SECTION("Step = 1.5") {

      auto first = float_step_iterator(std::begin(iterData), 1.5);

      std::vector<int> expected;
      for (int i = 0; i < std::size_t(someSize/1.5); i++) {
        expected.push_back(iterData.at(i * 1.5));
      }

      std::vector<int> actual;
      std::copy_n(first, expected.size(), std::back_inserter(actual));
      REQUIRE_THAT(actual, Catch::Matchers::Equals(expected));
    }

    SECTION("Step = -1.5") {

      auto first = float_step_iterator(std::end(iterData)-1, -1.5);

      std::vector<int> expected;
      for (int i = 0; i < int((someSize - 1) / 1.5); i++) {
        expected.push_back(iterData.at(someSize - 1 - i * 1.5));
      }

      std::vector<int> actual;
      std::copy_n(first, expected.size(), std::back_inserter(actual));
      REQUIRE_THAT(actual, Catch::Matchers::Equals(expected));
    }
  }

  TEST_CASE("Float step iterator: Going back and forth", "[iterator] [util]") {

    std::array data {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    SECTION("Step = 1") {

      auto first = float_step_iterator(std::begin(data), 1);

      std::vector expected {0, 1, 2, 3, 2, 1, 2};
      std::vector<int> actual;
      actual.push_back(*first);   // 0
      actual.push_back(*first++); // 1
      actual.push_back(*first++); // 2
      actual.push_back(*first++); // 3
      actual.push_back(*first--); // 2
      actual.push_back(*first--); // 1
      actual.push_back(*first++); // 2

      REQUIRE_THAT(expected, Catch::Matchers::Equals(actual));
    }

    SECTION("Step = -1") {

      auto first = float_step_iterator(std::end(data) -1, -1);

      std::vector expected {10, 9, 8, 7, 8, 9, 8};
      std::vector<int> actual;
      actual.push_back(*first);   // 10
      actual.push_back(*first++); // 9
      actual.push_back(*first++); // 8
      actual.push_back(*first++); // 7
      actual.push_back(*first--); // 8
      actual.push_back(*first--); // 9
      actual.push_back(*first++); // 8

      REQUIRE_THAT(expected, Catch::Matchers::Equals(actual));
    }

    SECTION("Step = 0.5") {

      auto first = float_step_iterator(std::begin(data), 0.5);

      std::vector expected {0, 0, 1, 1, 1, 0, 1};
      std::vector<int> actual;
      actual.push_back(*first);   // 0
      actual.push_back(*first++); // 0.5
      actual.push_back(*first++); // 1
      actual.push_back(*first++); // 1.5
      actual.push_back(*first--); // 1
      actual.push_back(*first--); // 0.5
      actual.push_back(*first++); // 1

      REQUIRE_THAT(expected, Catch::Matchers::Equals(actual));
    }

    SECTION("Step = -0.5") {

      auto first = float_step_iterator(std::end(data)-1, -0.5);

      std::vector expected {10, 9, 9, 8, 9, 9, 9};
      std::vector<int> actual;
      actual.push_back(*first);   // 10
      actual.push_back(*first++); // 9.5
      actual.push_back(*first++); // 9
      actual.push_back(*first++); // 8.5
      actual.push_back(*first--); // 9
      actual.push_back(*first--); // 9.5
      actual.push_back(*first++); // 9

      REQUIRE_THAT(expected, Catch::Matchers::Equals(actual));
    }
  }

}
