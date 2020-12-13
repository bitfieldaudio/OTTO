#pragma once

#include "app/input.hpp"

#include "app/services/audio.hpp"
#include "lib/core/service.hpp"
#include "lib/util/smart_ptr.hpp"
#include "lib/util/visitor.hpp"

namespace otto {
  /// Key handler that sends midi events for the keyboard keys
  struct KeyboardKeysHandler : InputHandler, core::ServiceAccessor<services::Audio> {
    struct State {
      int octave = 0;
      DECL_VISIT(octave);
    };

    KeyboardKeysHandler(util::smart_ptr<State> state = std::make_unique<State>()) : state_(std::move(state)) {}

    void handle(KeyPress e) noexcept override;
    void handle(KeyRelease e) noexcept override;

  private:
    util::smart_ptr<State> state_;
  };
} // namespace otto
