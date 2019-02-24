// A wavetable synth with remapping

import("stdfaust.lib");

process = vgroup("voices", par(n, 6, vgroup("%n", voice))) :> _ ;

voice = hgroup("midi", control( (wt_output : *(envelope)), envelope>0.001))
with {
  midigate	= button ("trigger");
  midifreq	= hslider("freq", 440, 20, 1000, 1);
  midigain	= hslider("velocity", 1, 0, 1, 1/127);

  osc1vol = hslider("/osc1/volume", 1, 0, 1, 0.1);
  osc2vol = hslider("/osc2/volume", 1, 0, 1, 0.1);

  osc1remap_amt = hslider("/osc1/remap_amt", 0, 0, 1, 0.1);
  osc2remap_amt = hslider("/osc2/remap_amt", 0, 0, 1, 0.1);

  wt_output = osc1vol * osc1out;

  osc1out = 1;

  tablesize 	= hslider("/osc1/numSamples", 600, 1, 1000, 1) : int;
  samplingfreq	= ma.SR;

  time 		= (+(1)~_ ) - 1; 			// 0,1,2,3,...
  sinwaveform 	= float(time)*(2.0*PI)/float(tablesize) : sin;

  decimal(x)	= x - floor(x);
  bare_idx(freq) 	= freq/float(samplingfreq) : (+ : decimal) ~ _ : *(float(tablesize));

  osc1idx(freq) = bare_idx(freq) : int ;
  waveosc(freq) = rdtable(tablesize, sinwaveform, idx(freq) );


  //ADSR envelope----------------------------
  envelope = adsre_OTTO(a,d,s,r,midigate)*(midigain);
  a = hslider("/v:envelope/Attack", 0.001, 0.001, 4, 0.001);
  d = hslider("/v:envelope/Decay", 0.0, 0.0, 4, 0.001);
  s = hslider("/v:envelope/Sustain", 1.0, 0.0, 1.0, 0.01);
  r = hslider("/v:envelope/Release", 0.0, 0.0, 4.0, 0.01);

  adsre_OTTO(attT60,decT60,susLvl,relT60,gate) = envel
  with {
    ugate = gate>0;
    samps = ugate : +~(*(ugate)); // ramp time in samples
    attSamps = int(attT60 * ma.SR);
    target = select2(ugate, 0.0,
             select2(samps<attSamps, (susLvl)*float(ugate), 1/0.63));
    t60 = select2(ugate, relT60, select2(samps<attSamps, decT60, attT60*6.91));
    pole = ba.tau2pole(t60/6.91);
    envel = target : si.smooth(pole) : min(1.0);
  };

};
