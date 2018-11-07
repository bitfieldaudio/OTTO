//----------------------------------------------------------
// name: "ottofm"
//
// Code generated with Faust 2.11.10 (https://faust.grame.fr)
//----------------------------------------------------------

/* link with  */
#include <math.h>
#include <math.h>
#include <algorithm>

#include <faust/gui/UI.h>
#include <faust/gui/meta.h>
#include <faust/dsp/dsp.h>

using std::max;
using std::min;

/********************************
	VECTOR INTRINSICS
*********************************/


/********************************
	ABSTRACT USER INTERFACE
*********************************/

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 


#ifndef FAUSTCLASS 
#define FAUSTCLASS faust_ottofm
#endif

class faust_ottofm : public dsp {
  private:
	class SIG0 {
	  private:
		int fSamplingFreq;
		int 	iRec0[2];
		float 	fTempPerm0;
	  public:
		int getNumInputs() { return 0; }
		int getNumOutputs() { return 1; }
		void init(int samplingFreq) {
			fSamplingFreq = samplingFreq;
			fTempPerm0 = 0;
			for (int i=0; i<2; i++) iRec0[i] = 0;
		}
		void fill (int count, float output[]) {
			for (int i=0; i<count; i++) {
				iRec0[0] = (iRec0[1] + 1);
				fTempPerm0 = sinf((9.5873799242852573e-05f * float((iRec0[0] + -1))));
				output[i] = fTempPerm0;
				// post processing
				iRec0[1] = iRec0[0];
			}
		}
	};


	FAUSTFLOAT 	fslider0;
	static float 	ftbl0[65536];
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT 	fslider3;
	float 	fConst0;
	float 	fConst1;
	float 	fRec1[2];
	float 	fTempPerm1;
	FAUSTFLOAT 	fbutton0;
	FAUSTFLOAT 	fslider4;
	FAUSTFLOAT 	fslider5;
	float 	fConst2;
	FAUSTFLOAT 	fslider6;
	float 	fRec3[2];
	float 	fConst3;
	int 	iTempPerm2;
	float 	fRec2[2];
	float 	fRec4[2];
	float 	fTempPerm3;
	FAUSTFLOAT 	fslider7;
	FAUSTFLOAT 	fslider8;
	float 	fTempPerm4;
	FAUSTFLOAT 	fslider9;
	FAUSTFLOAT 	fslider10;
	float 	fRec5[2];
	float 	fTempPerm5;
	FAUSTFLOAT 	fslider11;
	FAUSTFLOAT 	fslider12;
	FAUSTFLOAT 	fslider13;
	float 	fRec7[2];
	int 	iTempPerm6;
	float 	fRec6[2];
	float 	fRec8[2];
	float 	fTempPerm7;
	float 	fTempPerm8;
	FAUSTFLOAT 	fslider14;
	float 	fTempPerm9;
	FAUSTFLOAT 	fslider15;
	FAUSTFLOAT 	fslider16;
	float 	fRec9[2];
	float 	fTempPerm10;
	FAUSTFLOAT 	fslider17;
	FAUSTFLOAT 	fslider18;
	FAUSTFLOAT 	fslider19;
	float 	fRec11[2];
	int 	iTempPerm11;
	float 	fRec10[2];
	float 	fRec12[2];
	float 	fTempPerm12;
	FAUSTFLOAT 	fslider20;
	FAUSTFLOAT 	fslider21;
	FAUSTFLOAT 	fslider22;
	float 	fRec13[2];
	FAUSTFLOAT 	fslider23;
	FAUSTFLOAT 	fslider24;
	FAUSTFLOAT 	fslider25;
	FAUSTFLOAT 	fslider26;
	FAUSTFLOAT 	fslider27;
	int 	iRec15[2];
	int 	iTempPerm13;
	float 	fConst4;
	float 	fTempPerm14;
	FAUSTFLOAT 	fslider28;
	FAUSTFLOAT 	fslider29;
	float 	fRec14[2];
	float 	fTempPerm15;
	FAUSTFLOAT 	fslider30;
	FAUSTFLOAT 	fslider31;
	float 	fTempPerm16;
	FAUSTFLOAT 	fslider32;
	float 	fRec16[2];
	float 	fTempPerm17;
	FAUSTFLOAT 	fbutton1;
	float 	fRec18[2];
	int 	iTempPerm18;
	float 	fRec17[2];
	float 	fRec19[2];
	float 	fTempPerm19;
	float 	fTempPerm20;
	float 	fRec20[2];
	float 	fTempPerm21;
	float 	fRec22[2];
	int 	iTempPerm22;
	float 	fRec21[2];
	float 	fRec23[2];
	float 	fTempPerm23;
	float 	fTempPerm24;
	float 	fTempPerm25;
	float 	fRec24[2];
	float 	fTempPerm26;
	float 	fRec26[2];
	int 	iTempPerm27;
	float 	fRec25[2];
	float 	fRec27[2];
	float 	fTempPerm28;
	float 	fRec28[2];
	int 	iRec30[2];
	int 	iTempPerm29;
	float 	fTempPerm30;
	float 	fRec29[2];
	float 	fTempPerm31;
	FAUSTFLOAT 	fslider33;
	float 	fTempPerm32;
	FAUSTFLOAT 	fslider34;
	float 	fRec31[2];
	float 	fTempPerm33;
	FAUSTFLOAT 	fbutton2;
	float 	fRec33[2];
	int 	iTempPerm34;
	float 	fRec32[2];
	float 	fRec34[2];
	float 	fTempPerm35;
	float 	fTempPerm36;
	float 	fRec35[2];
	float 	fTempPerm37;
	float 	fRec37[2];
	int 	iTempPerm38;
	float 	fRec36[2];
	float 	fRec38[2];
	float 	fTempPerm39;
	float 	fTempPerm40;
	float 	fTempPerm41;
	float 	fRec39[2];
	float 	fTempPerm42;
	float 	fRec41[2];
	int 	iTempPerm43;
	float 	fRec40[2];
	float 	fRec42[2];
	float 	fTempPerm44;
	float 	fRec43[2];
	int 	iRec45[2];
	int 	iTempPerm45;
	float 	fTempPerm46;
	float 	fRec44[2];
	float 	fTempPerm47;
	FAUSTFLOAT 	fslider35;
	float 	fTempPerm48;
	FAUSTFLOAT 	fslider36;
	float 	fRec46[2];
	float 	fTempPerm49;
	FAUSTFLOAT 	fbutton3;
	float 	fRec48[2];
	int 	iTempPerm50;
	float 	fRec47[2];
	float 	fRec49[2];
	float 	fTempPerm51;
	float 	fTempPerm52;
	float 	fRec50[2];
	float 	fTempPerm53;
	float 	fRec52[2];
	int 	iTempPerm54;
	float 	fRec51[2];
	float 	fRec53[2];
	float 	fTempPerm55;
	float 	fTempPerm56;
	float 	fTempPerm57;
	float 	fRec54[2];
	float 	fTempPerm58;
	float 	fRec56[2];
	int 	iTempPerm59;
	float 	fRec55[2];
	float 	fRec57[2];
	float 	fTempPerm60;
	float 	fRec58[2];
	int 	iRec60[2];
	int 	iTempPerm61;
	float 	fTempPerm62;
	float 	fRec59[2];
	float 	fTempPerm63;
	FAUSTFLOAT 	fslider37;
	float 	fTempPerm64;
	FAUSTFLOAT 	fslider38;
	float 	fRec61[2];
	float 	fTempPerm65;
	FAUSTFLOAT 	fbutton4;
	float 	fRec63[2];
	int 	iTempPerm66;
	float 	fRec62[2];
	float 	fRec64[2];
	float 	fTempPerm67;
	float 	fTempPerm68;
	float 	fRec65[2];
	float 	fTempPerm69;
	float 	fRec67[2];
	int 	iTempPerm70;
	float 	fRec66[2];
	float 	fRec68[2];
	float 	fTempPerm71;
	float 	fTempPerm72;
	float 	fTempPerm73;
	float 	fRec69[2];
	float 	fTempPerm74;
	float 	fRec71[2];
	int 	iTempPerm75;
	float 	fRec70[2];
	float 	fRec72[2];
	float 	fTempPerm76;
	float 	fRec73[2];
	int 	iRec75[2];
	int 	iTempPerm77;
	float 	fTempPerm78;
	float 	fRec74[2];
	float 	fTempPerm79;
	FAUSTFLOAT 	fslider39;
	float 	fTempPerm80;
	FAUSTFLOAT 	fslider40;
	float 	fRec76[2];
	float 	fTempPerm81;
	FAUSTFLOAT 	fslider41;
	FAUSTFLOAT 	fslider42;
	FAUSTFLOAT 	fbutton5;
	int 	iRec78[2];
	int 	iTempPerm82;
	float 	fTempPerm83;
	FAUSTFLOAT 	fslider43;
	float 	fRec77[2];
	float 	fTempPerm84;
	float 	fRec79[2];
	float 	fTempPerm85;
	FAUSTFLOAT 	fslider44;
	FAUSTFLOAT 	fslider45;
	int 	iTempPerm86;
	float 	fTempPerm87;
	FAUSTFLOAT 	fslider46;
	float 	fRec80[2];
	float 	fTempPerm88;
	float 	fTempPerm89;
	float 	fRec81[2];
	float 	fTempPerm90;
	int 	iTempPerm91;
	float 	fTempPerm92;
	float 	fRec82[2];
	float 	fTempPerm93;
	float 	fTempPerm94;
	float 	fRec83[2];
	float 	fTempPerm95;
	FAUSTFLOAT 	fslider47;
	FAUSTFLOAT 	fslider48;
	int 	iTempPerm96;
	float 	fTempPerm97;
	FAUSTFLOAT 	fslider49;
	float 	fRec84[2];
	float 	fTempPerm98;
	FAUSTFLOAT 	fslider50;
	float 	fTempPerm99;
	FAUSTFLOAT 	fslider51;
	FAUSTFLOAT 	fslider52;
	FAUSTFLOAT 	fslider53;
	float 	fRec86[2];
	int 	iTempPerm100;
	float 	fRec85[2];
	float 	fRec87[2];
	float 	fTempPerm101;
	float 	fRec89[2];
	int 	iTempPerm102;
	float 	fRec88[2];
	float 	fRec90[2];
	float 	fTempPerm103;
	float 	fTempPerm104;
	float 	fTempPerm105;
	float 	fTempPerm106;
	float 	fTempPerm107;
	float 	fTempPerm108;
	float 	fRec92[2];
	int 	iTempPerm109;
	float 	fRec91[2];
	float 	fRec93[2];
	float 	fTempPerm110;
	float 	fTempPerm111;
	float 	fTempPerm112;
	float 	fRec95[2];
	int 	iTempPerm113;
	float 	fRec94[2];
	float 	fRec96[2];
	float 	fTempPerm114;
	float 	fTempPerm115;
	float 	fTempPerm116;
	float 	fTempPerm117;
	float 	fTempPerm118;
	float 	fTempPerm119;
	float 	fTempPerm120;
	float 	fTempPerm121;
	float 	fTempPerm122;
	float 	fTempPerm123;
	float 	fTempPerm124;
	float 	fTempPerm125;
	float 	fTempPerm126;
	float 	fTempPerm127;
	float 	fTempPerm128;
	float 	fTempPerm129;
	float 	fTempPerm130;
	float 	fTempPerm131;
	float 	fTempPerm132;
	int 	iTempPerm133;
	float 	fTempPerm134;
	float 	fRec97[2];
	float 	fTempPerm135;
	float 	fTempPerm136;
	float 	fTempPerm137;
	float 	fTempPerm138;
	float 	fTempPerm139;
	float 	fTempPerm140;
	float 	fTempPerm141;
	float 	fTempPerm142;
	float 	fTempPerm143;
	int 	iTempPerm144;
	float 	fTempPerm145;
	float 	fRec98[2];
	float 	fTempPerm146;
	float 	fTempPerm147;
	float 	fTempPerm148;
	float 	fTempPerm149;
	float 	fRec100[2];
	int 	iTempPerm150;
	float 	fRec99[2];
	float 	fRec101[2];
	float 	fTempPerm151;
	int 	iTempPerm152;
	float 	fTempPerm153;
	float 	fRec102[2];
	float 	fTempPerm154;
	float 	fTempPerm155;
	float 	fTempPerm156;
	float 	fTempPerm157;
	float 	fTempPerm158;
	float 	fTempPerm159;
	float 	fTempPerm160;
	float 	fTempPerm161;
	float 	fTempPerm162;
	int 	iTempPerm163;
	float 	fTempPerm164;
	float 	fRec103[2];
	float 	fTempPerm165;
	float 	fTempPerm166;
	float 	fTempPerm167;
	float 	fTempPerm168;
	float 	fTempPerm169;
	float 	fTempPerm170;
	float 	fTempPerm171;
	float 	fTempPerm172;
	float 	fTempPerm173;
	int 	iTempPerm174;
	float 	fTempPerm175;
	float 	fRec104[2];
	float 	fTempPerm176;
	float 	fTempPerm177;
	float 	fTempPerm178;
	float 	fTempPerm179;
	float 	fRec106[2];
	int 	iTempPerm180;
	float 	fRec105[2];
	float 	fRec107[2];
	float 	fTempPerm181;
	int 	iTempPerm182;
	float 	fTempPerm183;
	float 	fRec108[2];
	float 	fTempPerm184;
	float 	fTempPerm185;
	float 	fTempPerm186;
	float 	fTempPerm187;
	float 	fTempPerm188;
	float 	fTempPerm189;
	float 	fTempPerm190;
	float 	fTempPerm191;
	float 	fTempPerm192;
	int 	iTempPerm193;
	float 	fTempPerm194;
	float 	fRec109[2];
	float 	fTempPerm195;
	float 	fTempPerm196;
	float 	fTempPerm197;
	float 	fTempPerm198;
	float 	fTempPerm199;
	float 	fTempPerm200;
	float 	fTempPerm201;
	float 	fTempPerm202;
	float 	fTempPerm203;
	int 	iTempPerm204;
	float 	fTempPerm205;
	float 	fRec110[2];
	float 	fTempPerm206;
	float 	fTempPerm207;
	float 	fTempPerm208;
	float 	fTempPerm209;
	float 	fRec112[2];
	int 	iTempPerm210;
	float 	fRec111[2];
	float 	fRec113[2];
	float 	fTempPerm211;
	int 	iTempPerm212;
	float 	fTempPerm213;
	float 	fRec114[2];
	float 	fTempPerm214;
	float 	fTempPerm215;
	float 	fTempPerm216;
	float 	fTempPerm217;
	float 	fTempPerm218;
	float 	fTempPerm219;
	float 	fTempPerm220;
	float 	fTempPerm221;
	float 	fTempPerm222;
	int 	iTempPerm223;
	float 	fTempPerm224;
	float 	fRec115[2];
	float 	fTempPerm225;
	float 	fTempPerm226;
	float 	fTempPerm227;
	float 	fTempPerm228;
	float 	fTempPerm229;
	float 	fTempPerm230;
	float 	fTempPerm231;
	float 	fTempPerm232;
	float 	fTempPerm233;
	int 	iTempPerm234;
	float 	fTempPerm235;
	float 	fRec116[2];
	float 	fTempPerm236;
	float 	fTempPerm237;
	float 	fTempPerm238;
	float 	fTempPerm239;
	float 	fRec118[2];
	int 	iTempPerm240;
	float 	fRec117[2];
	float 	fRec119[2];
	float 	fTempPerm241;
	int 	iTempPerm242;
	float 	fTempPerm243;
	float 	fRec120[2];
	float 	fTempPerm244;
	float 	fTempPerm245;
	float 	fTempPerm246;
	float 	fTempPerm247;
	float 	fTempPerm248;
	float 	fTempPerm249;
	float 	fTempPerm250;
	float 	fTempPerm251;
	float 	fTempPerm252;
	int 	iTempPerm253;
	float 	fTempPerm254;
	float 	fRec121[2];
	float 	fTempPerm255;
	float 	fTempPerm256;
	float 	fTempPerm257;
	float 	fTempPerm258;
	float 	fTempPerm259;
	float 	fTempPerm260;
	float 	fTempPerm261;
	float 	fTempPerm262;
	float 	fTempPerm263;
	int 	iTempPerm264;
	float 	fTempPerm265;
	float 	fRec122[2];
	float 	fTempPerm266;
	float 	fTempPerm267;
	float 	fTempPerm268;
	float 	fTempPerm269;
	float 	fRec124[2];
	int 	iTempPerm270;
	float 	fRec123[2];
	float 	fRec125[2];
	float 	fTempPerm271;
	int 	iTempPerm272;
	float 	fTempPerm273;
	float 	fRec126[2];
	float 	fTempPerm274;
	float 	fTempPerm275;
	float 	fTempPerm276;
	int fSamplingFreq;

  public:
	virtual void metadata(Meta* m) { 
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.0");
		m->declare("filename", "ottofm");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.1");
		m->declare("name", "ottofm");
		m->declare("oscillators.lib/name", "Faust Oscillator Library");
		m->declare("oscillators.lib/version", "0.0");
		m->declare("signals.lib/name", "Faust Signal Routing Library");
		m->declare("signals.lib/version", "0.0");
	}

