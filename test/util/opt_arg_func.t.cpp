#include "testing.t.hpp"
#include "util/opt_arg_func.hpp"

namespace otto::test {

  TEST_CASE ("util::opt_arg_func") {
    using Func = util::opt_arg_func<void(int, float)>;

    int i;
    Func f = [&i](int j) { i = j; };
    f(10, 5.f);
    REQUIRE(i == 10);
    float fl;
    f = [&](int j, float g) {
      i = j;
      fl = g;
    };
    f(20, 1.5f);
    REQUIRE(i == 20);
    REQUIRE(fl == 1.5f);
    bool was_called = false;
    f = [&] () {
      was_called = true;
    };
    f(100, 23.f);
    REQUIRE(was_called);
  }
} // namespace otto::test
