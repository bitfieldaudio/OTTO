#include "../testing.t.hpp"

#include <string>

#include "util/result.hpp"

namespace top1 {

  using namespace std::literals;

  TEST_CASE("top1::result", "[result] [util]") {

    SECTION("Basic tests") {
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

    SECTION("map") {
      struct Err {
        int errCode;
      };

      result<std::string, Err> res = "U got it"s;

      result<bool, Err> res2 = res.map([] (const std::string& ok) {
          return ok == "U got it"s;
        });

      REQUIRE(res2.is_ok());
      REQUIRE(res2.ok() == true);

      res2 = Err{42};

      REQUIRE(res2.is_err());

      auto res3 = res2.map([] (bool b) {
          FAIL("The function passed to map should not be called from errored state");
          return (int) b;
        });

      REQUIRE(res3.is_err());
      REQUIRE(res3.err().value().errCode == 42);
    }
    }

}
