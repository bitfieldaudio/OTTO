#pragma once


#include <cfloat> /* DBL_MAX, FLT_MAX */

#include <Gamma/Domain.h>
#include <Gamma/Envelope.h>
#include <Gamma/Strategy.h>
#include <Gamma/gen.h>
#include <Gamma/ipl.h>
#include <Gamma/scl.h>

namespace otto::dsp {

  /// Exponential envelope segment for smoothing out value changes.

  /// \ingroup Envelope Interpolation
  template<class T = gam::real, class Td = gam::DomainObserver>
  class SegExpBypass : public Td {
  public:
    /// \param[in] len		Length of segment in domain units
    /// \param[in] crv		Curvature of segment
    /// \param[in] start	Start value
    /// \param[in] end		End value
    SegExpBypass(T len = 0.001, T crv = -2, T start = 1, T end = 1) : mLen(len), mCrv(crv), mStart(start), mEnd(end)
    {
      onDomainChange(1);
    }

    /// Returns whether envelope is done
    bool done() const
    {
      return mCurve.value() >= T(1);
    }

    /// Jumps to the end of the curve
    void finish()
    {
      mCurve.value(T(1));
    }

    /// Generate next value
    T operator()()
    {
      if (done()) return mEnd;
      mCurve();
      return value();
    }

    /// Set new end value.  Start value is set to current value.
    void operator=(T v)
    {
      mStart = value();
      mEnd = v;
      mCurve.reset();
    }

    T getEnd()
    {
      return mEnd;
    }

    T value() noexcept
    {
      return gam::ipl::linear(gam::scl::min(mCurve.value(), T(1)), mStart, mEnd);
    }

    /// Set curvature.  Negative gives faster change, positive gives slower change.
    void curve(T v)
    {
      set(mLen, v);
    }

    /// Set length in domain units.
    void period(T v)
    {
      set(v, mCrv);
    }

    /// Get the length in domain units
    T period() const
    {
      return mLen;
    }

    void reset()
    {
      mCurve.reset();
    }

    /// Set length and curvature
    void set(T len, T crv)
    {
      mLen = len;
      mCrv = crv;
      mCurve.set(len * Td::spu(), crv, mCurve.value());
    }

    void onDomainChange(double r)
    {
      set(mLen, mCrv);
    }

  protected:
    T mLen, mCrv, mStart, mEnd;
    gam::Curve<T, T> mCurve;
  };

} // namespace otto::dsp
