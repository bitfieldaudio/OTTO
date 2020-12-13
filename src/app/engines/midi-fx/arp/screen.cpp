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

#include "arp.hpp"

namespace otto::engines::arp {

  struct Handler final : InputReducer<State>, IInputLayer {
    using InputReducer::InputReducer;

    [[nodiscard]] util::enum_bitset<Key> key_mask() const noexcept override
    {
      return key_groups::enc_clicks + Key::shift;
    }

    void reduce(EncoderEvent e, State& state) noexcept final
    {
      switch (e.encoder) {
        case Encoder::blue: {
          if (e.steps > 0) {
            state.playmode++;
          } else {
            state.playmode--;
          }
        } break;
        case Encoder::green: {
          if (e.steps > 0) {
            state.octavemode++;
          } else {
            state.octavemode--;
          }
        } break;
        case Encoder::yellow: {
          state.subdivision += e.steps;
        } break;
        case Encoder::red: {
          state.note_length += e.steps * 0.01;
        } break;
      }
    }

  };

  struct Screen final : itc::Consumer<State>, ScreenBase {
    using Consumer::Consumer;

    Screen(itc::ChannelGroup& c) : Consumer(c)
    {
    }

    void on_state_change(const State& s) noexcept override
    {
    }

    void draw(skia::Canvas& ctx) noexcept override
    {
    }
  };

  ScreenWithHandler make_screen(itc::ChannelGroup& chan)
  {
    return {
      .screen = std::make_unique<Screen>(chan),
      .input = std::make_unique<Handler>(chan),
    };
  }

} // namespace otto::engines::ottofm
