#pragma once

#include <Gamma/Envelope.h>

/// Envelope with a fixed number of exponential segments and a sustain point

/// The envelope consists of N exponential curve 'segments' and N+1 break-point
/// levels. The curvature and length of each segment and the break-point levels
/// can be controlled independently.
/// This class can be used to construct many specialized envelopes such as an AD
/// (Attack Decay), an ADSR (Attack Decay Sustain Release), and an ADSHR (Attack
/// Decay Sustain Hold Release). The number of envelope segments is fixed to
/// ensure better memory locality.
///
/// \tparam N	number of segments
/// \tparam Tv	value (sample) type
/// \tparam Tp	parameter type
/// \ingroup Envelope
template<int N, class Tv = gam::real, class Tp = gam::real, class Td = gam::DomainObserver>
class Env_lite : public Td {
public:
  Env_lite(float (*voice)(void));

  Env_lite(Tp lvl1, Tp len1, Tp lvl2, float (*voice)(void));

  Env_lite(Tp lvl1, Tp len1, Tp lvl2, Tp len2, Tp lvl3, float (*voice)(void));

  Env_lite(Tp lvl1, Tp len1, Tp lvl2, Tp len2, Tp lvl3, Tp len3, Tp lvl4, float (*voice)(void));


  /// Get the number of segments
  int size() const
  {
    return N;
  }

  /// Get the position, in samples, within the current segment
  unsigned position() const
  {
    return mPos;
  }

  /// Get the sustain break-point
  int sustainPoint() const
  {
    return mSustain;
  }

  /// Get the envelope's current segment
  int stage() const
  {
    return mStage;
  }

  /// Get the current envelope value
  Tv value() const
  {
    return mCurve.value();
  }

  /// Returns whether the envelope is done
  bool done() const
  {
    return mStage == size();
  }

  /// Returns whether the envelope is released
  bool released() const
  {
    return mSustain < 0;
  }

  /// Returns whether the envelope is currently sustained
  bool sustained() const
  {
    return (mStage == mSustain);
  }


  /// Generate next value
  Tv operator()();

  /// Release the envelope
  void release();


  /// Set whether envelope loops

  /// Note that when this is activated the last segment moves from the second
  /// to last level to the first level. Thus, the very last level is ignored.
  /// This is done to avoid clicking due to mismatched levels when the
  /// envelope wraps around.
  Env_lite& loop(bool v)
  {
    mLoop = v;
    return *this;
  }

  /// Sets the point at which the envelope holds its value until released
  Env_lite& sustainPoint(int v)
  {
    mSustain = v;
    return *this;
  }

  /// Disable sustain
  Env_lite& sustainDisable()
  {
    return sustainPoint(N);
  }

  /// Reset envelope to starting point
  void reset();

  /// Reset envelope to starting point setting first level to current level
  void resetSoft();

  /// Jump to end of envelope
  void finish();


  /// Get segment lengths array
  Tp* lengths()
  {
    return mLengths;
  }
  const Tp* lengths() const
  {
    return mLengths;
  }

  /// Set break-point values
  template<class V>
  Env_lite& lengths(const V* vals, int len)
  {
    int n = len <= size() ? len : size();
    for (int i = 0; i < n; ++i) lengths()[i] = vals[i];
    return *this;
  }

  /// Set first two segment lengths
  Env_lite& lengths(Tp a, Tp b)
  {
    Tp v[] = {a, b};
    return lengths(v, 2);
  }

  /// Set first three segment lengths
  Env_lite& lengths(Tp a, Tp b, Tp c)
  {
    Tp v[] = {a, b, c};
    return lengths(v, 3);
  }

  /// Set first four segment lengths
  Env_lite& lengths(Tp a, Tp b, Tp c, Tp d)
  {
    Tp v[] = {a, b, c, d};
    return lengths(v, 4);
  }

  /// Set first five segment lengths
  Env_lite& lengths(Tp a, Tp b, Tp c, Tp d, Tp e)
  {
    Tp v[] = {a, b, c, d, e};
    return lengths(v, 5);
  }

  /// Get total length of all envelope segments
  Tp totalLength() const;

  /// Set total length of envelope by adjusting one segment length

  /// \param[in] length		desired length
  /// \param[in] modSegment	segment whose length is modified to match desired length
  Env_lite& totalLength(Tp length, int modSegment);

