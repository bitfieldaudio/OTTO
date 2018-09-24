#pragma once

#include <functional>
#include <type_traits>
#include <valarray>

#pragma GCC diagnostic push 
#pragma GCC diagnostic ignored "-Wpedantic"
#pragma GCC diagnostic ignored "-Wunused-function"
#include <nanovg.h>
#include <NanoCanvas.h>
#pragma GCC diagnostic pop

#include "util/math.hpp"
#include "util/iterator.hpp"

namespace otto::core::ui::vg {

  using NanoCanvas::HorizontalAlign;
  using NanoCanvas::VerticalAlign;
  namespace TextAlign = NanoCanvas::TextAlign;
  using NanoCanvas::TextStyle;
  using NanoCanvas::Font;
  using Winding = NanoCanvas::Canvas::Winding;

  struct Point {
    float x, y;

    constexpr Point() noexcept : Point(0, 0) {}
    constexpr Point(const Point&) noexcept = default;
    constexpr Point& operator=(const Point&) noexcept = default;
    constexpr Point(float x, float y) noexcept : x (x), y (y) {}

    // cppcheck-suppress noExplicitConstructor
    constexpr Point(util::math::vec v) noexcept : x (v.x), y (v.y) {}

    Point rotate(float rad) const noexcept {
      float sn = std::sin(rad);
      float cs = std::cos(rad);
      return {
        x * cs - y * sn,
        x * sn + y * cs
      };
    }

    constexpr Point swapXY() const noexcept {return {y, x};}
    constexpr Point flipX() const noexcept {return {-x, y};}
    constexpr Point flipY() const noexcept {return {x, -y};}

    constexpr bool operator==(Point rhs) const noexcept {return x == rhs.x && y == rhs.y;}
    constexpr bool operator!=(Point rhs) const noexcept {return x != rhs.x && y != rhs.y;}
    constexpr Point operator+(Point rhs) const noexcept {return {x + rhs.x, y + rhs.y};}
    constexpr Point operator*(float s) const noexcept {return {x * s, y * s};}
    constexpr Point operator/(float s) const noexcept {return {x / s, y / s};}
    constexpr Point operator-() const noexcept {return {-x, -y};}
    constexpr util::math::vec operator-(Point rhs) const noexcept {return {x - rhs.x, y - rhs.y};}

    constexpr explicit operator util::math::vec() const noexcept {return {x, y};}
    constexpr util::math::vec vec() const noexcept {return {x, y};}
  };

  inline auto operator*(std::valarray<Point> const& rhs, float lhs) noexcept
  {
    auto res = rhs;
    for (Point& p : res) {
      p = {p.x * lhs, p.y * lhs};
    }
    return res;
  }

  inline auto operator/(std::valarray<Point> const& rhs, float lhs) noexcept
  {
    auto res = rhs;
    for (Point& p : res) {
      p = {p.x / lhs, p.y / lhs};
    }
    return res;
  }

  struct Size {
    float w, h;

    constexpr Size() : Size(0, 0) {}
    constexpr Size(float w, float h) : w (w), h (h) {};

    // cppcheck-suppress noExplicitConstructor
    constexpr Size(util::math::vec v) : w (v.x), h (v.y) {};

    constexpr Size swapWH() const {return {h, w};}

    constexpr Point center() const {
      return {w / 2.f, h / 2.f};
    }

    constexpr Size abs() const {
      const auto abs = [] (float f) {return f < 0 ? -f : f;};
      return {abs(w), abs(h)};
    }
    constexpr explicit operator util::math::vec() const {return {w, h};}
    constexpr util::math::vec vec() const {return {w, h};}
  };

  /// A positioned box
  struct Box {
    float x = 0;
    float y = 0;
    float width = 0;
    float height = 0;

    constexpr Box() = default;

    constexpr Box(float x, float y, float width, float height) //
      : x(x), y(y), width(width), height(height)
    {}

    constexpr Box(Point p, Size s) //
      : x (p.x), y (p.y), width (s.w), height(s.h)
    {}

