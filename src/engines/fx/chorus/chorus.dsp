import("stdfaust.lib");

voices = 8; // MUST BE EVEN
process = chorus_mono(dmax,curdel,rate,sigma,do2,voices);

dmax = 8192;
curdel = dmax * 0.1;
rateMax = 7.0; // Hz
rateMin = 0.01;
rate = hslider("rate", 0.5, 0, 1, 0.0001)*(rateMax) + rateMin
    : si.smoo;

depth = hslider("depth", 0.5, 0, 1, 0.001) : si.smoo;

delayPerVoice = 0.5*curdel/voices;
sigma = delayPerVoice * hslider("deviation", 0.5, 0, 1, 0.001) : si.smoo;

periodic = 1;

do2 = depth;   // use when depth=1 means "multivibrato" effect (no original => all are modulated)

chorus_mono(dmax,curdel,rate,sigma,do2,voices)
	= _ <: (*(1-do2)<:_,_),(*(do2) <: par(i,voices,voice(i)) :> _,_) : ro.interleave(2,2) : +,+
    with {
        angle(i) = 2*ma.PI*(i/2)/voices + (i%2)*ma.PI/2;
        voice(i) = de.fdelay(dmax,min(dmax,del(i))) * cos(angle(i));
        del(i) = curdel*(i+1)/voices + dev(i);
        rates(i) = rate/float(i+1);
        dev(i) = sigma * os.oscp(rates(i),i*2*ma.PI/voices);
};