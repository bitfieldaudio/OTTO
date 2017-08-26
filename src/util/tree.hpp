#pragma once

#include <vector>
#include <unordered_map>
// TODO: Use c++17 std::variant
// NOTE: Might be hard due to recursion
#include <mapbox/variant.hpp>
#include <memory>
#include <string>
#include <type_traits>

#include "util/type_traits.hpp"

namespace top1::tree {

  struct String {

    String(const std::string& s) : value (s) {}
    String(std::string&& s) : value(std::move(s)) {}
    std::string value;

    operator std::string() {return value;}
  };

  struct Int    {
    int value;
  };
  struct Float  {
    float value;
  };
  struct Bool   {
    bool value;
  };
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
  inline Node makeNode(T);

  // Default specializations

  template<>
  inline Node makeNode<float>(float f) {
    return Float{f};
  }

  template<>
  inline Node makeNode<int>(int i) {
    return Int{i};
  }

  template<>
  inline Node makeNode<bool>(bool b) {
    return Bool{b};
  }

  template<>
  inline Node makeNode<std::string>(std::string s) {
    return String{std::move(s)};
  }

  // TODO: Add more, e.g. vector, array, map, etc.

  // Specialize for things
  template<typename T>
  inline std::optional<T> readNode(Node);

  // Default specializations

  template<>
  inline std::optional<float> readNode<float>(Node n) {
    return match(n, [] (Float n) {return std::optional(n.value);},
                 [] (auto&&) {return std::optional<float>();});
  }

  template<>
  inline std::optional<int> readNode<int>(Node n) {
    return match(n, [] (Int n) {return std::optional(n.value);},
                 [] (auto&&) {return std::optional<int>();});
  }

  template<>
  inline std::optional<bool> readNode<bool>(Node n) {
    return match(n, [] (Bool n) {return std::optional(n.value);},
                 [] (auto&&) {return std::optional<bool>();});
  }

  template<>
  inline std::optional<std::string> readNode<std::string>(Node n) {
    return match(n, [] (String n) {return std::optional(n.value);},
                 [] (auto&&) {return std::optional<std::string>();});
  }

  // TODO: Add more, e.g. vector, array, map, etc.

} // top1::tree
