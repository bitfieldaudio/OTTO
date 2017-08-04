#pragma once

#include "module.h"
#include "ui/screens.h"

namespace module {

namespace detail {

// Required to move implementation of ModuleDispatcher::display into the .cpp
// This is required as this function needs to check GLOB.ui.keys
bool isShiftPressed();
void displayScreen(ui::Screen::ptr);

}

template<class M>
class ModuleDispatcher : public Module {

  std::shared_ptr<ui::SelectorScreen<int>> selectorScreen;

  struct Mstor {
    std::string key;
    std::shared_ptr<M> val;

    bool operator==(const Mstor &other) const {
      return key == other.key;
    }

    bool operator==(const std::string &other) const {
      return key == other;
    }

    decltype(auto) operator->() {
      return val.operator->();
    }
  };

protected:

  std::vector<Mstor> modules;
  std::size_t currentModule = 0;

public:

  ModuleDispatcher();

  void display() override;

  std::shared_ptr<M> current();

  void current(std::size_t cur);

  void registerModule(std::string name, M *module);

  void registerModule(std::string name, std::shared_ptr<M> module);

  top1::tree::Node serialize() override;

  void deserialize(top1::tree::Node node) override;
};

class SynthModuleDispatcher : public ModuleDispatcher<SynthModule> {
public:

  void process(uint nframes) {
    if (modules.size() > 0)
      modules[currentModule].val->process(nframes);
  }
};

class EffectModuleDispatcher : public ModuleDispatcher<EffectModule> {
public:

  void process(uint nframes) {
    if (modules.size() > 0)
      modules[currentModule].val->process(nframes);
  }
};

class SequencerModuleDispatcher : public ModuleDispatcher<SequencerModule> {
public:

  void process(uint nframes) {
    if (modules.size() > 0)
      modules[currentModule].val->process(nframes);
  }
};

/****************************************/
/* ModuleDispatcher Implementation       /
/****************************************/

template<typename M>
ModuleDispatcher<M>::ModuleDispatcher() :
  selectorScreen (new ui::SelectorScreen<int>({}, drawing::Colours::Blue)) {
  selectorScreen->onSelect = [&]() {
    current(selectorScreen->selectedItem);
  };
}

template<typename M>
void ModuleDispatcher<M>::display() {
  if (detail::isShiftPressed()) {
    detail::displayScreen(selectorScreen);
  } else {
    modules[currentModule].val->display();
  }
}

template<typename M>
std::shared_ptr<M> ModuleDispatcher<M>::current() {
  return modules[currentModule].val;
}

template<typename M>
void ModuleDispatcher<M>::current(std::size_t cur) {
  if (cur < modules.size()) {
    modules[currentModule]->exit();
    currentModule = cur;
    selectorScreen->selectedItem = cur;
    modules[cur]->init();
  } else {
    throw std::out_of_range("Attempt to access module out of range");
  }
}

template<typename M>
void ModuleDispatcher<M>::registerModule(std::string name, M *module) {
  registerModule(name, std::shared_ptr<M>(module));
}

template<typename M>
void ModuleDispatcher<M>::registerModule(std::string name, std::shared_ptr<M> module) {
  selectorScreen->items.push_back({name, modules.size()});
  modules.push_back({name, module});
}

template<typename M>
top1::tree::Node ModuleDispatcher<M>::serialize() {
  top1::tree::Map node;
  for (auto m : modules) {
    node[m.key] = m.val->serialize();
  }
  return node;
}

template<typename M>
void ModuleDispatcher<M>::deserialize(top1::tree::Node node) {
  node.match([&] (top1::tree::Map n) {
     for (auto &m : n.values) {
       auto &&md = std::find(modules.begin(), modules.end(), m.first);
       if (md != modules.end()) {
         md->val->deserialize(m.second);
       } else {
         LOGE << "Unrecognized module";
       }
     }
   }, [] (auto) {});
}

}
