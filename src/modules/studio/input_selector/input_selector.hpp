#pragma once

#include "core/modules/module.hpp"
#include "core/modules/module-props.hpp"

namespace otto::modules {

  class InputSelector : public Module {
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
