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
#include "core/modules/module-props.hpp"

namespace otto::modules {

  class Module {
  public:
    Properties* propsPtr;
    Module(Properties* props) : propsPtr (props) {}
    Module() {}
    virtual ~Module() {}
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

  inline void to_json(nlohmann::json& j, const Module& m) {
    j = m.to_json();
  }

  inline void from_json(const nlohmann::json& j, Module& m) {
    if (m.propsPtr != nullptr) m.propsPtr->from_json(j);
  }

  class SynthModule : public Module {
  public:
    using Module::Module;
    virtual audio::ProcessData<1> process(audio::ProcessData<0>) = 0;
  };

  class EffectModule : public Module {
  public:
    using Module::Module;
    virtual audio::ProcessData<1> process(const audio::ProcessData<1>&) = 0;
  };

  class SequencerModule : public Module {
  public:
    using Module::Module;
    virtual audio::ProcessData<0> process(const audio::ProcessData<0>&) = 0;
  };

} // otto::module
