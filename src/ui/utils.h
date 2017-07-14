#pragma once

#include "../util/typedefs.h"
#include <fmt/format.h>

#include "../utils.h"
#include "canvas.h"

namespace drawing {

const uint WIDTH = 320;
const uint HEIGHT = 240;

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
