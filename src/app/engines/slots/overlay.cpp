#include "lib/util/with_limits.hpp"

#include "lib/widget.hpp"

#include "slots.hpp"

namespace otto::engines::slots {

  struct SlotsWidget : graphics::Widget<SlotsWidget> {
    int selected = 0;
    void do_draw(skia::Canvas& ctx)
    {
      float width = bounding_box.width();
      skia::Point center = {width / 2.f, width / 2.f};
      // Background
      ctx.drawRect(SkRect(bounding_box), paints::fill(colors::grey50));
      // Text
      skia::place_text(ctx, "SOUND SLOTS", fonts::black(26), paints::fill(colors::white),
                       bounding_box.point(anchors::bottom_center), anchors::bottom_center);
    }
  };

  struct SoundSlotsScreen : OverlayBase, itc::Consumer<SoundSlotsState> {
    struct Handler : InputReducer<SoundSlotsState>, IInputLayer {
      using InputReducer::InputReducer;

      [[nodiscard]] KeySet key_mask() const noexcept override
      {
        return key_groups::enc_clicks;
      }

      void reduce(EncoderEvent e, SoundSlotsState& state) noexcept override
      {
        state.active_slot += e.steps;
      }
    };

    using Consumer::Consumer;

    SlotsWidget widget;
    void draw(skia::Canvas& ctx) noexcept override
    {
      // Background
      skia::Rect bg_rect = skia::Rect::MakeXYWH(0, 0, otto::skia::width, otto::skia::height);

      ctx.drawRect(bg_rect, paints::fill(colors::black.fade(0.5f)));

      // Content
      widget.bounding_box = {skia::Box({50, 40}, {220, 160})};
      widget.selected = state().active_slot;
      widget.draw(ctx);
    }
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
