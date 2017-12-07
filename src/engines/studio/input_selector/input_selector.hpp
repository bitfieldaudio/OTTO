#pragma once

#include "core/engines/engine.hpp"
#include "core/engines/engine-props.hpp"

namespace otto::engines {

  class InputSelector : public Engine {
  public:
    enum class Selection {
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

  };

}
