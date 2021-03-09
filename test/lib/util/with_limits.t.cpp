#include "testing.t.hpp"

#include "lib/util/with_limits.hpp"

using namespace otto;

struct FloatConvertible {
  operator float() const
  {
    return 2.3f;
  };
};

TEST_CASE ("StaticallyBounded") {
  util::Bounded<float, util::bounds<-2, 3>> a = -3; // Will clamp to -2
  util::Bounded<float, util::bounds<-2, 3>> b = 1;
  util::Bounded<int, util::bounds<0, 3>> c = 2;
  util::Bounded<float, util::bounds<-2, 4>> d = 1;
  // util::Bounded<float, util::bounds<-2, 4>> e = 0.5;

  SECTION ("Initialization") {
    REQUIRE(a == -2.f);
    REQUIRE(b == 1.f);
    REQUIRE(c == 2);
  }

  SECTION ("Assignment") {
    a = 2.3;
    REQUIRE(a == 2.3_a);
    c = 0;
    REQUIRE(c == 0);
  }

  SECTION ("Limits") {
    a = 10.f;
    REQUIRE(a == 3);
    c = c + 10;
    REQUIRE(c == 3);
  }

  SECTION ("Addition") {
    REQUIRE(a == -2);
    REQUIRE(-1 == a + d);
    REQUIRE(0 == a + c);
  }

  SECTION ("Annoying types") {
    FloatConvertible f;
    REQUIRE(3.3f == b + f);
    REQUIRE(4.3f == c + f);
  }

  SECTION ("Other assignments") {
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
    REQUIRE(t == 0.5_a);
  }

  SECTION ("Comparison") {
    util::StaticallyBounded<float, -2, 3> k = 1;
    util::StaticallyBounded<float, -2, 3> l = 2;
    REQUIRE(b == k);
    REQUIRE(b != l);
  }
}

TEST_CASE ("DynamicallyBounded") {
  util::DynamicallyBounded<int> a = {-1, -2, 5};
  util::DynamicallyBounded<float> b = {1, -2, 5};

  SECTION ("Initialization") {
    REQUIRE(a == -1);
    util::DynamicallyBounded<int> c = {-4, -2, 5};
    REQUIRE(c == -2);
  }

  SECTION ("Assignment") {
    b = 2.3;
    REQUIRE(b == 2.3_a);
    a = 0;
    REQUIRE(a == 0);
  }

  SECTION ("Limits") {
    a = 10.f;
    REQUIRE(a == 5);
    b = b + 10;
    REQUIRE(b == 5);
  }

  SECTION ("Addition") {
    REQUIRE(a == -1);
    REQUIRE(-2 == a + a);
    util::DynamicallyBounded<float> c = {1, -2, 5};
    REQUIRE(b + c == 2._a);
  }

  SECTION ("Comparison") {
    util::DynamicallyBounded<float> k = {1, -2, 5};
    util::DynamicallyBounded<float> l = {2, -2, 3};
    REQUIRE(b == k);
    REQUIRE(b != l);
    k.max(3);
    REQUIRE(b != k);
  }

  // TODO: Changing limits
}

TEST_CASE ("Wrapping") {
  util::StaticallyBounded<int, -2, 5, util::bounds_policies::wrap> a = -1;
  util::StaticallyBounded<float, -2, 5, util::bounds_policies::wrap> b = 3;
  util::DynamicallyBounded<float, util::bounds_policies::wrap> c = {1, -2, 5};

  SECTION ("Upwards") {
    SECTION ("Static Int") {
      REQUIRE(a == -1);
      a = 5;
      a++;
      REQUIRE(a == -2);
    }
    SECTION ("Static float") {
      REQUIRE(b == 3._a);
      b = 6;
      REQUIRE(b == -1._a);
      b = 14;
      REQUIRE(b == 0._a);
    }
    SECTION ("Dynamic float") {
      REQUIRE(c == 1._a);
      c = 6;
      REQUIRE(c == -1._a);
      c = 14;
      REQUIRE(c == 0._a);
    }
  }
  SECTION ("Downwards") {
    SECTION ("Static Int") {
      REQUIRE(a == -1);
      a = -5;
      REQUIRE(a == 3);
    }
    SECTION ("Static float") {
      REQUIRE(b == 3._a);
      b = -6;
      REQUIRE(b == 1._a);
      b = -14;
      REQUIRE(b == 0._a);
    }
  }
}
