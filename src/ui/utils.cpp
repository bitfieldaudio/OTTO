#include "utils.h"

namespace drawing {

Font FONT_LIGHT;

void initUtils(Canvas &canvas) {
  FONT_LIGHT = Font(canvas, "Lato Light", "./fonts/Lato/Lato-Light.ttf");
}
}
