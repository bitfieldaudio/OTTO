#pragma once
#include "core/engine/engine.hpp"
#include "core/ui/screen.hpp"

namespace otto::core::engine {

  struct OffScreen : ui::Screen {
    void draw(ui::vg::Canvas& ctx) override;
  };

  /// An engine representing an off engine.
  ///
  /// For synths, the audio processing should just return an empty buffer, and for
  /// fx it returns the input. Any others should be fairly obvious then.
  template<EngineType ET>
  struct OffEngine;

  template<>
  struct OffEngine<EngineType::effect> : EffectEngine<OffEngine<EngineType::effect>> {
    static constexpr util::string_ref name = "OFF";
    struct Props {
      DECL_REFLECTION_EMPTY(Props);
    } props;
    OffEngine(itc::ActionChannel);

    ui::ScreenAndInput screen() noexcept
    {
      return {_screen, this};
    }
		struct Audio {
      audio::ProcessData<2> process(audio::ProcessData<1> data) noexcept;
		} audio_;
		Audio* const audio = &audio_;

  private:
    OffScreen _screen;
  };

  template<>
  struct OffEngine<EngineType::arpeggiator> : ArpeggiatorEngine<OffEngine<EngineType::arpeggiator>> {
    static constexpr util::string_ref name = "OFF";
    struct Props {
      DECL_REFLECTION_EMPTY(Props);
    } props;
    OffEngine(itc::ActionChannel);

    ui::ScreenAndInput screen() noexcept
    {
      return {_screen, this};
    }

		struct Audio {
      audio::ProcessData<0> process(audio::ProcessData<0> data) noexcept;
		} audio_;
		Audio* const audio = &audio_;

  private:
    OffScreen _screen;
  };

} // namespace otto::core::engine
