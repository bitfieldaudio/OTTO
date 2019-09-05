#if 0
#pragma once

#include <Gamma/gen.h>
#include <Gamma/ipl.h>
#include <Gamma/scl.h>
#include <Gamma/Domain.h>
#include <Gamma/Strategy.h>
#include <Gamma/Oscillator.h>

/// Oscillator with variable waveforms, using the same accumulator
template <class Tv=gam::real, class Td=gam::DomainObserver>
class VariableOsc : public gam::Impulse<Tv,Td> {
public:
  /// \param[in]	frq		Frequency
  /// \param[in]	phs		Phase in [0, 1)
  VariableOsc(Tv frq=440, Tv phs=0) : gam::Impulse<Tv,Td>(frq, phs){}

  /// Generate next sample
  // Sine wave
  Tv sine(){ return gam::scl::sinP9(this->nextPhase()); }
  // Square wave and saw wave are implemented in the Buzz class.
  // Use square() and saw() respectively.
};

template <class Tv=gam::real, class Td=gam::DomainObserver, int N=3>
class IMultiOsc {

    IMultiOsc() {}

    virtual Tv operator()() = 0;

private:
    std::array<VariableOsc<>, 3> osc;
};

template <class Tv=gam::real, class Td=gam::DomainObserver>
class SineSawSquare : IMultiOsc<Tv, Td, 3> {

    Tv operator()(){ return this->osc[0].sine() + this->osc[1].saw() + this->osc[2].square()}
};

template <class Tv=gam::real, class Td=gam::DomainObserver>
class SawSawSquare : IMultiOsc<Tv, Td, 3> {

    Tv operator()(){ return this->osc[0].saw() + this->osc[1].saw() + this->osc[2].square()}
};
#endif
