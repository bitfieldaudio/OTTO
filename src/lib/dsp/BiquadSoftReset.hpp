#include "Gamma/Containers.h"
#include "Gamma/Domain.h"
#include "Gamma/Filter.h"
#include "Gamma/Types.h"
#include "Gamma/ipl.h"
#include "Gamma/scl.h"

template<class T = gam::real, class Td = gam::DomainObserver>
class PanFromConstant : public Td {
public:
  PanFromConstant(T tau)
  {
    pan.period(tau);
  };

  void period(T tau)
  {
    pan.period(tau);
  }

  void operator=(T new_cst)
  {
    cst = new_cst;
    pan.reset();
  };

  T operator()(T in)
  {
    T val = pan();
    return cst * val + in * (1 - val);
  };

private:
  T cst = T(0);
  gam::SegExp<T, Td> pan{0.1};
};


/// 2-pole/2-zero IIR filter with soft reset

/// The biquadratic filter contains 2 zeros and 2 poles in its transfer
/// function. The zeros provide a better response near the DC and Nyquist
/// frequencies than an all-pole filter would. Second-order IIRs have a 12
/// dB/octave cutoff slope and are normally cascaded (run in series) to obtain
/// a sharper response. This particular implementation utilizes the RBJ
/// Sallen-Key/Butterworth design from:
///
/// http://www.musicdsp.org/files/Audio-EQ-Cookbook.txt
///
/// \tparam Tv	Value (sample) type
/// \tparam Tp	Parameter type
/// \tparam Td	Domain observer type
/// \ingroup Filter
template<class Tv = gam::real, class Tp = gam::real, class Td = gam::DomainObserver>
class BiquadSoftReset : public Td {
public:
  /// \param[in]	frq		Center frequency
  /// \param[in]	res		Resonance (Q) amount in [1, inf)
  /// \param[in]	type	Type of filter
  BiquadSoftReset(Tp frq = Tp(1000), Tp res = Tp(0.707), gam::FilterType type = gam::LOW_PASS);


  /// Get array of 3 feedforward coefficients
  Tp* a()
  {
    return mA;
  }

  /// Get array of 3 feedback coefficients (first element, b0, is not used)
  Tp* b()
  {
    return mB;
  }

  const Tp* a() const
  {
    return mA;
  }
  const Tp* b() const
  {
    return mB;
  }

  /// Set feedforward (a) and feedback (b) coefficients directly
  void coef(Tp a0, Tp a1, Tp a2, Tp b1, Tp b2);


  void freq(Tp v);                                ///< Set center frequency
  void res(Tp v);                                 ///< Set resonance (Q)
  void level(Tp v);                               ///< Set level (PEAKING, LOW_SHELF, HIGH_SHELF types only)
  void set(Tp frq, Tp res);                       ///< Set filter center frequency and resonance
  void set(Tp frq, Tp res, gam::FilterType type); ///< Set all filter params
  void type(gam::FilterType type);                ///< Set type of filter
  void zero();                                    ///< Zero internal delays. Softly.
  void smoothOutput();                            ///< Manual smoothing of the output
  void smoothTime(Tp time);                       ///< Set smoothing time

  Tv operator()(Tv in); ///< Filter next sample
  Tv nextBP(Tv in);     ///< Optimized for band-pass types

  Tp freq() const;              ///< Get center frequency
  Tp res() const;               ///< Get resonance (Q)
  Tp level() const;             ///< Get level
  gam::FilterType type() const; ///< Get filter type

  void onDomainChange(double r);

protected:
  Tp mA[3];            // feedforward coefs
  Tp mB[3];            // feedback coefs (first element used to scale coefs)
  Tv d1, d2;           // inner sample delays
  Tp mFreq, mResRecip; // center frequency, 1/resonance
  Tp mLevel;           // amplitude level (for peaking)
  gam::FilterType mType;
  Tp mReal, mImag; // real, imag components of center frequency
  Tp mAlpha, mBeta;
  Tp mFrqToRad;
  Tv o0 = 0;
  PanFromConstant<Tv, Td> smooth{0.004};

  void resRecip(Tp v);
};


