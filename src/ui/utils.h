#pragma once

#include <nanovg/nanovg.h>
#include <cstdlib>

namespace drawing {

const uint WIDTH = 320;
const uint HEIGHT = 240;

const auto COLOR_BLACK = nvgRGBf(0,0,0);
const auto COLOR_WHITE = nvgRGBf(1,1,1);
const auto COLOR_RED = nvgRGBf(1,0.20,0.20);
const auto COLOR_BLUE = nvgRGBf(0,0,1);
const auto COLOR_GREEN = nvgRGBf(0,1,0);

//const auto FONT_TITLE = Pango::FontDescription("Lato Light 40");
//const auto FONT_SUBTITLE = Pango::FontDescription("Lato Light 12");
//const auto FONT_BIG_NUM = Pango::FontDescription("Lato Light 21");
//const auto FONT_INFO = Pango::FontDescription("Lato Light 12");
}
