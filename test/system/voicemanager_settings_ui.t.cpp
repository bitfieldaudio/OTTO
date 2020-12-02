#include "testing.t.hpp"

#include "app/services/config.hpp"
#include "app/services/graphics.hpp"
#include "lib/widget.hpp"

#include <SkFont.h>
#include <SkPath.h>
#include <SkTextBlob.h>
#include <SkTypeface.h>
#include <SkRRect.h>

#include <fmt/format.h>
#include <string>

#include <choreograph/Choreograph.h>


using namespace otto;
using namespace otto::services;

//////////////
// Stuff we will need!
namespace otto::graphics {
  SkPaint OTTO_paint()
  {
    SkPaint p;
    p.setAntiAlias(true);
    p.setStyle(SkPaint::kStroke_Style);
    p.setStrokeCap(SkPaint::kRound_Cap);
    p.setStrokeJoin(SkPaint::kRound_Join);
    p.setStrokeWidth(6.f);
    return p;
  }

  namespace Colours {
    constexpr SkColor Blue = SkColorSetRGB(22, 184, 254);
    constexpr SkColor Green = SkColorSetRGB(22, 254, 101);
    constexpr SkColor Yellow = SkColorSetRGB(254, 245, 22);
    constexpr SkColor Red = SkColorSetRGB(254, 22, 22);
    constexpr SkColor White = SK_ColorWHITE;
    constexpr SkColor Grey50 = SK_ColorGRAY;
    constexpr SkColor Black = SK_ColorBLACK;
  } // namespace Colours



  // Not the real one, just for testing now
  SkColor mix(SkColor a, SkColor b, float m)
  {
    return a;
  }

}


//////////////////

enum struct PlayMode {
  poly,
  mono,
  unison,
  interval
};

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

void place_text(SkCanvas& ctx, SkPaint paint, otto::graphics::Anchor anchor, std::string text, int fontsize, float x, float y) {
  SkFont font = SkFont(nullptr, fontsize);
  SkRect rect;
  SkScalar wid = font.measureText(text.c_str(), text.size(), SkTextEncoding(), &rect, &paint);
  sk_sp<SkTextBlob> val = SkTextBlob::MakeFromString(text.c_str(), font);
  ctx.drawTextBlob(val.get(), x - anchor[0] * rect.width(), y + rect.height() - anchor[1] * rect.height(), paint);
}

struct VoiceModes : otto::graphics::Widget<VoiceModes> {
  int active_line;
  float rand;
  float sub;
  int interval;
  float detune;
  VoiceModes(int a, float r, float s, int i, float d) : active_line(a), rand(r), sub(s), interval(i), detune(d) {}

  void do_draw(SkCanvas& ctx) {
    float height = bounding_box.height();
    float width = bounding_box.width();
    // Set up x-coordinates
    float mode_text_x = width * 0.03;
    float division_x = width * 0.382; // Golden ratio
    float aux_text_x = width * 0.412;
    float aux_value_x = width * 0.97;

    // Set up y-coordinates
    float subject_height = 15.f;
    float line_size = (height - subject_height) / 4; 

    auto draw_line = [&](SkCanvas& ctx, bool active, float y, int i) {
      // Background squares
      if (active) {
        SkRRect left_rect = SkRRect::MakeRectXY(SkRect::MakeXYWH(0, y, width, line_size), 10.f, 10.f);
        SkPaint p = otto::graphics::OTTO_paint();
        p.setStyle(SkPaint::kFill_Style);
        p.setColor(otto::graphics::Colours::Blue);
        ctx.drawRRect(left_rect, p);
        p.setStrokeWidth(1.f);
        p.setStyle(SkPaint::kStroke_Style);
        p.setColor(otto::graphics::Colours::Black);
        ctx.drawRRect(left_rect, p);

        SkRRect right_rect = SkRRect::MakeRectXY(SkRect::MakeXYWH(division_x, y, width - division_x, line_size), 10.f, 10.f);
        p.setStyle(SkPaint::kFill_Style);
        p.setColor(otto::graphics::Colours::Green);
        ctx.drawRRect(right_rect, p);
        p.setStrokeWidth(3.f);
        p.setStyle(SkPaint::kStroke_Style);
        p.setColor(otto::graphics::Colours::Black);
        ctx.drawRRect(right_rect, p);
      }

      SkPaint p = otto::graphics::OTTO_paint();
      p.setStyle(SkPaint::kFill_Style);
      p.setStrokeWidth(0.f);
      if (active) {
        p.setColor(otto::graphics::Colours::White);
      } else {
        p.setColor(otto::graphics::Colours::Grey50);
      }
      place_text(ctx, p, otto::graphics::Anchors::MiddleLeft, playmode_string(playmodes[i]), 24, mode_text_x, y + line_size * 0.5);
      place_text(ctx, p, otto::graphics::Anchors::MiddleLeft, aux_setting(playmodes[i]), 24, aux_text_x, y + line_size * 0.5);
      place_text(ctx, p, otto::graphics::Anchors::MiddleRight, aux_value_string(playmodes[i]), 24, aux_value_x, y + line_size * 0.5);
      
    };

    // Top text
    SkPaint p = otto::graphics::OTTO_paint();
    p.setStyle(SkPaint::kFill_Style);
    p.setStrokeWidth(0.f);
    p.setColor(otto::graphics::Colours::White);
    place_text(ctx, p, otto::graphics::Anchors::TopLeft, "MODE", 18, mode_text_x, 0);
    place_text(ctx, p, otto::graphics::Anchors::TopLeft, "SETTING", 18, aux_text_x, 0);
    place_text(ctx, p, otto::graphics::Anchors::TopRight, "VALUE", 18, aux_value_x, 0);
    // Modes  
    int active_mode = 2;
    for (int i=0; i<4; i++) {
      draw_line(ctx, i == active_mode, subject_height + i * line_size, i);
    }
  }
};