// Implementation_______________________________________________________________

template<class Tv, class Tp, class Td>
BiquadSoftReset<Tv, Tp, Td>::BiquadSoftReset(Tp frq, Tp res, gam::FilterType type) : d1(0), d2(0), mLevel(1), mBeta(1)
{
  onDomainChange(1);
  set(frq, res, type);
}

template<class Tv, class Tp, class Td>
void BiquadSoftReset<Tv, Tp, Td>::onDomainChange(double /*r*/)
{
  mFrqToRad = M_2PI * Td::ups();
  freq(mFreq);
}

template<class Tv, class Tp, class Td>
Tp BiquadSoftReset<Tv, Tp, Td>::freq() const
{
  return mFreq;
}

template<class Tv, class Tp, class Td>
Tp BiquadSoftReset<Tv, Tp, Td>::res() const
{
  return Tp(0.5) / mResRecip;
}

template<class Tv, class Tp, class Td>
Tp BiquadSoftReset<Tv, Tp, Td>::level() const
{
  return mLevel;
}

template<class Tv, class Tp, class Td>
gam::FilterType BiquadSoftReset<Tv, Tp, Td>::type() const
{
  return mType;
}

template<class Tv, class Tp, class Td>
void BiquadSoftReset<Tv, Tp, Td>::set(Tp freq_, Tp res_, gam::FilterType type_)
{
  mType = type_;
  res(res_);
  freq(freq_);
}

template<class Tv, class Tp, class Td>
inline void BiquadSoftReset<Tv, Tp, Td>::set(Tp frq, Tp res)
{
  set(frq, res, mType);
}

template<class Tv, class Tp, class Td>
void BiquadSoftReset<Tv, Tp, Td>::zero()
{
  d1 = d2 = Tv(0);
  smooth = o0;
}

template<class Tv, class Tp, class Td>
void BiquadSoftReset<Tv, Tp, Td>::smoothOutput()
{
  smooth = o0;
}

template<class Tv, class Tp, class Td>
void BiquadSoftReset<Tv, Tp, Td>::smoothTime(Tp time)
{
  smooth.period(time);
}

template<class Tv, class Tp, class Td>
void BiquadSoftReset<Tv, Tp, Td>::coef(Tp a0, Tp a1, Tp a2, Tp b1, Tp b2)
{
  mA[0] = a0;
  mA[1] = a1;
  mA[2] = a2;
  mB[1] = b1;
  mB[2] = b2;
}

template<class Tv, class Tp, class Td>
inline void BiquadSoftReset<Tv, Tp, Td>::freq(Tp v)
{
  mFreq = v;
  Tp w = gam::scl::clip(mFreq * mFrqToRad, Tp(3.13));
  mReal = gam::scl::cosT8(w);
  mImag = gam::scl::sinT7(w);
  resRecip(mResRecip);
}

template<class Tv, class Tp, class Td>
inline void BiquadSoftReset<Tv, Tp, Td>::level(Tp v)
{
  mLevel = v;
  switch (mType) {
    case gam::PEAKING: mBeta = Tp(1) / mLevel; break;
    case gam::LOW_SHELF:
    case gam::HIGH_SHELF: mBeta = Tp(2) * std::pow(mLevel, Tp(0.25)); break;
    default: mBeta = Tp(1);
  }
  resRecip(mResRecip);
}

template<class Tv, class Tp, class Td>
inline void BiquadSoftReset<Tv, Tp, Td>::resRecip(Tp v)
{
  mResRecip = v;
  mAlpha = mImag * mResRecip * mBeta;

  switch (mType) {
    case gam::LOW_SHELF:
    case gam::HIGH_SHELF: break; // coefs computed in type()
    default:
      // Note: b_0 is assumed to be equal to 1 in the difference equation.
      // For this reason, we divide all other coefficients by b_0.
      mB[0] = Tp(1) / (Tp(1) + mAlpha); // 1/b_0
      mB[1] = Tp(-2) * mReal * mB[0];
      mB[2] = (Tp(1) - mAlpha) * mB[0];
  }

  type(mType);
}

