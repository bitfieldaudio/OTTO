#pragma once

#include <vector>
#include <string>
#include <memory>
#include <algorithm>
#include <cmath>

#include "util/type_traits.hpp"
#include "util/math.hpp"
#include "util/tree.hpp"

namespace top1::modules {

  namespace modes {

    // TODO: implement
    template<typename T>
    struct is_mode : public std::true_type {};

    template<typename T>
    constexpr inline bool is_mode_v = is_mode<T>::value;

    /// Has a member typedef `mode`, selected based on the type and the tag.
    /// Specialize this for each mode
    template<typename T, typename Tag, typename Enable = void>
    struct mode_for_tag {};

    /// Pass to mode_for_tag, to get the default mode for a type
    /// Specialize `mode_for_tag` with at least this for each new type
    struct default_tag {};

    /*
     * Modes:
     */

    /// Steps up/down by `step`, until `min`/`max` is reached, then stops
    struct sized_step {};

    template<typename T>
    struct sized_step_mode {

      sized_step_mode(T min = std::numeric_limits<T>::min(),
                      T max = std::numeric_limits<T>::max(),
                      T step = 1.0)
        : min (min), max (max), stepSize (step) {}

      void step(T& value, int steps) {
        value = std::clamp<T>(value + steps * stepSize, min, max);
      }

      void set(T& value, T v) {
        value = std::clamp(v, min, max);
      }

      T min, max, stepSize;
    };

    template<typename T>
    struct mode_for_tag<T, sized_step,
                        std::enable_if_t<top1::is_number_v<T>>> {
      using mode = sized_step_mode<T>;
    };


    /// Like `sized_step`, but wraps around when `max` or `min` reached
    struct wrap {}; // Tag

    template<typename T>
    struct wrap_mode {

      wrap_mode(T min, T max, T step = 1.0)
        : min (min), max (max), stepSize (step) {}

      void step(T& value, int steps) {
        value = min + math::modulo(value + steps * stepSize - min, max - min);
      }

      void set(T& value, T v) {
        value = std::clamp(v, min, max);
      }

      T min, max, stepSize;
    };

    /// Default mode for Bool
    struct toggle {};

    struct toggle_mode {
      void step(bool& value, int steps) {
        value = (steps & 0b1) xor value;
      }

      void set(bool& value, bool b) {
        value = b;
      }
    };

    // Specializations of mode_for_tag

    template<typename T>
    struct mode_for_tag<T, wrap,
                        std::enable_if_t<top1::is_number_v<T>>> {
      using mode = wrap_mode<T>;
    };

    template<typename T>
    struct mode_for_tag<T, default_tag,
                        std::enable_if_t<top1::is_number_v<T>>> {
      using mode = sized_step_mode<T>;
    };

    template<>
    struct mode_for_tag<bool, default_tag> {
      using mode = toggle_mode;
    };


    // Check modes
    static_assert(is_mode_v<sized_step_mode<float>>);
    static_assert(is_mode_v<sized_step_mode<int>>);
    static_assert(is_mode_v<sized_step_mode<double>>);
    static_assert(is_mode_v<sized_step_mode<uint>>);
    static_assert(is_mode_v<wrap_mode<float>>);
    static_assert(is_mode_v<wrap_mode<int>>);
    static_assert(is_mode_v<wrap_mode<double>>);
    static_assert(is_mode_v<wrap_mode<uint>>);
  }

  struct PropertyBase {
    std::string name;
    bool store;

    PropertyBase(std::string name, bool store = true)
      : name (name), store (store) {}

    virtual tree::Node makeNode() {
      return tree::Null();
    }
  };

  class Properties : public PropertyBase {
  public:

    // Raw pointers, because lifetime should be managed elsewhere
    using PropertyStorage = PropertyBase*;

    Properties()
      : PropertyBase{"", true} {}

    Properties(Properties* p, std::string n, bool s = true)
      : PropertyBase{n, s} {
      p->add(this);
    }

    void add(PropertyBase* ptr) {
      props.push_back(ptr);
    }

    void add(PropertyBase& ptr) {
      props.push_back(&ptr);
    }

    auto size() const { return props.size(); }
    auto begin() { return props.begin(); }
    auto begin() const { return props.begin(); }
    auto end() { return props.end(); }
    auto end() const { return props.end(); }
    PropertyBase& operator[](std::size_t idx) { return *props[idx]; }
    PropertyBase& operator[](std::size_t idx) const { return *props[idx]; }

    tree::Node makeNode() override {
      std::unordered_map<std::string, tree::Node> map;
      for (auto&& p : props) {
        if (p->store) {
          map[p->name] = p->makeNode();
        }
      }
      return tree::Map{std::move(map)};
    }

  protected:
    std::vector<PropertyStorage> props;
  };

    template<typename T, typename mode_tag = modes::default_tag,
           bool _store = true,
           typename mode_type = typename modes::mode_for_tag<T, mode_tag>::mode>
  struct Property final : public PropertyBase {
    using Value = T;
    using Mode = mode_type;

    Property(Properties* owner, const std::string& n, Value v = Value(), const Mode& mode = Mode())
      : PropertyBase {n, _store}, value(v), mode (mode) {
        owner->add(this);
      }

    Property(Property&) = delete;

    void step(int n = 1) {
      mode.step(value, n);
    }

    void set(const Value& v) {
      mode.set(value, v);
    }

    Property& operator=(const Value& v) {
      set(v);
      return *this;
    }

    operator Value() {
      return value;
    }

    tree::Node makeNode() override {
      return tree::makeNode(value);
    }

    Value value;
    Mode mode;
  };


  // Static tests
  static_assert(std::is_same<Property<float>::Mode,
                modes::sized_step_mode<float>>::value,
                "Default mode of Property<float> should be sized_step_mode");

  static_assert(std::is_same<Property<bool>::Mode, modes::toggle_mode>::value,
                "Default mode of Property<bool> should be toggle_mode");

} // top1::modules

namespace top1::tree {

  template<>
  Node makeNode<const modules::Properties&>(const modules::Properties& props) {
    std::unordered_map<std::string, tree::Node> map;
    for (auto&& p : props) {
      if (p->store) {
        map[p->name] = p->makeNode();
      }
    }
    return tree::Map{std::move(map)};
  }

} // top1::tree
