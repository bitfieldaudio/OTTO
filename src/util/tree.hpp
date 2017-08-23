#pragma once

#include <vector>
#include <unordered_map>
// TODO: Use c++17 std::variant
// NOTE: Might be hard due to recursion
#include <mapbox/variant.hpp>
#include <memory>
#include <string>
#include <type_traits>

namespace top1::tree {

  struct String { std::string value; };
  struct Int    { int value; };
  struct Float  { float value; };
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

  // Specialize for things
  template<typename T>
  inline tree::Node makeNode(T);

  // Default specializations

  template<>
  inline tree::Node makeNode<float>(float f) {
    return Float{f};
  } 

  template<>
  inline tree::Node makeNode<int>(int i) {
    return Int{i};
  } 

  template<>
  inline tree::Node makeNode<bool>(bool b) {
    return Bool{b};
  }

  template<>
  inline tree::Node makeNode<const std::string&>(const std::string& s) {
    return String{s};
  }

  // TODO: Add more, e.g. vector, array, map, etc.

} // top1::tree
