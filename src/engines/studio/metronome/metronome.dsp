osc = library("oscillators.lib");
en = library("envelopes.lib");

gate = button("/TRIGGER");
tone = hslider("/TONE", 12, 0, 24, 1);
gain = hslider("/GAIN", 1, 0, 1, 0.01);

// ENVELOPE
att = 0.0000001;
rel = 0.09;

env = en.ar(att, rel, gate);

process = osc.square(110 * 2^(tone/12)) * env * gain;