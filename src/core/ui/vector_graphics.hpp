#pragma once

#include <fmt/format.h>
#include "core/ui/canvas.hpp"
#include "services/log_manager.hpp"
#include "util/filesystem.hpp"

namespace otto::core::ui::vg {

  constexpr float width = 320;
  constexpr float height = 240;

  namespace Colours {
    const Colour Black = Colour(0x000000FF);

    const MainColour White = {0xFFFFFFFF, 0x646464FF};
    const MainColour Yellow = {0xFAB700FF, 0x646464FF};
    const MainColour Red = {0xE6332AFF, 0x6E0C0CFF};
    const MainColour Green = {0x5ECF3EFF, 0x0C6E0CFF};
    const MainColour Blue = {0x009EE3FF, 0x0C0C6EFF};

    const Colour Gray50 = 0x646464FF;
    const Colour Gray60 = 0x999999FF;
    const Colour Gray70 = 0xB2B2B2FF;

    const Colour Pink = 0xEE7AAAFF;
  } // namespace Colours

  namespace Fonts {
    inline Font Light;
    inline Font Norm;
    inline Font Bold;

    inline const fs::path font_dir{"data/fonts"};

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
  } // namespace Fonts

  inline void initUtils(Canvas& ctx)
  {
    Fonts::loadFont(ctx, Fonts::Light, "Roboto-Light");
    Fonts::loadFont(ctx, Fonts::Norm, "Roboto-Medium");
    Fonts::loadFont(ctx, Fonts::Bold, "Roboto-Black");
  }

} // namespace otto::core::ui::vg
