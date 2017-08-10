ba = library("basics.lib");
osc = library("oscillators.lib");
no = library("noises.lib");
fl = library("filters.lib");
en = library("envelopes.lib");

// ENVELOPE
att = vslider("/h:ENVELOPE/ATTACK", 0, 0, 2, 0.02);
dec = vslider("/h:ENVELOPE/DECAY", 0, 0, 2, 0.02);
sus = vslider("/h:ENVELOPE/SUSTAIN", 1, 0, 1, 0.01);
rel = vslider("/h:ENVELOPE/RELEASE", 0.2, 0, 2, 0.02);

gate = button("/TRIGGER");
velocity = vslider("/VELOCITY", 1, 0, 1, 0.01);
key = vslider("/KEY", 69, 0, 127, 1);

freq = ba.midikey2hz(key);

env = en.adsr(att, dec, sus * 100, rel, gate);

cutoff = 4000;

voice = osc.saw(freq) : fl.resonlp(freq * (1 + env * velocity), 8, 1);

process = voice * hgroup("ENVELOPE", env);