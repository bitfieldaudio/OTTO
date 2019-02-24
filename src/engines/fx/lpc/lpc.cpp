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
    void rotary(RotaryEvent e) override;

    using EngineScreen<LPC>::EngineScreen;
  };

  LPC::LPC() : EffectEngine("LPC", props, std::make_unique<LPCScreen>(this)) {}

  void LPC::makeSha(span<float> buffer, int sha_period)
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
    const int order = 25; // TODO: use parameter instead
    solve_yule_walker(span(gamma.begin(), order), this->sigmaAndCoeffs, this->scratchBuffer);

    // Vocal signals usually have fundamentals in the [20Hz; 600Hz] band
    const float f_min = 20;
    const float f_max = 600;
    const float sampling_freq = 44100;
    const int maxT = (int) ceil(sampling_freq/f_min);
    const int minT = (int) floor(sampling_freq/f_max);

    auto pitch = detect_pitch(span(gamma.begin(), gamma.end()), minT, maxT);

    gamma.release();

    // Create the source from:
    // 1. White noise
    // 2. Sha
    // 3. Harmonized Sha

    auto exciter = Application::current().audio_manager->buffer_pool().allocate();

    if (pitch != 0){
      makeSha(span(exciter.begin(), exciter.end()), pitch);
      for(auto&& s : exciter) s = s*0.8f + white()*0.2f;
    }else{
      for(auto&& s : exciter) s = white()*0.5f;
    }

    // TODO: filter exciter in-place
    auto l_out = Application::current().audio_manager->buffer_pool().allocate();

    // Filtering
    int N = (int) in.size();
    for(int i=0; i < N; ++i){
      if (i < order){
        // at the start of the buffer, we have to use memorised data
        for(int j=0; j<=i;++j){
          l_out[i] += exciter[i-j] * this->sigmaAndCoeffs[1+j];
        }
        for(int j=i+1; j < order;++j){
          l_out[i] += prev_exciter_data[i-j] * this->sigmaAndCoeffs[1+j];
        }
      }else{
        for(int j=0; j< order;++j){
          l_out[i] += exciter[i-j] * this->sigmaAndCoeffs[1+j];
        }
      }
    }

    util::copy(span(exciter.end()-max_order, exciter.end()), prev_exciter_data.begin());

    auto r_out = Application::current().audio_manager->buffer_pool().allocate();
    util::copy(l_out, r_out.begin());
    return ProcessData<2>({l_out, r_out});
  }

  // SCREEN //

  void LPCScreen::rotary(ui::RotaryEvent ev)
  {
    // TODO: add shift + encoder behaviour
    auto& props = engine.props;
    switch (ev.rotary) {
    case Rotary::blue: props.pitch.step(ev.clicks); break;
    case Rotary::green: props.pitch_tracking.step(ev.clicks); break;
    case Rotary::yellow: props.detune.step(ev.clicks); break;
    case Rotary::red: props.snr.step(ev.clicks); break;
    }
  }

  bool LPCScreen::keypress(ui::Key key)
  {
    // TODO: add shift + encoder behaviour
    return false;
  }

  void LPCScreen::draw(ui::vg::Canvas& ctx)
  {
    // TODO
  }

} // namespace otto::engines
