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

#include "util/tree.hpp"
#include "util/poly-ptr.hpp"
#include "core/audio/processor.hpp"
#include "core/modules/module-props.hpp"

namespace top1::modules {

  class Module {
  public:
    Properties* propsPtr;
    Module(Properties* props) : propsPtr (props) {}
    Module() {}
    virtual ~Module() {}
    virtual void init() {}
    virtual void exit() {}
    virtual void display() {};

    virtual tree::Node makeNode() {
      if (propsPtr != nullptr) return propsPtr->makeNode();
      return tree::Null();
    }
    virtual void readNode(top1::tree::Node node) {
      if (propsPtr != nullptr) propsPtr->readNode(node);
    }
  };

  class SynthModule : public Module {
  public:
    using Module::Module;
    virtual void process(audio::ProcessData&) = 0;
  };

  class EffectModule : public Module {
  public:
    using Module::Module;
    virtual void process(audio::ProcessData&) = 0;
  };

  class SequencerModule : public Module {
  public:
    using Module::Module;
    virtual void process(audio::ProcessData&) = 0;
  };

} // top1::module
