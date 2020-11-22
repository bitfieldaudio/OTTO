#include "stubs/state.gen.hpp"
#include "testing.t.hpp"

#include "lib/itc/state.hpp"

using namespace otto;

TEST_CASE ("itc::Diff") {
  itc::Diff<stubs::State1> diff;
  diff.bitset().set(reflect::flat_idx(diff.i1));
  REQUIRE(diff.i1.has_changed());
  REQUIRE(!diff.i2.has_changed());
  diff.bitset().set(reflect::flat_idx(diff.nested));
  REQUIRE(diff.nested.has_changed());
  REQUIRE(!diff.nested.f1.has_changed());
  diff.bitset().set(reflect::flat_idx(diff.nested.f1));
  REQUIRE(diff.nested.f1.has_changed());
}

TEST_CASE ("itc::Updater") {
  stubs::State1 state;
  itc::Updater<stubs::State1> updater = {state};
  SUBCASE ("Basics") {
    REQUIRE(updater.bitset().none());
    updater.i1.update() = 4;
    REQUIRE(updater.bitset().test(reflect::flat_idx(updater.i1)));
    REQUIRE(updater.bitset().count() == 1);
    REQUIRE(state.i1 == 4);
  }
  SUBCASE ("Nested") {
    updater.nested.update() = stubs::State1::Nested{.f1 = 1, .f2 = 2};
    REQUIRE(updater.bitset().test(reflect::flat_idx(updater.nested)));
    REQUIRE(updater.bitset().test(reflect::flat_idx(updater.nested.f1)));
    REQUIRE(updater.bitset().test(reflect::flat_idx(updater.nested.f2)));
    REQUIRE(updater.bitset().count() == 3);
    REQUIRE(state.nested.f1 == 1);
    REQUIRE(state.nested.f2 == 2);
  }
  SUBCASE ("for_each_changed") {
    updater.i1.update();
    updater.nested.f2.update();
    updater.str1.update();
    itc::for_each_changed(state, updater.bitset(),
                          [&](auto member) { updater.bitset().flip(reflect::flat_idx(member)); });
    REQUIRE(updater.bitset().none());
  }
}
