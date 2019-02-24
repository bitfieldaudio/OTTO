#include "core/ui/vector_graphics.hpp"
#include "ottofm.hpp"

#include "services/application.hpp"

#include "core/audio/voice_manager.hpp"
#include "services/ui_manager.hpp"

namespace otto::engines {

  using namespace ui;
  using namespace ui::vg;

  struct Fraction {
    int numerator;
    int denominator;

    constexpr Fraction(int n = 1, int d = 1) : numerator(n), denominator(d) {}

    operator float() const
    {
      return float(numerator) / float(denominator);
    }

    std::string to_string() const
    {
      return fmt::format("{}/{}", numerator, denominator);
    }
  };

  /// Used for graphics.
  enum struct Drawside {
    left,
    middle,
    right,
    // Number of sides
    n_sides,
  };

  struct Operatorline {
    int start;
    int end;
    Drawside side;

    constexpr Operatorline(int st = 1, int en = 2, Drawside si = Drawside::middle)
      : start(st), end(en), side(si)
    {}
  };

  struct Algorithm {
    std::array<bool, 4> modulator_flags = {false, false, false, false};
    std::vector<Operatorline> operator_lines;

    Algorithm(std::initializer_list<int> modulator_idx = {},
              std::vector<Operatorline> op_lines = {})
      : operator_lines(op_lines)
    {
      for (auto&& idx : modulator_idx) {
        modulator_flags[idx] = true;
      }
    }
  };


  static const std::array<Fraction, 19> fractions = {{{1, 1},
                                                      {1, 64},
                                                      {1, 32},
                                                      {3, 32},
                                                      {1, 8},
                                                      {5, 16},
                                                      {1, 2},
                                                      {5, 8},
                                                      {2, 1},
                                                      {3, 2},
                                                      {3, 4},
                                                      {1, 4},
                                                      {5, 32},
                                                      {1, 16},
                                                      {5, 8},
                                                      {4, 1},
                                                      {7, 4},
                                                      {7, 16},
                                                      {7, 2}}};

  static const std::array<Algorithm, 11> algorithms = {
    {Algorithm({1, 2, 3},
               {Operatorline(3, 2, Drawside::middle), Operatorline(2, 1, Drawside::middle),
                Operatorline(1, 0, Drawside::middle)}),
     Algorithm({1, 2, 3},
               {Operatorline(3, 1, Drawside::left), Operatorline(2, 1, Drawside::right),
                Operatorline(1, 0, Drawside::middle)}),
     Algorithm({1, 2, 3},
               {Operatorline(3, 0, Drawside::left), Operatorline(2, 1, Drawside::middle),
                Operatorline(1, 0, Drawside::middle)}),
     Algorithm({1, 2, 3},
               {Operatorline(3, 2, Drawside::left), Operatorline(3, 1, Drawside::left),
                Operatorline(2, 0, Drawside::right), Operatorline(1, 0, Drawside::right)}),
     Algorithm({2, 3},
               {Operatorline(3, 2, Drawside::middle), Operatorline(2, 1, Drawside::left),
                Operatorline(2, 0, Drawside::left)}),
     Algorithm({2, 3},
               {Operatorline(3, 2, Drawside::middle), Operatorline(2, 1, Drawside::middle)}),
     Algorithm({1, 2, 3},
               {Operatorline(3, 0, Drawside::left), Operatorline(2, 0, Drawside::right),
                Operatorline(1, 0, Drawside::middle)}),
     Algorithm({1, 3},
               {Operatorline(3, 2, Drawside::middle), Operatorline(1, 0, Drawside::middle)}),
     Algorithm({3},
               {Operatorline(3, 2, Drawside::middle), Operatorline(3, 1, Drawside::right),
                Operatorline(3, 0, Drawside::left)}),
     Algorithm({3}, {Operatorline(3, 2, Drawside::middle)}), Algorithm({})}};



  /*
   * Declarations
   */

