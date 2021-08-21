#pragma once

#include <Gamma/Oscillator.h>


namespace otto::dsp {
  /// Band-limited square wave

  /// This produces a Fourier representation of a square wave where the number of
  /// harmonics is adjusted automatically to prevent aliasing.
  /// Due to numerical issues, this generator should not be used for producing
  /// very low frequency modulation signals. For that purpose, it is better to use
  /// the LFO class.
  ///
  /// \tparam Tv	Value (sample) type
  /// \tparam Td	Domain type
  /// \ingroup Oscillator
  template<class Tv = gam::real, class Td = gam::DomainObserver>
  struct Triangle : public gam::Impulse<Tv, Td> {
    /// \param[in] frq		Frequency
    /// \param[in] phs		Phase, in [0, 1)
    Triangle(Tv frq = 440, Tv phs = 0) : gam::Impulse<Tv, Td>(frq, phs) {}


    /// Generate next sample - An integrated Square wave
    /// \param[in] itg		Leaky integration factor
    ///
    Tv operator()(Tv itg = 0.7)
    {
      // DLOGI("mPrev_tri: {}", mPrev_tri);
      return mPrev_tri = gam::Impulse<Tv, Td>::square(itg) + itg * mPrev_tri;
    }

  private:
    Tv mPrev_tri = 0;
  };


  // Band-limited Triangle with adjustable duty-cycle
  template<class Tv = gam::real, class Td = gam::DomainObserver>
  struct TrianglePW : public Td {
    /// \param[in] frq		Frequency
    /// \param[in] pw		  Pulse width, in [0, 1)
    TrianglePW(Tv frq = 440, Tv pw = 0.5)
      : mFreq(frq), mPW(pw), imp_up(gam::Impulse<Tv, Td>(frq, 0)), imp_down(gam::Impulse<Tv, Td>(frq, pw))
    {
      setGain();
    }

    void setGain()
    {
      mGain = 2.0 * mFreq / (Td::spu() * mPW * (1 - mPW));
      C6 = mPW;
    }
    void freq(float frq)
    {
      imp_up.freq(frq);
      imp_down.freq(frq);
      mFreq = frq;
      setGain();
    }
    void setDutyCycle(Tv pw)
    {
      imp_down.phase(imp_down.phase() - (mPW - pw)); // Shift of second BLIT
      mPW = pw;
      setGain();
    }

    Tv operator()(float itg = 0.99)
    {
      // Integrate for square
      mPrevRect = imp_up() - imp_down() + itg * mPrevRect;
      // Integrate for triangle
      // DLOGI("{}", mPrevRect);
      mPrevTri = mGain * (mPrevRect + C6) + itg * mPrevTri;

      return mPrevTri;
      // mPrev = gam::DWO<Sp, Td>::pulse() - (2 * mMod - 1) + itg * mPrev;
      // return mPrev * mGain;
      // return tri_;
      // return gam::DWO<Sp, Td>::tri();
    }

  private:
    gam::Impulse<Tv, Td> imp_up;
    gam::Impulse<Tv, Td> imp_down;
    float mPrevTri = 0;
    float mPrevRect = 0;
    float C6 = 0.5;
    float mPW;
    float mGain = 1;
    float mFreq;
  };

  /*
    // Band-limited Triangle with adjustable duty-cycle
    template<class Tv = gam::real, class Sp = gam::phsInc::Loop, class Td = gam::DomainObserver>
    struct TrianglePW {
      /// \param[in] frq		Frequency
      /// \param[in] phs		Phase, in [0, 1)
      /// \param[in] mod    Modifier amount (pulsewidth)
      TrianglePW(Tv frq = 440, Tv phs = 0.5, Tv mod = 0.5) : gam::DWO<Sp, Td>(frq, phs, mod) {}

      void freq(float frq) {
        mGain = 4.0 * frq / Td::spu();
        gam::DWO<Sp, Td>::freq(frq);
      }
      void setDutyCycle(Tv mod_)
      {
        mMod = mod_;
        gam::DWO<Sp, Td>::mod(mod_); // Duty Cycle of
      }

      Tv operator()(float itg = 0.99)
      {
        mPrev = gam::DWO<Sp, Td>::pulse() - (2*mMod - 1) + itg * mPrev;
        return mPrev * mGain;
        //return tri_;
        return gam::DWO<Sp, Td>::tri();
      }

    private:
      gam::Impulse<Tv, Td> imp_up;
      gam::Impulse<Tv, Td> imp_down;
      float mPrev = 0;
      float mMod = 0.5;
      float mGain = 1;
    };
  */

} // namespace otto::dsp