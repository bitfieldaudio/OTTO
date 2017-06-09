#pragma once

#include <functional>
#include <vector>
#include <unordered_map>
#include <mapbox/variant.hpp>
#include <memory>

namespace top1 {
namespace tree {

struct String { std::string value; };
struct Int { int value; };
struct Float { float value; };
struct Bool   { bool value; };
struct Null   { };

// Forward declarations only
struct Array;
struct Map;

using Node = mapbox::util::variant<
    Float,
    String,
    Int,
    Bool,
    Null,
    mapbox::util::recursive_wrapper<Array>,
    mapbox::util::recursive_wrapper<Map>>;

struct Array {
  std::vector<Node> values;

  auto &operator[](uint i) { return values[i];}
  auto begin() { return values.begin(); }
  auto end() { return values.end(); }
};

struct Map {
  std::unordered_map<std::string, Node> values;

  auto &operator[](std::string k) { return values[k];}
  auto begin() { return values.begin(); }
  auto end() { return values.end(); }
};

}
}
