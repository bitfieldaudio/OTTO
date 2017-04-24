#pragma once

#include <nanovg.h>
#include <nanocanvas/NanoCanvas.h>
#include <cstdlib>

namespace drawing {
using namespace NanoCanvas;

const uint WIDTH = 320;
const uint HEIGHT = 240;

const auto COLOR_BLACK = Color(0,0,0);
const auto COLOR_WHITE = Color(1.0f,1.0,1.0);
const auto COLOR_RED = Color(1.0f, 0.20,0.20);
const auto COLOR_BLUE = Color(0.0f,0.0,1.0);
const auto COLOR_GREEN = Color(0.0f,1.0,0.0);

const auto COLOR_CURRENT_TRACK = Color(255, 74, 74);
const auto COLOR_OTHER_TRACK = Color(80, 80, 80);
const auto COLOR_LOOP_MARKER = Color(0, 128, 0);
const auto COLOR_BAR_MARKER = Color(204, 204, 204);

extern Font FONT_LIGHT;

void initUtils(Canvas &canvas);

}
