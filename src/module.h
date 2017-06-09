#pragma once

#include <vector>
#include <map>
#include <string>
#include <memory>
#include <cstdlib>
#include <plog/Log.h>

#include "utils.h"
#include "util/tree.h"

namespace module {
class Data {
public:
  class Field {
  public:
    float *dataPtr;
    bool preserve = true;

    Field() {}
    Field(float *dataPtr, bool preserve = true) :
      dataPtr(dataPtr), preserve(preserve) {}

    virtual top1::tree::Node serialize() {
      return top1::tree::Float{*dataPtr};
    }

    virtual void deserialize(top1::tree::Node n) {
      n.match([&] (top1::tree::Float f) { *dataPtr = f.value; }, [] (auto) {});
    }
  };


  std::map<std::string, Field*> fields;

  void subGroup(std::string name, Data &subgroup) {
    for (auto field : subgroup.fields) {
      fields[name + "/" + field.first] = field.second;
    }
  }

  void addField(std::string name, Field *field) {
    fields[name] = field;
  };
  virtual top1::tree::Node serialize();
  virtual void deserialize(top1::tree::Node);
};

template<class T>
class Opt : public Data::Field {
public:
  Opt() {};
  Opt(Data *data);

  virtual void set(T value);
  virtual T get();
};

template<>
class Opt<float> : public Data::Field {
public:
  float init;
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
    bool preserve = true,
    float *dataPtr = new float):
    Field(dataPtr, preserve), init (init), min(min), max(max), step(step) {
    data->addField(name, this);
  };

  virtual float inc() {
    return set(*dataPtr + step);
  }
  virtual float dec() {
    return set(*dataPtr - step);
  }
  virtual float set(float newVal) {
    return *dataPtr = top1::withBounds(min, max, newVal);
  }
  virtual float get() const {
    return *dataPtr;
  }
  virtual void reset() {
    *dataPtr = init;
  }

  virtual float normalized() const {
    return (*dataPtr - min) / max;
  }

  float operator++() { return inc(); };
  float operator++(int) { return inc(); };
  float operator--() { return dec(); };
  float operator--(int) { return dec(); };
  float operator = (float newVal) { return set(newVal); };
  float operator()() const { return get(); }
  operator float() const { return get(); }

  virtual top1::tree::Node serialize() {
    return top1::tree::Float{*dataPtr};
  }

  virtual void deserialize(top1::tree::Node n) {
    n.match([&] (top1::tree::Float f) { *dataPtr = f.value; }, [] (auto) {});
  }
};

template<>
class Opt<bool> : public Data::Field {
public:
  bool init;

  Opt() {};
  Opt(Data *data,
    std::string name,
    bool init = false,
    bool preserve = true,
    float *dataPtr = new float) :
    Field(dataPtr, preserve), init (init) {
    data->addField(name, this);
  };
  virtual bool toggle() {
    return *dataPtr = !*dataPtr;
  }
  virtual bool set(bool newVal) {
    return *dataPtr = newVal;
  }
  virtual bool get() const {
    return *dataPtr;
  }
  virtual void reset() {
    *dataPtr = init;
  }

  bool operator = (bool newVal) { return set(newVal); };
  bool operator()() const {return get(); }
  operator bool() const { return get(); }

  virtual top1::tree::Node serialize() {
    return top1::tree::Bool{bool(*dataPtr)};
  }

  virtual void deserialize(top1::tree::Node n) {
    n.match([&] (top1::tree::Bool b) { *dataPtr = b.value; }, [] (auto) {});
  }
};

class ExpOpt : public Opt<float> {
public:
  ExpOpt() {};
  ExpOpt(Data *data,
   std::string name,
   float init = 0,
   float min = 0,
   float max = 1,
   float step = 0.01,
   bool preserve = false,
   float *dataPtr = new float):
    Opt<float>(data, name, init, min, max, step, preserve, dataPtr) {};
 
  float inc() override {return set(*dataPtr * step);}
  float dec() override {return set(*dataPtr / step);}
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
  virtual void process(uint nframes) = 0;
};

class EffectModule : public Module {
public:
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
