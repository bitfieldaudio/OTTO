#pragma once
#include <cstdlib>
#include <cmath>
#include <functional>
#include <algorithm>
#include <string>

#include "util/dyn-array.h"
#include "util/sndfile.h"

namespace top1 {

template<typename T>
inline bool between(T min, T max, T el) {
  return (el <= max && el >= min);
}

template<typename T>
inline T withBounds(T min, T max, T el) {
  if (el < min) {
    return min;
  }
  if (el > max) {
    return max;
  }
  return el;
}

template<typename T>
inline T clamp(T el, T min, T max) {
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

}

using AudioFrame = top1::SndFile<4>::AudioFrame;


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

