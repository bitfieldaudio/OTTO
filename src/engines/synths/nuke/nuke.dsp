// An analog style synth with ringmod and hardsync. This contains the code for the OTTO ADSR-envelope (exponential, but with arbitrary attack. Here it is linear.)
// A TO-DO is to add this to a dedicated faust library instead.

import("stdfaust.lib");

process = hgroup("voices", vgroup("0", voice) + vgroup("3", voice) +
                           vgroup("1", voice) + vgroup("4", voice) +
                           vgroup("2", voice) + vgroup("5", voice)) :  _ ;

voice = hgroup("midi", ( multi_osc(osc1_freq) , multi_osc(osc2_freq) ) <: mixer :> VCF : *(envelope))
//voice = hgroup("midi", envelope)
with {
  midigate	= button ("trigger");
  midifreq	= hslider("freq", 440, 20, 1000, 1);
  midigain	= hslider("velocity", 0.5, 0, 1, 1/127);

  // Filter
  flt = hslider("/Filter",0.5, 0, 1, 0.01) : si.smoo;
  fc = flt*flt*10000 + 100;
  Q = 1.25;
  VCF = fi.resonlp(fc,Q,0.5) : fi.resonlp(fc,Q,0.5);


  //Oscillators--------------------------
  wave = hslider("/Wave", 1, 0.08, 4, 0.01) : si.smoo;
  //Waveform modifiers
  hardsync = wave : max(3) : -(3) : *(midifreq) : *(0.1); //Amount of hardsync of the saw-wave
  duty = wave*(0.5) : min(0.5); //Duty cycle in the pulse wave

  sq_amount = 2-(wave) : max(0) : min(1);
  saw_amount = wave-(2) : max(0) : min(1);
  tri_amount = 1-(sq_amount) : -(saw_amount);

  multi_osc(frequency) = ( os.pulsetrain(frequency, duty)*(sq_amount) , os.triangle(frequency)*(tri_amount)*(1.5) , saw2_own(frequency+(hardsync),clock)*(saw_amount) ) :> _
  with{
    clock = ba.pulse(ba.sec2samp(1/(frequency))); //Master osc. for hardsync
    phase(slave_freq,master_freq) = 2 * (os.hs_phasor(1<<16,slave_freq,master_freq)/(1<<16) ) - 1.0; //Zero-mean sawtooth
    saw2_own(slave_freq,master_freq) = phase(slave_freq,master_freq) <: * <: -(mem) : *(0.25'*ma.SR/slave_freq); //Hard-syncable anti-alialised saw
  };
  //-----------------------------------------------

  //Oscillator relations
  relation = hslider("/Relation", 2, 0, 3.001, 0.001) : *(2) : /(2) : si.smoo ;
  detune_amount = (1, (relation-2.1 :*(0.02) : +(1.0)), (1-relation : *(0.02) : +(1.0) ) ) : (max, _) : max ;
  detune = ba.if( (relation == 0) + (relation >= 3) , 1, detune_amount);

  mixer = (_,_,_,_) <: (_,_,_,!,!,!,_,_) : ((+ : *(relation >= 2)), *(1-(octave)) , (* : *(octave))) : (_, (+ : *(relation<2)), third_osc_send)  ;
  octave = 2-relation : max(0) : min(1);
  detune_osc2 = 1.0/(detune);

  fifth = ba.if( (relation >= 3) , 1.49830, 1 ); //A fifth is seven semitones above
  osc1_freq = midifreq*detune;
  osc2_freq = midifreq*(detune_osc2) : *(fifth);

  //Fourth knob
  Sub = hslider("/Sub", 0, 0, 1, 0.001) : si.smoo;
  tonic_osc_send = multi_osc(midifreq)*(1-Sub);
  sub_osc_send =  multi_osc(midifreq/(2))*(Sub);
  third_osc_send = tonic_osc_send+sub_osc_send;


  //ADSR envelope----------------------------
  envelope = adsre_min(a,d,s,r,midigate)*(midigain);
  a = hslider("/v:envelope/Attack", 0.001, 0.001, 4, 0.001);
  d = hslider("/v:envelope/Decay", 0.0, 0.0, 4, 0.001);
  s = hslider("/v:envelope/Sustain", 1.0, 0.0, 1.0, 0.01);
  r = hslider("/v:envelope/Release", 0.0, 0.0, 4.0, 0.01);

  adsre_min(attT60,decT60,susLvl,relT60,gate) = envel
  with {
  ugate = gate>0;
  samps = ugate : +~(*(ugate)); // ramp time in samples
  attSamps = int(attT60 * ma.SR);
  attLvl = samps/attSamps; //The function for the attack phase. Should go from 0-1 in attSamps samples.
  target = select2(ugate, 0.0,
           select2(samps<attSamps, (susLvl)*float(ugate), attLvl)); //In the attack phase the target moves up following attLvl
  t60 = select2(ugate, relT60, select2(samps<attSamps, decT60, 0.0000001)); //Instead of attT60, we choose some very small number, such that there is virtually no smoothing in the attack phase
  pole = ba.tau2pole(t60/6.91);
  envel = target : si.smooth(pole);
  };
};
