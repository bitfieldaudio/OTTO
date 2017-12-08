#if false
#include "core/engines/engine.hpp"
#include "core/ui/screens.hpp"
#include "core/audio/processor.hpp"

namespace otto::engines {

  namespace detail {

    // Required to move implementation of EngineDispatcher::display into the .cpp
    // This is required as this function needs to check GLOB.ui.keys
    bool isShiftPressed();
    void displayScreen(ui::Screen&);

  }

  template<class M>
  class EngineDispatcher : public Engine {

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

    std::vector<Mstor> engines;
    std::size_t currentEngine = 0;

  public:

    EngineDispatcher();

    void display() override;

    M& current();

    void current(std::size_t cur);

    template<typename T, typename... Args>
    std::enable_if_t<std::is_convertible_v<T*, M*>, void>
    registerEngine(std::string name, Args&&... args) {
      selectorScreen->items.push_back({name, (int)engines.size()});
      engines.emplace_back(std::move(name),
        std::make_unique<T>(std::forward<Args>(args)...));
    }

    nlohmann::json to_json() const override;
    void from_json(const nlohmann::json&) override;
  };

  class SynthEngineDispatcher : public EngineDispatcher<SynthEngine> {
  public:

    audio::ProcessData<1> process(audio::ProcessData<0> data) {
      if (engines.size() > 0) {
        return engines[currentEngine].val->process(data);
      }
      return {};
    }
  };

  class EffectEngineDispatcher : public EngineDispatcher<EffectEngine> {
  public:

    audio::ProcessData<1> process(audio::ProcessData<1> data) {
      if (engines.size() > 0) {
        return engines[currentEngine].val->process(data);
      }
      return data;
    }
  };

  class SequencerEngineDispatcher : public EngineDispatcher<SequencerEngine> {
  public:

    audio::ProcessData<0> process(audio::ProcessData<0> data) {
      if (engines.size() > 0) {
        return engines[currentEngine].val->process(data);
      }
      return {};
    }
  };

  /****************************************/
  /* EngineDispatcher Implementation      */
  /****************************************/

  template<typename M>
  EngineDispatcher<M>::EngineDispatcher() :
    selectorScreen (new ui::SelectorScreen<int>({}, ui::vg::Colours::Blue)) {
    selectorScreen->onSelect = [&]() {
      current(selectorScreen->selectedItem);
    };
  }

  template<typename M>
  void EngineDispatcher<M>::display() {
    if (detail::isShiftPressed()) {
      detail::displayScreen(*selectorScreen);
    } else {
      engines[currentEngine].val->display();
    }
  }

  template<typename M>
  M& EngineDispatcher<M>::current() {
    return *engines[currentEngine].val;
  }

  template<typename M>
  void EngineDispatcher<M>::current(std::size_t cur) {
    if (cur < engines.size()) {
      engines[currentEngine]->exit();
      currentEngine = cur;
      selectorScreen->selectedItem = cur;
      engines[cur]->init();
    } else {
      throw std::out_of_range("Attempt to access engine out of range");
    }
  }

  template <typename M>
  nlohmann::json EngineDispatcher<M>::to_json() const
  {
    auto obj = nlohmann::json::object();
    for (auto&& [k, v] : engines) {
      obj[k] = v->to_json();
    }
    return obj;
  }

  template <typename M>
  void EngineDispatcher<M>::from_json(const nlohmann::json& j)
  {
    if (j.is_object()) {
      for (auto it = j.begin(); it != j.end(); it++) {
        auto md = std::find(engines.begin(), engines.end(), it.key());
        if (md != engines.end()) {
          md->val->from_json(it.value());
        } else {
          // Consider throwing? but it might be alright that a engine wasnt
          // found, maybe it was for a never version of the OTTO
          LOGE << "Unrecognized engine";
        }
      }
    } else if (!j.empty()) {
      throw util::JsonFile::exception(util::JsonFile::ErrorCode::invalid_data,
        "Expected a json object");
    }
  }
}

#endif
