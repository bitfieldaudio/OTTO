//Front-panel controls are "Wave", "Filter", "Relation", "Aux", and the ADSR envelope.
// Bargraphs are "Bars" (for the bars on top of the UI, indicating the filter cutoff), and "Dots" (for the dots next to  
// POWER)

import("stdfaust.lib");

process = hgroup("voices", vgroup("0", voice) + vgroup("3", voice) +
                           vgroup("1", voice) + vgroup("4", voice) +
                           vgroup("2", voice) + vgroup("5", voice)) :  _ ;

voice = hgroup("midi", (multi_osc(osc1_freq)*(only_noise) , multi_osc(osc2_freq)*(only_noise) ) <: mixer :> VCF : *(envelope))
with {
  midigate	= button ("trigger");
  midifreq	= hslider("freq", 440, 20, 1000, 1);
  midigain	= hslider("velocity", 0.5, 0, 1, 1/127);
  // Filter
  flt = hslider("/Filter",20, 0, 99, 1) : si.smoo;
  dtri(x) = ( (x/(25)) , (2-(x/(25))) , (x-(50) : /(25)) , (4-(x/(25))) )  : ba.selectn(4, flt -(1) : /(99) : *(4) : floor : (int) ) : *(4.5) : hbargraph("/Bars",0,5);
  fc = dtri(flt)*(2222) : +(300);
  Q = flt : min(60) : max(40) : -(40) : /(20) : *(1.5) : +(1.0) : si.smoo;
  VCF = fi.resonlp(fc,Q,0.5) : fi.resonlp(fc,Q,0.5);
  //VCF =fi.resonhp(fc,Q,0.8) : fi.resonhp(fc,Q,0.5);


  //Oscillators--------------------------
  wave = hslider("/Wave", 0, 0, 4, 0.01) : si.smoo;
  //Waveform modifiers
  hardsync = wave : max(3) : -(3) : *(midifreq) : *(0.1); //Amount of hardsync of the saw-wave
  duty = wave*(0.5) : min(0.5); //Duty cycle in the pulse wave

  sq_amount = 2-(wave) : max(0) : min(1);
  saw_amount = wave-(2) : max(0) : min(1);
  tri_amount = 1-(sq_amount) : -(saw_amount);

  multi_osc(frequency) = ( os.pulsetrain(frequency, duty)*(sq_amount) , os.triangle(frequency)*(tri_amount)*(1.3) , saw2_own(frequency+(hardsync),clock)*(saw_amount) ) :> _
  with{
    clock = ba.pulse(ba.sec2samp(1/(frequency))); //Master osc. for hardsync
    phase(slave_freq,master_freq) = 2 * (os.hs_phasor(1<<16,slave_freq,master_freq)/(1<<16) ) - 1.0; //Zero-mean sawtooth
    saw2_own(slave_freq,master_freq) = phase(slave_freq,master_freq) <: * <: -(mem) : *(0.25'*ma.SR/slave_freq); //Hard-syncable anti-alialised saw
  };
  //-----------------------------------------------

  //Oscillator relations
  relation = hslider("/Relation", 2, 0, 3.001, 0.001) : *(2) : hbargraph("/Dots",0,6) : /(2) : si.smoo ;
  detune_amount = (1, (relation-2.1 :*(0.0594) : +(1.0)), (1-relation : *(0.0594) : +(1.0) ) ) : (max, _) : max ;
  detune = ba.if( (relation == 0) + (relation >= 3) , 1, detune_amount);

  mixer = (_,_,_,_) <: (_,_,_,!,!,!,_,_) : ((+ : *(relation >= 2)), *(1-(octave)) , (* : *(octave))) : (_, (+ : *(relation<2)), third_osc_send, noise_send )  ;
  octave = 2-relation : max(0) : min(1);
  detune_osc2 = 1.0/(detune);

  fifth = ba.if( (relation >= 3) , 1.49830, 1 ); //A fifth is seven semitones above
  osc1_freq = midifreq*detune;
  osc2_freq = midifreq*(detune_osc2) : *(fifth);

  //Fourth knob
  aux = hslider("/Aux", 0, 0, 3, 0.001) : si.smoo;
  noise_amount = (1-aux, 0) : max;
  noise_send = no.noise*(noise_amount);
  tonic_osc_amount = ba.if(aux <= 1, aux, 2-aux) : max(0);
  tonic_osc_send = multi_osc(midifreq)*(tonic_osc_amount);
  sub_osc_amount = (0, aux-2) : max;
  sub_osc_send =  multi_osc(midifreq/(2))*(sub_osc_amount);
  third_osc_send = tonic_osc_send+sub_osc_send;
  only_noise = 1-(aux<=0.01);

  //ADSR envelope----------------------------
  envelope = en.adsre(a,d,s,r,midigate) * midigain;
  a = hslider("/v:envelope/Attack", 0.001, 0.001, 4, 0.001);
  d = hslider("/v:envelope/Decay", 0.0, 0.0, 4, 0.001);
  s = hslider("/v:envelope/Sustain", 1.0, 0.0, 1.0, 0.01) * 100;
  r = hslider("/v:envelope/Release", 0.0, 0.0, 4.0, 0.01);
};
