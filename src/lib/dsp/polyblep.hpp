#pragma once

#include <cmath>
#include <numbers>
#include <utility>

#include <Gamma/Domain.h>
#include <Gamma/Oscillator.h>
#include <Gamma/scl.h>


namespace otto::dsp {

  // A PolyBLEP oscillator with hardsync.
  // The BLEP is two samples long -
  // one before and one after any discontinuity.
  // For this reason, it is always outputting the _previous_ sample
  // compared to the one directed by the  AccumPhase base class.
  template<class Tv = gam::real>
  struct PolyBLEPSaw {
    PolyBLEPSaw(float frq = 440, float phs = 0) : phase(frq, phs), sync_phase(frq, phs) {}

    Tv operator()() noexcept;

    Tv freq() noexcept
    {
      return phase.freq();
    }
    void freq(Tv frq) noexcept
    {
      phase.freq(frq);
    }
    Tv sync_freq() noexcept
    {
      return sync_phase.freq();
    }
    void sync_freq(Tv frq) noexcept
    {
      sync_phase.freq(frq);
    }

    bool sync_on() const noexcept
    {
      return sync_on_;
    }
    void sync_on(bool on) noexcept
    {
      sync_on_ = on;
    }

  private:
    Tv polyblep_before(Tv t, Tv dt) const noexcept;
    Tv polyblep_after(Tv t, Tv dt) const noexcept;
    Tv phase_increment(Tv phs1, Tv phs2) const noexcept;
    bool sync_on_ = true;
    Tv current_sample = Tv(0);
    Tv current_phase = Tv(0);
    Tv next_sample = Tv(0);
    Tv next_phase = Tv(0);
    // For sync accumulator
    Tv current_sync_phase = Tv(0);
    Tv next_sync_phase = Tv(0);
    // Phase accumulators
    gam::Accum<> phase;
    gam::Accum<> sync_phase;
  };

  template<class Tv>
  inline Tv PolyBLEPSaw<Tv>::phase_increment(Tv phs1, Tv phs2) const noexcept
  {
    if (phs2 >= phs1) return phs2 - phs1;
    return phs2 + (Tv(1) - phs1);
  }

  // The call operator builds the following sample, but sends out the one
  // it calculated the last time. This way, it has a chance to adjust
  // it if it turns out the wave resets between samples
  template<class Tv>
  inline Tv PolyBLEPSaw<Tv>::operator()() noexcept
  {
    // Increment sync accumulator
    bool sync_phase_wrap = sync_phase();
    next_sync_phase = sync_phase.phase(); // [0, 1]
    Tv sync_dt = phase_increment(current_sync_phase, next_sync_phase);


    bool phase_wrap = phase();  // Increments phase
    next_phase = phase.phase(); // [0, 1]
    // PolyBLEP function depends on the phase increment
    // TODO: We don't need it in all samples
    Tv dt = phase_increment(current_phase, next_phase);

    // If sync phase wrapped (and we are syncing),
    // reset oscillator to correct phase
    if (sync_on() && sync_phase_wrap) {
      Tv fraction = next_sync_phase / sync_dt;
      phase.reset();
      phase.phaseAdd(dt * fraction);
      next_phase = phase.phase();
    }

    // Raw, non-bandlimited saw from current phase
    next_sample = Tv(2) * next_phase - Tv(1);

    // PolyBLEP-time. Correct for phasewrap/discontinuity.
    if (phase_wrap) {
      // Adjust samples
      current_sample -= polyblep_before(current_phase, dt);
      next_sample -= polyblep_after(next_phase, dt);
    }
    if (sync_phase_wrap) {
      // Adjust samples
      current_sample -= polyblep_before(current_sync_phase, dt);
      next_sample -= polyblep_after(next_sync_phase, dt);
    }

    std::swap(current_phase, next_phase);
    std::swap(current_sample, next_sample);

    std::swap(current_sync_phase, next_sync_phase);

    return next_sample;
  }

  template<class Tv>
  inline Tv PolyBLEPSaw<Tv>::polyblep_before(const Tv t, const Tv dt) const noexcept
  {
    Tv tx = (t - Tv(1)) / dt;
    return tx * tx + tx + tx + Tv(1);
  }

  template<class Tv>
  inline Tv PolyBLEPSaw<Tv>::polyblep_after(const Tv t, const Tv dt) const noexcept
  {
    Tv tx = t / dt;
    return tx + tx - tx * tx - Tv(1);
  }


} // namespace otto::dsp
