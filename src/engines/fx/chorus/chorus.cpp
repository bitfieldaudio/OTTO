#include "chorus.hpp"

#include "core/ui/vector_graphics.hpp"

#include "util/iterator.hpp"
#include "util/utility.hpp"

// The chorus was developed with inspiration from this:
// https://ccrma.stanford.edu/~dattorro/EffectDesignPart2.pdf

namespace otto::engines {

  using namespace ui;
  using namespace ui::vg;

  struct ChorusScreen : EngineScreen<Chorus> {
    void draw(Canvas& ctx) override;
    bool keypress(Key key) override;
    void encoder(EncoderEvent e) override;

    void draw_front_head(Canvas&, Point, Colour, float);
    void draw_background_head(Canvas&, Point, Colour, float);

    std::array<ui::vg::Colour, 10> colour_list = {Colours::Blue,
                                                  Colours::Green,
                                                  Colours::Yellow,
                                                  Colours::Red,
                                                  Colours::Green,
                                                  Colours::Blue,
                                                  Colours::Red,
                                                  Colours::Green,
                                                  Colours::Yellow,
                                                  Colours::Red};

    float wave_height = 20;
    float intpart = 1;
    gam::AD<> env_blue{0.0005, 0.002, 1, 0};
    gam::AD<> env_green{0.0005, 0.002, 1, 0};
    gam::AD<> env_yellow{0.0005, 0.002, 1, 0};
    gam::AD<> env_red{0.0005, 0.002, 1, 0};

    using EngineScreen<Chorus>::EngineScreen;
  };

  Chorus::Chorus() : EffectEngine<Chorus>(std::make_unique<ChorusScreen>(this))
  {
    // Set proper size of phase accumulator for graphics
    phase.radius(1);

    props.delay.on_change().connect([this](float d) {
      //Goes from minimal to around 20 ms nominal delay.
      chorus.center(d * d * 0.020 + 0.0005);
      //Naturally, the new nominal delay changes the maximum for the play head movement
      chorus.depth(props.depth * chorus.center());
    }).call_now(props.delay);

    props.rate.on_change().connect([this](float rate) {
      chorus.rate(rate * 0.5);
      phase.freq(rate * 0.5f);
    });

    props.feedback.on_change().connect([this](float fbk) {
      chorus.fbk(fbk);
      //if (abs(fbk) > 0.7)
        //chorus.ffd(1 + 0.7 - abs(fbk));
    });

    props.depth.on_change().connect([this](float d) {
      //chorus.depth(depth);
        chorus.depth(d * chorus.center());
    }).call_now(props.depth);
  }

  audio::ProcessData<2> Chorus::process(audio::ProcessData<1> data)
  {
    // Allocate two audio buffers (left and right channels)
    auto buf = Application::current().audio_manager->buffer_pool().allocate_multi<2>();
    // Fill buffers with processed samples
    for (auto&& [dat, bufL, bufR] : util::zip(data.audio, buf[0], buf[1])) {
      // Get one sample from chorus effect
      chorus(dat, bufL, bufR);
      // Update phase value for graphics
      props.phase_value = phase.nextPhase();
    }
    // Reassign (redirect) processed data to original data
    return data.redirect(buf);
  }

  // SCREEN //

  void ChorusScreen::encoder(ui::EncoderEvent ev)
  {
    auto& props = engine.props;
    switch (ev.encoder) {
    case Encoder::blue: {
      props.delay.step(ev.steps);
      env_blue.resetSoft();
      break;
    }
    case Encoder::green: {
      props.rate.step(ev.steps);
      env_green.resetSoft();
      break;
    }
    case Encoder::yellow: {
      props.feedback.step(ev.steps);
      env_yellow.resetSoft();
      break;
    }
    case Encoder::red: {
      props.depth.step(ev.steps);
      env_red.resetSoft();
      break;
    }
    }
  }

  bool ChorusScreen::keypress(ui::Key key)
  {
    return false;
  }

