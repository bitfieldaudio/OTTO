#include "core/engine/engine_dispatcher.hpp"
#include "testing.t.hpp"

namespace otto::test {
  using namespace otto::core::engine;

  namespace testfxengine1 {
    struct Audio;
    struct Screen;

    using Sndr = EngineSender<Audio, Screen>;

    struct Props {
      Sndr sender;

      Sndr::Prop<struct test_prop_tag, float> test_prop1 = {sender, 0.f};
    };

    struct TestFXEngine1 : EffectEngine<TestFXEngine1> {
      static constexpr util::string_ref name = "Test FX Engine 1";

      std::unique_ptr<Audio> audio;
      std::unique_ptr<Screen> screen;
      Props props = {{*audio, *screen}};
    };

    struct Audio {
      void action(itc::prop_change<&Props::test_prop1>, float tp)
      {
        val = tp;
      }
      float val = 0;

      core::audio::ProcessData<2> process(core::audio::ProcessData<1> data)
      {
        for (auto& a : data.audio) {
          a = val;
        }
        return data.with(std::array{data.audio, data.audio});
      }
    };
  } // namespace testfxengine1

  namespace testfxengine2 {
    struct Audio;
    struct Screen;

    using Sndr = EngineSender<Audio, Screen>;

    struct Props {
      Sndr sender;

      Sndr::Prop<struct test_prop_tag, float> test_prop2 = {sender, 0.f};
    };

    struct TestFXEngine2 : EffectEngine<TestFXEngine2> {
      static constexpr util::string_ref name = "Test FX Engine 2";

      std::unique_ptr<Audio> audio;
      std::unique_ptr<Screen> screen;
      Props props = {{*audio, *screen}};
    };

    struct Audio {
      void action(itc::prop_change<&Props::test_prop2>, float tp)
      {
        val = tp;
      }
      float val = 0;

      core::audio::ProcessData<2> process(core::audio::ProcessData<1> data)
      {
        for (auto& a : data.audio) {
          a = val;
        }
        return data.with(std::array{data.audio, data.audio});
      }
    };
  } // namespace testfxengine2


  TEST_CASE ("EngineDispatcher") {
    using EngDisp = EngineDispatcher<EngineType::effect, testfxengine1::TestFXEngine1, testfxengine2::TestFXEngine2>;

    EngDisp eng_disp;

    SECTION("Initially, the nullengine is selected") {
    }

    SECTION ("Serialization") {
      auto json = util::serialize(eng_disp);
      SECTION ("Serialize nullengine") {
        REQUIRE(json["current"] == nullptr);
      }
      SECTION ("Deserialization") {
        auto json = nlohmann::json{

        };
        util::deserialize(eng_disp, json);
      }
    }
  };
} // namespace otto::test
