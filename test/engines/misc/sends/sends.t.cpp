#include <algorithm>
#include <ostream>

#include "../test/graphics.t.hpp"
#include "core/ui/nvg/Canvas.hpp"
#include "core/ui/nvg/Color.hpp"
#include "core/ui/vector_graphics.hpp"
#include "itc/action_sender.hpp"
#include "itc/prop.hpp"
#include "testing.t.hpp"
#include "util/algorithm.hpp"

// Skipped for now
// TODO: Move this to test the actual sends object

using namespace otto::test;
using namespace otto::core::props;

using Sender = otto::itc::DirectActionSender<>;

struct Props {
  Sender sender;

  Sender::Prop<struct dry_tag, float> dry = {sender, 1, limits(0, 1), step_size(0.01)};
  Sender::Prop<struct fx1_tag, float> fx1 = {sender, 0, limits(0, 1), step_size(0.01)};
  Sender::Prop<struct fx2_tag, float> fx2 = {sender, 0, limits(0, 1), step_size(0.01)};

  struct StoredLevels {
    float fx1 = 0;
    float fx2 = 0;
    float dry = 1;
    float s = 1;
  } stored_levels;
};

bool operator==(const Props& lhs, const std::tuple<float, float, float>& rhs)
{
  return lhs.fx1 == std::get<0>(rhs) && lhs.fx2 == std::get<1>(rhs) && lhs.dry == std::get<2>(rhs);
}
std::ostream& operator<<(std::ostream& s, const Props& v)
{
  return s << "[" << v.fx1 << ", " << v.fx2 << ", " << v.dry << "]";
}

struct Sendstest {
  Sendstest()
  {
    props.dry.observe(nullptr, [&](float a) {
      if (is_recursive) return;
      set(a, props.stored_levels.dry, props.stored_levels.fx1, props.stored_levels.fx2);
    });
    props.fx1.observe(nullptr, [&](float a) {
      if (is_recursive) return;
      set(a, props.stored_levels.fx1, props.stored_levels.dry, props.stored_levels.fx2);
    });
    props.fx2.observe(nullptr, [&](float a) {
      if (is_recursive) return;
      set(a, props.stored_levels.fx2, props.stored_levels.dry, props.stored_levels.fx1);
    });
  }

  Props props;

  bool is_recursive = false;

  static constexpr float threshold = 0.0001;

  void set_scale(float x)
  {
    props.stored_levels.s = x;
    is_recursive = true;
    props.fx1 = props.stored_levels.fx1 * props.stored_levels.s;
    props.fx2 = props.stored_levels.fx2 * props.stored_levels.s;
    props.dry = props.stored_levels.dry * props.stored_levels.s;
    is_recursive = false;
  };

  void set(float value, float& changed, float& other1, float& other2)
  {
    if (value < threshold && ((other1 < threshold && other2 < threshold) ||
                              props.stored_levels.s < threshold)) { // Manually take care of "all 0" edge case
      other1 = 1.f;
      other2 = 1.f;
      changed = 1.f;
      props.stored_levels.s = 0.f;
    } // Main function body below
    else if (value >= other1 * props.stored_levels.s && value >= other2 * props.stored_levels.s) { // Now the largest
      changed = 1;
      other2 = other2 * props.stored_levels.s / value;
      other1 = other1 * props.stored_levels.s / value;
      props.stored_levels.s = value;
    } else if (changed > other1 && changed > other2) { // Was largest, now not
      float new_largest = std::max(other1, other2);
      changed = value / (new_largest * props.stored_levels.s);
      other1 = other1 / new_largest;
      other2 = other2 / new_largest;
      props.stored_levels.s = new_largest;
    } else { // Was not the largest, remained so
      changed = value / props.stored_levels.s;
    }
  };

  float get_pfx1()
  {
    return props.stored_levels.fx1;
  }
  float get_pfx2()
  {
    return props.stored_levels.fx2;
  }
  float get_pdry()
  {
    return props.stored_levels.dry;
  }
  float get_ps()
  {
    return props.stored_levels.s;
  }
};

