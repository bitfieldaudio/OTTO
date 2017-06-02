#pragma once

#include <vector>
#include <iterator>

namespace top1 {

typedef char byte;
typedef uint fourCC;

template<class T>
std::vector<byte> serialize(T);

template<class T>
T deserialize(std::vector<byte>);

template<class T>
void serialize(T, std::vector<byte>::iterator &it);

template<class T>
T deserialize(std::vector<byte>::iterator &it);

// Implementations

template<class T>
std::vector<char> serialize(T t) {
  std::vector<char> xs;
  serialize(t, xs.end());
  return xs;
}

template<class T>
T deserialize(std::vector<byte> data) {
  return deserialize<T>(data.begin());
}

template<>
void serialize<float>(float f, std::vector<byte>::iterator &it) {
  uint32_t ui = *reinterpret_cast<uint32_t *>(&f);
  *it = ((ui      ) & 0xFF); it++;
  *it = ((ui << 8 ) & 0xFF); it++;
  *it = ((ui << 16) & 0xFF); it++;
  *it = ((ui << 24) & 0xFF); it++;
}

template<>
float deserialize<float>(std::vector<char>::iterator &it) {
  uint32_t ui = 0;
  ui |= *it++;
  ui |= *it++ << 8;
  ui |= *it++ << 16;
  ui |= *it++ << 24;
  return *reinterpret_cast<float*>(&ui);
}

template<>
void serialize<uint32_t>(uint32_t ui, std::vector<byte>::iterator &it) {
  *it++ = ((ui) & 0xFF);
  *it++ = ((ui << 8) & 0xFF);
  *it++ = ((ui << 16) & 0xFF);
  *it++ = ((ui << 24) & 0xFF);
}

template<>
uint32_t deserialize<uint32_t>(std::vector<char>::iterator &it) {
  uint32_t ui = 0;
  ui |= *it++;
  ui |= *it++ << 8;
  ui |= *it++ << 16;
  ui |= *it++ << 24;
  return ui;
}

template<>
void serialize<std::string>(std::string s, std::vector<byte>::iterator &it) {
  serialize<uint>(s.size(), it);
  std::copy(s.begin(), s.end(), it);
  it += s.size();
}

template<>
std::string deserialize<std::string>(std::vector<char>::iterator &it) {
  uint size = deserialize<uint>(it);
  std::string s = std::string(it, it + size);
  it += size;
  return s;
}
}
