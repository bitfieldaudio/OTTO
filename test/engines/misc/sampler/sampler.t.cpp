#include "testing.t.hpp"

#include <atomic>

#include "dummy_services.hpp"

#include "core/audio/processor.hpp"
#include "core/engine/engine.hpp"
#include "itc/itc.hpp"
#include "util/dsp/sample.hpp"

namespace otto::engines::sampler {

  using namespace core;
  using namespace itc;
  struct Audio;
  struct MainScreen;
  struct EnvelopeScreen;

  using AudioAQH = ActionQueueHelper<Audio>;
  using GraphicsAQH = ActionQueueHelper<MainScreen, EnvelopeScreen>;
  using Aqh = JoinedActionQueueHelper<AudioAQH, GraphicsAQH>;

  struct Props {
    Aqh* aqh;

    Aqh::Prop<struct start_point_tag, int> start_point = {aqh, 0};
    Aqh::Prop<struct end_point_tag, int> end_point = {aqh, 0};
    Aqh::Prop<struct fade_in_time_tag, int> fade_in_time = {aqh, 0};
    Aqh::Prop<struct fade_out_time_tag, int> fade_out_time = {aqh, 0};
    Aqh::Prop<struct playback_speed_tag, float> playback_speed = {aqh, 0, props::limits(-10, 10)};

    DECL_REFLECTION(Props, start_point, end_point, fade_in_time, fade_out_time, playback_speed);
  };

  struct Actions {
    /// Get the current progress as a float in range [0;1], where 0 means
    using get_progress = Action<struct get_progress_action, std::atomic<float>&>;
    /// Action to set the audio data to play.
    ///
    /// start/end points, fade in/out times and playback speed will all be reset,
    /// so make sure to update these accordingly afterwards.
    using set_sample_buffer = Action<struct set_sample_action, gsl::span<float>>;
  };

  struct Audio {
    void process(audio::AudioBufferHandle audio, bool triggered) noexcept;

    void finish() noexcept;
    void reset() noexcept;

    void action(Actions::get_progress, std::atomic<float>&) const noexcept;
    void action(Actions::set_sample_buffer, gsl::span<float>) noexcept;

    void action(prop_change<&Props::start_point>, int) noexcept;
    void action(prop_change<&Props::end_point>, int) noexcept;
    void action(prop_change<&Props::fade_in_time>, int) noexcept;
    void action(prop_change<&Props::fade_out_time>, int) noexcept;
    void action(prop_change<&Props::playback_speed>, float) noexcept;

    dsp::Sample sample;
    dsp::Sample::iterator sample_iterator = sample.end();
    bool was_triggered = false;
  };

  struct MainScreen : ui::Screen {
    void draw(ui::vg::Canvas& ctx) override {}
  };

  struct EnvelopeScreen : ui::Screen {
    void draw(ui::vg::Canvas& ctx) override {}
  };
  struct Engine {
    static constexpr util::string_ref name = "Sampler";
    using Props = Props;

    Audio audio;
    MainScreen main_screen;
    EnvelopeScreen envelope_screen;

    AudioAQH audio_aqh = services::AudioManager::current().make_aqh(audio);
    GraphicsAQH graphics_aqh = services::UIManager::current().make_aqh(main_screen, envelope_screen);
    Aqh aqh = {audio_aqh, graphics_aqh};

    Props props = {&aqh};
  };

  using namespace test;

