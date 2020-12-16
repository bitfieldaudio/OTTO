#pragma once

#include <SkColor.h>

namespace otto::skia {

  /// An ARGB Color
  ///
  /// SkColor is just an alias to `uint32_t`, so this wrapper allows a bit
  /// more flexibility.
  struct Color {
    constexpr Color() : Color(bytes(0, 0, 0)) {}
    explicit constexpr Color(SkColor sk) : sk_color_(sk) {}

    constexpr operator SkColor() const noexcept
    {
      return sk_color_;
    }

    [[nodiscard]] static constexpr Color bytes(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 0xFF) noexcept
    {
      return Color(SkColorSetARGB(a, r, g, b));
    }
    [[nodiscard]] static constexpr Color floats(float r, float g, float b, float a = 1) noexcept
    {
      return bytes(r * 0xFF, g * 0xFF, b * 0xFF, a * 0xFF);
    }

    [[nodiscard]] constexpr float redf() const noexcept
    {
      return static_cast<float>(red()) / 255.0f;
    }
    [[nodiscard]] constexpr float greenf() const noexcept
    {
      return static_cast<float>(green()) / 255.0f;
    }
    [[nodiscard]] constexpr float bluef() const noexcept
    {
      return static_cast<float>(blue()) / 255.0f;
    }
    [[nodiscard]] constexpr float alphaf() const noexcept
    {
      return static_cast<float>(alpha()) / 255.0f;
    }

    [[nodiscard]] constexpr std::uint8_t red() const noexcept
    {
      return SkColorGetR(sk_color_);
    }
    [[nodiscard]] constexpr std::uint8_t green() const noexcept
    {
      return SkColorGetG(sk_color_);
    }
    [[nodiscard]] constexpr std::uint8_t blue() const noexcept
    {
      return SkColorGetB(sk_color_);
    }
    [[nodiscard]] constexpr std::uint8_t alpha() const noexcept
    {
      return SkColorGetA(sk_color_);
    }

    constexpr Color& redf(float r) noexcept
    {
      return red(std::clamp(r, 0.f, 1.f) * 255.0f);
    }
    constexpr Color& greenf(float g) noexcept
    {
      return green(std::clamp(g, 0.f, 1.f) * 255.0f);
    }
    constexpr Color& bluef(float b) noexcept
    {
      return blue(std::clamp(b, 0.f, 1.f) * 255.0f);
    }
    constexpr Color& alphaf(float a) noexcept
    {
      return alpha(std::clamp(a, 0.f, 1.f) * 255.0f);
    }

    constexpr Color& red(std::uint8_t r) noexcept
    {
      sk_color_ = SkColorSetARGB(alpha(), r, green(), blue());
      return *this;
    }
    constexpr Color& green(std::uint8_t g) noexcept
    {
      sk_color_ = SkColorSetARGB(alpha(), red(), g, blue());
      return *this;
    }
    constexpr Color& blue(std::uint8_t b) noexcept
    {
      sk_color_ = SkColorSetARGB(alpha(), red(), green(), b);
      return *this;
    }
    constexpr Color& alpha(std::uint8_t a) noexcept
    {
      sk_color_ = SkColorSetARGB(a, red(), green(), blue());
      return *this;
    }

    constexpr auto operator<=>(const Color&) const noexcept = default;

    constexpr Color& operator+=(const Color& color) noexcept
    {
      red(std::clamp<std::uint8_t>(red() + color.red(), 0, 0xFF));
      green(std::clamp<std::uint8_t>(green() + color.green(), 0, 0xFF));
      blue(std::clamp<std::uint8_t>(blue() + color.blue(), 0, 0xFF));
      alpha(std::clamp<std::uint8_t>(alpha() + color.alpha(), 0, 0xFF));
      return *this;
    }

    constexpr Color& operator-=(const Color& color) noexcept
    {
      red(std::clamp<std::uint8_t>(red() - color.red(), 0, 0xFF));
      green(std::clamp<std::uint8_t>(green() - color.green(), 0, 0xFF));
      blue(std::clamp<std::uint8_t>(blue() - color.blue(), 0, 0xFF));
      alpha(std::clamp<std::uint8_t>(alpha() - color.alpha(), 0, 0xFF));
      return *this;
    }

    constexpr Color& operator*=(float f) noexcept
    {
      redf(redf() * f);
      greenf(greenf() * f);
      bluef(bluef() * f);
      alphaf(alphaf() * f);
      return *this;
    }

    constexpr Color& operator/=(float f) noexcept
    {
      redf(redf() / f);
      greenf(greenf() / f);
      bluef(bluef() / f);
      alphaf(alphaf() / f);
      return *this;
    }

    constexpr Color operator+(const Color& color) const noexcept
    {
      Color ret(*this);
      ret += color;
      return ret;
    }

    constexpr Color operator-(const Color& color) const noexcept
    {
      Color ret(*this);
      ret -= color;
      return ret;
    }

    constexpr Color operator*(float f) const noexcept
    {
      Color ret(*this);
      ret *= f;
      return ret;
    }

    constexpr Color operator/(float f) const noexcept
    {
      Color ret(*this);
      ret *= f;
      return ret;
    }

    [[nodiscard]] constexpr Color mix(Color c, float ratio) const noexcept;
    [[nodiscard]] constexpr Color dim(float amount) const noexcept;
    [[nodiscard]] constexpr Color fade(float amount) const noexcept;
    [[nodiscard]] constexpr Color brighten(float amount) const noexcept;

  private:
    std::uint32_t sk_color_;
  };


  constexpr Color Color::mix(Color c, float ratio) const noexcept
  {
    return (*this) * (1 - ratio) + c * ratio;
  }

  constexpr Color Color::dim(float amount) const noexcept
  {
    return brighten(1.f - amount);
  }

  constexpr Color Color::brighten(float amount) const noexcept
  {
    return ((*this) * amount).alpha(alpha());
  }

  constexpr Color Color::fade(float amount) const noexcept
  {
    float fade = std::clamp(1.f - amount, 0.f, 1.f);
    Color ret = *this;
    ret.alphaf(alphaf() * fade);
    return ret;
  }
} // namespace otto::skia