  /// Set total length of envelope by scaling all segment lengths
  Env_lite& totalLength(Tp length);


  /// Get segment curvature array
  Tp* curves()
  {
    return mCurves;
  }
  const Tp* curves() const
  {
    return mCurves;
  }

  /// Set curvature of all segments
  Env_lite& curve(Tp v)
  {
    for (int i = 0; i < N; ++i) curves()[i] = v;
    return *this;
  }

  /// Set segment curve amounts
  template<class V>
  Env_lite& curves(const V* vals, int len)
  {
    int n = len < size() ? len : size();
    for (int i = 0; i < n; ++i) mCurves[i] = vals[i];
    return *this;
  }

  /// Set curvature of first two segments
  Env_lite& curves(Tp ca, Tp cb)
  {
    Tp c[] = {ca, cb};
    return curves(c, 2);
  }

  /// Set curvature of first three segments
  Env_lite& curves(Tp ca, Tp cb, Tp cc)
  {
    Tp c[] = {ca, cb, cc};
    return curves(c, 3);
  }

  /// Set curvature of first four segments
  Env_lite& curves(Tp ca, Tp cb, Tp cc, Tp cd)
  {
    Tp c[] = {ca, cb, cc, cd};
    return curves(c, 4);
  }


  /// Set length and curvature of a segment
  Env_lite& segment(int i, Tp len, Tp crv)
  {
    mLengths[i] = len;
    mCurves[i] = crv;
    return *this;
  }

  /// Set length and curvature of many segments
  template<class V>
  Env_lite& segments(const V* lens, const V* crvs, int len, int begin = 0)
  {
    int max = size() - begin;
    int n = len < max ? len : max;
    for (int i = 0; i < n; ++i) {
      segment(i + begin, lens[i], crvs[i]);
    }
    return *this;
  }

  /// Set length and curvature of first two segments
  Env_lite& segments(Tp la, Tp ca, Tp lb, Tp cb)
  {
    Tp l[] = {la, lb};
    Tp c[] = {ca, cb};
    return segments(l, c, 2);
  }

  /// Set length and curvature of first three segments
  Env_lite& segments(Tp la, Tp ca, Tp lb, Tp cb, Tp lc, Tp cc)
  {
    Tp l[] = {la, lb, lc};
    Tp c[] = {ca, cb, cc};
    return segments(l, c, 3);
  }

  /// Set length and curvature of first four segments
  Env_lite& segments(Tp la, Tp ca, Tp lb, Tp cb, Tp lc, Tp cc, Tp ld, Tp cd)
  {
    Tp l[] = {la, lb, lc, ld};
    Tp c[] = {ca, cb, cc, cd};
    return segments(l, c, 4);
  }


  /// Get break-point levels array
  Tv* levels()
  {
    return mLevels;
  }
  const Tv* levels() const
  {
    return mLevels;
  }

  /// Set break-point values
  template<class V>
  Env_lite& levels(const V* vals, int len)
  {
    int n = len <= size() ? len : size() + 1;
    for (int i = 0; i < n; ++i) levels()[i] = vals[i];
    return *this;
  }

  /// Set first two break-point levels
  Env_lite& levels(Tv a, Tv b)
  {
    Tv v[] = {a, b};
    return levels(v, 2);
  }

  /// Set first three break-point levels
  Env_lite& levels(Tv a, Tv b, Tv c)
  {
    Tv v[] = {a, b, c};
    return levels(v, 3);
  }

  /// Set first four break-point levels
  Env_lite& levels(Tv a, Tv b, Tv c, Tv d)
  {
    Tv v[] = {a, b, c, d};
    return levels(v, 4);
  }

  /// Set first five break-point levels
  Env_lite& levels(Tv a, Tv b, Tv c, Tv d, Tv e)
  {
    Tv v[] = {a, b, c, d, e};
    return levels(v, 5);
  }

  /// Set maximum level
  Env_lite& maxLevel(Tv v);

  /// Set function pointer
  Env_lite& setVoice(float (*voice)(void));

protected:
  gam::Curve<Tv, Tp> mCurve;
  Tp mLengths[N];    // segment lengths, in samples
  Tp mCurves[N];     // segment curvatures
  Tv mLevels[N + 1]; // break-point levels