  TEST_CASE ("Sampler") {
    ActionQueue audio_queue;
    ActionQueue ui_queue;
    Audio audio;
    MainScreen main_screen;
    EnvelopeScreen env_screen;
    Aqh aqh{{audio_queue, audio}, {ui_queue, main_screen, env_screen}};
    Props props{&aqh};

    int ref_count = 0;
    auto the_buffer = util::generate_array<10>([](auto i) { return float(i); });
    core::audio::AudioBufferHandle buffer = {the_buffer.data(), the_buffer.size(), ref_count};

    std::atomic<float> progress;

    SECTION ("Initial construction") {
      SECTION ("All audio is unchanged when not triggered") {
        audio.process(buffer, false);
        auto expected = util::generate_vector(10, [](auto i) { return float(i); });
        REQUIRE_THAT(util::view::to_vec(buffer), Catch::Approx(expected));
      }
      SECTION ("All audio is unchanged when triggered") {
        audio.process(buffer, true);
        auto expected = util::generate_vector(10, [](auto i) { return float(i); });
        REQUIRE_THAT(util::view::to_vec(buffer), Catch::Approx(expected));
      }
      SECTION ("Progress is 0") {
        audio.action(Actions::get_progress(), progress);
        REQUIRE(progress == approx(0));
        audio.process(buffer, false);
        REQUIRE(progress == approx(0));
        audio.process(buffer, true);
        REQUIRE(progress == approx(0));
      }
    }

    std::vector<float> the_sample;
    std::generate_n(std::back_inserter(the_sample), 100, [i = 0]() mutable { return i++; });

    audio.action(Actions::set_sample_buffer(), the_sample);

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

    SECTION ("get_progress action") {
      SECTION ("Initially, progress is zero") {
        audio.action(Actions::get_progress(), progress);
        REQUIRE(progress == approx(0.f));
      }
      SECTION ("Does not progress when not triggered") {
        audio.process(buffer, false);
        audio.action(Actions::get_progress(), progress);
        REQUIRE(progress == approx(0.f));
      }
      SECTION ("When progressing 10 frames into a 100 frames sample, progress is 0.1") {
        audio.process(buffer, true);
        audio.action(Actions::get_progress(), progress);
        REQUIRE(progress == approx(0.1f));
      }
      SECTION ("after processing 90 frames, progress is 0.9") {
        for (int i : util::view::ints(0, 9)) audio.process(buffer, true);
        audio.action(Actions::get_progress(), progress);
        REQUIRE(progress == approx(0.9f));
      }
      SECTION ("After processing 100 frames, progress is 0") {
        for (int i : util::view::ints(0, 11)) audio.process(buffer, true);
        audio.action(Actions::get_progress(), progress);
        REQUIRE(progress == approx(0.f));
      }
      SECTION ("When progressing 10 frames into a 100 frames sample playing at 2x, progress is 0.2") {
        audio.action(prop_change<&Props::playback_speed>(), 2);
        audio.process(buffer, true);
        audio.action(Actions::get_progress(), progress);
        REQUIRE(progress == approx(0.2f));
      }
      SECTION ("Reverse") {
        audio.action(prop_change<&Props::playback_speed>(), -1);
        SECTION ("Initially, progress is one") {
          audio.action(Actions::get_progress(), progress);
          REQUIRE(progress == approx(1.f));
        }
        SECTION ("Does not progress when not triggered") {
          audio.process(buffer, false);
          audio.action(Actions::get_progress(), progress);
          REQUIRE(progress == approx(1.f));
        }
        SECTION ("When progressing 10 frames into a 100 frames sample, progress is 0.9") {
          audio.process(buffer, true);
          audio.action(Actions::get_progress(), progress);
          REQUIRE(progress == approx(0.9f));
        }
        SECTION ("When progressing 10 frames into a 100 frames sample playing at 2x, progress is 0.2") {
          audio.action(prop_change<&Props::playback_speed>(), -2);
          audio.process(buffer, true);
          audio.action(Actions::get_progress(), progress);
          REQUIRE(progress == approx(0.8f));
        }
        SECTION ("after processing all 100 frames, progress is 1") {
          for (int i : util::view::ints(0, 10)) audio.process(buffer, true);
          audio.action(Actions::get_progress(), progress);
          REQUIRE(progress == approx(1.f));
        }
      }
    }
  }

  TEST_CASE ("Sampler integration audio") {
    auto app = services::test::make_dummy_application();

    ActionQueue graphics_queue;

    sampler::Audio sampler_audio;
    sampler::MainScreen main_screen;
    sampler::EnvelopeScreen envelope_screen;

    sampler::AudioAQH audio_aqh = services::AudioManager::current().make_aqh(sampler_audio);
    sampler::GraphicsAQH graphics_aqh = {graphics_queue, main_screen, envelope_screen};
    sampler::Aqh aqh = {audio_aqh, graphics_aqh};
    sampler::Props props = {&aqh};

    services::test::DummyEngineManager::current().on_process = [&](auto data) {
      auto buffer = services::AudioManager::current().buffer_pool().allocate();
      sampler_audio.process(data.audio, false);
      util::copy(data.audio, buffer.begin());
      return data.with(std::array{data.audio, buffer});
    };

    app.engine_manager->start();
    app.audio_manager->start();

    props.playback_speed = -1;

    services::test::DummyAudioManager::current().process();

    // The main test here is actually whether actions on the audio queue are run at all
    REQUIRE(sampler_audio.sample.playback_speed() == -1);
  }

  TEST_CASE ("Sampler integration") {
    auto app = services::test::make_dummy_application();

    sampler::Engine sampler_engine;

    app.engine_manager->start();
    app.audio_manager->start();

    services::test::DummyUIManager::current().display(sampler_engine.main_screen);
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

  void Audio::action(Actions::get_progress, std::atomic<float>& result) const noexcept
  {
    auto val = (sample_iterator - sample.begin()) / float(sample.size());
    if (sample_iterator == sample.end()) val = 0;
    // if going in reverse, progress starts at 1 and goes to 0
    if (sample.playback_speed() < 0) val = 1.f - val;
    result = val;
  }

  void Audio::action(Actions::set_sample_buffer, gsl::span<float> new_sample) noexcept
  {
    sample = dsp::Sample(new_sample);
    sample_iterator = sample.end();
  }

  void Audio::action(prop_change<&Props::start_point>, int new_value) noexcept
  {
    sample.start_point(new_value);
  }
  void Audio::action(prop_change<&Props::end_point>, int new_value) noexcept
  {
    sample.end_point(new_value);
  }
  void Audio::action(prop_change<&Props::fade_in_time>, int new_value) noexcept
  {
    sample.fade_in_time(new_value);
  }
  void Audio::action(prop_change<&Props::fade_out_time>, int new_value) noexcept
  {
    sample.fade_out_time(new_value);
  }
  void Audio::action(prop_change<&Props::playback_speed>, float new_value) noexcept
  {
    bool do_finish = sample_iterator == sample.end();
    sample.playback_speed(new_value);
    if (do_finish) finish();
  }

} // namespace otto::engines::sampler
