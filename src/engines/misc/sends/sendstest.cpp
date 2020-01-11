#include <algorithm>

#include "testing.t.hpp"


using namespace otto::test;

struct Props {
  float fx1 = 1;
  float fx2 = 0;
  float dry = 0;
  float s = 1;
};

struct Visual {
  float fx1 = 1;
  float fx2 = 0;
  float dry = 0;

  bool operator==(const Visual& rhs) const
  {
    return fx1 == rhs.fx1 && fx2 == rhs.fx2;
  }
};

struct Sendstest {
  Visual visual;

  static constexpr float threshold = 0.0001;

  void set_fx1(float a)
  {
    if (a < threshold && (props.fx2 < threshold || props.s < threshold)) { // Manually take care of "all 0" edge case
      props.fx1 = 1.f;
      props.fx2 = 1.f;
      props.s = 0.f;
    } // Main function body below
    else if (a >= props.fx2 * props.s) { // Now the largest
      props.fx1 = 1;
      props.fx2 = props.fx2 * props.s / a;
      props.s = a;
    } else if (props.fx1 > props.fx2) { // Was largest, now not
      props.fx1 = a / (props.fx2 * props.s);
      props.s = props.fx2 * props.s;
      props.fx2 = 1;
    } else { // Was not the largest, remained so
      props.fx1 = a / props.s;
    }
    recalculate();
  };

  void set_fx2(float a)
  {
    if (a < threshold && (props.fx1 < threshold || props.s < threshold)) { // Manually take care of "all 0" edge case
      props.fx1 = 1.f;
      props.fx2 = 1.f;
      props.s = 0.f;
    } // Main function body below
    else if (a >= props.fx1 * props.s) {
      props.fx2 = 1;
      props.fx1 = props.fx1 * props.s / a;
      props.s = a;
    } else if (props.fx1 > props.fx2) { // Was largest, now not
      props.fx2 = a / (props.fx1 * props.s);
      props.s = props.fx1 * props.s;
      props.fx1 = 1;
    } else {
      props.fx2 = a / props.s;
    }
    recalculate();
  };

  void set_scale(float x)
  {
    props.s = x;
    recalculate();
  };

  float get_pfx1()
  {
    return props.fx1;
  }
  float get_pfx2()
  {
    return props.fx2;
  }
  float get_ps()
  {
    return props.s;
  }

private:
  Props props;
  void recalculate()
  {
    visual.fx1 = props.fx1 * props.s;
    visual.fx2 = props.fx2 * props.s;
  };
};

TEST_CASE ("Sends Calculation") {
  Sendstest send;
  SUBCASE("Init")
  {
    REQUIRE(send.visual == Visual{1, 0});
  }
  SUBCASE("Set fx1")
  {
    send.set_fx1(0.5);
    REQUIRE(send.visual == Visual{0.5, 0});
  }
  SUBCASE("Set fx2")
  {
    send.set_fx2(0.5);
    REQUIRE(send.visual == Visual{1.f, 0.5});
  }
  SUBCASE("Make FX2 biggest")
  {
    send.set_fx1(0.5);
    send.set_fx2(0.7);
    REQUIRE(send.visual == Visual{0.5, 0.7});
  }
  SUBCASE("Step Down")
  {
    send.set_fx2(0.5);
    send.set_scale(0.5);
    REQUIRE(send.visual.fx1 == approx(0.5));
    REQUIRE(send.visual.fx2 == approx(0.25));
  }
  SUBCASE("Step Up")
  {
    send.set_fx1(0.5);
    send.set_fx2(0.25);
    send.set_scale(1);
    REQUIRE(send.visual.fx1 == approx(1));
    REQUIRE(send.visual.fx2 == approx(0.5));
  }
  SUBCASE("Make FX2 biggest and scale")
  {
    send.set_fx2(0.5);
    send.set_fx1(0.3);
    send.set_scale(1.0);
    REQUIRE(send.visual.fx1 == approx(0.6));
    REQUIRE(send.visual.fx2 == approx(1.0));
  }
  SUBCASE("Scale to 0 (from 1 non-zero)")
  {
    send.set_scale(0);
    REQUIRE(send.visual.fx1 == approx(0));
    REQUIRE(send.visual.fx2 == approx(0));
  }
  SUBCASE("Scale to 0 (from 2 non-zero)")
  {
    send.set_fx1(0.5);
    send.set_fx2(0.25);
    send.set_scale(0);
    REQUIRE(send.visual.fx1 == approx(0));
    REQUIRE(send.visual.fx2 == approx(0));
  }
  SUBCASE("Scale from zero (only one zero)")
  {
    send.set_fx1(0.5);
    send.set_fx2(0.0);
    send.set_scale(0);
    REQUIRE(send.get_pfx1() == approx(1));
    REQUIRE(send.get_pfx2() == approx(0));
    REQUIRE(send.get_ps() == approx(0));
    send.set_scale(0.5);
    REQUIRE(send.get_pfx1() == approx(1));
    REQUIRE(send.get_pfx2() == approx(0));
    REQUIRE(send.get_ps() == approx(0.5));
    REQUIRE(send.visual.fx1 == approx(0.5));
    REQUIRE(send.visual.fx2 == approx(0));
  }
  SUBCASE("Scale from zero")
  {
    send.set_fx1(0.5);
    send.set_fx2(0.25);
    send.set_scale(0);
    send.set_scale(0.5);
    REQUIRE(send.visual.fx1 > 0.f);
    REQUIRE(send.visual.fx2 > 0.f);
  }
  SUBCASE("Scale from zero to remembered values")
  {
    send.set_fx1(0.5);
    send.set_fx2(0.25);
    send.set_scale(0);
    send.set_scale(0.5);
    REQUIRE(send.visual.fx1 == approx(0.5));
    REQUIRE(send.visual.fx2 == approx(0.25));
  }
  SUBCASE("If all scrolled down - scale all up equally"){
    send.set_fx1(0);
    REQUIRE(send.get_pfx1() == approx(1));
    REQUIRE(send.get_pfx2() == approx(1));
    REQUIRE(send.get_ps() == approx(0));
    send.set_fx2(0);
    REQUIRE(send.get_pfx1() == approx(1));
    REQUIRE(send.get_pfx2() == approx(1));
    REQUIRE(send.get_ps() == approx(0));
    send.set_scale(0.5);
    REQUIRE(send.visual.fx1 == approx(0.5));
    REQUIRE(send.visual.fx2 == approx(0.5));
  }

}
