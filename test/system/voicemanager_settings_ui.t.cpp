#include "testing.t.hpp"

#include <string>

#include <SkFont.h>
#include <SkPath.h>
#include <SkRRect.h>
#include <SkTextBlob.h>
#include <SkTypeface.h>
#include <choreograph/Choreograph.h>
#include <fmt/format.h>

#include "lib/skia/skia.hpp"
#include "lib/widget.hpp"

#include "app/services/config.hpp"
#include "app/services/graphics.hpp"

using namespace otto;
using namespace otto::services;

//////////////////

enum struct PlayMode { poly, mono, unison, interval };

static std::string aux_setting(PlayMode pm) noexcept
{
  switch (pm) {
    case PlayMode::poly: return "RANDOM";
    case PlayMode::mono: return "SUB OSC.";
    case PlayMode::unison: return "DETUNE";
    case PlayMode::interval: return "INTERVAL";
  };
  return "";
}

static std::string playmode_string(PlayMode pm) noexcept
{
  switch (pm) {
    case PlayMode::poly: return "POLY";
    case PlayMode::mono: return "MONO";
    case PlayMode::unison: return "UNISON";
    case PlayMode::interval: return "DUO";
  };
  return "";
}

static std::string aux_value_string(PlayMode pm) noexcept
{
  switch (pm) {
    case PlayMode::poly: return "0.2";
    case PlayMode::mono: return "0.3";
    case PlayMode::unison: return "0.5";
    case PlayMode::interval: return "-3";
  };
  return "";
}

constexpr std::array<PlayMode, 4> playmodes = {PlayMode::poly, PlayMode::mono, PlayMode::unison, PlayMode::interval};
struct VoiceModes : otto::graphics::Widget<VoiceModes> {
  int active_line;
  float rand;
  float sub;
  int interval;
  float detune;
  VoiceModes(int a, float r, float s, int i, float d) : active_line(a), rand(r), sub(s), interval(i), detune(d) {}

  void do_draw(skia::Canvas& ctx)
  {
    float height = bounding_box.height();
    float width = bounding_box.width();
    // Set up x-coordinates
    float mode_text_x = width * 0.03f;
    float division_x = width * 0.382f; // Golden ratio
    float aux_text_x = width * 0.412f;
    float aux_value_x = width * 0.97f;

    // Set up y-coordinates
    float subject_height = 15.f;
    float line_size = (height - subject_height) / 4;

    auto draw_line = [&](skia::Canvas& ctx, bool active, float y, int i) {
      // Background squares
      if (active) {
        skia::RRect left_rect = skia::RRect::MakeRectXY(skia::Rect::MakeXYWH(0, y, width, line_size), 10.f, 10.f);
        ctx.drawRRect(left_rect, paints::fill(colors::blue));
        ctx.drawRRect(left_rect, paints::stroke(colors::black, 1.f));

        skia::RRect right_rect =
          skia::RRect::MakeRectXY(skia::Rect::MakeXYWH(division_x, y, width - division_x, line_size), 10.f, 10.f);
        ctx.drawRRect(right_rect, paints::fill(colors::green.dim(0.3f)));
        ctx.drawRRect(right_rect, paints::stroke(colors::black, 4.f));
      }

      skia::place_text(ctx, playmode_string(playmodes[i]), fonts::medium(24),
                       paints::fill(active ? colors::white : colors::grey50), {mode_text_x, y + line_size * 0.5},
                       anchors::middle_left);
      skia::place_text(ctx, aux_setting(playmodes[i]), fonts::medium(24),
                       paints::fill(active ? colors::white : colors::grey50), {aux_text_x, y + line_size * 0.5},
                       anchors::middle_left);
      skia::place_text(ctx, aux_value_string(playmodes[i]), fonts::medium(24),
                       paints::fill(active ? colors::white : colors::grey50), {aux_value_x, y + line_size * 0.5},
                       anchors::middle_right);
    };

    // Top text
    skia::Paint p = paints::fill(colors::white);
    skia::place_text(ctx, "MODE", fonts::regular(18.f), p, {mode_text_x, 0}, anchors::top_left);
    skia::place_text(ctx, "SETTING", fonts::regular(18.f), p, {aux_text_x, 0}, anchors::top_left);
    skia::place_text(ctx, "VALUE", fonts::regular(18.f), p, {aux_value_x, 0}, anchors::top_right);
    // Modes
    int active_mode = 2;
    for (int i = 0; i < 4; i++) {
      draw_line(ctx, i == active_mode, subject_height + float(i) * line_size, i);
    }
  }
};