template<class Tv, class Tp, class Td>
inline void BiquadSoftReset<Tv, Tp, Td>::res(Tp v)
{
  resRecip(Tp(0.5) / v);
}

template<class Tv, class Tp, class Td>
inline void BiquadSoftReset<Tv, Tp, Td>::type(gam::FilterType typeA)
{
  mType = typeA;

  switch (mType) {
    case gam::LOW_PASS:
      mA[1] = (Tp(1) - mReal) * mB[0];
      mA[0] = mA[1] * Tp(0.5);
      mA[2] = mA[0];
      break;
    case gam::HIGH_PASS: // low-pass with odd k a_k and freq flipped
      mA[1] = (Tp(-1) - mReal) * mB[0];
      mA[0] = mA[1] * Tp(-0.5);
      mA[2] = mA[0];
      break;
    case gam::RESONANT:
      mA[0] = mImag * Tp(0.5) * mB[0];
      mA[1] = Tp(0);
      mA[2] = -mA[0];
      break;
    case gam::BAND_PASS:
      mA[0] = mAlpha * mB[0];
      mA[1] = Tp(0);
      mA[2] = -mA[0];
      break;
    case gam::BAND_REJECT:
      mA[0] = mB[0];
      mA[1] = mB[1];
      mA[2] = mB[0];
      break;
    case gam::ALL_PASS:
      mA[0] = mB[2];
      mA[1] = mB[1];
      mA[2] = Tp(1);
      break;
    case gam::PEAKING: {
      Tp alpha_A_b0 = mAlpha * mLevel * mB[0];
      mA[0] = mB[0] + alpha_A_b0;
      mA[1] = mB[1];
      mA[2] = mB[0] - alpha_A_b0;
    } break;
    case gam::LOW_SHELF: {
      Tp A = mBeta * mBeta * Tp(0.25); // sqrt(mLevel)
      Tp Ap1 = A + Tp(1), Am1 = A - Tp(1);
      mB[0] = Tp(1) / (Ap1 + Am1 * mReal + mAlpha); // 1/b_0
      mB[1] = Tp(-2) * (Am1 + Ap1 * mReal) * mB[0];
      mB[2] = (Ap1 + Am1 * mReal - mAlpha) * mB[0];
      mA[0] = A * (Ap1 - Am1 * mReal + mAlpha) * mB[0];
      mA[1] = Tp(2) * A * (Am1 - Ap1 * mReal) * mB[0];
      mA[2] = A * (Ap1 - Am1 * mReal - mAlpha) * mB[0];
    } break;
    case gam::HIGH_SHELF: {
      Tp A = mBeta * mBeta * Tp(0.25); // sqrt(mLevel)
      Tp Ap1 = A + Tp(1), Am1 = A - Tp(1);
      mB[0] = Tp(1) / (Ap1 - Am1 * mReal + mAlpha); // 1/b_0
      mB[1] = Tp(2) * (Am1 - Ap1 * mReal) * mB[0];
      mB[2] = (Ap1 - Am1 * mReal - mAlpha) * mB[0];
      mA[0] = A * (Ap1 + Am1 * mReal + mAlpha) * mB[0];
      mA[1] = Tp(-2) * A * (Am1 + Ap1 * mReal) * mB[0];
      mA[2] = A * (Ap1 + Am1 * mReal - mAlpha) * mB[0];
    } break;
    default:;
  };
}

template<class Tv, class Tp, class Td>
inline Tv BiquadSoftReset<Tv, Tp, Td>::operator()(Tv i0)
{
  // Direct form II
  i0 = i0 - d1 * mB[1] - d2 * mB[2];
  o0 = i0 * mA[0] + d1 * mA[1] + d2 * mA[2];
  d2 = d1;
  d1 = i0;
  return smooth(o0);
}

template<class Tv, class Tp, class Td>
inline Tv BiquadSoftReset<Tv, Tp, Td>::nextBP(Tv i0)
{
  i0 = i0 - d1 * mB[1] - d2 * mB[2];
  o0 = (i0 - d2) * mA[0];
  d2 = d1;
  d1 = i0;
  return smooth(o0);
}
