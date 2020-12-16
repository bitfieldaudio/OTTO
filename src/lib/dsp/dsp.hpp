#pragma once

#include <algorithm>

#include <math.h>

#include "lib/logging.hpp"

namespace otto::dsp {

  // inline float semitone_to_detune(int st) {
  //  static std::array<float, 25> vals = util::generate_array<25>( [](int sts){ return pow(2.f, ((float)sts - 12.f)
  //  / 12.f); }); OTTO_ASSERT(st >= -12 && st <= 12, "Invalid input: {}", st); return vals[st + 12];
  //}

}
