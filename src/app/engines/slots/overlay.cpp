#include "lib/util/with_limits.hpp"

#include "lib/widget.hpp"

#include "app/input.hpp"

#include "slots.hpp"

namespace otto::engines::slots {

  constexpr int num_colors = 6;
  constexpr SkColor wheel_colors[num_colors + 1] = {SK_ColorRED,  SK_ColorYELLOW,  SK_ColorGREEN, SK_ColorCYAN,
                                                    SK_ColorBLUE, SK_ColorMAGENTA, SK_ColorRED};
  skia::Color f_to_color(float color_f)
  {
    std::size_t base_color_idx = std::floor(color_f * (num_colors + 1));
    auto base_color = skia::Color(wheel_colors[base_color_idx]);
    auto blend_color = skia::Color(wheel_colors[(base_color_idx + 1) % (num_colors + 1)]);
    float aux;
    return base_color.mix(blend_color, std::modf(color_f * (num_colors + 1), &aux));
  }

  struct SlotsWidget : graphics::Widget<SlotsWidget> {
    float selected_color_f = 0.f; // [0,1]
    skia::Color selected_color = skia::Color(SK_ColorRED);

    void do_draw(skia::Canvas& ctx)
    {
      float width = bounding_box.width();
      float height = bounding_box.height();
      skia::Point center = {width / 2.f, width / 2.f};
      // Background
      ctx.drawRRect(skia::RRect::MakeRectXY(bounding_box, 8, 8), paints::fill(colors::grey70));

      constexpr float outer_radius = 20;
      constexpr float middle_radius = 12;
      constexpr float inner_radius = 10;
      constexpr SkScalar text_offset = outer_radius + 6;
      // Blue Copy/Paste
      skia::Point copy_location = {width * 0.25f, height * 0.382};
      ctx.drawCircle(copy_location, middle_radius, paints::fill(colors::blue.fade(0.5f)));
      ctx.drawCircle(copy_location, inner_radius, paints::fill(colors::blue));
      skia::place_text(ctx, "COPY/PASTE", fonts::medium(14), paints::fill(colors::white),
                       {copy_location.x(), copy_location.y() + text_offset}, anchors::top_center);


      // Color wheel
      skia::Point color_wheel_location = {width * 0.75f, height * 0.382};
      skia::Paint paint;
      paint.setAntiAlias(true);
      paint.setShader(skia::GradientShader::MakeSweep(color_wheel_location.x(), color_wheel_location.y(), wheel_colors,
                                                      nullptr, num_colors + 1));
      ctx.drawCircle(color_wheel_location, outer_radius, paint);
      // Black border
      ctx.drawCircle(color_wheel_location, middle_radius, paints::fill(colors::black));
      // Colored center
      selected_color = f_to_color(selected_color_f);
      ctx.drawCircle(color_wheel_location, inner_radius, paints::fill(selected_color));
      skia::place_text(ctx, "COLOR", fonts::medium(14), paints::fill(colors::white),
                       {color_wheel_location.x(), color_wheel_location.y() + text_offset}, anchors::top_center);
    }
  };

  std::uint8_t channel_number_for(Key k)
  {
    return static_cast<std::uint8_t>(k) - static_cast<std::uint8_t>(Key::channel0);
  }

  struct SoundSlotsScreen : OverlayBase, itc::Consumer<SoundSlotsState> {
    using Consumer::Consumer;
    struct Handler : InputReducer<SoundSlotsState>, IInputLayer {
      using InputReducer::InputReducer;

      [[nodiscard]] KeySet key_mask() const noexcept override
      {
        return key_groups::enc_clicks | key_groups::channel;
      }

      void reduce(KeyPress e, SoundSlotsState& state) noexcept final
      {
        if (e.key == Key::blue_enc_click) {
          // TODO: Copy/paste
        } else if (key_groups::channel.test(e.key)) {
          state.active_idx = channel_number_for(e.key);
        }
      }

      void reduce(EncoderEvent e, SoundSlotsState& state) noexcept override
      {
        switch (e.encoder) {
          case Encoder::green: [[fallthrough]];
          case Encoder::yellow: [[fallthrough]];
          case Encoder::red: {
            state.slot_states[state.active_idx].selected_color_f += e.steps * 0.01f;
            break;
          }
          default: break;
        }
      }
    };

    [[nodiscard]] LedSet led_mask() const noexcept override
    {
      return led_groups::channel;
    }
    void leds(LEDColorSet& led_color) noexcept override
    {
      for (auto& led : util::enum_values<Led>()) {
        if (led_groups::channel.test(led)) {
          led_color[led] = LEDColor::from_skia(
            f_to_color(state().slot_states[channel_number_for(key_from(led).value())].selected_color_f));
        }
      }
    }


    SoundSlotsScreen(itc::Channel& c) : Consumer(c)
    {
      // Init Screen
      widget.bounding_box = {skia::Box({50, 80}, {220, 80})};
      widget.selected_color_f = state().slot_states[state().active_idx].selected_color_f;
      // Init LEDs
    }

    void draw(skia::Canvas& ctx) noexcept override
    {
      // Background
      skia::Rect bg_rect = skia::Rect::MakeXYWH(0, 0, otto::skia::width, otto::skia::height);
      ctx.drawRect(bg_rect, paints::fill(colors::black.fade(0.5f)));

      // Content
      widget.selected_color_f = state().slot_states[state().active_idx].selected_color_f;
      widget.draw(ctx);
    }

  private:
    SlotsWidget widget;
  };

  struct Logic : ILogic, itc::Producer<SoundSlotsState> {
    Logic(itc::Context& ctx) : Producer(ctx) {}
  };

  SoundSlots SoundSlots::make(itc::Context& ctx)
  {
    return {
      .logic = std::make_unique<Logic>(ctx),
      .overlay_screen =
        {
          std::make_unique<SoundSlotsScreen>(ctx),
          std::make_unique<SoundSlotsScreen::Handler>(ctx),
        },
    };
  }

} // namespace otto::engines::slots
