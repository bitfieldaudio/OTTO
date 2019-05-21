#include "rhodes.hpp"

#include "core/ui/vector_graphics.hpp"

namespace otto::engines {

  using namespace ui;
  using namespace ui::vg;

  /*
   * Declarations
   */

  struct RhodesSynthScreen : EngineScreen<RhodesSynth> {
    void draw(Canvas& ctx) override;
    bool keypress(Key key) override;
    void rotary(RotaryEvent e) override;

    using EngineScreen<RhodesSynth>::EngineScreen;
  };

  // RhodesSynth ////////////////////////////////////////////////////////////////

  RhodesSynth::RhodesSynth()
    : SynthEngine<RhodesSynth>(std::make_unique<RhodesSynthScreen>(this)), voice_mgr_(props)
  {}

  //Voice
  float RhodesSynth::Voice::operator()() noexcept
  {
    reson.freq(frequency());
    overtones.freq(frequency());
    float excitation = lpf(exciter() * (1 + noise()));
    float harmonics = env() * overtones();
    float orig_note = reson(excitation*hammer_strength);
    float aux = util::math::fasttanh3(0.3f*orig_note + props.asymmetry);
    return amp * pickup_hpf(powf(2, 10*aux)) + harmonics;
  }

  RhodesSynth::Voice::Voice(Pre& pre) noexcept : VoiceBase(pre) {
    reson.type(gam::RESONANT);
    reson.res(1500);
    reson.zero();

    exciter.attack(0.001);
    exciter.decay(1.f/frequency());
    exciter.curve(0);
    exciter.finish();

    noise.seed(123);

    lpf.type(gam::LOW_PASS);
    lpf.freq(powf(20,2));
    lpf.zero();

    pickup_hpf.type(gam::HIGH_PASS);
    pickup_hpf.freq(440.f);
    pickup_hpf.zero();

    overtones.resize(1024);
    overtones.addSine(7, 1, 0);
    overtones.addSine(20, 0.5, 0);

    env.decay(3);
  }

  void RhodesSynth::Voice::on_note_on() noexcept {
    reson.zero();

    exciter.decay(1.f/frequency());
    exciter.reset();

    hammer_strength = powf(2.f, (1.f + 3.0f * props.aggro * velocity()));

    noise.seed(123);

    lpf.freq(powf(velocity()*90*props.aggro + 20,2));
    lpf.zero();

    pickup_hpf.freq(frequency());
    pickup_hpf.zero();

    env.reset(1.7);
  }

  //Preprocessor
  RhodesSynth::Pre::Pre(Props& props) noexcept : PreBase(props)
  {

  }

  void RhodesSynth::Pre::operator()() noexcept {}

  //Postprocessor
  /// Constructor. Takes care of linking appropriate variables to props
  RhodesSynth::Post::Post(Pre& pre) noexcept : PostBase(pre)
  {

    props.lfo_depth.on_change().connect([this](float depth) {
        lfo_amount = depth*0.6;
    });
    props.lfo_speed.on_change().connect([this](float speed) {
        lfo.freq(speed*10);
    });
  }

  float RhodesSynth::Post::operator()(float in) noexcept
  {
    return 0.01f*in*(1 + lfo_amount*lfo.tri());
  }

  audio::ProcessData<1> RhodesSynth::process(audio::ProcessData<1> data)
  {
    return voice_mgr_.process(data);
  }

  /*
   * RhodesSynthScreen
   */

  bool RhodesSynthScreen::keypress(Key key)
  {
    return false;
  }

  void RhodesSynthScreen::rotary(RotaryEvent e)
  {

    switch (e.rotary) {
    case Rotary::blue:  engine.props.aggro.step(e.clicks); break;
    case Rotary::green:  engine. props.asymmetry.step(e.clicks); break;
    case Rotary::yellow: engine.props.lfo_speed.step(e.clicks); break;
    case Rotary::red: engine.props.lfo_depth.step(e.clicks); break;
    }

  }

  void RhodesSynthScreen::draw(ui::vg::Canvas& ctx)
  {
    using namespace ui::vg;
    using namespace core::ui::vg;

    //shift = Application::current().ui_manager->is_pressed(ui::Key::shift);

    ctx.font(Fonts::Norm, 35);

    constexpr float x_pad = 30;
    constexpr float y_pad = 50;
    constexpr float space = (height - 2.f * y_pad) / 3.f;

    ctx.beginPath();
    ctx.fillStyle(Colours::Blue);
    ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Middle);
    ctx.fillText("Aggro", {x_pad, y_pad});

    ctx.beginPath();
    ctx.fillStyle(Colours::Blue);
    ctx.textAlign(HorizontalAlign::Right, VerticalAlign::Middle);
    ctx.fillText(fmt::format("{:1}", engine.props.aggro), {width - x_pad, y_pad});

    ctx.beginPath();
    ctx.fillStyle(Colours::Green);
    ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Middle);
    ctx.fillText("Asym", {x_pad, y_pad + space});

    ctx.beginPath();
    ctx.fillStyle(Colours::Green);
    ctx.textAlign(HorizontalAlign::Right, VerticalAlign::Middle);
    ctx.fillText(fmt::format("{:1.2}", engine.props.asymmetry), {width - x_pad, y_pad + space});

    ctx.beginPath();
    ctx.fillStyle(Colours::Yellow);
    ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Middle);
    ctx.fillText("Speed", {x_pad, y_pad + 2 * space});

    ctx.beginPath();
    ctx.fillStyle(Colours::Yellow);
    ctx.textAlign(HorizontalAlign::Right, VerticalAlign::Middle);
    ctx.fillText(fmt::format("{:1.2}", engine.props.lfo_speed), {width - x_pad, y_pad + 2 * space});

    ctx.beginPath();
    ctx.fillStyle(Colours::Red);
    ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Middle);
    ctx.fillText("Depth", {x_pad, y_pad + 3 * space});

    ctx.beginPath();
    ctx.fillStyle(Colours::Red);
    ctx.textAlign(HorizontalAlign::Right, VerticalAlign::Middle);
    ctx.fillText(fmt::format("{:1.2}", engine.props.lfo_depth), {width - x_pad, y_pad + 3 * space});

    ///
  }
} // namespace otto::engines
