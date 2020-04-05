#include "testing.t.hpp"

#include <string>
#include "util/flat_multimap.hpp"

namespace otto::util {

  using Map = flat_multimap<int, std::string>;

  TEST_CASE ("flat_multimap") {
    Map map;

    map.insert(1, "one");
    map.insert(1, "eins");
    map.insert(1, "et");
    REQUIRE(map.size() == 3);
    REQUIRE(map.keys().size() == 1);

    map.insert(2, "two");
    map.insert(2, "zwei");
    map.insert(2, "to");
    REQUIRE(map.size() == 6);
    REQUIRE(map.keys().size() == 2);

    map.insert(3, "three");
    map.insert(3, "drei");
    map.insert(3, "tre");
  }
} // namespace otto::util
