declare name "TestSynth";

import("oscillators.lib");

freq = osci(0.1) * 200 + 440;

process = osci(freq);