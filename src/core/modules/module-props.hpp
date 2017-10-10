#pragma once

#include <vector>
#include <string>
#include <memory>
#include <algorithm>
#include <cmath>
#include <limits>
#include <type_traits>

#include <plog/Log.h>

#include "util/type_traits.hpp"
#include "util/math.hpp"
#include "util/tree.hpp"

namespace top1::modules {

  inline
  namespace mode {

    // TODO: implement
    template<typename T>
    struct is_mode : public std::true_type {};

    template<typename T>
    constexpr inline bool is_mode_v = is_mode<T>::value;

    /// Has a member typedef `mode`, selected based on the type and the tag.
    /// Specialize this for each mode
    template<typename T, typename Tag, typename Enable = void>
    struct mode_for_tag {};

    template<typename T, typename Tag, typename Enable = void>
    using mode_for_tag_m = typename mode_for_tag<T, Tag, Enable>::mode;

    /// Pass to mode_for_tag, to get the default mode for a type
    /// Specialize `mode_for_tag` with at least this for each new type
    struct def {};

    /*
     * Modes:
     */

    /// Steps up/down by `step`, until `min`/`max` is reached, then stops
    struct sized_step {};

    template<typename T>
    struct sized_step_mode {

      sized_step_mode(T min = std::numeric_limits<T>::min(),
        T max = std::numeric_limits<T>::max(),
        T step = static_cast<T>(1))
        : min (min), max (max), stepSize (step) {}

      void step(int steps) {
        set(*value + steps * stepSize);
      }

      void set(T v) {
        *value = std::clamp(v, min, max);
      }

      float normalize() const {
        return (*value - min)/ float(max);
      }

      T min, max, stepSize;
      T* value;
    };

    template<typename T>
    struct mode_for_tag<T, sized_step,
      std::enable_if_t<util::is_number_or_enum_v<T>>>
    {
      using mode = sized_step_mode<T>;
    };


    /// Like `sized_step`, but wraps around when `max` or `min` reached
    struct wrap {}; // Tag

    template<typename T>
    struct wrap_mode {

      wrap_mode(T min, T max, T step = static_cast<T>(1))
        : min (min), max (max), stepSize (step) {}

      void step(int steps) {
        *value = min + util::math::modulo(*value + steps * stepSize - min, max - min);
      }

      void set(T v) {
        *value = std::clamp(v, min, max);
      }

      float normalize() const {
        return (*value - min)/ float(max);
      }

      T min, max, stepSize;
      T* value;
    };

    /// Like `sized_step`, But steps exponentially
    struct exp {}; // Tag

    template<typename T>
    struct exp_mode {

      exp_mode(T min, T max, T step = static_cast<T>(1))
        : min (min), max (max), stepSize (step) {}

      void step(int steps) {
        set(*value * std::pow(stepSize, steps));
      }

      void set(T v) {
        *value = std::clamp(v, min, max);
      }

      float normalize() const {
        return (*value - min)/ float(max);
      }

      T min, max, stepSize;
      T* value;
    };

    /// Default mode for Bool
    struct toggle {};

    struct toggle_mode {
      void step(int steps) {
        *value = (steps & 0b1) xor *value;
      }

      void set(bool b) {
        *value = b;
      }

      bool* value;
    };

    /// Non-numeric
    struct plain_set {};

    template<typename T>
    struct plain_set_mode {
      void step(int steps) {};

      void set(const T& v) {
        *value = v;
      }

      T* value;
    };

    // Specializations of mode_for_tag

    template<typename T>
    struct mode_for_tag<T, wrap,
                        std::enable_if_t<util::is_number_or_enum_v<T>>> {
      using mode = wrap_mode<T>;
    };

    template<typename T>
    struct mode_for_tag<T, def,
                        std::enable_if_t<util::is_number_or_enum_v<T>>> {
      using mode = sized_step_mode<T>;
    };

    template<>
    struct mode_for_tag<bool, def> {
      using mode = toggle_mode;
    };

    template<>
    struct mode_for_tag<std::string, def> {
      using mode = plain_set_mode<std::string>;
    };

  } // mode

  struct PropertyBase {
    std::string name;
    bool store;
    struct FaustLink {
      float* ptr;
      enum Type {
        None = 0, Input, Output
      } type {None};
    } faustLink;

