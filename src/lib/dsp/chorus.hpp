#include <Gamma/Delay.h>
#include <Gamma/ipl.h>

/// Variable length delay-line with feedback and/or feedforward.

/// The general comb filter transfer function provides N evenly spaced poles
/// and/or zeroes around the unit circle. Feedback and feedforward produce
/// evenly spaced resonances and notches, respectively, in the frequency
/// response. Positive feeds result in even harmonics and negative feeds give
/// odd harmonics. If the feedback and feedforward amounts are inverses of each
/// other, an Nth order all-pass filter results. Comb filters are stable as
/// long as |feedback| < 1.
///
/// \tparam Tv	Value (sample) type
/// \tparam Si	Interpolation strategy
/// \tparam Tp	Parameter type
/// \tparam Td	Domain type
/// \ingroup Delay Filter
// H(z) = (ffd + z^-m) / (1 - fbk z^-m)
// y[n] = ffd x[n] + x[n-m] + fbk y[n-m]
template<class Tv = gam::real,
         template<class> class Si = gam::ipl::Linear,
         class Tp = gam::real,
         class Td = gam::DomainObserver>
class ChorusComb : public gam::Multitap<Tv, Si, Td> {
private:
  typedef gam::Multitap<Tv, Si, Td> Base;

public:
  /// \param[in]	delay		Delay length. The size of the delay line will
  ///							be the smallest possible power of two.
  /// \param[in]  N       Number of taps on the delay line.
  /// \param[in]	ffd			Feedforward amount, in [-1, 1]
  /// \param[in]	fbk			Feedback amount, in (-1, 1)
  ChorusComb(float delayMax, const Tp& ffd = Tp(0), const Tp& fbk = Tp(0));

  /// Set number of units for response to decay to end value

  /// The sign of the decay length determines the sign of the feedback coefficient.
  /// The default end value of 0.001 (-60 dB) is the reverberation time of
  /// the filter.  Setting the decay amount effects only the feedback value.
  /// The decay must be updated whenever the delay length of the filter changes.
  void decay(float units, float end = 0.001f);

  /// Sets feedback to argument and feedforward to argument negated
  void allPass(const Tp& v);

  void fbk(const Tp& v); ///< Set feedback amount, in (-1, 1)
  void ffd(const Tp& v); ///< Set feedforward amount [-1, 1]
  void feeds(const Tp& fwd, const Tp& bwd)
  {
    ffd(fwd);
    fbk(bwd);
  }

  void set(float delay, const Tp& ffd, const Tp& fbk); ///< Set several parameters
  void set_delays(float d0, float d1, float d2, float d3);

  void operator()(const Tv& in, Tv& oL, Tv& oR); ///< Returns next filtered value

  float norm() const;    ///< Get unity gain scale factor
  float normFbk() const; ///< Get unity gain scale factor due to feedback
  float normFfd() const; ///< Get unity gain scale factor due to feedforward
  Tp ffd() const;        ///< Get feedforward amount
  Tp fbk() const;        ///< Get feedback amount

protected:
  Tp mFFD, mFBK;
};

#define TM1 template<class Tv, template<class> class Si, class Tp, class Td>
#define TM2 Tv, Si, Tp, Td

TM1 ChorusComb<TM2>::ChorusComb(float delayMax, const Tp& ffd, const Tp& fbk)
  : gam::Multitap<Tv, Si, Td>(delayMax, 4), mFFD(ffd), mFBK(fbk)
{}

TM1 inline void ChorusComb<TM2>::operator()(const Tv& in, Tv& oL, Tv& oR)
{
  oL = this->read(0) + 0.5 * this->read(1) + in * mFFD;
  oR = this->read(2) + 0.5 * this->read(1) + in * mFFD;
  this->write(in + this->read(3) * mFBK);
}

TM1 inline void ChorusComb<TM2>::decay(float units, float end)
{
  mFBK = powf(end, this->delay() / gam::scl::abs(units));
  if (units < 0.f) mFBK = -mFBK;
}

TM1 inline void ChorusComb<TM2>::set_delays(float d0, float d1, float d2, float d3)
{
  this->delay(d0, 0);
  this->delay(d1, 1);
  this->delay(d2, 2);
  this->delay(d3, 3);
}

