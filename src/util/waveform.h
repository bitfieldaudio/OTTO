#pragma once

#include <cstdlib>
#include <vector>

#include "typedefs.h"

class Waveform {
public:

  using storageType = std::vector<float>;
  using iterator = storageType::iterator;
  using const_iterator = storageType::const_iterator;

  const float ratio; // audioframes pr point
  const float scale; // audio will be multiplied by this.

  Waveform(float ratio, float scale);

  void addFrame(float);
  void addPoint(float);

  std::size_t size() const;
  std::size_t timeSpan() const;

  float &operator[](std::size_t);
  const float& operator[](std::size_t) const;

  iterator begin();
  iterator end();
  const_iterator begin() const;
  const_iterator end() const;
  const_iterator cbegin() const;
  const_iterator cend() const;

private:
  std::vector<float> _data;

  struct Average {
    float sum;
    uint count;

    float average() const {
      if (count == 0) return 0;
      return sum/float(count);
    }

    void add(float f) {
      sum += f;
      ++count;
    }

    void clear() {
      sum = 0;
      count = 0;
    }
  } _current;
};

/************************************************************/
/* Waveform Implementation                                  */
/************************************************************/

inline Waveform::Waveform(float ratio, float scale) :
  ratio (ratio),
  scale (scale) {}

inline void Waveform::addFrame(float f) {
  _current.add(f);
  if (_current.count/ratio >= 0) {
    addPoint(_current.average());
    _current.clear();
  }
}

inline void Waveform::addPoint(float f) {
  _data.push_back(f * scale);
}

inline std::size_t Waveform::size() const {
  return _data.size();
}
inline std::size_t Waveform::timeSpan() const {
  return _data.size() * ratio;
}

inline float &Waveform::operator[](std::size_t idx) {
  return _data[idx];
}

inline const float &Waveform::operator[](std::size_t idx) const {
  return _data[idx];
}

inline Waveform::iterator Waveform::begin() {
  return _data.begin();
}
inline Waveform::iterator Waveform::end() {
  return _data.end();
}
inline Waveform::const_iterator Waveform::begin() const {
  return _data.begin();
}
inline Waveform::const_iterator Waveform::end() const {
  return _data.end();
}
inline Waveform::const_iterator Waveform::cbegin() const {
  return _data.cbegin();
}
inline Waveform::const_iterator Waveform::cend() const {
  return _data.cend();
}
