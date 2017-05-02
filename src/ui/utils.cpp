#include "utils.h"
#include <plog/Log.h>

namespace drawing {

Font FONT_LIGHT;

void initUtils(Canvas &canvas) {
  FONT_LIGHT = Font(canvas, "Lato Light", "./fonts/Lato/Lato-Light.ttf");
  if (!FONT_LIGHT.valid()) {
    LOGE << "Invalid font: " << FONT_LIGHT.name;
  }
}
}
