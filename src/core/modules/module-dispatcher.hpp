#pragma once

#include "core/modules/module.hpp"
#include "core/ui/screens.hpp"
#include "core/audio/processor.hpp"

namespace top1::modules {

namespace detail {

// Required to move implementation of ModuleDispatcher::display into the .cpp
// This is required as this function needs to check GLOB.ui.keys
bool isShiftPressed();
void displayScreen(ui::Screen&);

}

template<class M>
class ModuleDispatcher : public Module {

  std::unique_ptr<ui::SelectorScreen<int>> selectorScreen;

  struct Mstor {
    std::string key;
    std::unique_ptr<M> val;

    Mstor(const std::string& key, std::unique_ptr<M>&& v) : key (key), val (std::move(v)) {}

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

  M& current();

  void current(std::size_t cur);

  void registerModule(const std::string& name, M *module);

  void registerModule(const std::string& name, std::unique_ptr<M>&& module);

  top1::tree::Node serialize() override;

  void deserialize(top1::tree::Node node) override;
};

class SynthModuleDispatcher : public ModuleDispatcher<SynthModule> {
public:

  void process(audio::ProcessData& data) {
    if (modules.size() > 0)
      modules[currentModule].val->process(data);
  }
};

class EffectModuleDispatcher : public ModuleDispatcher<EffectModule> {
public:

  void process(audio::ProcessData& data) {
    if (modules.size() > 0)
      modules[currentModule].val->process(data);
  }
};

class SequencerModuleDispatcher : public ModuleDispatcher<SequencerModule> {
public:

  void process(audio::ProcessData& data) {
    if (modules.size() > 0)
      modules[currentModule].val->process(data);
  }
};

/****************************************/
/* ModuleDispatcher Implementation      */
/****************************************/

template<typename M>
ModuleDispatcher<M>::ModuleDispatcher() :
  selectorScreen (new ui::SelectorScreen<int>({}, ui::drawing::Colours::Blue)) {
  selectorScreen->onSelect = [&]() {
    current(selectorScreen->selectedItem);
  };
}

template<typename M>
void ModuleDispatcher<M>::display() {
  if (detail::isShiftPressed()) {
    detail::displayScreen(*selectorScreen);
  } else {
    modules[currentModule].val->display();
  }
}

template<typename M>
M& ModuleDispatcher<M>::current() {
  return *modules[currentModule].val;
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
void ModuleDispatcher<M>::registerModule(const std::string& name, M *module) {
  registerModule(name, std::unique_ptr<M>(module));
}

template<typename M>
void ModuleDispatcher<M>::registerModule(const std::string& name, std::unique_ptr<M>&& module) {
  selectorScreen->items.push_back({name, (int) modules.size()});
  modules.emplace_back(name, std::move(module));
}

  template<typename M>
  top1::tree::Node ModuleDispatcher<M>::serialize() {
    top1::tree::Map node;
    for (auto&& [k, v] : modules) {
      node[k] = v->serialize();
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
