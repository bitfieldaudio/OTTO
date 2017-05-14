#include "midi.h"
#include <cmath>

namespace midi {

float freqTable[128];

void generateFreqTable(float tuning) {

  for (int i = 0; i < 128; i++) {
    freqTable[i] = tuning * std::pow(2, float(i - 69)/float(12));
  }
}
}
