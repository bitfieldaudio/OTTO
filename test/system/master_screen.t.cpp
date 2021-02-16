#include "testing.t.hpp"

#include <string>

#include <SkFont.h>
#include <SkPath.h>
#include <SkRRect.h>
#include <SkTextBlob.h>
#include <SkTypeface.h>
#include <choreograph/Choreograph.h>
#include <fmt/format.h>

#include "lib/skia/anchor.hpp"
#include "lib/skia/skia.hpp"
#include "lib/widget.hpp"

#include "app/application.hpp"
#include "app/services/config.hpp"
#include "app/services/graphics.hpp"

using namespace otto;
using namespace otto::services;

struct Master : graphics::Widget<Master> {
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


TEST_CASE ("master-graphics", "[.interactive]") {
  using namespace otto::graphics;
  namespace ch = choreograph;
  ch::Timeline timeline;
  ch::Output<float> value = 1.0f;
  auto sequence = ch::Sequence<float>(value.value())
                    .then<ch::RampTo>(0.f, 2.0f, ch::EaseInOutQuad())
                    .then<ch::Hold>(0.f, 1.f)
                    .then<ch::RampTo>(1.0f, 2.0f, ch::EaseInOutQuad())
                    .then<ch::Hold>(1.f, 1.f);

  auto looped = makeRepeat<float>(sequence.asPhrase(), 100.f);

  timeline.apply(&value, looped);


  RuntimeController rt;
  Graphics graphics(rt);
  SECTION ("Master Screen") {
    Master master;


    auto stop = graphics.show([&](skia::Canvas& ctx) {
      master.value = value;
      master.bounding_box.resize({100, 120});
      master.bounding_box.move_to({110, 60});
      master.draw(ctx);

      timeline.step(1.0 / 60.0);
    });
    rt.wait_for_stop(10s);
  }
}
