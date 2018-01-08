#pragma once

#include "core/engines/engine.hpp"
#include "core/engines/engine_props.hpp"

namespace otto::engines {

  using namespace core;
  using namespace core::engines;

  struct InputSelector final : Engine<EngineType::studio> {
    enum struct Selection {
      Internal,
      External,
      TrackFB,
      MasterFB
    };

    struct Props : Properties {
      Property<Selection, wrap> input {this, "input",
          Selection::Internal, {Selection::Internal, Selection::MasterFB}};
      Property<int, wrap> track {this, "track", 0, {0, 3}};

      using Properties::Properties;
    } props;

    InputSelector()
      : Engine ("InputSelector", props, nullptr)
    {}

  };

}