struct Portamento : otto::graphics::Widget<Portamento> {
  float value;
  Portamento(float v) : value(v) {}

  void do_draw(skia::Canvas& ctx)
  {
    float height = bounding_box.height();
    float width = bounding_box.width();
    // Yellow Main Box (Fill)
    skia::RRect main_box = skia::RRect::MakeRectXY(skia::Rect::MakeXYWH(0, 0, width, height), 10.f, 10.f);
    ctx.drawRRect(main_box, paints::fill(colors::yellow));
    // Black covering box
    skia::Rect cover_box = skia::Rect::MakeXYWH(width * value, 0, width * (1 - value), height);
    ctx.drawRect(cover_box, paints::fill(colors::black));
    // Yellow Main Box (Stroke)
    ctx.drawRRect(main_box, paints::stroke(colors::yellow, 3.f));

    // Text
    skia::Paint p = paints::fill(colors::black);
    skia::place_text(ctx, "PORTAMENTO TIME", fonts::medium(18), p, {width / 2.f, height / 2.f}, anchors::center);
    ctx.save();
    ctx.clipRect(cover_box);
    p.setColor(colors::white);
    skia::place_text(ctx, "PORTAMENTO TIME", fonts::medium(18), p, {width / 2.f, height / 2.f}, anchors::center);
    ctx.restore();
  }
};

struct LegatoGraphic : otto::graphics::Widget<LegatoGraphic> {
  int value;
  LegatoGraphic(int v) : value(v) {}

  void do_draw(skia::Canvas& ctx)
  {
    float height = bounding_box.height();
    float width = bounding_box.width();

    skia::Paint p = paints::fill(colors::white);
    // Text
    skia::place_text(ctx, "LEGATO", fonts::regular(18), p, {0, 0}, anchors::top_left);


    auto set_color = [&](int i) {
      if (i == value) {
        p.setColor(colors::red);
      } else {
        p.setColor(colors::grey50);
      }
    };
    set_color(0);
    skia::place_text(ctx, "OFF", fonts::medium(24), p, {0, height}, anchors::bottom_left);
    set_color(1);
    skia::place_text(ctx, "ENV.", fonts::medium(24), p, {width * 0.2, height}, anchors::bottom_left);
    set_color(2);
    skia::place_text(ctx, "RETRIG", fonts::medium(24), p, {width * 0.44, height}, anchors::bottom_left);
    set_color(3);
    skia::place_text(ctx, "BOTH", fonts::medium(24), p, {width, height}, anchors::bottom_right);
  }
};