TM1 inline void ChorusComb<TM2>::allPass(const Tp& v)
{
  fbk(v);
  ffd(-v);
}
TM1 inline void ChorusComb<TM2>::fbk(const Tp& v)
{
  mFBK = v;
}
TM1 inline void ChorusComb<TM2>::ffd(const Tp& v)
{
  mFFD = v;
}
TM1 inline void ChorusComb<TM2>::set(float d, const Tp& ff, const Tp& fb)
{
  this->delay(d);
  ffd(ff);
  fbk(fb);
}

TM1 inline Tp ChorusComb<TM2>::fbk() const
{
  return mFBK;
}
TM1 inline Tp ChorusComb<TM2>::ffd() const
{
  return mFFD;
}
TM1 inline float ChorusComb<TM2>::norm() const
{
  return (1.f - gam::scl::abs(fbk())) / (1.f + gam::scl::abs(ffd()));
}
TM1 inline float ChorusComb<TM2>::normFbk() const
{
  return 1.f - gam::scl::abs(fbk());
}
TM1 inline float ChorusComb<TM2>::normFfd() const
{
  return 1.f / (1.f + gam::scl::abs(ffd()));
}

#undef TM1
#undef TM2

///
/// \ingroup Effects
template<class T = gam::real>
class ChorusEffect {
public:
  /// \param[in] delay	Delay interval
  /// \param[in] depth	Depth of delay-line modulation
  /// \param[in] freq		Frequency of modulation
  /// \param[in] ffd		Feedforward amount
  /// \param[in] fbk		Feedback amount
  ChorusEffect(float delayMax = 0.042,
               float depth = 0.007,
               float freq1 = 0.15,
               float freq2 = 0.4,
               float ffd = 0.7,
               float fbk = 0.0)
    : comb(delayMax, ffd, fbk),
      mod1A(freq1, 0),
      mod1B(freq1, 0.33f),
      mod1C(freq1, 0.66f),
      mod2A(freq2, 0),
      mod2B(freq2, 0.33f),
      mod2C(freq2, 0.66f),
      mDelayMax(delayMax),
      mDepth1(depth)
  {
    mDepth2 = depth * 0.2;
    mCenter = mDelayMax - mDepth1 - mDepth2;
  }

  ChorusEffect& maxDelay(float v)
  {
    comb.maxDelay(v);
    return *this;
  }
  ChorusEffect& fbk(float v)
  {
    comb.fbk(v);
    return *this;
  }
  ChorusEffect& ffd(float v)
  {
    comb.ffd(v);
    return *this;
  }
  ChorusEffect& freq1(float v)
  {
    mod1A.freq(v);
    mod1C.freq(v);
    mod1C.freq(v);
    return *this;
  }
  ChorusEffect& freq2(float v)
  {
    mod2A.freq(v);
    mod2C.freq(v);
    mod2C.freq(v);
    return *this;
  }
  ChorusEffect& depth(float v)
  {
    mDepth1 = v;
    mDepth2 = 0.2 * v;
    return *this;
  }
  ChorusEffect& center(float v)
  {
    mCenter = v;
    return *this;
  }
  float center()
  {
    return mCenter;
  }
  void rate(float v)
  {
    freq1(v);
    freq2(1.16 * v);
  }


  /// Filter sample (mono-stereo)
  void operator()(const T& in, T& o1, T& o2)
  {
    modulate();
    comb(in, o1, o2);
  }


  /// Perform delay modulation step (must manually step play heads after use!)
  void modulate()
  {
    float d0 = mCenter + mod1A() * mDepth1 + mod2A() * mDepth2;
    float d1 = mCenter + mod1B() * mDepth1 + mod2B() * mDepth2;
    float d2 = mCenter + mod1C() * mDepth1 + mod2C() * mDepth2;
    float d3 = mCenter;
    comb.set_delays(d0, d1, d2, d3);
  }

  ChorusComb<T, gam::ipl::Linear> comb;                 ///< Multitap comb filter
  gam::Sine<> mod1A, mod1B, mod1C, mod2A, mod2B, mod2C; ///< Modulators

private:
  float mDelayMax; // Delay interval
  float mDepth1, mDepth2, mCenter;
};
