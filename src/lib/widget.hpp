#pragma once
#include <functional>
#include "app/services/graphics.hpp"

#include "lib/skia/skia.hpp"

namespace otto::graphics {

  template<typename Derived>
  struct Widget : IDrawable {
    Widget() = default;

    void draw(skia::Canvas& ctx) noexcept final
    {
      ctx.save();
      skia::translate(ctx, bounding_box.point(anchors::top_left));
      static_cast<Derived*>(this)->do_draw(ctx);
      ctx.restore();
    }

    skia::Box bounding_box;
  };

} // namespace otto::graphics
