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
		int 	iRec1[2];
		float 	fTempPerm0;
	  public:
		int getNumInputs() { return 0; }
		int getNumOutputs() { return 1; }
		void init(int samplingFreq) {
			fSamplingFreq = samplingFreq;
			fTempPerm0 = 0;
			for (int i=0; i<2; i++) iRec1[i] = 0;
		}
		void fill (int count, float output[]) {
			for (int i=0; i<count; i++) {
				iRec1[0] = (iRec1[1] + 1);
				fTempPerm0 = sinf((9.5873799242852573e-05f * float((iRec1[0] + -1))));
				output[i] = fTempPerm0;
				// post processing
				iRec1[1] = iRec1[0];
			}
		}
	};


	FAUSTFLOAT 	fslider0;
	static float 	ftbl0[65536];
	FAUSTFLOAT 	fslider1;
	float 	fRec2[2];
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT 	fslider3;
	FAUSTFLOAT 	fslider4;
	float 	fConst0;
	float 	fConst1;
	float 	fRec3[2];
	FAUSTFLOAT 	fslider5;
	FAUSTFLOAT 	fbutton0;
	FAUSTFLOAT 	fslider6;
	float 	fConst2;
	FAUSTFLOAT 	fslider7;
	float 	fRec5[2];
	float 	fConst3;
	int 	iTempPerm1;
	float 	fRec4[2];
	float 	fRec6[2];
	float 	fTempPerm2;
	FAUSTFLOAT 	fbargraph0;
	float 	fTempPerm3;
	FAUSTFLOAT 	fslider8;
	FAUSTFLOAT 	fslider9;
	float 	fTempPerm4;
	FAUSTFLOAT 	fslider10;
	FAUSTFLOAT 	fslider11;
	float 	fRec7[2];
	FAUSTFLOAT 	fslider12;
	FAUSTFLOAT 	fslider13;
	FAUSTFLOAT 	fslider14;
	int 	iRec9[2];
	int 	iTempPerm5;
	float 	fConst4;
	float 	fTempPerm6;
	FAUSTFLOAT 	fslider15;
	float 	fRec8[2];
	float 	fTempPerm7;
	FAUSTFLOAT 	fbargraph1;
	float 	fTempPerm8;
	FAUSTFLOAT 	fslider16;
	FAUSTFLOAT 	fslider17;
	float 	fRec0[2];
	FAUSTFLOAT 	fslider18;
	float 	fRec11[2];
	FAUSTFLOAT 	fslider19;
	FAUSTFLOAT 	fslider20;
	float 	fRec12[2];
	FAUSTFLOAT 	fslider21;
	FAUSTFLOAT 	fslider22;
	FAUSTFLOAT 	fslider23;
	float 	fRec14[2];
	int 	iTempPerm9;
	float 	fRec13[2];
	float 	fRec15[2];
	float 	fTempPerm10;
	FAUSTFLOAT 	fbargraph2;
	float 	fTempPerm11;
	float 	fTempPerm12;
	FAUSTFLOAT 	fslider24;
	FAUSTFLOAT 	fslider25;
	FAUSTFLOAT 	fslider26;
	float 	fRec16[2];
	FAUSTFLOAT 	fbargraph3;
	float 	fTempPerm13;
	FAUSTFLOAT 	fslider27;
	float 	fRec10[2];
	float 	fTempPerm14;
	float 	fRec17[2];
	FAUSTFLOAT 	fslider28;
	FAUSTFLOAT 	fslider29;
	FAUSTFLOAT 	fslider30;
	float 	fRec20[2];
	int 	iTempPerm15;
	float 	fRec19[2];
	float 	fRec21[2];
	float 	fTempPerm16;
	FAUSTFLOAT 	fbargraph4;
	FAUSTFLOAT 	fslider31;
	float 	fRec22[2];
	FAUSTFLOAT 	fbargraph5;
	float 	fTempPerm17;
	float 	fRec18[2];
	FAUSTFLOAT 	fslider32;
	float 	fRec24[2];
	FAUSTFLOAT 	fbargraph6;
	float 	fRec23[2];
	float 	fTempPerm18;
	FAUSTFLOAT 	fslider33;
	FAUSTFLOAT 	fslider34;
	FAUSTFLOAT 	fslider35;
	float 	fRec27[2];
	int 	iTempPerm19;
	float 	fRec26[2];
	float 	fRec28[2];
	float 	fTempPerm20;
	FAUSTFLOAT 	fbargraph7;
	float 	fTempPerm21;
	float 	fTempPerm22;
	float 	fTempPerm23;
	float 	fTempPerm24;
	float 	fRec25[2];
	float 	fTempPerm25;
	float 	fTempPerm26;
	float 	fRec29[2];
	float 	fRec30[2];
	float 	fTempPerm27;
	float 	fRec31[2];
	float 	fRec32[2];
	float 	fRec33[2];
	float 	fRec34[2];
	FAUSTFLOAT 	fslider36;
	float 	fRec36[2];
	FAUSTFLOAT 	fbutton1;
	int 	iRec38[2];
	int 	iTempPerm28;
	float 	fTempPerm29;
	float 	fRec37[2];
	float 	fTempPerm30;
	FAUSTFLOAT 	fbargraph8;
	float 	fTempPerm31;
	FAUSTFLOAT 	fslider37;
	float 	fRec35[2];
	float 	fRec40[2];
	float 	fRec42[2];
	int 	iTempPerm32;
	float 	fRec41[2];
	float 	fRec43[2];
	float 	fTempPerm33;
	FAUSTFLOAT 	fbargraph9;
	float 	fRec44[2];
	FAUSTFLOAT 	fbargraph10;
	float 	fTempPerm34;
	float 	fRec39[2];
	float 	fRec46[2];
	FAUSTFLOAT 	fbargraph11;
	float 	fRec45[2];
	float 	fTempPerm35;
	float 	fRec49[2];
	int 	iTempPerm36;
	float 	fRec48[2];
	float 	fRec50[2];
	float 	fTempPerm37;
	FAUSTFLOAT 	fbargraph12;
	float 	fTempPerm38;
	float 	fTempPerm39;
	float 	fRec47[2];
	float 	fRec53[2];
	int 	iTempPerm40;
	float 	fRec52[2];
	float 	fRec54[2];
	float 	fTempPerm41;
	FAUSTFLOAT 	fbargraph13;
	float 	fTempPerm42;
	float 	fTempPerm43;
	FAUSTFLOAT 	fbargraph14;
	float 	fTempPerm44;
	float 	fRec51[2];
	float 	fTempPerm45;
	float 	fRec57[2];
	int 	iTempPerm46;
	float 	fRec56[2];
	float 	fRec58[2];
	float 	fTempPerm47;
	FAUSTFLOAT 	fbargraph15;
	float 	fTempPerm48;
	float 	fTempPerm49;
	float 	fTempPerm50;
	float 	fTempPerm51;
	float 	fRec55[2];
	float 	fTempPerm52;
	float 	fTempPerm53;
	float 	fRec59[2];
	float 	fRec60[2];
	float 	fTempPerm54;
	float 	fRec61[2];
	float 	fRec62[2];
	float 	fRec63[2];
	float 	fRec64[2];
	FAUSTFLOAT 	fslider38;
	float 	fRec66[2];
	FAUSTFLOAT 	fbutton2;
	int 	iRec68[2];
	int 	iTempPerm55;
	float 	fTempPerm56;
	float 	fRec67[2];
	float 	fTempPerm57;
	FAUSTFLOAT 	fbargraph16;
	float 	fTempPerm58;
	FAUSTFLOAT 	fslider39;
	float 	fRec65[2];
	float 	fRec70[2];
	float 	fRec72[2];
	int 	iTempPerm59;
	float 	fRec71[2];
	float 	fRec73[2];
	float 	fTempPerm60;
	FAUSTFLOAT 	fbargraph17;
	float 	fRec74[2];
	FAUSTFLOAT 	fbargraph18;
	float 	fTempPerm61;
	float 	fRec69[2];
	float 	fRec76[2];
	FAUSTFLOAT 	fbargraph19;
	float 	fRec75[2];
	float 	fTempPerm62;
	float 	fRec79[2];
	int 	iTempPerm63;
	float 	fRec78[2];
	float 	fRec80[2];
	float 	fTempPerm64;
	FAUSTFLOAT 	fbargraph20;
	float 	fTempPerm65;
	float 	fTempPerm66;
	float 	fRec77[2];
	float 	fRec83[2];
	int 	iTempPerm67;
	float 	fRec82[2];
	float 	fRec84[2];
	float 	fTempPerm68;
	FAUSTFLOAT 	fbargraph21;
	float 	fTempPerm69;
	float 	fTempPerm70;
	FAUSTFLOAT 	fbargraph22;
	float 	fTempPerm71;
	float 	fRec81[2];
	float 	fTempPerm72;
	float 	fRec87[2];
	int 	iTempPerm73;
	float 	fRec86[2];
	float 	fRec88[2];
	float 	fTempPerm74;
	FAUSTFLOAT 	fbargraph23;
	float 	fTempPerm75;
	float 	fTempPerm76;
	float 	fTempPerm77;
	float 	fTempPerm78;
	float 	fRec85[2];
	float 	fTempPerm79;
	float 	fTempPerm80;
	float 	fRec89[2];
	float 	fRec90[2];
	float 	fTempPerm81;
	float 	fRec91[2];
	float 	fRec92[2];
	float 	fRec93[2];
	float 	fRec94[2];
	FAUSTFLOAT 	fslider40;
	float 	fRec96[2];
	FAUSTFLOAT 	fbutton3;
	int 	iRec98[2];
	int 	iTempPerm82;
	float 	fTempPerm83;
	float 	fRec97[2];
	float 	fTempPerm84;
	FAUSTFLOAT 	fbargraph24;
	float 	fTempPerm85;
	FAUSTFLOAT 	fslider41;
	float 	fRec95[2];
	float 	fRec100[2];
	float 	fRec102[2];
	int 	iTempPerm86;
	float 	fRec101[2];
	float 	fRec103[2];
	float 	fTempPerm87;
	FAUSTFLOAT 	fbargraph25;
	float 	fRec104[2];
	FAUSTFLOAT 	fbargraph26;
	float 	fTempPerm88;
	float 	fRec99[2];
	float 	fRec106[2];
	FAUSTFLOAT 	fbargraph27;
	float 	fRec105[2];
	float 	fTempPerm89;
	float 	fRec109[2];
	int 	iTempPerm90;
	float 	fRec108[2];
	float 	fRec110[2];
	float 	fTempPerm91;
	FAUSTFLOAT 	fbargraph28;
	float 	fTempPerm92;
	float 	fTempPerm93;
	float 	fRec107[2];
	float 	fRec113[2];
	int 	iTempPerm94;
	float 	fRec112[2];
	float 	fRec114[2];
	float 	fTempPerm95;
	FAUSTFLOAT 	fbargraph29;
	float 	fTempPerm96;
	float 	fTempPerm97;
	FAUSTFLOAT 	fbargraph30;
	float 	fTempPerm98;
	float 	fRec111[2];
	float 	fTempPerm99;
	float 	fRec117[2];
	int 	iTempPerm100;
	float 	fRec116[2];
	float 	fRec118[2];
	float 	fTempPerm101;
	FAUSTFLOAT 	fbargraph31;
	float 	fTempPerm102;
	float 	fTempPerm103;
	float 	fTempPerm104;
	float 	fTempPerm105;
	float 	fRec115[2];
	float 	fTempPerm106;
	float 	fTempPerm107;
	float 	fRec119[2];
	float 	fRec120[2];
	float 	fTempPerm108;
	float 	fRec121[2];
	float 	fRec122[2];
	float 	fRec123[2];
	float 	fRec124[2];
	FAUSTFLOAT 	fslider42;
	float 	fRec126[2];
	FAUSTFLOAT 	fbutton4;
	int 	iRec128[2];
	int 	iTempPerm109;
	float 	fTempPerm110;
	float 	fRec127[2];
	float 	fTempPerm111;
	FAUSTFLOAT 	fbargraph32;
	float 	fTempPerm112;
	FAUSTFLOAT 	fslider43;
	float 	fRec125[2];
	float 	fRec130[2];
	float 	fRec132[2];
	int 	iTempPerm113;
	float 	fRec131[2];
	float 	fRec133[2];
	float 	fTempPerm114;
	FAUSTFLOAT 	fbargraph33;
	float 	fRec134[2];
	FAUSTFLOAT 	fbargraph34;
	float 	fTempPerm115;
	float 	fRec129[2];
	float 	fRec136[2];
	FAUSTFLOAT 	fbargraph35;
	float 	fRec135[2];
	float 	fTempPerm116;
	float 	fRec139[2];
	int 	iTempPerm117;
	float 	fRec138[2];
	float 	fRec140[2];
	float 	fTempPerm118;
	FAUSTFLOAT 	fbargraph36;
	float 	fTempPerm119;
	float 	fTempPerm120;
	float 	fRec137[2];
	float 	fRec143[2];
	int 	iTempPerm121;
	float 	fRec142[2];
	float 	fRec144[2];
	float 	fTempPerm122;
	FAUSTFLOAT 	fbargraph37;
	float 	fTempPerm123;
	float 	fTempPerm124;
	FAUSTFLOAT 	fbargraph38;
	float 	fTempPerm125;
	float 	fRec141[2];
	float 	fTempPerm126;
	float 	fRec147[2];
	int 	iTempPerm127;
	float 	fRec146[2];
	float 	fRec148[2];
	float 	fTempPerm128;
	FAUSTFLOAT 	fbargraph39;
	float 	fTempPerm129;
	float 	fTempPerm130;
	float 	fTempPerm131;
	float 	fTempPerm132;
	float 	fRec145[2];
	float 	fTempPerm133;
	float 	fTempPerm134;
	float 	fRec149[2];
	float 	fRec150[2];
	float 	fTempPerm135;
	float 	fRec151[2];
	float 	fRec152[2];
	float 	fRec153[2];
	float 	fRec154[2];
	FAUSTFLOAT 	fslider44;
	float 	fRec156[2];
	FAUSTFLOAT 	fbutton5;
	int 	iRec158[2];
	int 	iTempPerm136;
	float 	fTempPerm137;
	float 	fRec157[2];
	float 	fTempPerm138;
	FAUSTFLOAT 	fbargraph40;
	float 	fTempPerm139;
	FAUSTFLOAT 	fslider45;
	float 	fRec155[2];
	float 	fRec160[2];
	float 	fRec162[2];
	int 	iTempPerm140;
	float 	fRec161[2];
	float 	fRec163[2];
	float 	fTempPerm141;
	FAUSTFLOAT 	fbargraph41;
	float 	fRec164[2];
	FAUSTFLOAT 	fbargraph42;
	float 	fTempPerm142;
	float 	fRec159[2];
	float 	fRec166[2];
	FAUSTFLOAT 	fbargraph43;
	float 	fRec165[2];
	float 	fTempPerm143;
	float 	fRec169[2];
	int 	iTempPerm144;
	float 	fRec168[2];
	float 	fRec170[2];
	float 	fTempPerm145;
	FAUSTFLOAT 	fbargraph44;
	float 	fTempPerm146;
	float 	fTempPerm147;
	float 	fRec167[2];
	float 	fRec173[2];
	int 	iTempPerm148;
	float 	fRec172[2];
	float 	fRec174[2];
	float 	fTempPerm149;
	FAUSTFLOAT 	fbargraph45;
	float 	fTempPerm150;
	float 	fTempPerm151;
	FAUSTFLOAT 	fbargraph46;
	float 	fTempPerm152;
	float 	fRec171[2];
	float 	fTempPerm153;
	float 	fRec177[2];
	int 	iTempPerm154;
	float 	fRec176[2];
	float 	fRec178[2];
	float 	fTempPerm155;
	FAUSTFLOAT 	fbargraph47;
	float 	fTempPerm156;
	float 	fTempPerm157;
	float 	fTempPerm158;
	float 	fTempPerm159;
	float 	fRec175[2];
	float 	fTempPerm160;
	float 	fTempPerm161;
	float 	fRec179[2];
	float 	fRec180[2];
	float 	fTempPerm162;
	float 	fRec181[2];
	float 	fRec182[2];
	float 	fRec183[2];
	float 	fRec184[2];
	float 	fRec185[2];
	float 	fTempPerm163;
	float 	fRec186[2];
	float 	fRec187[2];
	float 	fTempPerm164;
	float 	fRec188[2];
	float 	fTempPerm165;
	float 	fRec189[2];
	float 	fTempPerm166;
	float 	fRec190[2];
	float 	fRec191[2];
	float 	fTempPerm167;
	float 	fRec192[2];
	float 	fTempPerm168;
	float 	fRec193[2];
	float 	fTempPerm169;
	float 	fRec194[2];
	float 	fRec195[2];
	float 	fTempPerm170;
	float 	fRec196[2];
	float 	fTempPerm171;
	float 	fRec197[2];
	float 	fTempPerm172;
	float 	fRec198[2];
	float 	fRec199[2];
	float 	fTempPerm173;
	float 	fRec200[2];
	float 	fTempPerm174;
	float 	fRec201[2];
	float 	fTempPerm175;
	float 	fRec202[2];
	float 	fRec203[2];
	float 	fTempPerm176;
	float 	fRec204[2];
	float 	fTempPerm177;
	float 	fRec205[2];
	float 	fTempPerm178;
	float 	fRec206[2];
	float 	fRec207[2];
	float 	fTempPerm179;
	float 	fRec208[2];
	float 	fTempPerm180;
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
		fConst2 = (3.0f * fConst0);
		fConst3 = (0.33333333333333331f / fConst0);
		iTempPerm1 = 0;
		fTempPerm2 = 0;
		fTempPerm3 = 0;
		fTempPerm4 = 0;
		iTempPerm5 = 0;
		fConst4 = (6.9100000000000001f / fConst0);
		fTempPerm6 = 0;
		fTempPerm7 = 0;
		fTempPerm8 = 0;
		iTempPerm9 = 0;
		fTempPerm10 = 0;
		fTempPerm11 = 0;
		fTempPerm12 = 0;
		fTempPerm13 = 0;
		fTempPerm14 = 0;
		iTempPerm15 = 0;
		fTempPerm16 = 0;
		fTempPerm17 = 0;
		fTempPerm18 = 0;
		iTempPerm19 = 0;
		fTempPerm20 = 0;
		fTempPerm21 = 0;
		fTempPerm22 = 0;
		fTempPerm23 = 0;
		fTempPerm24 = 0;
		fTempPerm25 = 0;
		fTempPerm26 = 0;
		fTempPerm27 = 0;
		iTempPerm28 = 0;
		fTempPerm29 = 0;
		fTempPerm30 = 0;
		fTempPerm31 = 0;
		iTempPerm32 = 0;
		fTempPerm33 = 0;
		fTempPerm34 = 0;
		fTempPerm35 = 0;
		iTempPerm36 = 0;
		fTempPerm37 = 0;
		fTempPerm38 = 0;
		fTempPerm39 = 0;
		iTempPerm40 = 0;
		fTempPerm41 = 0;
		fTempPerm42 = 0;
		fTempPerm43 = 0;
		fTempPerm44 = 0;
		fTempPerm45 = 0;
		iTempPerm46 = 0;
		fTempPerm47 = 0;
		fTempPerm48 = 0;
		fTempPerm49 = 0;
		fTempPerm50 = 0;
		fTempPerm51 = 0;
		fTempPerm52 = 0;
		fTempPerm53 = 0;
		fTempPerm54 = 0;
		iTempPerm55 = 0;
		fTempPerm56 = 0;
		fTempPerm57 = 0;
		fTempPerm58 = 0;
		iTempPerm59 = 0;
		fTempPerm60 = 0;
		fTempPerm61 = 0;
		fTempPerm62 = 0;
		iTempPerm63 = 0;
		fTempPerm64 = 0;
		fTempPerm65 = 0;
		fTempPerm66 = 0;
		iTempPerm67 = 0;
		fTempPerm68 = 0;
		fTempPerm69 = 0;
		fTempPerm70 = 0;
		fTempPerm71 = 0;
		fTempPerm72 = 0;
		iTempPerm73 = 0;
		fTempPerm74 = 0;
		fTempPerm75 = 0;
		fTempPerm76 = 0;
		fTempPerm77 = 0;
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
		iTempPerm90 = 0;
		fTempPerm91 = 0;
		fTempPerm92 = 0;
		fTempPerm93 = 0;
		iTempPerm94 = 0;
		fTempPerm95 = 0;
		fTempPerm96 = 0;
		fTempPerm97 = 0;
		fTempPerm98 = 0;
		fTempPerm99 = 0;
		iTempPerm100 = 0;
		fTempPerm101 = 0;
		fTempPerm102 = 0;
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
		iTempPerm117 = 0;
		fTempPerm118 = 0;
		fTempPerm119 = 0;
		fTempPerm120 = 0;
		iTempPerm121 = 0;
		fTempPerm122 = 0;
		fTempPerm123 = 0;
		fTempPerm124 = 0;
		fTempPerm125 = 0;
		fTempPerm126 = 0;
		iTempPerm127 = 0;
		fTempPerm128 = 0;
		fTempPerm129 = 0;
		fTempPerm130 = 0;
		fTempPerm131 = 0;
		fTempPerm132 = 0;
		fTempPerm133 = 0;
		fTempPerm134 = 0;
		fTempPerm135 = 0;
		iTempPerm136 = 0;
		fTempPerm137 = 0;
		fTempPerm138 = 0;
		fTempPerm139 = 0;
		iTempPerm140 = 0;
		fTempPerm141 = 0;
		fTempPerm142 = 0;
		fTempPerm143 = 0;
		iTempPerm144 = 0;
		fTempPerm145 = 0;
		fTempPerm146 = 0;
		fTempPerm147 = 0;
		iTempPerm148 = 0;
		fTempPerm149 = 0;
		fTempPerm150 = 0;
		fTempPerm151 = 0;
		fTempPerm152 = 0;
		fTempPerm153 = 0;
		iTempPerm154 = 0;
		fTempPerm155 = 0;
		fTempPerm156 = 0;
		fTempPerm157 = 0;
		fTempPerm158 = 0;
		fTempPerm159 = 0;
		fTempPerm160 = 0;
		fTempPerm161 = 0;
		fTempPerm162 = 0;
		fTempPerm163 = 0;
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
		fTempPerm174 = 0;
		fTempPerm175 = 0;
		fTempPerm176 = 0;
		fTempPerm177 = 0;
		fTempPerm178 = 0;
		fTempPerm179 = 0;
		fTempPerm180 = 0;
	}
	virtual void instanceResetUserInterface() {
		fslider0 = 0.0f;
		fslider1 = 0.0f;
		fslider2 = 1.0f;
		fslider3 = 440.0f;
		fslider4 = 0.0f;
		fslider5 = 0.0f;
		fbutton0 = 0.0;
		fslider6 = 0.0f;
		fslider7 = 0.0f;
		fslider8 = 1.0f;
		fslider9 = 1.0f;
		fslider10 = 1.0f;
		fslider11 = 0.0f;
		fslider12 = 0.0f;
		fslider13 = 0.0f;
		fslider14 = 0.001f;
		fslider15 = 1.0f;
		fslider16 = 1.0f;
		fslider17 = 1.0f;
		fslider18 = 0.0f;
		fslider19 = 1.0f;
		fslider20 = 0.0f;
		fslider21 = 0.0f;
		fslider22 = 0.0f;
		fslider23 = 0.0f;
		fslider24 = 1.0f;
		fslider25 = 1.0f;
		fslider26 = 0.0f;
		fslider27 = 1.0f;
		fslider28 = 0.0f;
		fslider29 = 0.0f;
		fslider30 = 0.0f;
		fslider31 = 0.0f;
		fslider32 = 0.0f;
		fslider33 = 0.0f;
		fslider34 = 0.0f;
		fslider35 = 0.0f;
		fslider36 = 440.0f;
		fbutton1 = 0.0;
		fslider37 = 1.0f;
		fslider38 = 440.0f;
		fbutton2 = 0.0;
		fslider39 = 1.0f;
		fslider40 = 440.0f;
		fbutton3 = 0.0;
		fslider41 = 1.0f;
		fslider42 = 440.0f;
		fbutton4 = 0.0;
		fslider43 = 1.0f;
		fslider44 = 440.0f;
		fbutton5 = 0.0;
		fslider45 = 1.0f;
	}
	virtual void instanceClear() {
		for (int i=0; i<2; i++) fRec2[i] = 0;
		for (int i=0; i<2; i++) fRec3[i] = 0;
		for (int i=0; i<2; i++) fRec5[i] = 0;
		for (int i=0; i<2; i++) fRec4[i] = 0;
		for (int i=0; i<2; i++) fRec6[i] = 0;
		for (int i=0; i<2; i++) fRec7[i] = 0;
		for (int i=0; i<2; i++) iRec9[i] = 0;
		for (int i=0; i<2; i++) fRec8[i] = 0;
		for (int i=0; i<2; i++) fRec0[i] = 0;
		for (int i=0; i<2; i++) fRec11[i] = 0;
		for (int i=0; i<2; i++) fRec12[i] = 0;
		for (int i=0; i<2; i++) fRec14[i] = 0;
		for (int i=0; i<2; i++) fRec13[i] = 0;
		for (int i=0; i<2; i++) fRec15[i] = 0;
		for (int i=0; i<2; i++) fRec16[i] = 0;
		for (int i=0; i<2; i++) fRec10[i] = 0;
		for (int i=0; i<2; i++) fRec17[i] = 0;
		for (int i=0; i<2; i++) fRec20[i] = 0;
		for (int i=0; i<2; i++) fRec19[i] = 0;
		for (int i=0; i<2; i++) fRec21[i] = 0;
		for (int i=0; i<2; i++) fRec22[i] = 0;
		for (int i=0; i<2; i++) fRec18[i] = 0;
		for (int i=0; i<2; i++) fRec24[i] = 0;
		for (int i=0; i<2; i++) fRec23[i] = 0;
		for (int i=0; i<2; i++) fRec27[i] = 0;
		for (int i=0; i<2; i++) fRec26[i] = 0;
		for (int i=0; i<2; i++) fRec28[i] = 0;
		for (int i=0; i<2; i++) fRec25[i] = 0;
		for (int i=0; i<2; i++) fRec29[i] = 0;
		for (int i=0; i<2; i++) fRec30[i] = 0;
		for (int i=0; i<2; i++) fRec31[i] = 0;
		for (int i=0; i<2; i++) fRec32[i] = 0;
		for (int i=0; i<2; i++) fRec33[i] = 0;
		for (int i=0; i<2; i++) fRec34[i] = 0;
		for (int i=0; i<2; i++) fRec36[i] = 0;
		for (int i=0; i<2; i++) iRec38[i] = 0;
		for (int i=0; i<2; i++) fRec37[i] = 0;
		for (int i=0; i<2; i++) fRec35[i] = 0;
		for (int i=0; i<2; i++) fRec40[i] = 0;
		for (int i=0; i<2; i++) fRec42[i] = 0;
		for (int i=0; i<2; i++) fRec41[i] = 0;
		for (int i=0; i<2; i++) fRec43[i] = 0;
		for (int i=0; i<2; i++) fRec44[i] = 0;
		for (int i=0; i<2; i++) fRec39[i] = 0;
		for (int i=0; i<2; i++) fRec46[i] = 0;
		for (int i=0; i<2; i++) fRec45[i] = 0;
		for (int i=0; i<2; i++) fRec49[i] = 0;
		for (int i=0; i<2; i++) fRec48[i] = 0;
		for (int i=0; i<2; i++) fRec50[i] = 0;
		for (int i=0; i<2; i++) fRec47[i] = 0;
		for (int i=0; i<2; i++) fRec53[i] = 0;
		for (int i=0; i<2; i++) fRec52[i] = 0;
		for (int i=0; i<2; i++) fRec54[i] = 0;
		for (int i=0; i<2; i++) fRec51[i] = 0;
		for (int i=0; i<2; i++) fRec57[i] = 0;
		for (int i=0; i<2; i++) fRec56[i] = 0;
		for (int i=0; i<2; i++) fRec58[i] = 0;
		for (int i=0; i<2; i++) fRec55[i] = 0;
		for (int i=0; i<2; i++) fRec59[i] = 0;
		for (int i=0; i<2; i++) fRec60[i] = 0;
		for (int i=0; i<2; i++) fRec61[i] = 0;
		for (int i=0; i<2; i++) fRec62[i] = 0;
		for (int i=0; i<2; i++) fRec63[i] = 0;
		for (int i=0; i<2; i++) fRec64[i] = 0;
		for (int i=0; i<2; i++) fRec66[i] = 0;
		for (int i=0; i<2; i++) iRec68[i] = 0;
		for (int i=0; i<2; i++) fRec67[i] = 0;
		for (int i=0; i<2; i++) fRec65[i] = 0;
		for (int i=0; i<2; i++) fRec70[i] = 0;
		for (int i=0; i<2; i++) fRec72[i] = 0;
		for (int i=0; i<2; i++) fRec71[i] = 0;
		for (int i=0; i<2; i++) fRec73[i] = 0;
		for (int i=0; i<2; i++) fRec74[i] = 0;
		for (int i=0; i<2; i++) fRec69[i] = 0;
		for (int i=0; i<2; i++) fRec76[i] = 0;
		for (int i=0; i<2; i++) fRec75[i] = 0;
		for (int i=0; i<2; i++) fRec79[i] = 0;
		for (int i=0; i<2; i++) fRec78[i] = 0;
		for (int i=0; i<2; i++) fRec80[i] = 0;
		for (int i=0; i<2; i++) fRec77[i] = 0;
		for (int i=0; i<2; i++) fRec83[i] = 0;
		for (int i=0; i<2; i++) fRec82[i] = 0;
		for (int i=0; i<2; i++) fRec84[i] = 0;
		for (int i=0; i<2; i++) fRec81[i] = 0;
		for (int i=0; i<2; i++) fRec87[i] = 0;
		for (int i=0; i<2; i++) fRec86[i] = 0;
		for (int i=0; i<2; i++) fRec88[i] = 0;
		for (int i=0; i<2; i++) fRec85[i] = 0;
		for (int i=0; i<2; i++) fRec89[i] = 0;
		for (int i=0; i<2; i++) fRec90[i] = 0;
		for (int i=0; i<2; i++) fRec91[i] = 0;
		for (int i=0; i<2; i++) fRec92[i] = 0;
		for (int i=0; i<2; i++) fRec93[i] = 0;
		for (int i=0; i<2; i++) fRec94[i] = 0;
		for (int i=0; i<2; i++) fRec96[i] = 0;
		for (int i=0; i<2; i++) iRec98[i] = 0;
		for (int i=0; i<2; i++) fRec97[i] = 0;
		for (int i=0; i<2; i++) fRec95[i] = 0;
		for (int i=0; i<2; i++) fRec100[i] = 0;
		for (int i=0; i<2; i++) fRec102[i] = 0;
		for (int i=0; i<2; i++) fRec101[i] = 0;
		for (int i=0; i<2; i++) fRec103[i] = 0;
		for (int i=0; i<2; i++) fRec104[i] = 0;
		for (int i=0; i<2; i++) fRec99[i] = 0;
		for (int i=0; i<2; i++) fRec106[i] = 0;
		for (int i=0; i<2; i++) fRec105[i] = 0;
		for (int i=0; i<2; i++) fRec109[i] = 0;
		for (int i=0; i<2; i++) fRec108[i] = 0;
		for (int i=0; i<2; i++) fRec110[i] = 0;
		for (int i=0; i<2; i++) fRec107[i] = 0;
		for (int i=0; i<2; i++) fRec113[i] = 0;
		for (int i=0; i<2; i++) fRec112[i] = 0;
		for (int i=0; i<2; i++) fRec114[i] = 0;
		for (int i=0; i<2; i++) fRec111[i] = 0;
		for (int i=0; i<2; i++) fRec117[i] = 0;
		for (int i=0; i<2; i++) fRec116[i] = 0;
		for (int i=0; i<2; i++) fRec118[i] = 0;
		for (int i=0; i<2; i++) fRec115[i] = 0;
		for (int i=0; i<2; i++) fRec119[i] = 0;
		for (int i=0; i<2; i++) fRec120[i] = 0;
		for (int i=0; i<2; i++) fRec121[i] = 0;
		for (int i=0; i<2; i++) fRec122[i] = 0;
		for (int i=0; i<2; i++) fRec123[i] = 0;
		for (int i=0; i<2; i++) fRec124[i] = 0;
		for (int i=0; i<2; i++) fRec126[i] = 0;
		for (int i=0; i<2; i++) iRec128[i] = 0;
		for (int i=0; i<2; i++) fRec127[i] = 0;
		for (int i=0; i<2; i++) fRec125[i] = 0;
		for (int i=0; i<2; i++) fRec130[i] = 0;
		for (int i=0; i<2; i++) fRec132[i] = 0;
		for (int i=0; i<2; i++) fRec131[i] = 0;
		for (int i=0; i<2; i++) fRec133[i] = 0;
		for (int i=0; i<2; i++) fRec134[i] = 0;
		for (int i=0; i<2; i++) fRec129[i] = 0;
		for (int i=0; i<2; i++) fRec136[i] = 0;
		for (int i=0; i<2; i++) fRec135[i] = 0;
		for (int i=0; i<2; i++) fRec139[i] = 0;
		for (int i=0; i<2; i++) fRec138[i] = 0;
		for (int i=0; i<2; i++) fRec140[i] = 0;
		for (int i=0; i<2; i++) fRec137[i] = 0;
		for (int i=0; i<2; i++) fRec143[i] = 0;
		for (int i=0; i<2; i++) fRec142[i] = 0;
		for (int i=0; i<2; i++) fRec144[i] = 0;
		for (int i=0; i<2; i++) fRec141[i] = 0;
		for (int i=0; i<2; i++) fRec147[i] = 0;
		for (int i=0; i<2; i++) fRec146[i] = 0;
		for (int i=0; i<2; i++) fRec148[i] = 0;
		for (int i=0; i<2; i++) fRec145[i] = 0;
		for (int i=0; i<2; i++) fRec149[i] = 0;
		for (int i=0; i<2; i++) fRec150[i] = 0;
		for (int i=0; i<2; i++) fRec151[i] = 0;
		for (int i=0; i<2; i++) fRec152[i] = 0;
		for (int i=0; i<2; i++) fRec153[i] = 0;
		for (int i=0; i<2; i++) fRec154[i] = 0;
		for (int i=0; i<2; i++) fRec156[i] = 0;
		for (int i=0; i<2; i++) iRec158[i] = 0;
		for (int i=0; i<2; i++) fRec157[i] = 0;
		for (int i=0; i<2; i++) fRec155[i] = 0;
		for (int i=0; i<2; i++) fRec160[i] = 0;
		for (int i=0; i<2; i++) fRec162[i] = 0;
		for (int i=0; i<2; i++) fRec161[i] = 0;
		for (int i=0; i<2; i++) fRec163[i] = 0;
		for (int i=0; i<2; i++) fRec164[i] = 0;
		for (int i=0; i<2; i++) fRec159[i] = 0;
		for (int i=0; i<2; i++) fRec166[i] = 0;
		for (int i=0; i<2; i++) fRec165[i] = 0;
		for (int i=0; i<2; i++) fRec169[i] = 0;
		for (int i=0; i<2; i++) fRec168[i] = 0;
		for (int i=0; i<2; i++) fRec170[i] = 0;
		for (int i=0; i<2; i++) fRec167[i] = 0;
		for (int i=0; i<2; i++) fRec173[i] = 0;
		for (int i=0; i<2; i++) fRec172[i] = 0;
		for (int i=0; i<2; i++) fRec174[i] = 0;
		for (int i=0; i<2; i++) fRec171[i] = 0;
		for (int i=0; i<2; i++) fRec177[i] = 0;
		for (int i=0; i<2; i++) fRec176[i] = 0;
		for (int i=0; i<2; i++) fRec178[i] = 0;
		for (int i=0; i<2; i++) fRec175[i] = 0;
		for (int i=0; i<2; i++) fRec179[i] = 0;
		for (int i=0; i<2; i++) fRec180[i] = 0;
		for (int i=0; i<2; i++) fRec181[i] = 0;
		for (int i=0; i<2; i++) fRec182[i] = 0;
		for (int i=0; i<2; i++) fRec183[i] = 0;
		for (int i=0; i<2; i++) fRec184[i] = 0;
		for (int i=0; i<2; i++) fRec185[i] = 0;
		for (int i=0; i<2; i++) fRec186[i] = 0;
		for (int i=0; i<2; i++) fRec187[i] = 0;
		for (int i=0; i<2; i++) fRec188[i] = 0;
		for (int i=0; i<2; i++) fRec189[i] = 0;
		for (int i=0; i<2; i++) fRec190[i] = 0;
		for (int i=0; i<2; i++) fRec191[i] = 0;
		for (int i=0; i<2; i++) fRec192[i] = 0;
		for (int i=0; i<2; i++) fRec193[i] = 0;
		for (int i=0; i<2; i++) fRec194[i] = 0;
		for (int i=0; i<2; i++) fRec195[i] = 0;
		for (int i=0; i<2; i++) fRec196[i] = 0;
		for (int i=0; i<2; i++) fRec197[i] = 0;
		for (int i=0; i<2; i++) fRec198[i] = 0;
		for (int i=0; i<2; i++) fRec199[i] = 0;
		for (int i=0; i<2; i++) fRec200[i] = 0;
		for (int i=0; i<2; i++) fRec201[i] = 0;
		for (int i=0; i<2; i++) fRec202[i] = 0;
		for (int i=0; i<2; i++) fRec203[i] = 0;
		for (int i=0; i<2; i++) fRec204[i] = 0;
		for (int i=0; i<2; i++) fRec205[i] = 0;
		for (int i=0; i<2; i++) fRec206[i] = 0;
		for (int i=0; i<2; i++) fRec207[i] = 0;
		for (int i=0; i<2; i++) fRec208[i] = 0;
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
		ui_interface->addHorizontalSlider("Attack", &fslider14, 0.001f, 0.001f, 4.0f, 0.001f);
		ui_interface->addHorizontalSlider("Decay", &fslider13, 0.0f, 0.0f, 4.0f, 0.001f);
		ui_interface->addHorizontalSlider("Release", &fslider12, 0.0f, 0.0f, 4.0f, 0.01f);
		ui_interface->addHorizontalSlider("Sustain", &fslider15, 1.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->closeBox();
		ui_interface->addHorizontalSlider("fmAmount", &fslider8, 1.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->openVerticalBox("op0");
		ui_interface->addHorizontalSlider("detune", &fslider26, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("feedback", &fslider18, 0.0f, -0.5f, 0.5f, 0.01f);
		ui_interface->addHorizontalSlider("mAtt", &fslider29, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mDecrel", &fslider30, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mSuspos", &fslider28, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("outLev", &fslider27, 1.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("ratio", &fslider25, 1.0f, 0.25f, 4.0f, 0.01f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("op1");
		ui_interface->addHorizontalSlider("detune", &fslider20, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("feedback", &fslider31, 0.0f, -0.5f, 0.5f, 0.01f);
		ui_interface->addHorizontalSlider("mAtt", &fslider22, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mDecrel", &fslider23, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mSuspos", &fslider21, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("outLev", &fslider24, 1.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("ratio", &fslider19, 1.0f, 0.25f, 4.0f, 0.01f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("op2");
		ui_interface->addHorizontalSlider("detune", &fslider11, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("feedback", &fslider1, 0.0f, -0.5f, 0.5f, 0.01f);
		ui_interface->addHorizontalSlider("mAtt", &fslider34, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mDecrel", &fslider35, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mSuspos", &fslider33, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("outLev", &fslider16, 1.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("ratio", &fslider10, 1.0f, 0.25f, 4.0f, 0.01f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("op3");
		ui_interface->addHorizontalSlider("detune", &fslider4, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("feedback", &fslider32, 0.0f, -0.5f, 0.5f, 0.01f);
		ui_interface->addHorizontalSlider("mAtt", &fslider6, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mDecrel", &fslider7, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mSuspos", &fslider5, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("outLev", &fslider9, 1.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("ratio", &fslider2, 1.0f, 0.25f, 4.0f, 0.01f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("v0");
		ui_interface->openVerticalBox("op0");
		ui_interface->addHorizontalBargraph("carrier", &fbargraph46, 0.0f, 1.0f);
		ui_interface->addHorizontalBargraph("modulator", &fbargraph41, 0.0f, 1.0f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("op1");
		ui_interface->addHorizontalBargraph("carrier", &fbargraph42, 0.0f, 1.0f);
		ui_interface->addHorizontalBargraph("modulator", &fbargraph45, 0.0f, 1.0f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("op2");
		ui_interface->addHorizontalBargraph("carrier", &fbargraph40, 0.0f, 1.0f);
		ui_interface->addHorizontalBargraph("modulator", &fbargraph47, 0.0f, 1.0f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("op3");
		ui_interface->addHorizontalBargraph("carrier", &fbargraph43, 0.0f, 1.0f);
		ui_interface->addHorizontalBargraph("modulator", &fbargraph44, 0.0f, 1.0f);
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->openVerticalBox("v1");
		ui_interface->openVerticalBox("op0");
		ui_interface->addHorizontalBargraph("carrier", &fbargraph38, 0.0f, 1.0f);
		ui_interface->addHorizontalBargraph("modulator", &fbargraph33, 0.0f, 1.0f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("op1");
		ui_interface->addHorizontalBargraph("carrier", &fbargraph34, 0.0f, 1.0f);
		ui_interface->addHorizontalBargraph("modulator", &fbargraph37, 0.0f, 1.0f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("op2");
		ui_interface->addHorizontalBargraph("carrier", &fbargraph32, 0.0f, 1.0f);
		ui_interface->addHorizontalBargraph("modulator", &fbargraph39, 0.0f, 1.0f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("op3");
		ui_interface->addHorizontalBargraph("carrier", &fbargraph35, 0.0f, 1.0f);
		ui_interface->addHorizontalBargraph("modulator", &fbargraph36, 0.0f, 1.0f);
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->openVerticalBox("v2");
		ui_interface->openVerticalBox("op0");
		ui_interface->addHorizontalBargraph("carrier", &fbargraph30, 0.0f, 1.0f);
		ui_interface->addHorizontalBargraph("modulator", &fbargraph25, 0.0f, 1.0f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("op1");
		ui_interface->addHorizontalBargraph("carrier", &fbargraph26, 0.0f, 1.0f);
		ui_interface->addHorizontalBargraph("modulator", &fbargraph29, 0.0f, 1.0f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("op2");
		ui_interface->addHorizontalBargraph("carrier", &fbargraph24, 0.0f, 1.0f);
		ui_interface->addHorizontalBargraph("modulator", &fbargraph31, 0.0f, 1.0f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("op3");
		ui_interface->addHorizontalBargraph("carrier", &fbargraph27, 0.0f, 1.0f);
		ui_interface->addHorizontalBargraph("modulator", &fbargraph28, 0.0f, 1.0f);
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->openVerticalBox("v3");
		ui_interface->openVerticalBox("op0");
		ui_interface->addHorizontalBargraph("carrier", &fbargraph22, 0.0f, 1.0f);
		ui_interface->addHorizontalBargraph("modulator", &fbargraph17, 0.0f, 1.0f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("op1");
		ui_interface->addHorizontalBargraph("carrier", &fbargraph18, 0.0f, 1.0f);
		ui_interface->addHorizontalBargraph("modulator", &fbargraph21, 0.0f, 1.0f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("op2");
		ui_interface->addHorizontalBargraph("carrier", &fbargraph16, 0.0f, 1.0f);
		ui_interface->addHorizontalBargraph("modulator", &fbargraph23, 0.0f, 1.0f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("op3");
		ui_interface->addHorizontalBargraph("carrier", &fbargraph19, 0.0f, 1.0f);
		ui_interface->addHorizontalBargraph("modulator", &fbargraph20, 0.0f, 1.0f);
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->openVerticalBox("v4");
		ui_interface->openVerticalBox("op0");
		ui_interface->addHorizontalBargraph("carrier", &fbargraph14, 0.0f, 1.0f);
		ui_interface->addHorizontalBargraph("modulator", &fbargraph9, 0.0f, 1.0f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("op1");
		ui_interface->addHorizontalBargraph("carrier", &fbargraph10, 0.0f, 1.0f);
		ui_interface->addHorizontalBargraph("modulator", &fbargraph13, 0.0f, 1.0f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("op2");
		ui_interface->addHorizontalBargraph("carrier", &fbargraph8, 0.0f, 1.0f);
		ui_interface->addHorizontalBargraph("modulator", &fbargraph15, 0.0f, 1.0f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("op3");
		ui_interface->addHorizontalBargraph("carrier", &fbargraph11, 0.0f, 1.0f);
		ui_interface->addHorizontalBargraph("modulator", &fbargraph12, 0.0f, 1.0f);
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->openVerticalBox("v5");
		ui_interface->openVerticalBox("op0");
		ui_interface->addHorizontalBargraph("carrier", &fbargraph3, 0.0f, 1.0f);
		ui_interface->addHorizontalBargraph("modulator", &fbargraph4, 0.0f, 1.0f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("op1");
		ui_interface->addHorizontalBargraph("carrier", &fbargraph5, 0.0f, 1.0f);
		ui_interface->addHorizontalBargraph("modulator", &fbargraph2, 0.0f, 1.0f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("op2");
		ui_interface->addHorizontalBargraph("carrier", &fbargraph1, 0.0f, 1.0f);
		ui_interface->addHorizontalBargraph("modulator", &fbargraph7, 0.0f, 1.0f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("op3");
		ui_interface->addHorizontalBargraph("carrier", &fbargraph6, 0.0f, 1.0f);
		ui_interface->addHorizontalBargraph("modulator", &fbargraph0, 0.0f, 1.0f);
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->openVerticalBox("voices");
		ui_interface->openVerticalBox("0");
		ui_interface->openVerticalBox("midi");
		ui_interface->addHorizontalSlider("freq", &fslider44, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addButton("trigger", &fbutton5);
		ui_interface->addHorizontalSlider("velocity", &fslider45, 1.0f, 0.0f, 1.0f, 0.007874015748031496f);
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->openVerticalBox("1");
		ui_interface->openVerticalBox("midi");
		ui_interface->addHorizontalSlider("freq", &fslider42, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addButton("trigger", &fbutton4);
		ui_interface->addHorizontalSlider("velocity", &fslider43, 1.0f, 0.0f, 1.0f, 0.007874015748031496f);
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->openVerticalBox("2");
		ui_interface->openVerticalBox("midi");
		ui_interface->addHorizontalSlider("freq", &fslider40, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addButton("trigger", &fbutton3);
		ui_interface->addHorizontalSlider("velocity", &fslider41, 1.0f, 0.0f, 1.0f, 0.007874015748031496f);
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->openVerticalBox("3");
		ui_interface->openVerticalBox("midi");
		ui_interface->addHorizontalSlider("freq", &fslider38, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addButton("trigger", &fbutton2);
		ui_interface->addHorizontalSlider("velocity", &fslider39, 1.0f, 0.0f, 1.0f, 0.007874015748031496f);
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->openVerticalBox("4");
		ui_interface->openVerticalBox("midi");
		ui_interface->addHorizontalSlider("freq", &fslider36, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addButton("trigger", &fbutton1);
		ui_interface->addHorizontalSlider("velocity", &fslider37, 1.0f, 0.0f, 1.0f, 0.007874015748031496f);
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->openVerticalBox("5");
		ui_interface->openVerticalBox("midi");
		ui_interface->addHorizontalSlider("freq", &fslider3, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addButton("trigger", &fbutton0);
		ui_interface->addHorizontalSlider("velocity", &fslider17, 1.0f, 0.0f, 1.0f, 0.007874015748031496f);
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->closeBox();
	}
	virtual void compute (int count, FAUSTFLOAT** input, FAUSTFLOAT** output) {
		//zone1
		//zone2
		int 	iSlow0 = int(float(fslider0));
		int 	iSlow1 = (float((iSlow0 == 7)) != 0.0f);
		int 	iSlow2 = (float((iSlow0 == 8)) != 0.0f);
		int 	iSlow3 = (float((iSlow0 == 9)) != 0.0f);
		int 	iSlow4 = (float((iSlow0 == 10)) != 0.0f);
		float 	fSlow5 = (0.0010000000000000009f * float(fslider1));
		int 	iSlow6 = (float((iSlow0 == 6)) != 0.0f);
		int 	iSlow7 = (float((iSlow0 == 4)) != 0.0f);
		int 	iSlow8 = (float((iSlow0 == 3)) != 0.0f);
		int 	iSlow9 = (float((iSlow0 == 2)) != 0.0f);
		int 	iSlow10 = (float((iSlow0 == 1)) != 0.0f);
		int 	iSlow11 = (float((iSlow0 == 0)) != 0.0f);
		int 	iSlow12 = (float((iSlow0 == 5)) != 0.0f);
		float 	fSlow13 = float(fslider2);
		float 	fSlow14 = float(fslider3);
		float 	fSlow15 = (25.0f * float(fslider4));
		float 	fSlow16 = (fConst1 * (fSlow15 + (fSlow14 * fSlow13)));
		float 	fSlow17 = float(fslider5);
		float 	fSlow18 = float(fbutton0);
		float 	fSlow19 = (fSlow18 * fSlow17);
		float 	fSlow20 = float(fslider6);
		float 	fSlow21 = (fConst2 * fSlow20);
		float 	fSlow22 = float(fslider7);
		float 	fSlow23 = (((1.0f - fSlow17) * fSlow22) + fSlow20);
		float 	fSlow24 = (fConst2 * fSlow23);
		int 	iSlow25 = int(((fSlow18 == 0.0f) > 0));
		float 	fSlow26 = (fSlow23 - fSlow20);
		float 	fSlow27 = (fConst3 * ((fSlow19 + -1.0f) / fSlow26));
		float 	fSlow28 = (fConst3 / fSlow20);
		int 	iSlow29 = (fSlow18 > 0.0f);
		float 	fSlow30 = float(iSlow29);
		int 	iSlow31 = int(iSlow29);
		float 	fSlow32 = max(0.001f, (fConst2 * (fSlow17 * fSlow22)));
		int 	iSlow33 = int((iSlow29 > 0));
		float 	fSlow34 = (1.0f / fSlow32);
		float 	fSlow35 = float(fslider8);
		float 	fSlow36 = float(fslider9);
		float 	fSlow37 = (fSlow36 * fSlow35);
		float 	fSlow38 = float(fslider10);
		float 	fSlow39 = (25.0f * float(fslider11));
		float 	fSlow40 = (fConst1 * (fSlow39 + (fSlow14 * fSlow38)));
		float 	fSlow41 = float(fslider12);
		float 	fSlow42 = float(fslider13);
		float 	fSlow43 = float(fslider14);
		float 	fSlow44 = (6.9100000000000001f * fSlow43);
		int 	iSlow45 = int((fConst0 * fSlow43));
		float 	fSlow46 = float(fslider15);
		float 	fSlow47 = (fSlow30 * fSlow46);
		float 	fSlow48 = float(fslider16);
		float 	fSlow49 = float(fslider17);
		float 	fSlow50 = (fSlow49 * fSlow48);
		float 	fSlow51 = (0.0010000000000000009f * float(fslider18));
		float 	fSlow52 = float(fslider19);
		float 	fSlow53 = (25.0f * float(fslider20));
		float 	fSlow54 = (fConst1 * (fSlow53 + (fSlow14 * fSlow52)));
		float 	fSlow55 = float(fslider21);
		float 	fSlow56 = (fSlow18 * fSlow55);
		float 	fSlow57 = float(fslider22);
		float 	fSlow58 = (fConst2 * fSlow57);
		float 	fSlow59 = float(fslider23);
		float 	fSlow60 = (((1.0f - fSlow55) * fSlow59) + fSlow57);
		float 	fSlow61 = (fConst2 * fSlow60);
		float 	fSlow62 = (fSlow60 - fSlow57);
		float 	fSlow63 = (fConst3 * ((fSlow56 + -1.0f) / fSlow62));
		float 	fSlow64 = (fConst3 / fSlow57);
		float 	fSlow65 = max(0.001f, (fConst2 * (fSlow55 * fSlow59)));
		float 	fSlow66 = (1.0f / fSlow65);
		float 	fSlow67 = float(fslider24);
		float 	fSlow68 = (fSlow67 * fSlow35);
		float 	fSlow69 = float(fslider25);
		float 	fSlow70 = (25.0f * float(fslider26));
		float 	fSlow71 = (fConst1 * (fSlow70 + (fSlow14 * fSlow69)));
		float 	fSlow72 = float(fslider27);
		float 	fSlow73 = (fSlow49 * fSlow72);
		float 	fSlow74 = float(fslider28);
		float 	fSlow75 = (fSlow18 * fSlow74);
		float 	fSlow76 = float(fslider29);
		float 	fSlow77 = (fConst2 * fSlow76);
		float 	fSlow78 = float(fslider30);
		float 	fSlow79 = (((1.0f - fSlow74) * fSlow78) + fSlow76);
		float 	fSlow80 = (fConst2 * fSlow79);
		float 	fSlow81 = (fSlow79 - fSlow76);
		float 	fSlow82 = (fConst3 * ((fSlow75 + -1.0f) / fSlow81));
		float 	fSlow83 = (fConst3 / fSlow76);
		float 	fSlow84 = max(0.001f, (fConst2 * (fSlow74 * fSlow78)));
		float 	fSlow85 = (1.0f / fSlow84);
		float 	fSlow86 = (fSlow72 * fSlow35);
		float 	fSlow87 = (0.0010000000000000009f * float(fslider31));
		float 	fSlow88 = (fSlow49 * fSlow67);
		float 	fSlow89 = (0.0010000000000000009f * float(fslider32));
		float 	fSlow90 = (fSlow49 * fSlow36);
		float 	fSlow91 = float(fslider33);
		float 	fSlow92 = (fSlow18 * fSlow91);
		float 	fSlow93 = float(fslider34);
		float 	fSlow94 = (fConst2 * fSlow93);
		float 	fSlow95 = float(fslider35);
		float 	fSlow96 = (((1.0f - fSlow91) * fSlow95) + fSlow93);
		float 	fSlow97 = (fConst2 * fSlow96);
		float 	fSlow98 = (fSlow96 - fSlow93);
		float 	fSlow99 = (fConst3 * ((fSlow92 + -1.0f) / fSlow98));
		float 	fSlow100 = (fConst3 / fSlow93);
		float 	fSlow101 = max(0.001f, (fConst2 * (fSlow91 * fSlow95)));
		float 	fSlow102 = (1.0f / fSlow101);
		float 	fSlow103 = (fSlow48 * fSlow35);
		float 	fSlow104 = float(fslider36);
		float 	fSlow105 = (fConst1 * (fSlow39 + (fSlow104 * fSlow38)));
		float 	fSlow106 = float(fbutton1);
		int 	iSlow107 = (fSlow106 > 0.0f);
		int 	iSlow108 = int(iSlow107);
		float 	fSlow109 = float(iSlow107);
		float 	fSlow110 = (fSlow109 * fSlow46);
		float 	fSlow111 = float(fslider37);
		float 	fSlow112 = (fSlow48 * fSlow111);
		float 	fSlow113 = (fConst1 * (fSlow70 + (fSlow104 * fSlow69)));
		float 	fSlow114 = (fSlow106 * fSlow74);
		int 	iSlow115 = int(((fSlow106 == 0.0f) > 0));
		float 	fSlow116 = (fConst3 * ((fSlow114 + -1.0f) / fSlow81));
		int 	iSlow117 = int((iSlow107 > 0));
		float 	fSlow118 = (fConst1 * (fSlow53 + (fSlow104 * fSlow52)));
		float 	fSlow119 = (fSlow67 * fSlow111);
		float 	fSlow120 = (fConst1 * (fSlow15 + (fSlow104 * fSlow13)));
		float 	fSlow121 = (fSlow36 * fSlow111);
		float 	fSlow122 = (fSlow106 * fSlow17);
		float 	fSlow123 = (fConst3 * ((fSlow122 + -1.0f) / fSlow26));
		float 	fSlow124 = (fSlow106 * fSlow55);
		float 	fSlow125 = (fConst3 * ((fSlow124 + -1.0f) / fSlow62));
		float 	fSlow126 = (fSlow72 * fSlow111);
		float 	fSlow127 = (fSlow106 * fSlow91);
		float 	fSlow128 = (fConst3 * ((fSlow127 + -1.0f) / fSlow98));
		float 	fSlow129 = float(fslider38);
		float 	fSlow130 = (fConst1 * (fSlow39 + (fSlow129 * fSlow38)));
		float 	fSlow131 = float(fbutton2);
		int 	iSlow132 = (fSlow131 > 0.0f);
		int 	iSlow133 = int(iSlow132);
		float 	fSlow134 = float(iSlow132);
		float 	fSlow135 = (fSlow134 * fSlow46);
		float 	fSlow136 = float(fslider39);
		float 	fSlow137 = (fSlow48 * fSlow136);
		float 	fSlow138 = (fConst1 * (fSlow70 + (fSlow129 * fSlow69)));
		float 	fSlow139 = (fSlow131 * fSlow74);
		int 	iSlow140 = int(((fSlow131 == 0.0f) > 0));
		float 	fSlow141 = (fConst3 * ((fSlow139 + -1.0f) / fSlow81));
		int 	iSlow142 = int((iSlow132 > 0));
		float 	fSlow143 = (fConst1 * (fSlow53 + (fSlow129 * fSlow52)));
		float 	fSlow144 = (fSlow67 * fSlow136);
		float 	fSlow145 = (fConst1 * (fSlow15 + (fSlow129 * fSlow13)));
		float 	fSlow146 = (fSlow36 * fSlow136);
		float 	fSlow147 = (fSlow131 * fSlow17);
		float 	fSlow148 = (fConst3 * ((fSlow147 + -1.0f) / fSlow26));
		float 	fSlow149 = (fSlow131 * fSlow55);
		float 	fSlow150 = (fConst3 * ((fSlow149 + -1.0f) / fSlow62));
		float 	fSlow151 = (fSlow72 * fSlow136);
		float 	fSlow152 = (fSlow131 * fSlow91);
		float 	fSlow153 = (fConst3 * ((fSlow152 + -1.0f) / fSlow98));
		float 	fSlow154 = float(fslider40);
		float 	fSlow155 = (fConst1 * (fSlow39 + (fSlow154 * fSlow38)));
		float 	fSlow156 = float(fbutton3);
		int 	iSlow157 = (fSlow156 > 0.0f);
		int 	iSlow158 = int(iSlow157);
		float 	fSlow159 = float(iSlow157);
		float 	fSlow160 = (fSlow159 * fSlow46);
		float 	fSlow161 = float(fslider41);
		float 	fSlow162 = (fSlow48 * fSlow161);
		float 	fSlow163 = (fConst1 * (fSlow70 + (fSlow154 * fSlow69)));
		float 	fSlow164 = (fSlow156 * fSlow74);
		int 	iSlow165 = int(((fSlow156 == 0.0f) > 0));
		float 	fSlow166 = (fConst3 * ((fSlow164 + -1.0f) / fSlow81));
		int 	iSlow167 = int((iSlow157 > 0));
		float 	fSlow168 = (fConst1 * (fSlow53 + (fSlow154 * fSlow52)));
		float 	fSlow169 = (fSlow67 * fSlow161);
		float 	fSlow170 = (fConst1 * (fSlow15 + (fSlow154 * fSlow13)));
		float 	fSlow171 = (fSlow36 * fSlow161);
		float 	fSlow172 = (fSlow156 * fSlow17);
		float 	fSlow173 = (fConst3 * ((fSlow172 + -1.0f) / fSlow26));
		float 	fSlow174 = (fSlow156 * fSlow55);
		float 	fSlow175 = (fConst3 * ((fSlow174 + -1.0f) / fSlow62));
		float 	fSlow176 = (fSlow72 * fSlow161);
		float 	fSlow177 = (fSlow156 * fSlow91);
		float 	fSlow178 = (fConst3 * ((fSlow177 + -1.0f) / fSlow98));
		float 	fSlow179 = float(fslider42);
		float 	fSlow180 = (fConst1 * (fSlow39 + (fSlow179 * fSlow38)));
		float 	fSlow181 = float(fbutton4);
		int 	iSlow182 = (fSlow181 > 0.0f);
		int 	iSlow183 = int(iSlow182);
		float 	fSlow184 = float(iSlow182);
		float 	fSlow185 = (fSlow184 * fSlow46);
		float 	fSlow186 = float(fslider43);
		float 	fSlow187 = (fSlow48 * fSlow186);
		float 	fSlow188 = (fConst1 * (fSlow70 + (fSlow179 * fSlow69)));
		float 	fSlow189 = (fSlow181 * fSlow74);
		int 	iSlow190 = int(((fSlow181 == 0.0f) > 0));
		float 	fSlow191 = (fConst3 * ((fSlow189 + -1.0f) / fSlow81));
		int 	iSlow192 = int((iSlow182 > 0));
		float 	fSlow193 = (fConst1 * (fSlow53 + (fSlow179 * fSlow52)));
		float 	fSlow194 = (fSlow67 * fSlow186);
		float 	fSlow195 = (fConst1 * (fSlow15 + (fSlow179 * fSlow13)));
		float 	fSlow196 = (fSlow36 * fSlow186);
		float 	fSlow197 = (fSlow181 * fSlow17);
		float 	fSlow198 = (fConst3 * ((fSlow197 + -1.0f) / fSlow26));
		float 	fSlow199 = (fSlow181 * fSlow55);
		float 	fSlow200 = (fConst3 * ((fSlow199 + -1.0f) / fSlow62));
		float 	fSlow201 = (fSlow72 * fSlow186);
		float 	fSlow202 = (fSlow181 * fSlow91);
		float 	fSlow203 = (fConst3 * ((fSlow202 + -1.0f) / fSlow98));
		float 	fSlow204 = float(fslider44);
		float 	fSlow205 = (fConst1 * ((fSlow204 * fSlow38) + fSlow39));
		float 	fSlow206 = float(fbutton5);
		int 	iSlow207 = (fSlow206 > 0.0f);
		int 	iSlow208 = int(iSlow207);
		float 	fSlow209 = float(iSlow207);
		float 	fSlow210 = (fSlow209 * fSlow46);
		float 	fSlow211 = float(fslider45);
		float 	fSlow212 = (fSlow48 * fSlow211);
		float 	fSlow213 = (fConst1 * ((fSlow204 * fSlow69) + fSlow70));
		float 	fSlow214 = (fSlow206 * fSlow74);
		int 	iSlow215 = int(((fSlow206 == 0.0f) > 0));
		float 	fSlow216 = (fConst3 * ((fSlow214 + -1.0f) / fSlow81));
		int 	iSlow217 = int((iSlow207 > 0));
		float 	fSlow218 = (fConst1 * ((fSlow204 * fSlow52) + fSlow53));
		float 	fSlow219 = (fSlow67 * fSlow211);
		float 	fSlow220 = (fConst1 * ((fSlow204 * fSlow13) + fSlow15));
		float 	fSlow221 = (fSlow36 * fSlow211);
		float 	fSlow222 = (fSlow206 * fSlow17);
		float 	fSlow223 = (fConst3 * ((fSlow222 + -1.0f) / fSlow26));
		float 	fSlow224 = (fSlow206 * fSlow55);
		float 	fSlow225 = (fConst3 * ((fSlow224 + -1.0f) / fSlow62));
		float 	fSlow226 = (fSlow72 * fSlow211);
		float 	fSlow227 = (fSlow206 * fSlow91);
		float 	fSlow228 = (fConst3 * ((fSlow227 + -1.0f) / fSlow98));
		//zone2b
		//zone3
		FAUSTFLOAT* output0 = output[0];
		//LoopGraphScalar
		for (int i=0; i<count; i++) {
			if (iSlow4 || iSlow2 || iSlow1 || iSlow3) {
				fRec2[0] = (fSlow5 + (0.999f * fRec2[1]));
			}
			if (iSlow4 || iSlow2 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow1 || iSlow3) {
				fRec3[0] = (fSlow16 + (fRec3[1] - floorf((fSlow16 + fRec3[1]))));
			}
			if (iSlow2 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow1) {
				fRec5[0] = ((iSlow25)?0.0f:min(fSlow24, (fRec5[1] + 1.0f)));
				iTempPerm1 = int((fRec5[0] < fSlow21));
				fRec4[0] = ((iSlow31)?(fSlow30 * ((iTempPerm1)?((int((fRec5[0] < 0.0f)))?0.0f:((iTempPerm1)?(fSlow28 * fRec5[0]):1.0f)):((int((fRec5[0] < fSlow24)))?((fSlow27 * (fRec5[0] - fSlow21)) + 1.0f):fSlow19))):fRec4[1]);
				fRec6[0] = ((iSlow33)?0.0f:min(fSlow32, (fRec6[1] + 1.0f)));
				fTempPerm2 = ((int((fRec6[0] < 0.0f)))?fRec4[0]:((int((fRec6[0] < fSlow32)))?(fRec4[0] + (fSlow34 * (0 - (fRec6[0] * fRec4[0])))):0.0f));
				fbargraph0 = fTempPerm2;
				fTempPerm3 = (fTempPerm2 * ftbl0[(((int((65536.0f * fRec3[0])) % 65536) + 65536) % 65536)]);
			}
			if (iSlow2 || iSlow12 || iSlow11 || iSlow8 || iSlow7 || iSlow1) {
				fTempPerm4 = (fSlow37 * fTempPerm3);
			}
			if (iSlow4 || iSlow2 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow1 || iSlow3) {
				fRec7[0] = (fSlow40 + (fRec7[1] - floorf((fSlow40 + fRec7[1]))));
				iRec9[0] = (iSlow29 * (iRec9[1] + 1));
				iTempPerm5 = int((iRec9[0] < iSlow45));
				fTempPerm6 = expf((0 - (fConst4 / ((iSlow31)?((iTempPerm5)?fSlow44:fSlow42):fSlow41))));
				fRec8[0] = ((fRec8[1] * fTempPerm6) + (((iSlow31)?((iTempPerm5)?1.5873015873015872f:fSlow47):0.0f) * (1.0f - fTempPerm6)));
				fTempPerm7 = min(1.0f, fRec8[0]);
			}
			if (iSlow4 || iSlow2 || iSlow1 || iSlow3) {
				fbargraph1 = fTempPerm7;
				fTempPerm8 = fTempPerm7;
			}
			if (iSlow2 || iSlow1) {
				fRec0[0] = (fSlow50 * (fTempPerm8 * ftbl0[(((int((65536.0f * (fRec7[0] + (fTempPerm4 + (fRec2[0] * fRec0[1]))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow4 || iSlow2 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow1) {
				fRec11[0] = (fSlow51 + (0.999f * fRec11[1]));
			}
			if (iSlow4 || iSlow2 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow1 || iSlow3) {
				fRec12[0] = (fSlow54 + (fRec12[1] - floorf((fSlow54 + fRec12[1]))));
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow6 || iSlow1) {
				fRec14[0] = ((iSlow25)?0.0f:min(fSlow61, (fRec14[1] + 1.0f)));
				iTempPerm9 = int((fRec14[0] < fSlow58));
				fRec13[0] = ((iSlow31)?(fSlow30 * ((iTempPerm9)?((int((fRec14[0] < 0.0f)))?0.0f:((iTempPerm9)?(fSlow64 * fRec14[0]):1.0f)):((int((fRec14[0] < fSlow61)))?((fSlow63 * (fRec14[0] - fSlow58)) + 1.0f):fSlow56))):fRec13[1]);
				fRec15[0] = ((iSlow33)?0.0f:min(fSlow65, (fRec15[1] + 1.0f)));
				fTempPerm10 = ((int((fRec15[0] < 0.0f)))?fRec13[0]:((int((fRec15[0] < fSlow65)))?(fRec13[0] + (fSlow66 * (0 - (fRec15[0] * fRec13[0])))):0.0f));
				fbargraph2 = fTempPerm10;
				fTempPerm11 = fTempPerm10;
			}
			if (iSlow6 || iSlow1) {
				fTempPerm12 = (fTempPerm11 * ftbl0[(((int((65536.0f * fRec12[0])) % 65536) + 65536) % 65536)]);
			}
			if (iSlow4 || iSlow2 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow1 || iSlow3) {
				fRec16[0] = (fSlow71 + (fRec16[1] - floorf((fSlow71 + fRec16[1]))));
			}
			if (iSlow4 || iSlow2 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow1) {
				fbargraph3 = fTempPerm7;
				fTempPerm13 = fTempPerm7;
			}
			if (iSlow1) {
				fRec10[0] = (fSlow73 * (fTempPerm13 * ftbl0[(((int((65536.0f * (fRec16[0] + ((fSlow68 * fTempPerm12) + (fRec11[0] * fRec10[1]))))) % 65536) + 65536) % 65536)]));
				fTempPerm14 = (fRec10[0] + fRec0[0]);
			}
			if (iSlow4 || iSlow3) {
				fRec17[0] = (fSlow50 * (fTempPerm8 * ftbl0[(((int((65536.0f * (fRec7[0] + (fRec2[0] * fRec17[1])))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow3) {
				fRec20[0] = ((iSlow25)?0.0f:min(fSlow80, (fRec20[1] + 1.0f)));
				iTempPerm15 = int((fRec20[0] < fSlow77));
				fRec19[0] = ((iSlow31)?(fSlow30 * ((iTempPerm15)?((int((fRec20[0] < 0.0f)))?0.0f:((iTempPerm15)?(fSlow83 * fRec20[0]):1.0f)):((int((fRec20[0] < fSlow80)))?((fSlow82 * (fRec20[0] - fSlow77)) + 1.0f):fSlow75))):fRec19[1]);
				fRec21[0] = ((iSlow33)?0.0f:min(fSlow84, (fRec21[1] + 1.0f)));
				fTempPerm16 = ((int((fRec21[0] < 0.0f)))?fRec19[0]:((int((fRec21[0] < fSlow84)))?(fRec19[0] + (fSlow85 * (0 - (fRec21[0] * fRec19[0])))):0.0f));
				fbargraph4 = fTempPerm16;
			}
			if (iSlow4 || iSlow2 || iSlow12 || iSlow7 || iSlow3) {
				fRec22[0] = (fSlow87 + (0.999f * fRec22[1]));
				fbargraph5 = fTempPerm7;
				fTempPerm17 = fTempPerm7;
			}
			if (iSlow3) {
				fRec18[0] = (fSlow88 * (fTempPerm17 * ftbl0[(((int((65536.0f * (fRec12[0] + ((fRec22[0] * fRec18[1]) + (fSlow86 * (fTempPerm16 * ftbl0[(((int((65536.0f * fRec16[0])) % 65536) + 65536) % 65536)])))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow4 || iSlow3) {
				fRec24[0] = (fSlow89 + (0.999f * fRec24[1]));
				fbargraph6 = fTempPerm7;
				fRec23[0] = (fSlow90 * (fTempPerm7 * ftbl0[(((int((65536.0f * (fRec3[0] + (fRec24[0] * fRec23[1])))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow3) {
				fTempPerm18 = ((fRec23[0] + fRec18[0]) + fRec17[0]);
			}
			if (iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6) {
				fRec27[0] = ((iSlow25)?0.0f:min(fSlow97, (fRec27[1] + 1.0f)));
				iTempPerm19 = int((fRec27[0] < fSlow94));
				fRec26[0] = ((iSlow31)?(fSlow30 * ((iTempPerm19)?((int((fRec27[0] < 0.0f)))?0.0f:((iTempPerm19)?(fSlow100 * fRec27[0]):1.0f)):((int((fRec27[0] < fSlow97)))?((fSlow99 * (fRec27[0] - fSlow94)) + 1.0f):fSlow92))):fRec26[1]);
				fRec28[0] = ((iSlow33)?0.0f:min(fSlow101, (fRec28[1] + 1.0f)));
				fTempPerm20 = ((int((fRec28[0] < 0.0f)))?fRec26[0]:((int((fRec28[0] < fSlow101)))?(fRec26[0] + (fSlow102 * (0 - (fRec28[0] * fRec26[0])))):0.0f));
				fbargraph7 = fTempPerm20;
				fTempPerm21 = fTempPerm20;
			}
			if (iSlow10 || iSlow9 || iSlow6) {
				fTempPerm22 = (fTempPerm21 * ftbl0[(((int((65536.0f * fRec7[0])) % 65536) + 65536) % 65536)]);
				fTempPerm23 = (fSlow36 * fTempPerm3);
			}
			if (iSlow10 || iSlow6) {
				fTempPerm24 = (fTempPerm23 + (fSlow48 * fTempPerm22));
			}
			if (iSlow6) {
				fRec25[0] = (fSlow73 * (fTempPerm13 * ftbl0[(((int((65536.0f * (fRec16[0] + ((fRec11[0] * fRec25[1]) + (fSlow35 * (fTempPerm24 + (fSlow67 * fTempPerm12))))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow12 || iSlow11 || iSlow8 || iSlow7) {
				fTempPerm25 = (fTempPerm21 * ftbl0[(((int((65536.0f * (fRec7[0] + fTempPerm4))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow12 || iSlow11 || iSlow7) {
				fTempPerm26 = (fSlow103 * fTempPerm25);
			}
			if (iSlow12 || iSlow7) {
				fRec29[0] = (fSlow88 * (fTempPerm17 * ftbl0[(((int((65536.0f * (fRec12[0] + (fTempPerm26 + (fRec22[0] * fRec29[1]))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow7) {
				fRec30[0] = (fSlow73 * (fTempPerm13 * ftbl0[(((int((65536.0f * (fRec16[0] + (fTempPerm26 + (fRec11[0] * fRec30[1]))))) % 65536) + 65536) % 65536)]));
				fTempPerm27 = (fRec30[0] + fRec29[0]);
			}
			if (iSlow8) {
				fRec31[0] = (fSlow73 * (fTempPerm13 * ftbl0[(((int((65536.0f * (fRec16[0] + ((fRec11[0] * fRec31[1]) + (fSlow35 * ((fSlow48 * fTempPerm25) + (fSlow67 * (fTempPerm11 * ftbl0[(((int((65536.0f * (fRec12[0] + fTempPerm4))) % 65536) + 65536) % 65536)])))))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow9) {
				fRec32[0] = (fSlow73 * (fTempPerm13 * ftbl0[(((int((65536.0f * (fRec16[0] + ((fRec11[0] * fRec32[1]) + (fSlow35 * (fTempPerm23 + (fSlow67 * (fTempPerm11 * ftbl0[(((int((65536.0f * (fRec12[0] + (fSlow103 * fTempPerm22)))) % 65536) + 65536) % 65536)])))))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow10) {
				fRec33[0] = (fSlow73 * (fTempPerm13 * ftbl0[(((int((65536.0f * (fRec16[0] + ((fRec11[0] * fRec33[1]) + (fSlow68 * (fTempPerm11 * ftbl0[(((int((65536.0f * (fRec12[0] + (fSlow35 * fTempPerm24)))) % 65536) + 65536) % 65536)])))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow11) {
				fRec34[0] = (fSlow73 * (fTempPerm13 * ftbl0[(((int((65536.0f * (fRec16[0] + ((fRec11[0] * fRec34[1]) + (fSlow68 * (fTempPerm11 * ftbl0[(((int((65536.0f * (fRec12[0] + fTempPerm26))) % 65536) + 65536) % 65536)])))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow4 || iSlow2 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow1 || iSlow3) {
				fRec36[0] = (fSlow105 + (fRec36[1] - floorf((fSlow105 + fRec36[1]))));
				iRec38[0] = (iSlow107 * (iRec38[1] + 1));
				iTempPerm28 = int((iRec38[0] < iSlow45));
				fTempPerm29 = expf((0 - (fConst4 / ((iSlow108)?((iTempPerm28)?fSlow44:fSlow42):fSlow41))));
				fRec37[0] = ((fRec37[1] * fTempPerm29) + (((iSlow108)?((iTempPerm28)?1.5873015873015872f:fSlow110):0.0f) * (1.0f - fTempPerm29)));
				fTempPerm30 = min(1.0f, fRec37[0]);
			}
			if (iSlow4 || iSlow2 || iSlow1 || iSlow3) {
				fbargraph8 = fTempPerm30;
				fTempPerm31 = fTempPerm30;
			}
			if (iSlow4 || iSlow3) {
				fRec35[0] = (fSlow112 * (fTempPerm31 * ftbl0[(((int((65536.0f * (fRec36[0] + (fRec2[0] * fRec35[1])))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow4 || iSlow2 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow1 || iSlow3) {
				fRec40[0] = (fSlow113 + (fRec40[1] - floorf((fSlow113 + fRec40[1]))));
			}
			if (iSlow3) {
				fRec42[0] = ((iSlow115)?0.0f:min(fSlow80, (fRec42[1] + 1.0f)));
				iTempPerm32 = int((fRec42[0] < fSlow77));
				fRec41[0] = ((iSlow108)?(fSlow109 * ((iTempPerm32)?((int((fRec42[0] < 0.0f)))?0.0f:((iTempPerm32)?(fSlow83 * fRec42[0]):1.0f)):((int((fRec42[0] < fSlow80)))?((fSlow116 * (fRec42[0] - fSlow77)) + 1.0f):fSlow114))):fRec41[1]);
				fRec43[0] = ((iSlow117)?0.0f:min(fSlow84, (fRec43[1] + 1.0f)));
				fTempPerm33 = ((int((fRec43[0] < 0.0f)))?fRec41[0]:((int((fRec43[0] < fSlow84)))?(fRec41[0] + (fSlow85 * (0 - (fRec43[0] * fRec41[0])))):0.0f));
				fbargraph9 = fTempPerm33;
			}
			if (iSlow4 || iSlow2 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow1 || iSlow3) {
				fRec44[0] = (fSlow118 + (fRec44[1] - floorf((fSlow118 + fRec44[1]))));
			}
			if (iSlow4 || iSlow2 || iSlow12 || iSlow7 || iSlow3) {
				fbargraph10 = fTempPerm30;
				fTempPerm34 = fTempPerm30;
			}
			if (iSlow3) {
				fRec39[0] = (fSlow119 * (fTempPerm34 * ftbl0[(((int((65536.0f * (fRec44[0] + ((fRec22[0] * fRec39[1]) + (fSlow86 * (fTempPerm33 * ftbl0[(((int((65536.0f * fRec40[0])) % 65536) + 65536) % 65536)])))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow4 || iSlow2 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow1 || iSlow3) {
				fRec46[0] = (fSlow120 + (fRec46[1] - floorf((fSlow120 + fRec46[1]))));
			}
			if (iSlow4 || iSlow3) {
				fbargraph11 = fTempPerm30;
				fRec45[0] = (fSlow121 * (fTempPerm30 * ftbl0[(((int((65536.0f * (fRec46[0] + (fRec24[0] * fRec45[1])))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow3) {
				fTempPerm35 = ((fRec45[0] + fRec39[0]) + fRec35[0]);
			}
			if (iSlow2 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow1) {
				fRec49[0] = ((iSlow115)?0.0f:min(fSlow24, (fRec49[1] + 1.0f)));
				iTempPerm36 = int((fRec49[0] < fSlow21));
				fRec48[0] = ((iSlow108)?(fSlow109 * ((iTempPerm36)?((int((fRec49[0] < 0.0f)))?0.0f:((iTempPerm36)?(fSlow28 * fRec49[0]):1.0f)):((int((fRec49[0] < fSlow24)))?((fSlow123 * (fRec49[0] - fSlow21)) + 1.0f):fSlow122))):fRec48[1]);
				fRec50[0] = ((iSlow117)?0.0f:min(fSlow32, (fRec50[1] + 1.0f)));
				fTempPerm37 = ((int((fRec50[0] < 0.0f)))?fRec48[0]:((int((fRec50[0] < fSlow32)))?(fRec48[0] + (fSlow34 * (0 - (fRec50[0] * fRec48[0])))):0.0f));
				fbargraph12 = fTempPerm37;
				fTempPerm38 = (fTempPerm37 * ftbl0[(((int((65536.0f * fRec46[0])) % 65536) + 65536) % 65536)]);
			}
			if (iSlow2 || iSlow12 || iSlow11 || iSlow8 || iSlow7 || iSlow1) {
				fTempPerm39 = (fSlow37 * fTempPerm38);
			}
			if (iSlow2 || iSlow1) {
				fRec47[0] = (fSlow112 * (fTempPerm31 * ftbl0[(((int((65536.0f * (fRec36[0] + (fTempPerm39 + (fRec2[0] * fRec47[1]))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow6 || iSlow1) {
				fRec53[0] = ((iSlow115)?0.0f:min(fSlow61, (fRec53[1] + 1.0f)));
				iTempPerm40 = int((fRec53[0] < fSlow58));
				fRec52[0] = ((iSlow108)?(fSlow109 * ((iTempPerm40)?((int((fRec53[0] < 0.0f)))?0.0f:((iTempPerm40)?(fSlow64 * fRec53[0]):1.0f)):((int((fRec53[0] < fSlow61)))?((fSlow125 * (fRec53[0] - fSlow58)) + 1.0f):fSlow124))):fRec52[1]);
				fRec54[0] = ((iSlow117)?0.0f:min(fSlow65, (fRec54[1] + 1.0f)));
				fTempPerm41 = ((int((fRec54[0] < 0.0f)))?fRec52[0]:((int((fRec54[0] < fSlow65)))?(fRec52[0] + (fSlow66 * (0 - (fRec54[0] * fRec52[0])))):0.0f));
				fbargraph13 = fTempPerm41;
				fTempPerm42 = fTempPerm41;
			}
			if (iSlow6 || iSlow1) {
				fTempPerm43 = (fTempPerm42 * ftbl0[(((int((65536.0f * fRec44[0])) % 65536) + 65536) % 65536)]);
			}
			if (iSlow4 || iSlow2 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow1) {
				fbargraph14 = fTempPerm30;
				fTempPerm44 = fTempPerm30;
			}
			if (iSlow1) {
				fRec51[0] = (fSlow126 * (fTempPerm44 * ftbl0[(((int((65536.0f * (fRec40[0] + ((fSlow68 * fTempPerm43) + (fRec11[0] * fRec51[1]))))) % 65536) + 65536) % 65536)]));
				fTempPerm45 = (fRec51[0] + fRec47[0]);
			}
			if (iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6) {
				fRec57[0] = ((iSlow115)?0.0f:min(fSlow97, (fRec57[1] + 1.0f)));
				iTempPerm46 = int((fRec57[0] < fSlow94));
				fRec56[0] = ((iSlow108)?(fSlow109 * ((iTempPerm46)?((int((fRec57[0] < 0.0f)))?0.0f:((iTempPerm46)?(fSlow100 * fRec57[0]):1.0f)):((int((fRec57[0] < fSlow97)))?((fSlow128 * (fRec57[0] - fSlow94)) + 1.0f):fSlow127))):fRec56[1]);
				fRec58[0] = ((iSlow117)?0.0f:min(fSlow101, (fRec58[1] + 1.0f)));
				fTempPerm47 = ((int((fRec58[0] < 0.0f)))?fRec56[0]:((int((fRec58[0] < fSlow101)))?(fRec56[0] + (fSlow102 * (0 - (fRec58[0] * fRec56[0])))):0.0f));
				fbargraph15 = fTempPerm47;
				fTempPerm48 = fTempPerm47;
			}
			if (iSlow10 || iSlow9 || iSlow6) {
				fTempPerm49 = (fTempPerm48 * ftbl0[(((int((65536.0f * fRec36[0])) % 65536) + 65536) % 65536)]);
				fTempPerm50 = (fSlow36 * fTempPerm38);
			}
			if (iSlow10 || iSlow6) {
				fTempPerm51 = (fTempPerm50 + (fSlow48 * fTempPerm49));
			}
			if (iSlow6) {
				fRec55[0] = (fSlow126 * (fTempPerm44 * ftbl0[(((int((65536.0f * (fRec40[0] + ((fRec11[0] * fRec55[1]) + (fSlow35 * (fTempPerm51 + (fSlow67 * fTempPerm43))))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow12 || iSlow11 || iSlow8 || iSlow7) {
				fTempPerm52 = (fTempPerm48 * ftbl0[(((int((65536.0f * (fRec36[0] + fTempPerm39))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow12 || iSlow11 || iSlow7) {
				fTempPerm53 = (fSlow103 * fTempPerm52);
			}
			if (iSlow12 || iSlow7) {
				fRec59[0] = (fSlow119 * (fTempPerm34 * ftbl0[(((int((65536.0f * (fRec44[0] + (fTempPerm53 + (fRec22[0] * fRec59[1]))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow7) {
				fRec60[0] = (fSlow126 * (fTempPerm44 * ftbl0[(((int((65536.0f * (fRec40[0] + (fTempPerm53 + (fRec11[0] * fRec60[1]))))) % 65536) + 65536) % 65536)]));
				fTempPerm54 = (fRec60[0] + fRec59[0]);
			}
			if (iSlow8) {
				fRec61[0] = (fSlow126 * (fTempPerm44 * ftbl0[(((int((65536.0f * (fRec40[0] + ((fRec11[0] * fRec61[1]) + (fSlow35 * ((fSlow48 * fTempPerm52) + (fSlow67 * (fTempPerm42 * ftbl0[(((int((65536.0f * (fRec44[0] + fTempPerm39))) % 65536) + 65536) % 65536)])))))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow9) {
				fRec62[0] = (fSlow126 * (fTempPerm44 * ftbl0[(((int((65536.0f * (fRec40[0] + ((fRec11[0] * fRec62[1]) + (fSlow35 * (fTempPerm50 + (fSlow67 * (fTempPerm42 * ftbl0[(((int((65536.0f * (fRec44[0] + (fSlow103 * fTempPerm49)))) % 65536) + 65536) % 65536)])))))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow10) {
				fRec63[0] = (fSlow126 * (fTempPerm44 * ftbl0[(((int((65536.0f * (fRec40[0] + ((fRec11[0] * fRec63[1]) + (fSlow68 * (fTempPerm42 * ftbl0[(((int((65536.0f * (fRec44[0] + (fSlow35 * fTempPerm51)))) % 65536) + 65536) % 65536)])))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow11) {
				fRec64[0] = (fSlow126 * (fTempPerm44 * ftbl0[(((int((65536.0f * (fRec40[0] + ((fRec11[0] * fRec64[1]) + (fSlow68 * (fTempPerm42 * ftbl0[(((int((65536.0f * (fRec44[0] + fTempPerm53))) % 65536) + 65536) % 65536)])))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow4 || iSlow2 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow1 || iSlow3) {
				fRec66[0] = (fSlow130 + (fRec66[1] - floorf((fSlow130 + fRec66[1]))));
				iRec68[0] = (iSlow132 * (iRec68[1] + 1));
				iTempPerm55 = int((iRec68[0] < iSlow45));
				fTempPerm56 = expf((0 - (fConst4 / ((iSlow133)?((iTempPerm55)?fSlow44:fSlow42):fSlow41))));
				fRec67[0] = ((fRec67[1] * fTempPerm56) + (((iSlow133)?((iTempPerm55)?1.5873015873015872f:fSlow135):0.0f) * (1.0f - fTempPerm56)));
				fTempPerm57 = min(1.0f, fRec67[0]);
			}
			if (iSlow4 || iSlow2 || iSlow1 || iSlow3) {
				fbargraph16 = fTempPerm57;
				fTempPerm58 = fTempPerm57;
			}
			if (iSlow4 || iSlow3) {
				fRec65[0] = (fSlow137 * (fTempPerm58 * ftbl0[(((int((65536.0f * (fRec66[0] + (fRec2[0] * fRec65[1])))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow4 || iSlow2 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow1 || iSlow3) {
				fRec70[0] = (fSlow138 + (fRec70[1] - floorf((fSlow138 + fRec70[1]))));
			}
			if (iSlow3) {
				fRec72[0] = ((iSlow140)?0.0f:min(fSlow80, (fRec72[1] + 1.0f)));
				iTempPerm59 = int((fRec72[0] < fSlow77));
				fRec71[0] = ((iSlow133)?(fSlow134 * ((iTempPerm59)?((int((fRec72[0] < 0.0f)))?0.0f:((iTempPerm59)?(fSlow83 * fRec72[0]):1.0f)):((int((fRec72[0] < fSlow80)))?((fSlow141 * (fRec72[0] - fSlow77)) + 1.0f):fSlow139))):fRec71[1]);
				fRec73[0] = ((iSlow142)?0.0f:min(fSlow84, (fRec73[1] + 1.0f)));
				fTempPerm60 = ((int((fRec73[0] < 0.0f)))?fRec71[0]:((int((fRec73[0] < fSlow84)))?(fRec71[0] + (fSlow85 * (0 - (fRec73[0] * fRec71[0])))):0.0f));
				fbargraph17 = fTempPerm60;
			}
			if (iSlow4 || iSlow2 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow1 || iSlow3) {
				fRec74[0] = (fSlow143 + (fRec74[1] - floorf((fSlow143 + fRec74[1]))));
			}
			if (iSlow4 || iSlow2 || iSlow12 || iSlow7 || iSlow3) {
				fbargraph18 = fTempPerm57;
				fTempPerm61 = fTempPerm57;
			}
			if (iSlow3) {
				fRec69[0] = (fSlow144 * (fTempPerm61 * ftbl0[(((int((65536.0f * (fRec74[0] + ((fRec22[0] * fRec69[1]) + (fSlow86 * (fTempPerm60 * ftbl0[(((int((65536.0f * fRec70[0])) % 65536) + 65536) % 65536)])))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow4 || iSlow2 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow1 || iSlow3) {
				fRec76[0] = (fSlow145 + (fRec76[1] - floorf((fSlow145 + fRec76[1]))));
			}
			if (iSlow4 || iSlow3) {
				fbargraph19 = fTempPerm57;
				fRec75[0] = (fSlow146 * (fTempPerm57 * ftbl0[(((int((65536.0f * (fRec76[0] + (fRec24[0] * fRec75[1])))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow3) {
				fTempPerm62 = ((fRec75[0] + fRec69[0]) + fRec65[0]);
			}
			if (iSlow2 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow1) {
				fRec79[0] = ((iSlow140)?0.0f:min(fSlow24, (fRec79[1] + 1.0f)));
				iTempPerm63 = int((fRec79[0] < fSlow21));
				fRec78[0] = ((iSlow133)?(fSlow134 * ((iTempPerm63)?((int((fRec79[0] < 0.0f)))?0.0f:((iTempPerm63)?(fSlow28 * fRec79[0]):1.0f)):((int((fRec79[0] < fSlow24)))?((fSlow148 * (fRec79[0] - fSlow21)) + 1.0f):fSlow147))):fRec78[1]);
				fRec80[0] = ((iSlow142)?0.0f:min(fSlow32, (fRec80[1] + 1.0f)));
				fTempPerm64 = ((int((fRec80[0] < 0.0f)))?fRec78[0]:((int((fRec80[0] < fSlow32)))?(fRec78[0] + (fSlow34 * (0 - (fRec80[0] * fRec78[0])))):0.0f));
				fbargraph20 = fTempPerm64;
				fTempPerm65 = (fTempPerm64 * ftbl0[(((int((65536.0f * fRec76[0])) % 65536) + 65536) % 65536)]);
			}
			if (iSlow2 || iSlow12 || iSlow11 || iSlow8 || iSlow7 || iSlow1) {
				fTempPerm66 = (fSlow37 * fTempPerm65);
			}
			if (iSlow2 || iSlow1) {
				fRec77[0] = (fSlow137 * (fTempPerm58 * ftbl0[(((int((65536.0f * (fRec66[0] + (fTempPerm66 + (fRec2[0] * fRec77[1]))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow6 || iSlow1) {
				fRec83[0] = ((iSlow140)?0.0f:min(fSlow61, (fRec83[1] + 1.0f)));
				iTempPerm67 = int((fRec83[0] < fSlow58));
				fRec82[0] = ((iSlow133)?(fSlow134 * ((iTempPerm67)?((int((fRec83[0] < 0.0f)))?0.0f:((iTempPerm67)?(fSlow64 * fRec83[0]):1.0f)):((int((fRec83[0] < fSlow61)))?((fSlow150 * (fRec83[0] - fSlow58)) + 1.0f):fSlow149))):fRec82[1]);
				fRec84[0] = ((iSlow142)?0.0f:min(fSlow65, (fRec84[1] + 1.0f)));
				fTempPerm68 = ((int((fRec84[0] < 0.0f)))?fRec82[0]:((int((fRec84[0] < fSlow65)))?(fRec82[0] + (fSlow66 * (0 - (fRec84[0] * fRec82[0])))):0.0f));
				fbargraph21 = fTempPerm68;
				fTempPerm69 = fTempPerm68;
			}
			if (iSlow6 || iSlow1) {
				fTempPerm70 = (fTempPerm69 * ftbl0[(((int((65536.0f * fRec74[0])) % 65536) + 65536) % 65536)]);
			}
			if (iSlow4 || iSlow2 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow1) {
				fbargraph22 = fTempPerm57;
				fTempPerm71 = fTempPerm57;
			}
			if (iSlow1) {
				fRec81[0] = (fSlow151 * (fTempPerm71 * ftbl0[(((int((65536.0f * (fRec70[0] + ((fSlow68 * fTempPerm70) + (fRec11[0] * fRec81[1]))))) % 65536) + 65536) % 65536)]));
				fTempPerm72 = (fRec81[0] + fRec77[0]);
			}
			if (iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6) {
				fRec87[0] = ((iSlow140)?0.0f:min(fSlow97, (fRec87[1] + 1.0f)));
				iTempPerm73 = int((fRec87[0] < fSlow94));
				fRec86[0] = ((iSlow133)?(fSlow134 * ((iTempPerm73)?((int((fRec87[0] < 0.0f)))?0.0f:((iTempPerm73)?(fSlow100 * fRec87[0]):1.0f)):((int((fRec87[0] < fSlow97)))?((fSlow153 * (fRec87[0] - fSlow94)) + 1.0f):fSlow152))):fRec86[1]);
				fRec88[0] = ((iSlow142)?0.0f:min(fSlow101, (fRec88[1] + 1.0f)));
				fTempPerm74 = ((int((fRec88[0] < 0.0f)))?fRec86[0]:((int((fRec88[0] < fSlow101)))?(fRec86[0] + (fSlow102 * (0 - (fRec88[0] * fRec86[0])))):0.0f));
				fbargraph23 = fTempPerm74;
				fTempPerm75 = fTempPerm74;
			}
			if (iSlow10 || iSlow9 || iSlow6) {
				fTempPerm76 = (fTempPerm75 * ftbl0[(((int((65536.0f * fRec66[0])) % 65536) + 65536) % 65536)]);
				fTempPerm77 = (fSlow36 * fTempPerm65);
			}
			if (iSlow10 || iSlow6) {
				fTempPerm78 = (fTempPerm77 + (fSlow48 * fTempPerm76));
			}
			if (iSlow6) {
				fRec85[0] = (fSlow151 * (fTempPerm71 * ftbl0[(((int((65536.0f * (fRec70[0] + ((fRec11[0] * fRec85[1]) + (fSlow35 * (fTempPerm78 + (fSlow67 * fTempPerm70))))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow12 || iSlow11 || iSlow8 || iSlow7) {
				fTempPerm79 = (fTempPerm75 * ftbl0[(((int((65536.0f * (fRec66[0] + fTempPerm66))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow12 || iSlow11 || iSlow7) {
				fTempPerm80 = (fSlow103 * fTempPerm79);
			}
			if (iSlow12 || iSlow7) {
				fRec89[0] = (fSlow144 * (fTempPerm61 * ftbl0[(((int((65536.0f * (fRec74[0] + (fTempPerm80 + (fRec22[0] * fRec89[1]))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow7) {
				fRec90[0] = (fSlow151 * (fTempPerm71 * ftbl0[(((int((65536.0f * (fRec70[0] + (fTempPerm80 + (fRec11[0] * fRec90[1]))))) % 65536) + 65536) % 65536)]));
				fTempPerm81 = (fRec90[0] + fRec89[0]);
			}
			if (iSlow8) {
				fRec91[0] = (fSlow151 * (fTempPerm71 * ftbl0[(((int((65536.0f * (fRec70[0] + ((fRec11[0] * fRec91[1]) + (fSlow35 * ((fSlow48 * fTempPerm79) + (fSlow67 * (fTempPerm69 * ftbl0[(((int((65536.0f * (fRec74[0] + fTempPerm66))) % 65536) + 65536) % 65536)])))))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow9) {
				fRec92[0] = (fSlow151 * (fTempPerm71 * ftbl0[(((int((65536.0f * (fRec70[0] + ((fRec11[0] * fRec92[1]) + (fSlow35 * (fTempPerm77 + (fSlow67 * (fTempPerm69 * ftbl0[(((int((65536.0f * (fRec74[0] + (fSlow103 * fTempPerm76)))) % 65536) + 65536) % 65536)])))))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow10) {
				fRec93[0] = (fSlow151 * (fTempPerm71 * ftbl0[(((int((65536.0f * (fRec70[0] + ((fRec11[0] * fRec93[1]) + (fSlow68 * (fTempPerm69 * ftbl0[(((int((65536.0f * (fRec74[0] + (fSlow35 * fTempPerm78)))) % 65536) + 65536) % 65536)])))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow11) {
				fRec94[0] = (fSlow151 * (fTempPerm71 * ftbl0[(((int((65536.0f * (fRec70[0] + ((fRec11[0] * fRec94[1]) + (fSlow68 * (fTempPerm69 * ftbl0[(((int((65536.0f * (fRec74[0] + fTempPerm80))) % 65536) + 65536) % 65536)])))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow4 || iSlow2 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow1 || iSlow3) {
				fRec96[0] = (fSlow155 + (fRec96[1] - floorf((fSlow155 + fRec96[1]))));
				iRec98[0] = (iSlow157 * (iRec98[1] + 1));
				iTempPerm82 = int((iRec98[0] < iSlow45));
				fTempPerm83 = expf((0 - (fConst4 / ((iSlow158)?((iTempPerm82)?fSlow44:fSlow42):fSlow41))));
				fRec97[0] = ((fRec97[1] * fTempPerm83) + (((iSlow158)?((iTempPerm82)?1.5873015873015872f:fSlow160):0.0f) * (1.0f - fTempPerm83)));
				fTempPerm84 = min(1.0f, fRec97[0]);
			}
			if (iSlow4 || iSlow2 || iSlow1 || iSlow3) {
				fbargraph24 = fTempPerm84;
				fTempPerm85 = fTempPerm84;
			}
			if (iSlow4 || iSlow3) {
				fRec95[0] = (fSlow162 * (fTempPerm85 * ftbl0[(((int((65536.0f * (fRec96[0] + (fRec2[0] * fRec95[1])))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow4 || iSlow2 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow1 || iSlow3) {
				fRec100[0] = (fSlow163 + (fRec100[1] - floorf((fSlow163 + fRec100[1]))));
			}
			if (iSlow3) {
				fRec102[0] = ((iSlow165)?0.0f:min(fSlow80, (fRec102[1] + 1.0f)));
				iTempPerm86 = int((fRec102[0] < fSlow77));
				fRec101[0] = ((iSlow158)?(fSlow159 * ((iTempPerm86)?((int((fRec102[0] < 0.0f)))?0.0f:((iTempPerm86)?(fSlow83 * fRec102[0]):1.0f)):((int((fRec102[0] < fSlow80)))?((fSlow166 * (fRec102[0] - fSlow77)) + 1.0f):fSlow164))):fRec101[1]);
				fRec103[0] = ((iSlow167)?0.0f:min(fSlow84, (fRec103[1] + 1.0f)));
				fTempPerm87 = ((int((fRec103[0] < 0.0f)))?fRec101[0]:((int((fRec103[0] < fSlow84)))?(fRec101[0] + (fSlow85 * (0 - (fRec103[0] * fRec101[0])))):0.0f));
				fbargraph25 = fTempPerm87;
			}
			if (iSlow4 || iSlow2 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow1 || iSlow3) {
				fRec104[0] = (fSlow168 + (fRec104[1] - floorf((fSlow168 + fRec104[1]))));
			}
			if (iSlow4 || iSlow2 || iSlow12 || iSlow7 || iSlow3) {
				fbargraph26 = fTempPerm84;
				fTempPerm88 = fTempPerm84;
			}
			if (iSlow3) {
				fRec99[0] = (fSlow169 * (fTempPerm88 * ftbl0[(((int((65536.0f * (fRec104[0] + ((fRec22[0] * fRec99[1]) + (fSlow86 * (fTempPerm87 * ftbl0[(((int((65536.0f * fRec100[0])) % 65536) + 65536) % 65536)])))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow4 || iSlow2 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow1 || iSlow3) {
				fRec106[0] = (fSlow170 + (fRec106[1] - floorf((fSlow170 + fRec106[1]))));
			}
			if (iSlow4 || iSlow3) {
				fbargraph27 = fTempPerm84;
				fRec105[0] = (fSlow171 * (fTempPerm84 * ftbl0[(((int((65536.0f * (fRec106[0] + (fRec24[0] * fRec105[1])))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow3) {
				fTempPerm89 = ((fRec105[0] + fRec99[0]) + fRec95[0]);
			}
			if (iSlow2 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow1) {
				fRec109[0] = ((iSlow165)?0.0f:min(fSlow24, (fRec109[1] + 1.0f)));
				iTempPerm90 = int((fRec109[0] < fSlow21));
				fRec108[0] = ((iSlow158)?(fSlow159 * ((iTempPerm90)?((int((fRec109[0] < 0.0f)))?0.0f:((iTempPerm90)?(fSlow28 * fRec109[0]):1.0f)):((int((fRec109[0] < fSlow24)))?((fSlow173 * (fRec109[0] - fSlow21)) + 1.0f):fSlow172))):fRec108[1]);
				fRec110[0] = ((iSlow167)?0.0f:min(fSlow32, (fRec110[1] + 1.0f)));
				fTempPerm91 = ((int((fRec110[0] < 0.0f)))?fRec108[0]:((int((fRec110[0] < fSlow32)))?(fRec108[0] + (fSlow34 * (0 - (fRec110[0] * fRec108[0])))):0.0f));
				fbargraph28 = fTempPerm91;
				fTempPerm92 = (fTempPerm91 * ftbl0[(((int((65536.0f * fRec106[0])) % 65536) + 65536) % 65536)]);
			}
			if (iSlow2 || iSlow12 || iSlow11 || iSlow8 || iSlow7 || iSlow1) {
				fTempPerm93 = (fSlow37 * fTempPerm92);
			}
			if (iSlow2 || iSlow1) {
				fRec107[0] = (fSlow162 * (fTempPerm85 * ftbl0[(((int((65536.0f * (fRec96[0] + (fTempPerm93 + (fRec2[0] * fRec107[1]))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow6 || iSlow1) {
				fRec113[0] = ((iSlow165)?0.0f:min(fSlow61, (fRec113[1] + 1.0f)));
				iTempPerm94 = int((fRec113[0] < fSlow58));
				fRec112[0] = ((iSlow158)?(fSlow159 * ((iTempPerm94)?((int((fRec113[0] < 0.0f)))?0.0f:((iTempPerm94)?(fSlow64 * fRec113[0]):1.0f)):((int((fRec113[0] < fSlow61)))?((fSlow175 * (fRec113[0] - fSlow58)) + 1.0f):fSlow174))):fRec112[1]);
				fRec114[0] = ((iSlow167)?0.0f:min(fSlow65, (fRec114[1] + 1.0f)));
				fTempPerm95 = ((int((fRec114[0] < 0.0f)))?fRec112[0]:((int((fRec114[0] < fSlow65)))?(fRec112[0] + (fSlow66 * (0 - (fRec114[0] * fRec112[0])))):0.0f));
				fbargraph29 = fTempPerm95;
				fTempPerm96 = fTempPerm95;
			}
			if (iSlow6 || iSlow1) {
				fTempPerm97 = (fTempPerm96 * ftbl0[(((int((65536.0f * fRec104[0])) % 65536) + 65536) % 65536)]);
			}
			if (iSlow4 || iSlow2 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow1) {
				fbargraph30 = fTempPerm84;
				fTempPerm98 = fTempPerm84;
			}
			if (iSlow1) {
				fRec111[0] = (fSlow176 * (fTempPerm98 * ftbl0[(((int((65536.0f * (fRec100[0] + ((fSlow68 * fTempPerm97) + (fRec11[0] * fRec111[1]))))) % 65536) + 65536) % 65536)]));
				fTempPerm99 = (fRec111[0] + fRec107[0]);
			}
			if (iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6) {
				fRec117[0] = ((iSlow165)?0.0f:min(fSlow97, (fRec117[1] + 1.0f)));
				iTempPerm100 = int((fRec117[0] < fSlow94));
				fRec116[0] = ((iSlow158)?(fSlow159 * ((iTempPerm100)?((int((fRec117[0] < 0.0f)))?0.0f:((iTempPerm100)?(fSlow100 * fRec117[0]):1.0f)):((int((fRec117[0] < fSlow97)))?((fSlow178 * (fRec117[0] - fSlow94)) + 1.0f):fSlow177))):fRec116[1]);
				fRec118[0] = ((iSlow167)?0.0f:min(fSlow101, (fRec118[1] + 1.0f)));
				fTempPerm101 = ((int((fRec118[0] < 0.0f)))?fRec116[0]:((int((fRec118[0] < fSlow101)))?(fRec116[0] + (fSlow102 * (0 - (fRec118[0] * fRec116[0])))):0.0f));
				fbargraph31 = fTempPerm101;
				fTempPerm102 = fTempPerm101;
			}
			if (iSlow10 || iSlow9 || iSlow6) {
				fTempPerm103 = (fTempPerm102 * ftbl0[(((int((65536.0f * fRec96[0])) % 65536) + 65536) % 65536)]);
				fTempPerm104 = (fSlow36 * fTempPerm92);
			}
			if (iSlow10 || iSlow6) {
				fTempPerm105 = (fTempPerm104 + (fSlow48 * fTempPerm103));
			}
			if (iSlow6) {
				fRec115[0] = (fSlow176 * (fTempPerm98 * ftbl0[(((int((65536.0f * (fRec100[0] + ((fRec11[0] * fRec115[1]) + (fSlow35 * (fTempPerm105 + (fSlow67 * fTempPerm97))))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow12 || iSlow11 || iSlow8 || iSlow7) {
				fTempPerm106 = (fTempPerm102 * ftbl0[(((int((65536.0f * (fRec96[0] + fTempPerm93))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow12 || iSlow11 || iSlow7) {
				fTempPerm107 = (fSlow103 * fTempPerm106);
			}
			if (iSlow12 || iSlow7) {
				fRec119[0] = (fSlow169 * (fTempPerm88 * ftbl0[(((int((65536.0f * (fRec104[0] + (fTempPerm107 + (fRec22[0] * fRec119[1]))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow7) {
				fRec120[0] = (fSlow176 * (fTempPerm98 * ftbl0[(((int((65536.0f * (fRec100[0] + (fTempPerm107 + (fRec11[0] * fRec120[1]))))) % 65536) + 65536) % 65536)]));
				fTempPerm108 = (fRec120[0] + fRec119[0]);
			}
			if (iSlow8) {
				fRec121[0] = (fSlow176 * (fTempPerm98 * ftbl0[(((int((65536.0f * (fRec100[0] + ((fRec11[0] * fRec121[1]) + (fSlow35 * ((fSlow48 * fTempPerm106) + (fSlow67 * (fTempPerm96 * ftbl0[(((int((65536.0f * (fRec104[0] + fTempPerm93))) % 65536) + 65536) % 65536)])))))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow9) {
				fRec122[0] = (fSlow176 * (fTempPerm98 * ftbl0[(((int((65536.0f * (fRec100[0] + ((fRec11[0] * fRec122[1]) + (fSlow35 * (fTempPerm104 + (fSlow67 * (fTempPerm96 * ftbl0[(((int((65536.0f * (fRec104[0] + (fSlow103 * fTempPerm103)))) % 65536) + 65536) % 65536)])))))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow10) {
				fRec123[0] = (fSlow176 * (fTempPerm98 * ftbl0[(((int((65536.0f * (fRec100[0] + ((fRec11[0] * fRec123[1]) + (fSlow68 * (fTempPerm96 * ftbl0[(((int((65536.0f * (fRec104[0] + (fSlow35 * fTempPerm105)))) % 65536) + 65536) % 65536)])))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow11) {
				fRec124[0] = (fSlow176 * (fTempPerm98 * ftbl0[(((int((65536.0f * (fRec100[0] + ((fRec11[0] * fRec124[1]) + (fSlow68 * (fTempPerm96 * ftbl0[(((int((65536.0f * (fRec104[0] + fTempPerm107))) % 65536) + 65536) % 65536)])))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow4 || iSlow2 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow1 || iSlow3) {
				fRec126[0] = (fSlow180 + (fRec126[1] - floorf((fSlow180 + fRec126[1]))));
				iRec128[0] = (iSlow182 * (iRec128[1] + 1));
				iTempPerm109 = int((iRec128[0] < iSlow45));
				fTempPerm110 = expf((0 - (fConst4 / ((iSlow183)?((iTempPerm109)?fSlow44:fSlow42):fSlow41))));
				fRec127[0] = ((fRec127[1] * fTempPerm110) + (((iSlow183)?((iTempPerm109)?1.5873015873015872f:fSlow185):0.0f) * (1.0f - fTempPerm110)));
				fTempPerm111 = min(1.0f, fRec127[0]);
			}
			if (iSlow4 || iSlow2 || iSlow1 || iSlow3) {
				fbargraph32 = fTempPerm111;
				fTempPerm112 = fTempPerm111;
			}
			if (iSlow4 || iSlow3) {
				fRec125[0] = (fSlow187 * (fTempPerm112 * ftbl0[(((int((65536.0f * (fRec126[0] + (fRec2[0] * fRec125[1])))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow4 || iSlow2 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow1 || iSlow3) {
				fRec130[0] = (fSlow188 + (fRec130[1] - floorf((fSlow188 + fRec130[1]))));
			}
			if (iSlow3) {
				fRec132[0] = ((iSlow190)?0.0f:min(fSlow80, (fRec132[1] + 1.0f)));
				iTempPerm113 = int((fRec132[0] < fSlow77));
				fRec131[0] = ((iSlow183)?(fSlow184 * ((iTempPerm113)?((int((fRec132[0] < 0.0f)))?0.0f:((iTempPerm113)?(fSlow83 * fRec132[0]):1.0f)):((int((fRec132[0] < fSlow80)))?((fSlow191 * (fRec132[0] - fSlow77)) + 1.0f):fSlow189))):fRec131[1]);
				fRec133[0] = ((iSlow192)?0.0f:min(fSlow84, (fRec133[1] + 1.0f)));
				fTempPerm114 = ((int((fRec133[0] < 0.0f)))?fRec131[0]:((int((fRec133[0] < fSlow84)))?(fRec131[0] + (fSlow85 * (0 - (fRec133[0] * fRec131[0])))):0.0f));
				fbargraph33 = fTempPerm114;
			}
			if (iSlow4 || iSlow2 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow1 || iSlow3) {
				fRec134[0] = (fSlow193 + (fRec134[1] - floorf((fSlow193 + fRec134[1]))));
			}
			if (iSlow4 || iSlow2 || iSlow12 || iSlow7 || iSlow3) {
				fbargraph34 = fTempPerm111;
				fTempPerm115 = fTempPerm111;
			}
			if (iSlow3) {
				fRec129[0] = (fSlow194 * (fTempPerm115 * ftbl0[(((int((65536.0f * (fRec134[0] + ((fRec22[0] * fRec129[1]) + (fSlow86 * (fTempPerm114 * ftbl0[(((int((65536.0f * fRec130[0])) % 65536) + 65536) % 65536)])))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow4 || iSlow2 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow1 || iSlow3) {
				fRec136[0] = (fSlow195 + (fRec136[1] - floorf((fSlow195 + fRec136[1]))));
			}
			if (iSlow4 || iSlow3) {
				fbargraph35 = fTempPerm111;
				fRec135[0] = (fSlow196 * (fTempPerm111 * ftbl0[(((int((65536.0f * (fRec136[0] + (fRec24[0] * fRec135[1])))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow3) {
				fTempPerm116 = ((fRec135[0] + fRec129[0]) + fRec125[0]);
			}
			if (iSlow2 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow1) {
				fRec139[0] = ((iSlow190)?0.0f:min(fSlow24, (fRec139[1] + 1.0f)));
				iTempPerm117 = int((fRec139[0] < fSlow21));
				fRec138[0] = ((iSlow183)?(fSlow184 * ((iTempPerm117)?((int((fRec139[0] < 0.0f)))?0.0f:((iTempPerm117)?(fSlow28 * fRec139[0]):1.0f)):((int((fRec139[0] < fSlow24)))?((fSlow198 * (fRec139[0] - fSlow21)) + 1.0f):fSlow197))):fRec138[1]);
				fRec140[0] = ((iSlow192)?0.0f:min(fSlow32, (fRec140[1] + 1.0f)));
				fTempPerm118 = ((int((fRec140[0] < 0.0f)))?fRec138[0]:((int((fRec140[0] < fSlow32)))?(fRec138[0] + (fSlow34 * (0 - (fRec140[0] * fRec138[0])))):0.0f));
				fbargraph36 = fTempPerm118;
				fTempPerm119 = (fTempPerm118 * ftbl0[(((int((65536.0f * fRec136[0])) % 65536) + 65536) % 65536)]);
			}
			if (iSlow2 || iSlow12 || iSlow11 || iSlow8 || iSlow7 || iSlow1) {
				fTempPerm120 = (fSlow37 * fTempPerm119);
			}
			if (iSlow2 || iSlow1) {
				fRec137[0] = (fSlow187 * (fTempPerm112 * ftbl0[(((int((65536.0f * (fRec126[0] + (fTempPerm120 + (fRec2[0] * fRec137[1]))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow6 || iSlow1) {
				fRec143[0] = ((iSlow190)?0.0f:min(fSlow61, (fRec143[1] + 1.0f)));
				iTempPerm121 = int((fRec143[0] < fSlow58));
				fRec142[0] = ((iSlow183)?(fSlow184 * ((iTempPerm121)?((int((fRec143[0] < 0.0f)))?0.0f:((iTempPerm121)?(fSlow64 * fRec143[0]):1.0f)):((int((fRec143[0] < fSlow61)))?((fSlow200 * (fRec143[0] - fSlow58)) + 1.0f):fSlow199))):fRec142[1]);
				fRec144[0] = ((iSlow192)?0.0f:min(fSlow65, (fRec144[1] + 1.0f)));
				fTempPerm122 = ((int((fRec144[0] < 0.0f)))?fRec142[0]:((int((fRec144[0] < fSlow65)))?(fRec142[0] + (fSlow66 * (0 - (fRec144[0] * fRec142[0])))):0.0f));
				fbargraph37 = fTempPerm122;
				fTempPerm123 = fTempPerm122;
			}
			if (iSlow6 || iSlow1) {
				fTempPerm124 = (fTempPerm123 * ftbl0[(((int((65536.0f * fRec134[0])) % 65536) + 65536) % 65536)]);
			}
			if (iSlow4 || iSlow2 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow1) {
				fbargraph38 = fTempPerm111;
				fTempPerm125 = fTempPerm111;
			}
			if (iSlow1) {
				fRec141[0] = (fSlow201 * (fTempPerm125 * ftbl0[(((int((65536.0f * (fRec130[0] + ((fSlow68 * fTempPerm124) + (fRec11[0] * fRec141[1]))))) % 65536) + 65536) % 65536)]));
				fTempPerm126 = (fRec141[0] + fRec137[0]);
			}
			if (iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6) {
				fRec147[0] = ((iSlow190)?0.0f:min(fSlow97, (fRec147[1] + 1.0f)));
				iTempPerm127 = int((fRec147[0] < fSlow94));
				fRec146[0] = ((iSlow183)?(fSlow184 * ((iTempPerm127)?((int((fRec147[0] < 0.0f)))?0.0f:((iTempPerm127)?(fSlow100 * fRec147[0]):1.0f)):((int((fRec147[0] < fSlow97)))?((fSlow203 * (fRec147[0] - fSlow94)) + 1.0f):fSlow202))):fRec146[1]);
				fRec148[0] = ((iSlow192)?0.0f:min(fSlow101, (fRec148[1] + 1.0f)));
				fTempPerm128 = ((int((fRec148[0] < 0.0f)))?fRec146[0]:((int((fRec148[0] < fSlow101)))?(fRec146[0] + (fSlow102 * (0 - (fRec148[0] * fRec146[0])))):0.0f));
				fbargraph39 = fTempPerm128;
				fTempPerm129 = fTempPerm128;
			}
			if (iSlow10 || iSlow9 || iSlow6) {
				fTempPerm130 = (fTempPerm129 * ftbl0[(((int((65536.0f * fRec126[0])) % 65536) + 65536) % 65536)]);
				fTempPerm131 = (fSlow36 * fTempPerm119);
			}
			if (iSlow10 || iSlow6) {
				fTempPerm132 = (fTempPerm131 + (fSlow48 * fTempPerm130));
			}
			if (iSlow6) {
				fRec145[0] = (fSlow201 * (fTempPerm125 * ftbl0[(((int((65536.0f * (fRec130[0] + ((fRec11[0] * fRec145[1]) + (fSlow35 * (fTempPerm132 + (fSlow67 * fTempPerm124))))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow12 || iSlow11 || iSlow8 || iSlow7) {
				fTempPerm133 = (fTempPerm129 * ftbl0[(((int((65536.0f * (fRec126[0] + fTempPerm120))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow12 || iSlow11 || iSlow7) {
				fTempPerm134 = (fSlow103 * fTempPerm133);
			}
			if (iSlow12 || iSlow7) {
				fRec149[0] = (fSlow194 * (fTempPerm115 * ftbl0[(((int((65536.0f * (fRec134[0] + (fTempPerm134 + (fRec22[0] * fRec149[1]))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow7) {
				fRec150[0] = (fSlow201 * (fTempPerm125 * ftbl0[(((int((65536.0f * (fRec130[0] + (fTempPerm134 + (fRec11[0] * fRec150[1]))))) % 65536) + 65536) % 65536)]));
				fTempPerm135 = (fRec150[0] + fRec149[0]);
			}
			if (iSlow8) {
				fRec151[0] = (fSlow201 * (fTempPerm125 * ftbl0[(((int((65536.0f * (fRec130[0] + ((fRec11[0] * fRec151[1]) + (fSlow35 * ((fSlow48 * fTempPerm133) + (fSlow67 * (fTempPerm123 * ftbl0[(((int((65536.0f * (fRec134[0] + fTempPerm120))) % 65536) + 65536) % 65536)])))))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow9) {
				fRec152[0] = (fSlow201 * (fTempPerm125 * ftbl0[(((int((65536.0f * (fRec130[0] + ((fRec11[0] * fRec152[1]) + (fSlow35 * (fTempPerm131 + (fSlow67 * (fTempPerm123 * ftbl0[(((int((65536.0f * (fRec134[0] + (fSlow103 * fTempPerm130)))) % 65536) + 65536) % 65536)])))))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow10) {
				fRec153[0] = (fSlow201 * (fTempPerm125 * ftbl0[(((int((65536.0f * (fRec130[0] + ((fRec11[0] * fRec153[1]) + (fSlow68 * (fTempPerm123 * ftbl0[(((int((65536.0f * (fRec134[0] + (fSlow35 * fTempPerm132)))) % 65536) + 65536) % 65536)])))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow11) {
				fRec154[0] = (fSlow201 * (fTempPerm125 * ftbl0[(((int((65536.0f * (fRec130[0] + ((fRec11[0] * fRec154[1]) + (fSlow68 * (fTempPerm123 * ftbl0[(((int((65536.0f * (fRec134[0] + fTempPerm134))) % 65536) + 65536) % 65536)])))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow4 || iSlow2 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow1 || iSlow3) {
				fRec156[0] = (fSlow205 + (fRec156[1] - floorf((fSlow205 + fRec156[1]))));
				iRec158[0] = (iSlow207 * (iRec158[1] + 1));
				iTempPerm136 = int((iRec158[0] < iSlow45));
				fTempPerm137 = expf((0 - (fConst4 / ((iSlow208)?((iTempPerm136)?fSlow44:fSlow42):fSlow41))));
				fRec157[0] = ((fRec157[1] * fTempPerm137) + (((iSlow208)?((iTempPerm136)?1.5873015873015872f:fSlow210):0.0f) * (1.0f - fTempPerm137)));
				fTempPerm138 = min(1.0f, fRec157[0]);
			}
			if (iSlow4 || iSlow2 || iSlow1 || iSlow3) {
				fbargraph40 = fTempPerm138;
				fTempPerm139 = fTempPerm138;
			}
			if (iSlow4 || iSlow3) {
				fRec155[0] = (fSlow212 * (fTempPerm139 * ftbl0[(((int((65536.0f * (fRec156[0] + (fRec2[0] * fRec155[1])))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow4 || iSlow2 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow1 || iSlow3) {
				fRec160[0] = (fSlow213 + (fRec160[1] - floorf((fSlow213 + fRec160[1]))));
			}
			if (iSlow3) {
				fRec162[0] = ((iSlow215)?0.0f:min(fSlow80, (fRec162[1] + 1.0f)));
				iTempPerm140 = int((fRec162[0] < fSlow77));
				fRec161[0] = ((iSlow208)?(fSlow209 * ((iTempPerm140)?((int((fRec162[0] < 0.0f)))?0.0f:((iTempPerm140)?(fSlow83 * fRec162[0]):1.0f)):((int((fRec162[0] < fSlow80)))?((fSlow216 * (fRec162[0] - fSlow77)) + 1.0f):fSlow214))):fRec161[1]);
				fRec163[0] = ((iSlow217)?0.0f:min(fSlow84, (fRec163[1] + 1.0f)));
				fTempPerm141 = ((int((fRec163[0] < 0.0f)))?fRec161[0]:((int((fRec163[0] < fSlow84)))?(fRec161[0] + (fSlow85 * (0 - (fRec163[0] * fRec161[0])))):0.0f));
				fbargraph41 = fTempPerm141;
			}
			if (iSlow4 || iSlow2 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow1 || iSlow3) {
				fRec164[0] = (fSlow218 + (fRec164[1] - floorf((fSlow218 + fRec164[1]))));
			}
			if (iSlow4 || iSlow2 || iSlow12 || iSlow7 || iSlow3) {
				fbargraph42 = fTempPerm138;
				fTempPerm142 = fTempPerm138;
			}
			if (iSlow3) {
				fRec159[0] = (fSlow219 * (fTempPerm142 * ftbl0[(((int((65536.0f * (fRec164[0] + ((fRec22[0] * fRec159[1]) + (fSlow86 * (fTempPerm141 * ftbl0[(((int((65536.0f * fRec160[0])) % 65536) + 65536) % 65536)])))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow4 || iSlow2 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow1 || iSlow3) {
				fRec166[0] = (fSlow220 + (fRec166[1] - floorf((fSlow220 + fRec166[1]))));
			}
			if (iSlow4 || iSlow3) {
				fbargraph43 = fTempPerm138;
				fRec165[0] = (fSlow221 * (fTempPerm138 * ftbl0[(((int((65536.0f * (fRec166[0] + (fRec24[0] * fRec165[1])))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow3) {
				fTempPerm143 = ((fRec165[0] + fRec159[0]) + fRec155[0]);
			}
			if (iSlow2 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow1) {
				fRec169[0] = ((iSlow215)?0.0f:min(fSlow24, (fRec169[1] + 1.0f)));
				iTempPerm144 = int((fRec169[0] < fSlow21));
				fRec168[0] = ((iSlow208)?(fSlow209 * ((iTempPerm144)?((int((fRec169[0] < 0.0f)))?0.0f:((iTempPerm144)?(fSlow28 * fRec169[0]):1.0f)):((int((fRec169[0] < fSlow24)))?((fSlow223 * (fRec169[0] - fSlow21)) + 1.0f):fSlow222))):fRec168[1]);
				fRec170[0] = ((iSlow217)?0.0f:min(fSlow32, (fRec170[1] + 1.0f)));
				fTempPerm145 = ((int((fRec170[0] < 0.0f)))?fRec168[0]:((int((fRec170[0] < fSlow32)))?(fRec168[0] + (fSlow34 * (0 - (fRec170[0] * fRec168[0])))):0.0f));
				fbargraph44 = fTempPerm145;
				fTempPerm146 = (fTempPerm145 * ftbl0[(((int((65536.0f * fRec166[0])) % 65536) + 65536) % 65536)]);
			}
			if (iSlow2 || iSlow12 || iSlow11 || iSlow8 || iSlow7 || iSlow1) {
				fTempPerm147 = (fSlow37 * fTempPerm146);
			}
			if (iSlow2 || iSlow1) {
				fRec167[0] = (fSlow212 * (fTempPerm139 * ftbl0[(((int((65536.0f * (fRec156[0] + (fTempPerm147 + (fRec2[0] * fRec167[1]))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow6 || iSlow1) {
				fRec173[0] = ((iSlow215)?0.0f:min(fSlow61, (fRec173[1] + 1.0f)));
				iTempPerm148 = int((fRec173[0] < fSlow58));
				fRec172[0] = ((iSlow208)?(fSlow209 * ((iTempPerm148)?((int((fRec173[0] < 0.0f)))?0.0f:((iTempPerm148)?(fSlow64 * fRec173[0]):1.0f)):((int((fRec173[0] < fSlow61)))?((fSlow225 * (fRec173[0] - fSlow58)) + 1.0f):fSlow224))):fRec172[1]);
				fRec174[0] = ((iSlow217)?0.0f:min(fSlow65, (fRec174[1] + 1.0f)));
				fTempPerm149 = ((int((fRec174[0] < 0.0f)))?fRec172[0]:((int((fRec174[0] < fSlow65)))?(fRec172[0] + (fSlow66 * (0 - (fRec174[0] * fRec172[0])))):0.0f));
				fbargraph45 = fTempPerm149;
				fTempPerm150 = fTempPerm149;
			}
			if (iSlow6 || iSlow1) {
				fTempPerm151 = (fTempPerm150 * ftbl0[(((int((65536.0f * fRec164[0])) % 65536) + 65536) % 65536)]);
			}
			if (iSlow4 || iSlow2 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow1) {
				fbargraph46 = fTempPerm138;
				fTempPerm152 = fTempPerm138;
			}
			if (iSlow1) {
				fRec171[0] = (fSlow226 * (fTempPerm152 * ftbl0[(((int((65536.0f * (fRec160[0] + ((fSlow68 * fTempPerm151) + (fRec11[0] * fRec171[1]))))) % 65536) + 65536) % 65536)]));
				fTempPerm153 = (fRec171[0] + fRec167[0]);
			}
			if (iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6) {
				fRec177[0] = ((iSlow215)?0.0f:min(fSlow97, (fRec177[1] + 1.0f)));
				iTempPerm154 = int((fRec177[0] < fSlow94));
				fRec176[0] = ((iSlow208)?(fSlow209 * ((iTempPerm154)?((int((fRec177[0] < 0.0f)))?0.0f:((iTempPerm154)?(fSlow100 * fRec177[0]):1.0f)):((int((fRec177[0] < fSlow97)))?((fSlow228 * (fRec177[0] - fSlow94)) + 1.0f):fSlow227))):fRec176[1]);
				fRec178[0] = ((iSlow217)?0.0f:min(fSlow101, (fRec178[1] + 1.0f)));
				fTempPerm155 = ((int((fRec178[0] < 0.0f)))?fRec176[0]:((int((fRec178[0] < fSlow101)))?(fRec176[0] + (fSlow102 * (0 - (fRec178[0] * fRec176[0])))):0.0f));
				fbargraph47 = fTempPerm155;
				fTempPerm156 = fTempPerm155;
			}
			if (iSlow10 || iSlow9 || iSlow6) {
				fTempPerm157 = (fTempPerm156 * ftbl0[(((int((65536.0f * fRec156[0])) % 65536) + 65536) % 65536)]);
				fTempPerm158 = (fSlow36 * fTempPerm146);
			}
			if (iSlow10 || iSlow6) {
				fTempPerm159 = (fTempPerm158 + (fSlow48 * fTempPerm157));
			}
			if (iSlow6) {
				fRec175[0] = (fSlow226 * (fTempPerm152 * ftbl0[(((int((65536.0f * (fRec160[0] + ((fRec11[0] * fRec175[1]) + (fSlow35 * (fTempPerm159 + (fSlow67 * fTempPerm151))))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow12 || iSlow11 || iSlow8 || iSlow7) {
				fTempPerm160 = (fTempPerm156 * ftbl0[(((int((65536.0f * (fRec156[0] + fTempPerm147))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow12 || iSlow11 || iSlow7) {
				fTempPerm161 = (fSlow103 * fTempPerm160);
			}
			if (iSlow12 || iSlow7) {
				fRec179[0] = (fSlow219 * (fTempPerm142 * ftbl0[(((int((65536.0f * (fRec164[0] + (fTempPerm161 + (fRec22[0] * fRec179[1]))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow7) {
				fRec180[0] = (fSlow226 * (fTempPerm152 * ftbl0[(((int((65536.0f * (fRec160[0] + (fTempPerm161 + (fRec11[0] * fRec180[1]))))) % 65536) + 65536) % 65536)]));
				fTempPerm162 = (fRec180[0] + fRec179[0]);
			}
			if (iSlow8) {
				fRec181[0] = (fSlow226 * (fTempPerm152 * ftbl0[(((int((65536.0f * (fRec160[0] + ((fRec11[0] * fRec181[1]) + (fSlow35 * ((fSlow48 * fTempPerm160) + (fSlow67 * (fTempPerm150 * ftbl0[(((int((65536.0f * (fRec164[0] + fTempPerm147))) % 65536) + 65536) % 65536)])))))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow9) {
				fRec182[0] = (fSlow226 * (fTempPerm152 * ftbl0[(((int((65536.0f * (fRec160[0] + ((fRec11[0] * fRec182[1]) + (fSlow35 * (fTempPerm158 + (fSlow67 * (fTempPerm150 * ftbl0[(((int((65536.0f * (fRec164[0] + (fSlow103 * fTempPerm157)))) % 65536) + 65536) % 65536)])))))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow10) {
				fRec183[0] = (fSlow226 * (fTempPerm152 * ftbl0[(((int((65536.0f * (fRec160[0] + ((fRec11[0] * fRec183[1]) + (fSlow68 * (fTempPerm150 * ftbl0[(((int((65536.0f * (fRec164[0] + (fSlow35 * fTempPerm159)))) % 65536) + 65536) % 65536)])))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow11) {
				fRec184[0] = (fSlow226 * (fTempPerm152 * ftbl0[(((int((65536.0f * (fRec160[0] + ((fRec11[0] * fRec184[1]) + (fSlow68 * (fTempPerm150 * ftbl0[(((int((65536.0f * (fRec164[0] + fTempPerm161))) % 65536) + 65536) % 65536)])))))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow4 || iSlow12) {
				fRec185[0] = (fSlow226 * (fTempPerm152 * ftbl0[(((int((65536.0f * (fRec160[0] + (fRec11[0] * fRec185[1])))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow12) {
				fTempPerm163 = (fRec179[0] + fRec185[0]);
			}
			if (iSlow2) {
				fRec186[0] = (fSlow226 * (fTempPerm152 * ftbl0[(((int((65536.0f * (fRec160[0] + (fTempPerm147 + (fRec11[0] * fRec186[1]))))) % 65536) + 65536) % 65536)]));
				fRec187[0] = (fSlow219 * (fTempPerm142 * ftbl0[(((int((65536.0f * (fRec164[0] + (fTempPerm147 + (fRec22[0] * fRec187[1]))))) % 65536) + 65536) % 65536)]));
				fTempPerm164 = (fRec187[0] + (fRec167[0] + fRec186[0]));
			}
			if (iSlow4) {
				fRec188[0] = (fSlow219 * (fTempPerm142 * ftbl0[(((int((65536.0f * (fRec164[0] + (fRec22[0] * fRec188[1])))) % 65536) + 65536) % 65536)]));
				fTempPerm165 = (fRec188[0] + (fRec155[0] + (fRec185[0] + fRec165[0])));
			}
			if (iSlow4 || iSlow12) {
				fRec189[0] = (fSlow201 * (fTempPerm125 * ftbl0[(((int((65536.0f * (fRec130[0] + (fRec11[0] * fRec189[1])))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow12) {
				fTempPerm166 = (fRec149[0] + fRec189[0]);
			}
			if (iSlow2) {
				fRec190[0] = (fSlow201 * (fTempPerm125 * ftbl0[(((int((65536.0f * (fRec130[0] + (fTempPerm120 + (fRec11[0] * fRec190[1]))))) % 65536) + 65536) % 65536)]));
				fRec191[0] = (fSlow194 * (fTempPerm115 * ftbl0[(((int((65536.0f * (fRec134[0] + (fTempPerm120 + (fRec22[0] * fRec191[1]))))) % 65536) + 65536) % 65536)]));
				fTempPerm167 = (fRec191[0] + (fRec137[0] + fRec190[0]));
			}
			if (iSlow4) {
				fRec192[0] = (fSlow194 * (fTempPerm115 * ftbl0[(((int((65536.0f * (fRec134[0] + (fRec22[0] * fRec192[1])))) % 65536) + 65536) % 65536)]));
				fTempPerm168 = (fRec192[0] + (fRec125[0] + (fRec189[0] + fRec135[0])));
			}
			if (iSlow4 || iSlow12) {
				fRec193[0] = (fSlow176 * (fTempPerm98 * ftbl0[(((int((65536.0f * (fRec100[0] + (fRec11[0] * fRec193[1])))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow12) {
				fTempPerm169 = (fRec119[0] + fRec193[0]);
			}
			if (iSlow2) {
				fRec194[0] = (fSlow176 * (fTempPerm98 * ftbl0[(((int((65536.0f * (fRec100[0] + (fTempPerm93 + (fRec11[0] * fRec194[1]))))) % 65536) + 65536) % 65536)]));
				fRec195[0] = (fSlow169 * (fTempPerm88 * ftbl0[(((int((65536.0f * (fRec104[0] + (fTempPerm93 + (fRec22[0] * fRec195[1]))))) % 65536) + 65536) % 65536)]));
				fTempPerm170 = (fRec195[0] + (fRec107[0] + fRec194[0]));
			}
			if (iSlow4) {
				fRec196[0] = (fSlow169 * (fTempPerm88 * ftbl0[(((int((65536.0f * (fRec104[0] + (fRec22[0] * fRec196[1])))) % 65536) + 65536) % 65536)]));
				fTempPerm171 = (fRec196[0] + (fRec95[0] + (fRec193[0] + fRec105[0])));
			}
			if (iSlow4 || iSlow12) {
				fRec197[0] = (fSlow151 * (fTempPerm71 * ftbl0[(((int((65536.0f * (fRec70[0] + (fRec11[0] * fRec197[1])))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow12) {
				fTempPerm172 = (fRec89[0] + fRec197[0]);
			}
			if (iSlow2) {
				fRec198[0] = (fSlow151 * (fTempPerm71 * ftbl0[(((int((65536.0f * (fRec70[0] + (fTempPerm66 + (fRec11[0] * fRec198[1]))))) % 65536) + 65536) % 65536)]));
				fRec199[0] = (fSlow144 * (fTempPerm61 * ftbl0[(((int((65536.0f * (fRec74[0] + (fTempPerm66 + (fRec22[0] * fRec199[1]))))) % 65536) + 65536) % 65536)]));
				fTempPerm173 = (fRec199[0] + (fRec77[0] + fRec198[0]));
			}
			if (iSlow4) {
				fRec200[0] = (fSlow144 * (fTempPerm61 * ftbl0[(((int((65536.0f * (fRec74[0] + (fRec22[0] * fRec200[1])))) % 65536) + 65536) % 65536)]));
				fTempPerm174 = (fRec200[0] + (fRec65[0] + (fRec197[0] + fRec75[0])));
			}
			if (iSlow4 || iSlow12) {
				fRec201[0] = (fSlow126 * (fTempPerm44 * ftbl0[(((int((65536.0f * (fRec40[0] + (fRec11[0] * fRec201[1])))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow12) {
				fTempPerm175 = (fRec59[0] + fRec201[0]);
			}
			if (iSlow2) {
				fRec202[0] = (fSlow126 * (fTempPerm44 * ftbl0[(((int((65536.0f * (fRec40[0] + (fTempPerm39 + (fRec11[0] * fRec202[1]))))) % 65536) + 65536) % 65536)]));
				fRec203[0] = (fSlow119 * (fTempPerm34 * ftbl0[(((int((65536.0f * (fRec44[0] + (fTempPerm39 + (fRec22[0] * fRec203[1]))))) % 65536) + 65536) % 65536)]));
				fTempPerm176 = (fRec203[0] + (fRec47[0] + fRec202[0]));
			}
			if (iSlow4) {
				fRec204[0] = (fSlow119 * (fTempPerm34 * ftbl0[(((int((65536.0f * (fRec44[0] + (fRec22[0] * fRec204[1])))) % 65536) + 65536) % 65536)]));
				fTempPerm177 = (fRec204[0] + (fRec35[0] + (fRec201[0] + fRec45[0])));
			}
			if (iSlow4 || iSlow12) {
				fRec205[0] = (fSlow73 * (fTempPerm13 * ftbl0[(((int((65536.0f * (fRec16[0] + (fRec11[0] * fRec205[1])))) % 65536) + 65536) % 65536)]));
			}
			if (iSlow12) {
				fTempPerm178 = (fRec29[0] + fRec205[0]);
			}
			if (iSlow2) {
				fRec206[0] = (fSlow73 * (fTempPerm13 * ftbl0[(((int((65536.0f * (fRec16[0] + (fTempPerm4 + (fRec11[0] * fRec206[1]))))) % 65536) + 65536) % 65536)]));
				fRec207[0] = (fSlow88 * (fTempPerm17 * ftbl0[(((int((65536.0f * (fRec12[0] + (fTempPerm4 + (fRec22[0] * fRec207[1]))))) % 65536) + 65536) % 65536)]));
				fTempPerm179 = (fRec207[0] + (fRec0[0] + fRec206[0]));
			}
			if (iSlow4) {
				fRec208[0] = (fSlow88 * (fTempPerm17 * ftbl0[(((int((65536.0f * (fRec12[0] + (fRec22[0] * fRec208[1])))) % 65536) + 65536) % 65536)]));
				fTempPerm180 = (fRec208[0] + (fRec17[0] + (fRec205[0] + fRec23[0])));
			}
			output0[i] = (FAUSTFLOAT)(fTempPerm180 + (fTempPerm179 + (fTempPerm178 + (fTempPerm177 + (fTempPerm176 + (fTempPerm175 + (fTempPerm174 + (fTempPerm173 + (fTempPerm172 + (fTempPerm171 + (fTempPerm170 + (fTempPerm169 + (fTempPerm168 + (fTempPerm167 + (fTempPerm166 + (fTempPerm165 + (fTempPerm164 + (fTempPerm163 + (fRec184[0] + (fRec183[0] + (fRec182[0] + (fRec181[0] + (fTempPerm162 + (fRec175[0] + (fTempPerm153 + (fTempPerm143 + (fRec154[0] + (fRec153[0] + (fRec152[0] + (fRec151[0] + (fTempPerm135 + (fRec145[0] + (fTempPerm126 + (fTempPerm116 + (fRec124[0] + (fRec123[0] + (fRec122[0] + (fRec121[0] + (fTempPerm108 + (fRec115[0] + (fTempPerm99 + (fTempPerm89 + (fRec94[0] + (fRec93[0] + (fRec92[0] + (fRec91[0] + (fTempPerm81 + (fRec85[0] + (fTempPerm72 + (fTempPerm62 + (fRec64[0] + (fRec63[0] + (fRec62[0] + (fRec61[0] + (fTempPerm54 + (fRec55[0] + (fTempPerm45 + (fTempPerm35 + (fRec34[0] + (fRec33[0] + (fRec32[0] + (fRec31[0] + (fTempPerm27 + (fRec25[0] + (fTempPerm18 + fTempPerm14)))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))));
			// post processing
			if (iSlow4) {
				fRec208[1] = fRec208[0];
			}
			if (iSlow2) {
				fRec207[1] = fRec207[0];
				fRec206[1] = fRec206[0];
			}
			if (iSlow4 || iSlow12) {
				fRec205[1] = fRec205[0];
			}
			if (iSlow4) {
				fRec204[1] = fRec204[0];
			}
			if (iSlow2) {
				fRec203[1] = fRec203[0];
				fRec202[1] = fRec202[0];
			}
			if (iSlow4 || iSlow12) {
				fRec201[1] = fRec201[0];
			}
			if (iSlow4) {
				fRec200[1] = fRec200[0];
			}
			if (iSlow2) {
				fRec199[1] = fRec199[0];
				fRec198[1] = fRec198[0];
			}
			if (iSlow4 || iSlow12) {
				fRec197[1] = fRec197[0];
			}
			if (iSlow4) {
				fRec196[1] = fRec196[0];
			}
			if (iSlow2) {
				fRec195[1] = fRec195[0];
				fRec194[1] = fRec194[0];
			}
			if (iSlow4 || iSlow12) {
				fRec193[1] = fRec193[0];
			}
			if (iSlow4) {
				fRec192[1] = fRec192[0];
			}
			if (iSlow2) {
				fRec191[1] = fRec191[0];
				fRec190[1] = fRec190[0];
			}
			if (iSlow4 || iSlow12) {
				fRec189[1] = fRec189[0];
			}
			if (iSlow4) {
				fRec188[1] = fRec188[0];
			}
			if (iSlow2) {
				fRec187[1] = fRec187[0];
				fRec186[1] = fRec186[0];
			}
			if (iSlow4 || iSlow12) {
				fRec185[1] = fRec185[0];
			}
			if (iSlow11) {
				fRec184[1] = fRec184[0];
			}
			if (iSlow10) {
				fRec183[1] = fRec183[0];
			}
			if (iSlow9) {
				fRec182[1] = fRec182[0];
			}
			if (iSlow8) {
				fRec181[1] = fRec181[0];
			}
			if (iSlow7) {
				fRec180[1] = fRec180[0];
			}
			if (iSlow12 || iSlow7) {
				fRec179[1] = fRec179[0];
			}
			if (iSlow6) {
				fRec175[1] = fRec175[0];
			}
			if (iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6) {
				fRec178[1] = fRec178[0];
				fRec176[1] = fRec176[0];
				fRec177[1] = fRec177[0];
			}
			if (iSlow1) {
				fRec171[1] = fRec171[0];
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow6 || iSlow1) {
				fRec174[1] = fRec174[0];
				fRec172[1] = fRec172[0];
				fRec173[1] = fRec173[0];
			}
			if (iSlow2 || iSlow1) {
				fRec167[1] = fRec167[0];
			}
			if (iSlow2 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow1) {
				fRec170[1] = fRec170[0];
				fRec168[1] = fRec168[0];
				fRec169[1] = fRec169[0];
			}
			if (iSlow4 || iSlow3) {
				fRec165[1] = fRec165[0];
			}
			if (iSlow4 || iSlow2 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow1 || iSlow3) {
				fRec166[1] = fRec166[0];
			}
			if (iSlow3) {
				fRec159[1] = fRec159[0];
			}
			if (iSlow4 || iSlow2 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow1 || iSlow3) {
				fRec164[1] = fRec164[0];
			}
			if (iSlow3) {
				fRec163[1] = fRec163[0];
				fRec161[1] = fRec161[0];
				fRec162[1] = fRec162[0];
			}
			if (iSlow4 || iSlow2 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow1 || iSlow3) {
				fRec160[1] = fRec160[0];
			}
			if (iSlow4 || iSlow3) {
				fRec155[1] = fRec155[0];
			}
			if (iSlow4 || iSlow2 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow1 || iSlow3) {
				fRec157[1] = fRec157[0];
				iRec158[1] = iRec158[0];
				fRec156[1] = fRec156[0];
			}
			if (iSlow11) {
				fRec154[1] = fRec154[0];
			}
			if (iSlow10) {
				fRec153[1] = fRec153[0];
			}
			if (iSlow9) {
				fRec152[1] = fRec152[0];
			}
			if (iSlow8) {
				fRec151[1] = fRec151[0];
			}
			if (iSlow7) {
				fRec150[1] = fRec150[0];
			}
			if (iSlow12 || iSlow7) {
				fRec149[1] = fRec149[0];
			}
			if (iSlow6) {
				fRec145[1] = fRec145[0];
			}
			if (iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6) {
				fRec148[1] = fRec148[0];
				fRec146[1] = fRec146[0];
				fRec147[1] = fRec147[0];
			}
			if (iSlow1) {
				fRec141[1] = fRec141[0];
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow6 || iSlow1) {
				fRec144[1] = fRec144[0];
				fRec142[1] = fRec142[0];
				fRec143[1] = fRec143[0];
			}
			if (iSlow2 || iSlow1) {
				fRec137[1] = fRec137[0];
			}
			if (iSlow2 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow1) {
				fRec140[1] = fRec140[0];
				fRec138[1] = fRec138[0];
				fRec139[1] = fRec139[0];
			}
			if (iSlow4 || iSlow3) {
				fRec135[1] = fRec135[0];
			}
			if (iSlow4 || iSlow2 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow1 || iSlow3) {
				fRec136[1] = fRec136[0];
			}
			if (iSlow3) {
				fRec129[1] = fRec129[0];
			}
			if (iSlow4 || iSlow2 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow1 || iSlow3) {
				fRec134[1] = fRec134[0];
			}
			if (iSlow3) {
				fRec133[1] = fRec133[0];
				fRec131[1] = fRec131[0];
				fRec132[1] = fRec132[0];
			}
			if (iSlow4 || iSlow2 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow1 || iSlow3) {
				fRec130[1] = fRec130[0];
			}
			if (iSlow4 || iSlow3) {
				fRec125[1] = fRec125[0];
			}
			if (iSlow4 || iSlow2 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow1 || iSlow3) {
				fRec127[1] = fRec127[0];
				iRec128[1] = iRec128[0];
				fRec126[1] = fRec126[0];
			}
			if (iSlow11) {
				fRec124[1] = fRec124[0];
			}
			if (iSlow10) {
				fRec123[1] = fRec123[0];
			}
			if (iSlow9) {
				fRec122[1] = fRec122[0];
			}
			if (iSlow8) {
				fRec121[1] = fRec121[0];
			}
			if (iSlow7) {
				fRec120[1] = fRec120[0];
			}
			if (iSlow12 || iSlow7) {
				fRec119[1] = fRec119[0];
			}
			if (iSlow6) {
				fRec115[1] = fRec115[0];
			}
			if (iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6) {
				fRec118[1] = fRec118[0];
				fRec116[1] = fRec116[0];
				fRec117[1] = fRec117[0];
			}
			if (iSlow1) {
				fRec111[1] = fRec111[0];
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow6 || iSlow1) {
				fRec114[1] = fRec114[0];
				fRec112[1] = fRec112[0];
				fRec113[1] = fRec113[0];
			}
			if (iSlow2 || iSlow1) {
				fRec107[1] = fRec107[0];
			}
			if (iSlow2 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow1) {
				fRec110[1] = fRec110[0];
				fRec108[1] = fRec108[0];
				fRec109[1] = fRec109[0];
			}
			if (iSlow4 || iSlow3) {
				fRec105[1] = fRec105[0];
			}
			if (iSlow4 || iSlow2 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow1 || iSlow3) {
				fRec106[1] = fRec106[0];
			}
			if (iSlow3) {
				fRec99[1] = fRec99[0];
			}
			if (iSlow4 || iSlow2 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow1 || iSlow3) {
				fRec104[1] = fRec104[0];
			}
			if (iSlow3) {
				fRec103[1] = fRec103[0];
				fRec101[1] = fRec101[0];
				fRec102[1] = fRec102[0];
			}
			if (iSlow4 || iSlow2 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow1 || iSlow3) {
				fRec100[1] = fRec100[0];
			}
			if (iSlow4 || iSlow3) {
				fRec95[1] = fRec95[0];
			}
			if (iSlow4 || iSlow2 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow1 || iSlow3) {
				fRec97[1] = fRec97[0];
				iRec98[1] = iRec98[0];
				fRec96[1] = fRec96[0];
			}
			if (iSlow11) {
				fRec94[1] = fRec94[0];
			}
			if (iSlow10) {
				fRec93[1] = fRec93[0];
			}
			if (iSlow9) {
				fRec92[1] = fRec92[0];
			}
			if (iSlow8) {
				fRec91[1] = fRec91[0];
			}
			if (iSlow7) {
				fRec90[1] = fRec90[0];
			}
			if (iSlow12 || iSlow7) {
				fRec89[1] = fRec89[0];
			}
			if (iSlow6) {
				fRec85[1] = fRec85[0];
			}
			if (iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6) {
				fRec88[1] = fRec88[0];
				fRec86[1] = fRec86[0];
				fRec87[1] = fRec87[0];
			}
			if (iSlow1) {
				fRec81[1] = fRec81[0];
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow6 || iSlow1) {
				fRec84[1] = fRec84[0];
				fRec82[1] = fRec82[0];
				fRec83[1] = fRec83[0];
			}
			if (iSlow2 || iSlow1) {
				fRec77[1] = fRec77[0];
			}
			if (iSlow2 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow1) {
				fRec80[1] = fRec80[0];
				fRec78[1] = fRec78[0];
				fRec79[1] = fRec79[0];
			}
			if (iSlow4 || iSlow3) {
				fRec75[1] = fRec75[0];
			}
			if (iSlow4 || iSlow2 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow1 || iSlow3) {
				fRec76[1] = fRec76[0];
			}
			if (iSlow3) {
				fRec69[1] = fRec69[0];
			}
			if (iSlow4 || iSlow2 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow1 || iSlow3) {
				fRec74[1] = fRec74[0];
			}
			if (iSlow3) {
				fRec73[1] = fRec73[0];
				fRec71[1] = fRec71[0];
				fRec72[1] = fRec72[0];
			}
			if (iSlow4 || iSlow2 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow1 || iSlow3) {
				fRec70[1] = fRec70[0];
			}
			if (iSlow4 || iSlow3) {
				fRec65[1] = fRec65[0];
			}
			if (iSlow4 || iSlow2 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow1 || iSlow3) {
				fRec67[1] = fRec67[0];
				iRec68[1] = iRec68[0];
				fRec66[1] = fRec66[0];
			}
			if (iSlow11) {
				fRec64[1] = fRec64[0];
			}
			if (iSlow10) {
				fRec63[1] = fRec63[0];
			}
			if (iSlow9) {
				fRec62[1] = fRec62[0];
			}
			if (iSlow8) {
				fRec61[1] = fRec61[0];
			}
			if (iSlow7) {
				fRec60[1] = fRec60[0];
			}
			if (iSlow12 || iSlow7) {
				fRec59[1] = fRec59[0];
			}
			if (iSlow6) {
				fRec55[1] = fRec55[0];
			}
			if (iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6) {
				fRec58[1] = fRec58[0];
				fRec56[1] = fRec56[0];
				fRec57[1] = fRec57[0];
			}
			if (iSlow1) {
				fRec51[1] = fRec51[0];
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow6 || iSlow1) {
				fRec54[1] = fRec54[0];
				fRec52[1] = fRec52[0];
				fRec53[1] = fRec53[0];
			}
			if (iSlow2 || iSlow1) {
				fRec47[1] = fRec47[0];
			}
			if (iSlow2 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow1) {
				fRec50[1] = fRec50[0];
				fRec48[1] = fRec48[0];
				fRec49[1] = fRec49[0];
			}
			if (iSlow4 || iSlow3) {
				fRec45[1] = fRec45[0];
			}
			if (iSlow4 || iSlow2 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow1 || iSlow3) {
				fRec46[1] = fRec46[0];
			}
			if (iSlow3) {
				fRec39[1] = fRec39[0];
			}
			if (iSlow4 || iSlow2 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow1 || iSlow3) {
				fRec44[1] = fRec44[0];
			}
			if (iSlow3) {
				fRec43[1] = fRec43[0];
				fRec41[1] = fRec41[0];
				fRec42[1] = fRec42[0];
			}
			if (iSlow4 || iSlow2 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow1 || iSlow3) {
				fRec40[1] = fRec40[0];
			}
			if (iSlow4 || iSlow3) {
				fRec35[1] = fRec35[0];
			}
			if (iSlow4 || iSlow2 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow1 || iSlow3) {
				fRec37[1] = fRec37[0];
				iRec38[1] = iRec38[0];
				fRec36[1] = fRec36[0];
			}
			if (iSlow11) {
				fRec34[1] = fRec34[0];
			}
			if (iSlow10) {
				fRec33[1] = fRec33[0];
			}
			if (iSlow9) {
				fRec32[1] = fRec32[0];
			}
			if (iSlow8) {
				fRec31[1] = fRec31[0];
			}
			if (iSlow7) {
				fRec30[1] = fRec30[0];
			}
			if (iSlow12 || iSlow7) {
				fRec29[1] = fRec29[0];
			}
			if (iSlow6) {
				fRec25[1] = fRec25[0];
			}
			if (iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6) {
				fRec28[1] = fRec28[0];
				fRec26[1] = fRec26[0];
				fRec27[1] = fRec27[0];
			}
			if (iSlow4 || iSlow3) {
				fRec23[1] = fRec23[0];
				fRec24[1] = fRec24[0];
			}
			if (iSlow3) {
				fRec18[1] = fRec18[0];
			}
			if (iSlow4 || iSlow2 || iSlow12 || iSlow7 || iSlow3) {
				fRec22[1] = fRec22[0];
			}
			if (iSlow3) {
				fRec21[1] = fRec21[0];
				fRec19[1] = fRec19[0];
				fRec20[1] = fRec20[0];
			}
			if (iSlow4 || iSlow3) {
				fRec17[1] = fRec17[0];
			}
			if (iSlow1) {
				fRec10[1] = fRec10[0];
			}
			if (iSlow4 || iSlow2 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow1 || iSlow3) {
				fRec16[1] = fRec16[0];
			}
			if (iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow6 || iSlow1) {
				fRec15[1] = fRec15[0];
				fRec13[1] = fRec13[0];
				fRec14[1] = fRec14[0];
			}
			if (iSlow4 || iSlow2 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow1 || iSlow3) {
				fRec12[1] = fRec12[0];
			}
			if (iSlow4 || iSlow2 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow1) {
				fRec11[1] = fRec11[0];
			}
			if (iSlow2 || iSlow1) {
				fRec0[1] = fRec0[0];
			}
			if (iSlow4 || iSlow2 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow1 || iSlow3) {
				fRec8[1] = fRec8[0];
				iRec9[1] = iRec9[0];
				fRec7[1] = fRec7[0];
			}
			if (iSlow2 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow1) {
				fRec6[1] = fRec6[0];
				fRec4[1] = fRec4[0];
				fRec5[1] = fRec5[0];
			}
			if (iSlow4 || iSlow2 || iSlow12 || iSlow11 || iSlow10 || iSlow9 || iSlow8 || iSlow7 || iSlow6 || iSlow1 || iSlow3) {
				fRec3[1] = fRec3[0];
			}
			if (iSlow4 || iSlow2 || iSlow1 || iSlow3) {
				fRec2[1] = fRec2[0];
			}
		}
	}
};


float 	faust_ottofm::ftbl0[65536];
