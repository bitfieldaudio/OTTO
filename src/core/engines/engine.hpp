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
#include <json.hpp>

#include "util/poly-ptr.hpp"
#include "core/audio/processor.hpp"
#include "core/engines/engine-props.hpp"

namespace otto::engines {

  class Engine {
  public:
    Properties* propsPtr;
    Engine(Properties* props) : propsPtr (props) {}
    Engine() {}
    virtual ~Engine() {}
    virtual void init() {}
    virtual void exit() {}
    virtual void display() {};

    virtual nlohmann::json to_json() const {
      if (propsPtr != nullptr) return propsPtr->to_json();
      return {};
    }

    virtual void from_json(const nlohmann::json& j) {
      if (propsPtr != nullptr) propsPtr->from_json(j);
    }
  };

  inline void to_json(nlohmann::json& j, const Engine& m) {
    j = m.to_json();
  }

  inline void from_json(const nlohmann::json& j, Engine& m) {
    m.from_json(j);
  }

  class SynthEngine : public Engine {
  public:
    using Engine::Engine;
    virtual audio::ProcessData<1> process(audio::ProcessData<0>) = 0;
  };

  class EffectEngine : public Engine {
  public:
    using Engine::Engine;
    virtual audio::ProcessData<1> process(const audio::ProcessData<1>&) = 0;
  };

  class SequencerEngine : public Engine {
  public:
    using Engine::Engine;
    virtual audio::ProcessData<0> process(const audio::ProcessData<0>&) = 0;
  };

} // otto::engine
