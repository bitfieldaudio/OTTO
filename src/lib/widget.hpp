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
      auto tmp = bounding_box.point();
      bounding_box.move_to({0, 0});
      static_cast<Derived*>(this)->do_draw(ctx);
      bounding_box.move_by(tmp);
      ctx.restore();
    }

    skia::Box bounding_box;
  };

} // namespace otto::graphics