    constexpr Box(Point p1, Point p2) //
      : Box(p1, Size(p2 - p1))
    {}

    constexpr Size size() const
    {
      return {width, height};
    }
  };

  struct Colour {

    std::uint8_t r;
    std::uint8_t g;
    std::uint8_t b;
    std::uint8_t a = 0xFF;

    Colour(float, float, float, float a = 1.0);

    // cppcheck-suppress noExplicitConstructor
    Colour(std::uint32_t data) {
      r = std::uint8_t((data >> 16) & 0x0000FF);
      g = std::uint8_t((data >> 8) & 0x0000FF);
      b = std::uint8_t((data) & 0x0000FF);
      a = 0xFF;
    };

    Colour();

    Colour mix(Colour c, float ratio) const;
    Colour dim(float amount) const;
    Colour brighten(float amount) const;

    operator NanoCanvas::Color() const {
      return NanoCanvas::Color(r, g, b, a);
    }

    static Colour floats(float r, float g, float b, float a = 1);
    static Colour bytes(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 0xFF);
  };

  inline Colour Colour::floats(float r, float g, float b, float a) {
    return Colour(r, g, b, a);
  }

  inline Colour Colour::bytes(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
    return Colour(r / 255.f, g / 255.f, b / 255.f, a / 255.f);
  }

  inline Colour::Colour(float r, float g, float b, float a) :
    r (r * 255), g (g * 255), b (b * 255), a (a * 255) {}

  inline Colour::Colour() : Colour(0,0,0) {}

  inline Colour Colour::mix(Colour c, float ratio) const {
    Colour ret;
    ret.r = std::clamp<uint8_t>(r + (c.r - r ) * ratio, 0x00, 0xFF);
    ret.g = std::clamp<uint8_t>(g + (c.g - g ) * ratio, 0x00, 0xFF);
    ret.b = std::clamp<uint8_t>(b + (c.b - b ) * ratio, 0x00, 0xFF);
    ret.a = std::clamp<uint8_t>(a + (c.a - a ) * ratio, 0x00, 0xFF);
    return ret;
  }

  inline Colour Colour::dim(float amount) const {
    float dim = std::clamp(1.f - amount,0.f,1.f);
    Colour ret;
    ret.r = std::clamp<uint8_t>(r * dim, 0x00, 0xFF);
    ret.g = std::clamp<uint8_t>(g * dim, 0x00, 0xFF);
    ret.b = std::clamp<uint8_t>(b * dim, 0x00, 0xFF);
    ret.a = a;
    return ret;
  }

  inline Colour Colour::brighten(float amount) const {
    Colour ret;
    ret.r = std::clamp<uint8_t>(r + (255 - r) * amount, 0x00, 0xFF);
    ret.g = std::clamp<uint8_t>(g + (255 - g) * amount, 0x00, 0xFF);
    ret.b = std::clamp<uint8_t>(b + (255 - b) * amount, 0x00, 0xFF);
    ret.a = a;
    return ret;
  }

  struct MainColour : public Colour {

    const Colour dimmed;

    // cppcheck-suppress noExplicitConstructor
    MainColour(Colour basic)
      : Colour (basic),
        dimmed (basic.dim(0))
    {}

    MainColour(Colour basic, Colour dimmed)
      : Colour (basic),
        dimmed (dimmed)
    {}

    // cppcheck-suppress noExplicitConstructor
    MainColour(std::uint32_t basic)
      : Colour (basic),
        dimmed (dim(0.1))
    {}

    MainColour(std::uint32_t basic, std::uint32_t dimmed)
      : Colour (basic),
        dimmed (dimmed)
    {}

    using Colour::operator NanoCanvas::Color;
  };

  struct Canvas; // FWDCL

  /// Anything that can be drawn on screen.
  ///
  /// Holds a pointer to its parent
  struct Drawable {

    Drawable() = default;

    virtual ~Drawable() = default;

    /// Draw this widget to the context.
    ///
    /// Called from the parent's draw method.
    /// \param ctx the canvas to draw on.
    virtual void draw(Canvas& ctx) = 0;

  };

