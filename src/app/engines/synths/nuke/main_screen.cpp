#include <string>

#include <choreograph/Choreograph.h>
#include <fmt/format.h>

#include "lib/util/eventdivider.hpp"
#include "lib/util/tweaks.hpp"
#include "lib/util/with_limits.hpp"

#include "lib/itc/itc.hpp"
#include "lib/skia/skia.hpp"
#include "lib/widget.hpp"

#include "app/input.hpp"
#include "app/services/config.hpp"
#include "app/services/graphics.hpp"
#include "app/services/ui_manager.hpp"

#include "nuke.hpp"
#include "widgets.hpp"

namespace otto::engines::nuke {

  struct MainHandler final : LogicDomain, InputReducer<State>, IInputLayer {
    using InputReducer::InputReducer;

    [[nodiscard]] util::enum_bitset<Key> key_mask() const noexcept override
    {
      return (key_groups::enc_clicks | key_groups::pages) + Key::shift;
    }


    void reduce(KeyPress e, State& state) noexcept final
    {
      switch (e.key) {
        // Operators are counted from the bottom
        case Key::page_a: state.mode = 0; break;
        case Key::page_b: state.mode = 1; break;
        case Key::page_c: state.mode = 2; break;
        case Key::page_d: state.mode = 3; break;
        case Key::shift: state.shift = true; break;
        default: break;
      }
    }

    void reduce(KeyRelease e, State& state) noexcept final
    {
      switch (e.key) {
        case Key::shift: state.shift = false; break;
        default: break;
      }
    }

    void reduce(EncoderEvent e, State& state) noexcept final
    {
      // TODO
      switch (e.encoder) {
        case Encoder::blue: state.osc2_pitch += e.steps * 0.002; break;
        case Encoder::green: state.osc_mix += e.steps * 0.01; break;
        case Encoder::yellow: state.cutoff += e.steps * 0.01; break;
        case Encoder::red: state.resonance += e.steps * 0.01; break;
      }
    }

  private:
    otto::util::EventDivider<4> divider;
  };

  struct MainScreen final : itc::Consumer<State>, ScreenBase {
    using Consumer::Consumer;

    FourParams params{"Synth", {"Osc2", "Mix", "Cutoff", "Resonance"}};

    MainScreen(itc::Context& c) : Consumer(c)
    {
      params.bounding_box = {{10, 30}, {270, 160}};
    }

    void on_state_change(const State& s) noexcept override
    {
      params.set({s.osc2_pitch, s.osc_mix, s.cutoff, s.resonance});
    }

    void draw(skia::Canvas& ctx) noexcept override
    {
      params.bounding_box = {{util::tweak("nuke_pad", 10.f), 30}, {270, 160}};
      params.draw(ctx);
    }
  };

  ScreenWithHandler make_main_screen(itc::Context& chan)
  {
    return {
      .screen = std::make_unique<MainScreen>(chan),
      .input = std::make_unique<MainHandler>(chan),
    };
  }

} // namespace otto::engines::nuke
