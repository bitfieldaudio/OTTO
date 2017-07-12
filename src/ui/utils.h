#pragma once

#include "../util/typedefs.h"

#include <nanovg.h>
#include <nanocanvas/NanoCanvas.h>
#include <fmt/format.h>

#include "../utils.h"

namespace drawing {
using NanoCanvas::Canvas;
using NanoCanvas::HorizontalAlign;
using NanoCanvas::VerticalAlign;
namespace TextAlign {using namespace NanoCanvas::TextAlign;}
using NanoCanvas::TextStyle;
using NanoCanvas::Font;

const uint WIDTH = 320;
const uint HEIGHT = 240;

struct Colour {

  byte r;
  byte g;
  byte b;
  byte a = 0xFF;

  Colour(float, float, float, float a = 1);
  Colour(uint32 data) {
    r = byte((data >> 16) & 0x0000FF);
    g = byte((data >> 8) & 0x0000FF);
    b = byte((data) & 0x0000FF);
    a = 0xFF;
  };
  Colour();

  Colour mix(Colour c, float ratio) const;
  Colour dim(float amount) const;
  Colour brighten(float amount) const;

  operator NanoCanvas::Color() const {
    return NanoCanvas::Color(r, g, b, a);
  }
};

inline Colour::Colour(float r, float g, float b, float a) :
  r (r * 255), g (g * 255), b (b * 255)  {}


inline Colour::Colour() : Colour(244,0,0) {}

inline Colour Colour::mix(Colour c, float ratio) const {
  Colour ret;
  ret.r = top1::withBounds<byte>(0, 255, r + (c.r - r ) * ratio);
  ret.g = top1::withBounds<byte>(0, 255, g + (c.g - g ) * ratio);
  ret.b = top1::withBounds<byte>(0, 255, b + (c.b - b ) * ratio);
  ret.a = top1::withBounds<byte>(0, 255, a + (c.a - a ) * ratio);
  return ret;
}

inline Colour Colour::dim(float amount) const {
  float dim = 1 - amount;
  Colour ret;
  ret.r = top1::withBounds<byte>(0, 255, r * dim);
  ret.g = top1::withBounds<byte>(0, 255, g * dim);
  ret.b = top1::withBounds<byte>(0, 255, b * dim);
  ret.a = a;
  return ret;
}

inline Colour Colour::brighten(float amount) const {
  Colour ret;
  ret.r = top1::withBounds<byte>(0, 255, r + (255 - r) * amount);
  ret.g = top1::withBounds<byte>(0, 255, g + (255 - g) * amount);
  ret.b = top1::withBounds<byte>(0, 255, b + (255 - b) * amount);
  ret.a = a;
  return ret;
}

struct MainColour : public Colour {

  const Colour dimmed;

  MainColour(Colour basic) :
    Colour (basic),
    dimmed (basic.dim(0.3)) {}

  MainColour(Colour basic, Colour dimmed) :
    Colour (basic),
    dimmed (dimmed) {}

  MainColour(uint32 basic) :
    Colour (basic),
    dimmed (dim(0.3)) {}

  MainColour(uint32 basic, uint32 dimmed) :
    Colour (basic),
    dimmed (dimmed) {}

  using Colour::operator NanoCanvas::Color;
};

namespace Colours {

static const Colour Black     = Colour(0x000000);

static const MainColour White = {0xFFFFFF, 0x646464};
static const MainColour Red   = {0xFF2A2A, 0x6E0C0C};
static const MainColour Green = {0x5ECF3E, 0x0C6E0C};
static const MainColour Blue  = {0x0A7CFF, 0x0C0C6E};

static const Colour Gray60    = 0x999999;
static const Colour Gray70    = 0xB2B2B2;

}

extern Font FONT_LIGHT;
extern Font FONT_NORM;
extern Font FONT_BOLD;

void initUtils(Canvas &canvas);

}
