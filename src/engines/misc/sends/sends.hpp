#pragma once

#include "core/engine/engine.hpp"

namespace otto::engines {

  using namespace core;
  using namespace core::engine;

  struct Sends : MiscEngine<Sends> {
    static constexpr util::string_ref name = "Sends";
    struct Props {
      props::Property<float> to_FX1 = {0, props::limits(0, 1), props::step_size(0.01)};
      props::Property<float> to_FX2 = {0, props::limits(0, 1), props::step_size(0.01)};
      props::Property<float> dry = {1, props::limits(0, 1), props::step_size(0.01)};
      props::Property<float> dry_pan = {0, props::limits(-1, 1), props::step_size(0.01)};

      DECL_REFLECTION(Props, to_FX1, to_FX2, dry, dry_pan);
    } props;

    Sends();
  };
} // namespace otto::engines
