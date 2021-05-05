#pragma once

#include "lib/util/func_interface.hpp"
#include "lib/util/smart_ptr.hpp"

#include "lib/skia/skia.hpp"

#include "app/input.hpp"
#include "app/layers.hpp"

namespace otto {
  struct IDrawable {
    virtual ~IDrawable() = default;
    virtual void draw(skia::Canvas& ctx) noexcept = 0;
  };

  using DrawFunc = util::FuncInterface<&IDrawable::draw>;

  struct IScreen : IDrawable, ILEDLayer {
    [[nodiscard]] virtual bool is_overlay() const
    {
      return false;
    }
  };

  struct IOverlay : IScreen {
    [[nodiscard]] bool is_overlay() const override
    {
      return true;
    }
  };

  /// Pair of unique_ptrs to a screen and an input layer.
  ///
  /// You almost never want to refer to either of these separately, but since they run on separate threads, they are
  /// split up into separate objects.
  struct ScreenWithHandler {
    std::unique_ptr<IScreen> screen;
    std::unique_ptr<IInputLayer> input;
    bool operator==(const ScreenWithHandler&) const = default;

    /// Make a `ScreenWithHandler` where both components are constructed from the same args
    template<std::derived_from<IScreen> Screen, std::derived_from<IInputLayer> InputLayer, typename... Args>
    requires(std::is_constructible_v<Screen, Args...>&& std::is_constructible_v<InputLayer, Args...>) //
      static ScreenWithHandler make(Args&&... args)
    {
      return {std::make_unique<Screen>(args...), std::make_unique<InputLayer>(args...)};
    }
  };

  struct ScreenWithHandlerPtr {
    ScreenWithHandlerPtr() = default;
    ScreenWithHandlerPtr(std::nullptr_t) {}
    ScreenWithHandlerPtr(IScreen* s, IInputLayer* h) : screen(s), input(h) {}
    ScreenWithHandlerPtr(const ScreenWithHandler& swh) : screen(swh.screen.get()), input(swh.input.get()) {}
    ScreenWithHandlerPtr(ScreenWithHandler&& swh) = delete;

    bool operator==(const ScreenWithHandlerPtr&) const = default;
    bool operator==(const ScreenWithHandler& rhs) const
    {
      return rhs.screen.get() == screen && rhs.input.get() == input;
    }
    bool operator==(std::nullptr_t) const
    {
      return screen == nullptr || input == nullptr;
    }

    IScreen* screen = nullptr;
    IInputLayer* input = nullptr;
  };
} // namespace otto
