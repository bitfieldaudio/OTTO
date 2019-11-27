#pragma once

#include "ColorConverter.hpp"
#include "services/log_manager.hpp"
#include "util.hpp"

namespace otto::nvg {

  using Byte = unsigned char;

  struct Color : ColorConverter::Rgba {
    constexpr Color()
    {
      r = g = b = a = 0;
    }

    /**
     * @brief Construct a color with an unsigned integer value
     * @param color The color code value
     */
    constexpr Color(const unsigned int color)
    {
      set(color);
    }

    /**
     * @brief Construct color with it's components value in the range [0,255]
     * @param _r The red component value
     * @param _g The green component value
     * @param _b The blue component value
     * @param _a The alpha component value
     */
    constexpr Color(Byte _r, Byte _g, Byte _b, Byte _a = 255)
    {
      set(_r, _g, _b, _a);
    }

    /**
     * @brief Construct color with it's components value in the range [0,255]
     * @param _r The red component value
     * @param _g The green component value
     * @param _b The blue component value
     * @param _a The alpha component value
     */
    constexpr Color(int _r, int _g, int _b, int _a = 255)
    {
      set(_r, _g, _b, _a);
    }

    /**
     * @brief Construct color with it's components value in the range [0,255]
     * @param _r The red component value
     * @param _g The green component value
     * @param _b The blue component value
     * @param _a The alpha component value
     */
    constexpr Color(unsigned _r, unsigned _g, unsigned _b, unsigned _a = 255)
    {
      set(_r, _g, _b, _a);
    }

    /**
     * @brief Construct color with it's components value in the range [0,1]
     * @param _r The red component value
     * @param _g The green component value
     * @param _b The blue component value
     * @param _a The alpha component value
     */
    constexpr Color(float _r, float _g, float _b, float _a = 1.0f)
    {
      set(_r, _g, _b, _a);
    }

    /// Convert the color to unsigned int as the color code
    constexpr operator unsigned int() const
    {
      return code();
    }

    constexpr Byte& operator[](int index)
    {
      switch (index) {
        case 0: return r;
        case 1: return g;
        case 2: return b;
        case 3: return a;
        default: OTTO_UNREACHABLE;
      }
    }
    constexpr const Byte operator[](int index) const
    {
      switch (index) {
        case 0: return r;
        case 1: return g;
        case 2: return b;
        case 3: return a;
        default: OTTO_UNREACHABLE;
      }
    }

    constexpr bool operator==(const Color& color)
    {
      return code() == color.code();
    }
    constexpr bool operator<(const Color& color)
    {
      return code() < color.code();
    }

    constexpr Color& operator=(const unsigned int color)
    {
      return set(color);
    }

    constexpr Color& operator+=(const Color& color)
    {
      r = std::clamp<Byte>(r + color.r, 0, UCHAR_MAX);
      g = std::clamp<Byte>(g + color.g, 0, UCHAR_MAX);
      b = std::clamp<Byte>(b + color.b, 0, UCHAR_MAX);
      a = std::clamp<Byte>(a + color.a, 0, UCHAR_MAX);
      return *this;
    }

    constexpr Color& operator-=(const Color& color)
    {
      using std::max;
      r = std::clamp<Byte>(r - color.r, 0, UCHAR_MAX);
      g = std::clamp<Byte>(g - color.g, 0, UCHAR_MAX);
      b = std::clamp<Byte>(b - color.b, 0, UCHAR_MAX);
      a = std::clamp<Byte>(a - color.a, 0, UCHAR_MAX);
      return *this;
    }

    constexpr Color& operator*=(const Color& color)
    {
      r = std::clamp<Byte>(r + (color.r * color.a / UCHAR_MAX), 0, UCHAR_MAX);
      g = std::clamp<Byte>(g + (color.g * color.a / UCHAR_MAX), 0, UCHAR_MAX);
      b = std::clamp<Byte>(b + (color.b * color.a / UCHAR_MAX), 0, UCHAR_MAX);
      return *this;
    }

    constexpr Color operator+(const Color& color)
    {
      Color ret(*this);
      ret += color;
      return ret;
    }

    constexpr Color operator-(const Color& color)
    {
      Color ret(*this);
      ret -= color;
      return ret;
    }

    constexpr Color operator*(const Color& color)
    {
      Color ret(*this);
      ret *= color;
      return ret;
    }

    constexpr Color& set(unsigned int color)
    {
      r = (Byte)(color >> 24U);
      g = (Byte)((color >> 16U) & 0x00ffU);
      b = (Byte)((color >> 8U) & 0x0000ffU);
      a = (Byte)(color % 0x100U);
      return *this;
    }

