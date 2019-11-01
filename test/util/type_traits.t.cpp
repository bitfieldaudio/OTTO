#include "testing.t.hpp"
#include "util/type_traits.hpp"

namespace otto::util {

  TEST_CASE("util::tuple::remove_last", "[util]") {

    std::tuple t = {1, 2.0, 3.f, false};
    REQUIRE(tuple::remove_last(t) == std::tuple{1, 2.0, 3.f});

    REQUIRE(tuple::remove_last(tuple::remove_last(t)) == std::tuple{1, 2.0});

    REQUIRE(tuple::remove_last(std::tuple{1}) == std::tuple<>{});
  }

} // namespace otto::util
