#include "app/services/graphics.hpp"
#include "app/input.hpp"
#include "lib/itc/itc.hpp"
#include "lib/util/with_limits.hpp"

#include "ottofm.hpp"

using namespace otto;

namespace otto::engines::ottofm {

  struct Screen final : services::Graphics::Consumer<State>, IScreen {
    using Consumer::Consumer;

    void draw(SkCanvas& ctx) noexcept override
    {
      SkPaint paint;
      paint.setAntiAlias(true);
      paint.setColor(SK_ColorWHITE);
      paint.setStyle(SkPaint::kFill_Style);
      ctx.drawCircle({160, 120}, 100.f, paint);
    }
  };

  struct Handler final : InputReducer<State> {
    void reduce(KeyPress e, State& state) noexcept final
    {
      switch (e.key) {
        case Key::blue_enc_click: state.cur_op_idx = 3; break;
        case Key::green_enc_click: state.cur_op_idx = 2; break;
        case Key::yellow_enc_click: state.cur_op_idx = 1; break;
        case Key::red_enc_click: state.cur_op_idx = 0; break;
        default: break;
      }
    }

    void reduce(EncoderEvent e, State& state) noexcept final
    {
      // TODO
      bool shift = false;
      switch (e.encoder) {
        case Encoder::blue: {
          state.algorithm_idx += e.steps;
        } break;
        case Encoder::green: {
          if (!shift) {
            state.current_op().ratio_idx += e.steps;
          } else {
            state.current_op().detune += e.steps * 0.01;
          }
        } break;
        case Encoder::yellow: {
          if (!shift) {
            state.current_op().level += e.steps * 0.01;
          } else {
            for (auto& op : state.operators) op.level += e.steps * 0.01;
          }
        } break;
        case Encoder::red: {
          if (!shift) {
            state.current_op().feedback += e.steps * 0.01;
          } else {
            for (auto& op : state.operators) op.feedback += e.steps * 0.01;
          }
        } break;
      }
    }
  };


} // namespace otto::engines::ottofm
