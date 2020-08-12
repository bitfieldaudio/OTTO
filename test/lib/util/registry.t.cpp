#include "testing.t.hpp"

#include "lib/util/registry.hpp"

using namespace otto;

struct Base {
  virtual ~Base() = default;
  virtual int get_int() = 0;
};

using BaseRegistry = util::StaticRegistry<Base, util::string_ref>;

struct T1 : Base {
  int get_int() override
  {
    return 1;
  }
};
auto r1 = BaseRegistry::add<T1>("T1");

struct T2 : Base {
  int get_int() override
  {
    return 2;
  }
};
auto r2 = BaseRegistry::add<T2>("T2");

TEST_CASE ("Registry") {
  std::vector<util::string_ref> names;
  std::ranges::transform(BaseRegistry::get(), std::back_inserter(names), &BaseRegistry::Entry::metadata);
  std::ranges::sort(names);

  REQUIRE(names == std::vector<util::string_ref>{"T1", "T2", "T3"});

  std::unique_ptr<Base> b = std::ranges::find(BaseRegistry::get(), "T1", &BaseRegistry::Entry::metadata)->constructor();
  REQUIRE(b->get_int() == 1);
  std::unique_ptr<Base> b3 = std::ranges::find(BaseRegistry::get(), "T3", &BaseRegistry::Entry::metadata)->constructor();
  REQUIRE(b3->get_int() == 3);
}
