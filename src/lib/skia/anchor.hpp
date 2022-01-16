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

inline SkVector interpolate(SkVector a, SkVector b, float ratio)
{
  return b * ratio + a * (1.f - ratio);
}

inline float interpolate(float a, float b, float ratio)
{
  return b * ratio + a * (1.f - ratio);
}

namespace otto::skia {

  using Anchor = SkVector;

  struct Box {
    Box(SkRect r) noexcept : top_left_{r.x(), r.y()}, s_{r.width(), r.height()} {}
    Box(SkPoint p = {0, 0}, SkVector s = {0, 0}) noexcept : top_left_(p), s_(s){};

    void move_to(SkPoint p, Anchor a = anchors::top_left)
    {
      top_left_.set(p.x() - s_.x() * a.x(), p.y() - s_.y() * a.y());
    }

    void move_by(SkVector v)
    {
      top_left_ += v;
    }

    void resize(SkVector s, Anchor a = anchors::top_left)
    {
      top_left_ -= {(s.x() - s_.x()) * a.x(), (s.y() - s_.y()) * a.y()};
      s_ = s;
    }

    void align(Box b, Anchor a = anchors::top_left)
    {
      move_to(b.point(a), a);
    }

    [[nodiscard]] Box moved_to(SkPoint p, Anchor a = anchors::top_left) const noexcept
    {
      Box res = *this;
      res.move_to(p, a);
      return res;
    }

    [[nodiscard]] Box moved_by(SkVector v) const noexcept
    {
      Box res = *this;
      res.move_by(v);
      return res;
    }

    [[nodiscard]] Box resized(SkVector s, Anchor a = anchors::top_left) const noexcept
    {
      Box res = *this;
      res.resize(s, a);
      return res;
    }

    [[nodiscard]] Box aligned(Box b, Anchor a = anchors::top_left) const noexcept
    {
      Box res = *this;
      res.align(b, a);
      return res;
    }

    [[nodiscard]] SkPoint point(Anchor a = anchors::top_left) const noexcept
    {
      return {top_left_.x() + s_.x() * a.x(), top_left_.y() + s_.y() * a.y()};
    }

    [[nodiscard]] SkPoint diff(Anchor start, Anchor end) const noexcept
    {
      return {(end.x() - start.x()) * s_.x(), (end.y() - start.y()) * s_.y()};
    }

    [[nodiscard]] SkPoint size() const noexcept
    {
      return s_;
    }

    [[nodiscard]] float width() const noexcept
    {
      return s_.x();
    }
    [[nodiscard]] float height() const noexcept
    {
      return s_.y();
    }
    [[nodiscard]] float x(Anchor a = anchors::top_left) const noexcept
    {
      return top_left_.x() + s_.x() * a.x();
    }
    [[nodiscard]] float y(Anchor a = anchors::top_left) const noexcept
    {
      return top_left_.y() + s_.y() * a.y();
    }

    [[nodiscard]] bool contains(SkPoint p) const noexcept
    {
      auto p2 = p - top_left_;
      return p2.x() >= 0 && p2.x() <= s_.x() && p2.y() >= 0 && p2.y() <= s_.y();
    }

    operator SkRect() const noexcept
    {
      return SkRect::MakeXYWH(x(), y(), width(), height());
    }

  private:
    SkPoint top_left_;
    SkVector s_;
  };

  inline Box interpolate(Box a, Box b, float ratio)
  {
    return {interpolate(a.point(), b.point(), ratio), interpolate(a.size(), b.size(), ratio)};
  }
} // namespace otto::skia
