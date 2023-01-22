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

  static util::enum_map<Key, skia::Box> generate_key_areas()
  {
    util::enum_map<Key, skia::Box> res;
    float side_length = 66;
    skia::Point origin;
    for (auto y = 0; y < 4; y++) {
      origin = {1096, 45};
      for (auto x = 0; x < 5; x++) {
        auto box = skia::Box{{origin.x() + x * side_length, origin.y() + y * side_length}, {60, 60}};
        res[function_keys[y * 7 + x]] = box;
      }
      // Func Group 2
      origin = {1460, 45};
      for (auto x = 0; x < 2; x++) {
        auto box = skia::Box{{origin.x() + x * side_length, origin.y() + y * side_length}, {60, 60}};
        res[function_keys[y * 7 + 5 + x]] = box;
      }
    }
    // Channel
    origin = {170, 344};
    side_length = 99;
    std::array<int, 10> the_black_keys = {0, 1, 3, 4, 5, 7, 8, 10, 11, 12};
    for (auto i = 0; i < 10; i++) {
      auto x = the_black_keys[i];
      auto box = skia::Box{{origin.x() + x * side_length, origin.y()}, {90, 83}};
      res[channel_key(i).value()] = box;
    }
    // Seq
    origin = {23, 428};
    for (auto x = 0; x < 16; x++) {
      auto box = skia::Box{{origin.x() + x * side_length, origin.y()}, {90, 90}};
      res[seq_key(x).value()] = box;
    }

    // Encoders
    res[Key::blue_enc_click] = skia::Box({74, 194}, {85, 85});
    res[Key::green_enc_click] = skia::Box({224, 86}, {85, 85});
    res[Key::yellow_enc_click] = skia::Box({371, 194}, {85, 85});
    res[Key::red_enc_click] = skia::Box({521, 86}, {85, 85});

    return res;
  }

  static const auto key_areas = generate_key_areas();


  void Emulator::draw_leds(skia::Canvas& ctx)
  {
    for (auto&& [k, box] : key_areas) {
      if (auto led = led_from(k)) {
        auto color = get_led_color(*led);
        ctx.drawRect(box, otto::paints::fill(color));
      }
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

    auto lc = (*port->led_colors.lock())[led];
    auto skc = skia::Color::bytes(lc.r, lc.g, lc.b);
    skc = skia::Color::floats(0.2, 0.2, 0.2) + skc.dim(0.2f);
    return skc;
  }

  void Emulator::run(std::function<bool(skia::Canvas&)> f)
  {
    glfw_.request_size(size);
    glfw_.window.emplace(size.x(), size.y(), "OTTO Emulator");
    auto& window = *glfw_.window;
    window.mouse_button_callback = BIND_THIS(handle_click);
    window.scroll_callback = BIND_THIS(handle_scroll);
    glfw_.run([&, f = std::move(f)](skia::Canvas& ctx) {
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
  static tl::optional<Key> key_at(skia::Point p)
  {
    for (auto&& [k, box] : key_areas) {
      if (box.contains(p)) return k;
    }
    return tl::nullopt;
  }

  void Emulator::handle_click(glfw::Button b, glfw::Action a, glfw::Modifiers m)
  {
    auto key = key_at(glfw_.window->skia_cursor_pos());
    if (key && (drivers::GlfwMCUPort::instance != nullptr)) {
      if (a == glfw::Action::press) {
        drivers::GlfwMCUPort::instance->handle(KeyPress{{*key}});
      }
      if (a == glfw::Action::release) {
        drivers::GlfwMCUPort::instance->handle(KeyRelease{{*key}});
      }
    }
  }

  void Emulator::handle_scroll(double x, double y)
  {
    auto key = key_at(glfw_.window->skia_cursor_pos());
    int clicks = y;
    if (key && (drivers::GlfwMCUPort::instance != nullptr)) {
      Encoder enc;
      if (key == Key::blue_enc_click) {
        enc = Encoder::blue;
      } else if (key == Key::green_enc_click) {
        enc = Encoder::green;
      } else if (key == Key::yellow_enc_click) {
        enc = Encoder::yellow;
      } else if (key == Key::red_enc_click) {
        enc = Encoder::red;
      } else {
        return;
      }
      drivers::GlfwMCUPort::instance->handle(EncoderEvent{{enc, clicks}});
    }
  }

} // namespace otto::board

// kak: other_file=../include/board/emulator.hpp
