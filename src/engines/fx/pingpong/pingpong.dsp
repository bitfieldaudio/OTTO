import("stdfaust.lib");
									 
/* ============ DESCRIPTION =============

- Variable delay effect. Front-panel controls are:
	- Delay Time (hslider) = Amount of time for delay
	- bpmFollow (checkbox) = Changes function of Delay Time between milliseconds and BPM subdivision
	- Feedback (hslider) = Amount of feedback
	- freq (hslider) = Adjust the center frequency of the bandpass filter on the delays ("Tone")
	- Spread (slider. Turned all the way up, it engages ping-pong)

TO-DO: 
- Insert flanger. Spread should modulate amount in some way.
- make bargraph-thing that indicates hit. Sawtooth-wave or something
*/



//Controls
//BPM = hbargraph("/bpm",1,400); // NOTE: Should be removed and replaced by some variable so Faust knows what the BPM is...
BPM = 120;
delaySlider = hslider("/delaytime", 0.5, 0.01, 0.999, 0.001):min(1):max(0.01); // We need to settle on a scale. Is it 1 to 99? Right now, it is in units of seconds when bpmFollow==0.
bpmFollow = checkbox("/bpm_follow");
feedback = hslider("/feedback", 0.5, 0, 1, 1);
freq = hslider("/tone", 0.5, 0, 1, 0.01)*freqScale+freq_lower :si.smoo;
spreadSlider = hslider("/spread", 0, 0, 1, 0.01);

//Constants
spreadScale = 1000;
freqScale = 1900;
freq_lower = 100;

process = _,_ : echo : (levelOutputBlock, _) ;

//Routing
echoIN = _,_  <: _,_,_, si.block(1) : *(1-pp), *(pp),_ : _,ro.cross(2) : _,_,_ ; //In: L,R -- Out: L_i, R_i, L_pp	

echoOUT = _,_,_: _,ro.cross(2) : +,_ ;									 									 
plusblock =  _,_,_,_ : _,ro.cross(2),_ : +,+: _,_  ; //In: 2 FX return, L_i, R_i -- Out: L_f, R_f

echo = echoIN : plusblock ~ tape ,_ : echoOUT ;
									 
									 
//Making the magnetic tape
tape = _,_ : delay <:  ro.cross(2),_,_ : ba.select2stereo(1-pp) : proc : _,_ ;

delay = _,_ : @(delayTime+spread*(1-pp)), @(delayTime) : _,_;
proc = _,_ : *(feedback),*(feedback) : ef.transpose(250,50,tpAmount),ef.transpose(250,50,tpAmount)  : lp, lp : _,_;
									 
//DelayTime
echoDelay = delaySlider*(ma.SR):int;
tempo = 60*ma.SR/BPM*subdivision; //This should instead access a BPM variable from the metronome...
delayTime = (bpmFollow, echoDelay, tempo) : select2;
									 
//Subdivision
aux1 = delaySlider*(4) : ceil;
subdivision = aux1 , 4 : / ;
									 							 
//Tape-effect with pitchshifting
integrator = delayTime <: ( @(delayTime), _ ) : -;
tpAmount = integrator*12 / delayTime :si.smooth(0.999);
									 						 
//Bandpass filter
lp = _:fi.resonbp(freq,1,1):_;
									 
//Stereo Spread
spread = spreadSlider*(spreadScale):int;

//Ping-Pong
pp = spreadSlider==1;

//Level output for graphics
levelOutputBlock =  _ <: attach(_, an.amp_follower(0.01) <: par(t, 10, @(t*delayTime/10 : int) : hbargraph("/v:delayline%t/level",0,5)) :> _) ;
