#pragma once

#include "lib/skia/skia.hpp"
#include "lib/util/any_ptr.hpp"
#include "lib/util/func_interface.hpp"

#include "app/input.hpp"

namespace otto {
  struct IDrawable {
    virtual ~IDrawable() = default;
    virtual void draw(skia::Canvas& ctx) noexcept = 0;
  };

  using DrawFunc = util::FuncInterface<&IDrawable::draw>;

  struct IScreen : IDrawable {};

  struct ScreenWithHandler {
    util::any_ptr<IScreen> screen;
    util::any_ptr<IInputHandler> handler;
  };
} // namespace otto
