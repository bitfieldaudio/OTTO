#include "testing.t.hpp"

#include "core/audio/clock.hpp"

namespace otto::test {
  using namespace otto::core::clock;
  using namespace otto::core::clock::notes;

  TEST_CASE ("core::audio::ClockRange") {
    ClockRange cr{whole + sixteenth, whole + quarter};


    SUBCASE ("contains_multiple") {
      REQUIRE(cr.contains_multiple(sixtyfourth));
      REQUIRE(cr.contains_multiple(thirtysecond));
      REQUIRE(cr.contains_multiple(sixteenth));
      REQUIRE(cr.contains_multiple(eighth));
      REQUIRE(!cr.contains_multiple(quarter));
      REQUIRE(!cr.contains_multiple(half));
      REQUIRE(!cr.contains_multiple(whole));

      REQUIRE(cr.contains_multiple(whole + sixteenth));
      REQUIRE(cr.contains_multiple(whole + eighth));
      REQUIRE(!cr.contains_multiple(whole + quarter));

      REQUIRE(cr.contains_multiple(1));

      cr = {whole, whole};

      REQUIRE(!cr.contains_multiple(1));

      cr = {0, whole};
      REQUIRE(cr.contains_multiple(1));
      REQUIRE(cr.contains_multiple(half));
    }

    SUBCASE ("count_multiple") {
      REQUIRE(cr.count_multiple(sixtyfourth) == 12);
      REQUIRE(cr.count_multiple(thirtysecond) == 6);
      REQUIRE(cr.count_multiple(sixteenth) == 3);
      REQUIRE(cr.count_multiple(eighth) == 1);
      REQUIRE(cr.count_multiple(quarter) == 0);
      REQUIRE(cr.count_multiple(half) == 0);
      REQUIRE(cr.count_multiple(whole) == 0);

      REQUIRE(cr.count_multiple(whole + sixteenth) == 1);
      REQUIRE(cr.count_multiple(whole + eighth) == 1);
      REQUIRE(cr.count_multiple(whole + quarter) == 0);

      REQUIRE(cr.count_multiple(1) == quarter - sixteenth);

      cr = {whole, whole};

      REQUIRE(cr.count_multiple(1) == 0);

      cr = {0, whole};

      REQUIRE(cr.count_multiple(1) == whole - 1);
      REQUIRE(cr.count_multiple(half) == 1);
    }
  }
} // namespace otto::test
