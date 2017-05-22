#pragma once

#include <vector>
#include <map>
#include <string>
#include <memory>
#include <cstdlib>

#include "utils.h"

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

    virtual std::vector<char> serialize();
    virtual void deserialize(std::vector<char> data);
  };

  std::map<std::string, std::shared_ptr<Field>> fields;

  void subGroup(std::string name, Data &subgroup) {
    for (auto field : subgroup.fields) {
      fields[name + "/" + field.first] = field.second;
    }
  }

  void addField(std::string name, std::shared_ptr<Field> field) {
    fields[name] = field;
  };
  virtual std::vector<char> serialize();
  virtual void deserialize(std::vector<char> data);

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
    bool preserve = false,
    float *dataPtr = new float):
    Field(dataPtr, preserve), init (init), min(min), max(max), step(step) {
    data->addField(name, std::shared_ptr<Opt<float>>(this));
  };

  virtual float inc() {
    return set(*dataPtr + step);
  }
  virtual float dec() {
    return set(*dataPtr - step);
  }
  virtual float set(float newVal) {
    return *dataPtr = top::withBounds(min, max, newVal);
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
  float operator--() { return dec(); };
  float operator = (float newVal) { return set(newVal); };
  float operator()() {return get(); }
};

template<>
class Opt<bool> : public Data::Field {
public:
  bool init;

  Opt() {};
  Opt(Data *data,
    std::string name,
    bool init = false,
    bool preserve = false,
    float *dataPtr = new float) :
    Field(dataPtr, preserve), init (init) {
    data->addField(name, std::shared_ptr<Field>(this));
  };
  virtual bool toggle() {
    return *dataPtr = !*dataPtr;
  }
  virtual bool set(bool newVal) {
    return *dataPtr = newVal;
  }
  virtual bool get() {
    return *dataPtr;
  }
  virtual void reset() {
    *dataPtr = init;
  }

  bool operator = (bool newVal) { return set(newVal); };
  bool operator()() {return get(); }
};

class ExpOpt : public Opt<float> {
  float inc() override {return set(*dataPtr * step);}
  float dec() override {return set(*dataPtr / step);}
};



class Module {
public:
  virtual void init() {}
  virtual void exit() {}
  virtual void display() {};
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
class ModuleDispatcher {
protected:

  std::map<std::string, std::shared_ptr<M>> modules;
  std::string currentModule;

public:

  void display() {
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