  /// A modified NanoCanvas interface.
  ///
  /// Allows for usage of [*Point]() and [*Size]() classes
  struct Canvas : NanoCanvas::Canvas {
    using Super = NanoCanvas::Canvas;

    // Enums
    using Super::Winding;
    using Super::LineCap;
    using Super::LineJoin;

    Canvas(NVGcontext* ctx, Size size, float scaleRatio = 1.0f) :
      Canvas(ctx, size.w, size.h, scaleRatio) {}

    Canvas(NVGcontext* ctx, float width, float height, float scaleRatio = 1.0f) :
      Super(ctx, width, height, scaleRatio) {}

    /// Canvas is non-copyable
    Canvas(const Canvas&) = delete;
    /// Canvas is non-copyable
    auto operator=(const Canvas&) = delete;

    /// Canvas is movable
    Canvas(Canvas&&) = default;
    /// Canvas is movable
    Canvas& operator=(Canvas&&) = default;

    /// Get the canvas size
    Size size() const noexcept {
      return {m_width, m_height};
    }

    using Super::moveTo;
    Canvas& moveTo(Point p) {
      Super::moveTo(p.x, p.y);
      return *this;
    }

    using Super::lineTo;
    Canvas& lineTo(Point p) {
      Super::lineTo(p.x, p.y);
      return *this;
    }

    using Super::arcTo;
    Canvas& arcTo(Point p1, Point p2, float r) {
      Super::arcTo(p1.x, p1.y, p2.x, p2.y, r);
      return *this;
    }

    using Super::quadraticCurveTo;
    Canvas& quadraticCurveTo(Point control, Point end) {
      Super::quadraticCurveTo(control.x, control.y, end.x, end.y);
      return *this;
    }

    using Super::bezierCurveTo;
    Canvas& bezierCurveTo(Point cp1, Point cp2, Point end) {
      Super::bezierCurveTo(cp1.x, cp1.y, cp2.x, cp2.y, end.x, end.y);
      return *this;
    }

    using Super::arc;
    Canvas& arc(Point cp,float r,
      float sAngle,float eAngle,bool counterclockwise = false) {
      Super::arc(cp.x, cp.y, r, sAngle, eAngle, counterclockwise);
      return *this;
    }

    using Super::rect;
    Canvas& rect(Point p, Size s) {
      Super::rect(p.x, p.y, s.w, s.h);
      return *this;
    }

    using Super::roundedRect;
    Canvas& roundedRect(Point p, Size s,float r) {
      Super::roundedRect(p.x, p.y, s.w, s.h, r);
      return *this;
    }

    using Super::circle;
    Canvas& circle(Point p, float r) {
      Super::circle(p.x, p.y, r);
      return *this;
    }

    using Super::ellipse;
    Canvas& ellipse(Point p, float rx, float ry) {
      Super::ellipse(p.x, p.y, rx, ry);
      return *this;
    }


    using Super::clearColor;
    Canvas& clearColor(const Colour& color) {
      Super::clearColor(color);
      return *this;
    }

    using Super::font;
    Canvas& font(const Font& f, float size) {
      Super::font(f);
      Super::font(size);
      return *this;
    }

    using Super::fillText;
    Canvas& fillText(const std::string& text, Point p, float rowWidth = NAN) {
      Super::fillText(text, p.x, p.y, rowWidth);
      return *this;
    }

    using Super::textAlign;

    using Super::fillStyle;
    Canvas& fillStyle(const Colour& color) {
      Super::fillStyle(color);
      return *this;
    }

    using Super::strokeStyle;
    Canvas& strokeStyle(const Colour& color) {
      Super::strokeStyle(color);
      return *this;
    }

    using Super::fill;
    Canvas& fill(const Colour& color) {
      Super::fillStyle(color);
      Super::fill();
      return *this;
    }

    using Super::stroke;
    Canvas& stroke(const Colour& color) {
      Super::strokeStyle(color);
      Super::stroke();
      return *this;
    }


    using Super::translate;
    Canvas& translate(Point p) {
      Super::translate(p.x, p.y);
      return *this;
    }

