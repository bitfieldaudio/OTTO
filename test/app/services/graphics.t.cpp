#include "testing.t.hpp"

#include "app/services/graphics.hpp"

#include "app/services/config.hpp"

using namespace otto;
using namespace otto::services;

TEST_CASE ("Graphics test", "[.interactive]") {
  RuntimeController rt;
  ConfigManager confman;
  Graphics graphics(rt);
  SECTION ("green rect") {
    auto stop = graphics.show([&](SkCanvas& ctx) {
      SkPaint paint;
      paint.setColor(SK_ColorGREEN);
      paint.setStrokeJoin(SkPaint::kRound_Join);
      paint.setStrokeCap(SkPaint::kRound_Cap);
      ctx.drawRect({0, 0, 20, 20}, paint);
    });
    rt.wait_for_stop(std::chrono::seconds(1));
  }
  SECTION ("Text1") {
    auto stop = graphics.show([&](SkCanvas& ctx) {
      SkFont font = fonts::regular(20);
      font.setEmbolden(true);
      ctx.drawString("Text1", 20, 20, font, paints::fill(colors::white));
    });
    rt.wait_for_stop(std::chrono::seconds(1));
  }
  // Some issues with skia and SkTextBlob/skia::place_text has lead to these tests
  SECTION ("Text2") {
    auto stop = graphics.show([&](SkCanvas& ctx) {
      SkFont font = fonts::regular(20);
      font.setEmbolden(true);
      ctx.drawTextBlob(SkTextBlob::MakeFromText("Text2", 5, font), 0, 0, paints::fill(colors::white));
    });
    rt.wait_for_stop(std::chrono::seconds(1));
  }
  SECTION ("Text3") {
    auto stop = graphics.show([&](SkCanvas& ctx) {
      SkFont font = fonts::regular(20);
      font.setEmbolden(true);
      skia::place_text(ctx, "Text3", font, colors::white, skia::Point{20, 20});
    });
    rt.wait_for_stop(std::chrono::seconds(1));
  }
}

TEST_CASE ("Graphics service tests (no graphics)") {
  SECTION ("Graphics executor") {
    int count = 0;
    {
      RuntimeController rt;
      ConfigManager confman;
      Graphics graphics(rt);
      itc::IExecutor& executor = graphics.executor();
      executor.execute([&] { count++; });
      executor.execute([&] {
        REQUIRE(count == 1);
        count++;
      });
      executor.execute([&] {
        REQUIRE(count == 2);
        count++;
        rt.request_stop();
      });
      for (int i = 0; i < 100; i++) {
        executor.execute([&] { count++; });
      }
    }
    REQUIRE(count == 103);
  }
}
