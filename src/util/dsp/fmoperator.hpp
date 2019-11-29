#include <Gamma/Oscillator.h>
#include <Gamma/Envelope.h>

struct FMOperator {
  // Custom version of the 'Sine' in Gamma. We need to call it with a phase offset
  // instead of a frequency offset. (Phase modulation, not frequency modulation)
  struct FMSine : public gam::AccumPhase<> {
    FMSine(float frq = 440, float phs = 0) : AccumPhase<>(frq, phs, 1) {}
    /// Generate next sample with phase offset
    float operator()(float phsOffset) noexcept 
    {
      return gam::scl::sinP9(gam::scl::wrap(this->nextPhase() + phsOffset, 1.f, -1.f));
    };
  };

  FMOperator(float frq = 440, float outlevel = 1, bool modulator = false) {}

  FMSine sine;
  gam::ADSR<> env;

  bool modulator = false; /// If it is a modulator, use the envelope.
  float outlevel = 1;
  float feedback = 0; /// TODO:Implement in call operator
  float fm_amount = 1;

  float freq_ratio = 1;
  float detune_amount = 0;

  float previous_value = 0;

  float operator()(float phaseMod = 0) noexcept 
  {
    if (modulator)
      return env() * sine(phaseMod) * outlevel * fm_amount;
    else {
      previous_value = sine(phaseMod + feedback * previous_value) * outlevel;
      return previous_value;
    }
  };

  /// Set frequency
  void freq(float frq)
  {
    sine.freq(frq);
  }; 

  /// Get current level
  float level() { return env.value() * outlevel; }; 
};