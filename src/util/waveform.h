#pragma once

#include <cstdlib>
#include <cmath>
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
  void clear();

  std::size_t size() const;
  std::size_t timeSpan() const;
  float max() const;         // Maximum value

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
  float _max;

  struct Average {
    float sum;
    uint count;

    float average() const {
      if (count == 0) return 0;
      return sum/float(count);
    }

    void add(float f) {
      sum += std::abs(f);
      ++count;
    }

    void clear() {
      sum = 0;
      count = 0;
    }
  } _current;
};
