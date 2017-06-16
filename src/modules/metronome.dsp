import("oscillators.lib");

// Faust screwed up so i copied the old version in here
ar(a,r,t) = ba.countup(attTime+relTime,on) : ba.bpf.start(0,0) :
	ba.bpf.point(attTime,1) : ba.bpf.end(attTime+relTime,0)
with{
	on = (t-t')==1;
	attTime = ma.SR*a;
	relTime = ma.SR*r;
};

gate = button("/TRIGGER");
tone = hslider("/TONE", 12, 0, 24, 1);
gain = hslider("/GAIN", 1, 0, 1, 0.01);

// ENVELOPE
att = 0.0000001;
rel = 0.09;

env = ar(att, rel, gate);

process = square(110 * 2^(tone/12)) * env * gain;