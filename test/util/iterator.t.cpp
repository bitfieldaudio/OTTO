#include "testing.t.hpp"

#include <array>

#include "util/iterator.hpp"

namespace otto::util {

  TEST_CASE("Float step iterator: Different Speeds through big array", "[iterator] [util]") {

    constexpr std::size_t someSize = 10;
    std::array<int, someSize> iterData;
    std::generate(std::begin(iterData), std::end(iterData),
      [n = -someSize/2] () mutable { return n++;});

    SECTION("Step = 1") {

      auto first = float_step(std::begin(iterData), 1);
      auto last = float_step(std::end(iterData), 1);

      REQUIRE(last - first == iterData.size());
      REQUIRE(std::equal(std::begin(iterData), std::end(iterData), first, last));
    }

    SECTION("Step = -1") {

      auto first = float_step(std::end(iterData)-1, -1);
      auto last = float_step(std::begin(iterData)-1, -1);

      std::vector<int> expected;
      std::reverse_copy(std::begin(iterData), std::end(iterData),
        std::back_inserter(expected));

      std::vector<int> actual;
      std::copy_n(first, expected.size(), std::back_inserter(actual));

      REQUIRE(last - first == expected.size());
      REQUIRE_THAT(actual, Catch::Matchers::Equals(expected));
    }

    SECTION("Step = 0.5") {

      auto first = float_step(std::begin(iterData), 0.5);

      std::vector<int> expected;
      for (size_t i = 0; i < std::size_t(someSize/0.5); i++) {
        expected.push_back(iterData.at(i * 0.5));
      }

      std::vector<int> actual;
      std::copy_n(first, expected.size(), std::back_inserter(actual));
      REQUIRE_THAT(actual, Catch::Matchers::Equals(expected));
    }

    SECTION("Step = -0.5") {

      auto first = float_step(std::end(iterData)-1, -0.5);

      std::vector<int> expected;
      for (int i = 0; i < int((someSize - 1) / 0.5); i++) {
        expected.push_back(iterData.at(someSize - 1 - i * 0.5));
      }

      std::vector<int> actual;
      std::copy_n(first, expected.size(), std::back_inserter(actual));
      REQUIRE_THAT(actual, Catch::Matchers::Equals(expected));
    }

    SECTION("Step = 1.5") {

      auto first = float_step(std::begin(iterData), 1.5);

      std::vector<int> expected;
      for (size_t i = 0; i < std::size_t(someSize/1.5); i++) {
        expected.push_back(iterData.at(i * 1.5));
      }

      std::vector<int> actual;
      std::copy_n(first, expected.size(), std::back_inserter(actual));
      REQUIRE_THAT(actual, Catch::Matchers::Equals(expected));
    }

    SECTION("Step = -1.5") {

      auto first = float_step(std::end(iterData)-1, -1.5);

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

    std::array<int, 11> data {{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10}};

    SECTION("Step = 1") {

      auto first = float_step(std::begin(data), 1);

      std::vector expected {0, 1, 2, 3, 2, 1, 2};
      std::vector<int> actual;
      actual.push_back(*first);   // 0
      actual.push_back(*++first); // 1
      actual.push_back(*++first); // 2
      actual.push_back(*++first); // 3
      actual.push_back(*--first); // 2
      actual.push_back(*--first); // 1
      actual.push_back(*++first); // 2

      REQUIRE_THAT(expected, Catch::Matchers::Equals(actual));
    }

    SECTION("Step = -1") {

      auto first = float_step(std::end(data) -1, -1);

      std::vector expected {10, 9, 8, 7, 8, 9, 8};
      std::vector<int> actual;
      actual.push_back(*first);   // 10
      actual.push_back(*++first); // 9
      actual.push_back(*++first); // 8
      actual.push_back(*++first); // 7
      actual.push_back(*--first); // 8
      actual.push_back(*--first); // 9
      actual.push_back(*++first); // 8

      REQUIRE_THAT(expected, Catch::Matchers::Equals(actual));
    }

    SECTION("Step = 0.5") {

      auto first = float_step(std::begin(data), 0.5);

      std::vector expected {0, 0, 1, 1, 1, 0, 1};
      std::vector<int> actual;
      actual.push_back(*first);   // 0
      actual.push_back(*++first); // 0.5
      actual.push_back(*++first); // 1
      actual.push_back(*++first); // 1.5
      actual.push_back(*--first); // 1
      actual.push_back(*--first); // 0.5
      actual.push_back(*++first); // 1

      REQUIRE_THAT(expected, Catch::Matchers::Equals(actual));
    }

    SECTION("Step = -0.5") {

      auto first = float_step(std::end(data)-1, -0.5);

      std::vector expected {10, 9, 9, 8, 9, 9, 9};
      std::vector<int> actual;
      actual.push_back(*first);   // 10
      actual.push_back(*++first); // 9.5
      actual.push_back(*++first); // 9
      actual.push_back(*++first); // 8.5
      actual.push_back(*--first); // 9
      actual.push_back(*--first); // 9.5
      actual.push_back(*++first); // 9

      REQUIRE_THAT(expected, Catch::Matchers::Equals(actual));
    }
  }

  TEST_CASE("Zipping iterators", "[iterator] [util]") {

    std::size_t some_size = 1000;

    SECTION("Referencing") {

      std::vector<int> data;
      data.reserve(some_size);
      std::generate_n(std::back_inserter(data), some_size, [] {return Random::get<int>(); });

      std::vector<int> new_data;
      new_data.reserve(some_size);
      std::generate_n(std::back_inserter(new_data), some_size, [] {return Random::get<int>(); });

      for (auto&& [dst, src] : util::zip(data, new_data)) {
        dst = src;
      }

      REQUIRE_THAT(data, Catch::Matchers::Equals(new_data));
    }
  }

  TEST_CASE("Adjacent Pair itereators", "[iterator] [util]") {

    std::size_t some_size = 1000;

    SECTION("Adjacent Pairs") {

      std::vector<int> data {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

      std::vector<int> expected {
        1, 2,
        2, 3,
        3, 4,
        4, 5,
        5, 6,
        6, 7,
        7, 8,
        8, 9,
        9, 10
      };

      std::vector<int> actual;

      for (auto pair : util::adjacent_pairs(data)) {
        static_assert(std::is_same_v<std::decay_t<decltype(pair)>, std::pair<int&, int&>>);
        actual.push_back(pair.first);
        actual.push_back(pair.second);
      }

      REQUIRE_THAT(actual, Catch::Matchers::Equals(expected));
    }

    SECTION("data.size() == 0") {

      std::vector<int> data {};

      bool flag = true;
      for (const auto& pair : util::adjacent_pairs(data)) {
        flag = false;
      }

      REQUIRE(flag);
    }

    SECTION("data.size() == 1") {

      std::vector<int> data {1};

      bool flag = true;
      for (const auto& pair : util::adjacent_pairs(data)) {
        flag = false;
      }

      REQUIRE(flag);
    }
  }

  TEST_CASE("Circular iterator", "[iterator] [util]") {
    std::vector<int> data = {1, 2, 3};

    auto circ = view::circular(data);
    auto iter = circ.begin();

    SECTION("basics") {
      REQUIRE(*iter == 1);
      REQUIRE(*++iter == 2);
      REQUIRE(*++iter == 3);
      REQUIRE(*++iter == 1);
      REQUIRE(*++iter == 2);
      REQUIRE(*--iter == 1);
      REQUIRE(*--iter == 3);
      REQUIRE(*--iter == 2);
      REQUIRE(*--iter == 1);

      std::advance(iter, 2);
      REQUIRE(*iter == 3);
      std::advance(iter, -2);
      REQUIRE(*iter == 1);
      std::advance(iter, -2);
      REQUIRE(*iter == 2);
    }
  }
}
