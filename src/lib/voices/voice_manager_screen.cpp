#include "voice_manager.hpp"

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

namespace otto::voices {

  struct Handler final : LogicDomain, InputReducer<VoicesState>, IInputLayer {
    using InputReducer::InputReducer;

    [[nodiscard]] util::enum_bitset<Key> key_mask() const noexcept override
    {
      return key_groups::enc_clicks + Key::shift;
    }

    void reduce(EncoderEvent e, VoicesState& state) noexcept final
    {
      switch (e.encoder) {
        case Encoder::blue: {
          state.play_mode += pm_divider(e);
        } break;
        case Encoder::green: {
          switch (state.play_mode) {
            case PlayMode::poly: state.rand += e.steps * 0.01f; break;
            case PlayMode::mono: state.sub += e.steps * 0.01f; break;
            case PlayMode::unison: state.detune += e.steps * 0.01f; break;
            case PlayMode::duo: state.interval += interval_divider(e); break;
          }
        } break;
        case Encoder::yellow: {
          state.portamento += e.steps * 0.01;
        } break;
        case Encoder::red: {
          if (e.steps < 0 && !state.legato && !state.retrig) break;
          if (e.steps > 0 && state.legato && state.retrig) break;
          if (e.steps > 0 && state.legato) {
            state.retrig = !state.retrig;
          } else if (e.steps < 0 && !state.legato) {
            state.retrig = !state.retrig;
          }
          state.legato = !state.legato;
        } break;
      }
    }

  private:
    otto::util::EventDivider<4> pm_divider;
    otto::util::EventDivider<4> interval_divider;
  };

  static std::string aux_setting(PlayMode pm) noexcept
  {
    switch (pm) {
      case PlayMode::poly: return "RANDOM";
      case PlayMode::mono: return "SUB OSC.";
      case PlayMode::unison: return "DETUNE";
      case PlayMode::duo: return "INTERVAL";
    };
    return "";
  }



  static std::string playmode_string(PlayMode pm) noexcept
  {
    switch (pm) {
      case PlayMode::poly: return "POLY";
      case PlayMode::mono: return "MONO";
      case PlayMode::unison: return "UNISON";
      case PlayMode::duo: return "DUO";
    };
    return "";
  }

  struct VoiceModes : otto::graphics::Widget<VoiceModes> {
    int active_line;
    float rand;
    float sub;
    int interval;
    float detune;
    VoiceModes(int a, float r, float s, int i, float d) : active_line(a), rand(r), sub(s), interval(i), detune(d) {}

    void do_draw(skia::Canvas& ctx)
    {
      float height = bounding_box.height();
      float width = bounding_box.width();
      // Set up x-coordinates
      float mode_text_x = width * 0.03f;
      float division_x = width * 0.382f; // Golden ratio
      float aux_text_x = width * 0.412f;
      float aux_value_x = width * 0.97f;

      // Set up y-coordinates
      float subject_height = 15.f;
      float line_size = (height - subject_height) / 4;

      auto aux_value = [&](PlayMode pm) -> std::string {
        switch (pm) {
          case PlayMode::poly: return fmt::format("{:.2f}", rand);
          case PlayMode::mono: return fmt::format("{:.2f}", sub);
          case PlayMode::unison: return fmt::format("{:.2f}", detune);
          case PlayMode::duo: return fmt::format("{:+d}", interval);
        };
        return "";
      };
      auto draw_line = [&](skia::Canvas& ctx, bool active, float y, int i) {
        // Background squares
        if (active) {
          skia::RRect left_rect = skia::RRect::MakeRectXY(skia::Rect::MakeXYWH(0, y, width, line_size), 10.f, 10.f);
          ctx.drawRRect(left_rect, paints::fill(colors::blue));
          ctx.drawRRect(left_rect, paints::stroke(colors::black, 1.f));

          skia::RRect right_rect =
            skia::RRect::MakeRectXY(skia::Rect::MakeXYWH(division_x, y, width - division_x, line_size), 10.f, 10.f);
          ctx.drawRRect(right_rect, paints::fill(colors::green.dim(0.3f)));
          ctx.drawRRect(right_rect, paints::stroke(colors::black, 4.f));
        }

        auto pm = magic_enum::enum_value<PlayMode>(i);
        skia::place_text(ctx, playmode_string(pm), fonts::medium(24),
                         paints::fill(active ? colors::white : colors::grey50), {mode_text_x, y + line_size * 0.5f},
                         anchors::middle_left);
        skia::place_text(ctx, aux_setting(pm), fonts::medium(24), paints::fill(active ? colors::white : colors::grey50),
                         {aux_text_x, y + line_size * 0.5f}, anchors::middle_left);
        skia::place_text(ctx, aux_value(pm), fonts::medium(24), paints::fill(active ? colors::white : colors::grey50),
                         {aux_value_x, y + line_size * 0.5f}, anchors::middle_right);
      };

      // Top text
      skia::Paint p = paints::fill(colors::white);
      skia::place_text(ctx, "MODE", fonts::regular(18.f), p, {mode_text_x, 0}, anchors::top_left);
      skia::place_text(ctx, "SETTING", fonts::regular(18.f), p, {aux_text_x, 0}, anchors::top_left);
      skia::place_text(ctx, "VALUE", fonts::regular(18.f), p, {aux_value_x, 0}, anchors::top_right);
      // Modes
      for (int i = 0; i < 4; i++) {
        draw_line(ctx, i == active_line, subject_height + float(i) * line_size, i);
      }
    }
  };

