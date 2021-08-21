#include <string>

#include <choreograph/Choreograph.h>
#include <fmt/format.h>

#include "lib/util/eventdivider.hpp"
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

  struct MainHandler final : InputReducer<State>, IInputLayer {
    using InputReducer::InputReducer;

    [[nodiscard]] util::enum_bitset<Key> key_mask() const noexcept override
    {
      return key_groups::enc_clicks + Key::shift;
    }

    void reduce(KeyPress e, State& state) noexcept final
    {
      switch (e.key) {
        // Operators are counted from the bottom
        case Key::blue_enc_click: break;
        case Key::green_enc_click: break;
        case Key::yellow_enc_click: break;
        case Key::red_enc_click: break;
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
        case Encoder::blue: state.param0 += e.steps * 0.002; break;
        case Encoder::green: state.param1 += e.steps * 0.01; break;
        case Encoder::yellow: state.param2 += e.steps * 0.01; break;
        case Encoder::red: state.param3 += e.steps * 0.01; break;
      }
    }

  private:
    otto::util::EventDivider<4> divider;
  };

  struct MainScreen final : itc::Consumer<State>, ScreenBase {
    using Consumer::Consumer;

    FourParams params{"Synth"};

    MainScreen(itc::Channel& c) : Consumer(c)
    {
      params.bounding_box = {{10, 30}, {270, 160}};
    }

    void on_state_change(const State& s) noexcept override
    {
      params.set({s.param0, s.param1, s.param2, s.param3});
    }

    void draw(skia::Canvas& ctx) noexcept override
    {
      params.draw(ctx);
    }
  };

  ScreenWithHandler make_main_screen(itc::Channel& chan)
  {
    return {
      .screen = std::make_unique<MainScreen>(chan),
      .input = std::make_unique<MainHandler>(chan),
    };
  }

} // namespace otto::engines::nuke
