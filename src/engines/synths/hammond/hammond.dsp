// Hammond-style organ with three drawbars and leslie emulation

import("stdfaust.lib");

process = hgroup("voices", vgroup("0", voice) + vgroup("3", voice) +
                           vgroup("1", voice) + vgroup("4", voice) +
                           vgroup("2", voice) + vgroup("5", voice)) :  _ ;

voice = hgroup("midi", (pipe0(midifreq), pipe1(midifreq), pipe2(midifreq), pipe3(midifreq), noise_att) :> modulator : *(envelope))
with {
  midigate	= button ("trigger");
  midifreq	= hslider("freq", 440, 20, 1000, 1);
  midigain	= hslider("velocity", 1, 0, 1, 1/127);

  //Voice definition
  drawbar1 = hslider("/drawbar1", 0.5, 0, 1, 0.01) : si.smoo;
  drawbar2 = hslider("/drawbar2", 0.5, 0, 1, 0.01) : si.smoo;
  drawbar3 = hslider("/drawbar3", 0.5, 0, 1, 0.01) : si.smoo;
  leslie = hslider("/leslie", 0.5, 0, 1, 0.01) : si.smoo;

  mastergain = 0.5;

  //Pitch modulation
  pitch_mod_amnt = 0.02; //Adjust to taste
  leslie_speed_tr = leslie*10;
  pitch_mod = pitch_mod_amnt*leslie*os.osc(leslie_speed_tr);

  pipe0(fr) = os.osc(fr*(1+pitch_mod));
  pipe1(fr) = os.osc(fr/2) : *(drawbar1);
  pipe2(fr) = os.osc(1.334839854*fr : *(1+pitch_mod) ) : *(drawbar2); //Perfect fifth above the fundamental
  pipe3(fr) = os.osc(2*fr : *(1+pitch_mod) ) : *(drawbar3);
  modulator = _ : attach(phasor) : *(mastergain) <: (fi.lowpass(2,center_freq), fi.highpass(2,center_freq)) : (*(1+os.osc(leslie_speed_tr)*(leslie_amnt_tr)) , *(1+os.osc(leslie_speed_bs)*(leslie_amnt_bs))) :> _
    with {

        leslie_speed_bs   = leslie*4;

        leslie_amnt_tr = leslie*(0.5);
        leslie_amnt_bs = leslie*(0.0);

        center_freq = 1800;

    };

  //Phasor
  phasor = os.lf_sawpos(leslie_speed_tr/2) : hbargraph("/phasor",0,1) ;

  noise_att = no.pink_noise : *(decay_env(0.02,ba.impulsify(midigate))) : *(0.05*leslie);


  //Decay envelope
  decay_env(d,t) = ba.countdown(decSamps,t) : /(decSamps)
  with{
          decSamps = ba.sec2samp(d);
  };

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
