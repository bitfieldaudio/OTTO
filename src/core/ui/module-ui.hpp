#pragma once

#include "core/ui/base.hpp"

namespace top1::ui {

  /**
   * A screen that belongs to a module of type M
   */
  template<class M>
  class ModuleScreen : public Screen {
  protected:
    M* module;

  public:
    using ptr = std::shared_ptr<ModuleScreen<M>>;

    ModuleScreen() : Screen(), module (nullptr){}

    ModuleScreen(M* module) : Screen (), module (module) {}

    virtual ~ModuleScreen() {}
  };

} // top1::ui
