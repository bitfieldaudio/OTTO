#pragma once

#include "util/typedefs.hpp"

#include <type_traits>
#include <cmath>

#include "util/dyn-array.hpp"

namespace top1::audio {

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

  /*
   * A simple average, used to get a 1-dimensional graph of audio
   *
   */
  struct Graph {
    float sum = 0;
    int nsamples = 0;
    float average = 0;

    void add(float sample) {
      ++nsamples;
      sum += std::abs(sample);
      average = sum/nsamples;
    }
    void clear() {
      sum /= 16.0;
      nsamples /= 16;
      average = sum/nsamples;
    }

    float clip() const {
      return std::min<float>(average, 1);
    }

    operator float() {
      return average;
    }
  };

  template<class T = int>
  struct Section {
  public:
    T in = 0;
    T out = 0;

    Section<T>() {};
    Section<T>(T in, T out) : in (in), out (out) {}

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

    enum Overlap {
      None,
      Contains,
      Contained,
      ContainsIn,
      ContainsOut,
    };

    Overlap overlaps(const Section<T> &other) const {
      if (contains(other)) return Overlap::Contains;
      if (other.contains(*this)) return Overlap::Contained;
      if (contains(other.in)) return Overlap::ContainsIn;
      if (contains(other.out)) return Overlap::ContainsOut;
      return Overlap::None;
    }
  };

} // top1::audio
