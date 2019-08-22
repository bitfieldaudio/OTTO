#include "core/ui/vector_graphics.hpp"
#include "util/algorithm.hpp"
#include "util/dsp/yule_walker.hpp"
#include "util/dsp/acovb.hpp"
#include "util/dsp/detectpitch.hpp"
#include "core/audio/processor.hpp"
#include "services/audio_manager.hpp"

#include "lpc.hpp"

namespace otto::engines {

  using namespace ui;
  using namespace ui::vg;
  using namespace dsp;
  using namespace gsl;
  using namespace otto::core::audio;

  struct LPCScreen : EngineScreen<LPC> {
    void draw(Canvas& ctx) override;
    bool keypress(Key key) override;
    void encoder(EncoderEvent e) override;

    using EngineScreen<LPC>::EngineScreen;
  };

  LPC::LPC() : EffectEngine<LPC>(std::make_unique<LPCScreen>(this)) {}

  void LPC::make_sha(span<float> buffer, int sha_period)
  {
    util::fill(buffer, 0.f);
    for (int i = this->lag; i < buffer.size(); i += sha_period) {
      buffer[i] = 1;
    }
    this->lag = sha_period - (int)(buffer.size()%sha_period);
  }

  ProcessData<2> LPC::process(ProcessData<1> data)
  {
    auto in = data.audio;
    auto gamma = Application::current().audio_manager->buffer_pool().allocate();
    util::copy(in, gamma.begin());

    acovb(span(gamma.begin(), gamma.end()));

    // Estimate coefficients
    //const int order = 25; // TODO: use parameter instead
    auto order = props.order;

    solve_yule_walker(span(gamma.begin(), order), this->sigmaAndCoeffs, this->scratchBuffer);

    // Vocal signals usually have fundamentals in the [20Hz; 600Hz] band
    const float f_min = 20;
    const float f_max = 600;
    const float sampling_freq = 44100;
    const int maxT = (int) ceil(sampling_freq/f_min);
    const int minT = (int) floor(sampling_freq/f_max);

    auto pitch = detect_pitch(span(gamma.begin(), gamma.end()), minT, maxT) + props.detune;

    gamma.release();

    // Create the source from:
    // 1. White noise
    // 2. Sha
    // 3. Harmonized Sha

    auto exciter = Application::current().audio_manager->buffer_pool().allocate();

    if (pitch != 0){
      make_sha(span(exciter.begin(), exciter.end()), pitch);
      for(auto&& s : exciter) s = s*0.8f + white()*0.2f;
    }else{
      for(auto&& s : exciter) s = white()*0.5f;
    }

    // Filtering

    int N = (int) in.size();

    for(int i=0; i < N; ++i){
      for(int j=0; j < order-i; j++){
        exciter[i] += prev_exciter_data[i+j] * this->sigmaAndCoeffs[1+j];
      }
      for(int j=0; j<i; j++){
        exciter[i] += exciter[j] * this->sigmaAndCoeffs[1+j+order-i];
      }
    }

    util::copy(span(exciter.end()-max_order, exciter.end()), prev_exciter_data.begin());

    auto r_out = Application::current().audio_manager->buffer_pool().allocate();
    //util::copy(exciter.begin(), r_out.begin());
    return ProcessData<2>({exciter, exciter});
  }

  // SCREEN //

  void LPCScreen::encoder(ui::EncoderEvent ev)
  {
    auto& props = engine.props;
    switch (ev.encoder) {
    case Encoder::blue: props.order.step(ev.steps); break;
    case Encoder::green: props.pitch_tracking.step(ev.steps); break;
    case Encoder::yellow: props.detune.step(ev.steps); break;
    case Encoder::red: props.snr.step(ev.steps); break;
    }
  }

  bool LPCScreen::keypress(ui::Key key)
  {
    return false;
  }

  void LPCScreen::draw(ui::vg::Canvas& ctx)
  {
    using namespace ui::vg;
    using namespace core::ui::vg;

    ctx.font(Fonts::Norm, 35);

    constexpr float x_pad = 30;
    constexpr float y_pad = 50;
    constexpr float space = (height - 2.f * y_pad) / 3.f;

    ctx.beginPath();
    ctx.fillStyle(Colours::Blue);
    ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Middle);
    ctx.fillText("order", {x_pad, y_pad});

    ctx.beginPath();
    ctx.fillStyle(Colours::Blue);
    ctx.textAlign(HorizontalAlign::Right, VerticalAlign::Middle);
    ctx.fillText(fmt::format("{:1}", engine.props.order), {width - x_pad, y_pad});

    ctx.beginPath();
    ctx.fillStyle(Colours::Green);
    ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Middle);
    ctx.fillText("tracking", {x_pad, y_pad + space});

    ctx.beginPath();
    ctx.fillStyle(Colours::Green);
    ctx.textAlign(HorizontalAlign::Right, VerticalAlign::Middle);
    ctx.fillText(fmt::format("{:1.2}", engine.props.pitch_tracking), {width - x_pad, y_pad + space});

    ctx.beginPath();
    ctx.fillStyle(Colours::Yellow);
    ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Middle);
    ctx.fillText("detune", {x_pad, y_pad + 2 * space});

    ctx.beginPath();
    ctx.fillStyle(Colours::Yellow);
    ctx.textAlign(HorizontalAlign::Right, VerticalAlign::Middle);
    ctx.fillText(fmt::format("{:1.2}", engine.props.detune), {width - x_pad, y_pad + 2 * space});

    ctx.beginPath();
    ctx.fillStyle(Colours::Red);
    ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Middle);
    ctx.fillText("balance", {x_pad, y_pad + 3 * space});

    ctx.beginPath();
    ctx.fillStyle(Colours::Red);
    ctx.textAlign(HorizontalAlign::Right, VerticalAlign::Middle);
    ctx.fillText(fmt::format("{:1.2}", engine.props.snr), {width - x_pad, y_pad + 3 * space});
  }

} // namespace otto::engines
