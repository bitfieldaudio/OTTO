#pragma once
#include <cmath>

namespace top {

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
static inline float mix(float A, float B, float ratio = 0.5) {
  return A + (B - A) * ratio;
}
}
}

/** One frame of nTracks samples */
struct AudioFrame {
  float data[4];

  float& operator[](uint i) {
    return data[i];
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

  enum OverlapType {
    NONE = 0,
    CONTAINS,
    CONTAINED,
    CONTAINS_IN,
    CONTAINS_OUT,
  };

  OverlapType overlaps(const Section<T> &other) {
    if (contains(other)) return CONTAINS;
    if (other.contains(*this)) return CONTAINED;
    if (contains(other.in)) return CONTAINS_IN;
    if (contains(other.out)) return CONTAINS_OUT;
    return NONE;
  }

};
