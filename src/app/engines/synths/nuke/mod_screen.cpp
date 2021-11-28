#include <string>

#include <choreograph/Choreograph.h>
#include <fmt/format.h>

#include "lib/util/with_limits.hpp"

#include "lib/itc/itc.hpp"
#include "lib/skia/skia.hpp"
#include "lib/widget.hpp"

#include "app/engines/synths/nuke/state.hpp"
#include "app/input.hpp"
#include "app/services/config.hpp"
#include "app/services/graphics.hpp"
#include "app/services/ui_manager.hpp"

#include "nuke.hpp"
#include "widgets.hpp"

namespace otto::engines::nuke {

  struct ModHandler final : InputReducer<State>, IInputLayer {
    using InputReducer::InputReducer;

    [[nodiscard]] util::enum_bitset<Key> key_mask() const noexcept override
    {
      return key_groups::enc_clicks + Key::shift;
    }

    void reduce(KeyPress e, State& state) noexcept final
    {
      switch (e.key) {
        // Operators are counted from the bottom
        case Key::blue_enc_click: state.active_idx = 0; break;
        case Key::green_enc_click: state.active_idx = 1; break;
        case Key::yellow_enc_click: state.active_idx = 2; break;
        case Key::red_enc_click: state.active_idx = 3; break;
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
      switch (state.active_idx) {
        case 0: {
          switch (e.encoder) {
            case Encoder::blue: state.envparam0_0 += e.steps * 0.01; break;
            case Encoder::green: state.envparam0_1 += e.steps * 0.01; break;
            case Encoder::yellow: state.envparam0_2 += e.steps * 0.01; break;
            case Encoder::red: state.envparam0_3 += e.steps * 0.01; break;
          }
          break;
        }
        case 1: {
          switch (e.encoder) {
            case Encoder::blue: state.envparam1_0 += e.steps * 0.01; break;
            case Encoder::green: state.envparam1_1 += e.steps * 0.01; break;
            case Encoder::yellow: state.envparam1_2 += e.steps * 0.01; break;
            case Encoder::red: state.envparam1_3 += e.steps * 0.01; break;
          }
          break;
        }
        case 2: {
          switch (e.encoder) {
            case Encoder::blue: state.envparam2_0 += e.steps * 0.01; break;
            case Encoder::green: state.envparam2_1 += e.steps; break;
            case Encoder::yellow: state.envparam2_2 += e.steps * 0.01; break;
            case Encoder::red: state.envparam2_3 += e.steps * 0.01; break;
          }
          break;
        }
        case 3: {
          switch (e.encoder) {
            case Encoder::blue: state.envparam3_0 += e.steps * 0.01; break;
            case Encoder::green: state.envparam3_1 += e.steps * 0.01; break;
            case Encoder::yellow: state.envparam3_2 += e.steps * 0.01; break;
            case Encoder::red: state.envparam3_3 += e.steps * 0.01; break;
          }
          break;
        }
        default: break;
      }
    }
  };

  struct ModScreen final : itc::Consumer<State>, ScreenBase {
    using Consumer::Consumer;

    FourParams params0{"Volume Envelope", {"Attack", "Decay", "Sustain", "Release"}};
    FourParams params1{"Filter Envelope", {"Attack", "Decay", "Sustain", "Amount"}};
    FourParams params2{"LFO", {"Speed", "Type", "Attack", "Decay"}};
    FourParams params3{"Targets", {"Pitch", "Volume", "Filter", "Ring Mod"}};

    ModScreen(itc::Channel& c) : Consumer(c)
    {
      params0.bounding_box = {{10, 30}, {270, 160}};
      params1.bounding_box = {{10, 30}, {270, 160}};
      params2.bounding_box = {{10, 30}, {270, 160}};
      params3.bounding_box = {{10, 30}, {270, 160}};
    }

    void on_state_change(const State& s) noexcept override
    {
      active_idx = s.active_idx;
      params0.set({s.envparam0_0, s.envparam0_1, s.envparam0_2, s.envparam0_3});
      params1.set({s.envparam1_0, s.envparam1_1, s.envparam1_2, s.envparam1_3});
      params2.set({s.envparam2_0, s.envparam2_1, s.envparam2_2, s.envparam2_3});
      params3.set({s.envparam3_0, s.envparam3_1, s.envparam3_2, s.envparam3_3});
    }

    void draw(skia::Canvas& ctx) noexcept override
    {
      switch (active_idx) {
        case 0: params0.draw(ctx); break;
        case 1: params1.draw(ctx); break;
        case 2: params2.draw(ctx); break;
        case 3: params3.draw(ctx); break;
        default: break;
      }
    }

  private:
    int active_idx = 0;
  };

  ScreenWithHandler make_mod_screen(itc::Channel& chan)
  {
    return {
      .screen = std::make_unique<ModScreen>(chan),
      .input = std::make_unique<ModHandler>(chan),
    };
  }

} // namespace otto::engines::nuke
