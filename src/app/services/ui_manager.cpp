#include "ui_manager.hpp"

namespace otto::services {

  struct UIManager::Handler final : IInputHandler {
    Handler(UIManager& uim) : uim(uim) {}

    void handle(KeyPress e) noexcept override {}

    void handle(KeyRelease e) noexcept override {}

    void handle(EncoderEvent e) noexcept override {}

    UIManager& uim;
  };

  struct UIManager::Drawable final : IDrawable {
    Drawable(UIManager& uim) : uim(uim) {}
    void draw(skia::Canvas& ctx) noexcept override {}
    UIManager& uim;
  };

  UIManager::UIManager()
    : input_handler_(std::make_unique<Handler>(*this)), drawable_(std::make_unique<Drawable>(*this))
  {
    // service<Controller>().set_input_handler(*input_handler_);
    // service<Graphics>().show(*drawable_);
  }

  UIManager::~UIManager() = default;

} // namespace otto::services
