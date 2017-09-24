ba = library("basics.lib");
osc = library("oscillators.lib");
no = library("noises.lib");
fl = library("filters.lib");
en = library("envelopes.lib");

clamp(f, mn, mx) = select2(f > mx, select2(f < mn, f, mn), mx);

// ENVELOPE
att = vslider("/h:ENVELOPE/ATTACK", 0, 0, 2, 0.02);
dec = vslider("/h:ENVELOPE/DECAY", 0, 0, 2, 0.02);
sus = vslider("/h:ENVELOPE/SUSTAIN", 1, 0, 1, 0.01);
rel = vslider("/h:ENVELOPE/RELEASE", 0.2, 0, 2, 0.02);

gate = button("/TRIGGER");
velocity = hslider("/VELOCITY", 1, 0, 1, 0.01);
key = hslider("/KEY", 69, 0, 127, 0.1);

filter = hslider("/FILTER", 1, 10, 15000, 10);
detune = hslider("/DETUNE", 0, 0, 1, 0.01);
voices = hslider("/VOICES", 1, 1, 4, 0.01);

baseFRQ = ba.midikey2hz(key);

env = en.adsr(att, dec, sus * 100, rel, gate);
vdtune = (0, 1, -1, 0);
voice(oct) = osc.sawtooth(freq) : fl.resonlp(cutoff, res, 1) with {
  freq = baseFRQ / 2^oct * (1 + dtune);
  cutoff = filter * velocity;
  res = 8 * (1.125 - filter / 15000);
  dtune = ba.take(oct + 1, vdtune) * detune * 1/24;
};

v1 = clamp(voices    , 0, 1) * voice(0);
v2 = clamp(voices - 1, 0, 1) * voice(1);
v3 = clamp(voices - 2, 0, 1) * voice(2);
v4 = clamp(voices - 3, 0, 1) * voice(3);

process = (v1 + v2 + v3 + v4) * hgroup("ENVELOPE", env);