  void ChorusScreen::draw(ui::vg::Canvas& ctx)
  {
    using namespace ui::vg;

    auto& props = engine.props;

    ctx.font(Fonts::Norm, 35);

    constexpr float x_pad = 20;
    constexpr float y_pad = 20;

    constexpr float x_right = width - x_pad;
    constexpr float y_bottom = height - y_pad;
    constexpr float number_shift = 30;

    wave_height = props.depth * 12;

    // Text
    ctx.font(Fonts::Norm, 25);
    ctx.fillStyle(Colours::Red);
    ctx.textAlign(HorizontalAlign::Right, VerticalAlign::Middle);
    ctx.fillText("depth", x_right, y_bottom);

    ctx.fillStyle(Colours::Green);
    ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Middle);
    ctx.fillText("rate", x_pad, y_bottom);

    ctx.fillStyle(Colours::Yellow);
    ctx.textAlign(HorizontalAlign::Right, VerticalAlign::Middle);
    ctx.fillText("feedback", x_right, y_pad);

    ctx.fillStyle(Colours::Blue);
    ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Middle);
    ctx.fillText("delay", x_pad, y_pad);

    // Numbers
    ctx.font(Fonts::Norm, 40);

    // chorus/RedValue/10
    ctx.fillStyle(Colours::Red.dim(1 - env_red()));
    ctx.textAlign(HorizontalAlign::Right, VerticalAlign::Middle);
    ctx.fillText(fmt::format("{}", std::round(100 * props.depth)), x_right, y_bottom - number_shift);

    // chorus/GreenValue/10
    ctx.fillStyle(Colours::Green.dim(1 - env_green()));
    ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Middle);
    ctx.fillText(fmt::format("{}", std::round(props.rate * 100)), x_pad, y_bottom - number_shift);

    // chorus/YellowValue/0
    ctx.fillStyle(Colours::Yellow.dim(1 - env_yellow()));
    ctx.textAlign(HorizontalAlign::Right, VerticalAlign::Middle);
    ctx.fillText(fmt::format("{}", std::round(props.feedback * 100)), x_right, y_pad + number_shift);

    // chorus/BlueValue/1
    ctx.fillStyle(Colours::Blue.dim(1 - env_blue()));
    ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Middle);
    ctx.fillText(fmt::format("{}", std::round(100 * props.delay)), x_pad, y_pad + number_shift);


    //Heads
    constexpr float spacing_constant = 10;
    constexpr int num_heads = 10;

    float spacing = spacing_constant * props.delay + 10;
    Point start = {120 - props.delay * 50, 165};

    for (int i=num_heads; i>=1; i--) {
      float head_height = wave_height * gam::scl::sinP9(gam::scl::wrap(props.phase_value - 0.2f*(float)i, 1.f, -1.f));
      //This brightness calculation is HORRIBLY over-engineered...
      float brightness = powf(cosh(abs(props.feedback)*1.5)*0.4, 0.3 * float(i));
      draw_background_head(ctx, {start.x + i*spacing, start.y + head_height}, colour_list[i].dim(1 - brightness), 1 - i*0.07);
    }
    draw_front_head(ctx, {start.x, start.y + wave_height * gam::scl::sinP9(props.phase_value)}, Colours::Blue, 1);




  }

  void ChorusScreen::draw_front_head(ui::vg::Canvas& ctx, Point p, Colour c, float scale)
  {
    // chorus/HeadMain
    ctx.beginPath();
    ctx.scaleTowards(scale, p);
    ctx.moveTo(p.x, p.y);
    ctx.lineTo(p.x, p.y - 173.0 + 153.6);
    ctx.bezierCurveTo(p.x + 121.4 - 130.8, p.y - 173.0 + 148.5, p.x + 115.0 - 130.8, p.y - 173.0 + 138.6, p.x + 115.0 - 130.8, p.y - 173.0 + 127.1);
    ctx.lineTo(p.x + 115.0 - 130.8, p.y - 173.0 + 107.3);
    ctx.bezierCurveTo(p.x + 115.0 - 130.8, p.y - 173.0 + 85.1, p.x + 133.0 - 130.8, p.y - 173.0 + 67.0, p.x + 155.2 - 130.8, p.y - 173.0 + 67.0);
    ctx.bezierCurveTo(p.x + 177.4 - 130.8, p.y - 173.0 + 67.0, p.x + 195.5 - 130.8, p.y - 173.0 + 85.1, p.x + 195.5 - 130.8, p.y - 173.0 + 107.3);
    ctx.lineTo(p.x + 195.5 - 130.8, p.y - 173.0 + 117.8);
    ctx.lineTo(p.x + 204.4 - 130.8, p.y - 173.0 + 130.0);
    ctx.bezierCurveTo(p.x + 205.4 - 130.8, p.y - 173.0 + 131.4, p.x + 205.1 - 130.8, p.y - 173.0 + 133.4, p.x + 203.7 - 130.8, p.y - 173.0 + 134.4);
    ctx.bezierCurveTo(p.x + 203.2 - 130.8, p.y - 173.0 + 134.8, p.x + 202.5 - 130.8, p.y - 173.0 + 135.0, p.x + 201.8 - 130.8, p.y - 173.0 + 135.0);
    ctx.lineTo(p.x + 195.5 - 130.8, p.y - 173.0 + 135.0);
    ctx.lineTo(p.x + 195.5 - 130.8, p.y - 173.0 + 152.4);
    ctx.bezierCurveTo(p.x + 195.5 - 130.8, p.y - 173.0 + 155.1, p.x + 193.3 - 130.8, p.y - 173.0 + 157.2, p.x + 190.7 - 130.8, p.y - 173.0 + 157.2);
    ctx.lineTo(p.x + 179.7 - 130.8, p.y - 173.0 + 157.2);
    ctx.lineTo(p.x + 179.7 - 130.8, p.y - 173.0 + 173.0);
    ctx.fill(Colours::Black);
    ctx.strokeStyle(c);
    ctx.stroke();

  }
  void ChorusScreen::draw_background_head(ui::vg::Canvas& ctx, Point p, Colour c, float scale)
  {
    ctx.group([&] {
      ctx.beginPath();
      ctx.scaleTowards(scale, {p.x, p.y + (67.f - 173.f) / 2.f});
      ctx.lineWidth(6 / scale);
      ctx.moveTo(p.x + 115.0 - 130.8, p.y - 173.0 + 127.1);
      ctx.lineTo(p.x + 115.0 - 130.8, p.y - 173.0 + 107.3);
      ctx.bezierCurveTo(p.x + 115.0 - 130.8, p.y - 173.0 + 85.1, p.x + 133.0 - 130.8, p.y - 173.0 + 67.0,
                        p.x + 155.2 - 130.8, p.y - 173.0 + 67.0);
      ctx.bezierCurveTo(p.x + 177.4 - 130.8, p.y - 173.0 + 67.0, p.x + 195.5 - 130.8, p.y - 173.0 + 85.1,
                        p.x + 195.5 - 130.8, p.y - 173.0 + 107.3);
      ctx.lineTo(p.x + 195.5 - 130.8, p.y - 173.0 + 117.8);
      ctx.lineTo(p.x + 204.4 - 130.8, p.y - 173.0 + 130.0);
      ctx.bezierCurveTo(p.x + 205.4 - 130.8, p.y - 173.0 + 131.4, p.x + 205.1 - 130.8, p.y - 173.0 + 133.4,
                        p.x + 203.7 - 130.8, p.y - 173.0 + 134.4);
      ctx.bezierCurveTo(p.x + 203.2 - 130.8, p.y - 173.0 + 134.8, p.x + 202.5 - 130.8, p.y - 173.0 + 135.0,
                        p.x + 201.8 - 130.8, p.y - 173.0 + 135.0);
      ctx.lineTo(p.x + 195.5 - 130.8, p.y - 173.0 + 135.0);
      ctx.lineTo(p.x + 195.5 - 130.8, p.y - 173.0 + 152.4);
      ctx.bezierCurveTo(p.x + 195.5 - 130.8, p.y - 173.0 + 155.1, p.x + 193.3 - 130.8, p.y - 173.0 + 157.2,
                        p.x + 190.7 - 130.8, p.y - 173.0 + 157.2);
      ctx.lineTo(p.x + 179.7 - 130.8, p.y - 173.0 + 157.2);
      ctx.lineTo(p.x + 179.7 - 130.8, p.y - 173.0 + 173.0);
      ctx.fill(Colours::Black);
      ctx.strokeStyle(c);
      ctx.stroke();
    });
  }

} // namespace otto::engines
