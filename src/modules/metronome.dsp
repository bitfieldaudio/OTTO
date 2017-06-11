import("oscillators.lib");
import("envelopes.lib");

gate = button("/TRIGGER");
tone = hslider("/TONE", 0.5, 0, 1, 0.01);
gain = hslider("/GAIN", 1, 0, 1, 0.01);

// ENVELOPE
att = 0.0000001;
rel = 0.09;

env = ar(att, rel, gate);

process = square(110 * 2^(tone*2)) * env * gain;