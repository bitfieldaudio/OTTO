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

#include "ottofm.hpp"
#include "widgets.hpp"

namespace otto::engines::ottofm {

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
        case Key::page_a: state.cur_op_idx = 3; break;
        case Key::page_b: state.cur_op_idx = 2; break;
        case Key::page_c: state.cur_op_idx = 1; break;
        case Key::page_d: state.cur_op_idx = 0; break;
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
      switch (e.encoder) {
        case Encoder::blue: {
          state.algorithm_idx += divider(e);
        } break;
        case Encoder::green: {
          if (!state.shift) {
            state.current_op().ratio_idx += e.steps;
          } else {
            state.current_op().detune += e.steps * 0.01f;
          }
        } break;
        case Encoder::yellow: {
          if (!state.shift) {
            state.current_op().level += e.steps * 0.01f;
          } else {
            for (auto& op : state.operators) op.level += e.steps * 0.01f;
          }
        } break;
        case Encoder::red: {
          if (!state.shift) {
            state.current_op().shape += e.steps * 0.01;
          } else {
            for (auto& op : state.operators) op.shape += e.steps * 0.01;
          }
        } break;
      }
    }

  private:
    otto::util::EventDivider<4> divider;
  };

  // For converting number to letter
  constexpr std::array<const char*, 27> alphabet = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M",
                                                    "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"};


  struct OpLine : graphics::Widget<OpLine> {
    int index;
    const State& state;

    FractionGraphic fract;
    DetuneGraphic detune;
    LevelGraphic lev;
    WaveShapeGraphic ws;

    skia::Anim<float> expansion = {0, 0.15};
    int denom = 0;
    int numer = 0;

    OpLine(int i, const State& s) : index(i), state(s)
    {
      fract.bounding_box.move_to({0, 0});
      detune.bounding_box.move_to({60, 0});
      lev.bounding_box.move_to({120, 0});
      ws.bounding_box.move_to({180, 0});
      bounding_box.resize({240, 40});
      on_state_change(s);
    }

    void on_state_change(const State& s)
    {
      const auto& op = s.operators[index];
      bool is_active = s.cur_op_idx == index;
      expansion = is_active ? 1.f : 0.f;
      auto ratio = fractions[op.ratio_idx];
      denom = ratio.denominator;
      numer = ratio.numerator;
      fract.active = is_active && !s.shift;
      detune.active = is_active && s.shift;
      lev.active = is_active || s.shift;
      ws.active = is_active || s.shift;

      detune.value = op.detune;
      lev.value = op.level;
      ws.value = op.shape;
    }

    void do_draw(skia::Canvas& ctx)
    {
      fract.expansion = expansion;
      detune.expansion = expansion;
      lev.expansion = expansion;
      ws.expansion = expansion;

      fract.denominator = denom;
      fract.numerator = numer;

      fract.draw(ctx);
      detune.draw(ctx);
      lev.draw(ctx);
      ws.draw(ctx);
      bounding_box.resize({240, 20 + 20 * expansion});
    }
  };

  struct MainScreen final : itc::Consumer<State, AudioState>, ScreenBase {
    using Consumer::Consumer;

    Operators ops{Consumer<AudioState>::state().activity};
    std::array<OpLine, 4> op_lines = {
      // Ops are counted from the bottom
      {{3, state<State>()}, {2, state<State>()}, {1, state<State>()}, {0, state<State>()}},
    };

    sk_sp<SkTextBlob> alg_text = skia::TextBlob::MakeFromString("ALGORITHM", fonts::regular(26));
    sk_sp<SkTextBlob> alg_letter =
      skia::TextBlob::MakeFromString(alphabet[Consumer<State>::state().algorithm_idx], fonts::black(26));
    SkRect rect = skia::measureText(fonts::regular(26), "A");

    MainScreen(itc::Context& c) : Consumer(c)
    {
      ops.bounding_box = {{10, 30}, {50, 180}};
    }

    void on_state_change(const AudioState& s) noexcept override {}

    void on_state_change(const State& s) noexcept override
    {
      ops.algorithm_idx = s.algorithm_idx;
      ops.cur_op = s.cur_op_idx;
      alg_letter = skia::TextBlob::MakeFromString(alphabet[Consumer<State>::state().algorithm_idx], fonts::black(26));
      for (auto& op : op_lines) op.on_state_change(s);
    }

    void draw(skia::Canvas& ctx) noexcept override
    {
      ops.draw(ctx);

      constexpr float y_pad = 30.f;

      // Draw algorithm text

      ctx.drawTextBlob(alg_text.get(), 80, y_pad + rect.height(), paints::fill(colors::blue));
      ctx.drawTextBlob(alg_letter.get(), 300 - rect.width(), y_pad + rect.height(), paints::fill(colors::blue));

      float y_spacing = (skia::height - 2 * y_pad - 3 * 20 - 40 - rect.height()) / 4;
      float y = y_pad + rect.height() + y_spacing;

      for (auto& line : op_lines) {
        line.bounding_box.move_to({80, y});
        line.draw(ctx);
        y += line.bounding_box.height() + y_spacing;
      }
    }

    [[nodiscard]] LedSet led_mask() const noexcept override
    {
      return led_groups::pages;
    }

    void leds(LEDColorSet& colors) noexcept override
    {
      colors[Led::page_a] = LEDColor::from_skia(ops.operator_colours[0].dim((1.f - op_lines[0].expansion) * 0.7f));
      colors[Led::page_b] = LEDColor::from_skia(ops.operator_colours[1].dim((1.f - op_lines[1].expansion) * 0.7f));
      colors[Led::page_c] = LEDColor::from_skia(ops.operator_colours[2].dim((1.f - op_lines[2].expansion) * 0.7f));
      colors[Led::page_d] = LEDColor::from_skia(ops.operator_colours[3].dim((1.f - op_lines[3].expansion) * 0.7f));
    }
  };

  ScreenWithHandler make_main_screen(itc::Context& ctx)
  {
    return {
      .screen = std::make_unique<MainScreen>(ctx),
      .input = std::make_unique<MainHandler>(ctx),
    };
  }

} // namespace otto::engines::ottofm
