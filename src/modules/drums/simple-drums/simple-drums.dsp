/****************************************/
/* The worlds simplest drum synthesizer */
/****************************************/

osc = library("oscillators.lib");
no = library("noises.lib");
fl = library("filters.lib");
en = library("envelopes.lib");

// ENVELOPE
att = vslider("/h:ENVELOPE/ATTACK", 0, 0, 2, 0.02);
sus = vslider("/h:ENVELOPE/SUSTAIN", 1, 0, 2, 0.02);
rel = vslider("/h:ENVELOPE/RELEASE", 0.2, 0, 2, 0.02);
gate = button("/TRIGGER");

env = sus * en.ar(0.001 + att, 0.001 + rel, gate);

drumOsc = (dOsc + n)  <: fl.resonlp(cutoff,resonance, 1) * filterOn, _ * (1-filterOn) :> +
  with {
    freq = hslider("FREQ", 500, 10, 500, 2.9);
    toneDec = hslider("TONE_DECAY",0.5, -1, 1, 0.01);
    noiseLVL = hslider("NOISE", 0.2, 0, 1, 0.01);
    cutoff = hslider("CUTOFF", 1000, 5, 10000, 0.001);
    filterOn = checkbox("FILTER_SWITCH");
    // SETTINGS
    resonance = 3;

    freqMod = 1 + (en.ar(0.0001, rel*abs(toneDec), gate) * toneDec : hbargraph("DECAY_GRAPH", -1, 1));

    dOsc = osc.square((freqMod) * freq) * (1 - noiseLVL);
    n = no.noise * noiseLVL;
  };
process = hgroup("ENVELOPE", env) * (vgroup("D1", drumOsc) + vgroup("D2", drumOsc) );