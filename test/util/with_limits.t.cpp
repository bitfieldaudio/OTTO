#include "testing.t.hpp"
#include "util/with_limits.hpp"

struct FloatConvertible
{
  operator float() const {return 2.3f;};
};

TEST_CASE("WithStaticLimits"){
  otto::util::WithStaticLimits<float, -2, 3> a = -3; // Will clamp to -2
  otto::util::WithStaticLimits<float, -2, 3> b = 1;
  otto::util::WithStaticLimits<int, 0, 3> c = 2;
  otto::util::WithStaticLimits<float, -2, 4> d = 1;
  otto::util::WithStaticLimits<float, -2, 4> e = 0.5;
  
  SUBCASE("Initialization"){
    REQUIRE(a.value == -2.f);
    REQUIRE(a == -2.f);
    REQUIRE(b == 1.f);
    REQUIRE(c == 2);
  }

  SUBCASE("Assignment"){
    a = 2.3;
    REQUIRE(a.value == doctest::Approx(2.3)); 
    c = 0;
    REQUIRE(c.value == 0);
  }

  SUBCASE("Limits"){
    a = 10.f;
    REQUIRE(a == 3);
    c = c + 10;
    REQUIRE(c == 3);
  }

  SUBCASE("Addition"){
    REQUIRE(a == -2);
    REQUIRE(-1 == a + d);
    REQUIRE(0 == a + c);
  }

  SUBCASE("Annoying types"){
    FloatConvertible f;
    REQUIRE(3.3f == b + f);
    REQUIRE(4.3f == c + f);
  }  
  
}