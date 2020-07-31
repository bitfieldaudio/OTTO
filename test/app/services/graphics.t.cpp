#include "testing.t.hpp"

#include "app/services/graphics.hpp"
#include "app/services/impl/runtime.hpp"

#include <SkFont.h>
#include <SkTypeface.h>

using namespace otto::app;
using namespace otto::lib;

TEST_CASE (doctest::skip() * "Graphics test") {
  SUBCASE ("Simple graphics and text for 2 second") {
    auto app = services::start_app(
      services::Graphics::make_board()
    );
    app.service<services::Graphics>().show([&](SkCanvas& ctx) {
      SkPaint paint;
      paint.setColor(SK_ColorBLACK);
      ctx.drawPaint(paint);
      paint.setColor(SK_ColorBLUE);
      paint.setStrokeJoin(SkPaint::kRound_Join);
      paint.setStrokeCap(SkPaint::kRound_Cap);
      ctx.drawRect({0, 0, 20, 20}, paint);
      SkFont font = {SkTypeface::MakeDefault(), 20};
      font.setEmbolden(true);
      ctx.drawString("OTTO", 20, 20, font, paint);
    });
    std::this_thread::sleep_for(std::chrono::seconds(2));
    app.stop();
  }
  SUBCASE ("Graphics service executor") {}
}