	virtual int getNumInputs() { return 0; }
	virtual int getNumOutputs() { return 1; }
	static void classInit(int samplingFreq) {
		SIG0 sig0;
		sig0.init(samplingFreq);
		sig0.fill(65536,ftbl0);
	}
	virtual void instanceConstants(int samplingFreq) {
		fSamplingFreq = samplingFreq;
		fConst0 = min(192000.0f, max(1.0f, (float)fSamplingFreq));
		fConst1 = (1.0f / fConst0);
		fTempPerm1 = 0;
		fConst2 = (3.0f * fConst0);
		fConst3 = (0.33333333333333331f / fConst0);
		iTempPerm2 = 0;
		fTempPerm3 = 0;
		fTempPerm4 = 0;
		fTempPerm5 = 0;
		iTempPerm6 = 0;
		fTempPerm7 = 0;
		fTempPerm8 = 0;
		fTempPerm9 = 0;
		fTempPerm10 = 0;
		iTempPerm11 = 0;
		fTempPerm12 = 0;
		iTempPerm13 = 0;
		fConst4 = (6.9100000000000001f / fConst0);
		fTempPerm14 = 0;
		fTempPerm15 = 0;
		fTempPerm16 = 0;
		fTempPerm17 = 0;
		iTempPerm18 = 0;
		fTempPerm19 = 0;
		fTempPerm20 = 0;
		fTempPerm21 = 0;
		iTempPerm22 = 0;
		fTempPerm23 = 0;
		fTempPerm24 = 0;
		fTempPerm25 = 0;
		fTempPerm26 = 0;
		iTempPerm27 = 0;
		fTempPerm28 = 0;
		iTempPerm29 = 0;
		fTempPerm30 = 0;
		fTempPerm31 = 0;
		fTempPerm32 = 0;
		fTempPerm33 = 0;
		iTempPerm34 = 0;
		fTempPerm35 = 0;
		fTempPerm36 = 0;
		fTempPerm37 = 0;
		iTempPerm38 = 0;
		fTempPerm39 = 0;
		fTempPerm40 = 0;
		fTempPerm41 = 0;
		fTempPerm42 = 0;
		iTempPerm43 = 0;
		fTempPerm44 = 0;
		iTempPerm45 = 0;
		fTempPerm46 = 0;
		fTempPerm47 = 0;
		fTempPerm48 = 0;
		fTempPerm49 = 0;
		iTempPerm50 = 0;
		fTempPerm51 = 0;
		fTempPerm52 = 0;
		fTempPerm53 = 0;
		iTempPerm54 = 0;
		fTempPerm55 = 0;
		fTempPerm56 = 0;
		fTempPerm57 = 0;
		fTempPerm58 = 0;
		iTempPerm59 = 0;
		fTempPerm60 = 0;
		iTempPerm61 = 0;
		fTempPerm62 = 0;
		fTempPerm63 = 0;
		fTempPerm64 = 0;
		fTempPerm65 = 0;
		iTempPerm66 = 0;
		fTempPerm67 = 0;
		fTempPerm68 = 0;
		fTempPerm69 = 0;
		iTempPerm70 = 0;
		fTempPerm71 = 0;
		fTempPerm72 = 0;
		fTempPerm73 = 0;
		fTempPerm74 = 0;
		iTempPerm75 = 0;
		fTempPerm76 = 0;
		iTempPerm77 = 0;
		fTempPerm78 = 0;
		fTempPerm79 = 0;
		fTempPerm80 = 0;
		fTempPerm81 = 0;
		iTempPerm82 = 0;
		fTempPerm83 = 0;
		fTempPerm84 = 0;
		fTempPerm85 = 0;
		iTempPerm86 = 0;
		fTempPerm87 = 0;
		fTempPerm88 = 0;
		fTempPerm89 = 0;
		fTempPerm90 = 0;
		iTempPerm91 = 0;
		fTempPerm92 = 0;
		fTempPerm93 = 0;
		fTempPerm94 = 0;
		fTempPerm95 = 0;
		iTempPerm96 = 0;
		fTempPerm97 = 0;
		fTempPerm98 = 0;
		fTempPerm99 = 0;
		iTempPerm100 = 0;
		fTempPerm101 = 0;
		iTempPerm102 = 0;
		fTempPerm103 = 0;
		fTempPerm104 = 0;
		fTempPerm105 = 0;
		fTempPerm106 = 0;
		fTempPerm107 = 0;
		fTempPerm108 = 0;
		iTempPerm109 = 0;
		fTempPerm110 = 0;
		fTempPerm111 = 0;
		fTempPerm112 = 0;
		iTempPerm113 = 0;
		fTempPerm114 = 0;
		fTempPerm115 = 0;
		fTempPerm116 = 0;
		fTempPerm117 = 0;
		fTempPerm118 = 0;
		fTempPerm119 = 0;
		fTempPerm120 = 0;
		fTempPerm121 = 0;
		fTempPerm122 = 0;
		fTempPerm123 = 0;
		fTempPerm124 = 0;
		fTempPerm125 = 0;
		fTempPerm126 = 0;
		fTempPerm127 = 0;
		fTempPerm128 = 0;
		fTempPerm129 = 0;
		fTempPerm130 = 0;
		fTempPerm131 = 0;
		fTempPerm132 = 0;
		iTempPerm133 = 0;
		fTempPerm134 = 0;
		fTempPerm135 = 0;
		fTempPerm136 = 0;
		fTempPerm137 = 0;
		fTempPerm138 = 0;
		fTempPerm139 = 0;
		fTempPerm140 = 0;
		fTempPerm141 = 0;
		fTempPerm142 = 0;
		fTempPerm143 = 0;
		iTempPerm144 = 0;
		fTempPerm145 = 0;
		fTempPerm146 = 0;
		fTempPerm147 = 0;
		fTempPerm148 = 0;
		fTempPerm149 = 0;
		iTempPerm150 = 0;
		fTempPerm151 = 0;
		iTempPerm152 = 0;
		fTempPerm153 = 0;
		fTempPerm154 = 0;
		fTempPerm155 = 0;
		fTempPerm156 = 0;
		fTempPerm157 = 0;
		fTempPerm158 = 0;
		fTempPerm159 = 0;
		fTempPerm160 = 0;
		fTempPerm161 = 0;
		fTempPerm162 = 0;
		iTempPerm163 = 0;
		fTempPerm164 = 0;
		fTempPerm165 = 0;
		fTempPerm166 = 0;
		fTempPerm167 = 0;
		fTempPerm168 = 0;
		fTempPerm169 = 0;
		fTempPerm170 = 0;
		fTempPerm171 = 0;
		fTempPerm172 = 0;
		fTempPerm173 = 0;
		iTempPerm174 = 0;
		fTempPerm175 = 0;
		fTempPerm176 = 0;
		fTempPerm177 = 0;
		fTempPerm178 = 0;
		fTempPerm179 = 0;
		iTempPerm180 = 0;
		fTempPerm181 = 0;
		iTempPerm182 = 0;
		fTempPerm183 = 0;
		fTempPerm184 = 0;
		fTempPerm185 = 0;
		fTempPerm186 = 0;
		fTempPerm187 = 0;
		fTempPerm188 = 0;
		fTempPerm189 = 0;
		fTempPerm190 = 0;
		fTempPerm191 = 0;
		fTempPerm192 = 0;
		iTempPerm193 = 0;
		fTempPerm194 = 0;
		fTempPerm195 = 0;
		fTempPerm196 = 0;
		fTempPerm197 = 0;
		fTempPerm198 = 0;
		fTempPerm199 = 0;
		fTempPerm200 = 0;
		fTempPerm201 = 0;
		fTempPerm202 = 0;
		fTempPerm203 = 0;
		iTempPerm204 = 0;
		fTempPerm205 = 0;
		fTempPerm206 = 0;
		fTempPerm207 = 0;
		fTempPerm208 = 0;
		fTempPerm209 = 0;
		iTempPerm210 = 0;
		fTempPerm211 = 0;
		iTempPerm212 = 0;
		fTempPerm213 = 0;
		fTempPerm214 = 0;
		fTempPerm215 = 0;
		fTempPerm216 = 0;
		fTempPerm217 = 0;
		fTempPerm218 = 0;
		fTempPerm219 = 0;
		fTempPerm220 = 0;
		fTempPerm221 = 0;
		fTempPerm222 = 0;
		iTempPerm223 = 0;
		fTempPerm224 = 0;
		fTempPerm225 = 0;
		fTempPerm226 = 0;
		fTempPerm227 = 0;
		fTempPerm228 = 0;
		fTempPerm229 = 0;
		fTempPerm230 = 0;
		fTempPerm231 = 0;
		fTempPerm232 = 0;
		fTempPerm233 = 0;
		iTempPerm234 = 0;
		fTempPerm235 = 0;
		fTempPerm236 = 0;
		fTempPerm237 = 0;
		fTempPerm238 = 0;
		fTempPerm239 = 0;
		iTempPerm240 = 0;
		fTempPerm241 = 0;
		iTempPerm242 = 0;
		fTempPerm243 = 0;
		fTempPerm244 = 0;
		fTempPerm245 = 0;
		fTempPerm246 = 0;
		fTempPerm247 = 0;
		fTempPerm248 = 0;
		fTempPerm249 = 0;
		fTempPerm250 = 0;
		fTempPerm251 = 0;
		fTempPerm252 = 0;
		iTempPerm253 = 0;
		fTempPerm254 = 0;
		fTempPerm255 = 0;
		fTempPerm256 = 0;
		fTempPerm257 = 0;
		fTempPerm258 = 0;
		fTempPerm259 = 0;
		fTempPerm260 = 0;
		fTempPerm261 = 0;
		fTempPerm262 = 0;
		fTempPerm263 = 0;
		iTempPerm264 = 0;
		fTempPerm265 = 0;
		fTempPerm266 = 0;
		fTempPerm267 = 0;
		fTempPerm268 = 0;
		fTempPerm269 = 0;
		iTempPerm270 = 0;
		fTempPerm271 = 0;
		iTempPerm272 = 0;
		fTempPerm273 = 0;
		fTempPerm274 = 0;
		fTempPerm275 = 0;
		fTempPerm276 = 0;
	}
	virtual void instanceResetUserInterface() {
		fslider0 = 0.0f;
		fslider1 = 440.0f;
		fslider2 = 1.0f;
		fslider3 = 0.0f;
		fbutton0 = 0.0;
		fslider4 = 0.0f;
		fslider5 = 0.0f;
		fslider6 = 0.0f;
		fslider7 = 1.0f;
		fslider8 = 1.0f;
		fslider9 = 1.0f;
		fslider10 = 0.0f;
		fslider11 = 0.0f;
		fslider12 = 0.0f;
		fslider13 = 0.0f;
		fslider14 = 1.0f;
		fslider15 = 1.0f;
		fslider16 = 0.0f;
		fslider17 = 0.0f;
		fslider18 = 0.0f;
		fslider19 = 0.0f;
		fslider20 = 1.0f;
		fslider21 = 1.0f;
		fslider22 = 0.0f;
		fslider23 = 0.0f;
		fslider24 = 0.0f;
		fslider25 = 0.0f;
		fslider26 = 0.0f;
		fslider27 = 0.001f;
		fslider28 = 0.0f;
		fslider29 = 1.0f;
		fslider30 = 1.0f;
		fslider31 = 1.0f;
		fslider32 = 440.0f;
		fbutton1 = 0.0;
		fslider33 = 1.0f;
		fslider34 = 440.0f;
		fbutton2 = 0.0;
		fslider35 = 1.0f;
		fslider36 = 440.0f;
		fbutton3 = 0.0;
		fslider37 = 1.0f;
		fslider38 = 440.0f;
		fbutton4 = 0.0;
		fslider39 = 1.0f;
		fslider40 = 440.0f;
		fslider41 = 0.0f;
		fslider42 = 0.0f;
		fbutton5 = 0.0;
		fslider43 = 0.0f;
		fslider44 = 0.0f;
		fslider45 = 0.0f;
		fslider46 = 0.0f;
		fslider47 = 0.0f;
		fslider48 = 0.0f;
		fslider49 = 0.0f;
		fslider50 = 1.0f;
		fslider51 = 0.0f;
		fslider52 = 0.0f;
		fslider53 = 0.0f;
	}
	virtual void instanceClear() {
		for (int i=0; i<2; i++) fRec1[i] = 0;
		for (int i=0; i<2; i++) fRec3[i] = 0;
		for (int i=0; i<2; i++) fRec2[i] = 0;
		for (int i=0; i<2; i++) fRec4[i] = 0;
		for (int i=0; i<2; i++) fRec5[i] = 0;
		for (int i=0; i<2; i++) fRec7[i] = 0;
		for (int i=0; i<2; i++) fRec6[i] = 0;
		for (int i=0; i<2; i++) fRec8[i] = 0;
		for (int i=0; i<2; i++) fRec9[i] = 0;
		for (int i=0; i<2; i++) fRec11[i] = 0;
		for (int i=0; i<2; i++) fRec10[i] = 0;
		for (int i=0; i<2; i++) fRec12[i] = 0;
		for (int i=0; i<2; i++) fRec13[i] = 0;
		for (int i=0; i<2; i++) iRec15[i] = 0;
		for (int i=0; i<2; i++) fRec14[i] = 0;
		for (int i=0; i<2; i++) fRec16[i] = 0;
		for (int i=0; i<2; i++) fRec18[i] = 0;
		for (int i=0; i<2; i++) fRec17[i] = 0;
		for (int i=0; i<2; i++) fRec19[i] = 0;
		for (int i=0; i<2; i++) fRec20[i] = 0;
		for (int i=0; i<2; i++) fRec22[i] = 0;
		for (int i=0; i<2; i++) fRec21[i] = 0;
		for (int i=0; i<2; i++) fRec23[i] = 0;
		for (int i=0; i<2; i++) fRec24[i] = 0;
		for (int i=0; i<2; i++) fRec26[i] = 0;
		for (int i=0; i<2; i++) fRec25[i] = 0;
		for (int i=0; i<2; i++) fRec27[i] = 0;
		for (int i=0; i<2; i++) fRec28[i] = 0;
		for (int i=0; i<2; i++) iRec30[i] = 0;
		for (int i=0; i<2; i++) fRec29[i] = 0;
		for (int i=0; i<2; i++) fRec31[i] = 0;
		for (int i=0; i<2; i++) fRec33[i] = 0;
		for (int i=0; i<2; i++) fRec32[i] = 0;
		for (int i=0; i<2; i++) fRec34[i] = 0;
		for (int i=0; i<2; i++) fRec35[i] = 0;
		for (int i=0; i<2; i++) fRec37[i] = 0;
		for (int i=0; i<2; i++) fRec36[i] = 0;
		for (int i=0; i<2; i++) fRec38[i] = 0;
		for (int i=0; i<2; i++) fRec39[i] = 0;
		for (int i=0; i<2; i++) fRec41[i] = 0;
		for (int i=0; i<2; i++) fRec40[i] = 0;
		for (int i=0; i<2; i++) fRec42[i] = 0;
		for (int i=0; i<2; i++) fRec43[i] = 0;
		for (int i=0; i<2; i++) iRec45[i] = 0;
		for (int i=0; i<2; i++) fRec44[i] = 0;
		for (int i=0; i<2; i++) fRec46[i] = 0;
		for (int i=0; i<2; i++) fRec48[i] = 0;
		for (int i=0; i<2; i++) fRec47[i] = 0;
		for (int i=0; i<2; i++) fRec49[i] = 0;
		for (int i=0; i<2; i++) fRec50[i] = 0;
		for (int i=0; i<2; i++) fRec52[i] = 0;
		for (int i=0; i<2; i++) fRec51[i] = 0;
		for (int i=0; i<2; i++) fRec53[i] = 0;
		for (int i=0; i<2; i++) fRec54[i] = 0;
		for (int i=0; i<2; i++) fRec56[i] = 0;
		for (int i=0; i<2; i++) fRec55[i] = 0;
		for (int i=0; i<2; i++) fRec57[i] = 0;
		for (int i=0; i<2; i++) fRec58[i] = 0;
		for (int i=0; i<2; i++) iRec60[i] = 0;
		for (int i=0; i<2; i++) fRec59[i] = 0;
		for (int i=0; i<2; i++) fRec61[i] = 0;
		for (int i=0; i<2; i++) fRec63[i] = 0;
		for (int i=0; i<2; i++) fRec62[i] = 0;
		for (int i=0; i<2; i++) fRec64[i] = 0;
		for (int i=0; i<2; i++) fRec65[i] = 0;
		for (int i=0; i<2; i++) fRec67[i] = 0;
		for (int i=0; i<2; i++) fRec66[i] = 0;
		for (int i=0; i<2; i++) fRec68[i] = 0;
		for (int i=0; i<2; i++) fRec69[i] = 0;
		for (int i=0; i<2; i++) fRec71[i] = 0;
		for (int i=0; i<2; i++) fRec70[i] = 0;
		for (int i=0; i<2; i++) fRec72[i] = 0;
		for (int i=0; i<2; i++) fRec73[i] = 0;
		for (int i=0; i<2; i++) iRec75[i] = 0;
		for (int i=0; i<2; i++) fRec74[i] = 0;
		for (int i=0; i<2; i++) fRec76[i] = 0;
		for (int i=0; i<2; i++) iRec78[i] = 0;
		for (int i=0; i<2; i++) fRec77[i] = 0;
		for (int i=0; i<2; i++) fRec79[i] = 0;
		for (int i=0; i<2; i++) fRec80[i] = 0;
		for (int i=0; i<2; i++) fRec81[i] = 0;
		for (int i=0; i<2; i++) fRec82[i] = 0;
		for (int i=0; i<2; i++) fRec83[i] = 0;
		for (int i=0; i<2; i++) fRec84[i] = 0;
		for (int i=0; i<2; i++) fRec86[i] = 0;
		for (int i=0; i<2; i++) fRec85[i] = 0;
		for (int i=0; i<2; i++) fRec87[i] = 0;
		for (int i=0; i<2; i++) fRec89[i] = 0;
		for (int i=0; i<2; i++) fRec88[i] = 0;
		for (int i=0; i<2; i++) fRec90[i] = 0;
		for (int i=0; i<2; i++) fRec92[i] = 0;
		for (int i=0; i<2; i++) fRec91[i] = 0;
		for (int i=0; i<2; i++) fRec93[i] = 0;
		for (int i=0; i<2; i++) fRec95[i] = 0;
		for (int i=0; i<2; i++) fRec94[i] = 0;
		for (int i=0; i<2; i++) fRec96[i] = 0;
		for (int i=0; i<2; i++) fRec97[i] = 0;
		for (int i=0; i<2; i++) fRec98[i] = 0;
		for (int i=0; i<2; i++) fRec100[i] = 0;
		for (int i=0; i<2; i++) fRec99[i] = 0;
		for (int i=0; i<2; i++) fRec101[i] = 0;
		for (int i=0; i<2; i++) fRec102[i] = 0;
		for (int i=0; i<2; i++) fRec103[i] = 0;
		for (int i=0; i<2; i++) fRec104[i] = 0;
		for (int i=0; i<2; i++) fRec106[i] = 0;
		for (int i=0; i<2; i++) fRec105[i] = 0;
		for (int i=0; i<2; i++) fRec107[i] = 0;
		for (int i=0; i<2; i++) fRec108[i] = 0;
		for (int i=0; i<2; i++) fRec109[i] = 0;
		for (int i=0; i<2; i++) fRec110[i] = 0;
		for (int i=0; i<2; i++) fRec112[i] = 0;
		for (int i=0; i<2; i++) fRec111[i] = 0;
		for (int i=0; i<2; i++) fRec113[i] = 0;
		for (int i=0; i<2; i++) fRec114[i] = 0;
		for (int i=0; i<2; i++) fRec115[i] = 0;
		for (int i=0; i<2; i++) fRec116[i] = 0;
		for (int i=0; i<2; i++) fRec118[i] = 0;
		for (int i=0; i<2; i++) fRec117[i] = 0;
		for (int i=0; i<2; i++) fRec119[i] = 0;
		for (int i=0; i<2; i++) fRec120[i] = 0;
		for (int i=0; i<2; i++) fRec121[i] = 0;
		for (int i=0; i<2; i++) fRec122[i] = 0;
		for (int i=0; i<2; i++) fRec124[i] = 0;
		for (int i=0; i<2; i++) fRec123[i] = 0;
		for (int i=0; i<2; i++) fRec125[i] = 0;
		for (int i=0; i<2; i++) fRec126[i] = 0;
	}
	virtual void init(int samplingFreq) {
		classInit(samplingFreq);
		instanceInit(samplingFreq);
	}
	virtual void instanceInit(int samplingFreq) {
		instanceConstants(samplingFreq);
		instanceResetUserInterface();
		instanceClear();
	}
	virtual faust_ottofm* clone() {
		return new faust_ottofm();
	}
	virtual int getSampleRate() {
		return fSamplingFreq;
	}
	virtual void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("ottofm");
		ui_interface->addHorizontalSlider("algN", &fslider0, 0.0f, 0.0f, 11.0f, 1.0f);
		ui_interface->openVerticalBox("envelope");
		ui_interface->addHorizontalSlider("Attack", &fslider27, 0.001f, 0.001f, 4.0f, 0.001f);
		ui_interface->addHorizontalSlider("Decay", &fslider25, 0.0f, 0.0f, 4.0f, 0.001f);
		ui_interface->addHorizontalSlider("Release", &fslider24, 0.0f, 0.0f, 4.0f, 0.01f);
		ui_interface->addHorizontalSlider("Sustain", &fslider29, 1.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->closeBox();
		ui_interface->addHorizontalSlider("fmAmount", &fslider8, 1.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->openVerticalBox("op0");
		ui_interface->addHorizontalSlider("cAtt", &fslider26, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cRel", &fslider23, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cSus", &fslider28, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("detune", &fslider22, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mAtt", &fslider52, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mDecrel", &fslider53, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mSuspos", &fslider51, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("outLev", &fslider30, 1.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("ratio", &fslider21, 1.0f, 0.25f, 4.0f, 0.01f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("op1");
		ui_interface->addHorizontalSlider("cAtt", &fslider45, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cRel", &fslider44, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cSus", &fslider46, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("detune", &fslider16, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mAtt", &fslider18, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mDecrel", &fslider19, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mSuspos", &fslider17, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("outLev", &fslider20, 1.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("ratio", &fslider15, 1.0f, 0.25f, 4.0f, 0.01f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("op2");
		ui_interface->addHorizontalSlider("cAtt", &fslider42, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cRel", &fslider41, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cSus", &fslider43, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("detune", &fslider10, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mAtt", &fslider12, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mDecrel", &fslider13, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mSuspos", &fslider11, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("outLev", &fslider14, 1.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("ratio", &fslider9, 1.0f, 0.25f, 4.0f, 0.01f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("op3");
		ui_interface->addHorizontalSlider("cAtt", &fslider48, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cRel", &fslider47, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("cSus", &fslider49, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("detune", &fslider3, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mAtt", &fslider5, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mDecrel", &fslider6, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mSuspos", &fslider4, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("outLev", &fslider7, 1.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("ratio", &fslider2, 1.0f, 0.25f, 4.0f, 0.01f);
		ui_interface->closeBox();
		ui_interface->openHorizontalBox("voices");
		ui_interface->openVerticalBox("0");
		ui_interface->openHorizontalBox("midi");
		ui_interface->addHorizontalSlider("freq", &fslider40, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addButton("trigger", &fbutton5);
		ui_interface->addHorizontalSlider("velocity", &fslider50, 1.0f, 0.0f, 1.0f, 0.007874015748031496f);
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->openVerticalBox("1");
		ui_interface->openHorizontalBox("midi");
		ui_interface->addHorizontalSlider("freq", &fslider36, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addButton("trigger", &fbutton3);
		ui_interface->addHorizontalSlider("velocity", &fslider37, 1.0f, 0.0f, 1.0f, 0.007874015748031496f);
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->openVerticalBox("2");
		ui_interface->openHorizontalBox("midi");
		ui_interface->addHorizontalSlider("freq", &fslider32, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addButton("trigger", &fbutton1);
		ui_interface->addHorizontalSlider("velocity", &fslider33, 1.0f, 0.0f, 1.0f, 0.007874015748031496f);
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->openVerticalBox("3");
		ui_interface->openHorizontalBox("midi");
		ui_interface->addHorizontalSlider("freq", &fslider38, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addButton("trigger", &fbutton4);
		ui_interface->addHorizontalSlider("velocity", &fslider39, 1.0f, 0.0f, 1.0f, 0.007874015748031496f);
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->openVerticalBox("4");
		ui_interface->openHorizontalBox("midi");
		ui_interface->addHorizontalSlider("freq", &fslider34, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addButton("trigger", &fbutton2);
		ui_interface->addHorizontalSlider("velocity", &fslider35, 1.0f, 0.0f, 1.0f, 0.007874015748031496f);
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->openVerticalBox("5");
		ui_interface->openHorizontalBox("midi");
		ui_interface->addHorizontalSlider("freq", &fslider1, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addButton("trigger", &fbutton0);
		ui_interface->addHorizontalSlider("velocity", &fslider31, 1.0f, 0.0f, 1.0f, 0.007874015748031496f);
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->closeBox();
	}
	virtual void compute (int count, FAUSTFLOAT** input, FAUSTFLOAT** output) {
		//zone1
		//zone2
		int 	iSlow0 = int(float(fslider0));
		int 	iSlow1 = (float((iSlow0 == 0)) != 0.0f);
		int 	iSlow2 = (float((iSlow0 == 1)) != 0.0f);
		int 	iSlow3 = (float((iSlow0 == 2)) != 0.0f);
		int 	iSlow4 = (float((iSlow0 == 3)) != 0.0f);
		int 	iSlow5 = (float((iSlow0 == 4)) != 0.0f);
		int 	iSlow6 = (float((iSlow0 == 5)) != 0.0f);
		int 	iSlow7 = (float((iSlow0 == 6)) != 0.0f);
		int 	iSlow8 = (float((iSlow0 == 7)) != 0.0f);
		int 	iSlow9 = (float((iSlow0 == 8)) != 0.0f);
		int 	iSlow10 = (float((iSlow0 == 9)) != 0.0f);
		int 	iSlow11 = (float((iSlow0 == 10)) != 0.0f);
		float 	fSlow12 = float(fslider1);
		float 	fSlow13 = float(fslider2);
		float 	fSlow14 = (25.0f * float(fslider3));
		float 	fSlow15 = (fConst1 * (fSlow14 + (fSlow13 * fSlow12)));
		float 	fSlow16 = float(fbutton0);
		float 	fSlow17 = float(fslider4);
		float 	fSlow18 = (fSlow17 * fSlow16);
		float 	fSlow19 = float(fslider5);
		float 	fSlow20 = (fConst2 * fSlow19);
		float 	fSlow21 = float(fslider6);
		float 	fSlow22 = (((1.0f - fSlow17) * fSlow21) + fSlow19);
		float 	fSlow23 = (fConst2 * fSlow22);
		int 	iSlow24 = int(((fSlow16 == 0.0f) > 0));
		float 	fSlow25 = (fSlow22 - fSlow19);
		float 	fSlow26 = (fConst3 * ((fSlow18 + -1.0f) / fSlow25));
		float 	fSlow27 = (fConst3 / fSlow19);
		int 	iSlow28 = (fSlow16 > 0.0f);
		float 	fSlow29 = float(iSlow28);
		int 	iSlow30 = int(iSlow28);
		float 	fSlow31 = max(0.001f, (fConst2 * (fSlow17 * fSlow21)));
		int 	iSlow32 = int((iSlow28 > 0));
		float 	fSlow33 = (1.0f / fSlow31);
		float 	fSlow34 = float(fslider7);
		float 	fSlow35 = float(fslider8);
		float 	fSlow36 = (fSlow35 * fSlow34);
		float 	fSlow37 = float(fslider9);
		float 	fSlow38 = (25.0f * float(fslider10));
		float 	fSlow39 = (fConst1 * (fSlow38 + (fSlow37 * fSlow12)));
		float 	fSlow40 = float(fslider11);
		float 	fSlow41 = (fSlow40 * fSlow16);
		float 	fSlow42 = float(fslider12);
		float 	fSlow43 = (fConst2 * fSlow42);
		float 	fSlow44 = float(fslider13);
		float 	fSlow45 = (((1.0f - fSlow40) * fSlow44) + fSlow42);
		float 	fSlow46 = (fConst2 * fSlow45);
		float 	fSlow47 = (fSlow45 - fSlow42);
		float 	fSlow48 = (fConst3 * ((fSlow41 + -1.0f) / fSlow47));
		float 	fSlow49 = (fConst3 / fSlow42);
		float 	fSlow50 = max(0.001f, (fConst2 * (fSlow40 * fSlow44)));
		float 	fSlow51 = (1.0f / fSlow50);
		float 	fSlow52 = float(fslider14);
		float 	fSlow53 = (fSlow35 * fSlow52);
		float 	fSlow54 = float(fslider15);
		float 	fSlow55 = (25.0f * float(fslider16));
		float 	fSlow56 = (fConst1 * (fSlow55 + (fSlow54 * fSlow12)));
		float 	fSlow57 = float(fslider17);
		float 	fSlow58 = (fSlow57 * fSlow16);
		float 	fSlow59 = float(fslider18);
		float 	fSlow60 = (fConst2 * fSlow59);
		float 	fSlow61 = float(fslider19);
		float 	fSlow62 = (((1.0f - fSlow57) * fSlow61) + fSlow59);
		float 	fSlow63 = (fConst2 * fSlow62);
		float 	fSlow64 = (fSlow62 - fSlow59);
		float 	fSlow65 = (fConst3 * ((fSlow58 + -1.0f) / fSlow64));
		float 	fSlow66 = (fConst3 / fSlow59);
		float 	fSlow67 = max(0.001f, (fConst2 * (fSlow57 * fSlow61)));
		float 	fSlow68 = (1.0f / fSlow67);
		float 	fSlow69 = float(fslider20);
		float 	fSlow70 = (fSlow35 * fSlow69);
		float 	fSlow71 = float(fslider21);
		float 	fSlow72 = (25.0f * float(fslider22));
		float 	fSlow73 = (fConst1 * (fSlow72 + (fSlow71 * fSlow12)));
		float 	fSlow74 = float(fslider24);
		float 	fSlow75 = max((float)0, (fSlow74 + float(fslider23)));
		float 	fSlow76 = float(fslider25);
		float 	fSlow77 = float(fslider27);
		float 	fSlow78 = max((float)0, (fSlow77 + float(fslider26)));
		float 	fSlow79 = (6.9100000000000001f * fSlow78);
		int 	iSlow80 = int((fConst0 * fSlow78));
		float 	fSlow81 = float(fslider29);
		float 	fSlow82 = max((float)0, (fSlow81 + (0.5f * float(fslider28))));
		float 	fSlow83 = (fSlow29 * fSlow82);
		float 	fSlow84 = float(fslider30);
		float 	fSlow85 = float(fslider31);
		float 	fSlow86 = (fSlow85 * fSlow84);
		float 	fSlow87 = float(fslider32);
		float 	fSlow88 = (fConst1 * (fSlow14 + (fSlow13 * fSlow87)));
		float 	fSlow89 = float(fbutton1);
		float 	fSlow90 = (fSlow17 * fSlow89);
		int 	iSlow91 = int(((fSlow89 == 0.0f) > 0));
		float 	fSlow92 = (fConst3 * ((fSlow90 + -1.0f) / fSlow25));
		int 	iSlow93 = (fSlow89 > 0.0f);
		float 	fSlow94 = float(iSlow93);
		int 	iSlow95 = int(iSlow93);
		int 	iSlow96 = int((iSlow93 > 0));
		float 	fSlow97 = (fConst1 * (fSlow38 + (fSlow37 * fSlow87)));
		float 	fSlow98 = (fSlow40 * fSlow89);
		float 	fSlow99 = (fConst3 * ((fSlow98 + -1.0f) / fSlow47));
		float 	fSlow100 = (fConst1 * (fSlow55 + (fSlow54 * fSlow87)));
		float 	fSlow101 = (fSlow57 * fSlow89);
		float 	fSlow102 = (fConst3 * ((fSlow101 + -1.0f) / fSlow64));
		float 	fSlow103 = (fConst1 * (fSlow72 + (fSlow71 * fSlow87)));
		float 	fSlow104 = (fSlow94 * fSlow82);
		float 	fSlow105 = float(fslider33);
		float 	fSlow106 = (fSlow84 * fSlow105);
		float 	fSlow107 = float(fslider34);
		float 	fSlow108 = (fConst1 * (fSlow14 + (fSlow13 * fSlow107)));
		float 	fSlow109 = float(fbutton2);
		float 	fSlow110 = (fSlow17 * fSlow109);
		int 	iSlow111 = int(((fSlow109 == 0.0f) > 0));
		float 	fSlow112 = (fConst3 * ((fSlow110 + -1.0f) / fSlow25));
		int 	iSlow113 = (fSlow109 > 0.0f);
		float 	fSlow114 = float(iSlow113);
		int 	iSlow115 = int(iSlow113);
		int 	iSlow116 = int((iSlow113 > 0));
		float 	fSlow117 = (fConst1 * (fSlow38 + (fSlow37 * fSlow107)));
		float 	fSlow118 = (fSlow40 * fSlow109);
		float 	fSlow119 = (fConst3 * ((fSlow118 + -1.0f) / fSlow47));
		float 	fSlow120 = (fConst1 * (fSlow55 + (fSlow54 * fSlow107)));
		float 	fSlow121 = (fSlow57 * fSlow109);
		float 	fSlow122 = (fConst3 * ((fSlow121 + -1.0f) / fSlow64));
		float 	fSlow123 = (fConst1 * (fSlow72 + (fSlow71 * fSlow107)));
		float 	fSlow124 = (fSlow114 * fSlow82);
		float 	fSlow125 = float(fslider35);
		float 	fSlow126 = (fSlow84 * fSlow125);
		float 	fSlow127 = float(fslider36);
		float 	fSlow128 = (fConst1 * (fSlow14 + (fSlow13 * fSlow127)));
		float 	fSlow129 = float(fbutton3);
		float 	fSlow130 = (fSlow17 * fSlow129);
		int 	iSlow131 = int(((fSlow129 == 0.0f) > 0));
		float 	fSlow132 = (fConst3 * ((fSlow130 + -1.0f) / fSlow25));
		int 	iSlow133 = (fSlow129 > 0.0f);
		float 	fSlow134 = float(iSlow133);
		int 	iSlow135 = int(iSlow133);
		int 	iSlow136 = int((iSlow133 > 0));
		float 	fSlow137 = (fConst1 * (fSlow38 + (fSlow37 * fSlow127)));
		float 	fSlow138 = (fSlow40 * fSlow129);
		float 	fSlow139 = (fConst3 * ((fSlow138 + -1.0f) / fSlow47));
		float 	fSlow140 = (fConst1 * (fSlow55 + (fSlow54 * fSlow127)));
		float 	fSlow141 = (fSlow57 * fSlow129);
		float 	fSlow142 = (fConst3 * ((fSlow141 + -1.0f) / fSlow64));
		float 	fSlow143 = (fConst1 * (fSlow72 + (fSlow71 * fSlow127)));
		float 	fSlow144 = (fSlow134 * fSlow82);
		float 	fSlow145 = float(fslider37);
		float 	fSlow146 = (fSlow84 * fSlow145);
		float 	fSlow147 = float(fslider38);
		float 	fSlow148 = (fConst1 * (fSlow14 + (fSlow13 * fSlow147)));
		float 	fSlow149 = float(fbutton4);
		float 	fSlow150 = (fSlow17 * fSlow149);
		int 	iSlow151 = int(((fSlow149 == 0.0f) > 0));
		float 	fSlow152 = (fConst3 * ((fSlow150 + -1.0f) / fSlow25));
		int 	iSlow153 = (fSlow149 > 0.0f);
		float 	fSlow154 = float(iSlow153);
		int 	iSlow155 = int(iSlow153);
		int 	iSlow156 = int((iSlow153 > 0));
		float 	fSlow157 = (fConst1 * (fSlow38 + (fSlow37 * fSlow147)));
		float 	fSlow158 = (fSlow40 * fSlow149);
		float 	fSlow159 = (fConst3 * ((fSlow158 + -1.0f) / fSlow47));
		float 	fSlow160 = (fConst1 * (fSlow55 + (fSlow54 * fSlow147)));
		float 	fSlow161 = (fSlow57 * fSlow149);
		float 	fSlow162 = (fConst3 * ((fSlow161 + -1.0f) / fSlow64));
		float 	fSlow163 = (fConst1 * (fSlow72 + (fSlow71 * fSlow147)));
		float 	fSlow164 = (fSlow154 * fSlow82);
		float 	fSlow165 = float(fslider39);
		float 	fSlow166 = (fSlow84 * fSlow165);
		float 	fSlow167 = float(fslider40);
		float 	fSlow168 = (fConst1 * (fSlow38 + (fSlow37 * fSlow167)));
		float 	fSlow169 = max((float)0, (fSlow74 + float(fslider41)));
		float 	fSlow170 = max((float)0, (fSlow77 + float(fslider42)));
		float 	fSlow171 = (6.9100000000000001f * fSlow170);
		int 	iSlow172 = int((fConst0 * fSlow170));
		float 	fSlow173 = float(fbutton5);
		int 	iSlow174 = (fSlow173 > 0.0f);
		int 	iSlow175 = int(iSlow174);
		float 	fSlow176 = max((float)0, (fSlow81 + (0.5f * float(fslider43))));
		float 	fSlow177 = float(iSlow174);
		float 	fSlow178 = (fSlow177 * fSlow176);
		float 	fSlow179 = (fConst1 * (fSlow55 + (fSlow54 * fSlow167)));
		float 	fSlow180 = max((float)0, (fSlow74 + float(fslider44)));
		float 	fSlow181 = max((float)0, (fSlow77 + float(fslider45)));
		float 	fSlow182 = (6.9100000000000001f * fSlow181);
		int 	iSlow183 = int((fConst0 * fSlow181));
		float 	fSlow184 = max((float)0, (fSlow81 + (0.5f * float(fslider46))));
		float 	fSlow185 = (fSlow177 * fSlow184);
		float 	fSlow186 = (fConst1 * (fSlow72 + (fSlow71 * fSlow167)));
		float 	fSlow187 = (fSlow177 * fSlow82);
		float 	fSlow188 = (fConst1 * (fSlow14 + (fSlow13 * fSlow167)));
		float 	fSlow189 = max((float)0, (fSlow74 + float(fslider47)));
		float 	fSlow190 = max((float)0, (fSlow77 + float(fslider48)));
		float 	fSlow191 = (6.9100000000000001f * fSlow190);
		int 	iSlow192 = int((fConst0 * fSlow190));
		float 	fSlow193 = max((float)0, (fSlow81 + (0.5f * float(fslider49))));
		float 	fSlow194 = (fSlow177 * fSlow193);
		float 	fSlow195 = float(fslider50);
		float 	fSlow196 = float(fslider51);
		float 	fSlow197 = (fSlow196 * fSlow173);
		float 	fSlow198 = float(fslider52);
		float 	fSlow199 = (fConst2 * fSlow198);
		float 	fSlow200 = float(fslider53);
		float 	fSlow201 = (((1.0f - fSlow196) * fSlow200) + fSlow198);
		float 	fSlow202 = (fConst2 * fSlow201);
		int 	iSlow203 = int(((fSlow173 == 0.0f) > 0));
		float 	fSlow204 = (fSlow201 - fSlow198);
		float 	fSlow205 = (fConst3 * ((fSlow197 + -1.0f) / fSlow204));
		float 	fSlow206 = (fConst3 / fSlow198);
		float 	fSlow207 = max(0.001f, (fConst2 * (fSlow196 * fSlow200)));
		int 	iSlow208 = int((iSlow174 > 0));
		float 	fSlow209 = (1.0f / fSlow207);
		float 	fSlow210 = (fSlow35 * fSlow84);
		float 	fSlow211 = (fSlow17 * fSlow173);
		float 	fSlow212 = (fConst3 * ((fSlow211 + -1.0f) / fSlow25));
		float 	fSlow213 = (fSlow57 * fSlow173);
		float 	fSlow214 = (fConst3 * ((fSlow213 + -1.0f) / fSlow64));
		float 	fSlow215 = (fSlow40 * fSlow173);
		float 	fSlow216 = (fConst3 * ((fSlow215 + -1.0f) / fSlow47));
		float 	fSlow217 = (fSlow84 * fSlow195);
		float 	fSlow218 = (fSlow154 * fSlow184);
		float 	fSlow219 = (fSlow154 * fSlow176);
		float 	fSlow220 = (fSlow196 * fSlow149);
		float 	fSlow221 = (fConst3 * ((fSlow220 + -1.0f) / fSlow204));
		float 	fSlow222 = (fSlow154 * fSlow193);
		float 	fSlow223 = (fSlow134 * fSlow184);
		float 	fSlow224 = (fSlow134 * fSlow176);
		float 	fSlow225 = (fSlow196 * fSlow129);
		float 	fSlow226 = (fConst3 * ((fSlow225 + -1.0f) / fSlow204));
		float 	fSlow227 = (fSlow134 * fSlow193);
		float 	fSlow228 = (fSlow114 * fSlow184);
		float 	fSlow229 = (fSlow114 * fSlow176);
		float 	fSlow230 = (fSlow196 * fSlow109);
		float 	fSlow231 = (fConst3 * ((fSlow230 + -1.0f) / fSlow204));
		float 	fSlow232 = (fSlow114 * fSlow193);
		float 	fSlow233 = (fSlow94 * fSlow184);
		float 	fSlow234 = (fSlow94 * fSlow176);
		float 	fSlow235 = (fSlow196 * fSlow89);
		float 	fSlow236 = (fConst3 * ((fSlow235 + -1.0f) / fSlow204));
		float 	fSlow237 = (fSlow94 * fSlow193);
		float 	fSlow238 = (fSlow29 * fSlow184);
		float 	fSlow239 = (fSlow29 * fSlow176);
		float 	fSlow240 = (fSlow196 * fSlow16);
		float 	fSlow241 = (fConst3 * ((fSlow240 + -1.0f) / fSlow204));
		float 	fSlow242 = (fSlow29 * fSlow193);
		//zone2b
		//zone3
		FAUSTFLOAT* output0 = output[0];
		//LoopGraphScalar
		for (int i=0; i<count; i++) {
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec1[0] = (fSlow15 + (fRec1[1] - floorf((fSlow15 + fRec1[1]))));
				fTempPerm1 = ftbl0[(((int((65536.0f * fRec1[0])) % 65536) + 65536) % 65536)];
			}
			if (iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec3[0] = ((iSlow24)?0.0f:min(fSlow23, (fRec3[1] + 1.0f)));
				iTempPerm2 = int((fRec3[0] < fSlow20));
				fRec2[0] = ((iSlow30)?(fSlow29 * ((iTempPerm2)?((int((fRec3[0] < 0.0f)))?0.0f:((iTempPerm2)?(fSlow27 * fRec3[0]):1.0f)):((int((fRec3[0] < fSlow23)))?((fSlow26 * (fRec3[0] - fSlow20)) + 1.0f):fSlow18))):fRec2[1]);
				fRec4[0] = ((iSlow32)?0.0f:min(fSlow31, (fRec4[1] + 1.0f)));
				fTempPerm3 = (((int((fRec4[0] < 0.0f)))?fRec2[0]:((int((fRec4[0] < fSlow31)))?(fRec2[0] + (fSlow33 * (0 - (fRec4[0] * fRec2[0])))):0.0f)) * fTempPerm1);
			}
			if (iSlow9 || iSlow8 || iSlow6 || iSlow5 || iSlow4 || iSlow2 || iSlow1) {
				fTempPerm4 = (fSlow36 * fTempPerm3);
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec5[0] = (fSlow39 + (fRec5[1] - floorf((fSlow39 + fRec5[1]))));
			}
			if (iSlow9 || iSlow8 || iSlow6 || iSlow5 || iSlow4 || iSlow2 || iSlow1) {
				fTempPerm5 = ftbl0[(((int((65536.0f * (fRec5[0] + fTempPerm4))) % 65536) + 65536) % 65536)];
			}
			if (iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec7[0] = ((iSlow24)?0.0f:min(fSlow46, (fRec7[1] + 1.0f)));
				iTempPerm6 = int((fRec7[0] < fSlow43));
				fRec6[0] = ((iSlow30)?(fSlow29 * ((iTempPerm6)?((int((fRec7[0] < 0.0f)))?0.0f:((iTempPerm6)?(fSlow49 * fRec7[0]):1.0f)):((int((fRec7[0] < fSlow46)))?((fSlow48 * (fRec7[0] - fSlow43)) + 1.0f):fSlow41))):fRec6[1]);
				fRec8[0] = ((iSlow32)?0.0f:min(fSlow50, (fRec8[1] + 1.0f)));
				fTempPerm7 = ((int((fRec8[0] < 0.0f)))?fRec6[0]:((int((fRec8[0] < fSlow50)))?(fRec6[0] + (fSlow51 * (0 - (fRec8[0] * fRec6[0])))):0.0f));
			}
			if (iSlow6 || iSlow5 || iSlow4 || iSlow2 || iSlow1) {
				fTempPerm8 = (fTempPerm7 * fTempPerm5);
			}
			if (iSlow6 || iSlow5 || iSlow2 || iSlow1) {
				fTempPerm9 = (fSlow53 * fTempPerm8);
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec9[0] = (fSlow56 + (fRec9[1] - floorf((fSlow56 + fRec9[1]))));
			}
			if (iSlow6 || iSlow5 || iSlow2 || iSlow1) {
				fTempPerm10 = ftbl0[(((int((65536.0f * (fRec9[0] + fTempPerm9))) % 65536) + 65536) % 65536)];
			}
			if (iSlow8 || iSlow7 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec11[0] = ((iSlow24)?0.0f:min(fSlow63, (fRec11[1] + 1.0f)));
				iTempPerm11 = int((fRec11[0] < fSlow60));
				fRec10[0] = ((iSlow30)?(fSlow29 * ((iTempPerm11)?((int((fRec11[0] < 0.0f)))?0.0f:((iTempPerm11)?(fSlow66 * fRec11[0]):1.0f)):((int((fRec11[0] < fSlow63)))?((fSlow65 * (fRec11[0] - fSlow60)) + 1.0f):fSlow58))):fRec10[1]);
				fRec12[0] = ((iSlow32)?0.0f:min(fSlow67, (fRec12[1] + 1.0f)));
				fTempPerm12 = ((int((fRec12[0] < 0.0f)))?fRec10[0]:((int((fRec12[0] < fSlow67)))?(fRec10[0] + (fSlow68 * (0 - (fRec12[0] * fRec10[0])))):0.0f));
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec13[0] = (fSlow73 + (fRec13[1] - floorf((fSlow73 + fRec13[1]))));
				iRec15[0] = (iSlow28 * (iRec15[1] + 1));
			}
			if (iSlow11 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				iTempPerm13 = int((iRec15[0] < iSlow80));
				fTempPerm14 = expf((0 - (fConst4 / ((iSlow30)?((iTempPerm13)?fSlow79:fSlow76):fSlow75))));
				fRec14[0] = ((fRec14[1] * fTempPerm14) + (((iSlow30)?((iTempPerm13)?1.5873015873015872f:fSlow83):0.0f) * (1.0f - fTempPerm14)));
				fTempPerm15 = min(1.0f, fRec14[0]);
			}
			if (iSlow2 || iSlow1) {
				fTempPerm16 = (fSlow86 * (fTempPerm15 * ftbl0[(((int((65536.0f * (fRec13[0] + (fSlow70 * (fTempPerm12 * fTempPerm10))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec16[0] = (fSlow88 + (fRec16[1] - floorf((fSlow88 + fRec16[1]))));
				fTempPerm17 = ftbl0[(((int((65536.0f * fRec16[0])) % 65536) + 65536) % 65536)];
			}
			if (iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec18[0] = ((iSlow91)?0.0f:min(fSlow23, (fRec18[1] + 1.0f)));
				iTempPerm18 = int((fRec18[0] < fSlow20));
				fRec17[0] = ((iSlow95)?(fSlow94 * ((iTempPerm18)?((int((fRec18[0] < 0.0f)))?0.0f:((iTempPerm18)?(fSlow27 * fRec18[0]):1.0f)):((int((fRec18[0] < fSlow23)))?((fSlow92 * (fRec18[0] - fSlow20)) + 1.0f):fSlow90))):fRec17[1]);
				fRec19[0] = ((iSlow96)?0.0f:min(fSlow31, (fRec19[1] + 1.0f)));
				fTempPerm19 = (((int((fRec19[0] < 0.0f)))?fRec17[0]:((int((fRec19[0] < fSlow31)))?(fRec17[0] + (fSlow33 * (0 - (fRec19[0] * fRec17[0])))):0.0f)) * fTempPerm17);
			}
			if (iSlow9 || iSlow8 || iSlow6 || iSlow5 || iSlow4 || iSlow2 || iSlow1) {
				fTempPerm20 = (fSlow36 * fTempPerm19);
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec20[0] = (fSlow97 + (fRec20[1] - floorf((fSlow97 + fRec20[1]))));
			}
			if (iSlow9 || iSlow8 || iSlow6 || iSlow5 || iSlow4 || iSlow2 || iSlow1) {
				fTempPerm21 = ftbl0[(((int((65536.0f * (fRec20[0] + fTempPerm20))) % 65536) + 65536) % 65536)];
			}
			if (iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec22[0] = ((iSlow91)?0.0f:min(fSlow46, (fRec22[1] + 1.0f)));
				iTempPerm22 = int((fRec22[0] < fSlow43));
				fRec21[0] = ((iSlow95)?(fSlow94 * ((iTempPerm22)?((int((fRec22[0] < 0.0f)))?0.0f:((iTempPerm22)?(fSlow49 * fRec22[0]):1.0f)):((int((fRec22[0] < fSlow46)))?((fSlow99 * (fRec22[0] - fSlow43)) + 1.0f):fSlow98))):fRec21[1]);
				fRec23[0] = ((iSlow96)?0.0f:min(fSlow50, (fRec23[1] + 1.0f)));
				fTempPerm23 = ((int((fRec23[0] < 0.0f)))?fRec21[0]:((int((fRec23[0] < fSlow50)))?(fRec21[0] + (fSlow51 * (0 - (fRec23[0] * fRec21[0])))):0.0f));
			}
			if (iSlow6 || iSlow5 || iSlow4 || iSlow2 || iSlow1) {
				fTempPerm24 = (fTempPerm23 * fTempPerm21);
			}
			if (iSlow6 || iSlow5 || iSlow2 || iSlow1) {
				fTempPerm25 = (fSlow53 * fTempPerm24);
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec24[0] = (fSlow100 + (fRec24[1] - floorf((fSlow100 + fRec24[1]))));
			}
			if (iSlow6 || iSlow5 || iSlow2 || iSlow1) {
				fTempPerm26 = ftbl0[(((int((65536.0f * (fRec24[0] + fTempPerm25))) % 65536) + 65536) % 65536)];
			}
			if (iSlow8 || iSlow7 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec26[0] = ((iSlow91)?0.0f:min(fSlow63, (fRec26[1] + 1.0f)));
				iTempPerm27 = int((fRec26[0] < fSlow60));
				fRec25[0] = ((iSlow95)?(fSlow94 * ((iTempPerm27)?((int((fRec26[0] < 0.0f)))?0.0f:((iTempPerm27)?(fSlow66 * fRec26[0]):1.0f)):((int((fRec26[0] < fSlow63)))?((fSlow102 * (fRec26[0] - fSlow60)) + 1.0f):fSlow101))):fRec25[1]);
				fRec27[0] = ((iSlow96)?0.0f:min(fSlow67, (fRec27[1] + 1.0f)));
				fTempPerm28 = ((int((fRec27[0] < 0.0f)))?fRec25[0]:((int((fRec27[0] < fSlow67)))?(fRec25[0] + (fSlow68 * (0 - (fRec27[0] * fRec25[0])))):0.0f));
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec28[0] = (fSlow103 + (fRec28[1] - floorf((fSlow103 + fRec28[1]))));
				iRec30[0] = (iSlow93 * (iRec30[1] + 1));
			}
			if (iSlow11 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				iTempPerm29 = int((iRec30[0] < iSlow80));
				fTempPerm30 = expf((0 - (fConst4 / ((iSlow95)?((iTempPerm29)?fSlow79:fSlow76):fSlow75))));
				fRec29[0] = ((fRec29[1] * fTempPerm30) + (((iSlow95)?((iTempPerm29)?1.5873015873015872f:fSlow104):0.0f) * (1.0f - fTempPerm30)));
				fTempPerm31 = min(1.0f, fRec29[0]);
			}
			if (iSlow2 || iSlow1) {
				fTempPerm32 = (fSlow106 * (fTempPerm31 * ftbl0[(((int((65536.0f * (fRec28[0] + (fSlow70 * (fTempPerm28 * fTempPerm26))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec31[0] = (fSlow108 + (fRec31[1] - floorf((fSlow108 + fRec31[1]))));
				fTempPerm33 = ftbl0[(((int((65536.0f * fRec31[0])) % 65536) + 65536) % 65536)];
			}
			if (iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec33[0] = ((iSlow111)?0.0f:min(fSlow23, (fRec33[1] + 1.0f)));
				iTempPerm34 = int((fRec33[0] < fSlow20));
				fRec32[0] = ((iSlow115)?(fSlow114 * ((iTempPerm34)?((int((fRec33[0] < 0.0f)))?0.0f:((iTempPerm34)?(fSlow27 * fRec33[0]):1.0f)):((int((fRec33[0] < fSlow23)))?((fSlow112 * (fRec33[0] - fSlow20)) + 1.0f):fSlow110))):fRec32[1]);
				fRec34[0] = ((iSlow116)?0.0f:min(fSlow31, (fRec34[1] + 1.0f)));
				fTempPerm35 = (((int((fRec34[0] < 0.0f)))?fRec32[0]:((int((fRec34[0] < fSlow31)))?(fRec32[0] + (fSlow33 * (0 - (fRec34[0] * fRec32[0])))):0.0f)) * fTempPerm33);
			}
			if (iSlow9 || iSlow8 || iSlow6 || iSlow5 || iSlow4 || iSlow2 || iSlow1) {
				fTempPerm36 = (fSlow36 * fTempPerm35);
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec35[0] = (fSlow117 + (fRec35[1] - floorf((fSlow117 + fRec35[1]))));
			}
			if (iSlow9 || iSlow8 || iSlow6 || iSlow5 || iSlow4 || iSlow2 || iSlow1) {
				fTempPerm37 = ftbl0[(((int((65536.0f * (fRec35[0] + fTempPerm36))) % 65536) + 65536) % 65536)];
			}
			if (iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec37[0] = ((iSlow111)?0.0f:min(fSlow46, (fRec37[1] + 1.0f)));
				iTempPerm38 = int((fRec37[0] < fSlow43));
				fRec36[0] = ((iSlow115)?(fSlow114 * ((iTempPerm38)?((int((fRec37[0] < 0.0f)))?0.0f:((iTempPerm38)?(fSlow49 * fRec37[0]):1.0f)):((int((fRec37[0] < fSlow46)))?((fSlow119 * (fRec37[0] - fSlow43)) + 1.0f):fSlow118))):fRec36[1]);
				fRec38[0] = ((iSlow116)?0.0f:min(fSlow50, (fRec38[1] + 1.0f)));
				fTempPerm39 = ((int((fRec38[0] < 0.0f)))?fRec36[0]:((int((fRec38[0] < fSlow50)))?(fRec36[0] + (fSlow51 * (0 - (fRec38[0] * fRec36[0])))):0.0f));
			}
			if (iSlow6 || iSlow5 || iSlow4 || iSlow2 || iSlow1) {
				fTempPerm40 = (fTempPerm39 * fTempPerm37);
			}
			if (iSlow6 || iSlow5 || iSlow2 || iSlow1) {
				fTempPerm41 = (fSlow53 * fTempPerm40);
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec39[0] = (fSlow120 + (fRec39[1] - floorf((fSlow120 + fRec39[1]))));
			}
			if (iSlow6 || iSlow5 || iSlow2 || iSlow1) {
				fTempPerm42 = ftbl0[(((int((65536.0f * (fRec39[0] + fTempPerm41))) % 65536) + 65536) % 65536)];
			}
			if (iSlow8 || iSlow7 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec41[0] = ((iSlow111)?0.0f:min(fSlow63, (fRec41[1] + 1.0f)));
				iTempPerm43 = int((fRec41[0] < fSlow60));
				fRec40[0] = ((iSlow115)?(fSlow114 * ((iTempPerm43)?((int((fRec41[0] < 0.0f)))?0.0f:((iTempPerm43)?(fSlow66 * fRec41[0]):1.0f)):((int((fRec41[0] < fSlow63)))?((fSlow122 * (fRec41[0] - fSlow60)) + 1.0f):fSlow121))):fRec40[1]);
				fRec42[0] = ((iSlow116)?0.0f:min(fSlow67, (fRec42[1] + 1.0f)));
				fTempPerm44 = ((int((fRec42[0] < 0.0f)))?fRec40[0]:((int((fRec42[0] < fSlow67)))?(fRec40[0] + (fSlow68 * (0 - (fRec42[0] * fRec40[0])))):0.0f));
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec43[0] = (fSlow123 + (fRec43[1] - floorf((fSlow123 + fRec43[1]))));
				iRec45[0] = (iSlow113 * (iRec45[1] + 1));
			}
			if (iSlow11 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				iTempPerm45 = int((iRec45[0] < iSlow80));
				fTempPerm46 = expf((0 - (fConst4 / ((iSlow115)?((iTempPerm45)?fSlow79:fSlow76):fSlow75))));
				fRec44[0] = ((fRec44[1] * fTempPerm46) + (((iSlow115)?((iTempPerm45)?1.5873015873015872f:fSlow124):0.0f) * (1.0f - fTempPerm46)));
				fTempPerm47 = min(1.0f, fRec44[0]);
			}
			if (iSlow2 || iSlow1) {
				fTempPerm48 = (fSlow126 * (fTempPerm47 * ftbl0[(((int((65536.0f * (fRec43[0] + (fSlow70 * (fTempPerm44 * fTempPerm42))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec46[0] = (fSlow128 + (fRec46[1] - floorf((fSlow128 + fRec46[1]))));
				fTempPerm49 = ftbl0[(((int((65536.0f * fRec46[0])) % 65536) + 65536) % 65536)];
			}
			if (iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec48[0] = ((iSlow131)?0.0f:min(fSlow23, (fRec48[1] + 1.0f)));
				iTempPerm50 = int((fRec48[0] < fSlow20));
				fRec47[0] = ((iSlow135)?(fSlow134 * ((iTempPerm50)?((int((fRec48[0] < 0.0f)))?0.0f:((iTempPerm50)?(fSlow27 * fRec48[0]):1.0f)):((int((fRec48[0] < fSlow23)))?((fSlow132 * (fRec48[0] - fSlow20)) + 1.0f):fSlow130))):fRec47[1]);
				fRec49[0] = ((iSlow136)?0.0f:min(fSlow31, (fRec49[1] + 1.0f)));
				fTempPerm51 = (((int((fRec49[0] < 0.0f)))?fRec47[0]:((int((fRec49[0] < fSlow31)))?(fRec47[0] + (fSlow33 * (0 - (fRec49[0] * fRec47[0])))):0.0f)) * fTempPerm49);
			}
			if (iSlow9 || iSlow8 || iSlow6 || iSlow5 || iSlow4 || iSlow2 || iSlow1) {
				fTempPerm52 = (fSlow36 * fTempPerm51);
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec50[0] = (fSlow137 + (fRec50[1] - floorf((fSlow137 + fRec50[1]))));
			}
			if (iSlow9 || iSlow8 || iSlow6 || iSlow5 || iSlow4 || iSlow2 || iSlow1) {
				fTempPerm53 = ftbl0[(((int((65536.0f * (fRec50[0] + fTempPerm52))) % 65536) + 65536) % 65536)];
			}
			if (iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec52[0] = ((iSlow131)?0.0f:min(fSlow46, (fRec52[1] + 1.0f)));
				iTempPerm54 = int((fRec52[0] < fSlow43));
				fRec51[0] = ((iSlow135)?(fSlow134 * ((iTempPerm54)?((int((fRec52[0] < 0.0f)))?0.0f:((iTempPerm54)?(fSlow49 * fRec52[0]):1.0f)):((int((fRec52[0] < fSlow46)))?((fSlow139 * (fRec52[0] - fSlow43)) + 1.0f):fSlow138))):fRec51[1]);
				fRec53[0] = ((iSlow136)?0.0f:min(fSlow50, (fRec53[1] + 1.0f)));
				fTempPerm55 = ((int((fRec53[0] < 0.0f)))?fRec51[0]:((int((fRec53[0] < fSlow50)))?(fRec51[0] + (fSlow51 * (0 - (fRec53[0] * fRec51[0])))):0.0f));
			}
			if (iSlow6 || iSlow5 || iSlow4 || iSlow2 || iSlow1) {
				fTempPerm56 = (fTempPerm55 * fTempPerm53);
			}
			if (iSlow6 || iSlow5 || iSlow2 || iSlow1) {
				fTempPerm57 = (fSlow53 * fTempPerm56);
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec54[0] = (fSlow140 + (fRec54[1] - floorf((fSlow140 + fRec54[1]))));
			}
			if (iSlow6 || iSlow5 || iSlow2 || iSlow1) {
				fTempPerm58 = ftbl0[(((int((65536.0f * (fRec54[0] + fTempPerm57))) % 65536) + 65536) % 65536)];
			}
			if (iSlow8 || iSlow7 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec56[0] = ((iSlow131)?0.0f:min(fSlow63, (fRec56[1] + 1.0f)));
				iTempPerm59 = int((fRec56[0] < fSlow60));
				fRec55[0] = ((iSlow135)?(fSlow134 * ((iTempPerm59)?((int((fRec56[0] < 0.0f)))?0.0f:((iTempPerm59)?(fSlow66 * fRec56[0]):1.0f)):((int((fRec56[0] < fSlow63)))?((fSlow142 * (fRec56[0] - fSlow60)) + 1.0f):fSlow141))):fRec55[1]);
				fRec57[0] = ((iSlow136)?0.0f:min(fSlow67, (fRec57[1] + 1.0f)));
				fTempPerm60 = ((int((fRec57[0] < 0.0f)))?fRec55[0]:((int((fRec57[0] < fSlow67)))?(fRec55[0] + (fSlow68 * (0 - (fRec57[0] * fRec55[0])))):0.0f));
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec58[0] = (fSlow143 + (fRec58[1] - floorf((fSlow143 + fRec58[1]))));
				iRec60[0] = (iSlow133 * (iRec60[1] + 1));
			}
			if (iSlow11 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				iTempPerm61 = int((iRec60[0] < iSlow80));
				fTempPerm62 = expf((0 - (fConst4 / ((iSlow135)?((iTempPerm61)?fSlow79:fSlow76):fSlow75))));
				fRec59[0] = ((fRec59[1] * fTempPerm62) + (((iSlow135)?((iTempPerm61)?1.5873015873015872f:fSlow144):0.0f) * (1.0f - fTempPerm62)));
				fTempPerm63 = min(1.0f, fRec59[0]);
			}
			if (iSlow2 || iSlow1) {
				fTempPerm64 = (fSlow146 * (fTempPerm63 * ftbl0[(((int((65536.0f * (fRec58[0] + (fSlow70 * (fTempPerm60 * fTempPerm58))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec61[0] = (fSlow148 + (fRec61[1] - floorf((fSlow148 + fRec61[1]))));
				fTempPerm65 = ftbl0[(((int((65536.0f * fRec61[0])) % 65536) + 65536) % 65536)];
			}
			if (iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec63[0] = ((iSlow151)?0.0f:min(fSlow23, (fRec63[1] + 1.0f)));
				iTempPerm66 = int((fRec63[0] < fSlow20));
				fRec62[0] = ((iSlow155)?(fSlow154 * ((iTempPerm66)?((int((fRec63[0] < 0.0f)))?0.0f:((iTempPerm66)?(fSlow27 * fRec63[0]):1.0f)):((int((fRec63[0] < fSlow23)))?((fSlow152 * (fRec63[0] - fSlow20)) + 1.0f):fSlow150))):fRec62[1]);
				fRec64[0] = ((iSlow156)?0.0f:min(fSlow31, (fRec64[1] + 1.0f)));
				fTempPerm67 = (((int((fRec64[0] < 0.0f)))?fRec62[0]:((int((fRec64[0] < fSlow31)))?(fRec62[0] + (fSlow33 * (0 - (fRec64[0] * fRec62[0])))):0.0f)) * fTempPerm65);
			}
			if (iSlow9 || iSlow8 || iSlow6 || iSlow5 || iSlow4 || iSlow2 || iSlow1) {
				fTempPerm68 = (fSlow36 * fTempPerm67);
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec65[0] = (fSlow157 + (fRec65[1] - floorf((fSlow157 + fRec65[1]))));
			}
			if (iSlow9 || iSlow8 || iSlow6 || iSlow5 || iSlow4 || iSlow2 || iSlow1) {
				fTempPerm69 = ftbl0[(((int((65536.0f * (fRec65[0] + fTempPerm68))) % 65536) + 65536) % 65536)];
			}
			if (iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec67[0] = ((iSlow151)?0.0f:min(fSlow46, (fRec67[1] + 1.0f)));
				iTempPerm70 = int((fRec67[0] < fSlow43));
				fRec66[0] = ((iSlow155)?(fSlow154 * ((iTempPerm70)?((int((fRec67[0] < 0.0f)))?0.0f:((iTempPerm70)?(fSlow49 * fRec67[0]):1.0f)):((int((fRec67[0] < fSlow46)))?((fSlow159 * (fRec67[0] - fSlow43)) + 1.0f):fSlow158))):fRec66[1]);
				fRec68[0] = ((iSlow156)?0.0f:min(fSlow50, (fRec68[1] + 1.0f)));
				fTempPerm71 = ((int((fRec68[0] < 0.0f)))?fRec66[0]:((int((fRec68[0] < fSlow50)))?(fRec66[0] + (fSlow51 * (0 - (fRec68[0] * fRec66[0])))):0.0f));
			}
			if (iSlow6 || iSlow5 || iSlow4 || iSlow2 || iSlow1) {
				fTempPerm72 = (fTempPerm71 * fTempPerm69);
			}
			if (iSlow6 || iSlow5 || iSlow2 || iSlow1) {
				fTempPerm73 = (fSlow53 * fTempPerm72);
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec69[0] = (fSlow160 + (fRec69[1] - floorf((fSlow160 + fRec69[1]))));
			}
			if (iSlow6 || iSlow5 || iSlow2 || iSlow1) {
				fTempPerm74 = ftbl0[(((int((65536.0f * (fRec69[0] + fTempPerm73))) % 65536) + 65536) % 65536)];
			}
			if (iSlow8 || iSlow7 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec71[0] = ((iSlow151)?0.0f:min(fSlow63, (fRec71[1] + 1.0f)));
				iTempPerm75 = int((fRec71[0] < fSlow60));
				fRec70[0] = ((iSlow155)?(fSlow154 * ((iTempPerm75)?((int((fRec71[0] < 0.0f)))?0.0f:((iTempPerm75)?(fSlow66 * fRec71[0]):1.0f)):((int((fRec71[0] < fSlow63)))?((fSlow162 * (fRec71[0] - fSlow60)) + 1.0f):fSlow161))):fRec70[1]);
				fRec72[0] = ((iSlow156)?0.0f:min(fSlow67, (fRec72[1] + 1.0f)));
				fTempPerm76 = ((int((fRec72[0] < 0.0f)))?fRec70[0]:((int((fRec72[0] < fSlow67)))?(fRec70[0] + (fSlow68 * (0 - (fRec72[0] * fRec70[0])))):0.0f));
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec73[0] = (fSlow163 + (fRec73[1] - floorf((fSlow163 + fRec73[1]))));
				iRec75[0] = (iSlow153 * (iRec75[1] + 1));
			}
			if (iSlow11 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				iTempPerm77 = int((iRec75[0] < iSlow80));
				fTempPerm78 = expf((0 - (fConst4 / ((iSlow155)?((iTempPerm77)?fSlow79:fSlow76):fSlow75))));
				fRec74[0] = ((fRec74[1] * fTempPerm78) + (((iSlow155)?((iTempPerm77)?1.5873015873015872f:fSlow164):0.0f) * (1.0f - fTempPerm78)));
				fTempPerm79 = min(1.0f, fRec74[0]);
			}
			if (iSlow2 || iSlow1) {
				fTempPerm80 = (fSlow166 * (fTempPerm79 * ftbl0[(((int((65536.0f * (fRec73[0] + (fSlow70 * (fTempPerm76 * fTempPerm74))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec76[0] = (fSlow168 + (fRec76[1] - floorf((fSlow168 + fRec76[1]))));
			}
			if (iSlow11 || iSlow7 || iSlow3) {
				fTempPerm81 = ftbl0[(((int((65536.0f * fRec76[0])) % 65536) + 65536) % 65536)];
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				iRec78[0] = (iSlow174 * (iRec78[1] + 1));
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8) {
				iTempPerm82 = int((iRec78[0] < iSlow172));
				fTempPerm83 = expf((0 - (fConst4 / ((iSlow175)?((iTempPerm82)?fSlow171:fSlow76):fSlow169))));
				fRec77[0] = ((fRec77[1] * fTempPerm83) + (((iSlow175)?((iTempPerm82)?1.5873015873015872f:fSlow178):0.0f) * (1.0f - fTempPerm83)));
				fTempPerm84 = min(1.0f, fRec77[0]);
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec79[0] = (fSlow179 + (fRec79[1] - floorf((fSlow179 + fRec79[1]))));
			}
			if (iSlow11 || iSlow10 || iSlow8 || iSlow7) {
				fTempPerm85 = ftbl0[(((int((65536.0f * fRec79[0])) % 65536) + 65536) % 65536)];
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow6 || iSlow5) {
				iTempPerm86 = int((iRec78[0] < iSlow183));
				fTempPerm87 = expf((0 - (fConst4 / ((iSlow175)?((iTempPerm86)?fSlow182:fSlow76):fSlow180))));
				fRec80[0] = ((fRec80[1] * fTempPerm87) + (((iSlow175)?((iTempPerm86)?1.5873015873015872f:fSlow185):0.0f) * (1.0f - fTempPerm87)));
				fTempPerm88 = min(1.0f, fRec80[0]);
			}
			if (iSlow11 || iSlow10) {
				fTempPerm89 = (fSlow69 * (fTempPerm88 * fTempPerm85));
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec81[0] = (fSlow186 + (fRec81[1] - floorf((fSlow186 + fRec81[1]))));
			}
			if (iSlow11 || iSlow10 || iSlow6) {
				fTempPerm90 = ftbl0[(((int((65536.0f * fRec81[0])) % 65536) + 65536) % 65536)];
			}
			if (iSlow11 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				iTempPerm91 = int((iRec78[0] < iSlow80));
				fTempPerm92 = expf((0 - (fConst4 / ((iSlow175)?((iTempPerm91)?fSlow79:fSlow76):fSlow75))));
				fRec82[0] = ((fRec82[1] * fTempPerm92) + (((iSlow175)?((iTempPerm91)?1.5873015873015872f:fSlow187):0.0f) * (1.0f - fTempPerm92)));
				fTempPerm93 = min(1.0f, fRec82[0]);
			}
			if (iSlow11 || iSlow6) {
				fTempPerm94 = (fSlow84 * (fTempPerm93 * fTempPerm90));
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec83[0] = (fSlow188 + (fRec83[1] - floorf((fSlow188 + fRec83[1]))));
				fTempPerm95 = ftbl0[(((int((65536.0f * fRec83[0])) % 65536) + 65536) % 65536)];
			}
			if (iSlow11 || iSlow10) {
				iTempPerm96 = int((iRec78[0] < iSlow192));
				fTempPerm97 = expf((0 - (fConst4 / ((iSlow175)?((iTempPerm96)?fSlow191:fSlow76):fSlow189))));
				fRec84[0] = ((fRec84[1] * fTempPerm97) + (((iSlow175)?((iTempPerm96)?1.5873015873015872f:fSlow194):0.0f) * (1.0f - fTempPerm97)));
				fTempPerm98 = (fSlow34 * (min(1.0f, fRec84[0]) * fTempPerm95));
			}
			if (iSlow11) {
				fTempPerm99 = (fSlow195 * (fTempPerm98 + ((fTempPerm94 + fTempPerm89) + (fSlow52 * (fTempPerm84 * fTempPerm81)))));
			}
			if (iSlow10) {
				fRec86[0] = ((iSlow203)?0.0f:min(fSlow202, (fRec86[1] + 1.0f)));
				iTempPerm100 = int((fRec86[0] < fSlow199));
				fRec85[0] = ((iSlow175)?(fSlow177 * ((iTempPerm100)?((int((fRec86[0] < 0.0f)))?0.0f:((iTempPerm100)?(fSlow206 * fRec86[0]):1.0f)):((int((fRec86[0] < fSlow202)))?((fSlow205 * (fRec86[0] - fSlow199)) + 1.0f):fSlow197))):fRec85[1]);
				fRec87[0] = ((iSlow208)?0.0f:min(fSlow207, (fRec87[1] + 1.0f)));
				fTempPerm101 = (fSlow195 * ((fTempPerm98 + fTempPerm89) + (fSlow52 * (fTempPerm84 * ftbl0[(((int((65536.0f * (fRec76[0] + (fSlow210 * (fTempPerm90 * ((int((fRec87[0] < 0.0f)))?fRec85[0]:((int((fRec87[0] < fSlow207)))?(fRec85[0] + (fSlow209 * (0 - (fRec87[0] * fRec85[0])))):0.0f))))))) % 65536) + 65536) % 65536)]))));
			}
			if (iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec89[0] = ((iSlow203)?0.0f:min(fSlow23, (fRec89[1] + 1.0f)));
				iTempPerm102 = int((fRec89[0] < fSlow20));
				fRec88[0] = ((iSlow175)?(fSlow177 * ((iTempPerm102)?((int((fRec89[0] < 0.0f)))?0.0f:((iTempPerm102)?(fSlow27 * fRec89[0]):1.0f)):((int((fRec89[0] < fSlow23)))?((fSlow212 * (fRec89[0] - fSlow20)) + 1.0f):fSlow211))):fRec88[1]);
				fRec90[0] = ((iSlow208)?0.0f:min(fSlow31, (fRec90[1] + 1.0f)));
				fTempPerm103 = (((int((fRec90[0] < 0.0f)))?fRec88[0]:((int((fRec90[0] < fSlow31)))?(fRec88[0] + (fSlow33 * (0 - (fRec90[0] * fRec88[0])))):0.0f)) * fTempPerm95);
			}
			if (iSlow9 || iSlow8 || iSlow6 || iSlow5 || iSlow4 || iSlow2 || iSlow1) {
				fTempPerm104 = (fSlow36 * fTempPerm103);
			}
			if (iSlow9 || iSlow4) {
				fTempPerm105 = ftbl0[(((int((65536.0f * (fRec79[0] + fTempPerm104))) % 65536) + 65536) % 65536)];
			}
			if (iSlow9 || iSlow8 || iSlow6 || iSlow5 || iSlow4 || iSlow2 || iSlow1) {
				fTempPerm106 = ftbl0[(((int((65536.0f * (fRec76[0] + fTempPerm104))) % 65536) + 65536) % 65536)];
			}
			if (iSlow9 || iSlow8) {
				fTempPerm107 = (fSlow52 * (fTempPerm84 * fTempPerm106));
			}
			if (iSlow9) {
				fTempPerm108 = (fSlow195 * (fTempPerm107 + ((fSlow84 * (fTempPerm93 * ftbl0[(((int((65536.0f * (fRec81[0] + fTempPerm104))) % 65536) + 65536) % 65536)])) + (fSlow69 * (fTempPerm88 * fTempPerm105)))));
			}
			if (iSlow8 || iSlow7 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec92[0] = ((iSlow203)?0.0f:min(fSlow63, (fRec92[1] + 1.0f)));
				iTempPerm109 = int((fRec92[0] < fSlow60));
				fRec91[0] = ((iSlow175)?(fSlow177 * ((iTempPerm109)?((int((fRec92[0] < 0.0f)))?0.0f:((iTempPerm109)?(fSlow66 * fRec92[0]):1.0f)):((int((fRec92[0] < fSlow63)))?((fSlow214 * (fRec92[0] - fSlow60)) + 1.0f):fSlow213))):fRec91[1]);
				fRec93[0] = ((iSlow208)?0.0f:min(fSlow67, (fRec93[1] + 1.0f)));
				fTempPerm110 = ((int((fRec93[0] < 0.0f)))?fRec91[0]:((int((fRec93[0] < fSlow67)))?(fRec91[0] + (fSlow68 * (0 - (fRec93[0] * fRec91[0])))):0.0f));
			}
			if (iSlow8 || iSlow7) {
				fTempPerm111 = (fTempPerm110 * fTempPerm85);
			}
			if (iSlow8) {
				fTempPerm112 = (fSlow195 * ((fSlow84 * (fTempPerm93 * ftbl0[(((int((65536.0f * (fRec81[0] + (fSlow70 * fTempPerm111)))) % 65536) + 65536) % 65536)])) + fTempPerm107));
			}
			if (iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec95[0] = ((iSlow203)?0.0f:min(fSlow46, (fRec95[1] + 1.0f)));
				iTempPerm113 = int((fRec95[0] < fSlow43));
				fRec94[0] = ((iSlow175)?(fSlow177 * ((iTempPerm113)?((int((fRec95[0] < 0.0f)))?0.0f:((iTempPerm113)?(fSlow49 * fRec95[0]):1.0f)):((int((fRec95[0] < fSlow46)))?((fSlow216 * (fRec95[0] - fSlow43)) + 1.0f):fSlow215))):fRec94[1]);
				fRec96[0] = ((iSlow208)?0.0f:min(fSlow50, (fRec96[1] + 1.0f)));
				fTempPerm114 = ((int((fRec96[0] < 0.0f)))?fRec94[0]:((int((fRec96[0] < fSlow50)))?(fRec94[0] + (fSlow51 * (0 - (fRec96[0] * fRec94[0])))):0.0f));
			}
			if (iSlow7 || iSlow3) {
				fTempPerm115 = (fTempPerm114 * fTempPerm81);
				fTempPerm116 = (fSlow34 * fTempPerm103);
			}
			if (iSlow7) {
				fTempPerm117 = (fSlow217 * (fTempPerm93 * ftbl0[(((int((65536.0f * (fRec81[0] + (fSlow35 * ((fTempPerm116 + (fSlow52 * fTempPerm115)) + (fSlow69 * fTempPerm111)))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow6 || iSlow5 || iSlow4 || iSlow2 || iSlow1) {
				fTempPerm118 = (fTempPerm114 * fTempPerm106);
			}
			if (iSlow6 || iSlow5 || iSlow2 || iSlow1) {
				fTempPerm119 = (fSlow53 * fTempPerm118);
				fTempPerm120 = ftbl0[(((int((65536.0f * (fRec79[0] + fTempPerm119))) % 65536) + 65536) % 65536)];
			}
			if (iSlow6 || iSlow5) {
				fTempPerm121 = (fSlow69 * (fTempPerm88 * fTempPerm120));
			}
			if (iSlow6) {
				fTempPerm122 = (fSlow195 * (fTempPerm121 + fTempPerm94));
			}
			if (iSlow5) {
				fTempPerm123 = (fSlow195 * ((fSlow84 * (fTempPerm93 * ftbl0[(((int((65536.0f * (fRec81[0] + fTempPerm119))) % 65536) + 65536) % 65536)])) + fTempPerm121));
			}
			if (iSlow4) {
				fTempPerm124 = (fSlow217 * (fTempPerm93 * ftbl0[(((int((65536.0f * (fRec81[0] + (fSlow35 * ((fSlow52 * fTempPerm118) + (fSlow69 * (fTempPerm110 * fTempPerm105))))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow3) {
				fTempPerm125 = (fSlow217 * (fTempPerm93 * ftbl0[(((int((65536.0f * (fRec81[0] + (fSlow35 * (fTempPerm116 + (fSlow69 * (fTempPerm110 * ftbl0[(((int((65536.0f * (fRec79[0] + (fSlow53 * fTempPerm115)))) % 65536) + 65536) % 65536)]))))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow2 || iSlow1) {
				fTempPerm126 = (fSlow217 * (fTempPerm93 * ftbl0[(((int((65536.0f * (fRec81[0] + (fSlow70 * (fTempPerm110 * fTempPerm120))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow11 || iSlow7 || iSlow3) {
				fTempPerm127 = ftbl0[(((int((65536.0f * fRec65[0])) % 65536) + 65536) % 65536)];
			}
			if (iSlow7 || iSlow3) {
				fTempPerm128 = (fTempPerm71 * fTempPerm127);
				fTempPerm129 = (fSlow34 * fTempPerm67);
			}
			if (iSlow3) {
				fTempPerm130 = (fSlow166 * (fTempPerm79 * ftbl0[(((int((65536.0f * (fRec73[0] + (fSlow35 * (fTempPerm129 + (fSlow69 * (fTempPerm76 * ftbl0[(((int((65536.0f * (fRec69[0] + (fSlow53 * fTempPerm128)))) % 65536) + 65536) % 65536)]))))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow9 || iSlow4) {
				fTempPerm131 = ftbl0[(((int((65536.0f * (fRec69[0] + fTempPerm68))) % 65536) + 65536) % 65536)];
			}
			if (iSlow4) {
				fTempPerm132 = (fSlow166 * (fTempPerm79 * ftbl0[(((int((65536.0f * (fRec73[0] + (fSlow35 * ((fSlow52 * fTempPerm72) + (fSlow69 * (fTempPerm76 * fTempPerm131))))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow6 || iSlow5) {
				iTempPerm133 = int((iRec75[0] < iSlow183));
				fTempPerm134 = expf((0 - (fConst4 / ((iSlow155)?((iTempPerm133)?fSlow182:fSlow76):fSlow180))));
				fRec97[0] = ((fRec97[1] * fTempPerm134) + (((iSlow155)?((iTempPerm133)?1.5873015873015872f:fSlow218):0.0f) * (1.0f - fTempPerm134)));
				fTempPerm135 = min(1.0f, fRec97[0]);
			}
			if (iSlow6 || iSlow5) {
				fTempPerm136 = (fSlow69 * (fTempPerm135 * fTempPerm74));
			}
			if (iSlow5) {
				fTempPerm137 = (fSlow165 * ((fSlow84 * (fTempPerm79 * ftbl0[(((int((65536.0f * (fRec73[0] + fTempPerm73))) % 65536) + 65536) % 65536)])) + fTempPerm136));
			}
			if (iSlow11 || iSlow10 || iSlow6) {
				fTempPerm138 = ftbl0[(((int((65536.0f * fRec73[0])) % 65536) + 65536) % 65536)];
			}
			if (iSlow11 || iSlow6) {
				fTempPerm139 = (fSlow84 * (fTempPerm79 * fTempPerm138));
			}
			if (iSlow6) {
				fTempPerm140 = (fSlow165 * (fTempPerm136 + fTempPerm139));
			}
			if (iSlow11 || iSlow10 || iSlow8 || iSlow7) {
				fTempPerm141 = ftbl0[(((int((65536.0f * fRec69[0])) % 65536) + 65536) % 65536)];
			}
			if (iSlow8 || iSlow7) {
				fTempPerm142 = (fTempPerm76 * fTempPerm141);
			}
			if (iSlow7) {
				fTempPerm143 = (fSlow166 * (fTempPerm79 * ftbl0[(((int((65536.0f * (fRec73[0] + (fSlow35 * ((fTempPerm129 + (fSlow52 * fTempPerm128)) + (fSlow69 * fTempPerm142)))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8) {
				iTempPerm144 = int((iRec75[0] < iSlow172));
				fTempPerm145 = expf((0 - (fConst4 / ((iSlow155)?((iTempPerm144)?fSlow171:fSlow76):fSlow169))));
				fRec98[0] = ((fRec98[1] * fTempPerm145) + (((iSlow155)?((iTempPerm144)?1.5873015873015872f:fSlow219):0.0f) * (1.0f - fTempPerm145)));
				fTempPerm146 = min(1.0f, fRec98[0]);
			}
			if (iSlow9 || iSlow8) {
				fTempPerm147 = (fSlow52 * (fTempPerm146 * fTempPerm69));
			}
			if (iSlow8) {
				fTempPerm148 = (fSlow165 * ((fSlow84 * (fTempPerm79 * ftbl0[(((int((65536.0f * (fRec73[0] + (fSlow70 * fTempPerm142)))) % 65536) + 65536) % 65536)])) + fTempPerm147));
			}
			if (iSlow9) {
				fTempPerm149 = (fSlow165 * (fTempPerm147 + ((fSlow84 * (fTempPerm79 * ftbl0[(((int((65536.0f * (fRec73[0] + fTempPerm68))) % 65536) + 65536) % 65536)])) + (fSlow69 * (fTempPerm135 * fTempPerm131)))));
			}
			if (iSlow10) {
				fRec100[0] = ((iSlow151)?0.0f:min(fSlow202, (fRec100[1] + 1.0f)));
				iTempPerm150 = int((fRec100[0] < fSlow199));
				fRec99[0] = ((iSlow155)?(fSlow154 * ((iTempPerm150)?((int((fRec100[0] < 0.0f)))?0.0f:((iTempPerm150)?(fSlow206 * fRec100[0]):1.0f)):((int((fRec100[0] < fSlow202)))?((fSlow221 * (fRec100[0] - fSlow199)) + 1.0f):fSlow220))):fRec99[1]);
				fRec101[0] = ((iSlow156)?0.0f:min(fSlow207, (fRec101[1] + 1.0f)));
			}
			if (iSlow11 || iSlow10) {
				fTempPerm151 = (fSlow69 * (fTempPerm135 * fTempPerm141));
				iTempPerm152 = int((iRec75[0] < iSlow192));
				fTempPerm153 = expf((0 - (fConst4 / ((iSlow155)?((iTempPerm152)?fSlow191:fSlow76):fSlow189))));
				fRec102[0] = ((fRec102[1] * fTempPerm153) + (((iSlow155)?((iTempPerm152)?1.5873015873015872f:fSlow222):0.0f) * (1.0f - fTempPerm153)));
				fTempPerm154 = (fSlow34 * (min(1.0f, fRec102[0]) * fTempPerm65));
			}
			if (iSlow10) {
				fTempPerm155 = (fSlow165 * ((fTempPerm154 + fTempPerm151) + (fSlow52 * (fTempPerm146 * ftbl0[(((int((65536.0f * (fRec65[0] + (fSlow210 * (fTempPerm138 * ((int((fRec101[0] < 0.0f)))?fRec99[0]:((int((fRec101[0] < fSlow207)))?(fRec99[0] + (fSlow209 * (0 - (fRec101[0] * fRec99[0])))):0.0f))))))) % 65536) + 65536) % 65536)]))));
			}
			if (iSlow11) {
				fTempPerm156 = (fSlow165 * (fTempPerm154 + ((fTempPerm139 + fTempPerm151) + (fSlow52 * (fTempPerm146 * fTempPerm127)))));
			}
			if (iSlow11 || iSlow7 || iSlow3) {
				fTempPerm157 = ftbl0[(((int((65536.0f * fRec50[0])) % 65536) + 65536) % 65536)];
			}
			if (iSlow7 || iSlow3) {
				fTempPerm158 = (fTempPerm55 * fTempPerm157);
				fTempPerm159 = (fSlow34 * fTempPerm51);
			}
			if (iSlow3) {
				fTempPerm160 = (fSlow146 * (fTempPerm63 * ftbl0[(((int((65536.0f * (fRec58[0] + (fSlow35 * (fTempPerm159 + (fSlow69 * (fTempPerm60 * ftbl0[(((int((65536.0f * (fRec54[0] + (fSlow53 * fTempPerm158)))) % 65536) + 65536) % 65536)]))))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow9 || iSlow4) {
				fTempPerm161 = ftbl0[(((int((65536.0f * (fRec54[0] + fTempPerm52))) % 65536) + 65536) % 65536)];
			}
			if (iSlow4) {
				fTempPerm162 = (fSlow146 * (fTempPerm63 * ftbl0[(((int((65536.0f * (fRec58[0] + (fSlow35 * ((fSlow52 * fTempPerm56) + (fSlow69 * (fTempPerm60 * fTempPerm161))))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow6 || iSlow5) {
				iTempPerm163 = int((iRec60[0] < iSlow183));
				fTempPerm164 = expf((0 - (fConst4 / ((iSlow135)?((iTempPerm163)?fSlow182:fSlow76):fSlow180))));
				fRec103[0] = ((fRec103[1] * fTempPerm164) + (((iSlow135)?((iTempPerm163)?1.5873015873015872f:fSlow223):0.0f) * (1.0f - fTempPerm164)));
				fTempPerm165 = min(1.0f, fRec103[0]);
			}
			if (iSlow6 || iSlow5) {
				fTempPerm166 = (fSlow69 * (fTempPerm165 * fTempPerm58));
			}
			if (iSlow5) {
				fTempPerm167 = (fSlow145 * ((fSlow84 * (fTempPerm63 * ftbl0[(((int((65536.0f * (fRec58[0] + fTempPerm57))) % 65536) + 65536) % 65536)])) + fTempPerm166));
			}
			if (iSlow11 || iSlow10 || iSlow6) {
				fTempPerm168 = ftbl0[(((int((65536.0f * fRec58[0])) % 65536) + 65536) % 65536)];
			}
			if (iSlow11 || iSlow6) {
				fTempPerm169 = (fSlow84 * (fTempPerm63 * fTempPerm168));
			}
			if (iSlow6) {
				fTempPerm170 = (fSlow145 * (fTempPerm166 + fTempPerm169));
			}
			if (iSlow11 || iSlow10 || iSlow8 || iSlow7) {
				fTempPerm171 = ftbl0[(((int((65536.0f * fRec54[0])) % 65536) + 65536) % 65536)];
			}
			if (iSlow8 || iSlow7) {
				fTempPerm172 = (fTempPerm60 * fTempPerm171);
			}
			if (iSlow7) {
				fTempPerm173 = (fSlow146 * (fTempPerm63 * ftbl0[(((int((65536.0f * (fRec58[0] + (fSlow35 * ((fTempPerm159 + (fSlow52 * fTempPerm158)) + (fSlow69 * fTempPerm172)))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8) {
				iTempPerm174 = int((iRec60[0] < iSlow172));
				fTempPerm175 = expf((0 - (fConst4 / ((iSlow135)?((iTempPerm174)?fSlow171:fSlow76):fSlow169))));
				fRec104[0] = ((fRec104[1] * fTempPerm175) + (((iSlow135)?((iTempPerm174)?1.5873015873015872f:fSlow224):0.0f) * (1.0f - fTempPerm175)));
				fTempPerm176 = min(1.0f, fRec104[0]);
			}
			if (iSlow9 || iSlow8) {
				fTempPerm177 = (fSlow52 * (fTempPerm176 * fTempPerm53));
			}
			if (iSlow8) {
				fTempPerm178 = (fSlow145 * ((fSlow84 * (fTempPerm63 * ftbl0[(((int((65536.0f * (fRec58[0] + (fSlow70 * fTempPerm172)))) % 65536) + 65536) % 65536)])) + fTempPerm177));
			}
			if (iSlow9) {
				fTempPerm179 = (fSlow145 * (fTempPerm177 + ((fSlow84 * (fTempPerm63 * ftbl0[(((int((65536.0f * (fRec58[0] + fTempPerm52))) % 65536) + 65536) % 65536)])) + (fSlow69 * (fTempPerm165 * fTempPerm161)))));
			}
			if (iSlow10) {
				fRec106[0] = ((iSlow131)?0.0f:min(fSlow202, (fRec106[1] + 1.0f)));
				iTempPerm180 = int((fRec106[0] < fSlow199));
				fRec105[0] = ((iSlow135)?(fSlow134 * ((iTempPerm180)?((int((fRec106[0] < 0.0f)))?0.0f:((iTempPerm180)?(fSlow206 * fRec106[0]):1.0f)):((int((fRec106[0] < fSlow202)))?((fSlow226 * (fRec106[0] - fSlow199)) + 1.0f):fSlow225))):fRec105[1]);
				fRec107[0] = ((iSlow136)?0.0f:min(fSlow207, (fRec107[1] + 1.0f)));
			}
			if (iSlow11 || iSlow10) {
				fTempPerm181 = (fSlow69 * (fTempPerm165 * fTempPerm171));
				iTempPerm182 = int((iRec60[0] < iSlow192));
				fTempPerm183 = expf((0 - (fConst4 / ((iSlow135)?((iTempPerm182)?fSlow191:fSlow76):fSlow189))));
				fRec108[0] = ((fRec108[1] * fTempPerm183) + (((iSlow135)?((iTempPerm182)?1.5873015873015872f:fSlow227):0.0f) * (1.0f - fTempPerm183)));
				fTempPerm184 = (fSlow34 * (min(1.0f, fRec108[0]) * fTempPerm49));
			}
			if (iSlow10) {
				fTempPerm185 = (fSlow145 * ((fTempPerm184 + fTempPerm181) + (fSlow52 * (fTempPerm176 * ftbl0[(((int((65536.0f * (fRec50[0] + (fSlow210 * (fTempPerm168 * ((int((fRec107[0] < 0.0f)))?fRec105[0]:((int((fRec107[0] < fSlow207)))?(fRec105[0] + (fSlow209 * (0 - (fRec107[0] * fRec105[0])))):0.0f))))))) % 65536) + 65536) % 65536)]))));
			}
			if (iSlow11) {
				fTempPerm186 = (fSlow145 * (fTempPerm184 + ((fTempPerm169 + fTempPerm181) + (fSlow52 * (fTempPerm176 * fTempPerm157)))));
			}
			if (iSlow11 || iSlow7 || iSlow3) {
				fTempPerm187 = ftbl0[(((int((65536.0f * fRec35[0])) % 65536) + 65536) % 65536)];
			}
			if (iSlow7 || iSlow3) {
				fTempPerm188 = (fTempPerm39 * fTempPerm187);
				fTempPerm189 = (fSlow34 * fTempPerm35);
			}
			if (iSlow3) {
				fTempPerm190 = (fSlow126 * (fTempPerm47 * ftbl0[(((int((65536.0f * (fRec43[0] + (fSlow35 * (fTempPerm189 + (fSlow69 * (fTempPerm44 * ftbl0[(((int((65536.0f * (fRec39[0] + (fSlow53 * fTempPerm188)))) % 65536) + 65536) % 65536)]))))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow9 || iSlow4) {
				fTempPerm191 = ftbl0[(((int((65536.0f * (fRec39[0] + fTempPerm36))) % 65536) + 65536) % 65536)];
			}
			if (iSlow4) {
				fTempPerm192 = (fSlow126 * (fTempPerm47 * ftbl0[(((int((65536.0f * (fRec43[0] + (fSlow35 * ((fSlow52 * fTempPerm40) + (fSlow69 * (fTempPerm44 * fTempPerm191))))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow6 || iSlow5) {
				iTempPerm193 = int((iRec45[0] < iSlow183));
				fTempPerm194 = expf((0 - (fConst4 / ((iSlow115)?((iTempPerm193)?fSlow182:fSlow76):fSlow180))));
				fRec109[0] = ((fRec109[1] * fTempPerm194) + (((iSlow115)?((iTempPerm193)?1.5873015873015872f:fSlow228):0.0f) * (1.0f - fTempPerm194)));
				fTempPerm195 = min(1.0f, fRec109[0]);
			}
			if (iSlow6 || iSlow5) {
				fTempPerm196 = (fSlow69 * (fTempPerm195 * fTempPerm42));
			}
			if (iSlow5) {
				fTempPerm197 = (fSlow125 * ((fSlow84 * (fTempPerm47 * ftbl0[(((int((65536.0f * (fRec43[0] + fTempPerm41))) % 65536) + 65536) % 65536)])) + fTempPerm196));
			}
			if (iSlow11 || iSlow10 || iSlow6) {
				fTempPerm198 = ftbl0[(((int((65536.0f * fRec43[0])) % 65536) + 65536) % 65536)];
			}
			if (iSlow11 || iSlow6) {
				fTempPerm199 = (fSlow84 * (fTempPerm47 * fTempPerm198));
			}
			if (iSlow6) {
				fTempPerm200 = (fSlow125 * (fTempPerm196 + fTempPerm199));
			}
			if (iSlow11 || iSlow10 || iSlow8 || iSlow7) {
				fTempPerm201 = ftbl0[(((int((65536.0f * fRec39[0])) % 65536) + 65536) % 65536)];
			}
			if (iSlow8 || iSlow7) {
				fTempPerm202 = (fTempPerm44 * fTempPerm201);
			}
			if (iSlow7) {
				fTempPerm203 = (fSlow126 * (fTempPerm47 * ftbl0[(((int((65536.0f * (fRec43[0] + (fSlow35 * ((fTempPerm189 + (fSlow52 * fTempPerm188)) + (fSlow69 * fTempPerm202)))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8) {
				iTempPerm204 = int((iRec45[0] < iSlow172));
				fTempPerm205 = expf((0 - (fConst4 / ((iSlow115)?((iTempPerm204)?fSlow171:fSlow76):fSlow169))));
				fRec110[0] = ((fRec110[1] * fTempPerm205) + (((iSlow115)?((iTempPerm204)?1.5873015873015872f:fSlow229):0.0f) * (1.0f - fTempPerm205)));
				fTempPerm206 = min(1.0f, fRec110[0]);
			}
			if (iSlow9 || iSlow8) {
				fTempPerm207 = (fSlow52 * (fTempPerm206 * fTempPerm37));
			}
			if (iSlow8) {
				fTempPerm208 = (fSlow125 * ((fSlow84 * (fTempPerm47 * ftbl0[(((int((65536.0f * (fRec43[0] + (fSlow70 * fTempPerm202)))) % 65536) + 65536) % 65536)])) + fTempPerm207));
			}
			if (iSlow9) {
				fTempPerm209 = (fSlow125 * (fTempPerm207 + ((fSlow84 * (fTempPerm47 * ftbl0[(((int((65536.0f * (fRec43[0] + fTempPerm36))) % 65536) + 65536) % 65536)])) + (fSlow69 * (fTempPerm195 * fTempPerm191)))));
			}
			if (iSlow10) {
				fRec112[0] = ((iSlow111)?0.0f:min(fSlow202, (fRec112[1] + 1.0f)));
				iTempPerm210 = int((fRec112[0] < fSlow199));
				fRec111[0] = ((iSlow115)?(fSlow114 * ((iTempPerm210)?((int((fRec112[0] < 0.0f)))?0.0f:((iTempPerm210)?(fSlow206 * fRec112[0]):1.0f)):((int((fRec112[0] < fSlow202)))?((fSlow231 * (fRec112[0] - fSlow199)) + 1.0f):fSlow230))):fRec111[1]);
				fRec113[0] = ((iSlow116)?0.0f:min(fSlow207, (fRec113[1] + 1.0f)));
			}
			if (iSlow11 || iSlow10) {
				fTempPerm211 = (fSlow69 * (fTempPerm195 * fTempPerm201));
				iTempPerm212 = int((iRec45[0] < iSlow192));
				fTempPerm213 = expf((0 - (fConst4 / ((iSlow115)?((iTempPerm212)?fSlow191:fSlow76):fSlow189))));
				fRec114[0] = ((fRec114[1] * fTempPerm213) + (((iSlow115)?((iTempPerm212)?1.5873015873015872f:fSlow232):0.0f) * (1.0f - fTempPerm213)));
				fTempPerm214 = (fSlow34 * (min(1.0f, fRec114[0]) * fTempPerm33));
			}
			if (iSlow10) {
				fTempPerm215 = (fSlow125 * ((fTempPerm214 + fTempPerm211) + (fSlow52 * (fTempPerm206 * ftbl0[(((int((65536.0f * (fRec35[0] + (fSlow210 * (fTempPerm198 * ((int((fRec113[0] < 0.0f)))?fRec111[0]:((int((fRec113[0] < fSlow207)))?(fRec111[0] + (fSlow209 * (0 - (fRec113[0] * fRec111[0])))):0.0f))))))) % 65536) + 65536) % 65536)]))));
			}
			if (iSlow11) {
				fTempPerm216 = (fSlow125 * (fTempPerm214 + ((fTempPerm199 + fTempPerm211) + (fSlow52 * (fTempPerm206 * fTempPerm187)))));
			}
			if (iSlow11 || iSlow7 || iSlow3) {
				fTempPerm217 = ftbl0[(((int((65536.0f * fRec20[0])) % 65536) + 65536) % 65536)];
			}
			if (iSlow7 || iSlow3) {
				fTempPerm218 = (fTempPerm23 * fTempPerm217);
				fTempPerm219 = (fSlow34 * fTempPerm19);
			}
			if (iSlow3) {
				fTempPerm220 = (fSlow106 * (fTempPerm31 * ftbl0[(((int((65536.0f * (fRec28[0] + (fSlow35 * (fTempPerm219 + (fSlow69 * (fTempPerm28 * ftbl0[(((int((65536.0f * (fRec24[0] + (fSlow53 * fTempPerm218)))) % 65536) + 65536) % 65536)]))))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow9 || iSlow4) {
				fTempPerm221 = ftbl0[(((int((65536.0f * (fRec24[0] + fTempPerm20))) % 65536) + 65536) % 65536)];
			}
			if (iSlow4) {
				fTempPerm222 = (fSlow106 * (fTempPerm31 * ftbl0[(((int((65536.0f * (fRec28[0] + (fSlow35 * ((fSlow52 * fTempPerm24) + (fSlow69 * (fTempPerm28 * fTempPerm221))))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow6 || iSlow5) {
				iTempPerm223 = int((iRec30[0] < iSlow183));
				fTempPerm224 = expf((0 - (fConst4 / ((iSlow95)?((iTempPerm223)?fSlow182:fSlow76):fSlow180))));
				fRec115[0] = ((fRec115[1] * fTempPerm224) + (((iSlow95)?((iTempPerm223)?1.5873015873015872f:fSlow233):0.0f) * (1.0f - fTempPerm224)));
				fTempPerm225 = min(1.0f, fRec115[0]);
			}
			if (iSlow6 || iSlow5) {
				fTempPerm226 = (fSlow69 * (fTempPerm225 * fTempPerm26));
			}
			if (iSlow5) {
				fTempPerm227 = (fSlow105 * ((fSlow84 * (fTempPerm31 * ftbl0[(((int((65536.0f * (fRec28[0] + fTempPerm25))) % 65536) + 65536) % 65536)])) + fTempPerm226));
			}
			if (iSlow11 || iSlow10 || iSlow6) {
				fTempPerm228 = ftbl0[(((int((65536.0f * fRec28[0])) % 65536) + 65536) % 65536)];
			}
			if (iSlow11 || iSlow6) {
				fTempPerm229 = (fSlow84 * (fTempPerm31 * fTempPerm228));
			}
			if (iSlow6) {
				fTempPerm230 = (fSlow105 * (fTempPerm226 + fTempPerm229));
			}
			if (iSlow11 || iSlow10 || iSlow8 || iSlow7) {
				fTempPerm231 = ftbl0[(((int((65536.0f * fRec24[0])) % 65536) + 65536) % 65536)];
			}
			if (iSlow8 || iSlow7) {
				fTempPerm232 = (fTempPerm28 * fTempPerm231);
			}
			if (iSlow7) {
				fTempPerm233 = (fSlow106 * (fTempPerm31 * ftbl0[(((int((65536.0f * (fRec28[0] + (fSlow35 * ((fTempPerm219 + (fSlow52 * fTempPerm218)) + (fSlow69 * fTempPerm232)))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8) {
				iTempPerm234 = int((iRec30[0] < iSlow172));
				fTempPerm235 = expf((0 - (fConst4 / ((iSlow95)?((iTempPerm234)?fSlow171:fSlow76):fSlow169))));
				fRec116[0] = ((fRec116[1] * fTempPerm235) + (((iSlow95)?((iTempPerm234)?1.5873015873015872f:fSlow234):0.0f) * (1.0f - fTempPerm235)));
				fTempPerm236 = min(1.0f, fRec116[0]);
			}
			if (iSlow9 || iSlow8) {
				fTempPerm237 = (fSlow52 * (fTempPerm236 * fTempPerm21));
			}
			if (iSlow8) {
				fTempPerm238 = (fSlow105 * ((fSlow84 * (fTempPerm31 * ftbl0[(((int((65536.0f * (fRec28[0] + (fSlow70 * fTempPerm232)))) % 65536) + 65536) % 65536)])) + fTempPerm237));
			}
			if (iSlow9) {
				fTempPerm239 = (fSlow105 * (fTempPerm237 + ((fSlow84 * (fTempPerm31 * ftbl0[(((int((65536.0f * (fRec28[0] + fTempPerm20))) % 65536) + 65536) % 65536)])) + (fSlow69 * (fTempPerm225 * fTempPerm221)))));
			}
			if (iSlow10) {
				fRec118[0] = ((iSlow91)?0.0f:min(fSlow202, (fRec118[1] + 1.0f)));
				iTempPerm240 = int((fRec118[0] < fSlow199));
				fRec117[0] = ((iSlow95)?(fSlow94 * ((iTempPerm240)?((int((fRec118[0] < 0.0f)))?0.0f:((iTempPerm240)?(fSlow206 * fRec118[0]):1.0f)):((int((fRec118[0] < fSlow202)))?((fSlow236 * (fRec118[0] - fSlow199)) + 1.0f):fSlow235))):fRec117[1]);
				fRec119[0] = ((iSlow96)?0.0f:min(fSlow207, (fRec119[1] + 1.0f)));
			}
			if (iSlow11 || iSlow10) {
				fTempPerm241 = (fSlow69 * (fTempPerm225 * fTempPerm231));
				iTempPerm242 = int((iRec30[0] < iSlow192));
				fTempPerm243 = expf((0 - (fConst4 / ((iSlow95)?((iTempPerm242)?fSlow191:fSlow76):fSlow189))));
				fRec120[0] = ((fRec120[1] * fTempPerm243) + (((iSlow95)?((iTempPerm242)?1.5873015873015872f:fSlow237):0.0f) * (1.0f - fTempPerm243)));
				fTempPerm244 = (fSlow34 * (min(1.0f, fRec120[0]) * fTempPerm17));
			}
			if (iSlow10) {
				fTempPerm245 = (fSlow105 * ((fTempPerm244 + fTempPerm241) + (fSlow52 * (fTempPerm236 * ftbl0[(((int((65536.0f * (fRec20[0] + (fSlow210 * (fTempPerm228 * ((int((fRec119[0] < 0.0f)))?fRec117[0]:((int((fRec119[0] < fSlow207)))?(fRec117[0] + (fSlow209 * (0 - (fRec119[0] * fRec117[0])))):0.0f))))))) % 65536) + 65536) % 65536)]))));
			}
			if (iSlow11) {
				fTempPerm246 = (fSlow105 * (fTempPerm244 + ((fTempPerm229 + fTempPerm241) + (fSlow52 * (fTempPerm236 * fTempPerm217)))));
			}
			if (iSlow11 || iSlow7 || iSlow3) {
				fTempPerm247 = ftbl0[(((int((65536.0f * fRec5[0])) % 65536) + 65536) % 65536)];
			}
			if (iSlow7 || iSlow3) {
				fTempPerm248 = (fTempPerm7 * fTempPerm247);
				fTempPerm249 = (fSlow34 * fTempPerm3);
			}
			if (iSlow3) {
				fTempPerm250 = (fSlow86 * (fTempPerm15 * ftbl0[(((int((65536.0f * (fRec13[0] + (fSlow35 * (fTempPerm249 + (fSlow69 * (fTempPerm12 * ftbl0[(((int((65536.0f * (fRec9[0] + (fSlow53 * fTempPerm248)))) % 65536) + 65536) % 65536)]))))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow9 || iSlow4) {
				fTempPerm251 = ftbl0[(((int((65536.0f * (fRec9[0] + fTempPerm4))) % 65536) + 65536) % 65536)];
			}
			if (iSlow4) {
				fTempPerm252 = (fSlow86 * (fTempPerm15 * ftbl0[(((int((65536.0f * (fRec13[0] + (fSlow35 * ((fSlow52 * fTempPerm8) + (fSlow69 * (fTempPerm12 * fTempPerm251))))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow6 || iSlow5) {
				iTempPerm253 = int((iRec15[0] < iSlow183));
				fTempPerm254 = expf((0 - (fConst4 / ((iSlow30)?((iTempPerm253)?fSlow182:fSlow76):fSlow180))));
				fRec121[0] = ((fRec121[1] * fTempPerm254) + (((iSlow30)?((iTempPerm253)?1.5873015873015872f:fSlow238):0.0f) * (1.0f - fTempPerm254)));
				fTempPerm255 = min(1.0f, fRec121[0]);
			}
			if (iSlow6 || iSlow5) {
				fTempPerm256 = (fSlow69 * (fTempPerm255 * fTempPerm10));
			}
			if (iSlow5) {
				fTempPerm257 = (fSlow85 * ((fSlow84 * (fTempPerm15 * ftbl0[(((int((65536.0f * (fRec13[0] + fTempPerm9))) % 65536) + 65536) % 65536)])) + fTempPerm256));
			}
			if (iSlow11 || iSlow10 || iSlow6) {
				fTempPerm258 = ftbl0[(((int((65536.0f * fRec13[0])) % 65536) + 65536) % 65536)];
			}
			if (iSlow11 || iSlow6) {
				fTempPerm259 = (fSlow84 * (fTempPerm15 * fTempPerm258));
			}
			if (iSlow6) {
				fTempPerm260 = (fSlow85 * (fTempPerm256 + fTempPerm259));
			}
			if (iSlow11 || iSlow10 || iSlow8 || iSlow7) {
				fTempPerm261 = ftbl0[(((int((65536.0f * fRec9[0])) % 65536) + 65536) % 65536)];
			}
			if (iSlow8 || iSlow7) {
				fTempPerm262 = (fTempPerm12 * fTempPerm261);
			}
			if (iSlow7) {
				fTempPerm263 = (fSlow86 * (fTempPerm15 * ftbl0[(((int((65536.0f * (fRec13[0] + (fSlow35 * ((fTempPerm249 + (fSlow52 * fTempPerm248)) + (fSlow69 * fTempPerm262)))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8) {
				iTempPerm264 = int((iRec15[0] < iSlow172));
				fTempPerm265 = expf((0 - (fConst4 / ((iSlow30)?((iTempPerm264)?fSlow171:fSlow76):fSlow169))));
				fRec122[0] = ((fRec122[1] * fTempPerm265) + (((iSlow30)?((iTempPerm264)?1.5873015873015872f:fSlow239):0.0f) * (1.0f - fTempPerm265)));
				fTempPerm266 = min(1.0f, fRec122[0]);
			}
			if (iSlow9 || iSlow8) {
				fTempPerm267 = (fSlow52 * (fTempPerm266 * fTempPerm5));
			}
			if (iSlow8) {
				fTempPerm268 = (fSlow85 * ((fSlow84 * (fTempPerm15 * ftbl0[(((int((65536.0f * (fRec13[0] + (fSlow70 * fTempPerm262)))) % 65536) + 65536) % 65536)])) + fTempPerm267));
			}
			if (iSlow9) {
				fTempPerm269 = (fSlow85 * (fTempPerm267 + ((fSlow84 * (fTempPerm15 * ftbl0[(((int((65536.0f * (fRec13[0] + fTempPerm4))) % 65536) + 65536) % 65536)])) + (fSlow69 * (fTempPerm255 * fTempPerm251)))));
			}
			if (iSlow10) {
				fRec124[0] = ((iSlow24)?0.0f:min(fSlow202, (fRec124[1] + 1.0f)));
				iTempPerm270 = int((fRec124[0] < fSlow199));
				fRec123[0] = ((iSlow30)?(fSlow29 * ((iTempPerm270)?((int((fRec124[0] < 0.0f)))?0.0f:((iTempPerm270)?(fSlow206 * fRec124[0]):1.0f)):((int((fRec124[0] < fSlow202)))?((fSlow241 * (fRec124[0] - fSlow199)) + 1.0f):fSlow240))):fRec123[1]);
				fRec125[0] = ((iSlow32)?0.0f:min(fSlow207, (fRec125[1] + 1.0f)));
			}
			if (iSlow11 || iSlow10) {
				fTempPerm271 = (fSlow69 * (fTempPerm255 * fTempPerm261));
				iTempPerm272 = int((iRec15[0] < iSlow192));
				fTempPerm273 = expf((0 - (fConst4 / ((iSlow30)?((iTempPerm272)?fSlow191:fSlow76):fSlow189))));
				fRec126[0] = ((fRec126[1] * fTempPerm273) + (((iSlow30)?((iTempPerm272)?1.5873015873015872f:fSlow242):0.0f) * (1.0f - fTempPerm273)));
				fTempPerm274 = (fSlow34 * (min(1.0f, fRec126[0]) * fTempPerm1));
			}
			if (iSlow10) {
				fTempPerm275 = (fSlow85 * ((fTempPerm274 + fTempPerm271) + (fSlow52 * (fTempPerm266 * ftbl0[(((int((65536.0f * (fRec5[0] + (fSlow210 * (fTempPerm258 * ((int((fRec125[0] < 0.0f)))?fRec123[0]:((int((fRec125[0] < fSlow207)))?(fRec123[0] + (fSlow209 * (0 - (fRec125[0] * fRec123[0])))):0.0f))))))) % 65536) + 65536) % 65536)]))));
			}
			if (iSlow11) {
				fTempPerm276 = (fSlow85 * (fTempPerm274 + ((fTempPerm259 + fTempPerm271) + (fSlow52 * (fTempPerm266 * fTempPerm247)))));
			}
			output0[i] = (FAUSTFLOAT)(fTempPerm276 + (fTempPerm275 + (fTempPerm269 + (fTempPerm268 + (fTempPerm263 + (fTempPerm260 + (fTempPerm257 + (fTempPerm252 + (fTempPerm250 + (fTempPerm16 + ((fTempPerm246 + (fTempPerm245 + (fTempPerm239 + (fTempPerm238 + (fTempPerm233 + (fTempPerm230 + (fTempPerm227 + (fTempPerm222 + (fTempPerm220 + (fTempPerm32 + ((fTempPerm216 + (fTempPerm215 + (fTempPerm209 + (fTempPerm208 + (fTempPerm203 + (fTempPerm200 + (fTempPerm197 + (fTempPerm192 + (fTempPerm190 + (fTempPerm48 + ((fTempPerm186 + (fTempPerm185 + (fTempPerm179 + (fTempPerm178 + (fTempPerm173 + (fTempPerm170 + (fTempPerm167 + (fTempPerm162 + (fTempPerm160 + (fTempPerm64 + ((fTempPerm156 + (fTempPerm155 + (fTempPerm149 + (fTempPerm148 + (fTempPerm143 + (fTempPerm140 + (fTempPerm137 + (fTempPerm132 + (fTempPerm130 + (fTempPerm80 + (((((((((((fTempPerm126 + fTempPerm126) + fTempPerm125) + fTempPerm124) + fTempPerm123) + fTempPerm122) + fTempPerm117) + fTempPerm112) + fTempPerm108) + fTempPerm101) + fTempPerm99) + fTempPerm80))))))))))) + fTempPerm64))))))))))) + fTempPerm48))))))))))) + fTempPerm32))))))))))) + fTempPerm16)))))))))));
			// post processing
			if (iSlow11 || iSlow10) {
				fRec126[1] = fRec126[0];
			}
			if (iSlow10) {
				fRec125[1] = fRec125[0];
				fRec123[1] = fRec123[0];
				fRec124[1] = fRec124[0];
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8) {
				fRec122[1] = fRec122[0];
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow6 || iSlow5) {
				fRec121[1] = fRec121[0];
			}
			if (iSlow11 || iSlow10) {
				fRec120[1] = fRec120[0];
			}
			if (iSlow10) {
				fRec119[1] = fRec119[0];
				fRec117[1] = fRec117[0];
				fRec118[1] = fRec118[0];
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8) {
				fRec116[1] = fRec116[0];
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow6 || iSlow5) {
				fRec115[1] = fRec115[0];
			}
			if (iSlow11 || iSlow10) {
				fRec114[1] = fRec114[0];
			}
			if (iSlow10) {
				fRec113[1] = fRec113[0];
				fRec111[1] = fRec111[0];
				fRec112[1] = fRec112[0];
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8) {
				fRec110[1] = fRec110[0];
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow6 || iSlow5) {
				fRec109[1] = fRec109[0];
			}
			if (iSlow11 || iSlow10) {
				fRec108[1] = fRec108[0];
			}
			if (iSlow10) {
				fRec107[1] = fRec107[0];
				fRec105[1] = fRec105[0];
				fRec106[1] = fRec106[0];
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8) {
				fRec104[1] = fRec104[0];
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow6 || iSlow5) {
				fRec103[1] = fRec103[0];
			}
			if (iSlow11 || iSlow10) {
				fRec102[1] = fRec102[0];
			}
			if (iSlow10) {
				fRec101[1] = fRec101[0];
				fRec99[1] = fRec99[0];
				fRec100[1] = fRec100[0];
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8) {
				fRec98[1] = fRec98[0];
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow6 || iSlow5) {
				fRec97[1] = fRec97[0];
			}
			if (iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec96[1] = fRec96[0];
				fRec94[1] = fRec94[0];
				fRec95[1] = fRec95[0];
			}
			if (iSlow8 || iSlow7 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec93[1] = fRec93[0];
				fRec91[1] = fRec91[0];
				fRec92[1] = fRec92[0];
			}
			if (iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec90[1] = fRec90[0];
				fRec88[1] = fRec88[0];
				fRec89[1] = fRec89[0];
			}
			if (iSlow10) {
				fRec87[1] = fRec87[0];
				fRec85[1] = fRec85[0];
				fRec86[1] = fRec86[0];
			}
			if (iSlow11 || iSlow10) {
				fRec84[1] = fRec84[0];
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec83[1] = fRec83[0];
			}
			if (iSlow11 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec82[1] = fRec82[0];
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec81[1] = fRec81[0];
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow6 || iSlow5) {
				fRec80[1] = fRec80[0];
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec79[1] = fRec79[0];
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8) {
				fRec77[1] = fRec77[0];
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				iRec78[1] = iRec78[0];
				fRec76[1] = fRec76[0];
			}
			if (iSlow11 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec74[1] = fRec74[0];
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				iRec75[1] = iRec75[0];
				fRec73[1] = fRec73[0];
			}
			if (iSlow8 || iSlow7 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec72[1] = fRec72[0];
				fRec70[1] = fRec70[0];
				fRec71[1] = fRec71[0];
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec69[1] = fRec69[0];
			}
			if (iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec68[1] = fRec68[0];
				fRec66[1] = fRec66[0];
				fRec67[1] = fRec67[0];
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec65[1] = fRec65[0];
			}
			if (iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec64[1] = fRec64[0];
				fRec62[1] = fRec62[0];
				fRec63[1] = fRec63[0];
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec61[1] = fRec61[0];
			}
			if (iSlow11 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec59[1] = fRec59[0];
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				iRec60[1] = iRec60[0];
				fRec58[1] = fRec58[0];
			}
			if (iSlow8 || iSlow7 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec57[1] = fRec57[0];
				fRec55[1] = fRec55[0];
				fRec56[1] = fRec56[0];
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec54[1] = fRec54[0];
			}
			if (iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec53[1] = fRec53[0];
				fRec51[1] = fRec51[0];
				fRec52[1] = fRec52[0];
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec50[1] = fRec50[0];
			}
			if (iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec49[1] = fRec49[0];
				fRec47[1] = fRec47[0];
				fRec48[1] = fRec48[0];
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec46[1] = fRec46[0];
			}
			if (iSlow11 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec44[1] = fRec44[0];
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				iRec45[1] = iRec45[0];
				fRec43[1] = fRec43[0];
			}
			if (iSlow8 || iSlow7 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec42[1] = fRec42[0];
				fRec40[1] = fRec40[0];
				fRec41[1] = fRec41[0];
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec39[1] = fRec39[0];
			}
			if (iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec38[1] = fRec38[0];
				fRec36[1] = fRec36[0];
				fRec37[1] = fRec37[0];
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec35[1] = fRec35[0];
			}
			if (iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec34[1] = fRec34[0];
				fRec32[1] = fRec32[0];
				fRec33[1] = fRec33[0];
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec31[1] = fRec31[0];
			}
			if (iSlow11 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec29[1] = fRec29[0];
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				iRec30[1] = iRec30[0];
				fRec28[1] = fRec28[0];
			}
			if (iSlow8 || iSlow7 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec27[1] = fRec27[0];
				fRec25[1] = fRec25[0];
				fRec26[1] = fRec26[0];
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec24[1] = fRec24[0];
			}
			if (iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec23[1] = fRec23[0];
				fRec21[1] = fRec21[0];
				fRec22[1] = fRec22[0];
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec20[1] = fRec20[0];
			}
			if (iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec19[1] = fRec19[0];
				fRec17[1] = fRec17[0];
				fRec18[1] = fRec18[0];
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec16[1] = fRec16[0];
			}
			if (iSlow11 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec14[1] = fRec14[0];
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				iRec15[1] = iRec15[0];
				fRec13[1] = fRec13[0];
			}
			if (iSlow8 || iSlow7 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec12[1] = fRec12[0];
				fRec10[1] = fRec10[0];
				fRec11[1] = fRec11[0];
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec9[1] = fRec9[0];
			}
			if (iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec8[1] = fRec8[0];
				fRec6[1] = fRec6[0];
				fRec7[1] = fRec7[0];
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec5[1] = fRec5[0];
			}
			if (iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec4[1] = fRec4[0];
				fRec2[1] = fRec2[0];
				fRec3[1] = fRec3[0];
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow5 || iSlow4 || iSlow3 || iSlow2 || iSlow1) {
				fRec1[1] = fRec1[0];
			}
		}
	}
};


float 	faust_ottofm::ftbl0[65536];