TEST_CASE ("voicemanager-graphics", "[.interactive]") {
  using namespace otto::graphics;
  namespace ch = choreograph;
  ch::Timeline timeline;
  ch::Output<float> expansion = 1.0f;
  auto sequence = ch::Sequence<float>(expansion.value())
                    .then<ch::RampTo>(0.f, 2.0f, ch::EaseInOutQuad())
                    .then<ch::Hold>(0.f, 1.f)
                    .then<ch::RampTo>(1.0f, 2.0f, ch::EaseInOutQuad())
                    .then<ch::Hold>(1.f, 1.f);

  auto looped = makeRepeat<float>(sequence.asPhrase(), 100.f);

  timeline.apply(&expansion, looped);


  RuntimeController rt;
  Graphics graphics(rt);
  SECTION ("Voicemanager") {
    PlayMode play_mode = PlayMode::poly;
    std::string play_mode_str = playmode_string(play_mode);
    std::string aux_name = aux_setting(play_mode);
    std::string aux_value = aux_value_string(play_mode);



    auto stop = graphics.show([&](skia::Canvas& ctx) {
      constexpr float x_pad = 30;
      constexpr float y_pad = 50;
      constexpr float y_shift = -12;
      float space = (skia::height - 2.f * y_pad) / 3.f;
      float green_x = skia::width - 2.5f * x_pad;

      //

      VoiceModes vms(2, 0.0f, 0.0f, 3, 0.0f);
      vms.bounding_box.move_to({10, 10});
      vms.bounding_box.resize({300, 130});
      vms.draw(ctx);

      Portamento port(0.3);
      port.bounding_box.move_to({10, 150});
      port.bounding_box.resize({300, 30});
      port.draw(ctx);

      LegatoGraphic leg(2);
      leg.bounding_box.move_to({10, 193});
      leg.bounding_box.resize({300, 37});
      leg.draw(ctx);


      /*
      ctx.font(Fonts::Norm, 35);
      ctx.beginPath();
      ctx.fillStyle(Colours::Green);
      ctx.textAlign(HorizontalAlign::Center, VerticalAlign::Middle);
      ctx.fillText(aux_name, {green_x, y_pad - 0.2 * space + y_shift});

      ctx.beginPath();
      ctx.fillStyle(Colours::Green);
      ctx.textAlign(HorizontalAlign::Center, VerticalAlign::Bottom);
      ctx.fillText(aux_value, {green_x, y_pad + 0.8f * space + y_shift});

      //------------------------------//
      // Portamento
      ctx.globalCompositeOperation(CompositeOperation::XOR);
      // Background. Note, colour doesn't matter for this,
      // it is only to get the logic to work
      ctx.beginPath();
      ctx.fillStyle(Colours::Gray50);
      ctx.roundedRect({x_pad, y_pad + space + y_shift}, {width - 2 * x_pad, space}, 10);
      ctx.fill();

      // Fill
      constexpr float fudge = 3.f;
      ctx.beginPath();
      ctx.fillStyle(Colours::Yellow);
      ctx.roundedRect({x_pad + fudge, y_pad + space + y_shift}, {(width - 2 * x_pad - fudge) * portamento, space}, 10);
      ctx.fill();

      // Text
      ctx.beginPath();
      ctx.fillStyle(Colours::Yellow);
      ctx.textAlign(HorizontalAlign::Center, VerticalAlign::Middle);
      ctx.fillText("portamento", {width * 0.5, y_pad + 1.5 * space + y_shift});

      ctx.globalCompositeOperation(CompositeOperation::SOURCE_OVER);

      // Rectangle
      ctx.beginPath();
     // std::this_thread::sleep_for(std::chrono::seconds(220s      ctx.strokeStyle(Colours::Yellow);
      ctx.roundedRect({x_pad, y_pad + space + y_shift}, {width - 2 * x_pad, space}, 10);
      ctx.stroke();

      //--------------------------//
      // Legato settings
      constexpr float top_part_length = 70;
      ctx.beginPath();
      ctx.strokeStyle(Colours::Red);
      ctx.moveTo(x_pad, y_pad + 2.5 * space + 0.5 * y_shift);
      ctx.lineTo(x_pad + top_part_length, y_pad + 2.5 * space + 0.5 * y_shift);
      ctx.moveTo(width - x_pad, y_pad + 2.5 * space + 0.5 * y_shift);
      ctx.lineTo(width - x_pad - top_part_length, y_pad + 2.5 * space + 0.5 * y_shift);
      ctx.moveTo(x_pad, y_pad + 3.5 * space);
      ctx.lineTo(width - x_pad, y_pad + 3.5 * space);
      ctx.stroke();

      ctx.beginPath();
      ctx.fillStyle(Colours::Red);
      ctx.textAlign(HorizontalAlign::Center, VerticalAlign::Middle);
      ctx.fillText("legato", {width * 0.5, y_pad + 2.5 * space + 0.5 * y_shift});

      ctx.beginPath();
      ctx.fillStyle(legato ? Colours::Red : Colours::Gray50);
      ctx.font(30);
      ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Middle);
      ctx.fillText("envelope", {x_pad, y_pad + 3 * space});

      ctx.beginPath();
      ctx.fillStyle(retrig ? Colours::Red : Colours::Gray50);
      ctx.font(30);
      ctx.textAlign(HorizontalAlign::Right, VerticalAlign::Middle);
      ctx.fillText("portamento", {width - x_pad, y_pad + 3 * space});

      */

      timeline.step(1.0 / 60.0);
    });
    rt.wait_for_stop(20s);
  }
}
