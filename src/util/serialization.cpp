#include <cstdlib>
#include <cinttypes>
#include <plog/Log.h>

#include "serialization.h"

template<>
std::vector<char> serialize<float>(float f) {
  uint32_t ui = *reinterpret_cast<uint32_t *>(&f);
  std::vector<char> xs;
  xs.push_back((ui) & 0xFF);
  xs.push_back((ui << 8) & 0xFF);
  xs.push_back((ui << 16) & 0xFF);
  xs.push_back((ui << 24) & 0xFF);
  return xs;
}

template<>
float deserialize<float>(std::vector<char> data) {
  if (data.size() != 4) {
    LOGE << "Wrong number of bytes for float";
  }
  uint32_t ui = 0;
  ui |= data[0];
  ui |= data[1] << 8;
  ui |= data[2] << 16;
  ui |= data[3] << 24;
  return *reinterpret_cast<float*>(&ui);
}
