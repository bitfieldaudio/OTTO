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

#include "app/services/config.hpp"
#include "app/services/graphics.hpp"

using namespace otto;
using namespace otto::services;

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
    // Master master;


    // auto stop = graphics.show([&](skia::Canvas& ctx) {
    //  master.value = value;
    //  master.bounding_box.resize({100, 120});
    //  master.bounding_box.move_to({110, 60});
    //  master.draw(ctx);

    //  timeline.step(1.0 / 60.0);
    //});
    // rt.wait_for_stop(10s);
  }
}