  float OTTOFMSynth::Voice::algos(int alg)
  {
    switch (alg) {
    case 0: return operators[0](operators[1](operators[2](operators[3](0))));
    case 1: return operators[0](operators[1](operators[2](0) + operators[3](0)));
    case 2: return operators[0](operators[1](operators[2](0)) + operators[3](0));
    case 3: {
      float aux = operators[3](0);
      return operators[0](operators[1](aux) + operators[2](aux));
    }
    case 4: {
      float aux = operators[2](operators[3](0));
      return operators[0](aux) + operators[1](aux);
    }
    case 5: return operators[0](0) + operators[1](operators[2](operators[3](0)));
    case 6: return operators[0](operators[1](0) + operators[2](0) + operators[3](0));
    case 7: return operators[0](operators[1](0)) + operators[2](operators[3](0));
    case 8: {
      float aux = operators[3](0);
      return operators[0](aux) + operators[1](aux) + operators[2](aux);
    }
    case 9: return operators[0](0) + operators[1](0) + operators[2](operators[3](0));
    case 10: return operators[0](0) + operators[1](0) + operators[2](0) + operators[3](0);
    default: return 0.f;
    }
  }

  float OTTOFMSynth::FMOperator::FMSine::operator()(float phsOffset = 0) noexcept
  {
    return gam::scl::sinP9(gam::scl::wrap(this->nextPhase() + phsOffset, 1.f, -1.f));
  }

  float OTTOFMSynth::FMOperator::operator()(float phaseMod = 0)
  {
    if (modulator)
      return env() * sine(phaseMod) * outlevel * fm_amount;
    else
      return sine(phaseMod) * outlevel;
  }

  void OTTOFMSynth::FMOperator::freq(float frq)
  {
    sine.freq(frq);
  }

  float OTTOFMSynth::FMOperator::level()
  {
    return env.value() * outlevel;
  }

  void OTTOFMSynth::Voice::reset_envelopes()
  {
    for (int i = 0; i < 4; i++) {
      operators[i].env.resetSoft();
    }
  }

  void OTTOFMSynth::Voice::release_envelopes()
  {
    for (int i = 0; i < 4; i++) {
      operators[i].env.release();
    }
  }

  // Voice
  float OTTOFMSynth::Voice::operator()() noexcept
  {
    set_frequencies();
    return algos(props.algN);
  }

  OTTOFMSynth::Voice::Voice(Pre& pre) noexcept : VoiceBase(pre)
  {
    for (int i = 0; i < 4; i++) {
      operators[i].env.finish();
    }
    /// Connect appropriate voice properties
    props.algN.on_change().connect([this](int algo) {
      // Change modulator flags
      for (int i = 0; i < 4; i++) {
        operators[i].modulator = algorithms[algo].modulator_flags[i];
      }
    });
    props.fmAmount.on_change().connect([this](float fm) {
      // Change modulator flags
      for (int i = 0; i < 4; i++) {
        operators[i].fm_amount = fm;
      }
    });

    // Connect properties for individual operators
    for (int i = 0; i < 4; i++) {
      props.operators[i].outLev.on_change().connect(
        [this, i](float level) { operators[i].outlevel = level; });
      props.operators[i].detune.on_change().connect(
        [this, i](float detune) { operators[i].detune_amount = detune * 25; });
      props.operators[i].ratio_idx.on_change().connect(
        [this, i](int idx) { operators[i].freq_ratio = (float) fractions[idx]; });
      props.operators[i].mAtt.on_change().connect(
        [this, i](float att) { operators[i].env.attack(3 * att); });
      props.operators[i].mDecrel.on_change().connect([this, i](float decrel) {
        operators[i].env.decay(3 * decrel * (1 - props.operators[i].mSuspos));
        operators[i].env.release(3 * decrel * props.operators[i].mSuspos);
      });
      props.operators[i].mSuspos.on_change().connect([this, i](float suspos) {
        operators[i].env.decay(3 * props.operators[i].mDecrel * (1 - suspos));
        operators[i].env.release(3 * props.operators[i].mDecrel * suspos);
        operators[i].env.sustain(suspos);
      });
      props.operators[i].feedback.on_change().connect(
        [this, i](float fb) { operators[i].feedback = fb; });
    }
  }

