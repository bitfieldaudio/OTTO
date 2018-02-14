#pragma once

#include "../internal/property.hpp"
#include "../internal/mixin_macros.hpp"

namespace otto::core::props {

  OTTO_PROPS_MIXIN(has_name) {
    OTTO_PROPS_MIXIN_DECLS(has_name);

    void init(std::string name)
    {
      _name = name;
    }

    const std::string& name()
    {
      return _name;
    }

  protected:
    std::string _name;
  };
}
