// Extra file to test registry from other translation unit

#include "testing.t.hpp"

#include "lib/util/registry.hpp"

using namespace otto;

struct Base {
  virtual ~Base() = default;
  virtual int get_int() = 0;
};

using BaseRegistry = util::StaticRegistry<Base, util::string_ref>;

struct T3 : Base {
  int get_int() override
  {
    return 3;
  }
};
auto r3 = BaseRegistry::add<T3>("T3");
