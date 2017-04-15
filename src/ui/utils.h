#pragma once

#include <cairomm/pattern.h>

namespace drawing {

const uint WIDTH = 320;
const uint HEIGHT = 240;

auto COLOUR_BLACK = Cairo::SolidPattern::create_rgb(0,0,0);
auto COLOUR_WHITE = Cairo::SolidPattern::create_rgb(1,1,1);
}
