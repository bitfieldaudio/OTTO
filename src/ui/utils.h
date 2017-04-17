#pragma once

#include <cairomm/pattern.h>
#include <pangomm/fontdescription.h>

namespace drawing {

const uint WIDTH = 320;
const uint HEIGHT = 240;

const auto COLOUR_BLACK = Cairo::SolidPattern::create_rgb(0,0,0);
const auto COLOUR_WHITE = Cairo::SolidPattern::create_rgb(1,1,1);

const auto FONT_TITLE = Pango::FontDescription("Lato Light 40");
const auto FONT_SUBTITLE = Pango::FontDescription("Lato Light 12");
const auto FONT_BIG_NUM = Pango::FontDescription("Lato Light 24");
const auto FONT_INFO = Pango::FontDescription("Lato Light 12");
}
