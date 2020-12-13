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
    std::unique_ptr<IScreen> screen;
    std::unique_ptr<IInputHandler> handler;
    bool operator==(const ScreenWithHandler&) const = default;
  };

  struct ScreenWithHandlerPtr {
    ScreenWithHandlerPtr() = default;
    ScreenWithHandlerPtr(std::nullptr_t) {}
    ScreenWithHandlerPtr(IScreen* s, IInputHandler* h) : screen(s), handler(h) {}
    ScreenWithHandlerPtr(const ScreenWithHandler& swh) : screen(swh.screen.get()), handler(swh.handler.get()) {}
    ScreenWithHandlerPtr(ScreenWithHandler&& swh) = delete;

    bool operator==(const ScreenWithHandlerPtr&) const = default;
    bool operator==(const ScreenWithHandler& rhs) const
    {
      return rhs.screen.get() == screen && rhs.handler.get() == handler;
    }
    bool operator==(std::nullptr_t) const
    {
      return screen == nullptr || handler == nullptr;
    }

    IScreen* screen = nullptr;
    IInputHandler* handler = nullptr;
  };
} // namespace otto
