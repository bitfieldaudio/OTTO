#pragma once

#include "util/typedefs.hpp"

#include <fmt/format.h>
#include <plog/Log.h>

#include "core/ui/canvas.hpp"

namespace ui::drawing {

static const uint WIDTH = 320;
static const uint HEIGHT = 240;

namespace Colours {

static const Colour Black     = Colour(0x000000);

static const MainColour White = {0xFFFFFF, 0x646464};
static const MainColour Red   = {0xFF2A2A, 0x6E0C0C};
static const MainColour Green = {0x5ECF3E, 0x0C6E0C};
static const MainColour Blue  = {0x0A7CFF, 0x0C0C6E};

static const Colour Gray60    = 0x999999;
static const Colour Gray70    = 0xB2B2B2;

} // Colours

inline static Font FONT_LIGHT;
inline static Font FONT_NORM;
inline static Font FONT_BOLD;

void initUtils(Canvas &canvas) {
  FONT_LIGHT = Font(canvas, "Lato Light", "./fonts/Lato/Lato-Light.ttf");
  if (!FONT_LIGHT.valid()) {
    LOGE << "Invalid font: " << FONT_LIGHT.name;
  }
  FONT_NORM = Font(canvas, "Lato Regular", "./fonts/Lato/Lato-Regular.ttf");
  if (!FONT_NORM.valid()) {
    LOGE << "Invalid font: " << FONT_NORM.name;
  }
  FONT_BOLD = Font(canvas, "Lato Bold", "./fonts/Lato/Lato-Bold.ttf");
  if (!FONT_BOLD.valid()) {
    LOGE << "Invalid font: " << FONT_BOLD.name;
  }
}

} // ui::drawing
