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

  struct ModHandler final : LogicDomain, InputReducer<State>, IInputLayer {
    using InputReducer::InputReducer;

    [[nodiscard]] util::enum_bitset<Key> key_mask() const noexcept override
    {
      return (key_groups::enc_clicks | key_groups::pages) + Key::shift;
    }

    void reduce(KeyPress e, State& state) noexcept final
    {
      switch (e.key) {
        case Key::page_a: state.active_idx = 0; break;
        case Key::page_b: state.active_idx = 1; break;
        case Key::page_c: state.active_idx = 2; break;
        case Key::page_d: state.active_idx = 3; break;
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
            case Encoder::blue: state.attack += e.steps * 0.01; break;
            case Encoder::green: state.decay += e.steps * 0.01; break;
            case Encoder::yellow: state.sustain += e.steps * 0.01; break;
            case Encoder::red: state.release += e.steps * 0.01; break;
          }
          break;
        }
        case 1: {
          switch (e.encoder) {
            case Encoder::blue: state.filter_attack += e.steps * 0.01; break;
            case Encoder::green: state.filter_decay += e.steps * 0.01; break;
            case Encoder::yellow: state.filter_sustain += e.steps * 0.01; break;
            case Encoder::red: state.filter_amount += e.steps * 0.01; break;
          }
          break;
        }
        case 2: {
          switch (e.encoder) {
            case Encoder::blue: state.lfo_speed += e.steps * 0.01; break;
            case Encoder::green: state.lfo_type += e.steps; break;
            case Encoder::yellow: state.lfo_attack += e.steps * 0.01; break;
            case Encoder::red: state.lfo_decay += e.steps * 0.01; break;
          }
          break;
        }
        case 3: {
          switch (e.encoder) {
            case Encoder::blue: state.lfo_pitch_amount += e.steps * 0.01; break;
            case Encoder::green: state.lfo_volume_amount += e.steps * 0.01; break;
            case Encoder::yellow: state.lfo_filter_amount += e.steps * 0.01; break;
            case Encoder::red: state.lfo_osc2_pitch_amount += e.steps * 0.01; break;
          }
          break;
        }
        default: break;
      }
    }
  };


  struct ModScreen final : itc::Consumer<State>, ScreenBase {
    using Consumer::Consumer;

    ADSRGraphic volume_widget{0};
    ADSGraphic filter_widget{1};
    LFOGraphic lfo_widget{2};
    Targets targets_widget{3};

    float widget_size = 0;

    // FourParams params0{"Volume Envelope", {"Attack", "Decay", "Sustain", "Release"}};
    // FourParams params1{"Filter Envelope", {"Attack", "Decay", "Sustain", "Amount"}};
    // FourParams params2{"LFO", {"Speed", "Type", "Attack", "Decay"}};
    // FourParams params3{"Targets", {"Pitch", "Volume", "Filter", "Ring Mod"}};

    ModScreen(itc::Context& c) : Consumer(c)
    {
      volume_widget.on_state_change(Consumer<State>::state());
      filter_widget.on_state_change(Consumer<State>::state());
      lfo_widget.on_state_change(Consumer<State>::state());
      targets_widget.on_state_change(Consumer<State>::state());
      // params0.bounding_box = {{10, 30}, {270, 160}};
      // params1.bounding_box = {{10, 30}, {270, 160}};
      // params2.bounding_box = {{10, 30}, {270, 160}};
      // params3.bounding_box = {{10, 30}, {270, 160}};
    }

    void on_state_change(const State& s) noexcept override
    {
      active_idx = s.active_idx;
      volume_widget.on_state_change(s);
      filter_widget.on_state_change(s);
      lfo_widget.on_state_change(s);
      targets_widget.on_state_change(s);
      // params0.set({s.envparam0_0, s.envparam0_1, s.envparam0_2, s.envparam0_3});
      // params1.set({s.envparam1_0, s.envparam1_1, s.envparam1_2, s.envparam1_3});
      // params2.set({s.envparam2_0, s.envparam2_1, s.envparam2_2, s.envparam2_3});
      // params3.set({s.envparam3_0, s.envparam3_1, s.envparam3_2, s.envparam3_3});
    }

    void draw_mod_widget(skia::Canvas& ctx, auto& graphic, skia::Point pos, skia::Vector size, float expansion) noexcept
    {
      graphic.bounding_box.move_to({pos.x(), pos.y()});
      graphic.bounding_box.resize({size.x(), size.y()});
      graphic.expanded = expansion;
      graphic.draw(ctx);
    }

    void draw(skia::Canvas& ctx) noexcept override
    {
      // Draw params for widgets
      constexpr int active_y = 50;
      constexpr int not_active_y = 15;
      constexpr int y_pad = 33;
      constexpr int x_start = 20;
      constexpr int x_size = 280;
      float step = (skia::height - 2 * y_pad - active_y - not_active_y * 3) / 3.f;

      float upper_y = 12.f + y_pad;

      skia::place_text(ctx, "VOLUME ENVELOPE", fonts::regular(22), colors::grey50.fade(1.f - volume_widget.size), {x_start, 14.f});
      skia::place_text(ctx, "FILTER ENVELOPE", fonts::regular(22), colors::grey50.fade(1.f - filter_widget.size), {x_start, 14.f});
      skia::place_text(ctx, "LFO", fonts::regular(22), colors::grey50.fade(1.f - lfo_widget.size), {x_start, 14.f});
      skia::place_text(ctx, "LFO TARGETS", fonts::regular(22), colors::grey50.fade(1.f - targets_widget.expansion),
                       {x_start, 14.f});

      // Volume
      auto& volume_graphic = volume_widget.graphic;
      widget_size = active_y * volume_widget.size + not_active_y * (1 - volume_widget.size);
      draw_mod_widget(ctx, volume_graphic, {x_start, upper_y}, {x_size, widget_size}, volume_widget.size);
      upper_y += widget_size + step;

      // Filter
      auto& filter_graphic = filter_widget.graphic;
      widget_size = active_y * filter_widget.size + not_active_y * (1 - filter_widget.size);
      draw_mod_widget(ctx, filter_graphic, {x_start, upper_y}, {x_size, widget_size}, filter_widget.size);
      upper_y += widget_size + step;

      // LFO
      auto& lfo_graphic = lfo_widget.graphic;
      widget_size = active_y * lfo_widget.size + not_active_y * (1 - lfo_widget.size);
      draw_mod_widget(ctx, lfo_graphic, {x_start, upper_y}, {x_size, widget_size}, lfo_widget.size);
      upper_y += widget_size + step;

      // Targets
      widget_size = active_y * targets_widget.expansion + not_active_y * (1 - targets_widget.expansion);
      draw_mod_widget(ctx, targets_widget, {x_start, upper_y}, {x_size, widget_size}, targets_widget.expansion);
    }

    [[nodiscard]] LedSet led_mask() const noexcept override
    {
      return led_groups::pages;
    }

    void leds(LEDColorSet& leds) noexcept override
    {
      leds[Led::page_a] = LEDColor::from_skia(colors::white.dim(1.f - 0.5f * volume_widget.size));
      leds[Led::page_b] = LEDColor::from_skia(colors::white.dim(1.f - 0.5f * filter_widget.size));
      leds[Led::page_c] = LEDColor::from_skia(colors::white.dim(1.f - 0.5f * lfo_widget.size));
      leds[Led::page_d] = LEDColor::from_skia(colors::white.dim(1.f - 0.5f * targets_widget.expansion));
    }

  private:
    int active_idx = 0;
  };

  ScreenWithHandler make_mod_screen(itc::Context& chan)
  {
    return {
      .screen = std::make_unique<ModScreen>(chan),
      .input = std::make_unique<ModHandler>(chan),
    };
  }

} // namespace otto::engines::nuke
