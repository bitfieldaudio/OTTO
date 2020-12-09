#include "app/services/graphics.hpp"
#include "app/engines/synths/ottofm/state.hpp"
#include "app/input.hpp"
#include "app/services/ui_manager.hpp"
#include "lib/itc/itc.hpp"
#include "lib/util/with_limits.hpp"

#include "ottofm.hpp"

#include "app/services/config.hpp"
#include "app/services/graphics.hpp"
#include "lib/skia/skia.hpp"
#include "lib/widget.hpp"

#include <fmt/format.h>
#include <string>

#include <choreograph/Choreograph.h>

#include "widgets.hpp"

namespace otto::engines::ottofm {

  struct ModHandler final : InputReducer<State> {
    using InputReducer::InputReducer;

    void reduce(KeyPress e, State& state) noexcept final
    {
      switch (e.key) {
        case Key::blue_enc_click: state.cur_op_idx = 3; break;
        case Key::green_enc_click: state.cur_op_idx = 2; break;
        case Key::yellow_enc_click: state.cur_op_idx = 1; break;
        case Key::red_enc_click: state.cur_op_idx = 0; break;
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
        case Encoder::blue: {
          if (!state.shift) {
            state.current_op().envelope.attack += e.steps * 0.01;
          } else {
            for (auto& op : state.operators) op.envelope.attack += e.steps * 0.01;
          }
        } break;
        case Encoder::green: {
          if (!state.shift) {
            state.current_op().envelope.decay += e.steps * 0.01;
          } else {
            for (auto& op : state.operators) op.envelope.decay += e.steps * 0.01;
          }
        } break;
        case Encoder::yellow: {
          if (!state.shift) {
            state.current_op().envelope.sustain += e.steps * 0.01;
          } else {
            for (auto& op : state.operators) op.envelope.sustain += e.steps * 0.01;
          }
        } break;
        case Encoder::red: {
          if (!state.shift) {
            state.current_op().envelope.release += e.steps * 0.01;
          } else {
            for (auto& op : state.operators) op.envelope.release += e.steps * 0.01;
          }
        } break;
      }
    }
  };

  struct ADSRGraphic {
    ADSRGraphic(int idx) : index(idx) {}
    int index;
    ADSR graphic;
    skia::Anim<float> size = {0, 0.25};
    void on_state_change(const State& s) {
      const auto& env = s.operators[index].envelope;
      graphic.a = env.attack;
      graphic.d = env.decay;
      graphic.s = env.sustain;
      graphic.r = env.release;
      bool active = s.cur_op_idx == index;
      graphic.active = active;
      size = active ? 1.f : 0.f;
    }
  };

  struct ModScreen final : itc::Consumer<State>, IScreen, GraphicsDomain {
    using Consumer::Consumer;

    Operators ops;
    std::array<ADSRGraphic, 4> envelopes = {0, 1, 2, 3};
    
    float env_size = 0;

    ModScreen(itc::ChannelGroup& c) : Consumer(c)
    {
      ops.bounding_box = {{10, 30}, {50, 180}};
    }

    void on_state_change(const State& s) noexcept override
    {
      ops.algorithm_idx = s.algorithm_idx;
      ops.cur_op = s.cur_op_idx;
      for (auto& env : envelopes) env.on_state_change(s);
    }

    void draw(skia::Canvas& ctx) noexcept override
    {
      ops.draw(ctx);

      // Draw params for envelopes
      constexpr int active_y = 60;
      constexpr int not_active_y = 0;
      constexpr int y_pad = 33;
      constexpr int x_start = 70;
      constexpr int x_size = 220;
      // TODO: Can this be made constexpr?
      float step = (ctx.imageInfo().height() - 2 * y_pad - active_y - not_active_y * 3) / 3.f;

      float upper_y = y_pad;
      for (auto& env : envelopes) {
        auto& graphic = env.graphic;
        env_size = active_y * env.size + not_active_y * (1 - env.size);
        graphic.bounding_box.move_to({x_start, upper_y});
        graphic.bounding_box.resize({x_size, env.size * active_y});
        graphic.draw(ctx);
        upper_y += env_size + step;
      }
    }
  };

  ScreenWithHandler make_mod_screen(itc::ChannelGroup& chan)
  {
    return {
      .screen = std::make_unique<ModScreen>(chan),
      .handler = std::make_unique<ModHandler>(chan),
    };
  }

} // namespace otto::engines::ottofm
