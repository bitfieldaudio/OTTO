#pragma once
#include <functional>

#include "lib/itc/state/state.hpp"
#include "lib/skia/skia.hpp"

#include "app/services/graphics.hpp"

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

  // template<typename Derived, AState State>
  // struct StatefulWidget : IDrawable {
  //   StatefulWidget() = default;

  //   void draw(skia::Canvas& ctx) noexcept final
  //   {
  //     ctx.save();
  //     skia::translate(ctx, bounding_box.point(anchors::top_left));
  //     auto tmp = bounding_box.point();
  //     bounding_box.move_to({0, 0});
  //     static_cast<Derived*>(this)->do_draw(ctx);
  //     bounding_box.move_by(tmp);
  //     ctx.restore();
  //   }

  //   virtual void on_state_change(State& s);

  //   skia::Box bounding_box;
  // };



} // namespace otto::graphics
