#pragma once

#include <SkPoint.h>
#include <SkRect.h>

namespace otto::anchors {
  constexpr SkVector top_left = {0.f, 0.f};
  constexpr SkVector top_center = {0.5f, 0.f};
  constexpr SkVector top_right = {1.f, 0.f};
  constexpr SkVector middle_left = {0.f, 0.5f};
  constexpr SkVector center = {0.5f, 0.5f};
  constexpr SkVector middle_right = {1.f, 0.5f};
  constexpr SkVector bottom_left = {0.f, 1.f};
  constexpr SkVector bottom_center = {0.5f, 1.0f};
  constexpr SkVector bottom_right = {1.f, 1.f};
} // namespace otto::anchors

namespace otto::skia {

  using Anchor = SkVector;

  struct Box {
    Box(SkRect r) : top_left_{r.x(), r.y()}, s_{r.width(), r.height()} {}
    Box(SkPoint p = {0, 0}, SkVector s = {0, 0}) : top_left_(p), s_(s){};

    void move_to(SkPoint p, Anchor a = anchors::top_left)
    {
      top_left_.set(p.x() - s_.x() * a.x(), p.y() - s_.y() * a.y());
    };

    void resize(SkVector p, Anchor a = anchors::top_left)
    {
      top_left_.set((p.x() - s_.x()) * a.x(), (p.y() - s_.y()) * a.y());
      s_ = p;
    }

    SkPoint get_point(Anchor a)
    {
      return {top_left_.x() + s_.x() * a.x(), top_left_.y() + s_.y() * a.y()};
    }

    SkPoint get_diff(Anchor start, Anchor end)
    {
      return {(end.x() - start.x()) * s_.x(), (end.y() - start.y()) * s_.y()};
    }

    float width()
    {
      return s_.x();
    }
    float height()
    {
      return s_.y();
    }
    float x(Anchor a = anchors::top_left)
    {
      return top_left_.x() + s_.x() * a.x();
    }
    float y(Anchor a = anchors::top_left)
    {
      return top_left_.y() + s_.y() * a.y();
    }

  private:
    SkPoint top_left_;
    SkVector s_;
  };
} // namespace otto::skia
