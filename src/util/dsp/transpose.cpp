#include "transpose.hpp"

namespace otto::dsp {

  /// Simple Pitch shifter
  SimplePitchShift::SimplePitchShift()
  {
    this->maxdelay(10000);
    this->crossfade(1000);

    for (int i = 0; i < 2; i++) {
      amp[i].attack(0.9 * _crossfade / gam::sampleRate());
      amp[i].decay(0.f);
      amp[i].sustain(1.0);
      amp[i].release(0.9 * _crossfade / gam::sampleRate());
      amp[i].finish();
    }

    lfo_delay[1].phase(0.5);
  }

  float SimplePitchShift::operator()(float in) noexcept
  {
    float res = float(0);
    for (int i = 0; i < 2; i++) {
      delay_amount[i] -= 1;
      if (delay_amount[i] < 0)
        delay_amount[i] = 0;
      else if (delay_amount[i] < _crossfade) {
        amp_amount[i] = 0.f;
        amp[i].release();
      }

      if (delay_amount[(i + 1) % 2] == _crossfade) {
        delay_amount[i] = _maxdelay + _crossfade;
        amp_amount[i] = 1.;
        amp[i].reset();
      }

      delay[i].delaySamples(delay_amount[i]);
      res += delay[i](in) * amp[i]();
    }
    return res;
  }

  void SimplePitchShift::crossfade(int cf)
  {
    _crossfade = cf;
    for (int i = 0; i < 2; i++) {
      delay[i].maxDelay((float) (_maxdelay + _crossfade) / gam::sampleRate());
    }
    _frac = cf / _maxdelay;
  }

  void SimplePitchShift::maxdelay(int md)
  {
    _maxdelay = md;
    for (int i = 0; i < 2; i++) {
      delay[i].maxDelay((float) (_maxdelay + _crossfade) / gam::sampleRate());
    }
    _frac = _crossfade / md;
  }

} // namespace otto::dsp