  void OTTOFMSynth::Voice::on_note_on() noexcept
  {
    reset_envelopes();
  }

  void OTTOFMSynth::Voice::on_note_off() noexcept
  {
    release_envelopes();
  }

  void OTTOFMSynth::Voice::set_frequencies()
  {
    for (int i = 0; i < 4; i++) {
      operators[i].freq(frequency() * operators[i].freq_ratio + operators[i].detune_amount);
    }
  }
  // Preprocessor
  OTTOFMSynth::Pre::Pre(Props& props) noexcept : PreBase(props) {}

  void OTTOFMSynth::Pre::operator()() noexcept {}

  // Postprocessor
  /// Constructor. Takes care of linking appropriate variables to props
  OTTOFMSynth::Post::Post(Pre& pre) noexcept : PostBase(pre) {}

  float OTTOFMSynth::Post::operator()(float in) noexcept
  {
    return in;
  }

  // OTTOFMSynth ////////////////////////////////////////////////////////////////

  audio::ProcessData<1> OTTOFMSynth::process(audio::ProcessData<1> data)
  {
    return voice_mgr_.process(data);
  }

  /*
   * OTTOFMSynthScreen
   */

  struct OTTOFMSynthScreen : EngineScreen<OTTOFMSynth> {
    void draw(Canvas& ctx) override;
    void draw_with_shift(Canvas& ctx);
    void draw_no_shift(Canvas& ctx);
    void draw_operators(Canvas& ctx);
    void draw_envelope(Canvas& ctx);
    bool keypress(Key key) override;
    void rotary(RotaryEvent e) override;

    bool shift = false;
    int cur_op = 0;

    using EngineScreen<OTTOFMSynth>::EngineScreen;
  };

  OTTOFMSynth::OTTOFMSynth()
    : SynthEngine("OTTO.FM", props, std::make_unique<OTTOFMSynthScreen>(this)), voice_mgr_(props)
  {}

  bool OTTOFMSynthScreen::keypress(Key key)
  {
    switch (key) {
    case ui::Key::blue_click: cur_op = 3; break;
    case ui::Key::green_click: cur_op = 2; break;
    case ui::Key::yellow_click: cur_op = 1; break;
    case ui::Key::red_click: cur_op = 0; break;
    default: return false; ;
    }
    return true;
  }

  void OTTOFMSynthScreen::rotary(RotaryEvent e)
  {
    auto& props = engine.props;
    auto& current = props.operators.at(cur_op);
    switch (e.rotary) {
    case Rotary::blue:
      if (!shift) {
        current.ratio_idx.step(e.clicks);
      } else {
        current.detune.step(e.clicks);
      }
      break;
    case Rotary::green:
      if (!shift) {
        current.outLev.step(e.clicks);
      } else {
        current.mSuspos.step(e.clicks);
      }
      break;
    case Rotary::yellow:
      if (!shift) {
        current.feedback.step(e.clicks);
        current.mAtt.step(e.clicks);
      } else {
        current.mDecrel.step(e.clicks);
      }
      break;
    case Rotary::red:
      if (!shift) {
        props.fmAmount.step(e.clicks);
      } else {
        props.algN.step(e.clicks);
      }
      break;
    }
  }


  void OTTOFMSynthScreen::draw(ui::vg::Canvas& ctx)
  {
    using namespace ui::vg;

    shift = Application::current().ui_manager->is_pressed(ui::Key::shift);
    ctx.font(Fonts::Norm, 35);

    if (shift)
      draw_with_shift(ctx);
    else
      draw_no_shift(ctx);

    draw_envelope(ctx);
    draw_operators(ctx);
  }

  void OTTOFMSynthScreen::draw_no_shift(ui::vg::Canvas& ctx)
  {
    using namespace ui::vg;
    ctx.font(Fonts::Norm, 35);

    constexpr float x_pad_left = 90;
    constexpr float x_pad = 30;
    constexpr float y_pad = 50;
    constexpr float space = (height - 2.f * y_pad) / 3.f;
    // Ratio and Detune
    ctx.beginPath();
    ctx.fillStyle(Colours::Blue);
    ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Middle);
    ctx.fillText("Ratio", {x_pad_left, y_pad});

