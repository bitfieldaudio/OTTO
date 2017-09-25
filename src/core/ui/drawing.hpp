#pragma once

#include <fmt/format.h>
#include <plog/Log.h>

#include "util/typedefs.hpp"
#include "filesystem.hpp"

#include "core/ui/canvas.hpp"

namespace top1::ui::drawing {

  const uint WIDTH = 320;
  const uint HEIGHT = 240;

  namespace Colours {

    const Colour Black     = Colour(0x000000);

    const MainColour White = {0xFFFFFF, 0x646464};
    const MainColour Red   = {0xFF2A2A, 0x6E0C0C};
    const MainColour Green = {0x5ECF3E, 0x0C6E0C};
    const MainColour Blue  = {0x0A7CFF, 0x0C0C6E};

    const Colour Gray60    = 0x999999;
    const Colour Gray70    = 0xB2B2B2;

  } // Colours

  namespace Fonts {
    inline Font Light;
    inline Font Norm;
    inline Font Bold;
    inline Font SemiBold;
    inline Font Mono;

    inline fs::path font_dir {"data/fonts"};
    inline void loadFont(Canvas& ctx, Font& font, const std::string& name)
    {
      auto path = Fonts::font_dir / (name + ".ttf");
      font = Font(ctx, name, path);
      if (!Fonts::Light.valid()) {
        LOGE << "Invalid font: " << Fonts::Light.name << "";
        if (!fs::exists(path)) {
          LOGE << "Font file not found: " << path.c_str();
        }
      }
    }
  }

  inline void initUtils(Canvas& ctx) {
    Fonts::loadFont(ctx, Fonts::Light, "TOP-1-Light");
    Fonts::loadFont(ctx, Fonts::Norm, "TOP-1-Regular");
    Fonts::loadFont(ctx, Fonts::Bold, "TOP-1-Bold");
    Fonts::loadFont(ctx, Fonts::SemiBold, "TOP-1-SemiBold");
    Fonts::loadFont(ctx, Fonts::Mono, "TOP-1-Mono-Regular");
  }

} // ui::drawing