  unsigned mPos, mLen; // position in and length of current segment, in samples
  int mStage;          // the current curve segment
  int mSustain;        // index of sustain point
  int mLoop;

  void setLen(int i)
  {
    mLen = mLengths[i] * Td::spu();
  }

  float (*voice_)(void);
};

// IMPLEMENTATION //



template<int N, class Tv, class Tp, class Td>
Env_lite<N, Tv, Tp, Td>::Env_lite(float (*voice)(void)) : mSustain(N), mLoop(0), voice_(voice)
{
  for (int i = 0; i < N; ++i) {
    mLengths[i] = 1e-8;
    mCurves[i] = -4;
    mLevels[i] = Tv();
  }
  mLevels[N] = Tv();
  reset();
}

template<int N, class Tv, class Tp, class Td>
Env_lite<N, Tv, Tp, Td>::Env_lite(Tp lvl1, Tp len1, Tp lvl2, float (*voice)(void))
  : mSustain(N), mLoop(0), voice_(voice)
{
  levels(lvl1, lvl2);
  lengths()[0] = len1;
  curve(-4);
  reset();
}

template<int N, class Tv, class Tp, class Td>
Env_lite<N, Tv, Tp, Td>::Env_lite(Tp lvl1, Tp len1, Tp lvl2, Tp len2, Tp lvl3, float (*voice)(void))
  : mSustain(N), mLoop(0), voice_(voice)
{
  levels(lvl1, lvl2, lvl3);
  lengths(len1, len2);
  curve(-4);
  reset();
}

template<int N, class Tv, class Tp, class Td>
Env_lite<N, Tv, Tp, Td>::Env_lite(Tp lvl1, Tp len1, Tp lvl2, Tp len2, Tp lvl3, Tp len3, Tp lvl4, float (*voice)(void))
  : mSustain(N), mLoop(0), voice_(voice)
{
  levels(lvl1, lvl2, lvl3, lvl4);
  lengths(len1, len2, len3);
  curve(-4);
  reset();
}

template<int N, class Tv, class Tp, class Td>
inline Tv Env_lite<N, Tv, Tp, Td>::operator()()
{
  // Sustain stage:
  if (sustained()) {
    return mLevels[mStage] * voice_();
  }

  // Interpolating along segment:
  else if (mPos < mLen) {
    ++mPos;
    return mCurve() * voice_();
  }

  // Just went past end of current segment and there are more left:
  else if (mStage < size()) {
    ++mStage;
    if (mLoop && done()) mStage = 0;
    if (!done()) {
      mPos = 0;
      setLen(mStage);
      int nextStage = mStage + 1;
      // If looping, ensure we wrap back around to first level
      if (mLoop && (nextStage == size())) nextStage = 0;
      mCurve.set(mLen, mCurves[mStage], mLevels[mStage], mLevels[nextStage]);

      // Immediately return start level of new stage
      return (*this)() * voice_();
    }
  }

  // Envelope is done. No call to parent voice here:
  return mLevels[mStage];
}

template<int N, class Tv, class Tp, class Td>
void Env_lite<N, Tv, Tp, Td>::release()
{
  if (released()) return;

  mSustain = -gam::scl::abs(mSustain);

  // begin release portion immediately starting at current level
  Tv curVal = value();
  mStage = -mSustain;
  if (!done()) {
    mPos = 0;
    setLen(mStage);
    mCurve.set(mLen, mCurves[mStage], curVal, mLevels[mStage + 1]);
  }
}

template<int N, class Tv, class Tp, class Td>
void Env_lite<N, Tv, Tp, Td>::reset()
{
  // this forces a stage increment upon first iteration
  mPos = 0; // 0xFFFFFFFF;
  mLen = 0;
  mStage = -1;
  mSustain = gam::scl::abs(mSustain);
}

template<int N, class Tv, class Tp, class Td>
void Env_lite<N, Tv, Tp, Td>::resetSoft()
{
  Tv curVal = value();
  mPos = 0;
  mStage = 0;
  setLen(mStage);
  mCurve.set(mLen, mCurves[mStage], curVal, mLevels[mStage + 1]);
  mSustain = gam::scl::abs(mSustain);
}