    constexpr Color& set(float _r, float _g, float _b, float _a)
    {
      r = std::clamp<Byte>((Byte)(_r * UCHAR_MAX), 0, UCHAR_MAX);
      g = std::clamp<Byte>((Byte)(_g * UCHAR_MAX), 0, UCHAR_MAX);
      b = std::clamp<Byte>((Byte)(_b * UCHAR_MAX), 0, UCHAR_MAX);
      a = std::clamp<Byte>((Byte)(_a * UCHAR_MAX), 0, UCHAR_MAX);
      return *this;
    }

    constexpr Color& set(Byte _r, Byte _g, Byte _b, Byte _a)
    {
      r = _r;
      g = _g;
      b = _b;
      a = _a;
      return *this;
    }

    constexpr Color& set(unsigned _r, unsigned _g, unsigned _b, unsigned _a)
    {
      r = (Byte) _r;
      g = (Byte) _g;
      b = (Byte) _b;
      a = (Byte) _a;
      return *this;
    }

    constexpr Color& set(int _r, int _g, int _b, int _a)
    {
      r = (Byte) _r;
      g = (Byte) _g;
      b = (Byte) _b;
      a = (Byte) _a;
      return *this;
    }

    static constexpr Color floats(float r, float g, float b, float a = 1);
    static constexpr Color bytes(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 0xFF);

    constexpr unsigned int code() const
    {
      unsigned int color = 0U;
      color |= (r << 24U);
      color |= (g << 16U);
      color |= (b << 8U);
      color |= a;
      return color;
    }

    constexpr float redf() const
    {
      return r / 255.0f;
    }
    constexpr float greenf() const
    {
      return g / 255.0f;
    }
    constexpr float bluef() const
    {
      return b / 255.0f;
    }
    constexpr float alphaf() const
    {
      return a / 255.0f;
    }

    static constexpr Color createWidthHSL(float _h, float _s, float _l, float _a = 1.0f)
    {
      Rgb rgb = ColorConverter::hslToRgb(_h, _s, _l);
      return {rgb.r, rgb.g, rgb.b, Byte(_a * 255)};
    }

    constexpr Color mix(Color c, float ratio) const;
    constexpr Color dim(float amount) const;
    constexpr Color fade(float amount) const;
    constexpr Color brighten(float amount) const;
  };

  constexpr Color Color::floats(float r, float g, float b, float a)
  {
    return Color(r * 255, g * 255, b * 255, a * 255);
  }

  constexpr Color Color::bytes(Byte r, Byte g, Byte b, Byte a)
  {
    return Color(r, g, b, a);
  }

  constexpr Color Color::mix(Color c, float ratio) const
  {
    Color ret;
    ret.r = std::clamp<uint8_t>(r + (c.r - r) * ratio, 0x00, 0xFF);
    ret.g = std::clamp<uint8_t>(g + (c.g - g) * ratio, 0x00, 0xFF);
    ret.b = std::clamp<uint8_t>(b + (c.b - b) * ratio, 0x00, 0xFF);
    ret.a = std::clamp<uint8_t>(a + (c.a - a) * ratio, 0x00, 0xFF);
    return ret;
  }

  constexpr Color Color::dim(float amount) const
  {
    float dim = std::clamp(1.f - amount, 0.f, 1.f);
    Color ret;
    ret.r = std::clamp<uint8_t>(r * dim, 0x00, 0xFF);
    ret.g = std::clamp<uint8_t>(g * dim, 0x00, 0xFF);
    ret.b = std::clamp<uint8_t>(b * dim, 0x00, 0xFF);
    ret.a = a;
    return ret;
  }

  constexpr Color Color::brighten(float amount) const
  {
    Color ret;
    ret.r = std::clamp<uint8_t>(r + (255 - r) * amount, 0x00, 0xFF);
    ret.g = std::clamp<uint8_t>(g + (255 - g) * amount, 0x00, 0xFF);
    ret.b = std::clamp<uint8_t>(b + (255 - b) * amount, 0x00, 0xFF);
    ret.a = a;
    return ret;
  }

  constexpr Color Color::fade(float amount) const
  {
    float fade = std::clamp(1.f - amount, 0.f, 1.f);
    Color ret = *this;;
    ret.a = std::clamp<uint8_t>(a * fade, 0x00, 0xFF);
    return ret;
  }

