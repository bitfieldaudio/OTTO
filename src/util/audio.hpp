#pragma once

#include <type_traits>
#include <cmath>
#include <gsl/span>

#include "util/dyn-array.hpp"
#include "util/iterator.hpp"

namespace otto::util::audio {

  /*
   * Mixes two signals, and normalizes the result.
   * Simple weighted average
   * @A Signal A
   * @B Signal B
   * @ratio B:A, amount of B to mix into signal A.
   */
  inline float mix(float A, float B, float ratio = 0.5) {
    return A + (B - A) * ratio;
  }

  /*
   * A frame of audio, with nChannels channels
   */
  template<int nChannels = 4, typename SampleType = float>
  using AudioFrame = std::array<SampleType, nChannels>;

  template<typename Rng1, typename Rng2>
  void add_all(Rng1&& r1, Rng2&& r2)
  {
    for (auto&& [r1, r2] : util::zip(r1, r2)) {
      r1 += r2;
    }
  }

  /*
   * A simple average, used to get a 1-dimensional graph of audio
   */
  struct Graph {
    float sum = 0;
    int nsamples = 0;
    float average = 0;

    /// Add a sample to the graph
    void add(float sample) {
      ++nsamples;
      sum += std::abs(sample);
      average = nsamples == 0 ? 0 : sum/nsamples;
    }

    /// Clear the values, starting a new average
    void clear() {
      int scale = 64;
      sum /= scale;
      nsamples /= scale;
      average = nsamples == 0 ? 0 : sum/nsamples;
    }

    /// get `average` clamped to `[0, 1]`
    float clip() const {
      return std::clamp(average, 0.f, 1.f);
    }

    operator float() const {
      return average;
    }
  };

  /// Agregate of an in and an out point, providing operations to compare and
  /// mutate one dimensional sections.
  ///
  /// Useful especially for marking sections on the tape
  template<class T = int>
  struct Section {
    T in = 0;
    T out = 0;

    operator bool() const {
      return in != out;
    }

    T size() const {
      return out - in;
    }

    bool contains(const T element) const {
      return (element >= in && element <= out);
    }

    bool contains(const Section<T> &other) const {
      return (contains(other.in) && contains(other.out));
    }

    bool operator==(Section o) const {
      return in == o.in && out == o.out;
    }

    bool operator!=(Section o) const {
      return in != o.in || out != o.out;
    }

    enum Overlap {
      None        = 0b0000,
      Equal       = 0b0001,
      Contained   = 0b0010,
      ContainsIn  = 0b0100,
      ContainsOut = 0b1000,
      Contains    = ContainsIn | ContainsOut,
    };

    Overlap overlaps(const Section<T> &other) const {
      if (*this == other) return Overlap::Equal;
      if (contains(other)) return Overlap::Contains;
      if (other.contains(*this)) return Overlap::Contained;
      if (contains(other.in)) return Overlap::ContainsIn;
      if (contains(other.out)) return Overlap::ContainsOut;
      return Overlap::None;
    }

    /// Add `o` to this section
    ///
    /// Will, if needed, extend this section to span over both this and `o`
    ///
    /// If `o` has `size < 0`, no modifications are made
    Section& operator+=(Section o) {
      in = std::min(in, o.in);
      out = std::max(out, o.out);
      return *this;
    }

    /// Add `o` to a copy of this section
    ///
    /// see <operator+=> for details
    Section operator+(Section o) const {
      Section res = *this;
      res += o;
      return res;
    }

    /// Subtract `o` from this section.
    ///
    /// If the result cannot be expressed as a single section, no modifications
    /// are made.
    ///
    ///  - If this contains `o`, no modifications are made.
    ///  - If this is contained by or equal to `o`, it will be turned into a
    ///    unspecified, zero-size section.
    ///  - If the two sections partially overlap, the overlapping part will be
    ///    removed.
    ///
    /// As such, it is guarantied that every part in this, but not in `o` will
    /// be preserved. It is however not guarrantied that all of `o` will be
    /// removed.
    Section& operator-=(Section o) {
      switch (overlaps(o)) {
      case ContainsIn:
        out = o.in; break;
      case ContainsOut:
        in = o.out; break;
      case Contained:
      case Equal:
        in = out; break;
      default:
        break;
      }
      return *this;
    }

    /// Subtract `o` from a copy of this.
    ///
    /// See <operator-=> for details
    Section operator-(Section o) const {
      Section res = *this;
      res -= o;
      return res;
    }
  };

} // otto::audio
