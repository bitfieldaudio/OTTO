// Vocoder. The excitation (carrier) is done by a simple poly sawtooth synth. The modulator is the audio input.

import("stdfaust.lib");

process = _ : (_ , hgroup("voices", vgroup("0", voice) + vgroup("3", voice) +
                           vgroup("1", voice) + vgroup("4", voice) +
                           vgroup("2", voice) + vgroup("5", voice))) :  vocoderModule : _ ;

//process = an.amp_follower(0.000001);

vocoderModule = _,_ : (ef.gate_mono(-40+20*gating, 0.01, 0.0001 ,0.01) , _) : ve.vocoder(28,att,rel,BWRatio);
//vocoderModule = (ef.gate_mono(-40+20*gating, 0.01, 0.0001 ,0.01) , _) :> _;

att = hslider("/attTime", 0.5, 0, 1, 0.01) : si.smoo;
rel = hslider("/decTime", 0.5, 0, 1, 0.01) : si.smoo;
BWRatio = hslider("/ratio", 0.1, 0.1, 2, 0.01) : si.smoo;
gating = hslider("/gateamount", 0.5, 0, 1, 0.01) : si.smoo;

//Vocoder definition
oneVocoderBand(band,bandsNumb,bwRatio,bandGain,x) = x : fi.resonbp(bandFreq,bandQ,bandGain) with{
        bandFreq = 125*pow(2,(band+1)*(9/bandsNumb));
        BW = (bandFreq - 125*pow(2,(band)*(9/bandsNumb)))*bwRatio;
        bandQ = bandFreq/BW;
};

vocoder(nBands,att,rel,BWRatio,source,excitation) = source <: par(i,nBands,oneVocoderBand(i,nBands,BWRatio,1) :
an.amp_follower(0.001) : _,excitation : oneVocoderBand(i,nBands,BWRatio)) :> _ ;

voice = hgroup("midi", wave(midifreq) : *(envelope))
with {
  midigate	= button ("trigger");
  midifreq	= hslider("freq", 440, 20, 1000, 1);
  midigain	= hslider("velocity", 1, 0, 1, 1/127);

  //Voice definition

  wave(freq) = os.saw2(freq)*0.2;

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
