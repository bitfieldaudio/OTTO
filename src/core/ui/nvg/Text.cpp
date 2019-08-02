#include "Canvas.hpp"
#include "Text.hpp"

#include <nanovg.h>

namespace otto::nvg {
  Font::Font(Canvas& canvas, const std::string& fname, const std::string& ttfPath)
  {
    if (canvas.valid() && fname.length() && ttfPath.length()) {
      face = nvgCreateFont(canvas.nvgContext(), fname.c_str(), ttfPath.c_str());
    }
    name = fname;
  }

  Font::Font(Canvas& canvas, const std::string& fname, const Memery& memory, bool invalidateMem)
  {
    if (canvas.valid() && memory.valid() && fname.length()) {
      face =
        nvgCreateFontMem(canvas.nvgContext(), fname.c_str(), (unsigned char*) memory.data, memory.size, invalidateMem);
    }
    name = fname;
  }
} // namespace NanoCanvas
