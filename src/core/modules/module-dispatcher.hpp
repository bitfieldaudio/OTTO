#pragma once

#include "core/modules/module.hpp"
#include "core/ui/screens.hpp"
#include "core/audio/processor.hpp"

namespace otto::modules {

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

    template<typename T, typename... Args>
    std::enable_if_t<std::is_convertible_v<T*, M*>, void>
    registerModule(std::string name, Args&&... args) {
      selectorScreen->items.push_back({name, (int)modules.size()});
      modules.emplace_back(std::move(name),
        std::make_unique<T>(std::forward<Args>(args)...));
    }

    util::tree::Node makeNode() override;

    void readNode(util::tree::Node node) override;
  };

  class SynthModuleDispatcher : public ModuleDispatcher<SynthModule> {
  public:

    audio::ProcessData<1> process(audio::ProcessData<0> data) {
      if (modules.size() > 0) {
        return modules[currentModule].val->process(data);
      }
      return {};
    }
  };

  class EffectModuleDispatcher : public ModuleDispatcher<EffectModule> {
  public:

    audio::ProcessData<1> process(audio::ProcessData<1> data) {
      if (modules.size() > 0) {
        return modules[currentModule].val->process(data);
      }
      return data;
    }
  };

  class SequencerModuleDispatcher : public ModuleDispatcher<SequencerModule> {
  public:

    audio::ProcessData<0> process(audio::ProcessData<0> data) {
      if (modules.size() > 0) {
        return modules[currentModule].val->process(data);
      }
      return {};
    }
  };

  /****************************************/
  /* ModuleDispatcher Implementation      */
  /****************************************/

  template<typename M>
  ModuleDispatcher<M>::ModuleDispatcher() :
    selectorScreen (new ui::SelectorScreen<int>({}, ui::vg::Colours::Blue)) {
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
  util::tree::Node ModuleDispatcher<M>::makeNode() {
    util::tree::Map node;
    for ([[maybe_unused]] auto&& [k, v] : modules) {
      node[k] = v->makeNode();
    }
    return node;
  }

  template<typename M>
  void ModuleDispatcher<M>::readNode(util::tree::Node node) {
    node.match([&] (util::tree::Map n) {
        for (auto&& m : n.values) {
          auto&& md = std::find(modules.begin(), modules.end(), m.first);
          if (md != modules.end()) {
            md->val->readNode(m.second);
          } else {
            LOGE << "Unrecognized module";
          }
        }
      }, [] (auto) {});
  }

}
