#include <array>

#include "testing.t.hpp"
#include "util/iterator.hpp"

namespace otto::util {

  TEST_CASE ("[iterator] [util] Float step iterator: Different Speeds through big array") {
    constexpr std::size_t someSize = 10;
    std::array<int, someSize> iterData;
    std::generate(std::begin(iterData), std::end(iterData), [n = -someSize / 2]() mutable { return n++; });

    SUBCASE ("Step = 1") {
      auto first = float_step(std::begin(iterData), 1);
      auto last = float_step(std::end(iterData), 1);

      REQUIRE(last - first == iterData.size());
      REQUIRE(std::equal(std::begin(iterData), std::end(iterData), first, last));
    }

    SUBCASE ("Step = -1") {
      auto first = float_step(std::end(iterData) - 1, -1);
      auto last = float_step(std::begin(iterData) - 1, -1);

      std::vector<int> expected;
      std::reverse_copy(std::begin(iterData), std::end(iterData), std::back_inserter(expected));

      std::vector<int> actual;
      std::copy_n(first, expected.size(), std::back_inserter(actual));

      REQUIRE(last - first == expected.size());
      REQUIRE(actual == expected);
    }

    SUBCASE ("Step = 0.5") {
      auto first = float_step(std::begin(iterData), 0.5);

      std::vector<int> expected;
      for (size_t i = 0; i < std::size_t(someSize / 0.5); i++) {
        expected.push_back(iterData.at(i * 0.5));
      }

      std::vector<int> actual;
      std::copy_n(first, expected.size(), std::back_inserter(actual));
      REQUIRE(actual == expected);
    }

    SUBCASE ("Step = -0.5") {
      auto first = float_step(std::end(iterData) - 1, -0.5);

      std::vector<int> expected;
      for (int i = 0; i < int((someSize - 1) / 0.5); i++) {
        expected.push_back(iterData.at(someSize - 1 - i * 0.5));
      }

      std::vector<int> actual;
      std::copy_n(first, expected.size(), std::back_inserter(actual));
      REQUIRE(actual == expected);
    }

    SUBCASE ("Step = 1.5") {
      auto first = float_step(std::begin(iterData), 1.5);

      std::vector<int> expected;
      for (size_t i = 0; i < std::size_t(someSize / 1.5); i++) {
        expected.push_back(iterData.at(i * 1.5));
      }

      std::vector<int> actual;
      std::copy_n(first, expected.size(), std::back_inserter(actual));
      REQUIRE(actual == expected);
    }

    SUBCASE ("Step = -1.5") {
      auto first = float_step(std::end(iterData) - 1, -1.5);

      std::vector<int> expected;
      for (int i = 0; i < int((someSize - 1) / 1.5); i++) {
        expected.push_back(iterData.at(someSize - 1 - i * 1.5));
      }

      std::vector<int> actual;
      std::copy_n(first, expected.size(), std::back_inserter(actual));
      REQUIRE(actual == expected);
    }
  }

  TEST_CASE ("[iterator] [util] Float step iterator: Going back and forth") {
    std::array<int, 11> data{{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10}};

    SUBCASE ("Step = 1") {
      auto first = float_step(std::begin(data), 1);

      std::vector expected{0, 1, 2, 3, 2, 1, 2};
      std::vector<int> actual;
      actual.push_back(*first);   // 0
      actual.push_back(*++first); // 1
      actual.push_back(*++first); // 2
      actual.push_back(*++first); // 3
      actual.push_back(*--first); // 2
      actual.push_back(*--first); // 1
      actual.push_back(*++first); // 2

      REQUIRE(actual == expected);
    }

    SUBCASE ("Step = -1") {
      auto first = float_step(std::end(data) - 1, -1);

      std::vector expected{10, 9, 8, 7, 8, 9, 8};
      std::vector<int> actual;
      actual.push_back(*first);   // 10
      actual.push_back(*++first); // 9
      actual.push_back(*++first); // 8
      actual.push_back(*++first); // 7
      actual.push_back(*--first); // 8
      actual.push_back(*--first); // 9
      actual.push_back(*++first); // 8

      REQUIRE(actual == expected);
    }

    SUBCASE ("Step = 0.5") {
      auto first = float_step(std::begin(data), 0.5);

      std::vector expected{0, 0, 1, 1, 1, 0, 1};
      std::vector<int> actual;
      actual.push_back(*first);   // 0
      actual.push_back(*++first); // 0.5
      actual.push_back(*++first); // 1
      actual.push_back(*++first); // 1.5
      actual.push_back(*--first); // 1
      actual.push_back(*--first); // 0.5
      actual.push_back(*++first); // 1

      REQUIRE(actual == expected);
    }

    SUBCASE ("Step = -0.5") {
      auto first = float_step(std::end(data) - 1, -0.5);

      std::vector expected{10, 9, 9, 8, 9, 9, 9};
      std::vector<int> actual;
      actual.push_back(*first);   // 10
      actual.push_back(*++first); // 9.5
      actual.push_back(*++first); // 9
      actual.push_back(*++first); // 8.5
      actual.push_back(*--first); // 9
      actual.push_back(*--first); // 9.5
      actual.push_back(*++first); // 9

      REQUIRE(actual == expected);
    }
  }