  struct Portamento : otto::graphics::Widget<Portamento> {
    float value;
    Portamento(float v) : value(v) {}

    void do_draw(skia::Canvas& ctx)
    {
      float height = bounding_box.height();
      float width = bounding_box.width();
      // Yellow Main Box (Fill)
      skia::RRect main_box = skia::RRect::MakeRectXY(skia::Rect::MakeXYWH(0, 0, width, height), 10.f, 10.f);
      ctx.drawRRect(main_box, paints::fill(colors::yellow));
      // Black covering box
      skia::Rect cover_box = skia::Rect::MakeXYWH(width * value, 0, width * (1 - value), height);
      ctx.drawRect(cover_box, paints::fill(colors::black));
      // Yellow Main Box (Stroke)
      ctx.drawRRect(main_box, paints::stroke(colors::yellow, 3.f));

      // Text
      skia::Paint p = paints::fill(colors::black);
      skia::place_text(ctx, "PORTAMENTO TIME", fonts::medium(18), p, {width / 2.f, height / 2.f}, anchors::center);
      ctx.save();
      ctx.clipRect(cover_box);
      p.setColor(colors::white);
      skia::place_text(ctx, "PORTAMENTO TIME", fonts::medium(18), p, {width / 2.f, height / 2.f}, anchors::center);
      ctx.restore();
    }
  };

  struct LegatoGraphic : otto::graphics::Widget<LegatoGraphic> {
    int value;
    LegatoGraphic(int v) : value(v) {}

    void do_draw(skia::Canvas& ctx)
    {
      float height = bounding_box.height();
      float width = bounding_box.width();

      skia::Paint p = paints::fill(colors::white);
      // Text
      skia::place_text(ctx, "LEGATO", fonts::regular(18), p, {0, 0}, anchors::top_left);


      auto set_color = [&](int i) {
        if (i == value) {
          p.setColor(colors::red);
        } else {
          p.setColor(colors::grey50);
        }
      };
      set_color(0);
      skia::place_text(ctx, "OFF", fonts::medium(24), p, {0.f, height}, anchors::bottom_left);
      set_color(1);
      skia::place_text(ctx, "ENV.", fonts::medium(24), p, {width * 0.25f, height}, anchors::bottom_left);
      set_color(2);
      skia::place_text(ctx, "PORT.", fonts::medium(24), p, {width * 0.51f, height}, anchors::bottom_left);
      set_color(3);
      skia::place_text(ctx, "BOTH", fonts::medium(24), p, {width, height}, anchors::bottom_right);
    }
  };

  struct VoicesScreen final : itc::Consumer<VoicesState>, ScreenBase {
    using Consumer::Consumer;

    VoiceModes vms{2, 0.0f, 0.0f, 3, 0.0f};
    Portamento port{0.3};
    LegatoGraphic leg{2};

    VoicesScreen(itc::Context& c) : Consumer(c)
    {
      vms.bounding_box.move_to({10, 10});
      vms.bounding_box.resize({300, 130});
      port.bounding_box.move_to({10, 150});
      port.bounding_box.resize({300, 30});
      leg.bounding_box.move_to({10, 193});
      leg.bounding_box.resize({300, 37});
    }

    void on_state_change(const VoicesState& s) noexcept override
    {
      vms.active_line = s.play_mode.index();
      vms.rand = s.rand;
      vms.sub = s.sub;
      vms.detune = s.detune;
      vms.interval = s.interval;

      port.value = s.portamento;

      leg.value = static_cast<int>(s.legato) + 2 * static_cast<int>(s.retrig);
    }

    void draw(skia::Canvas& ctx) noexcept override
    {
      vms.draw(ctx);
      port.draw(ctx);
      leg.draw(ctx);
    }
  };

  ScreenWithHandler make_voices_screen(itc::Context& ctx)
  {
    return {
      .screen = std::make_unique<VoicesScreen>(ctx),
      .input = std::make_unique<Handler>(ctx),
    };
  }

} // namespace otto::voices
