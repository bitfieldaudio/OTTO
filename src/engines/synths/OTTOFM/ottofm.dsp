//An FM synth. Adapted for OTTO, by OTTO.

import("stdfaust.lib");

process = hgroup("voices", vgroup("0", voice) + vgroup("3", voice) +
                           vgroup("1", voice) + vgroup("4", voice) +
                           vgroup("2", voice) + vgroup("5", voice)) :  _ ;

voice = hgroup("midi", out)
with {
  midigate	= button ("trigger");
  midifreq	= hslider("freq", 440, 20, 1000, 1);
  midigain	= hslider("velocity", 1, 0, 1, 1/127);

  //Voice definition
  algN = hslider("/algN", 0, 0 ,11, 1) : int;



  //ADSR envelope----------------------------
  a = hslider("/v:envelope/Attack", 0.001, 0.001, 4, 0.001);
  d = hslider("/v:envelope/Decay", 0.0, 0.0, 4, 0.001);
  s = hslider("/v:envelope/Sustain", 1.0, 0.0, 1.0, 0.01);
  r = hslider("/v:envelope/Release", 0.0, 0.0, 4.0, 0.01);


  out = par(i, 11, control( DXOTTO_algo(i, a,d,s,r,midifreq,midigain,midigate) , algN==i)) :> _;
};

//------------------------------`DXOTTO_modulator_op`---------------------------
// FM carrier operator for OTTO. Implements a phase-modulable sine wave oscillator connected
// to an ADSR envelope generator.
// ```
// DXOTTO_modulator_op(freq,phaseMod,outLev,att,dec,sus,rel,gain,gate) : _
// ```
// * `freq`: frequency of the oscillator
// * `phaseMod`: phase deviation (-1 - 1) (The 'input' of an operator. It is 0 for the top of a stack without self-modulation, and _ otherwise)
// * `outLev`: output level (0-1)
// * `att, rel` : AR parameters
// * `gate`: trigger signal
//-----------------------------------------------------------------
DXOTTO_modulator_op(basefreq,phaseMod,gate) =
adsr_OTTO(attack,dec,suspos,rel,gate)*outLev*sineWave
with{
  //Sine oscillator
  tablesize = 1 << 16;
  sineWave = rdtable(tablesize, os.sinwaveform(tablesize), ma.modulo(int(os.phasor(tablesize,freq) + phaseMod*tablesize),tablesize));
  freq =  hslider("ratio",1,0.25,4,0.01)*basefreq + hslider("detune",0,-1,1,0.01)*25;

  outLev = hslider("outLev",0,0,1,0.01);
  //Envelope
  attack = hslider("mAtt", 0, 0, 1, 0.01)*3;
  decrel = hslider("mDecrel", 0, 0, 1, 0.01)*3;
  suspos = hslider("mSuspos", 0, 0, 1, 0.01);
  dec = decrel*(1 - suspos);
  rel = decrel*suspos;
  adsr_OTTO(a,d,s,r,t) = on*(ads) : ba.sAndH(on) : rel
  with{
        on = t>0;
        off = t==0;
        attTime = ma.SR*a;
        decTime = ma.SR*d;
        relTime = ma.SR*r : max(0.001);
        sustainGain = t*s;
        ads = ba.countup(attTime+decTime,off) : ba.bpf.start(0,0) :
                ba.bpf.point(attTime,1) : ba.bpf.end(attTime+decTime,sustainGain);
        rel = _,ba.countup(relTime,on) : ba.bpf.start(0) : ba.bpf.end(relTime,0);
  };

};