    Canvas& rotateAround(float r, Point p) {
      translate(p);
      rotate(r);
      translate(-p);
      return *this;
    }

    Canvas& scaleTowards(float s, Point p) {
      translate(p);
      scale(s, s);
      translate(-p);
      return *this;
    }

    Canvas& draw(Drawable &d) {
      d.draw(*this);
      return *this;
    }

    Canvas& draw(Drawable &&d) {
      d.draw(*this);
      return *this;
    }

    Canvas& drawAt(Point p, Drawable &&d) {
      save();
      translate(p);
      d.draw(*this);
      restore();
      return *this;
    }

    Canvas& drawAt(Point p, Drawable &d) {
      save();
      translate(p);
      d.draw(*this);
      restore();
      return *this;
    }

    template<typename FuncRef>
    Canvas& group(FuncRef&& func) {
        save();
        func();
        restore();
        return *this;
    }

    Canvas& callAt(Point p, const std::function<void(void)>& f) {
      save();
      translate(p);
      f();
      restore();
      return *this;
    }

    template<typename It>
    Canvas& plotBezier(It pointB, It pointE, float f = 0.5, float t = 1) {

      moveTo(*pointB);

      float m = 0;
      Point d1;

      Point prev = *pointB;
      Point cur = prev;
      Point next = prev;
      for (auto it = pointB; it != pointE; ++it) {
        prev = cur;
        cur = next;
        next = *it;
        if (cur == prev) continue;
        m = (next.y - prev.y) / (next.x - prev.x);
        Point d2 = {
          (next.x - cur.x) * -f,
          0
        };
        d2.y = d2.x * m * t;
        bezierCurveTo(prev - d1, cur + d2, cur);
        d1 = d2;
      }
      return *this;
    }

    /// Draw a curve between points using only horizontal and vertical lines and
    /// rounded corners
    ///
    /// This is the algorithm used by the samplers, and in general to display waveforms
    ///
    /// \param first An iterator to the first point
    /// \param last An iterator one past the last point
    /// \param maxR The maximum radius for curves, in pixels. If negative, there
    ///             is no limit
    /// \requires `It` shall be an `InputIterator<Point>`
    template<typename Iter>
    void plotRounded(Iter first, Iter last, float max_radius)
    {
      if (first == last) return;

      moveTo(*first);
      for (auto [p1, p2] : util::adjacent_pairs(first, last))
      {
        float dx = std::abs(p2.x - p1.x);
        float dy = std::abs(p2.y - p1.y);
        float r = std::min({dx / 2.f, dy / 2.f, max_radius});
        vg::Point md = (p1 + p2) / 2.0;
        vg::Point cp1 = {md.x, p1.y};
        vg::Point cp2 = md;
        vg::Point cp3 = {md.x, p2.y};

        arcTo(cp1, cp2, r);
        arcTo(cp3, p2, r);
      }
      lineTo(*(--last));
    }

    /// Plot a curve between points using straight lines
    ///
    /// \param first An iterator to the first point
    /// \param last An iterator one past the last point
    /// \requires `It` shall be an `InputIterator<Point>`
    template<typename Iter>
    void plotLines(Iter first, Iter last)
    {
      if (first == last) return;

      moveTo(*first++);
      for (auto p : util::sequence(first, last)) {
        lineTo(p);
      }
    }

    /// A scatterplot of points
    ///
    /// \param first An iterator to the first point
    /// \param last An iterator one past the last point
    /// \param r The radius of the points
    /// \param c The colour of the points
    /// \requires `It` shall be an `InputIterator<Point>`
    ///
    template<typename It>
    Canvas& plotPoints(It first, It last, float r, Colour c)
    {
      std::for_each(first, last, [this, c, r] (Point p) {
          beginPath();
          circle(p, r);
          fill(c);
        });
      return *this;
    }

    // Debuging

    Canvas& debugDot(Point p, Colour c = 0xFFFF00) {
      beginPath();
      circle(p, 1);
      fill(c);
      return *this;
    }
  };

} // otto::ui::drawing
