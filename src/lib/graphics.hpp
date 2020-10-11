#pragma once

#include <SkCanvas.h>

#include "lib/util/func_interface.hpp"

namespace otto {
  struct IDrawable {
    virtual void draw(SkCanvas& ctx) noexcept = 0;
  };

  using DrawFunc = util::FuncInterface<&IDrawable::draw>;

  struct IScreen : IDrawable {};

} // namespace otto
