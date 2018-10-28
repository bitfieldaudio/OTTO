// A full DX-motherfucking-7
// What should the controls be?
//Brainstorm:
//Operator frequencies (chaotic, has to be tuned),
//Envelope rates (faster, slower. But should have some starting point. But this could be controlled from the envelope)
//Algorithm
//Feedback
//Operator detune?

import("stdfaust.lib");

process = hgroup("voices", vgroup("0", voice) + vgroup("3", voice) +
                           vgroup("1", voice) + vgroup("4", voice) +
                           vgroup("2", voice) + vgroup("5", voice)) :  _ ;

voice =hgroup("midi", out :*(envelope))
with {
  midigate	= button ("trigger");
  midifreq	= hslider("freq", 440, 20, 1000, 1);
  midigain	= hslider("velocity", 1, 0, 1, 1/127);

  //Voice definition
  preset = hslider("/preset", 0, 0, 99, 1);
  variable1 = hslider("/variable1", 0.5, 0, 1, 0.01) : si.smoo;
  variable2 = hslider("/variable2", 0.5, 0, 1, 0.01) : si.smoo;
  variable3 = hslider("/variable3", 0.5, 0, 1, 0.01) : si.smoo;

  algN = hslider("/algN", 0, 0 ,31, 1) : int;

  out = par(i, 32, control( dx.dx7_algo(i,egR1,egR2,egR3,egR4,egL1,egL2,egL3,egL4,outLevel,keyVelSens,ampModSens,opMode,opFreq,opDetune,opRateScale,feedback,0,0,0,midifreq,midigain,midigate) , algN==i)) :> _;

  egR1UI = par(i,6, hslider("/egR1_%i", 1, 0, 99, 1)); //Creates 6 different variables to hook into. egR1_0, egR1_1, etc. Where the last index refers to the operator and is 0-indexed.
  egR2UI = par(i,6, hslider("/egR2_%i", 1, 0, 99, 1));
  egR3UI = par(i,6, hslider("/egR3_%i", 1, 0, 99, 1));
  egR4UI = par(i,6, hslider("/egR4_%i", 1, 0, 99, 1));
  egL1UI = par(i,6, hslider("/egL1_%i", 1, 0, 99, 1));
  egL2UI = par(i,6, hslider("/egL2_%i", 1, 0, 99, 1));
  egL3UI = par(i,6, hslider("/egL3_%i", 1, 0, 99, 1));
  egL4UI = par(i,6, hslider("/egL4_%i", 1, 0, 99, 1));
  egR1(n) = ba.take(n+1, egR1UI);
  egR2(n) = ba.take(n+1, egR2UI);
  egR3(n) = ba.take(n+1, egR3UI);
  egR4(n) = ba.take(n+1, egR4UI);
  egL1(n) = ba.take(n+1, egL1UI);
  egL2(n) = ba.take(n+1, egL2UI);
  egL3(n) = ba.take(n+1, egL3UI);
  egL4(n) = ba.take(n+1, egL4UI);

    //egR1UI = (96, 95, 95, 95, 95, 95);
    //egR2UI = (25, 50, 20, 29, 20, 29);
    //egR3UI = (25, 35, 20, 20, 20, 20);
    //egR4UI = (67, 78, 50, 50, 50, 50);
    //egL1UI = (99, 99, 99, 99, 99, 99);
    //egL2UI = (75, 75, 95, 95, 95, 95);
    //egL3UI = (0, 0, 0, 0, 0, 0);
    //egL4UI = (0, 0, 0, 0, 0, 0);
    //outLevelUI = (99, 58, 99, 89, 99, 79);
    //keyVelSensUI = (2,7,2,6,0,6);
    //ampModSensUI = (0,0,0,0,0,0);
    //opModeUI = (0,0,0,0,0,0);
    //opFreqUI = (1, 14, 1, 1, 1, 1);
    //opDetuneUI = (3, 0, 0, 0, -7, 7);
    //opRateScaleUI = (3, 3,3, 3, 3, 3);
    //feedback = 6;

  outLevelUI = par(i,6, hslider("/outLevel_%i", 99, 0, 99, 1));
  outLevel(n) = ba.take(n+1, outLevelUI);
  keyVelSensUI = par(i,6, hslider("/keyVelSens_%i", 99, 0, 99, 1));
  keyVelSens(n) = ba.take(n+1, keyVelSensUI);
  ampModSensUI = par(i,6, hslider("/ampModSens_%i", 99, 0, 99, 1));
  ampModSens(n) = ba.take(n+1,ampModSensUI);
  opModeUI = par(i,6, hslider("/opMode_%i", 0, 0, 1, 1) : int ); //0 is ratio, 1 is fixed frequency (Perhaps it should  be cast as int)
  opMode(n) = ba.take(n+1, opModeUI);
  opFreqUI = par(i,6, hslider("/opFreq_%i", 1, 0, 99, 1));
  opFreq(n) = ba.take(n+1,opFreqUI);
  opDetuneUI = par(i,6, hslider("/opDetune_%i", 0, -7, 7, 1));
  opDetune(n) = ba.take(n+1,opDetuneUI);
  opRateScaleUI = par(i,6, hslider("/opRateScale_%i", 3, 0, 99, 1)); //Might also be called the 'keyboardRateScaling'.
  opRateScale(n) = ba.take(n+1,opRateScaleUI);
  feedback = hslider("/feedback", 0, 0, 99, 1); //Only one operator has feedback in each algo


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
