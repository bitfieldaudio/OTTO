#pragma once

#include "core/engines/engine.hpp"

namespace otto::engines {

  using namespace core;
  using namespace core::engines;
  using namespace props;

  struct InputSelector final : Engine<EngineType::studio> {
    enum struct Selection {
      Internal = 0,
      External = 1,
      TrackFB = 2,
      MasterFB = 3
    };

    struct Props : Properties<> {
      Property<std::underlying_type_t<Selection>, wrap> input = {
        this, "input", 0,
        has_limits::init(0, 3)};
      Property<int, wrap> track {this, "track", 0, has_limits::init(0, 3)};

      using Properties::Properties;
    } props;

    InputSelector()
      : Engine ("InputSelector", props, nullptr)
    {}

  };

}
