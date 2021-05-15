#pragma once
#include <Gamma/Envelope.h>
#include <Gamma/Oscillator.h>

namespace otto::dsp {

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

  struct FMOperator {
    FMOperator(float frq = 440, float outlevel = 1, bool modulator = false) {}

    float operator()(float phaseMod = 0) noexcept
    {
      if (modulator_)
        return env_() * sine(phaseMod) * outlevel_ * fm_amount_;
      else {
        previous_value_ = sine(phaseMod + feedback_ * previous_value_) * outlevel_;
        return previous_value_;
      }
    };

    /// Set frequency
    void freq(float frq)
    {
      sine.freq(frq);
    };

    /// Get current level
    float level()
    {
      return env_.value() * outlevel_;
    };

    /// Set fm_amount
    void fm_amount(float fm)
    {
      fm_amount_ = fm;
    };

    /// Reset envelope
    void reset()
    {
      env_.resetSoft();
    };

    /// Release envelope
    void release()
    {
      env_.release();
    };

    /// Finish envelope
    void finish()
    {
      env_.finish();
    };

  private:
    FMSine sine;
    gam::ADSR<> env_;

    bool modulator_ = false; /// If it is a modulator, use the envelope.
    float outlevel_ = 1;
    float feedback_ = 0; /// TODO:Implement in call operator
    float fm_amount_ = 1;

    float freq_ratio_ = 1;
    float detune_amount_ = 0;

    float previous_value_ = 0;
  };

} // namespace otto::dsp
