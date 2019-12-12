#include "util/variant_w_base.hpp"
#include "testing.t.hpp"

namespace otto::util {
  struct Base {
    virtual std::string f()
    {
      return "Base";
    }
  };

  struct A : Base {
    std::string f() override
    {
      return "A";
    }
  };

  struct B : Base {
    std::string f() override
    {
      return "B";
    }
  };

  struct C : Base {
    std::string f() override
    {
      return "C";
    }
  };

  TEST_CASE("variant_w_base", "[util]") {
    variant_w_base<Base, A, B, C> variant;

    SECTION("emplace_by_index") {
      variant.emplace_by_index(1);
      REQUIRE(variant->f() == "B");
      variant.emplace_by_index(0);
      REQUIRE(variant->f() == "A");
      variant.emplace_by_index(2);
      REQUIRE(variant->f() == "C");
      variant.emplace_by_index(-1);
      REQUIRE(variant->f() == "C");
      variant.emplace_by_index(4);
      REQUIRE(variant->f() == "C");
    }
  }
} // namespace otto::util
