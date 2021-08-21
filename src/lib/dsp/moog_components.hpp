#pragma once

#include <cmath>
#include <numbers>

#include <Gamma/Domain.h>
#include <Gamma/scl.h>

#include "lib/dsp/fmoperator.hpp"
#include "lib/dsp/triangle_wave.hpp"

namespace otto::dsp {
  // Based on an implementation by Aaron Krajeski (Public Domain)
  template<class Tv = float, class Tp = float, class Td = gam::DomainObserver>
  struct MoogLadder : public Td {
    MoogLadder(Tp frq = Tp(1000), Tp res = Tp(0.2))
    {
      onDomainChange(1);
      set(frq, res);
    }

    void onDomainChange(double r)
    {
      // setCutoff(mFreq);
    }

    Tv operator()(Tv in)
    {
      float x = in - resonance * stage[3];

      // Four cascaded one-pole filters (bilinear transform)
      stage[0] = x * p + delay[0] * p - k * stage[0];
      stage[1] = stage[0] * p + delay[1] * p - k * stage[1];
      stage[2] = stage[1] * p + delay[2] * p - k * stage[2];
      stage[3] = stage[2] * p + delay[3] * p - k * stage[3];

      // Clipping band-limited sigmoid
      stage[3] -= (stage[3] * stage[3] * stage[3]) / 6.0;

      delay[0] = x;
      delay[1] = stage[0];
      delay[2] = stage[1];
      delay[3] = stage[2];

      return stage[3];
    }
    void setResonance(float r)
    {
      res = r;
      resonance = r * (t2 + 6.0 * t1) / (t2 - 6.0 * t1);
    }

    void setCutoff(float c)
    {
      cutoff = 2.0 * c / Td::spu();

      p = cutoff * (1.8 - 0.8 * cutoff);
      k = 2.0 * gam::scl::mapSinSS(cutoff) - 1.0; // mapSinSS(x) = sin(x * pi/2)
      t1 = (1.0 - p) * 1.386249;
      t2 = 12.0 + t1 * t1;

      setResonance(res);
    }



    void set(Tp frq, Tp res)
    {
      setCutoff(frq);
      setResonance(res);
    }

  private:
    std::array<double, 5> state = {0};
    std::array<double, 5> delay = {0};
    Tv wc = 1;          // The angular frequency of the cutoff.
    double g = 1;       // A derived parameter for the cutoff frequency
    double gRes = 1;    // A similar derived parameter for resonance.
    double gComp = 1.0; // Compensation factor.
    double drive = 2.0; // A parameter that controls intensity of nonlinearities.

    Tp mFreq = 1000;
    Tp mRes;

    Tp res;       // Underlying resonance value [0, 1]
    Tp resonance; // Derived quantity
    Tp cutoff;
    double stage[4];
    double p;
    double k;
    double t1;
    double t2;
  };


  // Based on https://asp-eurasipjournals.springeropen.com/track/pdf/10.1155/2011/785103.pdf
  // A phase-distortion implementation of the classic Moog Saw wave
  struct MoogSawOffset {
    MoogSawOffset(float frq = 440) : phaser_(gam::AccumPhase<>(frq, 0, 1)) {}

    float triangular(const float t) const
    {
      // This requires that t is always [0, 1]
      if (t < P) return t / P;
      return (1 - t) / (1 - P);
    }

    /// Generate next sample
    float operator()() noexcept
    {
      phaser_.nextPhase();
      return (std::numbers::pi - 2 * std::numbers::pi * P) * triangular(phaser_.phase());
    };

    void freq(float frq)
    {
      P = 0.9924f - 0.00002151f * frq;
      phaser_.freq(frq);
    }

  private:
    gam::AccumPhase<> phaser_;
    float P = 0.5;
  };

  struct MoogSawOffset2 {
    /// Generate next sample
    float operator()() noexcept
    {
      return (std::numbers::pi - 2 * std::numbers::pi * P) * (1 + tri_()) * 0.5;
    };

    void freq(float frq)
    {
      P = 0.9924f - 0.00002151f * frq;
      tri_.freq(frq);
      tri_.setDutyCycle(P);
    }

  private:
    dsp::TrianglePW<> tri_;
    float P = 0.5;
  };

  template<class Tv = gam::real, class Tp = gam::real>
  struct MoogSawEQ {
    MoogSawEQ(Tp frq = 440)
    {
      freq(frq);
    }

    void freq(Tp frq)
    {
      Tv frq2 = frq * frq;
      g = 0.54 + 4.473e-5;
      a = 0.6398 - 2.417e-4 * frq + 1.335e-8 * frq2;
      b = 0.3894 - 3.102e-4 * frq + 2.217e-8 * frq2;
    }

    Tv operator()(Tv in)
    {
      inPrev = in;
      return outPrev = g * (in - b * inPrev) + a * outPrev;
    }

  private:
    Tv g, a, b = 0;
    Tv inPrev = 0;
    Tv outPrev = 0;
  };

  template<class Tv = float, class Tp = float, class Td = gam::DomainObserver>
  struct MoogSaw : public Td {
    MoogSaw(Tp frq = Tp(440))
    {
      onDomainChange(1);
      freq(frq);
    }
    void onDomainChange(double r)
    {
      // setCutoff(mFreq);
    }

    void freq(Tp frq)
    {
      saw.freq(frq);
      filter.freq(frq);
    }
    Tv phase()
    {
      return saw.phase();
    }

    Tv operator()()
    {
      return filter(saw());
    }

  private:
    gam::Saw<> saw;
    MoogSawEQ<> filter;
  };

  /*
  template<class Tv = float, class Tp = float, class Td = gam::DomainObserver>
  struct MoogSaw : public Td {
    MoogSaw(Tp frq = Tp(440))
    {
      onDomainChange(1);
      freq(frq);
    }
    void onDomainChange(double r)
    {
      // setCutoff(mFreq);
    }

    void freq(Tp frq)
    {
      carrier.freq(frq);
      mod_saw.freq(frq);
    }
    Tv operator()()
    {
      return carrier(mod_saw());
    }

  private:
    FMSine carrier;
    MoogSawOffset2 mod_saw;
    float P;
  };
  */
} // namespace otto::dsp
