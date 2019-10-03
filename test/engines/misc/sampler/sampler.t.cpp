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
    template<typename Val, typename Tag, typename... Mixins>
    using ActionProp = ActionProp<Aqh, Val, Tag, Mixins...>;
    Aqh* aqh;

    ActionProp<struct start_point_tag, int> start_point = {aqh, 0};
    ActionProp<struct end_point_tag, int> end_point = {aqh, 0};
    ActionProp<struct fade_in_time_tag, int> fade_in_time = {aqh, 0};
    ActionProp<struct fade_out_time_tag, int> fade_out_time = {aqh, 0};
    ActionProp<struct playback_speed_tag, float> playback_speed = {aqh, 0};

    DECL_REFLECTION(Props, start_point, end_point, fade_in_time, fade_out_time, playback_speed);
  };

  struct Audio {
    void process(audio::AudioBufferHandle audio, bool triggered) noexcept;

    void finish() noexcept;
    void reset() noexcept;

    void action(prop_change<&Props::start_point>, int, int) noexcept;
    void action(prop_change<&Props::end_point>, int, int) noexcept;
    void action(prop_change<&Props::fade_in_time>, int, int) noexcept;
    void action(prop_change<&Props::fade_out_time>, int, int) noexcept;
    void action(prop_change<&Props::playback_speed>, float, float) noexcept;

  private:
    dsp::Sample sample;
    dsp::Sample::iterator sample_iterator;
    bool was_triggered = false;
  };

  TEST_CASE ("Sampler") {
    ActionQueue queue;
    Audio audio;
    Aqh aqh{queue, audio};
    Props props{&aqh};

    SECTION ("Property serialization") {
      props.start_point = 1;
      props.end_point = 2;
      props.fade_in_time = 5;
      props.fade_out_time = 6;
      props.playback_speed = 7;
      auto json = util::serialize(props);
      REQUIRE(json["start_point"] == 1);
      REQUIRE(json["end_point"] == 2);
      REQUIRE(json["fade_in_time"] == 5);
      REQUIRE(json["fade_out_time"] == 6);
      REQUIRE(json["playback_speed"] == 7);
    }

    SECTION ("Property deserialization") {
      auto json = nlohmann::json{
        {"start_point", 1},   //
        {"end_point", 2},     //
        {"fade_in_time", 5},  //
        {"fade_out_time", 6}, //
        {"playback_speed", 7} //
      };
      util::deserialize(props, json);
      REQUIRE(props.start_point == 1);
      REQUIRE(props.end_point == 2);
      REQUIRE(props.fade_in_time == 5);
      REQUIRE(props.fade_out_time == 6);
      REQUIRE(props.playback_speed == 7);
    }
  }

  void Audio::process(audio::AudioBufferHandle audio, bool triggered) noexcept
  {
    if (triggered && !was_triggered) reset();
    was_triggered = triggered;
    for (float& f : audio) {
      f += *sample_iterator++;
    }
  }

  void Audio::finish() noexcept
  {
    sample_iterator = sample.end();
  }

  void Audio::reset() noexcept
  {
    sample_iterator = sample.begin();
  }

/// Helper macro to forward action recievers to sample
#define ACTION_TO_SAMPLE(Name, Type)                                                                                   \
  void Audio::action(prop_change<&Props::Name>, Type new_value, Type old_value) noexcept                               \
  {                                                                                                                    \
    sample.Name(new_value);                                                                                            \
  }

  ACTION_TO_SAMPLE(start_point, int)
  ACTION_TO_SAMPLE(end_point, int)
  ACTION_TO_SAMPLE(fade_in_time, int)
  ACTION_TO_SAMPLE(fade_out_time, int)
  ACTION_TO_SAMPLE(playback_speed, float)

} // namespace otto::engines::sampler
