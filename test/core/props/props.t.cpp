#include "testing.t.hpp"

#include "core/props/props.hpp"

namespace otto::core::props {

  // Make sure that tags are sorted and uniquified correctly

  BOOST_HANA_CONSTANT_CHECK(
    black_magic::sort_tags(
      black_magic::tag_list<mixins::has_value, mixins::steppable>()) ==
    black_magic::sort_tags(
      black_magic::tag_list<mixins::steppable, mixins::has_value>()));

  BOOST_HANA_CONSTANT_CHECK(
    black_magic::sort_tags(black_magic::tag_list<mixins::has_value,
                                                 mixins::steppable,
                                                 mixins::has_value>()) ==
    black_magic::sort_tags(
      black_magic::tag_list<mixins::steppable, mixins::has_value>()));

  // Make sure that requirements are pulled in, and still sorted correctly

  BOOST_HANA_CONSTANT_CHECK(
    black_magic::with_required(black_magic::tag_list<mixins::steppable>()) ==
    black_magic::sort_tags(
      black_magic::tag_list<mixins::steppable, mixins::has_value>()));

  // Test the public `make_tag_list_t` type

  BOOST_HANA_CONSTANT_CHECK(
    make_tag_list_t<mixins::steppable>() ==
    black_magic::sort_tags(
      black_magic::tag_list<mixins::steppable, mixins::has_value>()));

  // Test the tags of a property

  Property<float, mixins::steppable> pf;

  BOOST_HANA_CONSTANT_CHECK(
    pf.tag_list ==
    black_magic::sort_tags(
      black_magic::tag_list<mixins::steppable, mixins::has_value>()));

  // Assert that the mixin implementation is inherited by the property
  static_assert(std::is_base_of_v<tag_mixin_t<mixins::steppable, float, make_tag_list_t<mixins::steppable>>, decltype(pf)>);

  void test()
  {
    pf.step(1);
    pf.get();
    float f = pf;
  }
} // namespace otto::core::props