//------------------------------`DXOTTO_carrier_op`---------------------------
// FM carrier operator for OTTO. Implements a phase-modulable sine wave oscillator connected
// to an ADSR envelope generator.
// ```
// DXOTTO_carrier_op(freq,phaseMod,outLev,att,dec,sus,rel,gain,gate) : _
// ```
// * `freq`: frequency of the oscillator
// * `phaseMod`: phase deviation (-1 - 1) (The 'input' of an operator. It is 0 for the top of a stack without self-modulation, and _ otherwise)
// * `outLev`: output level (0-1)
// * `att, dec, sus, rel` : ADSR parameters
// * `gain`: Gain from MIDI velocity
// * `gate`: trigger signal
//-----------------------------------------------------------------
DXOTTO_carrier_op(basefreq,phaseMod,att,dec,sus,rel,gain,gate) =
adsre_OTTO(attack,dec,sustain,release,gate)*outLev*gain*sineWave
with{
  //Sine oscillator
  tablesize = 1 << 16;
  sineWave = rdtable(tablesize, os.sinwaveform(tablesize), ma.modulo(int(os.phasor(tablesize,freq) + phaseMod*tablesize),tablesize));
  freq =  hslider("ratio",1,0.25,4,0.01)*basefreq + hslider("detune",0,-1,1,0.01)*25;

  outLev = hslider("outLev",0,0,1,0.01);
  //Envelope
  attack = att + hslider("cAtt", 0, -1, 1, 0.01) : max(0);
  sustain = sus + hslider("cSus", 0, -1, 1, 0.01)*0.5 : max(0);
  release = rel + hslider("cRel", 0, -1, 1, 0.01) : max(0);
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

//------------------------------`DXOTTO_algo`---------------------------
// DXOTTO algorithms. Implements the FM algorithms. Each algorithm uses 4 operators
// ```
// DXOTTO_algo(algN,att,dec,sus,rel,outLevel,opFreq,opDetune,feedback,freq,gain,gate) : _
// ```
// * `algN`: algorithm number (0-11, should be an int...)
// * `att, dec, sus, rel` : Carrier ADSR parameters (each a list of four values)
// * `cAtt, cRel` : Modulator AR parameters (a list of 4 values between 0-1. Those not needed are ignored)
// * `outLev`: Operator output levels (a list of 4 values between 0-1)
// * `opDetune`: Operator detunings (a list of 4 values between 0-1)
// * `opFreq`: Operator frequency ratios (a list of 4 values)
// * `freq`: fundamental frequency
// * `gain`: general gain
// * `gate`: trigger signal
//-----------------------------------------------------------------
// Alg 0
DXOTTO_algo(0, att, dec, sus, rel, freq, gain, gate) =
op4 : op3 : op2 : op1 : _
with{
  op4 = vgroup("op3", DXOTTO_modulator_op(freq,0,gate) );
  op3 = vgroup("op2", DXOTTO_modulator_op(freq,_,gate) );
  op2 = vgroup("op1", DXOTTO_modulator_op(freq,_,gate) );
  op1 = vgroup("op0", DXOTTO_carrier_op(freq,_,att,dec,sus,rel,gain,gate) );
};
// Alg 1
DXOTTO_algo(1, att, dec, sus, rel, freq, gain, gate) =
(op4 : op3) :> op2 :op1 : _
with{
  op4 = vgroup("op3", DXOTTO_modulator_op(freq,0,gate) );
  op3 = vgroup("op2", DXOTTO_modulator_op(freq,_,gate) );
  op2 = vgroup("op1", DXOTTO_modulator_op(freq,_,gate) );
  op1 = vgroup("op0", DXOTTO_carrier_op(freq,_,att,dec,sus,rel,gain,gate) );
};
// Alg 2
DXOTTO_algo(2, att, dec, sus, rel, freq, gain, gate) =
op3 : (op2, op4) :> op1 : _
with{
  op4 = vgroup("op3", DXOTTO_modulator_op(freq,0,gate) );
  op3 = vgroup("op2", DXOTTO_modulator_op(freq,0,gate) );
  op2 = vgroup("op1", DXOTTO_modulator_op(freq,_,gate) );
  op1 = vgroup("op0", DXOTTO_carrier_op(freq,_,att,dec,sus,rel,gain,gate) );
};
// Alg 3
DXOTTO_algo(3, att, dec, sus, rel, freq, gain, gate) =
op4 <: (op2, op3) :> op1 : _
with{
  op4 = vgroup("op3", DXOTTO_modulator_op(freq,0,gate) );
  op3 = vgroup("op2", DXOTTO_modulator_op(freq,_,gate) );
  op2 = vgroup("op1", DXOTTO_modulator_op(freq,_,gate) );
  op1 = vgroup("op0", DXOTTO_carrier_op(freq,_,att,dec,sus,rel,gain,gate) );
};
// Alg 4
DXOTTO_algo(4, att, dec, sus, rel, freq, gain, gate) =
op4 : op3 <: (op1, op2) :> _
with{
  op4 = vgroup("op3", DXOTTO_modulator_op(freq,0,gate) );
  op3 = vgroup("op2", DXOTTO_modulator_op(freq,_,gate) );
  op2 = vgroup("op1", DXOTTO_carrier_op(freq,_,att,dec,sus,rel,gain,gate) );
  op1 = vgroup("op0", DXOTTO_carrier_op(freq,_,att,dec,sus,rel,gain,gate) );
};
// Alg 5
DXOTTO_algo(5, att, dec, sus, rel, freq, gain, gate) =
op4 : op3 : (op1, op2) :> _
with{
  op4 = vgroup("op3", DXOTTO_modulator_op(freq,0,gate) );
  op3 = vgroup("op2", DXOTTO_modulator_op(freq,_,gate) );
  op2 = vgroup("op1", DXOTTO_carrier_op(freq,_,att,dec,sus,rel,gain,gate) );
  op1 = vgroup("op0", DXOTTO_carrier_op(freq,0,att,dec,sus,rel,gain,gate) );
};
// Alg 6
DXOTTO_algo(6, att, dec, sus, rel, freq, gain, gate) =
(op4, op3, op2) :> op1 : _
with{
  op4 = vgroup("op3", DXOTTO_modulator_op(freq,0,gate) );
  op3 = vgroup("op2", DXOTTO_modulator_op(freq,0,gate) );
  op2 = vgroup("op1", DXOTTO_modulator_op(freq,0,gate) );
  op1 = vgroup("op0", DXOTTO_carrier_op(freq,_,att,dec,sus,rel,gain,gate) );
};
// Alg 7
DXOTTO_algo(7, att, dec, sus, rel, freq, gain, gate) =
(op2 : op1),(op4 : op3) :> _
with{
  op4 = vgroup("op3", DXOTTO_modulator_op(freq,0,gate) );
  op3 = vgroup("op2", DXOTTO_carrier_op(freq,_,att,dec,sus,rel,gain,gate) );
  op2 = vgroup("op1", DXOTTO_modulator_op(freq,0,gate) );
  op1 = vgroup("op0", DXOTTO_carrier_op(freq,_,att,dec,sus,rel,gain,gate) );
};
// Alg 8
DXOTTO_algo(8, att, dec, sus, rel, freq, gain, gate) =
op4 <: (op1, op2, op3) :> _
with{
  op4 = vgroup("op3", DXOTTO_modulator_op(freq,0,gate) );
  op3 = vgroup("op2", DXOTTO_carrier_op(freq,_,att,dec,sus,rel,gain,gate) );
  op2 = vgroup("op1", DXOTTO_carrier_op(freq,_,att,dec,sus,rel,gain,gate) );
  op1 = vgroup("op0", DXOTTO_carrier_op(freq,_,att,dec,sus,rel,gain,gate) );
};
// Alg 9
DXOTTO_algo(9, att, dec, sus, rel, freq, gain, gate) =
op4 : (op1, op2, op3) :> _
with{
  op4 = vgroup("op3", DXOTTO_modulator_op(freq,0,gate) );
  op3 = vgroup("op2", DXOTTO_carrier_op(freq,_,att,dec,sus,rel,gain,gate) );
  op2 = vgroup("op1", DXOTTO_carrier_op(freq,0,att,dec,sus,rel,gain,gate) );
  op1 = vgroup("op0", DXOTTO_carrier_op(freq,0,att,dec,sus,rel,gain,gate) );
};
// Alg 10
DXOTTO_algo(10, att, dec, sus, rel, freq, gain, gate) =
(op1, op2, op3, op4) :> _
with{
  op4 = vgroup("op3", DXOTTO_carrier_op(freq,0,att,dec,sus,rel,gain,gate) );
  op3 = vgroup("op2", DXOTTO_carrier_op(freq,0,att,dec,sus,rel,gain,gate) );
  op2 = vgroup("op1", DXOTTO_carrier_op(freq,0,att,dec,sus,rel,gain,gate) );
  op1 = vgroup("op0", DXOTTO_carrier_op(freq,0,att,dec,sus,rel,gain,gate) );
};
