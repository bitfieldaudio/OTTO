#include "core/ui/vector_graphics.hpp"
#include "ottofm.hpp"

#include "services/application.hpp"

#include "ottofm.faust.hpp"
#include "services/ui_manager.hpp"
#include "core/audio/voice_manager.hpp"

namespace otto::engines {

  using namespace ui;
  using namespace ui::vg;

  // Usefuls structs
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
        return fmt::format("{}/{}",numerator,denominator);
    }

  };

  enum struct Drawside {
    left,
    middle,
    right,
    //Number of sides
    n_sides,
  };

  struct Operatorline {
    int start;
    int end;
    Drawside side;

    constexpr Operatorline(int st = 1, int en = 2, Drawside si = Drawside::middle)
                                                  : start(st), end(en), side(si) {}
  };

  struct Algorithm {
    std::array<bool,4> modulator_flags = {false,false,false,false};
    std::vector<Operatorline> operator_lines;

    Algorithm(std::initializer_list<int> modulator_idx = {},
                        std::vector<Operatorline> op_lines = {})
                                 : operator_lines(op_lines) {
      for(auto&& idx : modulator_idx){
        modulator_flags[idx] = true;
      }
    }
  };

  /*
   * Declarations
   */

  struct OTTOFMSynthScreen : EngineScreen<OTTOFMSynth> {
    void draw(Canvas& ctx) override;
    void drawWithShift(Canvas& ctx);
    void drawNoShift(Canvas& ctx);
    void drawOperators(Canvas& ctx);
    bool keypress(Key key) override;
    void rotary(RotaryEvent e) override;

    bool shift = false;
    int cur_op = 0;

    std::array<Fraction, 19> fractions = {{{1, 1},
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

    std::array<Algorithm,11> algorithms = {{Algorithm({1,2,3},
                                            {Operatorline(3,2,Drawside::middle),
                                             Operatorline(2,1,Drawside::middle),
                                             Operatorline(1,0,Drawside::middle)}),
                                            Algorithm({1,2,3},
                                            {Operatorline(3,1,Drawside::left),
                                             Operatorline(2,1,Drawside::right),
                                             Operatorline(1,0,Drawside::middle)}),
                                            Algorithm({1,2,3},
                                            {Operatorline(3,1,Drawside::left),
                                             Operatorline(2,1,Drawside::middle),
                                             Operatorline(1,0,Drawside::middle)}),
                                            Algorithm({1,2,3},
                                            {Operatorline(3,2,Drawside::left),
                                             Operatorline(3,1,Drawside::left),
                                             Operatorline(2,0,Drawside::right),
                                             Operatorline(1,0,Drawside::right)}),
                                            Algorithm({2,3},
                                            {Operatorline(3,2,Drawside::middle),
                                             Operatorline(2,1,Drawside::left),
                                             Operatorline(2,0,Drawside::left)}),
                                            Algorithm({2,3},
                                            {Operatorline(3,2,Drawside::middle),
                                             Operatorline(2,1,Drawside::middle)}),
                                            Algorithm({1,2,3},
                                            {Operatorline(3,0,Drawside::left),
                                             Operatorline(2,0,Drawside::right),
                                             Operatorline(1,0,Drawside::middle)}),
                                            Algorithm({1,3},
                                            {Operatorline(3,2,Drawside::middle),
                                             Operatorline(1,0,Drawside::middle)}),
                                            Algorithm({3},
                                            {Operatorline(3,2,Drawside::middle),
                                             Operatorline(3,1,Drawside::right),
                                             Operatorline(3,0,Drawside::left)}),
                                            Algorithm({3},
                                             {Operatorline(3,2,Drawside::middle)}),
                                            Algorithm({})}};

    using EngineScreen<OTTOFMSynth>::EngineScreen;
  };

  // DXOTTOSynth ////////////////////////////////////////////////////////////////

  OTTOFMSynth::OTTOFMSynth()
    : SynthEngine("OTTO.FM", props, std::make_unique<OTTOFMSynthScreen>(this)),
      voice_mgr_(props),
      faust_(std::make_unique<FAUSTCLASS>(), props)
  {}

  audio::ProcessData<1> OTTOFMSynth::process(audio::ProcessData<1> data)
  {
    voice_mgr_.process_before(data.midi_only());
    auto res = faust_.process(data.midi_only());
    voice_mgr_.process_after(data.midi_only());
    return res;
  }

  /*
   * OTTOFMSynthScreen
   */
  bool OTTOFMSynthScreen::keypress(Key key)
  {
    switch (key) {
    case ui::Key::blue_click: cur_op = 0; break;
    case ui::Key::green_click: cur_op = 1; break;
    case ui::Key::white_click: cur_op = 2; break;
    case ui::Key::red_click: cur_op = 3; break;
    default: return false; ;
    }
  }

  void OTTOFMSynthScreen::rotary(RotaryEvent e)
  {
    auto& props = engine.props;
    auto& current = props.operators.at(cur_op);
    switch (e.rotary) {
    case Rotary::Blue:
      if (!shift) {
        current.ratio_idx.step(e.clicks);
        current.ratio.set(float(fractions[current.ratio_idx]));
      } else{
        current.detune.step(e.clicks);
      }
      break;
    case Rotary::Green:
      if (!shift) {
        current.cAtt.step(e.clicks);
        current.mAtt.step(e.clicks);
      } else {
        current.cSus.step(e.clicks);
        current.mSuspos.step(e.clicks);
      }
      break;
    case Rotary::White:
      if (!shift) {
        current.cRel.step(e.clicks);
        current.mDecrel.step(e.clicks);
      } else {
        current.outLev.step(e.clicks);
      }
      break;
    case Rotary::Red:
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

    if(shift)
        drawWithShift(ctx);
    else
        drawNoShift(ctx);

    drawOperators(ctx);


  }

  void OTTOFMSynthScreen::drawNoShift(ui::vg::Canvas& ctx)
  {
    using namespace ui::vg;
    ctx.font(Fonts::Norm, 35);

    constexpr float x_pad_left = 90;
    constexpr float x_pad = 30;
    constexpr float y_pad = 50;
    constexpr float space = (height - 2.f * y_pad) / 3.f;
    //Ratio and Detune
    ctx.beginPath();
    ctx.fillStyle(Colours::Blue);
    ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Middle);
    ctx.fillText("Ratio", {x_pad_left, y_pad});

    ctx.beginPath();
    ctx.fillStyle(Colours::Blue);
    ctx.textAlign(HorizontalAlign::Right, VerticalAlign::Middle);
    ctx.fillText(fractions[engine.props.operators.at(cur_op).ratio_idx].to_string(), {width - x_pad, y_pad});

    //FM Amount
    ctx.beginPath();
    ctx.fillStyle(Colours::Red);
    ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Middle);
    ctx.fillText("FM", {x_pad_left, y_pad + 3 * space});

    ctx.lineWidth(6.f);
    constexpr float x_left = width - 6 * x_pad;
    constexpr float x_right = width - x_pad;
    constexpr float y_low =  y_pad + 3 * space + 10;
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

    //Operator level
    //vertical line
    float line_top = y_pad + 0.7 * space;
    float line_bot = line_top + 1.5*space;
    float line_x = width - 1.5*x_pad;
    float bar_width = 20.f;
    ctx.beginPath();
    ctx.moveTo(line_x, line_top);
    ctx.lineTo(line_x, line_bot);
    ctx.lineWidth(6.0);
    ctx.lineCap(Canvas::LineCap::ROUND);
    ctx.closePath();
    //shift not held
    ctx.stroke(Colours::Gray60);
    //Horizontal line
    ctx.beginPath();
    ctx.moveTo(line_x - 0.5*bar_width , line_bot - engine.props.operators.at(cur_op).outLev.normalize() * (line_bot-line_top));
    ctx.lineTo(line_x + 0.5*bar_width , line_bot - engine.props.operators.at(cur_op).outLev.normalize() * (line_bot-line_top));
    ctx.lineWidth(6.0);
    ctx.lineCap(Canvas::LineCap::ROUND);
    ctx.closePath();
    //shift not held
    ctx.stroke(Colours::Gray60);

    //Operator envelope
    constexpr auto b = vg::Box{ x_pad_left, y_pad + 0.7 * space, width - x_pad_left - x_pad - 35.f , space*1.5};
    const float spacing = 10.f;
    const float max_width = (b.width - 3 * spacing) / 3.f;
    float aw, dw, sh, rw;
    if (algorithms[engine.props.algN].modulator_flags[cur_op]) {
      aw = max_width * engine.props.operators.at(cur_op).mAtt.normalize();
      dw = max_width * std::max(0.f, (
                        engine.props.operators.at(cur_op).mDecrel.normalize()*
                        (1 - engine.props.operators.at(cur_op).mSuspos.normalize())));
      sh = b.height * engine.props.operators.at(cur_op).mSuspos.normalize();
      rw = max_width * std::max(0.f, (
               engine.props.operators.at(cur_op).mDecrel.normalize()*
               engine.props.operators.at(cur_op).mSuspos.normalize()));
    } else {
      aw = max_width * engine.props.operators.at(cur_op).cAtt.normalize();
      //dw = max_width * otto::core::audio::EnvelopeScreen::props.sustain.normalize();
      dw = max_width * 0.2;
      sh = b.height * engine.props.operators.at(cur_op).cSus.normalize();
      rw = max_width * engine.props.operators.at(cur_op).cRel.normalize();
    }

    ctx.lineWidth(6.f);

    const float arc_size = 0.9;
    //Drawing. Colors depend on whether or not shift is held
    ctx.beginPath();
    ctx.moveTo(b.x, b.y + b.height);
    ctx.quadraticCurveTo({b.x + aw * arc_size, b.y + b.height * arc_size}, {b.x + aw, b.y}); // curve
    ctx.lineTo(b.x + aw, b.y + b.height);
    ctx.closePath();
    //Shift is not held
    ctx.stroke(Colours::Green);
    ctx.fill(Colours::Green);

    ctx.beginPath();
    ctx.moveTo(b.x + aw + spacing, b.y + b.height);
    ctx.lineTo(b.x + aw + spacing, b.y);
    ctx.quadraticCurveTo({b.x + aw + spacing + dw * (1 - arc_size), b.y + (b.height - sh) * arc_size}, {b.x + aw + spacing + dw, b.y + b.height - sh}); // curve
    ctx.lineTo(b.x + aw + spacing + dw, b.y + b.height);
    ctx.closePath();
    if (algorithms[engine.props.algN].modulator_flags[cur_op]) {
      ctx.stroke(Colours::Yellow);
      ctx.fill(Colours::Yellow);
    } else {
      ctx.stroke(Colours::Gray60);
      ctx.fill(Colours::Gray60);
    }

    ctx.beginPath();
    ctx.moveTo(b.x + aw + spacing + dw + spacing,      b.y + b.height - sh);
    ctx.lineTo(b.x + b.width - spacing - rw, b.y + b.height - sh);
    ctx.lineTo(b.x + b.width - spacing - rw, b.y + b.height);
    ctx.lineTo(b.x + aw + spacing + dw + spacing, b.y + b.height);
    ctx.closePath();
    ctx.stroke(Colours::Gray60);
    ctx.fill(Colours::Gray60);

    ctx.beginPath();
    ctx.moveTo(b.x + b.width - rw, b.y + b.height);
    ctx.lineTo(b.x + b.width - rw, b.y + b.height - sh);
    ctx.quadraticCurveTo({b.x + b.width - rw * arc_size, b.y + b.height - sh * (1 - arc_size)}, {b.x + b.width,      b.y + b.height});
    ctx.closePath();
    ctx.stroke(Colours::Yellow);
    ctx.fill(Colours::Yellow);

  }

  void OTTOFMSynthScreen::drawWithShift(ui::vg::Canvas& ctx)
  {
    using namespace ui::vg;
    ctx.font(Fonts::Norm, 35);
    constexpr float x_pad_left = 90;
    constexpr float x_pad = 30;
    constexpr float y_pad = 50;
    constexpr float space = (height - 2.f * y_pad) / 3.f;
    //Ratio and Detune
    ctx.beginPath();
    ctx.fillStyle(Colours::Blue);
    ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Middle);
    ctx.fillText("Detune", {x_pad_left, y_pad});

    ctx.beginPath();
    ctx.fillStyle(Colours::Blue);
    ctx.textAlign(HorizontalAlign::Right, VerticalAlign::Middle);
    ctx.fillText(fmt::format("{:2}",engine.props.operators.at(cur_op).detune), {width - x_pad, y_pad});

    //Operator level
    //vertical line
    float line_top = y_pad + 0.7 * space;
    float line_bot = line_top + 1.5*space;
    float line_x = width - 1.5*x_pad;
    float bar_width = 20.f;
    ctx.beginPath();
    ctx.moveTo(line_x, line_top);
    ctx.lineTo(line_x, line_bot);
    ctx.lineWidth(6.0);
    ctx.lineCap(Canvas::LineCap::ROUND);
    ctx.closePath();
    //shift is held
    ctx.stroke(Colours::Yellow);
    //Horizontal line
    ctx.beginPath();
    ctx.moveTo(line_x - 0.5*bar_width , line_bot - engine.props.operators.at(cur_op).outLev.normalize() * (line_bot-line_top));
    ctx.lineTo(line_x + 0.5*bar_width , line_bot - engine.props.operators.at(cur_op).outLev.normalize() * (line_bot-line_top));
    ctx.lineWidth(6.0);
    ctx.lineCap(Canvas::LineCap::ROUND);
    ctx.closePath();
    //shift not held
    ctx.stroke(Colours::Yellow);

    //Operator envelope
    constexpr auto b = vg::Box{ x_pad_left, y_pad + 0.7 * space, width - x_pad_left - x_pad - 35.f , space*1.5};
    const float spacing = 10.f;
    const float max_width = (b.width - 3 * spacing) / 3.f;
    float aw, dw, sh, rw;
    if (algorithms[engine.props.algN].modulator_flags[cur_op]) {
      aw = max_width * engine.props.operators.at(cur_op).mAtt.normalize();
      dw = max_width * std::max(0.f, (
                        engine.props.operators.at(cur_op).mDecrel.normalize()*
                        (1 - engine.props.operators.at(cur_op).mSuspos.normalize())));
      sh = b.height * engine.props.operators.at(cur_op).mSuspos.normalize();
      rw = max_width * std::max(0.f, (
               engine.props.operators.at(cur_op).mDecrel.normalize()*
               engine.props.operators.at(cur_op).mSuspos.normalize()));
    } else {
      aw = max_width * engine.props.operators.at(cur_op).cAtt.normalize();
      //dw = max_width * engine.voice_mgr_.props.sustain.normalize();
      dw = max_width * 0.2;
      sh = b.height * engine.props.operators.at(cur_op).cSus.normalize();
      rw = max_width * engine.props.operators.at(cur_op).cRel.normalize();
    }

    ctx.lineWidth(6.f);

    const float arc_size = 0.9;
    //Drawing. Colors depend on whether or not shift is held
    ctx.beginPath();
    ctx.moveTo(b.x, b.y + b.height);
    ctx.quadraticCurveTo({b.x + aw * arc_size, b.y + b.height * arc_size}, {b.x + aw, b.y}); // curve
    ctx.lineTo(b.x + aw, b.y + b.height);
    ctx.closePath();
    //Shift is held
    ctx.stroke(Colours::Gray60);
    ctx.fill(Colours::Gray60);

    ctx.beginPath();
    ctx.moveTo(b.x + aw + spacing, b.y + b.height);
    ctx.lineTo(b.x + aw + spacing, b.y);
    ctx.quadraticCurveTo({b.x + aw + spacing + dw * (1 - arc_size), b.y + (b.height - sh) * arc_size}, {b.x + aw + spacing + dw, b.y + b.height - sh}); // curve
    ctx.lineTo(b.x + aw + spacing + dw, b.y + b.height);
    ctx.closePath();
    if (algorithms[engine.props.algN].modulator_flags[cur_op]) {
      ctx.stroke(Colours::Green);
      ctx.fill(Colours::Green);
    } else {
      ctx.stroke(Colours::Gray60);
      ctx.fill(Colours::Gray60);
    }

    ctx.beginPath();
    ctx.moveTo(b.x + aw + spacing + dw + spacing,      b.y + b.height - sh);
    ctx.lineTo(b.x + b.width - spacing - rw, b.y + b.height - sh);
    ctx.lineTo(b.x + b.width - spacing - rw, b.y + b.height);
    ctx.lineTo(b.x + aw + spacing + dw + spacing, b.y + b.height);
    ctx.closePath();
    ctx.stroke(Colours::Green);
    ctx.fill(Colours::Green);

    ctx.beginPath();
    ctx.moveTo(b.x + b.width - rw, b.y + b.height);
    ctx.lineTo(b.x + b.width - rw, b.y + b.height - sh);
    ctx.quadraticCurveTo({b.x + b.width - rw * arc_size, b.y + b.height - sh * (1 - arc_size)}, {b.x + b.width,      b.y + b.height});
    ctx.closePath();
    if (algorithms[engine.props.algN].modulator_flags[cur_op]) {
      ctx.stroke(Colours::Green);
      ctx.fill(Colours::Green);
    } else {
      ctx.stroke(Colours::Gray60);
      ctx.fill(Colours::Gray60);
    }

    //Algorithm
    ctx.beginPath();
    ctx.fillStyle(Colours::Red);
    ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Middle);
    ctx.fillText("Algorithm", {x_pad_left, y_pad + 3 * space});

    ctx.beginPath();
    ctx.fillStyle(Colours::Red);
    ctx.textAlign(HorizontalAlign::Right, VerticalAlign::Middle);
    ctx.fillText(fmt::format("{}", engine.props.algN),{width - x_pad, y_pad + 3 * space});
  }

  void OTTOFMSynthScreen::drawOperators(ui::vg::Canvas& ctx)
  {
    ctx.lineWidth(6.f);
    constexpr float x_pad = 35;
    constexpr float y_pad = 50;
    constexpr float space = (height - 2.f * y_pad) / 3.f;

    //Draw lines between operators
    for(auto&& line : algorithms[engine.props.algN].operator_lines){
      int x_middle = x_pad + 12;
      int mid_to_side = 15;
      int vertical_length = 10;

      if (line.side == Drawside::left) {
        int x_close = x_middle - mid_to_side;
        int x_far = x_close - vertical_length;

        int y_start = y_pad + line.start * space;
        int y_end = y_pad + line.end * space;

        ctx.beginPath();
        ctx.moveTo(x_close, y_start);
        ctx.lineTo(x_far, y_start);
        ctx.lineTo(x_far, y_end);
        ctx.lineTo(x_close, y_end);
        ctx.stroke(Colours::White);
      }
      else if (line.side == Drawside::right) {
        int x_close = x_middle + mid_to_side;
        int x_far = x_close + vertical_length;

        int y_start = y_pad + line.start * space;
        int y_end = y_pad + line.end * space;

        ctx.beginPath();
        ctx.moveTo(x_close, y_start);
        ctx.lineTo(x_far, y_start);
        ctx.lineTo(x_far, y_end);
        ctx.lineTo(x_close, y_end);
        ctx.stroke(Colours::White);
      } else {
        int y_start = y_pad + line.start * space - 16;
        int y_end = y_pad + line.end * space + 16;

        ctx.beginPath();
        ctx.moveTo(x_middle, y_start);
        ctx.lineTo(x_middle, y_end);
        ctx.lineTo(x_middle, y_end);
        ctx.lineTo(x_middle, y_end);
        ctx.stroke(Colours::White);
      }
    }

    //draw operators
    for(int i=0;i<4;i++){
      ctx.beginPath();
      if(algorithms[engine.props.algN].modulator_flags[i]){ //draw modulator
        ctx.rect({x_pad, y_pad + i*space - 13}, {25, 25});
      } else { // draw carrier
        ctx.circle({x_pad + 12, y_pad + i*space}, 15);
      }
      ctx.closePath();
      //Choose colour
      if (i == 0) {
        ctx.stroke(Colours::Blue);
        if(i == cur_op) ctx.fill(Colours::Blue);
      }
      else if (i == 1) {
        ctx.stroke(Colours::Green);
        if(i == cur_op) ctx.fill(Colours::Green);
      }
      else if (i == 2) {
        ctx.stroke(Colours::Yellow);
        if(i == cur_op) ctx.fill(Colours::Yellow);
      }
      else if (i == 3) {
        ctx.stroke(Colours::Red);
        if(i == cur_op) ctx.fill(Colours::Red);
      }

    }




  }


} // namespace otto::engines
