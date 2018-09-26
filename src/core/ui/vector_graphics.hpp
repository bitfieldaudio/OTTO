#pragma once

#include <fmt/format.h>
#include "util/filesystem.hpp"
#include "core/ui/canvas.hpp"
#include "services/logger.hpp"

namespace otto::core::ui::vg {

  constexpr float width = 320;
  constexpr float height = 240;

  namespace Colours {
    const Colour Black      = Colour(0x000000);

    const MainColour White  = {0xFFFFFF, 0x646464};
    const MainColour Yellow = {0xFAB700, 0x646464};
    const MainColour Red    = {0xE6332A, 0x6E0C0C};
    const MainColour Green  = {0x5ECF3E, 0x0C6E0C};
    const MainColour Blue   = {0x009EE3, 0x0C0C6E};

    const Colour Gray50     = 0x646464;
    const Colour Gray60     = 0x999999;
    const Colour Gray70     = 0xB2B2B2;

    const Colour Pink       = 0xEE7AAA;
  } // Colours

  namespace Fonts {
    inline Font Light;
    inline Font Norm;
    inline Font Bold;

    inline const fs::path font_dir {"data/fonts"};

    inline void loadFont(Canvas& ctx, Font& font, const std::string& name)
    {
      auto path = Fonts::font_dir / (name + ".ttf");
      font = Font(ctx, name, path);
      if (!Fonts::Light.valid()) {
        LOG_F(ERROR, "Invalid font: {}", Fonts::Light.name);
        if (!fs::exists(path)) {
          LOG_F(ERROR, "Font file not found: {}", path);
        }
      }
    }
  }

  inline void initUtils(Canvas& ctx) {
    Fonts::loadFont(ctx, Fonts::Light, "Roboto-Light");
    Fonts::loadFont(ctx, Fonts::Norm, "Roboto-Medium");
    Fonts::loadFont(ctx, Fonts::Bold, "Roboto-Black");
  }

} // ui::drawing
