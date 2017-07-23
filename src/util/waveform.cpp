#include "waveform.h"

#include <cmath>

/************************************************************/
/* Waveform Implementation                                  */
/************************************************************/

Waveform::Waveform(float ratio, float scale) :
  ratio (ratio),
  scale (scale) {}

void Waveform::addFrame(float f) {
  _current.add(f);
  if (_current.count/ratio >= 1) {
    addPoint(_current.average());
    _current.clear();
  }
}

void Waveform::addPoint(float f) {
  _data.push_back(std::abs(f * scale));
  _max = std::max(_max, f);
}

void Waveform::clear() {
  _data.clear();
}

std::size_t Waveform::size() const {
  return _data.size();
}
std::size_t Waveform::timeSpan() const {
  return _data.size() * ratio;
}

float Waveform::max() const {
  return _max;
}

float &Waveform::operator[](std::size_t idx) {
  return _data[idx];
}

const float &Waveform::operator[](std::size_t idx) const {
  return _data[idx];
}

Waveform::iterator Waveform::begin() {
  return _data.begin();
}
Waveform::iterator Waveform::end() {
  return _data.end();
}
Waveform::const_iterator Waveform::begin() const {
  return _data.begin();
}
Waveform::const_iterator Waveform::end() const {
  return _data.end();
}
Waveform::const_iterator Waveform::cbegin() const {
  return _data.cbegin();
}
Waveform::const_iterator Waveform::cend() const {
  return _data.cend();
}
