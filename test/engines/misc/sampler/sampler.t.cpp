#include "testing.t.hpp"

#include "core2/core2.hpp"

namespace otto::engines::sampler {

  using namespace core;
  using namespace core2;

  struct Audio;

  using Aqh = ActionQueueHelper<Audio>;

  struct Props {
    Aqh* aqh;

    props::Property<int, props::mixin::action<struct start_point_tag, Aqh>> start_point = { 0, props::mixin::action<struct start_point_tag, Aqh>::init(aqh) };
  };

  struct Audio {
    void action(prop_change<&Props::start_point>, int new_value, int old_value) {
      start_point = new_value;
    }

    int start_point = 0;
  };

  TEST_CASE ("Sampler") {
    ActionQueue queue;
    Audio audio;
    Aqh aqh {queue, audio};
    Props props {&aqh};

    SECTION("Assigning to start_point calls the action in Audio") {
      props.start_point = 10;
      queue.pop_call_all();
      REQUIRE(audio.start_point == 10);
    }
  }

} // namespace otto::engines::sampler
