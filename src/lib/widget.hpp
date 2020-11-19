#pragma once
#include <functional>
#include "app/services/graphics.hpp"

namespace otto::graphics {

  using Anchor = std::array<float, 2>;
  namespace Anchors {
    constexpr Anchor TopLeft = {0.f, 0.f};
    constexpr Anchor TopCenter = {0.f, 0.5f};
    constexpr Anchor TopRight = {0.f, 1.f};
    constexpr Anchor MiddleLeft = {0.5f, 0.f}; 
    constexpr Anchor Center = {0.5f, 0.5f};
    constexpr Anchor MiddleRight = {0.5, 1.f};
    constexpr Anchor BottomLeft = {1.f, 0.f};
    constexpr Anchor BottomCenter = {1.f, 0.5f};
    constexpr Anchor BottomRight = {1.f, 1.f};
  }

  //float x_pos_of(const Anchor a){
  //}

  using Point = std::array<float, 2>;
  using Size = std::array<float, 2>;

  struct Box {
    
    Box(Point p = {0, 0}, Size s = {0, 0}) : top_left_(p), s_(s) {};
      
    void move_to(Point p, Anchor a = Anchors::TopLeft) {
      top_left_[0] = p[0] - s_[0] * a[0];
      top_left_[1] = p[1] - s_[1] * a[1];
    };
      
    void resize(Size p, Anchor a = Anchors::TopLeft) {
      top_left_[0] -= (p[0] - s_[0]) * a[0];
      top_left_[1] -= (p[1] - s_[1]) * a[1];
      s_ = p;
    }

    Point get_point(Anchor a) {
      return {top_left_[0] + s_[0] * a[0], top_left_[1] + s_[1] * a[1]};
    }

    float width() { return s_[0]; }
    float height() { return s_[1]; }
    float x_pos(Anchor a) { return top_left_[0] + s_[0] * a[0]; }
    float y_pos(Anchor a) { return top_left_[1] + s_[1] * a[1]; }

  private:
    Point top_left_;
    Size s_;
  };
  
  template<typename Derived>
  struct Widget {
    Widget() = default;
    void draw_func(SkCanvas& ctx, int size_x, int size_y) {};

    void draw(SkCanvas& ctx) {
      ctx.save();
      // Translate from origin to draw_anchor
      // Does the C++ Skia not have translate(SkPoint)??
      ctx.translate(bounding_box.get_point(Anchors::TopLeft)[0], bounding_box.get_point(Anchors::TopLeft)[1]);
      static_cast<Derived*>(this)->do_draw(ctx);
      ctx.restore();
    }

    Box bounding_box;
  };

}