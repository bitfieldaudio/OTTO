#pragma once
#include <cstdlib>
#include <cmath>
#include <functional>
#include <algorithm>
#include <string>

#include "util/dyn-array.h"
#include "util/sndfile.h"

namespace top1 {

inline bool between(float min, float max, float el) {
  return (el <= max && el >= min);
}

inline float withBounds(float min, float max, float el) {
  if (el < min) {
    return min;
  }
  if (el > max) {
    return max;
  }
  return el;
}

inline float round(float f, int places) {
  int i = std::pow(10, places);
  return std::round(f * i)/i;
}

namespace audio {

/**
 * Mixes two signals.
 * @param A Signal A
 * @param B Signal B
 * @param ratio B:A, amount of B to mix into signal A.
 */
inline float mix(float A, float B, float ratio = 0.5) {
  return A + (B - A) * ratio;
}
}

struct Track {
  uint idx;
  uint name() const { return idx + 1; }
  std::string str() const { return std::to_string(name()); }

  Track() {};

  bool operator == (Track &other) const { return idx == other.idx; }
  bool operator != (Track &other) const { return idx != other.idx; }

  static void foreach(std::function<void(Track)> f) {
    for (uint i = 0; i < 4; i++) f(newIdx(i));
  }

  static Track newIdx(uint idx) { return Track(idx); }
  static Track newName(uint name) { return Track(name-1); }
private:
  Track(uint idx) : idx (idx) {}
};

struct AudioAverage {
  float sum = 0;
  uint nsamples = 0;
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

}

using AudioFrame = top1::SndFile<4>::AudioFrame;

namespace detail {

// to avoid circular deps
void registerAudioBufferResize(std::function<void(uint)>);

}

template<typename T>
class AudioBuffer : public top1::DynArray<T> {
public:

  using typename top1::DynArray<T>::value_type;
  using typename top1::DynArray<T>::size_type;
  using typename top1::DynArray<T>::difference_type;
  using typename top1::DynArray<T>::reference;
  using typename top1::DynArray<T>::const_reference;
  using typename top1::DynArray<T>::pointer;
  using typename top1::DynArray<T>::iterator;
  using typename top1::DynArray<T>::const_iterator;
  using typename top1::DynArray<T>::reverse_iterator;
  using typename top1::DynArray<T>::const_reverse_iterator;

  AudioBuffer(size_type sizeFactor = 1)
    : top1::DynArray<T>(0),
    sFactor (sizeFactor) {
    detail::registerAudioBufferResize([this] (uint newSize) {
       this->resize(newSize * sFactor);
     });
  }

  using top1::DynArray<T>::operator[];

private:
  size_type sFactor;
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

  enum OverlapType {
    NONE = 0,
    CONTAINS,
    CONTAINED,
    CONTAINS_IN,
    CONTAINS_OUT,
  };

  OverlapType overlaps(const Section<T> &other) const {
    if (contains(other)) return CONTAINS;
    if (other.contains(*this)) return CONTAINED;
    if (contains(other.in)) return CONTAINS_IN;
    if (contains(other.out)) return CONTAINS_OUT;
    return NONE;
  }

};

