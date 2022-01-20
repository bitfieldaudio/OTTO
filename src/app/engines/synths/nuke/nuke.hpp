#pragma once

#include "lib/util/local_vector.hpp"
#include "lib/util/visitor.hpp"
#include "lib/util/with_limits.hpp"

#include "lib/audio.hpp"
#include "lib/engine.hpp"
#include "lib/engines/synthdispatcher/synthdispatcher.hpp"
#include "lib/graphics.hpp"
#include "lib/midi.hpp"

#include "app/services/graphics.hpp"

#include "state.hpp"

using namespace otto;

namespace otto::engines::nuke {

  enum class LfoShapes { constant, up, down, tri, sqr, sine, C2, S5 };

  std::unique_ptr<ILogic> make_logic(itc::Context&);
  ScreenWithHandler make_main_screen(itc::Context&);
  ScreenWithHandler make_mod_screen(itc::Context&);
  ScreenWithHandler make_voices_screen(itc::Context&);
  std::unique_ptr<ISynthAudio> make_audio(itc::Context&);

  // NOLINTNEXTLINE
  inline SynthEngineFactory factory = {
    ._metadata = {.name = "ANALOGUE"},
    .make_logic = make_logic,
    .make_audio = make_audio,
    .make_mod_screen = make_mod_screen,
    .make_main_screen = make_main_screen,
    .make_voices_screen = make_voices_screen,
  };

  // Functions shared between graphics and audio
  // Duration of an envelope stage in seconds from underlying state member
  inline float envelope_stage_duration(const float d)
  {
    return 5 * d * d + 0.001f;
  }
} // namespace otto::engines::nuke
