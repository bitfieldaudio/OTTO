declare name "TestSynth";

import("oscillators.lib");

freq = osci(0.1) * 200 + vslider("FREQ", 440, 60, 900, 0.0001);

process = osci(freq);