#include "core/engine/engine.hpp"
#include "itc/itc.hpp"
#include "testing.t.hpp"

namespace otto::engines::test_engine {

  using namespace core;
  using namespace itc;

  struct PropAR;

  using Sndr = ActionSender<PropAR>;

  struct Props {
    Sndr* sndr;

    Sndr::Prop<struct float_prop_tag, float> float_prop = {sndr, 10};
    Sndr::Prop<struct int_prop_tag, int> int_prop = {sndr, 20};
    Sndr::Prop<struct int_prop_w_limits_tag, int, props::has_limits> int_prop_w_limits = {sndr, 30, props::limits(0, 10)};
  };

  struct PropAR {
    void action(prop_change<&Props::float_prop>, float v)
    {
      float_prop = v;
    };
    float float_prop = 0;

    void action(prop_change<&Props::int_prop>, int v)
    {
      int_prop = v;
    };
    int int_prop = 0;


    void action(prop_change<&Props::int_prop_w_limits>, int v)
    {
      int_prop_w_limits = v;
    };
    int int_prop_w_limits = 0;
  };

  TEST_CASE ("itc::Prop") {
    ActionQueue queue;
    PropAR par;
    Sndr sndr{queue, par};
    Props props{&sndr};

    SECTION ("Upon construction, all properties send change actions") {
      REQUIRE(queue.size() == 3);
      queue.pop_call_all();
      REQUIRE(props.float_prop == 10);
      REQUIRE(props.int_prop == 20);
      REQUIRE(props.int_prop_w_limits == 30);
    }
  }
} // namespace otto::engines::test_engine
