#include "utils.h"
#include <plog/Log.h>

namespace drawing {

Font FONT_LIGHT;
Font FONT_NORM;
Font FONT_BOLD;

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
}