  namespace DefaultColors {
    constexpr Color ZeroColor = 0U;
    constexpr Color AliceBlue = 0xF0F8FFFF;
    constexpr Color AntiqueWhile = 0xFAEBD7FF;
    constexpr Color Aqua = 0x00FFFFFF;
    constexpr Color Aquamarine = 0x7FFFd4FF;
    constexpr Color Azure = 0xF0FFFFFF;
    constexpr Color Beiqe = 0xF5F5DCFF;
    constexpr Color Bisque = 0xFFE4C4FF;
    constexpr Color Black = 0x000000FF;
    constexpr Color BlanchedAlmond = 0xFFEBCDFF;
    constexpr Color Blue = 0x0000FFFF;
    constexpr Color BlueViolet = 0x8A2BE2FF;
    constexpr Color Brown = 0xA52A2AFF;
    constexpr Color BurlyWood = 0xDEB887FF;
    constexpr Color CadetBlue = 0x5F9EA0FF;
    constexpr Color Chartreuse = 0x7FFF00FF;
    constexpr Color Chocolate = 0xD2691EFF;
    constexpr Color Coral = 0xFF7F50FF;
    constexpr Color CornflowerBlue = 0x6495EDFF;
    constexpr Color Cornsilk = 0xFFF8DCFF;
    constexpr Color Crimson = 0xDC143CFF;
    constexpr Color Cyan = 0x00FFFFFF;
    constexpr Color DarkBlue = 0x00008BFF;
    constexpr Color DarkCyan = 0x008B8BFF;
    constexpr Color DarkGoldenRod = 0xB8860BFF;
    constexpr Color DarkGray = 0xA9A9A9FF;
    constexpr Color DarkGreen = 0x006400FF;
    constexpr Color DarkKhaki = 0xBDB76BFF;
    constexpr Color DarkMagenta = 0x8B008BFF;
    constexpr Color DarkOliveGreen = 0x556B2FFF;
    constexpr Color Darkorange = 0xFF8C00FF;
    constexpr Color DarkOrchid = 0x9932CCFF;
    constexpr Color DarkRed = 0x8B0000FF;
    constexpr Color DarkSalmon = 0xE9967AFF;
    constexpr Color DarkSeaGreen = 0x8FBC8FFF;
    constexpr Color DarkSlateBlue = 0x483D8BFF;
    constexpr Color DarkSlateGray = 0x2F4F4FFF;
    constexpr Color DarkTurquoise = 0x00CED1FF;
    constexpr Color DarkViolet = 0x9400D3FF;
    constexpr Color DeepPink = 0xFF1493FF;
    constexpr Color DeepSkyBlue = 0x00BFFFFF;
    constexpr Color DimGray = 0x696969FF;
    constexpr Color DodgerBlue = 0x1E90FFFF;
    constexpr Color Feldspar = 0xD19275FF;
    constexpr Color FireBrick = 0xB22222FF;
    constexpr Color FloralWhite = 0xFFFAF0FF;
    constexpr Color ForestGreen = 0x228B22FF;
    constexpr Color Fuchsia = 0xFF00FFFF;
    constexpr Color Gainsboro = 0xDCDCDCFF;
    constexpr Color GhostWhite = 0xF8F8FFFF;
    constexpr Color Gold = 0xFFD700FF;
    constexpr Color GoldenRod = 0xDAA520FF;
    constexpr Color Gray = 0x808080FF;
    constexpr Color Green = 0x008000FF;
    constexpr Color GreenYellow = 0xADFF2FFF;
    constexpr Color HoneyDew = 0xF0FFF0FF;
    constexpr Color HotPink = 0xFF69B4FF;
    constexpr Color IndianRed = 0xCD5C5CFF;
    constexpr Color Indigo = 0x4B0082FF;
    constexpr Color Ivory = 0xFFFFF0FF;
    constexpr Color Khaki = 0xF0E68CFF;
    constexpr Color Lavender = 0xE6E6FAFF;
    constexpr Color LavenderBlush = 0xFFF0F5FF;
    constexpr Color LawnGreen = 0x7CFC00FF;
    constexpr Color LemonChiffon = 0xFFFACDFF;
    constexpr Color LightBlue = 0xADD8E6FF;
    constexpr Color LightCoral = 0xF08080FF;
    constexpr Color LightCyan = 0xE0FFFFFF;
    constexpr Color LightGoldenRodYellow = 0xFAFAD2FF;
    constexpr Color LightGrey = 0xD3D3D3FF;
    constexpr Color LightGreen = 0x90EE90FF;
    constexpr Color LightPink = 0xFFB6C1FF;
    constexpr Color LightSalmon = 0xFFA07AFF;
    constexpr Color LightSeaGreen = 0x20B2AAFF;
    constexpr Color LightSkyBlue = 0x87CEFAFF;
    constexpr Color LightSlateBlue = 0x8470FFFF;
    constexpr Color LightSlateGray = 0x778899FF;
    constexpr Color LightSteelBlue = 0xB0C4DEFF;
    constexpr Color LightYellow = 0xFFFFE0FF;
    constexpr Color Lime = 0x00FF00FF;
    constexpr Color LimeGreen = 0x32CD32FF;
    constexpr Color Linen = 0xFAF0E6FF;
    constexpr Color Magenta = 0xFF00FFFF;
    constexpr Color Maroon = 0x800000FF;
    constexpr Color MediumAquaMarine = 0x66CDAAFF;
    constexpr Color MediumBlue = 0x0000CDFF;
    constexpr Color MediumOrchid = 0xBA55D3FF;
    constexpr Color MediumPurple = 0x9370D8FF;
    constexpr Color MediumSeaGreen = 0x3CB371FF;
    constexpr Color MediumSlateBlue = 0x7B68EEFF;
    constexpr Color MediumSpringGreen = 0x00FA9AFF;
    constexpr Color MediumTurquoise = 0x48D1CCFF;
    constexpr Color MediumVioletRed = 0xC71585FF;
    constexpr Color MidnightBlue = 0x191970FF;
    constexpr Color MintCream = 0xF5FFFAFF;
    constexpr Color MistyRose = 0xFFE4E1FF;
    constexpr Color Moccasin = 0xFFE4B5FF;
    constexpr Color NavajoWhite = 0xFFDEADFF;
    constexpr Color Navy = 0x000080FF;
    constexpr Color OldLace = 0xFDF5E6FF;
    constexpr Color Olive = 0x808000FF;
    constexpr Color OliveDrab = 0x6B8E23FF;
    constexpr Color Orange = 0xFFA500FF;
    constexpr Color OrangeRed = 0xFFA500FF;
    constexpr Color Orchid = 0xDA70D6FF;
    constexpr Color PaleGoldenRod = 0xEEE8AAFF;
    constexpr Color PaleGreen = 0x98FB98FF;
    constexpr Color PaleTurquoise = 0xAFEEEEFF;
    constexpr Color PaleVioletRed = 0xD87093FF;
    constexpr Color PapayaWhip = 0xFFEFD5FF;
    constexpr Color PeachPuff = 0xFFDAB9FF;
    constexpr Color Peru = 0xCD853FFF;
    constexpr Color Pink = 0xFFC0CBFF;
    constexpr Color Plum = 0xDDA0DDFF;
    constexpr Color PowderBlue = 0xB0E0E6FF;
    constexpr Color Purple = 0x800080FF;
    constexpr Color Red = 0xFF0000FF;
    constexpr Color RosyBrown = 0xBC8F8FFF;
    constexpr Color RoyalBlue = 0x4169E1FF;
    constexpr Color SaddleBrown = 0x8B4513FF;
    constexpr Color Salmon = 0xFA8072FF;
    constexpr Color SandyBrown = 0xF4A460FF;
    constexpr Color SeaGreen = 0x2E8B57FF;
    constexpr Color SeaShell = 0xFFF5EEFF;
    constexpr Color Sienna = 0xA0522DFF;
    constexpr Color Silver = 0xC0C0C0FF;
    constexpr Color SkyBlue = 0x87CEEBFF;
    constexpr Color SlateBlue = 0x6A5ACDFF;
    constexpr Color SlateGray = 0x708090FF;
    constexpr Color Snow = 0xFFFAFAFF;
    constexpr Color SpringGreen = 0x00FF7FFF;
    constexpr Color SteelBlue = 0x4682B4FF;
    constexpr Color Tan = 0xD2B48CFF;
    constexpr Color Teal = 0x008080FF;
    constexpr Color Thistle = 0xD8BFD8FF;
    constexpr Color Tomato = 0xFF6347FF;
    constexpr Color Turquoise = 0x40E0D0FF;
    constexpr Color Violet = 0xEE82EEFF;
    constexpr Color VioletRed = 0xD02090FF;
    constexpr Color Wheat = 0xF5DEB3FF;
    constexpr Color White = 0xFFFFFFFF;
    constexpr Color WhiteSmoke = 0xF5F5F5FF;
    constexpr Color Yellow = 0xFFFF00FF;
    constexpr Color YellowGreen = 0x9ACD32FF;
  } // namespace DefaultColors

  /** @brief Get hex code string from color */
  std::string to_string(const Color& color);
} // namespace otto::nvg
