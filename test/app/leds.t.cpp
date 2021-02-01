#include "testing.t.hpp"

#include "app/leds.hpp"

#include "lib/util/serialization.hpp"

using namespace otto;

TEST_CASE ("LEDColor") {
  SECTION ("Serialization") {
    REQUIRE(util::serialize(LEDColor{0, 0, 0}) == "#000000");
    REQUIRE(util::serialize(LEDColor{0, 0, 1}) == "#000001");
    REQUIRE(util::serialize(LEDColor{0xFF, 0x89, 0x12}) == "#FF8912");
    REQUIRE(util::serialize(LEDColor{0xFF, 0xFF, 0xFF}) == "#FFFFFF");
  }
  SECTION ("Deserialization") {
    REQUIRE(util::deserialize<LEDColor>("#000000") == LEDColor{0, 0, 0});
    REQUIRE(util::deserialize<LEDColor>("#000001") == LEDColor{0, 0, 1});
    REQUIRE(util::deserialize<LEDColor>("#FF8912") == LEDColor{0xFF, 0x89, 0x12});
    REQUIRE(util::deserialize<LEDColor>("#FFFFFF") == LEDColor{0xFF, 0xFF, 0xFF});
    REQUIRE(util::deserialize<LEDColor>("#abcdef") == LEDColor{0xAB, 0xCD, 0xEF});
    REQUIRE_THROWS(util::deserialize<LEDColor>(""));
    REQUIRE_THROWS(util::deserialize<LEDColor>("0000000"));
    REQUIRE_THROWS(util::deserialize<LEDColor>("#0000000"));
    REQUIRE_THROWS(util::deserialize<LEDColor>("#-00000"));
    REQUIRE_THROWS(util::deserialize<LEDColor>("# 00000"));
    REQUIRE_THROWS(util::deserialize<LEDColor>("#00000G"));
  }
}

TEST_CASE ("Every LED is in an led_group") {
  auto all_groups = led_groups::piano | led_groups::func;
  CAPTURE(all_groups);
  REQUIRE(all_groups.all());
}