  TEST_CASE ("[iterator] [util] Zipping iterators") {
    std::size_t some_size = 1000;

    SUBCASE ("Referencing") {
      std::vector<int> data;
      data.reserve(some_size);
      std::generate_n(std::back_inserter(data), some_size, [] { return Random::get<int>(); });

      std::vector<int> new_data;
      new_data.reserve(some_size);
      std::generate_n(std::back_inserter(new_data), some_size, [] { return Random::get<int>(); });

      for (auto&& [dst, src] : util::zip(data, new_data)) {
        dst = src;
      }

      REQUIRE(data == new_data);
    }
  }

  TEST_CASE ("[iterator] [util] Adjacent Pair itereators") {
    std::size_t some_size = 1000;

    SUBCASE ("Adjacent Pairs") {
      std::vector<int> data{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

      std::vector<int> expected{1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 10};

      std::vector<int> actual;

      for (auto pair : util::adjacent_pairs(data)) {
        static_assert(std::is_same_v<std::decay_t<decltype(pair)>, std::pair<int&, int&>>);
        actual.push_back(pair.first);
        actual.push_back(pair.second);
      }

      REQUIRE(actual == expected);
    }

    SUBCASE ("data.size() == 0") {
      std::vector<int> data{};

      bool flag = true;
      for (const auto& pair : util::adjacent_pairs(data)) {
        flag = false;
      }

      REQUIRE(flag);
    }

    SUBCASE ("data.size() == 1") {
      std::vector<int> data{1};

      bool flag = true;
      for (const auto& pair : util::adjacent_pairs(data)) {
        flag = false;
      }

      REQUIRE(flag);
    }
  }

  TEST_CASE ("[iterator] [util] Circular iterator") {
    std::vector<int> data = {1, 2, 3};

    auto circ = view::circular(data);
    auto iter = circ.begin();

    SUBCASE ("basics") {
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

  TEST_CASE ("[iterator][util] Filter view") {
    std::vector data = {1, 2, 3, 4, 5, 5, 4, 3, 2, 1};
    auto lt_3 = util::view::filter(data, [](int i) { return i < 3; });
    auto gt_3 = util::view::filter(data, [](int i) { return i > 3; });
    SUBCASE ("Simple filter test") {
      auto first = lt_3.begin();
      auto last = lt_3.end();
      for (; first != last; first++) {
        REQUIRE(*first < 3);
      }

      REQUIRE(util::view::to_vec(lt_3) == std::vector{1, 2, 2, 1});
      REQUIRE(util::view::to_vec(lt_3) == std::vector{1, 2, 2, 1});
      REQUIRE(util::view::to_vec(gt_3) == std::vector{4, 5, 5, 4});
    }

    SUBCASE ("[iterator][util] Filter -> Transform") {
      auto transformed = util::view::transform(lt_3, [] (int i) { return i * 2; });
      REQUIRE(util::view::to_vec(transformed) == std::vector{2,4,4,2});
      REQUIRE(util::view::to_vec(transformed) == std::vector{2,4,4,2});
    }
  }

} // namespace otto::util
