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
delaySlider = hslider("/delaytime", 0.5, 0.01, 0.999, 0.001):min(1):max(0.01);
bpmFollow = checkbox("/bpm_follow");
feedback = hslider("/feedback", 0.5, 0, 1, 1);
freq = hslider("/tone", 0.5, 0, 1, 0.01)*freqScale+freq_lower :si.smoo;
spreadSlider = hslider("/spread", 0, 0, 1, 0.01);

//Constants
spreadScale = 1000;
freqScale = 1900;
freq_lower = 100;

process = levelOutputBlock <: echo : (_, _) ;

//Routing
echoIN = _,_  <: _,_,_, si.block(1) : *(1-pp), *(pp),_ : _,ro.cross(2) : _,_,_ ; //In: L,R -- Out: L_i, R_i, L_pp	

echoOUT = _,_,_: _,ro.cross(2) : +,_ ;									 									 
plusblock =  _,_,_,_ : _,ro.cross(2),_ : +,+: _,_  ; //In: 2 FX return, L_i, R_i -- Out: L_f, R_f

echo = echoIN : plusblock ~ tape ,_ : echoOUT ;
									 
									 
//Making the magnetic tape
tape = _,_ : delay <:  ro.cross(2),_,_ : ba.select2stereo(1-pp) : proc : chorusblock : _,_ ;

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
lp = _:fi.resonbp(freq,1, 0.8):_; //last argument is Q. Low for a broad filter, high for a narrow filter
									 
//Stereo Spread (on top half of slider)
spread = 2*(spreadSlider-0.5 : max(0))*(spreadScale):int;

//Ping-Pong
pp = spreadSlider==1;

//Level output for graphics
levelOutputBlock =  _ <: attach(_, an.amp_follower(0.2) <: par(t, 20, @(t*delayTime : int) : hbargraph("/v:delayline%t/level",0,5)) :> _) ;

//Chorus (on bottom half of slider)
/*
chorusblock = (left, right)
with {
	left		= chorus(dtime,chorusfreq,depth,0);
	right		= chorus(dtime,chorusfreq,depth,ma.PI/2);
};

level	= depth;
chorusfreq	= depth*0.5;
dtime	= 0.2;
depth	= 2*(0.5-spreadSlider) : max(0);

tblosc(n,f,chorusfreq,mod)	= (1-d)*rdtable(n,wave,i&(n-1)) +
			  d*rdtable(n,wave,(i+1)&(n-1))
with {
	wave	 	= ba.time*(2.0*ma.PI)/n : f;
	phase		= chorusfreq/ma.SR : (+ : ma.decimal) ~ _;
	modphase	= ma.decimal(phase+mod/(2*ma.PI))*n;
	i		= int(floor(modphase));
	d		= ma.decimal(modphase);
};

chorus(dtime,chorusfreq,depth,phase,x)
			= x+level*de.fdelay(1<<16, t, x)
with {
	t		= ma.SR*dtime/2*(1+0.5*depth*tblosc(1<<16, sin, chorusfreq, phase));
};
*/
//Second attempt
voices = 4; // MUST BE EVEN
chorusblock = (left, right)
with {
	left		= chorus_mono(dmax,curdel,rate,sigma,do2,voices);
	right		= chorus_mono(dmax,curdel,rate,sigma,do2,voices);
};

dmax = 8192;
curdel = dmax * 0.5;

rate = depth * 7;

depth = (0.5-spreadSlider) : max(0);

delayPerVoice = 0.5*curdel/voices;
sigma = delayPerVoice * 0.3;

periodic = 1;

do2 = depth;   // use when depth=1 means "multivibrato" effect (no original => all are modulated)

chorus_mono(dmax,curdel,rate,sigma,do2,voices)
	= _ <: (*(1-do2)<:_,_),(*(do2) <: par(i,voices,voice(i)) :> _,_) : ro.interleave(2,2) : +,+ : +
    with {
        angle(i) = 2*ma.PI*(i/2)/voices + (i%2)*ma.PI/2;
        voice(i) = de.fdelay(dmax,min(dmax,del(i))) * cos(angle(i));
        del(i) = curdel*(i+1)/voices + dev(i);
        rates(i) = rate/float(i+1);
        dev(i) = sigma * os.oscp(rates(i),i*2*ma.PI/voices);
};