/*
Black Hole Reverb for the OTTO -- By Jonatan Midtgaard
Adapted by with permission from the "OWLGAZER" modules by Xavier Godart (Empirical Noises).

To-Do:
- Perhaps adjust allpass values to be closer to freeverb?
- Add stereo spread. Are some delay lines for left/right?? Modulation for this?
- Look at shimmer. More modulation?
- Being able to change number of AP filters. Few makes more of a metallic clang. 

*/

import("stdfaust.lib");

blackhole(decay,shape,pitchmix,spread) =
    _ <:
    (
        (si.bus(N*2) :> networkline)~(feedbackline)
    ) : si.bus(N) <: (par(i, N, *(1-spread)), (ro.cross(N) : par(i,N,*(1+spread))))
    :> ef.gate_stereo(gate_amount*64-60,0.001,0.01,0.04)
with {
    N = 4; //Number of comb filters
    earlyAPNb = 4; //Number of allpass filters.
    hicut = 10000;
    MAXDELAY = 8192;
    gate_amount = (shape-1) : max(0);
    duck_amount = (1-shape) : max(0);
      

    //delays = (1356, 1422, 1557, 1617, 1933, 2401, 3125, 6561, 14641); //latereflections values (comb)
    delays = (1422, 1617, 2401, 6561);
    delayval(i) = ba.take(i+1,delays) : *(time_lfo_late);
	time_lfo_late = os.osc(lfo_rate)*(lfo_strength_late) : +(1);
	lfo_strength_late = 0.001;
	lfo_rate = 0.25;

	pitchshifter(delay, pitch, amount) = _ <: de.delay(MAXDELAY, delay)*(1-amount),(ef.transpose(delay,delay,pitch)*amount) :> _;
	  
    earlyreflections(i) = seq(j, earlyAPNb, fi.allpass_fcomb(2048, delayval(j+1), -allpassfb))
    with{
        allpassfb = 0.6;
        //delays = (243, 343, 441, 625, 727, 1331, 2403, 3119); //earlyreflections values (allpass)
        delays = (243, 441, 727, 2403, 3119);
	    time_lfo = os.osc(lfo_rate)*(lfo_strength) : +(1);
	    lfo_strength = 0.001;
        delayval(x) = ba.take(x+1, delays) : *(time_lfo);
    };

    latereflections(i) = _ <:
            de.fdelay(MAXDELAY, delayval(i))*(i!=3),
            pitchshifter(MAXDELAY + delayval(i),12,pitchmix)*(i==3) :>
        _;

    networkline = par(i,N,
        _ :
        earlyreflections(i) :
        latereflections(i) :
        _/sqrt(N)
    ) : _,_,fi.highpass(2, 100),_;

    feedbackline = ro.hadamard(N) : par(i,N,(*(decay) : fi.lowpass(2, hicut) ));
};

blackhole_master = blackhole(decay,shape,pitchmix,spread)
with {
    decay = hslider("LENGTH", 0.5, 0.0, 1.50, 0.01) :si.smoo ;
    shape = hslider("SHAPE[scale:log]", 1, 0, 2, 0.01) :si.smoo;
    pitchmix = hslider("SHIMMER", 0.0, 0, 1.2, 0.01);
    spread = hslider("SPREAD", 0, 0, 1, 0.01) : si.smoo;
};

process = _ : blackhole_master : _ , _ ;

