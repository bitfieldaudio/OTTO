declare name "TestSynth";

import("oscillators.lib");

freq = vslider("FREQ", 440, 60, 900, 0.0001);

process = osci(freq);