#include "testing.t.hpp"

#include <functional>

#include "core/props/mixins/all.hpp"
#include "core/props/props.hpp"

namespace otto::core::props {

  TEST_CASE ("Propeties") {
    SUBCASE ("Basic mixin tests") {
      // Test the tags of a property

      Property<float, no_defaults, steppable> pf = 0;

      OTTO_META_ASSERT_EQUAL(decltype(pf)::tag_list, meta::_t<normalize_tags<tag_list<steppable>>>);

      pf.set(3.f);
      REQUIRE(pf.get() == 3.f);
      pf.init<steppable>(2.f);
      pf.step(1);
      REQUIRE(pf == 5.f);
      float f = pf;
    }

    struct Props {
      Property<float, no_defaults, steppable, has_limits> pf1 = 0.f;
      Property<float, steppable> pf2 = 1.f;

      Props()
      {
        pf1.init<steppable>(1.f);
        pf1.init<has_limits>(-5.f, 5.f);
      };
    } props;

    static_assert(HookTag::is<common::hooks::on_set, typename decltype(props.pf1)::value_type>);

    static_assert(MixinImpl::has_handler_v<typename decltype(props.pf1)::mixin<has_limits>, common::hooks::on_set,
                                           HookOrder::Middle>);

    // REQUIRE(props.pf1 == 0.f);
    REQUIRE(props.pf2 == 1.f);
    props.pf1.set(10.f);
    props.pf1 = 10.f;
    // Test limits
    REQUIRE(props.pf1 == 5.f);

    SUBCASE ("observer hooks") {
      Property<float> pf = 0;
      bool ran = false;
      pf.observe_no_imidiate_call(nullptr, [&](float f) {
        REQUIRE(f == 10);
        ran = true;
      });
      pf.set(10);
      REQUIRE(ran);
    }
  }

} // namespace otto::core::props

namespace otto::core::props {

  BETTER_ENUM(TestEnum, std::int8_t, V0, V1, V2, V3);

  Property<float, steppable, has_limits> property = 0;

  struct Props {
    Property<float> prop1 = 0;
    Property<float> prop2 = 4;

  } props;


  TEST_CASE ("[props] Property conversions") {
    const float& val = static_cast<const float&>(property);
    REQUIRE(&val == &property.get());
  }

  TEST_CASE ("[props] has_limits") {
    Property<float, steppable, has_limits> pp = {
      0,
      has_limits::init(1, 5),
      steppable::init(1.5f),
    };

    REQUIRE(pp.min == 1.f);
    REQUIRE(pp.max == 5.f);
    REQUIRE(pp.step_size == 1.5f);

    pp.set(4);
    REQUIRE(pp == 4.f);
    pp.set(5);
    REQUIRE(pp == 5.f);
    pp = 5.0001f;
    REQUIRE(pp == 5.f);
    pp = 1023095.f;
    REQUIRE(pp == 5.f);
    pp = 1.f;
    REQUIRE(pp == 1.f);
    pp = 0.f;
    REQUIRE(pp == 1.f);
    pp = -203.f;
    REQUIRE(pp == 1.f);
    pp.min = -10;
    REQUIRE(pp == 1.f);
    pp = -3;
    REQUIRE(pp == -3.f);
    pp = -30;
    REQUIRE(pp == -10.f);
  }

  TEST_CASE ("[props] wrap") {
    Property<int, wrap> prop = {0, has_limits::init(-2, 2)};

    REQUIRE(prop == 0);
    prop.set(1);
    REQUIRE(prop == 1);
    prop.set(2);
    REQUIRE(prop == 2);
    prop.set(3);
    REQUIRE(prop == -2);
    prop.set(-2);
    REQUIRE(prop == -2);
    prop.set(-3);
    REQUIRE(prop == 2);

    prop.set(-2);
    REQUIRE(prop == -2);
    prop.step(-1);
    REQUIRE(prop == 2);
    prop.step(1);
    REQUIRE(prop == -2);

    Property<TestEnum, wrap> ep = {TestEnum::V0};

    REQUIRE(ep == TestEnum::V0);
    ep.step(-1);
    REQUIRE(ep == TestEnum::V3);
    ep.step(1);
    REQUIRE(ep == TestEnum::V0);

    using namespace otto::test;

    SUBCASE ("Floating point") {
      Property<float, wrap> fprop = {0, limits(0, 1), step_size(0.1)};

      REQUIRE(fprop == approx(0));
      fprop.set(0.5);
      REQUIRE(fprop == approx(0.5));
      fprop.set(1);
      REQUIRE(fprop == approx(0));
      fprop.set(1.1);
      REQUIRE(fprop == approx(0.1));
      fprop.set(2);
      REQUIRE(fprop == approx(0));
      fprop.set(-1);
      REQUIRE(fprop == approx(0));

      fprop.set(0);
      REQUIRE(fprop == approx(0));
      fprop.step(-1);
      REQUIRE(fprop == approx(0.9));
      fprop.step(1);
      REQUIRE(fprop == approx(0));
    }
  }
} // namespace otto::core::props
