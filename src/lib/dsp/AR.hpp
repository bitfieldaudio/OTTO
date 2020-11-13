#pragma once

#include <Gamma/Envelope.h>

/// AD (Attack, Release) envelope

template<class Tv = gam::real, class Tp = gam::real, class Td = gam::DomainObserver>
class AR : public gam::Env<2, Tv, Tp, Td> {
public:
  using gam::Env<2, Tv, Tp, Td>::release;

  /// \param[in] att	Attack length
  /// \param[in] rel	Release length
  /// \param[in] amp	Amplitude
  /// \param[in] crv	Curvature of all segments
  AR(Tp att = Tp(0.01), Tp rel = Tp(0.1), Tv amp = Tv(1.0), Tp crv = Tp(0))
  {
    this->sustainPoint(1);
    this->levels(0, amp, 0);
    attack(att).release(rel);
    this->curve(crv);
  }

  /// Set attack length
  AR& attack(Tp len)
  {
    return setLen(0, len);
  }

  /// Set release length
  AR& release(Tp len)
  {
    return setLen(1, len);
  }

  /// Set amplitude
  AR& amp(Tv v)
  {
    this->maxLevel(v);
    return *this;
  }


  /// Get attack length
  Tp attack() const
  {
    return this->lengths()[0];
  }

  /// Get release length
  Tp release() const
  {
    return this->lengths()[1];
  }

  /// Get amplitude
  Tv amp() const
  {
    return this->levels()[1];
  }

protected:
  AR& setLen(int i, Tp v)
  {
    this->lengths()[i] = v;
    return *this;
  }
};
