#include "testing.t.hpp"

#include "app/services/graphics.hpp"
#include "app/services/impl/runtime.hpp"

#include <SkFont.h>
#include <SkTypeface.h>

using namespace otto;
using namespace otto::services;

TEST_CASE (doctest::skip() * "Graphics test") {
  auto app = start_app(Graphics::make_board());
  SUBCASE ("Simple graphics and text for 2 second") {
    app.service<Graphics>().show([&](SkCanvas& ctx) {
      SkPaint paint;
      paint.setColor(SK_ColorBLACK);
      ctx.drawPaint(paint);
      paint.setColor(SK_ColorGREEN);
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
}

TEST_CASE ("Graphics service tests (no graphics)") {
  auto app = start_app(Graphics::make_board());
  SUBCASE ("Graphics executor") {
    itc::IExecutor& executor = app.service<Graphics>().executor();
    int count = 0;
    executor.execute([&] { count++; });
    executor.execute([&] {
      REQUIRE(count == 1);
      count++;
    });
    executor.execute([&] {
      REQUIRE(count == 2);
      count++;
      app.service<Runtime>().request_stop();
    });
    for (int i = 0; i < 100; i++) {
      executor.execute([&] { count++; });
    }
    app.stop();
    REQUIRE(count == 103);
  }
}
