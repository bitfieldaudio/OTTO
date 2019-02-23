#include "core/ui/vector_graphics.hpp"
#include "util/algorithm.hpp"
#include "util/dsp/yule_walker.hpp"
#include "util/dsp/acovb.hpp"
#include "util/dsp/detectpitch.hpp"

#include "lpc.hpp"

namespace otto::engines {

  using namespace ui;
  using namespace ui::vg;

  struct LPCScreen : EngineScreen<LPC> {
    void draw(Canvas& ctx) override;
    bool keypress(Key key) override;
    void rotary(RotaryEvent e) override;

    using EngineScreen<LPC>::EngineScreen;
  };

  LPC::LPC() : EffectEngine("LPC", props, std::make_unique<LPCScreen>(this)) {}

  void LPC::makeSha(gsl::span<float> buffer, float sha_period, int lag)
  {
    util::fill(buffer, 0.f);
    for (int i = lag; i < buffer.size(); i += sha_period) {
      buffer[i] = 1;
    }
    lag = sha_period - buffer.size()%sha_period;
  }

  audio::ProcessData<2> LPC::process(audio::ProcessData<2> data)
  {
    // TODO: Add processing
    #define ORDER 25
    for(int i=0;i<ORDER;++i) acov[i] = data[i];
    acov = acovb(acov);

    // Vocal signals usually have fundamentals in the [20Hz; 600Hz] band
    const float f_min = 20;
    const float f_max = 600;

    const float sampling_freq = 44100;

    const maxT = ceil(sampling_freq/f_min);
    const minT = floor(sampling_freq/f_max);

    auto pitch = detect_pitch(gsl::span<float> data, unsigned minT, unsigned maxT);
    // Estimate coefficients

    solve_yule_walker(acov.subspan(0, ORDER), sigma_and_coeffs, scratch_buffer);

    // Create the source from:
    // 1. White noise
    // 2. Sha
    // 3. Harmonized Sha

    if (pitch !=0){
      makeSha(data, pitch, lag);
      for(auto&& s : data) s = s*0.8 + white()*0.2;
    }else{
      for(auto&& s : data) s = white()*0.5;
    }

    // copy in buffer
    auto data_out = data;

    // Filtering
    for(int i=0;i<ORDER;++i){
      if (i < ORDER){
        // at the start of the buffer, we have to use memorised data
        for(int j=0; j<=i;++j){
          data_out[i] += data[i-j] * sigma_and_coeffs[1+j];
        }
        for(int j=i+1; j < ORDER;++i){
          data_out[i] += prev_audio_data[i-j] * sigma_and_coeffs[1+j];
        }
      }else{
        for(int j=0; j< ORDER;++j){
          data_out[i] += data[i-j] * sigma_and_coeffs[1+j];
        }
      }
    }

    return data_out;
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
