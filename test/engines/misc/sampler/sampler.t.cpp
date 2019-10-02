#include "testing.t.hpp"

#include "core/audio/processor.hpp"
#include "core2/core2.hpp"
#include "util/dsp/sample.hpp"

namespace otto::engines::sampler {

  using namespace core;
  using namespace core2;
  struct Audio;

  using Aqh = ActionQueueHelper<Audio>;

  struct Props {
    template<typename Val, typename Tags, typename... Mixins>
    using ActionProp = ActionProp<Aqh, Val, Tags, Mixins...>;
    Aqh* aqh;

    ActionProp<int, struct start_point_tag> start_point = {0, aqh};
    ActionProp<int, struct end_point_tag> end_point = {0, aqh};
    ActionProp<int, struct loop_start_tag> loop_start = {0, aqh};
    ActionProp<int, struct loop_end_tag> loop_end = {0, aqh};
    ActionProp<int, struct fade_in_time_tag> fade_in_time = {0, aqh};
    ActionProp<int, struct fade_out_time_tag> fade_out_time = {0, aqh};
    ActionProp<float, struct playback_speed_tag> playback_speed = {0, aqh};

    DECL_REFLECTION(Props, start_point);
  };

  struct Audio {
    void action(Action<start_point_tag, int, int>, int new_value, int old_value)
    {
      sample.start_point(new_value);
    }
    void action(prop_change<&Props::end_point>, int new_value, int old_value)
    {
      sample.end_point(new_value);
    }
    void process(audio::AudioBufferHandle audio, bool triggered);

  private:
    dsp::Sample sample;
  };

  TEST_CASE ("Sampler") {
    ActionQueue queue;
    Audio audio;
    Aqh aqh{queue, audio};
    Props props{&aqh};

    SECTION ("Property serialization") {
      auto json = util::serialize(props);
      REQUIRE(json["start_point"] == 0);
    }

    SECTION ("Property deserialization") {
      auto json = nlohmann::json{{"start_point", 10}};
      util::deserialize(props, json);
      REQUIRE(props.start_point == 10);
    }
  }


  void Audio::process(audio::AudioBufferHandle audio, bool triggered) {}

} // namespace otto::engines::sampler
