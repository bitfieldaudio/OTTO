#include "../testing.t.hpp"

#include "util/result.hpp"

namespace top1 {

  using namespace std::literals;

  TEST_CASE("top1::result", "[result] [util]") {

    SECTION("Ok state basic tests") {
      using result_t = result<std::string, int>;

      result_t r {"I am ok!"s};

      REQUIRE(r.is_ok());
      REQUIRE(r.ok().has_value());
      REQUIRE(r.ok().value() == "I am ok!"s);
      REQUIRE(!r.is_err());
      REQUIRE(!r.err().has_value());

      r = 4;

      REQUIRE(r.is_err());
      REQUIRE(r.err().has_value());
      REQUIRE(r.err().value() == 4);
      REQUIRE(!r.is_ok());
      REQUIRE(!r.ok().has_value());
    }

  }

}
