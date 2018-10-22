/*
Black Hole Reverb for the OTTO -- By Jonatan Midtgaard
Adapted by with permission from the "OWLGAZER" modules by Xavier Godart (Empirical Noises).

To-Do:
- Perhaps adjust allpass values to be closer to freeverb?
- Add stereo spread. Are some delay lines for left/right?? Modulation for this?
- Look at shimmer. More modulation?
- Better tone control. More... dynamic? Reverb is very static at high decay rates.
- Being able to change number of AP filters. Few makes more of a metallic clang. 

*/

import("stdfaust.lib");

blackhole(mix,decay,hicut,pitchmix) =
    _ <:
    (
        _,_ <:
        (si.bus(N*2) :> networkline)~(feedbackline)
        :> fi.lowpass(2, hicut),fi.lowpass(2, hicut) : *(mix),*(mix) //Here are the lowpass filters. Perhaps move them or make another inside the reverb? 
    ),
    (*(1-mix),*(1-mix)) :>
    _
with {
    N = 8; //Number of comb filters
    earlyAPNb = 6; //Number of allpass filters.
    MAXDELAY = 8192;
      

    delays = (1356, 1422, 1557, 1617, 1933, 2401, 3125, 6561, 14641); //latereflections values (comb)
    delayval(i) = ba.take(i+1,delays) : *(time_lfo_late);
	time_lfo_late = os.osc(lfo_rate)*(lfo_strength_late) : +(1);
	//lfo_strength_late = hslider("LFO Late", 0.001, 0.0, 0.02,0.001);
	lfo_strength_late = 0.001;
	//lfo_rate = hslider("LFO Rate",1, 0.0, 10, 0.01);
	lfo_rate = 0.25;

	pitchshifter(delay, pitch, amount) = _ <: de.delay(MAXDELAY, delay)*(1-amount),(ef.transpose(delay,delay,pitch)*amount) :> _;
	  
    earlyreflections(i) = seq(j, earlyAPNb,
        fi.allpass_fcomb(2048, delayval(j+1), -allpassfb)
    )
    with{
        allpassfb = 0.6;
        delays = (243, 343, 441, 625, 727, 1331, 2403, 3119); //earlyreflections values (allpass)
	    time_lfo = os.osc(lfo_rate)*(lfo_strength) : +(1);
	    //lfo_strength = hslider("LFO Early", 0.003, 0.0, 0.02,0.001);
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
    ) : _,_,fi.highpass(2, 100),_,_,_,_,_;

    feedbackline = ro.hadamard(N) : par(i,N,(*(decay) : fi.lowpass(4, hicut) ));
};

blackhole_master = blackhole(mix,decay,hicut,pitchmix)
with {
    decay = hslider("LENGTH", 0.5, 0.05, 1.00, 0.01) : *(0.5) : +(0.5);
    hicut = hslider("SHAPE[scale:log]", 4000, 100, 14000, 0.01) :si.smoo;
    pitchmix = hslider("SHIMMER", 0.0, 0, 1.2, 0.01);
    mix = hslider("MIX", 0.5, 0, 1, 0.01);
};

process = _, _ :> blackhole_master <: _ , _ ;

