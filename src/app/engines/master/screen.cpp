#include "lib/util/with_limits.hpp"

#include "lib/widget.hpp"

#include "app/domains/logic.hpp"
#include "app/drivers/audio_driver.hpp"

#include "master.hpp"

namespace otto::engines::master {

  struct VolumeWidget : graphics::Widget<VolumeWidget> {
    float value = 0.5;
    void do_draw(skia::Canvas& ctx)
    {
      float width = bounding_box.width();
      skia::Box dial_box = bounding_box.resized({width, width}, anchors::top_left);
      skia::Point center = {width / 2.f, width / 2.f};
      float marker_radius = width * 0.4f;
      float rotation = (value - 0.5f) * 270;
      // Text
      skia::place_text(ctx, "VOLUME", fonts::black(26), paints::fill(colors::white),
                       bounding_box.point(anchors::bottom_center), anchors::bottom_center);

      // Dot
      ctx.drawCircle(center.x(), center.y(), 4.f, paints::fill(colors::green));

      skia::saved(ctx, [&] {
        skia::rotate(ctx, rotation, center);
        skia::Path path;
        path.moveTo(center);
        path.lineTo(center - skia::Vector{0, marker_radius});
        ctx.drawPath(path, paints::stroke(colors::green));
      });

      // Outer circle
      skia::Path path;
      path.arcTo(dial_box, -90.f - 0.5f * 270, 270, false);
      ctx.drawPath(path, paints::stroke(colors::white, 3.f));

      // Middle circle
      path.reset();
      path.arcTo(dial_box.resized({width * 0.6f, width * 0.6f}, anchors::center), -90.f - 0.5f * 270, 270, false);
      ctx.drawPath(path, paints::stroke(colors::green.fade(0.9), 3.f));

      // Inner circle
      path.reset();
      path.arcTo(dial_box.resized({width * 0.3f, width * 0.3f}, anchors::center), -90.f - 0.5f * 270, 270, false);
      ctx.drawPath(path, paints::stroke(colors::green.fade(0.7), 3.f));
    }
  };

  struct MasterScreen : ScreenBase, itc::Consumer<MasterState> {
    struct Handler : LogicDomain, InputReducer<MasterState>, IInputLayer {
      using InputReducer::InputReducer;

      [[nodiscard]] KeySet key_mask() const noexcept override
      {
        return key_groups::enc_clicks;
      }

      void reduce(EncoderEvent e, MasterState& state) noexcept override
      {
        state.volume += util::narrow(e.steps) * 0.01f;
      }
    };

    using Consumer::Consumer;

    void draw(skia::Canvas& ctx) noexcept override
    {
      VolumeWidget volume;
      volume.bounding_box = {skia::Box({110, 60}, {100, 120})};
      volume.value = state().volume;
      volume.draw(ctx);
    }
  };

  struct Logic final : ILogic, itc::Producer<MasterState> {
    Logic(itc::Context& ctx, drivers::IAudioMixer& mixer) : Producer(ctx), mixer_(mixer) {}

    void on_state_change(const MasterState& state) noexcept override
    {
      mixer_.set_volume(state.volume);
    }

    drivers::IAudioMixer& mixer_;
  };

  Master Master::make(itc::Context& ctx, drivers::IAudioMixer& mixer)
  {
    return {
      .logic = std::make_unique<Logic>(ctx, mixer),
      .screen =
        {
          std::make_unique<MasterScreen>(ctx),
          std::make_unique<MasterScreen::Handler>(ctx),
        },
    };
  }

} // namespace otto::engines::master
