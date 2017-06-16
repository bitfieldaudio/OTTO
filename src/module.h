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

#include "utils.h"
#include "util/tree.h"
#include "util/poly-ptr.h"

namespace module {

template<class T> struct isValidFieldType { static constexpr bool value = false; };
template<> struct isValidFieldType<float> { static constexpr bool value = true; };
template<> struct isValidFieldType<bool> { static constexpr bool value = true; };
template<> struct isValidFieldType<int> { static constexpr bool value = true; };

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

template<class T, typename = std::enable_if_t<isValidFieldType<T>::value>>
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
    value = top1::withBounds(min, max, newVal);
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
    n.match([&] (top1::tree::Float f) { set(f.value); }, [] (auto) {});
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
    value = top1::withBounds(min, max, newVal);
    changed();
    return value;
  }
  void reset() override {
    set(init);
  }

  virtual int normalized() const {
    return (value - min) / max;
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
    n.match([&] (top1::tree::Int i) { set(i.value); }, [] (auto) {});
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

class ExpOpt : public Opt<float> {
public:

  using Opt<float>::Opt;

  float inc() override {return set(value * step);}
  float dec() override {return set(value / step);}
};


using FieldPtr = top1::PolyPtr<Field, Opt<bool>, Opt<float>, Opt<int>>;


class Data {
public:

  std::map<std::string, FieldPtr> fields;

  void subGroup(std::string name, Data &subgroup) {
    for (auto &&field : subgroup.fields) {
      fields[name + "/" + field.first] = field.second;
    }
  }

  template<typename T>
  void addField(std::string name, T *field) {
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
  virtual void process(uint nframes) = 0;
};

class EffectModule : public Module {
public:
  using Module::Module;
  virtual void process(uint nframes) = 0;
};

template<class M>
class ModuleDispatcher : public Module {
protected:

  std::map<std::string, std::shared_ptr<M>> modules;
  std::string currentModule;

public:

  void display() override {
    modules[currentModule]->display();
  }

  std::shared_ptr<M> getCurrent() {
    return modules[currentModule];
  }

  void registerModule(std::string name, M *module) {
    registerModule(name, std::shared_ptr<M>(module));
  }

  void registerModule(std::string name, std::shared_ptr<M> module) {
    modules[name] = module;
    currentModule = name;
  }

  top1::tree::Node serialize() override {
    top1::tree::Map node;
    for (auto m : modules) {
      node[m.first] = m.second->serialize();
    }
    return node;
  }

  void deserialize(top1::tree::Node node) override {
    node.match([&] (top1::tree::Map n) {
       for (auto &m : n.values) {
         if (modules.find(m.first) != modules.end()) {
           modules[m.first]->deserialize(m.second);
         } else {
           LOGE << "Unrecognized module";
         }
       }
     }, [] (auto) {});
  }
};

class SynthModuleDispatcher : public ModuleDispatcher<SynthModule> {
public:

  void process(uint nframes) {
    if (modules.size() > 0)
      modules[currentModule]->process(nframes);
  }
};

class EffectModuleDispatcher : public ModuleDispatcher<EffectModule> {
public:

  void process(uint nframes) {
    if (modules.size() > 0)
      modules[currentModule]->process(nframes);
  }
};

}
