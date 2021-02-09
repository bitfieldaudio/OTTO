#include "testing.t.hpp"

#include <queue>

#include "lib/util/with_limits.hpp"

#include "app/application.hpp"
#include "app/services/config.hpp"
#include "app/services/controller.hpp"
#include "app/services/graphics.hpp"
#include "app/services/logic_thread.hpp"
#include "app/services/runtime.hpp"

using namespace otto;
using namespace otto::services;

TEST_CASE ("EncoderGUI", "[.interactive]") {
  auto app = start_app(ConfigManager::make_default(), LogicThread::make(), Controller::make(), Graphics::make());

  struct Handler final : InputHandler {
    void handle(KeyPress e) noexcept override
    {
      LOGI("Keypress {}", util::enum_name(e.key));
      // led_from(e.key).map([&](auto k) { controller->send_led_color(k, {0xFF, 0xFF, 0xFF}); });
    }
    void handle(KeyRelease e) noexcept override
    {
      LOGI("Keyrelease {}", util::enum_name(e.key));
      // led_from(e.key).map([&](auto k) { controller->send_led_color(k, {0x00, 0x00, 0x00}); });
    }
    void handle(EncoderEvent e) noexcept override
    {
      color = [&] {
        switch (e.encoder) {
          case Encoder::blue: return SK_ColorBLUE;
          case Encoder::green: return SK_ColorGREEN;
          case Encoder::yellow: return SK_ColorYELLOW;
          case Encoder::red: return SK_ColorRED;
        }
        OTTO_UNREACHABLE();
      }();
      n += e.steps;
    }
    [[no_unique_address]] core::ServiceAccessor<Controller> controller;
    SkColor color = SK_ColorWHITE;
    util::StaticallyBounded<int, 0, 160> n = 80;
  } handler;

  app.service<Controller>().set_input_handler(handler);
  app.service<Graphics>().show([&](SkCanvas& ctx) {
    SkPaint paint;
    paint.setAntiAlias(true);
    paint.setStyle(SkPaint::kFill_Style);
    paint.setColor(handler.color);
    ctx.drawCircle({160, 120}, handler.n, paint);
    if (handler.n == 0) app.service<Runtime>().request_stop();
  });
  app.wait_for_stop();
}
