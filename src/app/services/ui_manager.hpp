#pragma once

#include "lib/graphics.hpp"
#include "lib/midi.hpp"

#include "app/input.hpp"
#include "app/services/audio.hpp"
#include "app/services/controller.hpp"
#include "app/services/graphics.hpp"

namespace otto::services {

  struct UIManager {
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
