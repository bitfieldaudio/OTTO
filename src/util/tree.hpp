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

    operator std::string() const {return value;}
    bool operator==(const String& lhs) const {return value == lhs.value;}
    bool operator!=(const String& lhs) const {return value != lhs.value;}
    bool operator<(const String& lhs) const {return value < lhs.value;}
    bool operator>(const String& lhs) const {return value > lhs.value;}
    bool operator<=(const String& lhs) const {return value <= lhs.value;}
    bool operator>=(const String& lhs) const {return value >= lhs.value;}
  };

  struct Int    {
    int value;
    operator int() const {return value;}
    bool operator==(const Int& lhs) const {return value == lhs.value;}
    bool operator!=(const Int& lhs) const {return value != lhs.value;}
    bool operator< (const Int& lhs) const {return value < lhs.value;}
    bool operator> (const Int& lhs) const {return value > lhs.value;}
    bool operator<=(const Int& lhs) const {return value <= lhs.value;}
    bool operator>=(const Int& lhs) const {return value >= lhs.value;}
  };
  struct Float  {
    float value;
    operator float() const {return value;}
    bool operator==(const Float& lhs) const {return value == lhs.value;}
    bool operator!=(const Float& lhs) const {return value != lhs.value;}
    bool operator< (const Float& lhs) const {return value < lhs.value;}
    bool operator> (const Float& lhs) const {return value > lhs.value;}
    bool operator<=(const Float& lhs) const {return value <= lhs.value;}
    bool operator>=(const Float& lhs) const {return value >= lhs.value;}
  };
  struct Bool   {
    bool value;
    operator bool() const {return value;}
    bool operator==(const Bool& lhs) const {return value == lhs.value;}
    bool operator!=(const Bool& lhs) const {return value != lhs.value;}
    bool operator< (const Bool& lhs) const {return value < lhs.value;}
    bool operator> (const Bool& lhs) const {return value > lhs.value;}
    bool operator<=(const Bool& lhs) const {return value <= lhs.value;}
    bool operator>=(const Bool& lhs) const {return value >= lhs.value;}
  };
  struct Null   {
    bool operator==(const Null& lhs) const {return true;}
    bool operator!=(const Null& lhs) const {return false;}
    bool operator< (const Null& lhs) const {return false;}
    bool operator> (const Null& lhs) const {return false;}
    bool operator<=(const Null& lhs) const {return false;}
    bool operator>=(const Null& lhs) const {return false;}
  };

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

    auto &operator[](int i) { return values[i];}
    auto begin() { return values.begin(); }
    auto end() { return values.end(); }
    auto begin() const { return values.begin(); }
    auto end() const { return values.end(); }
    bool operator==(const Array& lhs) const {
      return std::is_permutation(begin(), end(), lhs.begin());
    }
    bool operator!=(const Array& lhs) const {return !(*this == lhs);}
  };

  struct Map {
    std::unordered_map<std::string, Node> values;
    auto& operator[](std::string k) { return values[k];}
    auto begin() { return values.begin(); }
    auto end() { return values.end(); }
    auto begin() const { return values.begin(); }
    auto end() const { return values.end(); }

    bool operator==(const Map& lhs) const {
      return std::is_permutation(begin(), end(), lhs.begin());
    }
    bool operator!=(const Map& lhs) const {return !(*this == lhs);}
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
    return n.match([] (Float n) {return std::optional(n.value);},
                 [] (auto&&) {return std::optional<float>();});
  }

  template<>
  inline std::optional<int> readNode<int>(Node n) {
    return n.match([] (Int n) {return std::optional(n.value);},
                 [] (auto&&) {return std::optional<int>();});
  }

  template<>
  inline std::optional<bool> readNode<bool>(Node n) {
    return n.match([] (Bool n) {return std::optional(n.value);},
                 [] (auto&&) {return std::optional<bool>();});
  }

  template<>
  inline std::optional<std::string> readNode<std::string>(Node n) {
    return n.match([] (String n) {return std::optional(n.value);},
                 [] (auto&&) {return std::optional<std::string>();});
  }

  // TODO: Add more, e.g. vector, array, map, etc.

} // top1::tree
