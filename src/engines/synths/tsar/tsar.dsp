// An analog style synth with fewer features but hopefully more robust sound?

import("stdfaust.lib");

process = vgroup("voices", par(n, 6, vgroup("%n", voice))) :> VCF ;

voice = hgroup("midi", control(( multi_osc(osc1_freq, wave) , multi_osc(osc2_freq, wave), third_osc_send) :>  *(envelope), envelope>0.001))
with {
  midigate	= button ("trigger");
  midifreq	= hslider("freq", 440, 20, 1000, 1);
  midigain	= hslider("velocity", 1, 0, 1, 1/127);

  //Oscillators--------------------------
  wave = hslider("/Wave", 1, 0.08, 4, 0.01);
  //Waveform modifiers
  duty = ba.if(wave<1, 0.5 - 0.5*wave, 0.5) : si.smoo; //Duty cycle in the pulse wave
  osc_amount(w, pos) = max(0, min(-pos+(w : %(3))+1, pos-(w : %(3))+1)) : si.smoo;
  sq_amount(w) = max(0, max(1-(w : %(3)),(w : %(3))-2));

  multi_osc(frequency, w) = ( os.pulsetrainN(3,frequency, duty)*sq_amount(w) , os.triangle(frequency)*osc_amount(w,1)*(1.5) , os.sawN(3,frequency)*osc_amount(w,2) ) :> _ ;
  //-----------------------------------------------

  //Oscillator relations
  relation = hslider("/Relation", 0, 0, 1, 0.001) : si.smoo ;
  detune = relation *(0.3);

  semitone_up  = 0.05946309436;
  semitone_down = -0.05612568731;
  osc1_freq = midifreq*(1+detune*semitone_up);
  osc2_freq = midifreq*(1+detune*semitone_down);

  //Fourth knob
  Sub = hslider("/Sub", 0, 0, 1, 0.001) : si.smoo;
  sub_osc_send =  multi_osc(midifreq/(2),wave)*(1-Sub);
  high_osc_send =  multi_osc(midifreq*(2),wave)*(Sub);
  third_osc_send = high_osc_send+sub_osc_send ;


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

// Filter
flt = hslider("/Filter",0.5, 0, 1, 0.01);
fc = flt*flt*10000 + 100 : si.smoo;
Q = 1.25;
//VCF = fi.resonlp(fc,Q,0.5) : fi.resonlp(fc,Q,0.5);


	archsw = 1; // Use Biquads [tooltip: Select moog_vcf_2b (two-biquad) implementation, instead of the default moog_vcf (analog style) implementation]"))

	bqsw = 1; // Normalized Ladders [tooltip: If using biquads, make them normalized ladders (moog_vcf_2bn)]"));

	res = 0.1;

	vcfbq = _ <: select2(bqsw, ve.moog_vcf_2b(res,fc), ve.moog_vcf_2bn(res,fc));
	vcfarch = _ <: select2(archsw, ve.moog_vcf(res^4,fc), vcfbq);
    VCF = vcfarch;

