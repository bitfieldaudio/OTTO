#include <cstdlib>
#include <cinttypes>
#include <plog/Log.h>

#include "serialization.h"

namespace top1 {

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

template<>
std::vector<char> serialize<uint32_t>(uint32_t ui) {
  std::vector<char> xs;
  xs.push_back((ui) & 0xFF);
  xs.push_back((ui << 8) & 0xFF);
  xs.push_back((ui << 16) & 0xFF);
  xs.push_back((ui << 24) & 0xFF);
  return xs;
}

template<>
uint32_t deserialize<uint32_t>(std::vector<char> data) {
  if (data.size() != 4) {
    LOGE << "Wrong number of bytes for uint32";
  }
  uint32_t ui = 0;
  ui |= data[0];
  ui |= data[1] << 8;
  ui |= data[2] << 16;
  ui |= data[3] << 24;
  return ui;
}

template<>
std::vector<char> serialize<std::string>(std::string s) {
  return std::vector<char>(s.begin(), s.end());
}

template<>
std::string deserialize<std::string>(std::vector<char> data) {
  return std::string(data.begin(), data.end());
}

}