struct Portamento : otto::graphics::Widget<Portamento> {
  float value;
  Portamento(float v) : value(v) {}

  void do_draw(SkCanvas& ctx) {
    float height = bounding_box.height();
    float width = bounding_box.width();
    // Yellow Main Box (Fill)
    SkRRect main_box = SkRRect::MakeRectXY(SkRect::MakeXYWH(0, 0, width, height), 10.f, 10.f);
    SkPaint yp = otto::graphics::OTTO_paint();
    yp.setStyle(SkPaint::kFill_Style);
    yp.setColor(otto::graphics::Colours::Yellow);
    ctx.drawRRect(main_box, yp);

    // Black covering box
    SkRect cover_box = SkRect::MakeXYWH(width * value, 0, width * (1 - value), height);
    SkPaint bp = otto::graphics::OTTO_paint();
    bp.setStyle(SkPaint::kFill_Style);
    bp.setColor(otto::graphics::Colours::Black);
    ctx.drawRect(cover_box, bp);
    // Yellow Main Box (Stroke)
    yp.setStrokeWidth(3.f);
    yp.setStyle(SkPaint::kStroke_Style);
    ctx.drawRRect(main_box, yp);

    // Text
    SkPaint p = otto::graphics::OTTO_paint();
    p.setStyle(SkPaint::kFill_Style);
    p.setColor(otto::graphics::Colours::Black);
    place_text(ctx, p, otto::graphics::Anchors::Center, "PORTAMENTO TIME", 18, width / 2.f, height / 2.f);
    ctx.save();
    ctx.clipRect(cover_box);
    p.setColor(otto::graphics::Colours::White);
    place_text(ctx, p, otto::graphics::Anchors::Center, "PORTAMENTO TIME", 18, width / 2.f, height / 2.f);
    ctx.restore();
  }
};

struct LegatoGraphic : otto::graphics::Widget<LegatoGraphic> {
  int value;
  LegatoGraphic(int v) : value(v) {}

  void do_draw(SkCanvas& ctx) {
    float height = bounding_box.height();
    float width = bounding_box.width();
    
    // Text
    SkPaint p = otto::graphics::OTTO_paint();
    p.setStyle(SkPaint::kFill_Style);
    p.setColor(otto::graphics::Colours::White);
    place_text(ctx, p, otto::graphics::Anchors::TopLeft, "LEGATO", 18, 0, 0);
    
    auto set_color = [&](int i){
      if (i == value) { p.setColor(otto::graphics::Colours::Red); }
      else {p.setColor(otto::graphics::Colours::Grey50); } 
    };
    set_color(0);
    place_text(ctx, p, otto::graphics::Anchors::BottomLeft, "OFF", 24, 0, height);
    set_color(1);
    place_text(ctx, p, otto::graphics::Anchors::BottomLeft, "ENV.", 24, width * 0.2, height);
    set_color(2);
    place_text(ctx, p, otto::graphics::Anchors::BottomLeft, "RETRIG", 24, width * 0.44, height);
    set_color(3);
    place_text(ctx, p, otto::graphics::Anchors::BottomRight, "BOTH", 24, width, height);
  }
};




TEST_CASE ("Voicemanager Settings graphics") {
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


  auto app = start_app(ConfigManager::make(), Graphics::make());
  SECTION ("Voicemanager") {



    PlayMode play_mode = PlayMode::poly;
    std::string play_mode_str = playmode_string(play_mode);
    std::string aux_name = aux_setting(play_mode);
    std::string aux_value = aux_value_string(play_mode);

    

    app.service<Graphics>().show([&](SkCanvas& ctx) {
     
      float height = ctx.imageInfo().height();
      float width = ctx.imageInfo().width();
      constexpr float x_pad = 30;
      constexpr float y_pad = 50;
      constexpr float y_shift = -12;
      float space = (height - 2.f * y_pad) / 3.f;
      float green_x = width - 2.5f * x_pad;

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
      leg.bounding_box.move_to({10, 190});
      leg.bounding_box.resize({300, 40});
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
      ctx.strokeStyle(Colours::Yellow);
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
        
      timeline.step( 1.0 / 60.0 );
    });
    // std::this_thread::sleep_for(std::chrono::seconds(20));
    app.wait_for_stop();
  }
}
