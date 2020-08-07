#include "lib/util/with_limits.hpp"
#include "testing.t.hpp"

using namespace otto;

struct FloatConvertible {
  operator float() const
  {
    return 2.3f;
  };
};

TEST_CASE ("StaticallyBounded") {
  util::StaticallyBounded<float, -2, 3> a = -3; // Will clamp to -2
  util::StaticallyBounded<float, -2, 3> b = 1;
  util::StaticallyBounded<int, 0, 3> c = 2;
  util::StaticallyBounded<float, -2, 4> d = 1;
  util::StaticallyBounded<float, -2, 4> e = 0.5;

  SUBCASE ("Initialization") {
    REQUIRE(a == -2.f);
    REQUIRE(b == 1.f);
    REQUIRE(c == 2);
  }

  SUBCASE ("Assignment") {
    a = 2.3;
    REQUIRE(a == doctest::Approx(2.3));
    c = 0;
    REQUIRE(c == 0);
  }

  SUBCASE ("Limits") {
    a = 10.f;
    REQUIRE(a == 3);
    c = c + 10;
    REQUIRE(c == 3);
  }

  SUBCASE ("Addition") {
    REQUIRE(a == -2);
    REQUIRE(-1 == a + d);
    REQUIRE(0 == a + c);
  }

  SUBCASE ("Annoying types") {
    FloatConvertible f;
    REQUIRE(3.3f == b + f);
    REQUIRE(4.3f == c + f);
  }

  SUBCASE ("Other assignments") {
    // Plus
    a += 10;
    REQUIRE(a == 3);
    // Minus
    a -= 100;
    REQUIRE(a == -2);
    // Multiply
    util::StaticallyBounded<float, -2, 3> s = 1;
    s *= 2;
    REQUIRE(s == 2);
    s *= 2;
    REQUIRE(s == 3);
    s = -1;
    s *= 3;
    REQUIRE(s == -2);
    // Divide
    util::StaticallyBounded<float, -2, 3> t = 1;
    t /= 2;
    REQUIRE(t == doctest::Approx(0.5f));
  }

  SUBCASE ("Comparison") {
    util::StaticallyBounded<float, -2, 3> k = 1;
    util::StaticallyBounded<float, -2, 3> l = 2;
    REQUIRE(b == k);
    REQUIRE(b != l);
  }
}

TEST_CASE ("DynamicallyBounded") {
  util::DynamicallyBounded<int> a = {-1, -2, 5};
  util::DynamicallyBounded<float> b = {1, -2, 5};

  SUBCASE ("Initialization") {
    REQUIRE(a == -1);
    util::DynamicallyBounded<int> c = {-4, -2, 5};
    REQUIRE(c == -2);
  }

  SUBCASE ("Assignment") {
    b = 2.3;
    REQUIRE(b == doctest::Approx(2.3));
    a = 0;
    REQUIRE(a == 0);
  }

  SUBCASE ("Limits") {
    a = 10.f;
    REQUIRE(a == 5);
    b = b + 10;
    REQUIRE(b == 5);
  }

  SUBCASE ("Addition") {
    REQUIRE(a == -1);
    REQUIRE(-2 == a + a);
    util::DynamicallyBounded<float> c = {1, -2, 5};
    REQUIRE(b + c == doctest::Approx(2.f));
  }

  SUBCASE ("Comparison") {
    util::DynamicallyBounded<float> k = {1, -2, 5};
    util::DynamicallyBounded<float> l = {2, -2, 3};
    REQUIRE(b == k);
    REQUIRE(b != l);
    k.max(3);
    REQUIRE(b != k);
  }

  // TODO: Changing limits
}