    PropertyBase(std::string name, bool store = true)
      : name (std::move(name)), store (store) {}

    /// Link this property to a faust variable.
    ///
    /// Should only be used from `FaustWrapper`,
    /// where it is handled automatically
    virtual void linkToFaust(float* ptr, bool isOutput) {
      faustLink = {ptr, isOutput ? FaustLink::Output : FaustLink::Input};
    }

    /// Update the linked faust variable.
    ///
    /// When the faust link uses this property as an input, call this from
    /// `set`, `step` etc.
    virtual void updateFaust() = 0;

    /// Reset to inital value
    virtual void reset() = 0;

    virtual util::tree::Node makeNode() {
      return util::tree::Null();
    }

    virtual void readNode(const util::tree::Node& n) {}
  };

  class Properties : public PropertyBase {
  public:

    // Raw pointers, because lifetime should be managed elsewhere
    using PropertyStorage = PropertyBase*;

    Properties()
      : PropertyBase{"", true} {}

    Properties(Properties* p, const std::string& n, bool s = true)
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

    /// Reset all properties
    void reset() override {
      std::for_each(begin(), end(), [] (auto&& p) {p->reset();});
    }

    void updateFaust() override {
      std::for_each(begin(), end(), [] (auto&& p) {p->updateFaust();});
    }

    util::tree::Node makeNode() override {
      std::unordered_map<std::string, util::tree::Node> map;
      for (auto&& p : props) {
        if (p->store) {
          map[p->name] = p->makeNode();
        }
      }
      return util::tree::Map{std::move(map)};
    }

    void readNode(const util::tree::Node& n) override {
      n.match([this] (const util::tree::Map& m) {
          for (auto&& pair : m.values) {
            auto p = std::find_if(begin(), end(),
                                  [&] (auto&& p) {return p->name == pair.first;});
            if (p != end()) {
              (*p)->readNode(pair.second);
            }
          }
        }, [] (auto&&) {
          LOGF << "Expected tree::Map";
        });
    }

  protected:
    std::vector<PropertyStorage> props;
  };

  template<typename T, typename mode_tag = mode::def,
           bool _store = true,
           typename mode_type = typename mode::mode_for_tag_m<T, mode_tag>>
  struct Property final : public PropertyBase {
    using Value = T;
    using Mode = mode_type;
    using Watcher = std::function<void(const Value&)>;

    Property(Properties* owner, const std::string& n, Value v = Value(), const Mode& _mode = Mode())
      : PropertyBase {n, _store}, value(v), init(v), mode (_mode) {
        mode.value = &value;
        owner->add(this);
      }

    Property(Property&) = delete;

    void step(int n = 1) {
      mode.step(n);
      updateFaust();
    }

    void set(const Value& v) {
      mode.set(v);
      updateFaust();
    }

    const Value& get() const {
      return value;
    }

    void reset() final {
      value = init;
      updateFaust();
    }

    util::tree::Node makeNode() final {
      return util::tree::makeNode(value);
    }

    void readNode(const util::tree::Node& n) final {
      value = util::tree::readNode<Value>(n).value_or(value);
      updateFaust();
    }

    void updateFaust() final {
      if (faustLink.type == FaustLink::Input) {
        if constexpr (std::is_convertible_v<Value, float>) {
            *faustLink.ptr = (float) value;
          } else {
          LOGF << "Attempt to update a faust link with an incompatible type";
        }
      } else if (faustLink.type == FaustLink::Input) {
        if constexpr (std::is_convertible_v<float, Value>) {
            set((Value) *faustLink.ptr);
          } else {
          LOGF << "Attempt to update a faust link with an incompatible type";
        }
      }
    }

    Property& operator=(const Value& v) {
      set(v);
      return *this;
    }

    operator Value&() {
      return value;
    }

    operator const Value&() const {
      return value;
    }

  private:
    Value value;
  public:
    Value init;
    Mode mode;
  };


  // Static tests
  static_assert(std::is_same_v<Property<float>::Mode,
                mode::sized_step_mode<float>>,
                "Default mode of Property<float> should be sized_step_mode");

  static_assert(std::is_same_v<Property<bool>::Mode, mode::toggle_mode>,
                "Default mode of Property<bool> should be toggle_mode");

} // top1::modules
