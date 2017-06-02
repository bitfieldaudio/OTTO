#pragma once

#include <vector>
#include <map>
#include <string>
#include <memory>
#include <cstdlib>
#include <plog/Log.h>

#include "utils.h"
#include "util/tree.h"
#include "util/serialization.h"

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

    virtual top1::TreeNode serialize();
    virtual void deserialize(top1::TreeNode);
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
  virtual top1::TreeBranch serialize();
  virtual void deserialize(top1::TreeBranch);
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
};

class ExpOpt : public Opt<float> {
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

  virtual top1::TreeBranch serialize() {
    if (data != nullptr) return data->serialize();
    return top1::TreeBranch();
  }
  virtual void deserialize(top1::TreeBranch node) {
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

  std::map<top1::fourCC, std::shared_ptr<M>> modules;
  top1::fourCC currentModule;

public:

  void display() override {
    modules[currentModule]->display();
  }

  std::shared_ptr<M> getCurrent() {
    return modules[currentModule];
  }

  void registerModule(top1::fourCC name, M *module) {
    registerModule(name, std::shared_ptr<M>(module));
  }

  void registerModule(top1::fourCC name, std::shared_ptr<M> module) {
    modules[name] = module;
    currentModule = name;
  }

  top1::TreeBranch serialize() override {
    std::vector<char> xs;
    for (auto m : modules) {
      auto md = m.second->serialize();
      top1::serialize<top1::fourCC>(m.first, xs.end());
      top1::serialize<uint>(md.size(), xs.end());
      xs.reserve(xs.size() + md.size());
      xs.insert(xs.end(), md.begin(), md.end());
    }
  }

  void deserialize(top1::TreeBranch node) override {
    node.visit([&](top1::TreeNode &node) {
       if () {
         n.
       }
     });
    auto it = bytes.begin();
    while (it < bytes.end()) {
      uint name = top1::deserialize<uint>(it);
      uint size = top1::deserialize<uint>(it);
      auto m = modules.find(name);
      if (m != modules.end()) {
        m.second->deserialize(std::vector<char>(it, it + size));
      } else {
        it += size;
        LOGE << "Unrecognized module";
      }
    }
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
