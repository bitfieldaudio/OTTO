// Vocoder. The excitation (carrier) is done by a simple poly sawtooth synth. The modulator is the audio input.

import("stdfaust.lib");

process = _ : (_ , hgroup("voices", vgroup("0", voice) + vgroup("3", voice) +
                           vgroup("1", voice) + vgroup("4", voice) +
                           vgroup("2", voice) + vgroup("5", voice))) :  vocoderModule : _ ;

//process = an.amp_follower(0.000001);

vocoderModule = _,_ <: (_ , _, *(mix), !) : (vocoder(16, 0.01, BWRatio),_) :> _;
//vocoderModule = (ef.gate_mono(-40+20*gating, 0.01, 0.0001 ,0.01) , _) :> _;

//att = hslider("/attTime", 0.5, 0, 1, 0.01) : si.smoo;
//rel = hslider("/decTime", 0.5, 0, 1, 0.01) : si.smoo;
mix = hslider("/mix", 0.5, 0, 1, 0.01) : si.smoo;
noiseamount = hslider("/noise",0,0,1,0.01)*(0.03) : si.smoo;
BWRatio = hslider("/ratio", 0.5, 0.1, 2, 0.01) : si.smoo;
gating = hslider("/gateamount", 0.5, 0, 1, 0.01) : si.smoo;

//Vocoder definition
oneVocoderBand(band,Qadjust, bandGain, x) = x : fi.resonbp(bandFreq,bandQ,bandGain) with{
        bandFreq = ba.take(band,voc_freqs);
        //BW = (bandFreq - 125*pow(2,(band)*(9/bandsNumb)))*bwRatio;
        //bandQ = bandFreq/BW;
        //bandQ = ba.take(band,bandQs) : *(0.5 + Qadjust);
        bandQ = 4.3185;
};

vocoder(nBands,speed,Qadjust,source,excitation) = source <: par(i,nBands,
    oneVocoderBand(i+1, Qadjust,1) : an.amp_follower(speed) : ef.gate_mono(-40+20*gating, 0.01, 0.0001 ,0.01) : *(ba.take(i+1,carrierTrim)) : _,excitation : oneVocoderBand(i+1,Qadjust) : *(ba.take(i+1,modulatorTrim)) ) :> _ ;

//voc_freqs = (50, 100, 200, 252, 317, 400, 504, 635, 800, 1008, 1270, 1600, 2016, 2504, 3200, 5032, 5080);
voc_freqs = (104.5, 179.5, 226, 284.5, 358.5, 452, 569.5, 717.5, 904, 1139, 1435, 1808, 2260, 2852, 3616, 4556);
//bandQs = (0.008, 0.05, 0.02, 0.03, 0.03, 0.03, 0.03, 0.04, 0.04, 0.04, 0.04, 0.04, 0.03, 0.05, 0.05, 0.05, 0.03);
bandQs = (0.001, 0.02, 0.02, 0.03, 0.03, 0.05, 0.04, 0.07, 0.04, 0.04, 0.1, 0.04, 0.05, 0.03, 0.05, 0.05, 0.3);
carrierTrim = (5, 5, 4, 1.5, 1.4, 1.3, 1.3, 1, 1.1, 1.2, 0.85, 1, 0.85, 0.95, 0.9, 0.85); //To equalise the carriers
modulatorTrim = (0.4, 0.85, 1.1, 1.35, 1.55, 1.8, 2, 2.25, 2.5, 2.75, 3.25, 3.5, 4.5, 4.5, 5, 5.25); //To equalise the modulators

voice = hgroup("midi", wave(midifreq) + no.noise*(noiseamount) : *(envelope))
with {
  midigate	= button ("trigger");
  midifreq	= hslider("freq", 440, 20, 1000, 1);
  midigain	= hslider("velocity", 1, 0, 1, 1/127);

  //Voice definition

  wave(freq) = os.saw2(freq)*0.2;
  //wave(freq) = os.square(freq)*0.2;

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
