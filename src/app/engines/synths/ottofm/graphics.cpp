#include "lib/itc/itc.hpp"
#include "lib/util/with_limits.hpp"
#include "app/input.hpp"
#include "app/services/graphics.hpp"

#include "ottofm.hpp"

using namespace otto;

namespace otto::engines::ottofm {

  struct Screen final : services::Graphics::Consumer<State> {
      using Consumer::Consumer;

      void draw(SkCanvas& ctx) noexcept override
      {
        SkPaint paint;
        paint.setAntiAlias(true);
        paint.setColor(SK_ColorWHITE);
        paint.setStyle(SkPaint::kFill_Style);
        ctx.drawCircle({160, 120},  100.f, paint);
      }
    };

}