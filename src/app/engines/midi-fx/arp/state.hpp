#pragma once

#include "lib/util/visitor.hpp"
#include "lib/util/with_limits.hpp"

namespace otto::engines::arp {

  enum struct PlayMode { up, down, updown, downup, updowninc, downupinc, manual, chord, random };
  enum struct OctaveMode { standard, octaveup, doubleoctaveup, octaveupunison, fifthunison, octavedownup, multiply };

  struct State {
    util::SelectableEnum<PlayMode, util::bounds_policies::wrap> playmode = {PlayMode::up};
    util::SelectableEnum<OctaveMode, util::bounds_policies::wrap> octavemode = {OctaveMode::standard};
    util::StaticallyBounded<float, 0, 1> note_length = 0.2f;
    util::StaticallyBounded<int, 1, 5, util::bounds_policies::wrap> subdivision = 1;

    DECL_VISIT(playmode, octavemode, note_length, subdivision);
  };

} // namespace otto::engines::arp