    ctx.beginPath();
    ctx.fillStyle(Colours::Blue);
    ctx.textAlign(HorizontalAlign::Right, VerticalAlign::Middle);
    ctx.fillText(fractions[engine.props.operators.at(cur_op).ratio_idx].to_string(),
                 {width - x_pad, y_pad});

    // FM Amount
    ctx.beginPath();
    ctx.fillStyle(Colours::Red);
    ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Middle);
    ctx.fillText("FM", {x_pad_left, y_pad + 3 * space});

    ctx.lineWidth(6.f);
    constexpr float x_left = width - 6 * x_pad;
    constexpr float x_right = width - x_pad;
    constexpr float y_low = y_pad + 3 * space + 10;
    constexpr float y_high = y_pad + 3 * space - 10;
    ctx.beginPath();
    ctx.moveTo(x_left, y_low);
    ctx.lineTo(x_right, y_high);
    ctx.lineTo(x_right, y_low);
    ctx.closePath();
    ctx.stroke(Colours::Red);

    float x_middle = x_left * (1 - engine.props.fmAmount) + x_right * engine.props.fmAmount;
    float y_middle = y_low * (1 - engine.props.fmAmount) + y_high * engine.props.fmAmount;

    ctx.beginPath();
    ctx.moveTo(x_left, y_low);
    ctx.lineTo(x_middle, y_middle);
    ctx.lineTo(x_middle, y_low);
    ctx.closePath();
    ctx.fill(Colours::Red);

    // Operator level
    // vertical line
    float line_top = y_pad + 0.7 * space;
    float line_bot = line_top + 1.5 * space;
    float line_x = width - 1.5 * x_pad;
    float bar_width = 20.f;
    ctx.beginPath();
    ctx.moveTo(line_x, line_top);
    ctx.lineTo(line_x, line_bot);
    ctx.lineWidth(6.0);
    ctx.lineCap(Canvas::LineCap::ROUND);
    ctx.closePath();
    // shift not held
    ctx.stroke(Colours::Green);
    // Horizontal line
    ctx.beginPath();
    ctx.moveTo(
      line_x - 0.5 * bar_width,
      line_bot - engine.props.operators.at(cur_op).outLev.normalize() * (line_bot - line_top));
    ctx.lineTo(
      line_x + 0.5 * bar_width,
      line_bot - engine.props.operators.at(cur_op).outLev.normalize() * (line_bot - line_top));
    ctx.lineWidth(6.0);
    ctx.lineCap(Canvas::LineCap::ROUND);
    ctx.closePath();
    // shift not held
    ctx.stroke(Colours::Green);
  }

  void OTTOFMSynthScreen::draw_with_shift(ui::vg::Canvas& ctx)
  {
    using namespace ui::vg;
    ctx.font(Fonts::Norm, 35);
    constexpr float x_pad_left = 90;
    constexpr float x_pad = 30;
    constexpr float y_pad = 50;
    constexpr float space = (height - 2.f * y_pad) / 3.f;
    // Ratio and Detune
    ctx.beginPath();
    ctx.fillStyle(Colours::Blue);
    ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Middle);
    ctx.fillText("Detune", {x_pad_left, y_pad});

    ctx.beginPath();
    ctx.fillStyle(Colours::Blue);
    ctx.textAlign(HorizontalAlign::Right, VerticalAlign::Middle);
    ctx.fillText(fmt::format("{:2}", engine.props.operators.at(cur_op).detune),
                 {width - x_pad, y_pad});

    // Operator level
    // vertical line
    float line_top = y_pad + 0.7 * space;
    float line_bot = line_top + 1.5 * space;
    float line_x = width - 1.5 * x_pad;
    float bar_width = 20.f;
    ctx.beginPath();
    ctx.moveTo(line_x, line_top);
    ctx.lineTo(line_x, line_bot);
    ctx.lineWidth(6.0);
    ctx.lineCap(Canvas::LineCap::ROUND);
    ctx.closePath();
    // shift is held
    ctx.stroke(Colours::Gray60);
    // Horizontal line
    ctx.beginPath();
    ctx.moveTo(
      line_x - 0.5 * bar_width,
      line_bot - engine.props.operators.at(cur_op).outLev.normalize() * (line_bot - line_top));
    ctx.lineTo(
      line_x + 0.5 * bar_width,
      line_bot - engine.props.operators.at(cur_op).outLev.normalize() * (line_bot - line_top));
    ctx.lineWidth(6.0);
    ctx.lineCap(Canvas::LineCap::ROUND);
    ctx.closePath();
    // shift not held
    ctx.stroke(Colours::Gray60);

    // Algorithm
    ctx.beginPath();
    ctx.fillStyle(Colours::Red);
    ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Middle);
    ctx.fillText("Algorithm", {x_pad_left, y_pad + 3 * space});

    ctx.beginPath();
    ctx.fillStyle(Colours::Red);
    ctx.textAlign(HorizontalAlign::Right, VerticalAlign::Middle);
    ctx.fillText(fmt::format("{}", engine.props.algN), {width - x_pad, y_pad + 3 * space});
  }

  void OTTOFMSynthScreen::draw_envelope(Canvas& ctx)
  {
    constexpr float x_pad_left = 90;
    constexpr float x_pad = 30;
    constexpr float y_pad = 50;
    constexpr float space = (height - 2.f * y_pad) / 3.f;

    // Operator envelope
    constexpr auto b =
      vg::Box{x_pad_left, y_pad + 0.7 * space, width - x_pad_left - x_pad - 35.f, space * 1.5};
    const float spacing = 10.f;
    const float max_width = (b.width - 3 * spacing) / 3.f;

    bool is_modulator = algorithms[engine.props.algN].modulator_flags[cur_op];

    if (is_modulator) {
      float aw, dw, sh, rw;
      aw = max_width * engine.props.operators.at(cur_op).mAtt.normalize();
      dw = max_width * std::max(0.f, (engine.props.operators.at(cur_op).mDecrel.normalize() *
                                      (1 - engine.props.operators.at(cur_op).mSuspos.normalize())));
      sh = b.height * engine.props.operators.at(cur_op).mSuspos.normalize();
      rw = max_width * std::max(0.f, (engine.props.operators.at(cur_op).mDecrel.normalize() *
                                      engine.props.operators.at(cur_op).mSuspos.normalize()));

      ctx.lineWidth(6.f);
      // Drawing. Colors depend on whether or not shift is held
      // Attack
      ctx.beginPath();
      ctx.moveTo(b.x, b.y + b.height);
      ctx.lineTo(b.x + aw, b.y);
      ctx.lineTo(b.x + aw, b.y + b.height);
      ctx.closePath();
      // Choose colour
      if (shift) {
        ctx.stroke(Colours::Gray60);
        ctx.fill(Colours::Gray60);
      } else {
        ctx.stroke(Colours::Yellow);
        ctx.fill(Colours::Yellow);
      }

      // Decay
      ctx.beginPath();
      ctx.moveTo(b.x + aw + spacing, b.y + b.height);
      ctx.lineTo(b.x + aw + spacing, b.y);
      ctx.lineTo(b.x + aw + spacing + dw, b.y + b.height - sh);
      ctx.lineTo(b.x + aw + spacing + dw, b.y + b.height);
      ctx.closePath();
      if (!shift) {
        ctx.stroke(Colours::Gray60);
        ctx.fill(Colours::Gray60);
      } else {
        ctx.stroke(Colours::Yellow);
        ctx.fill(Colours::Yellow);
      }

      // Sustain
      ctx.beginPath();
      ctx.moveTo(b.x + aw + spacing + dw + spacing, b.y + b.height - sh);
      ctx.lineTo(b.x + b.width - spacing - rw, b.y + b.height - sh);
      ctx.lineTo(b.x + b.width - spacing - rw, b.y + b.height);
      ctx.lineTo(b.x + aw + spacing + dw + spacing, b.y + b.height);
      ctx.closePath();
      if (shift) {
        ctx.stroke(Colours::Green);
        ctx.fill(Colours::Green);
      } else {
        ctx.stroke(Colours::Gray60);
        ctx.fill(Colours::Gray60);
      }

      // Release
      ctx.beginPath();
      ctx.moveTo(b.x + b.width - rw, b.y + b.height);
      ctx.lineTo(b.x + b.width - rw, b.y + b.height - sh);
      ctx.lineTo(b.x + b.width, b.y + b.height);
      ctx.closePath();
      if (shift) {
        ctx.stroke(Colours::Yellow);
        ctx.fill(Colours::Yellow);
      } else {
        ctx.stroke(Colours::Gray60);
        ctx.fill(Colours::Gray60);
      }
    } else {
      // Feedback
      ctx.beginPath();
      if (!shift)
        ctx.fillStyle(Colours::Yellow);
      else
        ctx.fillStyle(Colours::Gray60);

      ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Middle);
      ctx.fillText("Self-mod", {x_pad_left, y_pad + 100});

      int circ_x = 2 * x_pad_left;
      int circ_y = 2.2 * y_pad;
      int rad = 15;


      ctx.beginPath();
      ctx.moveTo(circ_x - rad, circ_y);
      ctx.lineTo(circ_x - rad - 20, circ_y);
      ctx.arc(circ_x, circ_y, rad + 20, -M_PI, 0, false);
      ctx.stroke(Colours::Gray60);

      ctx.beginPath();
      ctx.arc(circ_x, circ_y, rad + 20, -engine.props.operators.at(cur_op).feedback / 0.4 * M_PI, 0,
              false);
      ctx.lineTo(circ_x + rad, circ_y);
      if (!shift)
        ctx.stroke(Colours::Yellow);
      else
        ctx.stroke(Colours::White);

      // Inner circle
      ctx.beginPath();
      ctx.circle({circ_x, circ_y}, rad);
      ctx.stroke(Colours::Gray60);
    }
  }

  void OTTOFMSynthScreen::draw_operators(ui::vg::Canvas& ctx)
  {
    ctx.lineWidth(6.f);
    constexpr float x_pad = 35;
    constexpr float y_pad = 50;
    constexpr float space = (height - 2.f * y_pad) / 3.f;

    // Draw lines between operators
    for (auto&& line : algorithms[engine.props.algN].operator_lines) {
      int x_middle = x_pad + 12;
      int mid_to_side = 15;
      int horizontal_length = 13;

      if (line.side == Drawside::left) {
        int x_close = x_middle - mid_to_side;
        int x_far = x_close - horizontal_length;

        int y_start = y_pad + (3 - line.start) * space;
        int y_end = y_pad + (3 - line.end) * space;

        ctx.beginPath();
        ctx.moveTo(x_close, y_start);
        ctx.lineTo(x_far, y_start);
        ctx.lineTo(x_far, y_end);
        ctx.lineTo(x_close, y_end);
        ctx.stroke(Colours::White);
      } else if (line.side == Drawside::right) {
        int x_close = x_middle + mid_to_side;
        int x_far = x_close + horizontal_length;

        int y_start = y_pad + (3 - line.start) * space;
        int y_end = y_pad + (3 - line.end) * space;

        ctx.beginPath();
        ctx.moveTo(x_close, y_start);
        ctx.lineTo(x_far, y_start);
        ctx.lineTo(x_far, y_end);
        ctx.lineTo(x_close, y_end);
        ctx.stroke(Colours::White);
      } else {
        int y_start = y_pad + (3 - line.start) * space + 16;
        int y_end = y_pad + (3 - line.end) * space - 16;

        ctx.beginPath();
        ctx.moveTo(x_middle, y_start);
        ctx.lineTo(x_middle, y_end);
        ctx.lineTo(x_middle, y_end);
        ctx.lineTo(x_middle, y_end);
        ctx.stroke(Colours::White);
      }
    }

    // draw operators
    for (int i = 0; i < 4; i++) {
      ctx.beginPath();
      if (algorithms[engine.props.algN].modulator_flags[i]) { // draw modulator
        ctx.rect({x_pad, y_pad + (3 - i) * space - 13}, {25, 25});
      } else { // draw carrier
        ctx.circle({x_pad + 12, y_pad + (3 - i) * space}, 15);
      }
      ctx.closePath();
      // Choose colour
      if (i == 3) {
        if (i == cur_op) {
          ctx.stroke(Colours::White);
          ctx.fill(Colours::White);
        } else {
          ctx.stroke(Colours::Blue);
        }
      } else if (i == 2) {
        if (i == cur_op) {
          ctx.stroke(Colours::White);
          ctx.fill(Colours::White);
        } else {
          ctx.stroke(Colours::Green);
        }
      } else if (i == 1) {
        if (i == cur_op) {
          ctx.stroke(Colours::White);
          ctx.fill(Colours::White);
        } else {
          ctx.stroke(Colours::Yellow);
        }
      } else if (i == 0) {
        if (i == cur_op) {
          ctx.stroke(Colours::White);
          ctx.fill(Colours::White);
        } else {
          ctx.stroke(Colours::Red);
        }
      }
      /*
      //Draw activity levels
      ctx.beginPath();
      float op_level;
      if(engine.props.algorithms[engine.props.algN].modulator_flags[i]){
        op_level =
      engine.props.voice_envelopes.at(engine.voice_mgr_.last_voice).ops.at(i).modulator*
            engine.props.operators.at(i).outLev;
      } else {
        op_level = engine.voice_mgr_.voices[last_voice].carrier*
            engine.props.operators.at(i).outLev;
      }
      if(engine.props.algorithms[engine.props.algN].modulator_flags[i]){ //draw modulator
        ctx.rect({x_pad + 12.5*(1 - op_level), y_pad + (3 - i)*space - 13 + 12.5*(1 - op_level)},
      {25*op_level, 25*op_level}); } else { // draw carrier ctx.circle({x_pad + 12, y_pad + (3 -
      i)*space}, 15*op_level);
      }
      //Choose colour
      if (i == 3) {
        ctx.fill(Colours::Blue);
      } else if (i == 2) {
        ctx.fill(Colours::Green);
      } else if (i == 1) {
        ctx.fill(Colours::Yellow);
      } else if (i == 0) {
        ctx.fill(Colours::Red);
      }
       */
    }

    // draw arrowheads
    for (auto&& line : algorithms[engine.props.algN].operator_lines) {
      int x_middle = x_pad + 12;
      int mid_to_side = 15;
      int side_length = 5;



      if (line.side == Drawside::left) {
        int x = x_middle - mid_to_side;
        int y = y_pad + (3 - line.end) * space;

        ctx.group([&] {
          ctx.lineWidth(4.f);
          ctx.beginPath();
          ctx.moveTo(x, y);
          ctx.lineTo(x - side_length, y - side_length);
          ctx.lineTo(x - side_length, y + side_length);
          ctx.closePath();
          ctx.stroke(Colours::White);
          ctx.fill(Colours::White);
        });
      } else if (line.side == Drawside::right) {
        int x = x_middle + mid_to_side;
        int y = y_pad + (3 - line.end) * space;

        ctx.group([&] {
          ctx.lineWidth(4.f);
          ctx.beginPath();
          ctx.moveTo(x, y);
          ctx.lineTo(x + side_length, y - side_length);
          ctx.lineTo(x + side_length, y + side_length);
          ctx.closePath();
          ctx.stroke(Colours::White);
          ctx.fill(Colours::White);
        });
      } else {
        int x = x_middle;
        int y = y_pad + (3 - line.end) * space - mid_to_side;

        ctx.group([&] {
          ctx.lineWidth(4.f);
          ctx.beginPath();
          ctx.moveTo(x, y);
          ctx.lineTo(x + side_length, y - side_length);
          ctx.lineTo(x - side_length, y - side_length);
          ctx.closePath();
          ctx.stroke(Colours::White);
          ctx.fill(Colours::White);
        });
      }
    }
  }

} // namespace otto::engines
