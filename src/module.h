#pragma once

#include <vector>
#include <cstdlib>

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

  std::vector<M*> modules;
  uint currentModule;

public:

  void display() {
    modules[currentModule]->display();
  }

  M *getCurrent() {
    return modules[currentModule];
  }

  uint registerModule(M *module) {
    modules.push_back(module);
    return modules.size() - 1;
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