TEST_CASE ("Sends Calculation" * doctest::skip()) {
  Sendstest send;
  SUBCASE("Init")
  {
    REQUIRE(send.props == std::tuple{0.f, 0.f, 1.f});
  }
  SUBCASE("Set fx1")
  {
    send.props.fx1.set(0.5);
    REQUIRE(send.props == std::tuple{0.5f, 0.f, 1.f});
  }
  SUBCASE("Set fx2")
  {
    send.props.fx2.set(0.5);
    REQUIRE(send.props == std::tuple{0.f, 0.5f, 1.f});
  }
  SUBCASE("Set dry")
  {
    send.props.dry.set(0.5);
    REQUIRE(send.props == std::tuple{0.f, 0.f, 0.5f});
  }
  SUBCASE("Make FX2 biggest")
  {
    send.props.dry.set(0.5);
    send.props.fx2.set(0.7);
    REQUIRE(send.props.dry == approx(0.5));
    REQUIRE(send.props.fx2 == approx(0.7));
    REQUIRE(send.props.fx1 == approx(0));
  }
  SUBCASE("Step Down")
  {
    send.props.fx2.set(0.5);
    send.set_scale(0.5);
    REQUIRE(send.props.dry == approx(0.5));
    REQUIRE(send.props.fx2 == approx(0.25));
  }
  SUBCASE("Step Up")
  {
    send.props.dry.set(0.1);
    send.props.fx1.set(0.5);
    send.props.fx2.set(0.25);
    send.set_scale(1);
    REQUIRE(send.props.fx1 == approx(1));
    REQUIRE(send.props.fx2 == approx(0.5));
    REQUIRE(send.props.dry == approx(0.2));
  }
  SUBCASE("Make FX2 biggest and scale")
  {
    send.props.fx2.set(0.5);
    send.props.dry.set(0.3);
    send.set_scale(1.0);
    REQUIRE(send.props.dry == approx(0.6));
    REQUIRE(send.props.fx2 == approx(1.0));
  }
  SUBCASE("Scale to 0 (from 1 non-zero)")
  {
    send.set_scale(0);
    REQUIRE(send.props.fx1 == approx(0));
    REQUIRE(send.props.fx2 == approx(0));
    REQUIRE(send.props.dry == approx(0));
  }
  SUBCASE("Scale to 0 (from 3 non-zero)")
  {
    send.props.fx1.set(0.5);
    send.props.fx2.set(0.25);
    send.set_scale(0);
    REQUIRE(send.props.fx1 == approx(0));
    REQUIRE(send.props.fx2 == approx(0));
    REQUIRE(send.props.dry == approx(0));
  }
  SUBCASE("Scale from zero (only one zero)")
  {
    send.props.fx1.set(0.5);
    send.props.dry.set(0.0);
    send.set_scale(0);
    REQUIRE(send.get_pfx1() == approx(1));
    REQUIRE(send.get_pfx2() == approx(0));
    REQUIRE(send.get_pdry() == approx(0));
    REQUIRE(send.get_ps() == approx(0));
    send.set_scale(0.5);
    REQUIRE(send.get_pfx1() == approx(1));
    REQUIRE(send.get_pfx2() == approx(0));
    REQUIRE(send.get_ps() == approx(0.5));
    REQUIRE(send.props.fx1 == approx(0.5));
    REQUIRE(send.props.fx2 == approx(0));
    REQUIRE(send.props.dry == approx(0));
  }
  SUBCASE("Scale from zero")
  {
    send.props.fx1.set(0.5);
    send.props.fx2.set(0.25);
    send.set_scale(0);
    send.set_scale(0.5);
    REQUIRE(send.props.fx1 > 0.f);
    REQUIRE(send.props.fx2 > 0.f);
  }
  SUBCASE("Scale from zero to remembered values")
  {
    send.props.fx1.set(0.5);
    send.props.fx2.set(0.25);
    send.props.dry.set(0.1);
    send.set_scale(0);
    send.set_scale(0.5);
    REQUIRE(send.props.fx1 == approx(0.5));
    REQUIRE(send.props.fx2 == approx(0.25));
    REQUIRE(send.props.dry == approx(0.1));
  }
  SUBCASE("If all scrolled down - scale all up equally")
  {
    send.props.dry.set(0);
    REQUIRE(send.get_pfx1() == approx(1));
    REQUIRE(send.get_pfx2() == approx(1));
    REQUIRE(send.get_pdry() == approx(1));
    REQUIRE(send.get_ps() == approx(0));
    send.props.fx2.set(0);
    REQUIRE(send.get_pfx1() == approx(1));
    REQUIRE(send.get_pfx2() == approx(1));
    REQUIRE(send.get_pdry() == approx(1));
    REQUIRE(send.get_ps() == approx(0));
    send.set_scale(0.5);
    REQUIRE(send.props.fx1 == approx(0.5));
    REQUIRE(send.props.fx2 == approx(0.5));
    REQUIRE(send.props.dry == approx(0.5));
  }
}
