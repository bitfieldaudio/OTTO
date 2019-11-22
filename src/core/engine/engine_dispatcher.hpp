#pragma once

#include "util/variant_w_base.hpp"

#include "core/engine/engine.hpp"
#include "core/engine/nullengine.hpp"

namespace otto::core::engine {

  /// Owns engines of type `ET`, and dispatches to a selected one of them
  template<EngineType ET, typename... Engines>
  struct EngineDispatcher {};
} // namespace otto::core::engine
