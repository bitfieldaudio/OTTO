#pragma once
#include "core/module.h"

namespace top1 {

/**
 * A screen that belongs to a module of type M
 */
template<class M>
class ModuleScreen : public Screen {
protected:
  M *module;

public:
  using ptr = std::shared_ptr<ModuleScreen<M>>;

  ModuleScreen() :
    Screen() {}

  ModuleScreen(M *module)
    : module (module),
      Screen () {}

  virtual ~ModuleScreen() {}
};

}  // top1
