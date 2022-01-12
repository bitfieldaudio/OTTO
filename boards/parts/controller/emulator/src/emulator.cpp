#include "board/emulator.hpp"

#include <SkImageInfo.h>

#include "board/ui/glfw_ui.hpp"

namespace otto::board {

  /// Render emulator SVG at higher scale
  constexpr float scale_factor = 1;

  Emulator::Emulator()
  {
    auto path = globals::resource_dir() / "emulator_front.svg";
    auto document = lunasvg::Document::loadFromFile(path);
    if (!document) {
      LOGC("Could not load emulator texture from {}", path);
      std::terminate();
    }
    // document->scale(scale_factor, scale_factor);
    svg_bitmap = document->renderToBitmap(size.x() * scale_factor, size.y() * scale_factor, 0x00000000);

    image_info = skia::ImageInfo::Make(size.x() * scale_factor, size.y() * scale_factor, kRGBA_8888_SkColorType,
                                       kUnpremul_SkAlphaType);

    auto pixmap = skia::Pixmap(image_info, svg_bitmap.data(), size.x() * scale_factor * 4);
    image = skia::Image::MakeRasterCopy(pixmap);
  }

  void Emulator::draw_bg(skia::Canvas& ctx)
  {
    ctx.drawRect(skia::Rect::MakeXYWH(0, 0, size.x(), size.y()), otto::paints::fill(colors::black));
  }

  constexpr std::array<Key, 28> function_keys = {
    Key::page_a, Key::arp,       Key::synth,   Key::envelope, Key::voices, Key::settings, Key::master, //
    Key::page_b, Key::external,  Key::sends,   Key::fx1,      Key::fx2,    Key::minus,    Key::plus,   //
    Key::page_c, Key::sequencer, Key::sampler, Key::looper,   Key::mixer,  Key::record,   Key::play,   //
    Key::page_d, Key::shift,     Key::sigma,   Key::omega,    Key::slots,  Key::twist1,   Key::twist2, //
  };

  void Emulator::draw_leds(skia::Canvas& ctx)
  {
    // Func Group 1
    float side_length = 66;
    skia::Point origin;
    for (auto y = 0; y < 4; y++) {
      origin = {1116, 65};
      for (auto x = 0; x < 5; x++) {
        auto color = get_led_color(led_from(function_keys[y * 7 + x]).value());
        ctx.drawCircle({origin.x() + x * side_length, origin.y() + y * side_length}, 20, otto::paints::fill(color));
      }
      // Func Group 2
      origin = {1480, 65};
      for (auto x = 0; x < 2; x++) {
        auto color = get_led_color(led_from(function_keys[y * 7 + 5 + x]).value());
        ctx.drawCircle({origin.x() + x * side_length, origin.y() + y * side_length}, 20, otto::paints::fill(color));
      }
    }
    // Channel
    origin = {190, 344};
    side_length = 99;
    std::array<int, 10> the_black_keys = {0, 1, 3, 4, 5, 7, 8, 10, 11, 12};
    for (auto i = 0; i < 10; i++) {
      auto x = the_black_keys[i];
      auto color = get_led_color(led_from(channel_key(i).value()).value());
      ctx.drawRect(skia::Rect::MakeXYWH(origin.x() + x * side_length, origin.y(), 50, 15), otto::paints::fill(color));
    }
    // Seq
    origin = {43, 428};
    for (auto x = 0; x < 16; x++) {
      auto color = get_led_color(led_from(seq_key(x).value()).value());
      ctx.drawRect(skia::Rect::MakeXYWH(origin.x() + x * side_length, origin.y(), 50, 15), otto::paints::fill(color));
    }
  }

  void Emulator::draw_frontpanel(skia::Canvas& ctx)
  {
    skia::saved(ctx, [&] {
      ctx.scale(1 / scale_factor, 1 / scale_factor);
      ctx.drawImage(image, 0, 0);
    });
  }

  skia::Color Emulator::get_led_color(Led led)
  {
    auto* port = drivers::GlfwMCUPort::instance;
    if (port == nullptr) return colors::blue;

    auto lc = port->led_colors[led];
    return skia::Color::bytes(lc.r, lc.g, lc.b);
  }

  void Emulator::run(std::function<bool(skia::Canvas&)> f)
  {
    glfw_.request_size(size);
    glfw_.run([this, f = std::move(f)](skia::Canvas& ctx) {
      draw_bg(ctx);
      draw_leds(ctx);
      draw_frontpanel(ctx);
      bool res = false;
      skia::saved(ctx, [&] {
        skia::translate(ctx, {703, 53});
        res = f(ctx);
      });
      return res;
    });
  }

} // namespace otto::board

// kak: other_file=../include/board/emulator.hpp
