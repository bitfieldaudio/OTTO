#pragma once

#include <vector>
#include <map>
#include <string>
#include <memory>
#include <functional>
#include <cstdlib>
#include <type_traits>
#include <limits>
#include <plog/Log.h>

#include "util/tree.hpp"
#include "util/poly-ptr.hpp"
#include "core/audio/processor.hpp"

namespace top1::modules {

  template<class T> struct is_valid_field_type       : std::false_type {};
  template<> struct is_valid_field_type<float>       : std::true_type  {};
  template<> struct is_valid_field_type<bool>        : std::true_type  {};
  template<> struct is_valid_field_type<int>         : std::true_type  {};
  template<> struct is_valid_field_type<std::string> : std::true_type  {};

  class Field {
  public:
    bool preserve = true;

    Field(bool preserve = true) :
      preserve(preserve) {}

    virtual void reset() {}
    virtual void changed() {}

    virtual top1::tree::Node serialize() { return top1::tree::Null(); };

    virtual void deserialize(top1::tree::Node) {}
  };

  template<class T, typename = std::enable_if_t<is_valid_field_type<T>::value>>
  class TypedField : public Field {
  protected:
    T init;
    T value;
    std::vector<std::function<void(TypedField<T>*)>> onChange;
  public:

    using Field::Field;

    TypedField() : Field() {};

    TypedField(bool preserve, T init) : Field(preserve), init (init) {
      reset();
    }

    void reset() override {
      set(init);
    }
    void changed() override {
      for (auto h : onChange) {
        h(this);
      }
    }

    void addChangeHandler(std::function<void(TypedField<T>*)> f) {
      onChange.push_back(f);
    }

    virtual T set(T newVal) {
      value = newVal;
      changed();
      return value;
    }
    virtual T get() const {
      return value;
    }

    virtual void setRaw(T newVal) {
      value = newVal;
    }

    T operator = (T newVal) { return set(newVal); };
    T operator()() const { return get(); }
    operator T() const { return get(); }
  };


  // Forward Declarations
  class Data;

  template<class T> class Opt;

  template<>
  class Opt<float> : public TypedField<float> {
  public:
    float min;
    float max;
    float step;

    Opt() {};
    Opt(Data *data,
        std::string name,
        float init = 0,
        float min = 0,
        float max = 1,
        float step = 0.01,
        bool preserve = true);

    virtual float inc() {
      return set(value + step);
    }

    virtual float dec() {
      return set(value - step);
    }

    float set(float newVal) override {
      value = std::clamp(newVal, min, max);
      changed();
      return value;
    }

    void reset() override {
      value = init;
      changed();
    }

    virtual float normalized() const {
      return (value - min) / max;
    }

    float operator++() { return inc(); };
    float operator++(int) { return inc(); };
    float operator--() { return dec(); };
    float operator--(int) { return dec(); };

    using TypedField::operator=;
    using TypedField::operator float;

    top1::tree::Node serialize() override {
      return top1::tree::Float{value};
    }

    void deserialize(top1::tree::Node n) override {
      n.match([&] (top1::tree::Float f) { value = f.value; }, [] (auto) {});
      changed();
    }
  };

  template<>
  class Opt<int> : public TypedField<int> {
  public:
    int min;
    int max;
    int step;

    Opt() {};
    Opt(Data *data,
        std::string name,
        int init = 0,
        int min = std::numeric_limits<int>::min(),
        int max = std::numeric_limits<int>::max(),
        int step = 1,
        bool preserve = true);

    virtual int inc() {
      return set(value + step);
    }
    virtual int dec() {
      return set(value - step);
    }
    int set(int newVal) override {
      value = std::clamp(newVal, min, max);
      changed();
      return value;
    }
    void reset() override {
      set(init);
    }

    virtual float normalized() const {
      return (value - min) / (float)max;
    }

    int operator++() { return inc(); };
    int operator++(int) { return inc(); };
    int operator--() { return dec(); };
    int operator--(int) { return dec(); };
    using TypedField::operator=;
    using TypedField::operator int;

    top1::tree::Node serialize() override {
      return top1::tree::Int{value};
    }

    void deserialize(top1::tree::Node n) override {
      n.match([&] (top1::tree::Int i) { value = i.value; }, [] (auto) {});
      changed();
    }
  };

  template<>
  class Opt<bool> : public TypedField<bool> {
  public:
    Opt() {};
    Opt(Data *data,
        std::string name,
        bool init = false,
        bool preserve = true);

    virtual bool toggle() {
      return value = !value;
    }

    void reset() override {
      set(init);
    }

    using TypedField::operator=;
    using TypedField::operator bool;

    top1::tree::Node serialize() override {
      return top1::tree::Bool{bool(value)};
    }

    void deserialize(top1::tree::Node n) override {
      n.match([&] (top1::tree::Bool b) { set(b.value); }, [] (auto) {});
    }
  };

  template<>
  class Opt<std::string> : public TypedField<std::string> {
  public:
    Opt() {};
    Opt(Data *data,
        std::string name,
        std::string init = "",
        bool preserve = true);

    std::size_t size() const {
      return value.size();
    }

    void reset() override {
      set(init);
    }

    using TypedField::operator=;
    using TypedField::operator std::string;

    top1::tree::Node serialize() override {
      return top1::tree::String{value};
    }

    void deserialize(top1::tree::Node n) override {
      n.match([&] (top1::tree::String s) { set(s.value); }, [] (auto) {});
    }
  };


  class ExpOpt : public Opt<float> {
  public:

    using Opt<float>::Opt;

    float inc() override {return set(value * step);}
    float dec() override {return set(value / step);}
  };

  template<typename T>
  class WrapOpt : public Opt<T> {
  public:
    using Opt<T>::Opt;

    T set(T v) override {
      if (v > this->max) {
        this->value = this->min;
      } else if (v < this->min) {
        this->value = this->max;
      } else {
        this->value = v;
      }
      return this->value;
    }
  };


  using FieldPtr = top1::PolyPtr<
    Field,
    Opt<bool>,
    Opt<float>,
    Opt<int>,
    Opt<std::string>
    >;


  class Data {
  public:

    std::map<std::string, FieldPtr> fields;

    void subGroup(const std::string& name, Data& subgroup) {
      for (auto&& [key, val] : subgroup.fields) {
        fields[name + "/" + key] = val;
      }
    }

    template<typename T>
    void addField(const std::string& name, T *field) {
      fields[name] = field;
    };

    virtual top1::tree::Node serialize();
    virtual void deserialize(top1::tree::Node);
  };

  class Module {
  public:
    Data *data;
    Module(Data *data) : data (data) {}
    Module() {}
    virtual void init() {}
    virtual void exit() {}
    virtual void display() {};

    virtual top1::tree::Node serialize() {
      if (data != nullptr) return data->serialize();
      return top1::tree::Null();
    }
    virtual void deserialize(top1::tree::Node node) {
      if (data != nullptr) data->deserialize(node);
    }
  };

  class SynthModule : public Module {
  public:
    using Module::Module;
    virtual void process(audio::ProcessData&) = 0;
  };

  class EffectModule : public Module {
  public:
    using Module::Module;
    virtual void process(audio::ProcessData&) = 0;
  };

  class SequencerModule : public Module {
  public:
    using Module::Module;
    virtual void process(audio::ProcessData&) = 0;
  };

} // top1::module
