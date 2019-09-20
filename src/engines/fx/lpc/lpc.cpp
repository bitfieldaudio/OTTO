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

  LPC::LPC() : EffectEngine<LPC>(std::make_unique<LPCScreen>(this)) 
  {
    util::fill(this->prev_exciter_data, 0.f);
  }

  void LPC::make_sha(span<float> buffer, int sha_period)
  {
    util::fill(buffer, 0.f);
    for (int i = this->lag_; i < buffer.size(); i += sha_period) {
      buffer.at(i) = 1;
    }
    this->lag_ = sha_period - buffer.size()%sha_period;
  }

  ProcessData<2> LPC::process(ProcessData<1> data)
  {
    auto in = data.audio;
    auto gamma = Application::current().audio_manager->buffer_pool().allocate();
    util::copy(in, gamma.begin());

    acovb(span(gamma.begin(), gamma.end()));

    // Estimate coefficients
    auto order = props.order;

    solve_yule_walker(span(gamma.begin(), order), this->sigmaAndCoeffs, this->scratchBuffer);

    

    // Vocal signals usually have fundamentals in the [20Hz; 600Hz] band
    const float f_min = 20;
    const float f_max = 600;
    const float sampling_freq = 44100;
    const int maxT = (int) ceil(sampling_freq/f_min);
    const int minT = (int) floor(sampling_freq/f_max);

    auto pitch = detect_pitch(span(gamma.begin(), gamma.end()), minT, maxT) + props.detune;

    DLOGI("pitch: {}", pitch);
    //return ProcessData<2>({gamma, gamma});

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

    DLOGI("saC: {}", sigmaAndCoeffs[1]);

    DLOGI("saC: {}", sigmaAndCoeffs[order]);
    
    //Saving exciter samples for next buffer
    util::copy(span(exciter.end()-max_order, exciter.end()), prev_exciter_data.begin());

    // Filtering
    // This is essentially a convolution of 'order' exciter samples
    // and the estimated filter coefficients
    int N = (int) exciter.size();
    //Loop is done in reverse to preserve unaltered samples
    for(int i=N-1; i >= 0; i--){
      float sample = 0;
      //For the first iterations (in the end of the buffer)
      //Only this loop runs
      //Start loop from max of i-order and 0
      auto start = (i>order)*(i-order);
      for(int j=start; j<i; j++){
        sample += exciter[i-1-j+start] * this->sigmaAndCoeffs.at(1+j-start);
      }
      //Takes care of the memory from last buffer. Only runs the first order samples
      for(int j=0; j < order-i; j++){
        sample += prev_exciter_data.at(max_order-1-j) * this->sigmaAndCoeffs.at(1+j);
      }
      exciter[i] = sample;
    }

    for (auto& frm : exciter) {
      if (std::isnan(frm)) {
        LOGE("ProcessData was constructed with a frame containing NAN");
      } else if (frm == INFINITY) {
        LOGE("ProcessData was constructed with a frame containing INFINITY");
      } else if (frm == -INFINITY) {
        LOGE("ProcessData was constructed with a frame containing -INFINITY");
      } else {
        break;
      }
      // Set breakpoint here to catch error where it happens
      frm = 0;
      LOGE("The frame was set to zero here, but will crash the audio service in release builds!");
    }

    


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