template<int N, class Tv, class Tp, class Td>
void Env_lite<N, Tv, Tp, Td>::finish()
{
  mStage = size();
  mPos = mLen;
  mSustain = gam::scl::abs(mSustain);
}

template<int N, class Tv, class Tp, class Td>
Tp Env_lite<N, Tv, Tp, Td>::totalLength() const
{
  Tp sum = Tp(0);
  for (int i = 0; i < size(); ++i) sum += mLengths[i];
  return sum;
}

template<int N, class Tv, class Tp, class Td>
Env_lite<N, Tv, Tp, Td>& Env_lite<N, Tv, Tp, Td>::totalLength(Tp length, int modSegment)
{
  mLengths[modSegment] = Tp(0);
  mLengths[modSegment] = length - totalLength();
  return *this;
}

template<int N, class Tv, class Tp, class Td>
Env_lite<N, Tv, Tp, Td>& Env_lite<N, Tv, Tp, Td>::totalLength(Tp length)
{
  Tp mul = length / totalLength();
  for (int i = 0; i < size(); ++i) {
    lengths()[i] *= mul;
  }
  return *this;
}

template<int N, class Tv, class Tp, class Td>
Env_lite<N, Tv, Tp, Td>& Env_lite<N, Tv, Tp, Td>::maxLevel(Tv v)
{
  Tv mx(0);
  for (int i = 0; i < N + 1; ++i) mx = gam::scl::max(gam::scl::abs(mLevels[i]), mx);
  v = v / mx;
  for (int i = 0; i < N + 1; ++i) mLevels[i] *= v;
  return *this;
}

template<int N, class Tv, class Tp, class Td>
Env_lite<N, Tv, Tp, Td>& Env_lite<N, Tv, Tp, Td>::setVoice(float (*voice)(void))
{
  voice_ = voice;
}

/// ADSR (Attack, Decay, Sustain, Release) envelope. Uses the Env_lite envelope template.

/// \tparam Tv	value (sample) type
/// \tparam Tp	parameter type
/// \tparam Td	domain observer type
/// \ingroup Envelope
template<class Tv = gam::real, class Tp = gam::real, class Td = gam::DomainObserver>
class ADSR_lite : public Env_lite<3, Tv, Tp, Td> {
public:
  using Env_lite<3, Tv, Tp, Td>::release;

  /// \param[in] att	Attack length
  /// \param[in] dec	Decay length
  /// \param[in] sus	Sustain level (as factor of amplitude)
  /// \param[in] rel	Release length
  /// \param[in] amp	Amplitude
  /// \param[in] crv	Curvature of all segments
  ADSR_lite(float (*voice)(void),
            Tp att = Tp(0.01),
            Tp dec = Tp(0.1),
            Tv sus = Tv(0.7),
            Tp rel = Tp(1.),
            Tv amp = Tv(1),
            Tp crv = Tp(-4))
  {
    this->setVoice(voice);
    this->sustainPoint(2);
    this->levels(0, amp, sus * amp, 0);
    attack(att).decay(dec).release(rel);
    this->curve(crv);
  }

  /// Set attack length
  ADSR_lite& attack(Tp len)
  {
    return setLen(0, len);
  }

  /// Set decay length
  ADSR_lite& decay(Tp len)
  {
    return setLen(1, len);
  }

  /// Set sustain level
  ADSR_lite& sustain(Tv val)
  {
    this->levels()[2] = val * this->levels()[1];
    return *this;
  }

  /// Set release length
  ADSR_lite& release(Tp len)
  {
    return setLen(2, len);
  }

  /// Set amplitude
  ADSR_lite& amp(Tv v)
  {
    this->maxLevel(v);
    return *this;
  }


  /// Get attack length
  Tp attack() const
  {
    return this->lengths()[0];
  }

  /// Get decay length
  Tp decay() const
  {
    return this->lengths()[1];
  }

  /// Get sustain level
  Tv sustain() const
  {
    return this->levels()[2] / this->levels()[1];
  }

  /// Get release length
  Tp release() const
  {
    return this->lengths()[2];
  }

  /// Get amplitude
  Tv amp() const
  {
    return this->levels()[1];
  }

protected:
  ADSR_lite& setLen(int i, Tp v)
  {
    this->lengths()[i] = v;
    return *this;
  }
};