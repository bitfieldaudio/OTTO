#pragma once

#include "app/services/audio.hpp"
#include "app/services/controller.hpp"
#include "app/services/graphics.hpp"
#include "lib/core/service.hpp"
#include "lib/graphics.hpp"

#include "app/input.hpp"
#include "lib/midi.hpp"

namespace otto::services {

  struct UIManager : core::Service<UIManager>, core::ServiceAccessor<Audio, Controller, Graphics> {
  private:
    struct Handler;
    struct Drawable;

  public:
    UIManager();
    ~UIManager();
    UIManager(const UIManager&) = delete;
    UIManager& operator=(const UIManager&) = delete;

  private:
    std::unique_ptr<Handler> input_handler_;
    std::unique_ptr<Drawable> drawable_;
    std::vector<util::smart_ptr<InputHandler>> global_handlers_;
  };

} // namespace otto::services
