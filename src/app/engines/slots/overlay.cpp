#include "lib/util/change_checker.hpp"
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
    int selected_index = 0;
    float selected_color_f = 0.f; // [0,1]
    skia::Color selected_color = skia::Color(SK_ColorRED);
    std::optional<int> clipboard;

    void do_draw(skia::Canvas& ctx)
    {
      float width = bounding_box.width();
      float height = bounding_box.height();
      skia::Point center = {width / 2.f, width / 2.f};
      // Background
      constexpr float rect_radius = 4;
      ctx.drawRRect(skia::RRect::MakeRectXY(bounding_box, rect_radius, rect_radius), paints::fill(colors::black));
      ctx.drawRRect(skia::RRect::MakeRectXY(bounding_box, rect_radius, rect_radius),
                    paints::stroke(colors::yellow, 3.f));

      skia::place_text(ctx, fmt::format("SLOT {}", selected_index + 1), fonts::medium(22), colors::white,
                       {width / 2, 16}, anchors::top_center);

      constexpr float outer_radius = 20;
      constexpr float middle_radius = 12;
      constexpr float inner_radius = 10;
      constexpr SkScalar text_offset = outer_radius + 6;
      const float btn_center = height * 0.55f;
      // Blue Copy/Paste
      skia::Point copy_location = {width * 0.25f, btn_center};
      ctx.drawCircle(copy_location, middle_radius, paints::fill(colors::blue.fade(0.5f)));
      ctx.drawCircle(copy_location, inner_radius, paints::fill(colors::blue));

      if (clipboard) {
        skia::place_text(ctx, "PASTE", fonts::medium(14), paints::fill(colors::white),
                         {copy_location.x(), copy_location.y() + text_offset}, anchors::top_center);
      } else {
        skia::place_text(ctx, "COPY", fonts::medium(14), paints::fill(colors::white),
                         {copy_location.x(), copy_location.y() + text_offset}, anchors::top_center);
      }


      // Color wheel
      skia::Point color_wheel_location = {width * 0.75f, btn_center};
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

  struct SoundSlotsScreen : OverlayBase, itc::Consumer<SoundSlotsState> {
    using Consumer::Consumer;
    struct Handler final : LogicDomain,
                           itc::Producer<SoundSlotsState>,
                           itc::Sender<action::Type>,
                           IInputLayer,
                           InputHandler {
      Handler(itc::Context& ctx) : Producer(ctx), Sender(ctx) {}

      [[nodiscard]] KeySet key_mask() const noexcept override
      {
        return key_groups::enc_clicks | key_groups::channel;
      }

      void handle(KeyPress e) noexcept final
      {
        if (e.key == Key::blue_enc_click) {
          if (state().clipboard) {
            send(action::CopySlot{.source = *state().clipboard, .destination = state().active_idx});
            commit([&](SoundSlotsState& state) { state.clipboard = std::nullopt; });
          } else {
            commit([&](SoundSlotsState& state) { state.clipboard = state.active_idx; });
          }
        } else if (auto chan = channel_number_for(e.key)) {
          commit([&](auto& state) { state.active_idx = *chan; });
        }
      }

      void handle(EncoderEvent e) noexcept override
      {
        switch (e.encoder) {
          case Encoder::green: [[fallthrough]];
          case Encoder::yellow: [[fallthrough]];
          case Encoder::red: {
            commit([&](auto& state) {
              state.slot_states[state.active_idx].selected_color_f += float(e.steps) * 0.01f; // Internal
            });
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
      for (const auto& led : util::enum_values<Led>()) {
        if (led_groups::channel.test(led)) {
          auto key = *key_from(led); // This is certain to contain a value
          auto channel_idx = *channel_number_for(key);
          led_color[led] = LEDColor::from_skia(f_to_color(state().slot_states[channel_idx].selected_color_f)
                                                 .dim(channel_idx == state().active_idx ? 0 : 0.75));
        }
      }
    }

    SoundSlotsScreen(itc::Context& c) : Consumer(c)
    {
      // Init Screen
      widget.bounding_box = {skia::Box({50, 60}, {220, 120})};
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
      widget.selected_index = state().active_idx;
      widget.clipboard = state().clipboard;
      widget.draw(ctx);
    }

  private:
    SlotsWidget widget;
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
