#pragma once

#include <fmt/format.h>
#include <fmt/ostream.h>

#include <choreograph/Choreograph.h>

#include "core/ui/canvas.hpp"
#include "services/log_manager.hpp"
#include "util/filesystem.hpp"

namespace otto::core::ui::vg {

  constexpr float width = 320;
  constexpr float height = 240;

  namespace Colors {
    constexpr Color Black = Color(0x000000FF);

    constexpr MainColor White = {0xFFFFFFFF, 0x646464FF};
    constexpr MainColor Yellow = {0xFAB700FF, 0x646464FF};
    constexpr MainColor Red = {0xE6332AFF, 0x6E0C0CFF};
    constexpr MainColor Green = {0x5ECF3EFF, 0x0C6E0CFF};
    constexpr MainColor Blue = {0x009EE3FF, 0x0C0C6EFF};

    constexpr Color Gray50 = 0x646464FF;
    constexpr Color Gray60 = 0x999999FF;
    constexpr Color Gray70 = 0xB2B2B2FF;

    constexpr Color Pink = 0xEE7AAAFF;
  } // namespace Colours

  namespace Colours = Colors;

  namespace Fonts {
    inline Font Light;
    inline Font Norm;
    inline Font Bold;

    inline Font LightItalic;
    inline Font NormItalic;
    inline Font BoldItalic;

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
    Fonts::loadFont(ctx, Fonts::LightItalic, "Roboto-LightItalic");
    Fonts::loadFont(ctx, Fonts::NormItalic, "Roboto-MediumItalic");
    Fonts::loadFont(ctx, Fonts::BoldItalic, "Roboto-BlackItalic");
  }

  /// Get the Choreograph timeline
  /// 
  /// This is stepped on each frame in the UIManager
  inline ch::Timeline& timeline() {
    static ch::Timeline timeline;
    return timeline;
  }
} // namespace otto::core::ui::vg
