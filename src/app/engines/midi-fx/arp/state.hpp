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
    // This is only until we have a proper clock. Once we have that, we revert to subdivision
    util::StaticallyBounded<int, 20, 800> bpm = 480;
    // This is only untl we have a proper enginedispatcher
    bool active = false;

    DECL_VISIT(playmode, octavemode, note_length, subdivision, bpm, active);
  };

} // namespace otto::engines::arp
