#include "testing.t.hpp"

#include <functional>

#include "core/props/props.hpp"
#include "core/props/mixins/all.hpp"

namespace otto::core::props {

  TEST_CASE("Propeties", "[props]")
  {
    SECTION("Basic mixin tests")
    {
      // Test the tags of a property

      Property<float, no_defaults, steppable> pf = {nullptr, "pf", 0};

      OTTO_META_ASSERT_EQUAL(
        decltype(pf)::tag_list,
        meta::_t<normalize_tags<
        tag_list<steppable>>>);

      pf.set(3.f);
      REQUIRE(pf.get() == 3.f);
      pf.init<steppable>(2.f);
      pf.step(1);
      REQUIRE(pf == 5.f);
      float f = pf;
    }

    struct Props : Properties<> {
      Property<float, no_defaults, steppable, has_limits, faust_link> pf1 = {this, "", 0.f};
      Property<float, steppable, faust_link> pf2                          = {this, "", 1.f};

      Props()
      {
        pf1.init<steppable>(1.f);
        pf1.init<has_limits>(-5.f, 5.f);
      };
    } props;

    CONCEPT_ASSERT(cpts::models<HookTag, common::hooks::on_set,
                                typename decltype(props.pf1)::value_type>());

    static_assert(MixinImpl::has_handler_v<
                  typename decltype(props.pf1)::mixin<has_limits>,
                  common::hooks::on_set, HookOrder::Early>);

    // REQUIRE(props.pf1 == 0.f);
    REQUIRE(props.pf2 == 1.f);
    props.pf1.set(10.f);
    props.pf1 = 10.f;
    // Test limits
    REQUIRE(props.pf1 == 5.f);
  }
} // namespace otto::core::props

namespace otto::core::props {

  Property<float, steppable, has_limits, serializable> property = {nullptr, "property", 0};

  struct Props : Properties<serializable> {
    Property<float, serializable> prop1 = {this, "prop1", 0};
    Property<float, serializable> prop2 = {this, "prop2", 4};

  } props;


  TEST_CASE("Property conversions", "[props]") {
    auto& pb = static_cast<property_base&>(property);
    REQUIRE(&pb == &property);

    const float& val = static_cast<const float&>(property);
    REQUIRE(&val == &property.get());
  }

  TEST_CASE("serializable", "[props]") {
    REQUIRE(props.prop1.to_json() == 0.f);
    REQUIRE(props.prop2.to_json() == 4.f);
    auto expct = nlohmann::json{{"prop1", 0.f}, {"prop2", 4.f}};
    auto& interface = props.as<serializable>();
    REQUIRE(props.name() == "");
    auto got = interface.to_json();
    REQUIRE(got == expct);
  }

  TEST_CASE("has_limits", "[props]") {
    Property<float, steppable, has_limits, serializable> pp = {nullptr, "", 0,
      has_limits::init(1, 5), //
      steppable::init(1.5f),  //
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

  TEST_CASE("wrap", "[props]") {

    Property<int, wrap> prop = {nullptr, "prop", 0,
                                has_limits::init(-2, 2)};

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
  }
}
