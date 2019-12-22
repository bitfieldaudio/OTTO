#pragma once

#include <algorithm>
#include <climits>
#include <cmath>
#include <string>
#include <valarray>

namespace otto::nvg {

  static std::string nullstr;

  /// The data structure for memery blocks
  struct Memery {
    /// The data of the memery block
    void* data = nullptr;

    /// Size of the memery block in bytes
    unsigned long size = 0UL;

    /// Check is the data is not NULL and size is not 0
    bool valid() const
    {
      return (data && size);
    }

    /**
     * @brief Invalidate the memery object
     * @attention This method does NOT free the memery,you have to do it yourself!
     */
    void invalidate()
    {
      data = nullptr;
      size = 0UL;
    }
  };

  /// The π definition
  static constexpr long double PI = 3.14159265358979323846264338327L;

  /**
   * @brief Get a number in range @b [a,b]
   * @return The value between @e a and @e b
   * @li if @e a <= @e x <= @e b returns @e x
   * @li if @e x < @e a returns @e a
   * @li if @e x > @e b returns @e b
   */
  template<typename T>
  inline T clamp(T x, T a, T b)
  {
    return x < a ? a : (x > b ? b : x);
  }


  // Convert degree to radians
  template<typename T>
  T degree2Radians(const T _degree)
  {
    return _degree * (PI / (T) 180);
  }

  // Conver radians to degree
  template<typename T>
  T radians2Degree(const T _radians)
  {
    return _radians * (((T) 180) / PI);
  }

  struct Vec2 {
    float x, y;

    constexpr Vec2() noexcept : Vec2(0, 0) {}
    constexpr Vec2(Vec2 const&) noexcept = default;
    constexpr Vec2& operator=(Vec2 const&) noexcept = default;
    constexpr Vec2(float x, float y) noexcept : x(x), y(y) {}

    Vec2 rotate(float angle) const noexcept
    {
      float s = std::sin(angle);
      float c = std::cos(angle);

      float nx = x * c - y * s;
      float ny = x * s + y * c;

      return {nx, ny};
    }

    float angle() const noexcept
    {
      return std::atan(y / x);
    }

    float len() const noexcept
    {
      return std::sqrt(x * x + y * y);
    }
    constexpr float dir() const noexcept
    {
      return y / x;
    }

    constexpr Vec2 hat() const noexcept
    {
      return {-y, x};
    }

    constexpr Vec2 swapXY() const noexcept
    {
      return {y, x};
    }
    constexpr Vec2 flipSignX() const noexcept
    {
      return {-x, y};
    }
    constexpr Vec2 flipSignY() const noexcept
    {
      return {x, -y};
    }

    constexpr bool operator==(const Vec2& r) const noexcept
    {
      return x == r.x && y == r.y;
    }
    constexpr bool operator!=(const Vec2& r) const noexcept
    {
      return x != r.x && y != r.y;
    }
    constexpr Vec2 operator-(const Vec2& r) const noexcept
    {
      return {x - r.x, y - r.y};
    }
    constexpr Vec2 operator+(const Vec2& r) const noexcept
    {
      return {x + r.x, y + r.y};
    }
    constexpr Vec2 operator*(float s) const noexcept
    {
      return {x * s, y * s};
    }
    constexpr Vec2 operator/(float s) const noexcept
    {
      return {x / s, y / s};
    }
    constexpr Vec2 operator*(const Vec2& r) const noexcept
    {
      return {x * r.x, y * r.y};
    }
    constexpr Vec2 operator/(const Vec2& r) const noexcept
    {
      return {x / r.x, y / r.y};
    }
    constexpr Vec2 operator-() const noexcept
    {
      return {-x, -y};
    }

    // Factory methods
    static Vec2 angleAndLen(float a, float l)
    {
      return Vec2(std::cos(a), std::sin(a)) * l;
    }
  };

  inline auto operator*(std::valarray<Vec2> const& rhs, float lhs) noexcept
  {
    auto res = rhs;
    for (Vec2& p : res) {
      p = {p.x * lhs, p.y * lhs};
    }
    return res;
  }

  inline auto operator/(std::valarray<Vec2> const& rhs, float lhs) noexcept
  {
    auto res = rhs;
    for (Vec2& p : res) {
      p = {p.x / lhs, p.y / lhs};
    }
    return res;
  }


  struct Point {
    float x = 0, y = 0;

    constexpr Point() noexcept : Point(0, 0) {}
    constexpr Point(const Point&) noexcept = default;
    constexpr Point& operator=(const Point&) noexcept = default;
    constexpr Point(float x, float y) noexcept : x(x), y(y) {}

    // cppcheck-suppress noExplicitConstructor
    constexpr Point(Vec2 v) noexcept : x(v.x), y(v.y) {}

    Point rotate(float rad) const noexcept
    {
      float sn = std::sin(rad);
      float cs = std::cos(rad);
      return {x * cs - y * sn, x * sn + y * cs};
    }

    constexpr Point swapXY() const noexcept
    {
      return {y, x};
    }
    constexpr Point flipX() const noexcept
    {
      return {-x, y};
    }
    constexpr Point flipY() const noexcept
    {
      return {x, -y};
    }

    constexpr bool operator==(Point rhs) const noexcept
    {
      return x == rhs.x && y == rhs.y;
    }
    constexpr bool operator!=(Point rhs) const noexcept
    {
      return x != rhs.x && y != rhs.y;
    }
    constexpr Point operator+(Point rhs) const noexcept
    {
      return {x + rhs.x, y + rhs.y};
    }
    constexpr Point operator*(float s) const noexcept
    {
      return {x * s, y * s};
    }
    constexpr Point operator/(float s) const noexcept
    {
      return {x / s, y / s};
    }
    constexpr Point operator-() const noexcept
    {
      return {-x, -y};
    }
    constexpr Vec2 operator-(Point rhs) const noexcept
    {
      return {x - rhs.x, y - rhs.y};
    }

    constexpr explicit operator Vec2() const noexcept
    {
      return {x, y};
    }
    constexpr Vec2 vec() const noexcept
    {
      return {x, y};
    }
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
    constexpr Size(float w, float h) : w(w), h(h){};

    // cppcheck-suppress noExplicitConstructor
    constexpr Size(Vec2 v) : w(v.x), h(v.y){};

    constexpr Size swapWH() const
    {
      return {h, w};
    }

    constexpr Point center() const
    {
      return {w / 2.f, h / 2.f};
    }

    constexpr float min() const
    {
      return std::min(w, h);
    }

    constexpr float max() const
    {
      return std::max(w, h);
    }

    constexpr Size abs() const
    {
      const auto abs = [](float f) { return f < 0 ? -f : f; };
      return {abs(w), abs(h)};
    }
    constexpr explicit operator Vec2() const
    {
      return {w, h};
    }
    constexpr Vec2 vec() const
    {
      return {w, h};
    }
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
      : x(p.x), y(p.y), width(s.w), height(s.h)
    {}

    constexpr Box(Point p1, Point p2) //
      : Box(p1, Size(p2 - p1))
    {}

    constexpr Size size() const
    {
      return {width, height};
    }

    constexpr Point pmin() const
    {
      return {x, y};
    }

    constexpr Point pmax() const
    {
      return {x + width, y + height};
    }
  };

} // namespace NanoCanvas
