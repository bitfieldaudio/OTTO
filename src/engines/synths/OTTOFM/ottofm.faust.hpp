//----------------------------------------------------------
// name: "ottofm"
//
// Code generated with Faust 2.13.11 (https://faust.grame.fr)
//----------------------------------------------------------

/* link with  */
#include <math.h>
#ifndef FAUSTPOWER
#define FAUSTPOWER
#include <cmath>
template <int N> inline int faustpower(int x)              { return faustpower<N/2>(x) * faustpower<N-N/2>(x); } 
template <> 	 inline int faustpower<0>(int x)            { return 1; }
template <> 	 inline int faustpower<1>(int x)            { return x; }
template <> 	 inline int faustpower<2>(int x)            { return x*x; }
template <int N> inline float faustpower(float x)            { return faustpower<N/2>(x) * faustpower<N-N/2>(x); } 
template <> 	 inline float faustpower<0>(float x)          { return 1; }
template <> 	 inline float faustpower<1>(float x)          { return x; }
template <> 	 inline float faustpower<2>(float x)          { return x*x; }
#endif
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
		int 	iRec3[2];
		float 	fTempPerm4;
	  public:
		int getNumInputs() { return 0; }
		int getNumOutputs() { return 1; }
		void init(int samplingFreq) {
			fSamplingFreq = samplingFreq;
			fTempPerm4 = 0;
			for (int i=0; i<2; i++) iRec3[i] = 0;
		}
		void fill (int count, float output[]) {
			for (int i=0; i<count; i++) {
				iRec3[0] = (iRec3[1] + 1);
				fTempPerm4 = sinf((9.5873799242852573e-05f * float((iRec3[0] + -1))));
				output[i] = fTempPerm4;
				// post processing
				iRec3[1] = iRec3[0];
			}
		}
	};


	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT 	fslider2;
	float 	fConst0;
	FAUSTFLOAT 	fbutton0;
	int 	iRec1[2];
	int 	iTempPerm0;
	float 	fConst1;
	float 	fTempPerm1;
	FAUSTFLOAT 	fslider3;
	float 	fRec0[2];
	float 	fTempPerm2;
	FAUSTFLOAT 	fbargraph0;
	float 	fTempPerm3;
	FAUSTFLOAT 	fslider4;
	static float 	ftbl0[65536];
	FAUSTFLOAT 	fbutton1;
	int 	iRec6[2];
	int 	iTempPerm5;
	float 	fTempPerm6;
	float 	fRec5[2];
	float 	fTempPerm7;
	FAUSTFLOAT 	fbargraph1;
	float 	fTempPerm8;
	FAUSTFLOAT 	fbutton2;
	int 	iRec8[2];
	int 	iTempPerm9;
	float 	fTempPerm10;
	float 	fRec7[2];
	float 	fTempPerm11;
	FAUSTFLOAT 	fbargraph2;
	float 	fTempPerm12;
	FAUSTFLOAT 	fbutton3;
	int 	iRec10[2];
	int 	iTempPerm13;
	float 	fTempPerm14;
	float 	fRec9[2];
	float 	fTempPerm15;
	FAUSTFLOAT 	fbargraph3;
	float 	fTempPerm16;
	FAUSTFLOAT 	fbutton4;
	int 	iRec12[2];
	int 	iTempPerm17;
	float 	fTempPerm18;
	float 	fRec11[2];
	float 	fTempPerm19;
	FAUSTFLOAT 	fbargraph4;
	float 	fTempPerm20;
	FAUSTFLOAT 	fbutton5;
	int 	iRec14[2];
	int 	iTempPerm21;
	float 	fTempPerm22;
	float 	fRec13[2];
	float 	fTempPerm23;
	FAUSTFLOAT 	fbargraph5;
	float 	fTempPerm24;
	FAUSTFLOAT 	fslider5;
	float 	fRec4[2];
	FAUSTFLOAT 	fslider6;
	FAUSTFLOAT 	fslider7;
	FAUSTFLOAT 	fslider8;
	float 	fConst2;
	float 	fRec15[2];
	FAUSTFLOAT 	fslider9;
	FAUSTFLOAT 	fslider10;
	float 	fRec2[2];
	FAUSTFLOAT 	fslider11;
	float 	fRec17[2];
	FAUSTFLOAT 	fslider12;
	FAUSTFLOAT 	fslider13;
	float 	fRec18[2];
	FAUSTFLOAT 	fslider14;
	float 	fRec16[2];
	FAUSTFLOAT 	fslider15;
	float 	fRec20[2];
	FAUSTFLOAT 	fslider16;
	FAUSTFLOAT 	fslider17;
	float 	fRec21[2];
	FAUSTFLOAT 	fslider18;
	float 	fRec19[2];
	FAUSTFLOAT 	fslider19;
	float 	fRec23[2];
	FAUSTFLOAT 	fslider20;
	FAUSTFLOAT 	fslider21;
	float 	fRec24[2];
	FAUSTFLOAT 	fslider22;
	float 	fRec22[2];
	float 	fTempPerm25;
	FAUSTFLOAT 	fslider23;
	FAUSTFLOAT 	fslider24;
	float 	fConst3;
	FAUSTFLOAT 	fslider25;
	float 	fRec27[2];
	float 	fConst4;
	int 	iTempPerm26;
	float 	fRec26[2];
	float 	fRec28[2];
	float 	fTempPerm27;
	FAUSTFLOAT 	fbargraph6;
	float 	fTempPerm28;
	FAUSTFLOAT 	fslider26;
	float 	fTempPerm29;
	float 	fRec25[2];
	FAUSTFLOAT 	fslider27;
	FAUSTFLOAT 	fslider28;
	FAUSTFLOAT 	fslider29;
	float 	fRec31[2];
	int 	iTempPerm30;
	float 	fRec30[2];
	float 	fRec32[2];
	float 	fTempPerm31;
	FAUSTFLOAT 	fbargraph7;
	float 	fTempPerm32;
	float 	fTempPerm33;
	float 	fRec29[2];
	float 	fTempPerm34;
	FAUSTFLOAT 	fslider30;
	FAUSTFLOAT 	fslider31;
	FAUSTFLOAT 	fslider32;
	float 	fRec35[2];
	int 	iTempPerm35;
	float 	fRec34[2];
	float 	fRec36[2];
	float 	fTempPerm36;
	FAUSTFLOAT 	fbargraph8;
	float 	fRec33[2];
	float 	fTempPerm37;
	FAUSTFLOAT 	fslider33;
	FAUSTFLOAT 	fslider34;
	FAUSTFLOAT 	fslider35;
	float 	fRec39[2];
	int 	iTempPerm38;
	float 	fRec38[2];
	float 	fRec40[2];
	float 	fTempPerm39;
	FAUSTFLOAT 	fbargraph9;
	float 	fTempPerm40;
	float 	fTempPerm41;
	float 	fTempPerm42;
	float 	fTempPerm43;
	float 	fRec37[2];
	float 	fTempPerm44;
	float 	fTempPerm45;
	float 	fRec41[2];
	float 	fRec42[2];
	float 	fTempPerm46;
	float 	fRec43[2];
	float 	fRec44[2];
	float 	fRec45[2];
	float 	fRec46[2];
	float 	fTempPerm47;
	float 	fRec47[2];
	float 	fRec48[2];
	float 	fTempPerm48;
	float 	fTempPerm49;
	FAUSTFLOAT 	fslider36;
	float 	fRec50[2];
	FAUSTFLOAT 	fslider37;
	float 	fRec49[2];
	float 	fRec52[2];
	float 	fRec51[2];
	float 	fRec54[2];
	float 	fRec53[2];
	float 	fRec56[2];
	float 	fRec55[2];
	float 	fTempPerm50;
	float 	fRec59[2];
	int 	iTempPerm51;
	float 	fRec58[2];
	float 	fRec60[2];
	float 	fTempPerm52;
	FAUSTFLOAT 	fbargraph10;
	float 	fTempPerm53;
	float 	fTempPerm54;
	float 	fRec57[2];
	float 	fRec63[2];
	int 	iTempPerm55;
	float 	fRec62[2];
	float 	fRec64[2];
	float 	fTempPerm56;
	FAUSTFLOAT 	fbargraph11;
	float 	fTempPerm57;
	float 	fTempPerm58;
	float 	fRec61[2];
	float 	fTempPerm59;
	float 	fRec67[2];
	int 	iTempPerm60;
	float 	fRec66[2];
	float 	fRec68[2];
	float 	fTempPerm61;
	FAUSTFLOAT 	fbargraph12;
	float 	fRec65[2];
	float 	fTempPerm62;
	float 	fRec71[2];
	int 	iTempPerm63;
	float 	fRec70[2];
	float 	fRec72[2];
	float 	fTempPerm64;
	FAUSTFLOAT 	fbargraph13;
	float 	fTempPerm65;
	float 	fTempPerm66;
	float 	fTempPerm67;
	float 	fTempPerm68;
	float 	fRec69[2];
	float 	fTempPerm69;
	float 	fTempPerm70;
	float 	fRec73[2];
	float 	fRec74[2];
	float 	fTempPerm71;
	float 	fRec75[2];
	float 	fRec76[2];
	float 	fRec77[2];
	float 	fRec78[2];
	float 	fTempPerm72;
	float 	fRec79[2];
	float 	fRec80[2];
	float 	fTempPerm73;
	float 	fTempPerm74;
	FAUSTFLOAT 	fslider38;
	float 	fRec82[2];
	FAUSTFLOAT 	fslider39;
	float 	fRec81[2];
	float 	fRec84[2];
	float 	fRec83[2];
	float 	fRec86[2];
	float 	fRec85[2];
	float 	fRec88[2];
	float 	fRec87[2];
	float 	fTempPerm75;
	float 	fRec91[2];
	int 	iTempPerm76;
	float 	fRec90[2];
	float 	fRec92[2];
	float 	fTempPerm77;
	FAUSTFLOAT 	fbargraph14;
	float 	fTempPerm78;
	float 	fTempPerm79;
	float 	fRec89[2];
	float 	fRec95[2];
	int 	iTempPerm80;
	float 	fRec94[2];
	float 	fRec96[2];
	float 	fTempPerm81;
	FAUSTFLOAT 	fbargraph15;
	float 	fTempPerm82;
	float 	fTempPerm83;
	float 	fRec93[2];
	float 	fTempPerm84;
	float 	fRec99[2];
	int 	iTempPerm85;
	float 	fRec98[2];
	float 	fRec100[2];
	float 	fTempPerm86;
	FAUSTFLOAT 	fbargraph16;
	float 	fRec97[2];
	float 	fTempPerm87;
	float 	fRec103[2];
	int 	iTempPerm88;
	float 	fRec102[2];
	float 	fRec104[2];
	float 	fTempPerm89;
	FAUSTFLOAT 	fbargraph17;
	float 	fTempPerm90;
	float 	fTempPerm91;
	float 	fTempPerm92;
	float 	fTempPerm93;
	float 	fRec101[2];
	float 	fTempPerm94;
	float 	fTempPerm95;
	float 	fRec105[2];
	float 	fRec106[2];
	float 	fTempPerm96;
	float 	fRec107[2];
	float 	fRec108[2];
	float 	fRec109[2];
	float 	fRec110[2];
	float 	fTempPerm97;
	float 	fRec111[2];
	float 	fRec112[2];
	float 	fTempPerm98;
	float 	fTempPerm99;
	FAUSTFLOAT 	fslider40;
	float 	fRec114[2];
	FAUSTFLOAT 	fslider41;
	float 	fRec113[2];
	float 	fRec116[2];
	float 	fRec115[2];
	float 	fRec118[2];
	float 	fRec117[2];
	float 	fRec120[2];
	float 	fRec119[2];
	float 	fTempPerm100;
	float 	fRec123[2];
	int 	iTempPerm101;
	float 	fRec122[2];
	float 	fRec124[2];
	float 	fTempPerm102;
	FAUSTFLOAT 	fbargraph18;
	float 	fTempPerm103;
	float 	fTempPerm104;
	float 	fRec121[2];
	float 	fRec127[2];
	int 	iTempPerm105;
	float 	fRec126[2];
	float 	fRec128[2];
	float 	fTempPerm106;
	FAUSTFLOAT 	fbargraph19;
	float 	fTempPerm107;
	float 	fTempPerm108;
	float 	fRec125[2];
	float 	fTempPerm109;
	float 	fRec131[2];
	int 	iTempPerm110;
	float 	fRec130[2];
	float 	fRec132[2];
	float 	fTempPerm111;
	FAUSTFLOAT 	fbargraph20;
	float 	fRec129[2];
	float 	fTempPerm112;
	float 	fRec135[2];
	int 	iTempPerm113;
	float 	fRec134[2];
	float 	fRec136[2];
	float 	fTempPerm114;
	FAUSTFLOAT 	fbargraph21;
	float 	fTempPerm115;
	float 	fTempPerm116;
	float 	fTempPerm117;
	float 	fTempPerm118;
	float 	fRec133[2];
	float 	fTempPerm119;
	float 	fTempPerm120;
	float 	fRec137[2];
	float 	fRec138[2];
	float 	fTempPerm121;
	float 	fRec139[2];
	float 	fRec140[2];
	float 	fRec141[2];
	float 	fRec142[2];
	float 	fTempPerm122;
	float 	fRec143[2];
	float 	fRec144[2];
	float 	fTempPerm123;
	float 	fTempPerm124;
	FAUSTFLOAT 	fslider42;
	float 	fRec146[2];
	FAUSTFLOAT 	fslider43;
	float 	fRec145[2];
	float 	fRec148[2];
	float 	fRec147[2];
	float 	fRec150[2];
	float 	fRec149[2];
	float 	fRec152[2];
	float 	fRec151[2];
	float 	fTempPerm125;
	float 	fRec155[2];
	int 	iTempPerm126;
	float 	fRec154[2];
	float 	fRec156[2];
	float 	fTempPerm127;
	FAUSTFLOAT 	fbargraph22;
	float 	fTempPerm128;
	float 	fTempPerm129;
	float 	fRec153[2];
	float 	fRec159[2];
	int 	iTempPerm130;
	float 	fRec158[2];
	float 	fRec160[2];
	float 	fTempPerm131;
	FAUSTFLOAT 	fbargraph23;
	float 	fTempPerm132;
	float 	fTempPerm133;
	float 	fRec157[2];
	float 	fTempPerm134;
	float 	fRec163[2];
	int 	iTempPerm135;
	float 	fRec162[2];
	float 	fRec164[2];
	float 	fTempPerm136;
	FAUSTFLOAT 	fbargraph24;
	float 	fRec161[2];
	float 	fTempPerm137;
	float 	fRec167[2];
	int 	iTempPerm138;
	float 	fRec166[2];
	float 	fRec168[2];
	float 	fTempPerm139;
	FAUSTFLOAT 	fbargraph25;
	float 	fTempPerm140;
	float 	fTempPerm141;
	float 	fTempPerm142;
	float 	fTempPerm143;
	float 	fRec165[2];
	float 	fTempPerm144;
	float 	fTempPerm145;
	float 	fRec169[2];
	float 	fRec170[2];
	float 	fTempPerm146;
	float 	fRec171[2];
	float 	fRec172[2];
	float 	fRec173[2];
	float 	fRec174[2];
	float 	fTempPerm147;
	float 	fRec175[2];
	float 	fRec176[2];
	float 	fTempPerm148;
	float 	fTempPerm149;
	FAUSTFLOAT 	fslider44;
	float 	fRec178[2];
	FAUSTFLOAT 	fslider45;
	float 	fRec177[2];
	float 	fRec180[2];
	float 	fRec179[2];
	float 	fRec182[2];
	float 	fRec181[2];
	float 	fRec184[2];
	float 	fRec183[2];
	float 	fTempPerm150;
	float 	fRec187[2];
	int 	iTempPerm151;
	float 	fRec186[2];
	float 	fRec188[2];
	float 	fTempPerm152;
	FAUSTFLOAT 	fbargraph26;
	float 	fTempPerm153;
	float 	fTempPerm154;
	float 	fRec185[2];
	float 	fRec191[2];
	int 	iTempPerm155;
	float 	fRec190[2];
	float 	fRec192[2];
	float 	fTempPerm156;
	FAUSTFLOAT 	fbargraph27;
	float 	fTempPerm157;
	float 	fTempPerm158;
	float 	fRec189[2];
	float 	fTempPerm159;
	float 	fRec195[2];
	int 	iTempPerm160;
	float 	fRec194[2];
	float 	fRec196[2];
	float 	fTempPerm161;
	FAUSTFLOAT 	fbargraph28;
	float 	fRec193[2];
	float 	fTempPerm162;
	float 	fRec199[2];
	int 	iTempPerm163;
	float 	fRec198[2];
	float 	fRec200[2];
	float 	fTempPerm164;
	FAUSTFLOAT 	fbargraph29;
	float 	fTempPerm165;
	float 	fTempPerm166;
	float 	fTempPerm167;
	float 	fTempPerm168;
	float 	fRec197[2];
	float 	fTempPerm169;
	float 	fTempPerm170;
	float 	fRec201[2];
	float 	fRec202[2];
	float 	fTempPerm171;
	float 	fRec203[2];
	float 	fRec204[2];
	float 	fRec205[2];
	float 	fRec206[2];
	float 	fTempPerm172;
	float 	fRec207[2];
	float 	fRec208[2];
	float 	fTempPerm173;
	float 	fTempPerm174;
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
		iTempPerm0 = 0;
		fConst1 = (6.9100000000000001f / fConst0);
		fTempPerm1 = 0;
		fTempPerm2 = 0;
		fTempPerm3 = 0;
		iTempPerm5 = 0;
		fTempPerm6 = 0;
		fTempPerm7 = 0;
		fTempPerm8 = 0;
		iTempPerm9 = 0;
		fTempPerm10 = 0;
		fTempPerm11 = 0;
		fTempPerm12 = 0;
		iTempPerm13 = 0;
		fTempPerm14 = 0;
		fTempPerm15 = 0;
		fTempPerm16 = 0;
		iTempPerm17 = 0;
		fTempPerm18 = 0;
		fTempPerm19 = 0;
		fTempPerm20 = 0;
		iTempPerm21 = 0;
		fTempPerm22 = 0;
		fTempPerm23 = 0;
		fTempPerm24 = 0;
		fConst2 = (1.0f / fConst0);
		fTempPerm25 = 0;
		fConst3 = (3.0f * fConst0);
		fConst4 = (0.33333333333333331f / fConst0);
		iTempPerm26 = 0;
		fTempPerm27 = 0;
		fTempPerm28 = 0;
		fTempPerm29 = 0;
		iTempPerm30 = 0;
		fTempPerm31 = 0;
		fTempPerm32 = 0;
		fTempPerm33 = 0;
		fTempPerm34 = 0;
		iTempPerm35 = 0;
		fTempPerm36 = 0;
		fTempPerm37 = 0;
		iTempPerm38 = 0;
		fTempPerm39 = 0;
		fTempPerm40 = 0;
		fTempPerm41 = 0;
		fTempPerm42 = 0;
		fTempPerm43 = 0;
		fTempPerm44 = 0;
		fTempPerm45 = 0;
		fTempPerm46 = 0;
		fTempPerm47 = 0;
		fTempPerm48 = 0;
		fTempPerm49 = 0;
		fTempPerm50 = 0;
		iTempPerm51 = 0;
		fTempPerm52 = 0;
		fTempPerm53 = 0;
		fTempPerm54 = 0;
		iTempPerm55 = 0;
		fTempPerm56 = 0;
		fTempPerm57 = 0;
		fTempPerm58 = 0;
		fTempPerm59 = 0;
		iTempPerm60 = 0;
		fTempPerm61 = 0;
		fTempPerm62 = 0;
		iTempPerm63 = 0;
		fTempPerm64 = 0;
		fTempPerm65 = 0;
		fTempPerm66 = 0;
		fTempPerm67 = 0;
		fTempPerm68 = 0;
		fTempPerm69 = 0;
		fTempPerm70 = 0;
		fTempPerm71 = 0;
		fTempPerm72 = 0;
		fTempPerm73 = 0;
		fTempPerm74 = 0;
		fTempPerm75 = 0;
		iTempPerm76 = 0;
		fTempPerm77 = 0;
		fTempPerm78 = 0;
		fTempPerm79 = 0;
		iTempPerm80 = 0;
		fTempPerm81 = 0;
		fTempPerm82 = 0;
		fTempPerm83 = 0;
		fTempPerm84 = 0;
		iTempPerm85 = 0;
		fTempPerm86 = 0;
		fTempPerm87 = 0;
		iTempPerm88 = 0;
		fTempPerm89 = 0;
		fTempPerm90 = 0;
		fTempPerm91 = 0;
		fTempPerm92 = 0;
		fTempPerm93 = 0;
		fTempPerm94 = 0;
		fTempPerm95 = 0;
		fTempPerm96 = 0;
		fTempPerm97 = 0;
		fTempPerm98 = 0;
		fTempPerm99 = 0;
		fTempPerm100 = 0;
		iTempPerm101 = 0;
		fTempPerm102 = 0;
		fTempPerm103 = 0;
		fTempPerm104 = 0;
		iTempPerm105 = 0;
		fTempPerm106 = 0;
		fTempPerm107 = 0;
		fTempPerm108 = 0;
		fTempPerm109 = 0;
		iTempPerm110 = 0;
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
		iTempPerm126 = 0;
		fTempPerm127 = 0;
		fTempPerm128 = 0;
		fTempPerm129 = 0;
		iTempPerm130 = 0;
		fTempPerm131 = 0;
		fTempPerm132 = 0;
		fTempPerm133 = 0;
		fTempPerm134 = 0;
		iTempPerm135 = 0;
		fTempPerm136 = 0;
		fTempPerm137 = 0;
		iTempPerm138 = 0;
		fTempPerm139 = 0;
		fTempPerm140 = 0;
		fTempPerm141 = 0;
		fTempPerm142 = 0;
		fTempPerm143 = 0;
		fTempPerm144 = 0;
		fTempPerm145 = 0;
		fTempPerm146 = 0;
		fTempPerm147 = 0;
		fTempPerm148 = 0;
		fTempPerm149 = 0;
		fTempPerm150 = 0;
		iTempPerm151 = 0;
		fTempPerm152 = 0;
		fTempPerm153 = 0;
		fTempPerm154 = 0;
		iTempPerm155 = 0;
		fTempPerm156 = 0;
		fTempPerm157 = 0;
		fTempPerm158 = 0;
		fTempPerm159 = 0;
		iTempPerm160 = 0;
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
		fTempPerm174 = 0;
	}
	virtual void instanceResetUserInterface() {
		fslider0 = 0.0f;
		fslider1 = 0.0f;
		fslider2 = 0.001f;
		fbutton0 = 0.0;
		fslider3 = 1.0f;
		fslider4 = 0.0f;
		fbutton1 = 0.0;
		fbutton2 = 0.0;
		fbutton3 = 0.0;
		fbutton4 = 0.0;
		fbutton5 = 0.0;
		fslider5 = 0.0f;
		fslider6 = 1.0f;
		fslider7 = 440.0f;
		fslider8 = 0.0f;
		fslider9 = 1.0f;
		fslider10 = 1.0f;
		fslider11 = 0.0f;
		fslider12 = 1.0f;
		fslider13 = 0.0f;
		fslider14 = 1.0f;
		fslider15 = 0.0f;
		fslider16 = 1.0f;
		fslider17 = 0.0f;
		fslider18 = 1.0f;
		fslider19 = 0.0f;
		fslider20 = 1.0f;
		fslider21 = 0.0f;
		fslider22 = 1.0f;
		fslider23 = 0.0f;
		fslider24 = 0.0f;
		fslider25 = 0.0f;
		fslider26 = 1.0f;
		fslider27 = 0.0f;
		fslider28 = 0.0f;
		fslider29 = 0.0f;
		fslider30 = 0.0f;
		fslider31 = 0.0f;
		fslider32 = 0.0f;
		fslider33 = 0.0f;
		fslider34 = 0.0f;
		fslider35 = 0.0f;
		fslider36 = 440.0f;
		fslider37 = 1.0f;
		fslider38 = 440.0f;
		fslider39 = 1.0f;
		fslider40 = 440.0f;
		fslider41 = 1.0f;
		fslider42 = 440.0f;
		fslider43 = 1.0f;
		fslider44 = 440.0f;
		fslider45 = 1.0f;
	}
	virtual void instanceClear() {
		for (int i=0; i<2; i++) iRec1[i] = 0;
		for (int i=0; i<2; i++) fRec0[i] = 0;
		for (int i=0; i<2; i++) iRec6[i] = 0;
		for (int i=0; i<2; i++) fRec5[i] = 0;
		for (int i=0; i<2; i++) iRec8[i] = 0;
		for (int i=0; i<2; i++) fRec7[i] = 0;
		for (int i=0; i<2; i++) iRec10[i] = 0;
		for (int i=0; i<2; i++) fRec9[i] = 0;
		for (int i=0; i<2; i++) iRec12[i] = 0;
		for (int i=0; i<2; i++) fRec11[i] = 0;
		for (int i=0; i<2; i++) iRec14[i] = 0;
		for (int i=0; i<2; i++) fRec13[i] = 0;
		for (int i=0; i<2; i++) fRec4[i] = 0;
		for (int i=0; i<2; i++) fRec15[i] = 0;
		for (int i=0; i<2; i++) fRec2[i] = 0;
		for (int i=0; i<2; i++) fRec17[i] = 0;
		for (int i=0; i<2; i++) fRec18[i] = 0;
		for (int i=0; i<2; i++) fRec16[i] = 0;
		for (int i=0; i<2; i++) fRec20[i] = 0;
		for (int i=0; i<2; i++) fRec21[i] = 0;
		for (int i=0; i<2; i++) fRec19[i] = 0;
		for (int i=0; i<2; i++) fRec23[i] = 0;
		for (int i=0; i<2; i++) fRec24[i] = 0;
		for (int i=0; i<2; i++) fRec22[i] = 0;
		for (int i=0; i<2; i++) fRec27[i] = 0;
		for (int i=0; i<2; i++) fRec26[i] = 0;
		for (int i=0; i<2; i++) fRec28[i] = 0;
		for (int i=0; i<2; i++) fRec25[i] = 0;
		for (int i=0; i<2; i++) fRec31[i] = 0;
		for (int i=0; i<2; i++) fRec30[i] = 0;
		for (int i=0; i<2; i++) fRec32[i] = 0;
		for (int i=0; i<2; i++) fRec29[i] = 0;
		for (int i=0; i<2; i++) fRec35[i] = 0;
		for (int i=0; i<2; i++) fRec34[i] = 0;
		for (int i=0; i<2; i++) fRec36[i] = 0;
		for (int i=0; i<2; i++) fRec33[i] = 0;
		for (int i=0; i<2; i++) fRec39[i] = 0;
		for (int i=0; i<2; i++) fRec38[i] = 0;
		for (int i=0; i<2; i++) fRec40[i] = 0;
		for (int i=0; i<2; i++) fRec37[i] = 0;
		for (int i=0; i<2; i++) fRec41[i] = 0;
		for (int i=0; i<2; i++) fRec42[i] = 0;
		for (int i=0; i<2; i++) fRec43[i] = 0;
		for (int i=0; i<2; i++) fRec44[i] = 0;
		for (int i=0; i<2; i++) fRec45[i] = 0;
		for (int i=0; i<2; i++) fRec46[i] = 0;
		for (int i=0; i<2; i++) fRec47[i] = 0;
		for (int i=0; i<2; i++) fRec48[i] = 0;
		for (int i=0; i<2; i++) fRec50[i] = 0;
		for (int i=0; i<2; i++) fRec49[i] = 0;
		for (int i=0; i<2; i++) fRec52[i] = 0;
		for (int i=0; i<2; i++) fRec51[i] = 0;
		for (int i=0; i<2; i++) fRec54[i] = 0;
		for (int i=0; i<2; i++) fRec53[i] = 0;
		for (int i=0; i<2; i++) fRec56[i] = 0;
		for (int i=0; i<2; i++) fRec55[i] = 0;
		for (int i=0; i<2; i++) fRec59[i] = 0;
		for (int i=0; i<2; i++) fRec58[i] = 0;
		for (int i=0; i<2; i++) fRec60[i] = 0;
		for (int i=0; i<2; i++) fRec57[i] = 0;
		for (int i=0; i<2; i++) fRec63[i] = 0;
		for (int i=0; i<2; i++) fRec62[i] = 0;
		for (int i=0; i<2; i++) fRec64[i] = 0;
		for (int i=0; i<2; i++) fRec61[i] = 0;
		for (int i=0; i<2; i++) fRec67[i] = 0;
		for (int i=0; i<2; i++) fRec66[i] = 0;
		for (int i=0; i<2; i++) fRec68[i] = 0;
		for (int i=0; i<2; i++) fRec65[i] = 0;
		for (int i=0; i<2; i++) fRec71[i] = 0;
		for (int i=0; i<2; i++) fRec70[i] = 0;
		for (int i=0; i<2; i++) fRec72[i] = 0;
		for (int i=0; i<2; i++) fRec69[i] = 0;
		for (int i=0; i<2; i++) fRec73[i] = 0;
		for (int i=0; i<2; i++) fRec74[i] = 0;
		for (int i=0; i<2; i++) fRec75[i] = 0;
		for (int i=0; i<2; i++) fRec76[i] = 0;
		for (int i=0; i<2; i++) fRec77[i] = 0;
		for (int i=0; i<2; i++) fRec78[i] = 0;
		for (int i=0; i<2; i++) fRec79[i] = 0;
		for (int i=0; i<2; i++) fRec80[i] = 0;
		for (int i=0; i<2; i++) fRec82[i] = 0;
		for (int i=0; i<2; i++) fRec81[i] = 0;
		for (int i=0; i<2; i++) fRec84[i] = 0;
		for (int i=0; i<2; i++) fRec83[i] = 0;
		for (int i=0; i<2; i++) fRec86[i] = 0;
		for (int i=0; i<2; i++) fRec85[i] = 0;
		for (int i=0; i<2; i++) fRec88[i] = 0;
		for (int i=0; i<2; i++) fRec87[i] = 0;
		for (int i=0; i<2; i++) fRec91[i] = 0;
		for (int i=0; i<2; i++) fRec90[i] = 0;
		for (int i=0; i<2; i++) fRec92[i] = 0;
		for (int i=0; i<2; i++) fRec89[i] = 0;
		for (int i=0; i<2; i++) fRec95[i] = 0;
		for (int i=0; i<2; i++) fRec94[i] = 0;
		for (int i=0; i<2; i++) fRec96[i] = 0;
		for (int i=0; i<2; i++) fRec93[i] = 0;
		for (int i=0; i<2; i++) fRec99[i] = 0;
		for (int i=0; i<2; i++) fRec98[i] = 0;
		for (int i=0; i<2; i++) fRec100[i] = 0;
		for (int i=0; i<2; i++) fRec97[i] = 0;
		for (int i=0; i<2; i++) fRec103[i] = 0;
		for (int i=0; i<2; i++) fRec102[i] = 0;
		for (int i=0; i<2; i++) fRec104[i] = 0;
		for (int i=0; i<2; i++) fRec101[i] = 0;
		for (int i=0; i<2; i++) fRec105[i] = 0;
		for (int i=0; i<2; i++) fRec106[i] = 0;
		for (int i=0; i<2; i++) fRec107[i] = 0;
		for (int i=0; i<2; i++) fRec108[i] = 0;
		for (int i=0; i<2; i++) fRec109[i] = 0;
		for (int i=0; i<2; i++) fRec110[i] = 0;
		for (int i=0; i<2; i++) fRec111[i] = 0;
		for (int i=0; i<2; i++) fRec112[i] = 0;
		for (int i=0; i<2; i++) fRec114[i] = 0;
		for (int i=0; i<2; i++) fRec113[i] = 0;
		for (int i=0; i<2; i++) fRec116[i] = 0;
		for (int i=0; i<2; i++) fRec115[i] = 0;
		for (int i=0; i<2; i++) fRec118[i] = 0;
		for (int i=0; i<2; i++) fRec117[i] = 0;
		for (int i=0; i<2; i++) fRec120[i] = 0;
		for (int i=0; i<2; i++) fRec119[i] = 0;
		for (int i=0; i<2; i++) fRec123[i] = 0;
		for (int i=0; i<2; i++) fRec122[i] = 0;
		for (int i=0; i<2; i++) fRec124[i] = 0;
		for (int i=0; i<2; i++) fRec121[i] = 0;
		for (int i=0; i<2; i++) fRec127[i] = 0;
		for (int i=0; i<2; i++) fRec126[i] = 0;
		for (int i=0; i<2; i++) fRec128[i] = 0;
		for (int i=0; i<2; i++) fRec125[i] = 0;
		for (int i=0; i<2; i++) fRec131[i] = 0;
		for (int i=0; i<2; i++) fRec130[i] = 0;
		for (int i=0; i<2; i++) fRec132[i] = 0;
		for (int i=0; i<2; i++) fRec129[i] = 0;
		for (int i=0; i<2; i++) fRec135[i] = 0;
		for (int i=0; i<2; i++) fRec134[i] = 0;
		for (int i=0; i<2; i++) fRec136[i] = 0;
		for (int i=0; i<2; i++) fRec133[i] = 0;
		for (int i=0; i<2; i++) fRec137[i] = 0;
		for (int i=0; i<2; i++) fRec138[i] = 0;
		for (int i=0; i<2; i++) fRec139[i] = 0;
		for (int i=0; i<2; i++) fRec140[i] = 0;
		for (int i=0; i<2; i++) fRec141[i] = 0;
		for (int i=0; i<2; i++) fRec142[i] = 0;
		for (int i=0; i<2; i++) fRec143[i] = 0;
		for (int i=0; i<2; i++) fRec144[i] = 0;
		for (int i=0; i<2; i++) fRec146[i] = 0;
		for (int i=0; i<2; i++) fRec145[i] = 0;
		for (int i=0; i<2; i++) fRec148[i] = 0;
		for (int i=0; i<2; i++) fRec147[i] = 0;
		for (int i=0; i<2; i++) fRec150[i] = 0;
		for (int i=0; i<2; i++) fRec149[i] = 0;
		for (int i=0; i<2; i++) fRec152[i] = 0;
		for (int i=0; i<2; i++) fRec151[i] = 0;
		for (int i=0; i<2; i++) fRec155[i] = 0;
		for (int i=0; i<2; i++) fRec154[i] = 0;
		for (int i=0; i<2; i++) fRec156[i] = 0;
		for (int i=0; i<2; i++) fRec153[i] = 0;
		for (int i=0; i<2; i++) fRec159[i] = 0;
		for (int i=0; i<2; i++) fRec158[i] = 0;
		for (int i=0; i<2; i++) fRec160[i] = 0;
		for (int i=0; i<2; i++) fRec157[i] = 0;
		for (int i=0; i<2; i++) fRec163[i] = 0;
		for (int i=0; i<2; i++) fRec162[i] = 0;
		for (int i=0; i<2; i++) fRec164[i] = 0;
		for (int i=0; i<2; i++) fRec161[i] = 0;
		for (int i=0; i<2; i++) fRec167[i] = 0;
		for (int i=0; i<2; i++) fRec166[i] = 0;
		for (int i=0; i<2; i++) fRec168[i] = 0;
		for (int i=0; i<2; i++) fRec165[i] = 0;
		for (int i=0; i<2; i++) fRec169[i] = 0;
		for (int i=0; i<2; i++) fRec170[i] = 0;
		for (int i=0; i<2; i++) fRec171[i] = 0;
		for (int i=0; i<2; i++) fRec172[i] = 0;
		for (int i=0; i<2; i++) fRec173[i] = 0;
		for (int i=0; i<2; i++) fRec174[i] = 0;
		for (int i=0; i<2; i++) fRec175[i] = 0;
		for (int i=0; i<2; i++) fRec176[i] = 0;
		for (int i=0; i<2; i++) fRec178[i] = 0;
		for (int i=0; i<2; i++) fRec177[i] = 0;
		for (int i=0; i<2; i++) fRec180[i] = 0;
		for (int i=0; i<2; i++) fRec179[i] = 0;
		for (int i=0; i<2; i++) fRec182[i] = 0;
		for (int i=0; i<2; i++) fRec181[i] = 0;
		for (int i=0; i<2; i++) fRec184[i] = 0;
		for (int i=0; i<2; i++) fRec183[i] = 0;
		for (int i=0; i<2; i++) fRec187[i] = 0;
		for (int i=0; i<2; i++) fRec186[i] = 0;
		for (int i=0; i<2; i++) fRec188[i] = 0;
		for (int i=0; i<2; i++) fRec185[i] = 0;
		for (int i=0; i<2; i++) fRec191[i] = 0;
		for (int i=0; i<2; i++) fRec190[i] = 0;
		for (int i=0; i<2; i++) fRec192[i] = 0;
		for (int i=0; i<2; i++) fRec189[i] = 0;
		for (int i=0; i<2; i++) fRec195[i] = 0;
		for (int i=0; i<2; i++) fRec194[i] = 0;
		for (int i=0; i<2; i++) fRec196[i] = 0;
		for (int i=0; i<2; i++) fRec193[i] = 0;
		for (int i=0; i<2; i++) fRec199[i] = 0;
		for (int i=0; i<2; i++) fRec198[i] = 0;
		for (int i=0; i<2; i++) fRec200[i] = 0;
		for (int i=0; i<2; i++) fRec197[i] = 0;
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
		ui_interface->addHorizontalSlider("algN", &fslider4, 0.0f, 0.0f, 11.0f, 1.0f);
		ui_interface->openVerticalBox("envelope");
		ui_interface->addHorizontalSlider("Attack", &fslider2, 0.001f, 0.001f, 4.0f, 0.001f);
		ui_interface->addHorizontalSlider("Decay", &fslider1, 0.0f, 0.0f, 4.0f, 0.001f);
		ui_interface->addHorizontalSlider("Release", &fslider0, 0.0f, 0.0f, 4.0f, 0.01f);
		ui_interface->addHorizontalSlider("Sustain", &fslider3, 1.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->closeBox();
		ui_interface->addHorizontalSlider("fmAmount", &fslider26, 1.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->openVerticalBox("op0");
		ui_interface->addHorizontalSlider("detune", &fslider13, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("feedback", &fslider11, 0.0f, -0.5f, 0.5f, 0.01f);
		ui_interface->addHorizontalSlider("mAtt", &fslider31, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mDecrel", &fslider32, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mSuspos", &fslider30, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("outLev", &fslider14, 1.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("ratio", &fslider12, 1.0f, 0.25f, 4.0f, 0.01f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("op1");
		ui_interface->addHorizontalSlider("detune", &fslider21, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("feedback", &fslider19, 0.0f, -0.5f, 0.5f, 0.01f);
		ui_interface->addHorizontalSlider("mAtt", &fslider28, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mDecrel", &fslider29, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mSuspos", &fslider27, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("outLev", &fslider22, 1.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("ratio", &fslider20, 1.0f, 0.25f, 4.0f, 0.01f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("op2");
		ui_interface->addHorizontalSlider("detune", &fslider17, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("feedback", &fslider15, 0.0f, -0.5f, 0.5f, 0.01f);
		ui_interface->addHorizontalSlider("mAtt", &fslider34, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mDecrel", &fslider35, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mSuspos", &fslider33, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("outLev", &fslider18, 1.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("ratio", &fslider16, 1.0f, 0.25f, 4.0f, 0.01f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("op3");
		ui_interface->addHorizontalSlider("detune", &fslider8, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("feedback", &fslider5, 0.0f, -0.5f, 0.5f, 0.01f);
		ui_interface->addHorizontalSlider("mAtt", &fslider24, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mDecrel", &fslider25, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("mSuspos", &fslider23, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("outLev", &fslider9, 1.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("ratio", &fslider6, 1.0f, 0.25f, 4.0f, 0.01f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("v0");
		ui_interface->addHorizontalBargraph("carrier", &fbargraph5, 0.0f, 1.0f);
		ui_interface->openVerticalBox("op0");
		ui_interface->addHorizontalBargraph("modulator", &fbargraph28, 0.0f, 1.0f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("op1");
		ui_interface->addHorizontalBargraph("modulator", &fbargraph27, 0.0f, 1.0f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("op2");
		ui_interface->addHorizontalBargraph("modulator", &fbargraph29, 0.0f, 1.0f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("op3");
		ui_interface->addHorizontalBargraph("modulator", &fbargraph26, 0.0f, 1.0f);
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->openVerticalBox("v1");
		ui_interface->addHorizontalBargraph("carrier", &fbargraph4, 0.0f, 1.0f);
		ui_interface->openVerticalBox("op0");
		ui_interface->addHorizontalBargraph("modulator", &fbargraph24, 0.0f, 1.0f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("op1");
		ui_interface->addHorizontalBargraph("modulator", &fbargraph23, 0.0f, 1.0f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("op2");
		ui_interface->addHorizontalBargraph("modulator", &fbargraph25, 0.0f, 1.0f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("op3");
		ui_interface->addHorizontalBargraph("modulator", &fbargraph22, 0.0f, 1.0f);
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->openVerticalBox("v2");
		ui_interface->addHorizontalBargraph("carrier", &fbargraph3, 0.0f, 1.0f);
		ui_interface->openVerticalBox("op0");
		ui_interface->addHorizontalBargraph("modulator", &fbargraph20, 0.0f, 1.0f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("op1");
		ui_interface->addHorizontalBargraph("modulator", &fbargraph19, 0.0f, 1.0f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("op2");
		ui_interface->addHorizontalBargraph("modulator", &fbargraph21, 0.0f, 1.0f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("op3");
		ui_interface->addHorizontalBargraph("modulator", &fbargraph18, 0.0f, 1.0f);
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->openVerticalBox("v3");
		ui_interface->addHorizontalBargraph("carrier", &fbargraph2, 0.0f, 1.0f);
		ui_interface->openVerticalBox("op0");
		ui_interface->addHorizontalBargraph("modulator", &fbargraph16, 0.0f, 1.0f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("op1");
		ui_interface->addHorizontalBargraph("modulator", &fbargraph15, 0.0f, 1.0f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("op2");
		ui_interface->addHorizontalBargraph("modulator", &fbargraph17, 0.0f, 1.0f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("op3");
		ui_interface->addHorizontalBargraph("modulator", &fbargraph14, 0.0f, 1.0f);
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->openVerticalBox("v4");
		ui_interface->addHorizontalBargraph("carrier", &fbargraph1, 0.0f, 1.0f);
		ui_interface->openVerticalBox("op0");
		ui_interface->addHorizontalBargraph("modulator", &fbargraph12, 0.0f, 1.0f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("op1");
		ui_interface->addHorizontalBargraph("modulator", &fbargraph11, 0.0f, 1.0f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("op2");
		ui_interface->addHorizontalBargraph("modulator", &fbargraph13, 0.0f, 1.0f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("op3");
		ui_interface->addHorizontalBargraph("modulator", &fbargraph10, 0.0f, 1.0f);
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->openVerticalBox("v5");
		ui_interface->addHorizontalBargraph("carrier", &fbargraph0, 0.0f, 1.0f);
		ui_interface->openVerticalBox("op0");
		ui_interface->addHorizontalBargraph("modulator", &fbargraph8, 0.0f, 1.0f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("op1");
		ui_interface->addHorizontalBargraph("modulator", &fbargraph7, 0.0f, 1.0f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("op2");
		ui_interface->addHorizontalBargraph("modulator", &fbargraph9, 0.0f, 1.0f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("op3");
		ui_interface->addHorizontalBargraph("modulator", &fbargraph6, 0.0f, 1.0f);
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
		ui_interface->addHorizontalSlider("freq", &fslider7, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addButton("trigger", &fbutton0);
		ui_interface->addHorizontalSlider("velocity", &fslider10, 1.0f, 0.0f, 1.0f, 0.007874015748031496f);
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->closeBox();
	}
	virtual void compute (int count, FAUSTFLOAT** input, FAUSTFLOAT** output) {
		//zone1
		//zone2
		float 	fSlow0 = float(fslider0);
		float 	fSlow1 = float(fslider1);
		float 	fSlow2 = float(fslider2);
		float 	fSlow3 = (6.9100000000000001f * fSlow2);
		int 	iSlow4 = int((fConst0 * fSlow2));
		float 	fSlow5 = float(fbutton0);
		int 	iSlow6 = (fSlow5 > 0.0f);
		int 	iSlow7 = int(iSlow6);
		float 	fSlow8 = float(fslider3);
		float 	fSlow9 = float(iSlow6);
		float 	fSlow10 = (fSlow9 * fSlow8);
		int 	iSlow11 = int(float(fslider4));
		int 	iSlow12 = (float((iSlow11 == 10)) != 0.0f);
		int 	iSlow13 = (float((iSlow11 == 9)) != 0.0f);
		float 	fSlow14 = float(fbutton1);
		int 	iSlow15 = (fSlow14 > 0.0f);
		int 	iSlow16 = int(iSlow15);
		float 	fSlow17 = float(iSlow15);
		float 	fSlow18 = (fSlow17 * fSlow8);
		float 	fSlow19 = float(fbutton2);
		int 	iSlow20 = (fSlow19 > 0.0f);
		int 	iSlow21 = int(iSlow20);
		float 	fSlow22 = float(iSlow20);
		float 	fSlow23 = (fSlow22 * fSlow8);
		float 	fSlow24 = float(fbutton3);
		int 	iSlow25 = (fSlow24 > 0.0f);
		int 	iSlow26 = int(iSlow25);
		float 	fSlow27 = float(iSlow25);
		float 	fSlow28 = (fSlow27 * fSlow8);
		float 	fSlow29 = float(fbutton4);
		int 	iSlow30 = (fSlow29 > 0.0f);
		int 	iSlow31 = int(iSlow30);
		float 	fSlow32 = float(iSlow30);
		float 	fSlow33 = (fSlow32 * fSlow8);
		float 	fSlow34 = float(fbutton5);
		int 	iSlow35 = (fSlow34 > 0.0f);
		int 	iSlow36 = int(iSlow35);
		float 	fSlow37 = float(iSlow35);
		float 	fSlow38 = (fSlow37 * fSlow8);
		float 	fSlow39 = (0.0010000000000000009f * float(fslider5));
		int 	iSlow40 = (float((iSlow11 == 7)) != 0.0f);
		int 	iSlow41 = (float((iSlow11 == 6)) != 0.0f);
		int 	iSlow42 = (float((iSlow11 == 4)) != 0.0f);
		int 	iSlow43 = (float((iSlow11 == 3)) != 0.0f);
		int 	iSlow44 = (float((iSlow11 == 2)) != 0.0f);
		int 	iSlow45 = (float((iSlow11 == 1)) != 0.0f);
		int 	iSlow46 = (float((iSlow11 == 0)) != 0.0f);
		int 	iSlow47 = (float((iSlow11 == 5)) != 0.0f);
		int 	iSlow48 = (float((iSlow11 == 8)) != 0.0f);
		float 	fSlow49 = float(fslider6);
		float 	fSlow50 = float(fslider7);
		float 	fSlow51 = (25.0f * float(fslider8));
		float 	fSlow52 = (fConst2 * (fSlow51 + (fSlow50 * fSlow49)));
		float 	fSlow53 = float(fslider9);
		float 	fSlow54 = float(fslider10);
		float 	fSlow55 = (fSlow54 * fSlow53);
		float 	fSlow56 = (0.0010000000000000009f * float(fslider11));
		float 	fSlow57 = float(fslider12);
		float 	fSlow58 = (25.0f * float(fslider13));
		float 	fSlow59 = (fConst2 * (fSlow58 + (fSlow50 * fSlow57)));
		float 	fSlow60 = float(fslider14);
		float 	fSlow61 = (fSlow54 * fSlow60);
		float 	fSlow62 = (0.0010000000000000009f * float(fslider15));
		float 	fSlow63 = float(fslider16);
		float 	fSlow64 = (25.0f * float(fslider17));
		float 	fSlow65 = (fConst2 * (fSlow64 + (fSlow50 * fSlow63)));
		float 	fSlow66 = float(fslider18);
		float 	fSlow67 = (fSlow54 * fSlow66);
		float 	fSlow68 = (0.0010000000000000009f * float(fslider19));
		float 	fSlow69 = float(fslider20);
		float 	fSlow70 = (25.0f * float(fslider21));
		float 	fSlow71 = (fConst2 * (fSlow70 + (fSlow50 * fSlow69)));
		float 	fSlow72 = float(fslider22);
		float 	fSlow73 = (fSlow54 * fSlow72);
		float 	fSlow74 = float(fslider23);
		float 	fSlow75 = (fSlow5 * fSlow74);
		float 	fSlow76 = float(fslider24);
		float 	fSlow77 = (fConst3 * fSlow76);
		float 	fSlow78 = float(fslider25);
		float 	fSlow79 = (((1.0f - fSlow74) * fSlow78) + fSlow76);
		float 	fSlow80 = (fConst3 * fSlow79);
		int 	iSlow81 = int(((fSlow5 == 0.0f) > 0));
		float 	fSlow82 = (fSlow79 - fSlow76);
		float 	fSlow83 = (fConst4 * ((fSlow75 + -1.0f) / fSlow82));
		float 	fSlow84 = (fConst4 / fSlow76);
		float 	fSlow85 = max(0.001f, (fConst3 * (fSlow74 * fSlow78)));
		int 	iSlow86 = int((iSlow6 > 0));
		float 	fSlow87 = (1.0f / fSlow85);
		float 	fSlow88 = float(fslider26);
		float 	fSlow89 = (fSlow53 * fSlow88);
		float 	fSlow90 = float(fslider27);
		float 	fSlow91 = (fSlow5 * fSlow90);
		float 	fSlow92 = float(fslider28);
		float 	fSlow93 = (fConst3 * fSlow92);
		float 	fSlow94 = float(fslider29);
		float 	fSlow95 = (((1.0f - fSlow90) * fSlow94) + fSlow92);
		float 	fSlow96 = (fConst3 * fSlow95);
		float 	fSlow97 = (fSlow95 - fSlow92);
		float 	fSlow98 = (fConst4 * ((fSlow91 + -1.0f) / fSlow97));
		float 	fSlow99 = (fConst4 / fSlow92);
		float 	fSlow100 = max(0.001f, (fConst3 * (fSlow90 * fSlow94)));
		float 	fSlow101 = (1.0f / fSlow100);
		float 	fSlow102 = (fSlow72 * fSlow88);
		float 	fSlow103 = float(fslider30);
		float 	fSlow104 = (fSlow5 * fSlow103);
		float 	fSlow105 = float(fslider31);
		float 	fSlow106 = (fConst3 * fSlow105);
		float 	fSlow107 = float(fslider32);
		float 	fSlow108 = (((1.0f - fSlow103) * fSlow107) + fSlow105);
		float 	fSlow109 = (fConst3 * fSlow108);
		float 	fSlow110 = (fSlow108 - fSlow105);
		float 	fSlow111 = (fConst4 * ((fSlow104 + -1.0f) / fSlow110));
		float 	fSlow112 = (fConst4 / fSlow105);
		float 	fSlow113 = max(0.001f, (fConst3 * (fSlow103 * fSlow107)));
		float 	fSlow114 = (1.0f / fSlow113);
		float 	fSlow115 = (fSlow60 * fSlow88);
		float 	fSlow116 = float(fslider33);
		float 	fSlow117 = (fSlow5 * fSlow116);
		float 	fSlow118 = float(fslider34);
		float 	fSlow119 = (fConst3 * fSlow118);
		float 	fSlow120 = float(fslider35);
		float 	fSlow121 = (((1.0f - fSlow116) * fSlow120) + fSlow118);
		float 	fSlow122 = (fConst3 * fSlow121);
		float 	fSlow123 = (fSlow121 - fSlow118);
		float 	fSlow124 = (fConst4 * ((fSlow117 + -1.0f) / fSlow123));
		float 	fSlow125 = (fConst4 / fSlow118);
		float 	fSlow126 = max(0.001f, (fConst3 * (fSlow116 * fSlow120)));
		float 	fSlow127 = (1.0f / fSlow126);
		float 	fSlow128 = (fSlow66 * fSlow88);
		float 	fSlow129 = float(fslider36);
		float 	fSlow130 = (fConst2 * (fSlow51 + (fSlow129 * fSlow49)));
		float 	fSlow131 = float(fslider37);
		float 	fSlow132 = (fSlow53 * fSlow131);
		float 	fSlow133 = (fConst2 * (fSlow58 + (fSlow129 * fSlow57)));
		float 	fSlow134 = (fSlow60 * fSlow131);
		float 	fSlow135 = (fConst2 * (fSlow64 + (fSlow129 * fSlow63)));
		float 	fSlow136 = (fSlow66 * fSlow131);
		float 	fSlow137 = (fConst2 * (fSlow70 + (fSlow129 * fSlow69)));
		float 	fSlow138 = (fSlow72 * fSlow131);
		float 	fSlow139 = (fSlow14 * fSlow74);
		int 	iSlow140 = int(((fSlow14 == 0.0f) > 0));
		float 	fSlow141 = (fConst4 * ((fSlow139 + -1.0f) / fSlow82));
		int 	iSlow142 = int((iSlow15 > 0));
		float 	fSlow143 = (fSlow14 * fSlow90);
		float 	fSlow144 = (fConst4 * ((fSlow143 + -1.0f) / fSlow97));
		float 	fSlow145 = (fSlow14 * fSlow103);
		float 	fSlow146 = (fConst4 * ((fSlow145 + -1.0f) / fSlow110));
		float 	fSlow147 = (fSlow14 * fSlow116);
		float 	fSlow148 = (fConst4 * ((fSlow147 + -1.0f) / fSlow123));
		float 	fSlow149 = float(fslider38);
		float 	fSlow150 = (fConst2 * (fSlow51 + (fSlow149 * fSlow49)));
		float 	fSlow151 = float(fslider39);
		float 	fSlow152 = (fSlow53 * fSlow151);
		float 	fSlow153 = (fConst2 * (fSlow58 + (fSlow149 * fSlow57)));
		float 	fSlow154 = (fSlow60 * fSlow151);
		float 	fSlow155 = (fConst2 * (fSlow64 + (fSlow149 * fSlow63)));
		float 	fSlow156 = (fSlow66 * fSlow151);
		float 	fSlow157 = (fConst2 * (fSlow70 + (fSlow149 * fSlow69)));
		float 	fSlow158 = (fSlow72 * fSlow151);
		float 	fSlow159 = (fSlow19 * fSlow74);
		int 	iSlow160 = int(((fSlow19 == 0.0f) > 0));
		float 	fSlow161 = (fConst4 * ((fSlow159 + -1.0f) / fSlow82));
		int 	iSlow162 = int((iSlow20 > 0));
		float 	fSlow163 = (fSlow19 * fSlow90);
		float 	fSlow164 = (fConst4 * ((fSlow163 + -1.0f) / fSlow97));
		float 	fSlow165 = (fSlow19 * fSlow103);
		float 	fSlow166 = (fConst4 * ((fSlow165 + -1.0f) / fSlow110));
		float 	fSlow167 = (fSlow19 * fSlow116);
		float 	fSlow168 = (fConst4 * ((fSlow167 + -1.0f) / fSlow123));
		float 	fSlow169 = float(fslider40);
		float 	fSlow170 = (fConst2 * (fSlow51 + (fSlow169 * fSlow49)));
		float 	fSlow171 = float(fslider41);
		float 	fSlow172 = (fSlow53 * fSlow171);
		float 	fSlow173 = (fConst2 * (fSlow58 + (fSlow169 * fSlow57)));
		float 	fSlow174 = (fSlow60 * fSlow171);
		float 	fSlow175 = (fConst2 * (fSlow64 + (fSlow169 * fSlow63)));
		float 	fSlow176 = (fSlow66 * fSlow171);
		float 	fSlow177 = (fConst2 * (fSlow70 + (fSlow169 * fSlow69)));
		float 	fSlow178 = (fSlow72 * fSlow171);
		float 	fSlow179 = (fSlow24 * fSlow74);
		int 	iSlow180 = int(((fSlow24 == 0.0f) > 0));
		float 	fSlow181 = (fConst4 * ((fSlow179 + -1.0f) / fSlow82));
		int 	iSlow182 = int((iSlow25 > 0));
		float 	fSlow183 = (fSlow24 * fSlow90);
		float 	fSlow184 = (fConst4 * ((fSlow183 + -1.0f) / fSlow97));
		float 	fSlow185 = (fSlow24 * fSlow103);
		float 	fSlow186 = (fConst4 * ((fSlow185 + -1.0f) / fSlow110));
		float 	fSlow187 = (fSlow24 * fSlow116);
		float 	fSlow188 = (fConst4 * ((fSlow187 + -1.0f) / fSlow123));
		float 	fSlow189 = float(fslider42);
		float 	fSlow190 = (fConst2 * (fSlow51 + (fSlow189 * fSlow49)));
		float 	fSlow191 = float(fslider43);
		float 	fSlow192 = (fSlow53 * fSlow191);
		float 	fSlow193 = (fConst2 * (fSlow58 + (fSlow189 * fSlow57)));
		float 	fSlow194 = (fSlow60 * fSlow191);
		float 	fSlow195 = (fConst2 * (fSlow64 + (fSlow189 * fSlow63)));
		float 	fSlow196 = (fSlow66 * fSlow191);
		float 	fSlow197 = (fConst2 * (fSlow70 + (fSlow189 * fSlow69)));
		float 	fSlow198 = (fSlow72 * fSlow191);
		float 	fSlow199 = (fSlow29 * fSlow74);
		int 	iSlow200 = int(((fSlow29 == 0.0f) > 0));
		float 	fSlow201 = (fConst4 * ((fSlow199 + -1.0f) / fSlow82));
		int 	iSlow202 = int((iSlow30 > 0));
		float 	fSlow203 = (fSlow29 * fSlow90);
		float 	fSlow204 = (fConst4 * ((fSlow203 + -1.0f) / fSlow97));
		float 	fSlow205 = (fSlow29 * fSlow103);
		float 	fSlow206 = (fConst4 * ((fSlow205 + -1.0f) / fSlow110));
		float 	fSlow207 = (fSlow29 * fSlow116);
		float 	fSlow208 = (fConst4 * ((fSlow207 + -1.0f) / fSlow123));
		float 	fSlow209 = float(fslider44);
		float 	fSlow210 = (fConst2 * ((fSlow209 * fSlow49) + fSlow51));
		float 	fSlow211 = float(fslider45);
		float 	fSlow212 = (fSlow53 * fSlow211);
		float 	fSlow213 = (fConst2 * ((fSlow209 * fSlow57) + fSlow58));
		float 	fSlow214 = (fSlow60 * fSlow211);
		float 	fSlow215 = (fConst2 * ((fSlow209 * fSlow63) + fSlow64));
		float 	fSlow216 = (fSlow66 * fSlow211);
		float 	fSlow217 = (fConst2 * ((fSlow209 * fSlow69) + fSlow70));
		float 	fSlow218 = (fSlow72 * fSlow211);
		float 	fSlow219 = (fSlow34 * fSlow74);
		int 	iSlow220 = int(((fSlow34 == 0.0f) > 0));
		float 	fSlow221 = (fConst4 * ((fSlow219 + -1.0f) / fSlow82));
		int 	iSlow222 = int((iSlow35 > 0));
		float 	fSlow223 = (fSlow34 * fSlow90);
		float 	fSlow224 = (fConst4 * ((fSlow223 + -1.0f) / fSlow97));
		float 	fSlow225 = (fSlow34 * fSlow103);
		float 	fSlow226 = (fConst4 * ((fSlow225 + -1.0f) / fSlow110));
		float 	fSlow227 = (fSlow34 * fSlow116);
		float 	fSlow228 = (fConst4 * ((fSlow227 + -1.0f) / fSlow123));
		//zone2b
		//zone3
		FAUSTFLOAT* output0 = output[0];
		//LoopGraphScalar
		for (int i=0; i<count; i++) {
			iRec1[0] = (iSlow6 * (iRec1[1] + 1));
			iTempPerm0 = int((iRec1[0] < iSlow4));
			fTempPerm1 = expf((0 - (fConst1 / ((iSlow7)?((iTempPerm0)?fSlow3:fSlow1):fSlow0))));
			fRec0[0] = ((fRec0[1] * fTempPerm1) + (((iSlow7)?((iTempPerm0)?1.5873015873015872f:fSlow10):0.0f) * (1.0f - fTempPerm1)));
			fTempPerm2 = min(1.0f, fRec0[0]);
			fbargraph0 = fTempPerm2;
			fTempPerm3 = fTempPerm2;
			iRec6[0] = (iSlow15 * (iRec6[1] + 1));
			iTempPerm5 = int((iRec6[0] < iSlow4));
			fTempPerm6 = expf((0 - (fConst1 / ((iSlow16)?((iTempPerm5)?fSlow3:fSlow1):fSlow0))));
			fRec5[0] = ((fRec5[1] * fTempPerm6) + (((iSlow16)?((iTempPerm5)?1.5873015873015872f:fSlow18):0.0f) * (1.0f - fTempPerm6)));
			fTempPerm7 = min(1.0f, fRec5[0]);
			fbargraph1 = fTempPerm7;
			fTempPerm8 = fTempPerm7;
			iRec8[0] = (iSlow20 * (iRec8[1] + 1));
			iTempPerm9 = int((iRec8[0] < iSlow4));
			fTempPerm10 = expf((0 - (fConst1 / ((iSlow21)?((iTempPerm9)?fSlow3:fSlow1):fSlow0))));
			fRec7[0] = ((fRec7[1] * fTempPerm10) + (((iSlow21)?((iTempPerm9)?1.5873015873015872f:fSlow23):0.0f) * (1.0f - fTempPerm10)));
			fTempPerm11 = min(1.0f, fRec7[0]);
			fbargraph2 = fTempPerm11;
			fTempPerm12 = fTempPerm11;
			iRec10[0] = (iSlow25 * (iRec10[1] + 1));
			iTempPerm13 = int((iRec10[0] < iSlow4));
			fTempPerm14 = expf((0 - (fConst1 / ((iSlow26)?((iTempPerm13)?fSlow3:fSlow1):fSlow0))));
			fRec9[0] = ((fRec9[1] * fTempPerm14) + (((iSlow26)?((iTempPerm13)?1.5873015873015872f:fSlow28):0.0f) * (1.0f - fTempPerm14)));
			fTempPerm15 = min(1.0f, fRec9[0]);
			fbargraph3 = fTempPerm15;
			fTempPerm16 = fTempPerm15;
			iRec12[0] = (iSlow30 * (iRec12[1] + 1));
			iTempPerm17 = int((iRec12[0] < iSlow4));
			fTempPerm18 = expf((0 - (fConst1 / ((iSlow31)?((iTempPerm17)?fSlow3:fSlow1):fSlow0))));
			fRec11[0] = ((fRec11[1] * fTempPerm18) + (((iSlow31)?((iTempPerm17)?1.5873015873015872f:fSlow33):0.0f) * (1.0f - fTempPerm18)));
			fTempPerm19 = min(1.0f, fRec11[0]);
			fbargraph4 = fTempPerm19;
			fTempPerm20 = fTempPerm19;
			iRec14[0] = (iSlow35 * (iRec14[1] + 1));
			iTempPerm21 = int((iRec14[0] < iSlow4));
			fTempPerm22 = expf((0 - (fConst1 / ((iSlow36)?((iTempPerm21)?fSlow3:fSlow1):fSlow0))));
			fRec13[0] = ((fRec13[1] * fTempPerm22) + (((iSlow36)?((iTempPerm21)?1.5873015873015872f:fSlow38):0.0f) * (1.0f - fTempPerm22)));
			fTempPerm23 = min(1.0f, fRec13[0]);
			fbargraph5 = fTempPerm23;
			fTempPerm24 = fTempPerm23;
			if (iSlow13 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow12 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow13 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow12 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow13 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow12 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow13 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow12 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow13 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow12 && (float((fTempPerm8 > 0.001f)) != 0.0f) || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow13 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow12) {
				fRec4[0] = (fSlow39 + (0.999f * fRec4[1]));
			}
			if ((float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow48 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow47 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow46 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow45 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow44 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow43 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow42 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow41 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow13 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow40 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow12) {
				fRec15[0] = (fSlow52 + (fRec15[1] - floorf((fSlow52 + fRec15[1]))));
			}
			if ((float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow13 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow12) {
				fRec2[0] = (fSlow55 * ftbl0[(((int((65536.0f * (fRec15[0] + (fRec4[0] * fRec2[1])))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow48 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow47 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow46 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow45 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow44 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow43 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow42 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow41 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow40 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow12 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow48 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow47 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow46 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow45 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow44 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow43 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow42 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow41 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow40 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow12 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow48 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow47 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow46 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow45 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow44 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow43 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow42 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow41 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow40 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow12 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow48 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow47 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow46 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow45 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow44 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow43 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow42 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow41 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow40 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow12 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow48 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow47 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow46 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow45 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow44 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow43 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow42 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow41 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow40 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow12 && (float((fTempPerm8 > 0.001f)) != 0.0f) || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow48 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow47 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow46 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow45 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow44 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow43 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow42 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow41 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow40 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow12) {
				fRec17[0] = (fSlow56 + (0.999f * fRec17[1]));
			}
			if ((float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow48 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow47 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow46 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow45 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow44 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow43 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow42 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow41 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow13 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow40 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow12) {
				fRec18[0] = (fSlow59 + (fRec18[1] - floorf((fSlow59 + fRec18[1]))));
			}
			if ((float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow47 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow12) {
				fRec16[0] = (fSlow61 * ftbl0[(((int((65536.0f * (fRec18[0] + (fRec17[0] * fRec16[1])))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow48 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow13 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow40 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow12 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow48 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow13 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow40 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow12 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow48 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow13 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow40 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow12 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow48 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow13 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow40 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow12 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow48 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow13 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow40 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow12 && (float((fTempPerm8 > 0.001f)) != 0.0f) || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow48 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow13 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow40 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow12) {
				fRec20[0] = (fSlow62 + (0.999f * fRec20[1]));
			}
			if ((float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow48 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow47 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow46 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow45 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow44 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow43 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow42 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow41 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow13 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow40 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow12) {
				fRec21[0] = (fSlow65 + (fRec21[1] - floorf((fSlow65 + fRec21[1]))));
			}
			if ((float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow13 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow12) {
				fRec19[0] = (fSlow67 * ftbl0[(((int((65536.0f * (fRec21[0] + (fRec20[0] * fRec19[1])))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow48 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow47 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow42 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow13 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow12 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow48 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow47 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow42 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow13 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow12 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow48 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow47 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow42 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow13 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow12 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow48 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow47 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow42 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow13 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow12 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow48 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow47 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow42 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow13 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow12 && (float((fTempPerm8 > 0.001f)) != 0.0f) || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow48 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow47 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow42 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow13 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow12) {
				fRec23[0] = (fSlow68 + (0.999f * fRec23[1]));
			}
			if ((float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow48 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow47 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow46 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow45 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow44 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow43 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow42 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow41 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow13 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow40 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow12) {
				fRec24[0] = (fSlow71 + (fRec24[1] - floorf((fSlow71 + fRec24[1]))));
			}
			if ((float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow12) {
				fRec22[0] = (fSlow73 * ftbl0[(((int((65536.0f * (fRec24[0] + (fRec23[0] * fRec22[1])))) % 65536) + 65536) % 65536)]);
				fTempPerm25 = (fRec22[0] + (fRec19[0] + (fRec16[0] + fRec2[0])));
			}
			if ((float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow48 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow47 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow46 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow45 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow44 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow43 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow42 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow41 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow40) {
				fRec27[0] = ((iSlow81)?0.0f:min(fSlow80, (fRec27[1] + 1.0f)));
				iTempPerm26 = int((fRec27[0] < fSlow77));
				fRec26[0] = ((iSlow7)?(fSlow9 * ((iTempPerm26)?((int((fRec27[0] < 0.0f)))?0.0f:((iTempPerm26)?(fSlow84 * fRec27[0]):1.0f)):((int((fRec27[0] < fSlow80)))?((fSlow83 * (fRec27[0] - fSlow77)) + 1.0f):fSlow75))):fRec26[1]);
				fRec28[0] = ((iSlow86)?0.0f:min(fSlow85, (fRec28[1] + 1.0f)));
				fTempPerm27 = ((int((fRec28[0] < 0.0f)))?fRec26[0]:((int((fRec28[0] < fSlow85)))?(fRec26[0] + (fSlow87 * (0 - (fRec28[0] * fRec26[0])))):0.0f));
				fbargraph6 = fTempPerm27;
				fTempPerm28 = (fTempPerm27 * ftbl0[(((int((65536.0f * fRec15[0])) % 65536) + 65536) % 65536)]);
			}
			if ((float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow48 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow47 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow46 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow43 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow42 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow40) {
				fTempPerm29 = (fSlow89 * fTempPerm28);
			}
			if ((float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow48 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow40) {
				fRec25[0] = (fSlow67 * ftbl0[(((int((65536.0f * (fRec21[0] + (fTempPerm29 + (fRec20[0] * fRec25[1]))))) % 65536) + 65536) % 65536)]);
			}
			if ((float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow46 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow45 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow44 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow43 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow41 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow40) {
				fRec31[0] = ((iSlow81)?0.0f:min(fSlow96, (fRec31[1] + 1.0f)));
				iTempPerm30 = int((fRec31[0] < fSlow93));
				fRec30[0] = ((iSlow7)?(fSlow9 * ((iTempPerm30)?((int((fRec31[0] < 0.0f)))?0.0f:((iTempPerm30)?(fSlow99 * fRec31[0]):1.0f)):((int((fRec31[0] < fSlow96)))?((fSlow98 * (fRec31[0] - fSlow93)) + 1.0f):fSlow91))):fRec30[1]);
				fRec32[0] = ((iSlow86)?0.0f:min(fSlow100, (fRec32[1] + 1.0f)));
				fTempPerm31 = ((int((fRec32[0] < 0.0f)))?fRec30[0]:((int((fRec32[0] < fSlow100)))?(fRec30[0] + (fSlow101 * (0 - (fRec32[0] * fRec30[0])))):0.0f));
				fbargraph7 = fTempPerm31;
				fTempPerm32 = fTempPerm31;
			}
			if ((float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow41 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow40) {
				fTempPerm33 = (fTempPerm32 * ftbl0[(((int((65536.0f * fRec24[0])) % 65536) + 65536) % 65536)]);
			}
			if ((float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow40) {
				fRec29[0] = (fSlow61 * ftbl0[(((int((65536.0f * (fRec18[0] + ((fSlow102 * fTempPerm33) + (fRec17[0] * fRec29[1]))))) % 65536) + 65536) % 65536)]);
				fTempPerm34 = (fRec29[0] + fRec25[0]);
			}
			if ((float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow13) {
				fRec35[0] = ((iSlow81)?0.0f:min(fSlow109, (fRec35[1] + 1.0f)));
				iTempPerm35 = int((fRec35[0] < fSlow106));
				fRec34[0] = ((iSlow7)?(fSlow9 * ((iTempPerm35)?((int((fRec35[0] < 0.0f)))?0.0f:((iTempPerm35)?(fSlow112 * fRec35[0]):1.0f)):((int((fRec35[0] < fSlow109)))?((fSlow111 * (fRec35[0] - fSlow106)) + 1.0f):fSlow104))):fRec34[1]);
				fRec36[0] = ((iSlow86)?0.0f:min(fSlow113, (fRec36[1] + 1.0f)));
				fTempPerm36 = ((int((fRec36[0] < 0.0f)))?fRec34[0]:((int((fRec36[0] < fSlow113)))?(fRec34[0] + (fSlow114 * (0 - (fRec36[0] * fRec34[0])))):0.0f));
				fbargraph8 = fTempPerm36;
				fRec33[0] = (fSlow73 * ftbl0[(((int((65536.0f * (fRec24[0] + ((fRec23[0] * fRec33[1]) + (fSlow115 * (fTempPerm36 * ftbl0[(((int((65536.0f * fRec18[0])) % 65536) + 65536) % 65536)])))))) % 65536) + 65536) % 65536)]);
				fTempPerm37 = ((fRec2[0] + fRec33[0]) + fRec19[0]);
			}
			if ((float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow47 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow46 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow45 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow44 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow43 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow42 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow41) {
				fRec39[0] = ((iSlow81)?0.0f:min(fSlow122, (fRec39[1] + 1.0f)));
				iTempPerm38 = int((fRec39[0] < fSlow119));
				fRec38[0] = ((iSlow7)?(fSlow9 * ((iTempPerm38)?((int((fRec39[0] < 0.0f)))?0.0f:((iTempPerm38)?(fSlow125 * fRec39[0]):1.0f)):((int((fRec39[0] < fSlow122)))?((fSlow124 * (fRec39[0] - fSlow119)) + 1.0f):fSlow117))):fRec38[1]);
				fRec40[0] = ((iSlow86)?0.0f:min(fSlow126, (fRec40[1] + 1.0f)));
				fTempPerm39 = ((int((fRec40[0] < 0.0f)))?fRec38[0]:((int((fRec40[0] < fSlow126)))?(fRec38[0] + (fSlow127 * (0 - (fRec40[0] * fRec38[0])))):0.0f));
				fbargraph9 = fTempPerm39;
				fTempPerm40 = fTempPerm39;
			}
			if ((float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow45 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow44 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow41) {
				fTempPerm41 = (fTempPerm40 * ftbl0[(((int((65536.0f * fRec21[0])) % 65536) + 65536) % 65536)]);
				fTempPerm42 = (fSlow53 * fTempPerm28);
			}
			if ((float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow45 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow41) {
				fTempPerm43 = (fTempPerm42 + (fSlow66 * fTempPerm41));
			}
			if ((float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow41) {
				fRec37[0] = (fSlow61 * ftbl0[(((int((65536.0f * (fRec18[0] + ((fRec17[0] * fRec37[1]) + (fSlow88 * (fTempPerm43 + (fSlow72 * fTempPerm33))))))) % 65536) + 65536) % 65536)]);
			}
			if ((float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow47 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow46 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow43 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow42) {
				fTempPerm44 = (fTempPerm40 * ftbl0[(((int((65536.0f * (fRec21[0] + fTempPerm29))) % 65536) + 65536) % 65536)]);
			}
			if ((float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow47 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow46 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow42) {
				fTempPerm45 = (fSlow128 * fTempPerm44);
			}
			if ((float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow47 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow42) {
				fRec41[0] = (fSlow73 * ftbl0[(((int((65536.0f * (fRec24[0] + (fTempPerm45 + (fRec23[0] * fRec41[1]))))) % 65536) + 65536) % 65536)]);
			}
			if ((float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow42) {
				fRec42[0] = (fSlow61 * ftbl0[(((int((65536.0f * (fRec18[0] + (fTempPerm45 + (fRec17[0] * fRec42[1]))))) % 65536) + 65536) % 65536)]);
				fTempPerm46 = (fRec42[0] + fRec41[0]);
			}
			if ((float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow43) {
				fRec43[0] = (fSlow61 * ftbl0[(((int((65536.0f * (fRec18[0] + ((fRec17[0] * fRec43[1]) + (fSlow88 * ((fSlow66 * fTempPerm44) + (fSlow72 * (fTempPerm32 * ftbl0[(((int((65536.0f * (fRec24[0] + fTempPerm29))) % 65536) + 65536) % 65536)])))))))) % 65536) + 65536) % 65536)]);
			}
			if ((float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow44) {
				fRec44[0] = (fSlow61 * ftbl0[(((int((65536.0f * (fRec18[0] + ((fRec17[0] * fRec44[1]) + (fSlow88 * (fTempPerm42 + (fSlow72 * (fTempPerm32 * ftbl0[(((int((65536.0f * (fRec24[0] + (fSlow128 * fTempPerm41)))) % 65536) + 65536) % 65536)])))))))) % 65536) + 65536) % 65536)]);
			}
			if ((float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow45) {
				fRec45[0] = (fSlow61 * ftbl0[(((int((65536.0f * (fRec18[0] + ((fRec17[0] * fRec45[1]) + (fSlow102 * (fTempPerm32 * ftbl0[(((int((65536.0f * (fRec24[0] + (fSlow88 * fTempPerm43)))) % 65536) + 65536) % 65536)])))))) % 65536) + 65536) % 65536)]);
			}
			if ((float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow46) {
				fRec46[0] = (fSlow61 * ftbl0[(((int((65536.0f * (fRec18[0] + ((fRec17[0] * fRec46[1]) + (fSlow102 * (fTempPerm32 * ftbl0[(((int((65536.0f * (fRec24[0] + fTempPerm45))) % 65536) + 65536) % 65536)])))))) % 65536) + 65536) % 65536)]);
			}
			if ((float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow47) {
				fTempPerm47 = (fRec41[0] + fRec16[0]);
			}
			if ((float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow48) {
				fRec47[0] = (fSlow61 * ftbl0[(((int((65536.0f * (fRec18[0] + (fTempPerm29 + (fRec17[0] * fRec47[1]))))) % 65536) + 65536) % 65536)]);
				fRec48[0] = (fSlow73 * ftbl0[(((int((65536.0f * (fRec24[0] + (fTempPerm29 + (fRec23[0] * fRec48[1]))))) % 65536) + 65536) % 65536)]);
				fTempPerm48 = (fRec48[0] + (fRec25[0] + fRec47[0]));
			}
			if ((float((fTempPerm3 > 0.001f)) != 0.0f)) {
				fTempPerm49 = (faustpower<2>(fTempPerm3) * ((fTempPerm48 + (fTempPerm47 + (fRec46[0] + (fRec45[0] + (fRec44[0] + (fRec43[0] + (fTempPerm46 + (fRec37[0] + (fTempPerm37 + fTempPerm34))))))))) + fTempPerm25));
			}
			if (iSlow48 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow47 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow46 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow45 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow44 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow43 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow42 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow41 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow13 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow40 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow12 && (float((fTempPerm8 > 0.001f)) != 0.0f)) {
				fRec50[0] = (fSlow130 + (fRec50[1] - floorf((fSlow130 + fRec50[1]))));
			}
			if (iSlow13 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow12 && (float((fTempPerm8 > 0.001f)) != 0.0f)) {
				fRec49[0] = (fSlow132 * ftbl0[(((int((65536.0f * (fRec50[0] + (fRec4[0] * fRec49[1])))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow48 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow47 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow46 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow45 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow44 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow43 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow42 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow41 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow13 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow40 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow12 && (float((fTempPerm8 > 0.001f)) != 0.0f)) {
				fRec52[0] = (fSlow133 + (fRec52[1] - floorf((fSlow133 + fRec52[1]))));
			}
			if (iSlow47 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow12 && (float((fTempPerm8 > 0.001f)) != 0.0f)) {
				fRec51[0] = (fSlow134 * ftbl0[(((int((65536.0f * (fRec52[0] + (fRec17[0] * fRec51[1])))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow48 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow47 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow46 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow45 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow44 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow43 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow42 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow41 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow13 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow40 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow12 && (float((fTempPerm8 > 0.001f)) != 0.0f)) {
				fRec54[0] = (fSlow135 + (fRec54[1] - floorf((fSlow135 + fRec54[1]))));
			}
			if (iSlow13 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow12 && (float((fTempPerm8 > 0.001f)) != 0.0f)) {
				fRec53[0] = (fSlow136 * ftbl0[(((int((65536.0f * (fRec54[0] + (fRec20[0] * fRec53[1])))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow48 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow47 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow46 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow45 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow44 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow43 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow42 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow41 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow13 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow40 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow12 && (float((fTempPerm8 > 0.001f)) != 0.0f)) {
				fRec56[0] = (fSlow137 + (fRec56[1] - floorf((fSlow137 + fRec56[1]))));
			}
			if (iSlow12 && (float((fTempPerm8 > 0.001f)) != 0.0f)) {
				fRec55[0] = (fSlow138 * ftbl0[(((int((65536.0f * (fRec56[0] + (fRec23[0] * fRec55[1])))) % 65536) + 65536) % 65536)]);
				fTempPerm50 = (fRec55[0] + (fRec53[0] + (fRec51[0] + fRec49[0])));
			}
			if (iSlow48 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow47 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow46 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow45 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow44 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow43 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow42 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow41 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow40 && (float((fTempPerm8 > 0.001f)) != 0.0f)) {
				fRec59[0] = ((iSlow140)?0.0f:min(fSlow80, (fRec59[1] + 1.0f)));
				iTempPerm51 = int((fRec59[0] < fSlow77));
				fRec58[0] = ((iSlow16)?(fSlow17 * ((iTempPerm51)?((int((fRec59[0] < 0.0f)))?0.0f:((iTempPerm51)?(fSlow84 * fRec59[0]):1.0f)):((int((fRec59[0] < fSlow80)))?((fSlow141 * (fRec59[0] - fSlow77)) + 1.0f):fSlow139))):fRec58[1]);
				fRec60[0] = ((iSlow142)?0.0f:min(fSlow85, (fRec60[1] + 1.0f)));
				fTempPerm52 = ((int((fRec60[0] < 0.0f)))?fRec58[0]:((int((fRec60[0] < fSlow85)))?(fRec58[0] + (fSlow87 * (0 - (fRec60[0] * fRec58[0])))):0.0f));
				fbargraph10 = fTempPerm52;
				fTempPerm53 = (fTempPerm52 * ftbl0[(((int((65536.0f * fRec50[0])) % 65536) + 65536) % 65536)]);
			}
			if (iSlow48 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow47 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow46 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow43 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow42 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow40 && (float((fTempPerm8 > 0.001f)) != 0.0f)) {
				fTempPerm54 = (fSlow89 * fTempPerm53);
			}
			if (iSlow48 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow40 && (float((fTempPerm8 > 0.001f)) != 0.0f)) {
				fRec57[0] = (fSlow136 * ftbl0[(((int((65536.0f * (fRec54[0] + (fTempPerm54 + (fRec20[0] * fRec57[1]))))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow46 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow45 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow44 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow43 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow41 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow40 && (float((fTempPerm8 > 0.001f)) != 0.0f)) {
				fRec63[0] = ((iSlow140)?0.0f:min(fSlow96, (fRec63[1] + 1.0f)));
				iTempPerm55 = int((fRec63[0] < fSlow93));
				fRec62[0] = ((iSlow16)?(fSlow17 * ((iTempPerm55)?((int((fRec63[0] < 0.0f)))?0.0f:((iTempPerm55)?(fSlow99 * fRec63[0]):1.0f)):((int((fRec63[0] < fSlow96)))?((fSlow144 * (fRec63[0] - fSlow93)) + 1.0f):fSlow143))):fRec62[1]);
				fRec64[0] = ((iSlow142)?0.0f:min(fSlow100, (fRec64[1] + 1.0f)));
				fTempPerm56 = ((int((fRec64[0] < 0.0f)))?fRec62[0]:((int((fRec64[0] < fSlow100)))?(fRec62[0] + (fSlow101 * (0 - (fRec64[0] * fRec62[0])))):0.0f));
				fbargraph11 = fTempPerm56;
				fTempPerm57 = fTempPerm56;
			}
			if (iSlow41 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow40 && (float((fTempPerm8 > 0.001f)) != 0.0f)) {
				fTempPerm58 = (fTempPerm57 * ftbl0[(((int((65536.0f * fRec56[0])) % 65536) + 65536) % 65536)]);
			}
			if (iSlow40 && (float((fTempPerm8 > 0.001f)) != 0.0f)) {
				fRec61[0] = (fSlow134 * ftbl0[(((int((65536.0f * (fRec52[0] + ((fSlow102 * fTempPerm58) + (fRec17[0] * fRec61[1]))))) % 65536) + 65536) % 65536)]);
				fTempPerm59 = (fRec61[0] + fRec57[0]);
			}
			if (iSlow13 && (float((fTempPerm8 > 0.001f)) != 0.0f)) {
				fRec67[0] = ((iSlow140)?0.0f:min(fSlow109, (fRec67[1] + 1.0f)));
				iTempPerm60 = int((fRec67[0] < fSlow106));
				fRec66[0] = ((iSlow16)?(fSlow17 * ((iTempPerm60)?((int((fRec67[0] < 0.0f)))?0.0f:((iTempPerm60)?(fSlow112 * fRec67[0]):1.0f)):((int((fRec67[0] < fSlow109)))?((fSlow146 * (fRec67[0] - fSlow106)) + 1.0f):fSlow145))):fRec66[1]);
				fRec68[0] = ((iSlow142)?0.0f:min(fSlow113, (fRec68[1] + 1.0f)));
				fTempPerm61 = ((int((fRec68[0] < 0.0f)))?fRec66[0]:((int((fRec68[0] < fSlow113)))?(fRec66[0] + (fSlow114 * (0 - (fRec68[0] * fRec66[0])))):0.0f));
				fbargraph12 = fTempPerm61;
				fRec65[0] = (fSlow138 * ftbl0[(((int((65536.0f * (fRec56[0] + ((fRec23[0] * fRec65[1]) + (fSlow115 * (fTempPerm61 * ftbl0[(((int((65536.0f * fRec52[0])) % 65536) + 65536) % 65536)])))))) % 65536) + 65536) % 65536)]);
				fTempPerm62 = ((fRec49[0] + fRec65[0]) + fRec53[0]);
			}
			if (iSlow47 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow46 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow45 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow44 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow43 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow42 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow41 && (float((fTempPerm8 > 0.001f)) != 0.0f)) {
				fRec71[0] = ((iSlow140)?0.0f:min(fSlow122, (fRec71[1] + 1.0f)));
				iTempPerm63 = int((fRec71[0] < fSlow119));
				fRec70[0] = ((iSlow16)?(fSlow17 * ((iTempPerm63)?((int((fRec71[0] < 0.0f)))?0.0f:((iTempPerm63)?(fSlow125 * fRec71[0]):1.0f)):((int((fRec71[0] < fSlow122)))?((fSlow148 * (fRec71[0] - fSlow119)) + 1.0f):fSlow147))):fRec70[1]);
				fRec72[0] = ((iSlow142)?0.0f:min(fSlow126, (fRec72[1] + 1.0f)));
				fTempPerm64 = ((int((fRec72[0] < 0.0f)))?fRec70[0]:((int((fRec72[0] < fSlow126)))?(fRec70[0] + (fSlow127 * (0 - (fRec72[0] * fRec70[0])))):0.0f));
				fbargraph13 = fTempPerm64;
				fTempPerm65 = fTempPerm64;
			}
			if (iSlow45 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow44 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow41 && (float((fTempPerm8 > 0.001f)) != 0.0f)) {
				fTempPerm66 = (fTempPerm65 * ftbl0[(((int((65536.0f * fRec54[0])) % 65536) + 65536) % 65536)]);
				fTempPerm67 = (fSlow53 * fTempPerm53);
			}
			if (iSlow45 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow41 && (float((fTempPerm8 > 0.001f)) != 0.0f)) {
				fTempPerm68 = (fTempPerm67 + (fSlow66 * fTempPerm66));
			}
			if (iSlow41 && (float((fTempPerm8 > 0.001f)) != 0.0f)) {
				fRec69[0] = (fSlow134 * ftbl0[(((int((65536.0f * (fRec52[0] + ((fRec17[0] * fRec69[1]) + (fSlow88 * (fTempPerm68 + (fSlow72 * fTempPerm58))))))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow47 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow46 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow43 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow42 && (float((fTempPerm8 > 0.001f)) != 0.0f)) {
				fTempPerm69 = (fTempPerm65 * ftbl0[(((int((65536.0f * (fRec54[0] + fTempPerm54))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow47 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow46 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow42 && (float((fTempPerm8 > 0.001f)) != 0.0f)) {
				fTempPerm70 = (fSlow128 * fTempPerm69);
			}
			if (iSlow47 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow42 && (float((fTempPerm8 > 0.001f)) != 0.0f)) {
				fRec73[0] = (fSlow138 * ftbl0[(((int((65536.0f * (fRec56[0] + (fTempPerm70 + (fRec23[0] * fRec73[1]))))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow42 && (float((fTempPerm8 > 0.001f)) != 0.0f)) {
				fRec74[0] = (fSlow134 * ftbl0[(((int((65536.0f * (fRec52[0] + (fTempPerm70 + (fRec17[0] * fRec74[1]))))) % 65536) + 65536) % 65536)]);
				fTempPerm71 = (fRec74[0] + fRec73[0]);
			}
			if (iSlow43 && (float((fTempPerm8 > 0.001f)) != 0.0f)) {
				fRec75[0] = (fSlow134 * ftbl0[(((int((65536.0f * (fRec52[0] + ((fRec17[0] * fRec75[1]) + (fSlow88 * ((fSlow66 * fTempPerm69) + (fSlow72 * (fTempPerm57 * ftbl0[(((int((65536.0f * (fRec56[0] + fTempPerm54))) % 65536) + 65536) % 65536)])))))))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow44 && (float((fTempPerm8 > 0.001f)) != 0.0f)) {
				fRec76[0] = (fSlow134 * ftbl0[(((int((65536.0f * (fRec52[0] + ((fRec17[0] * fRec76[1]) + (fSlow88 * (fTempPerm67 + (fSlow72 * (fTempPerm57 * ftbl0[(((int((65536.0f * (fRec56[0] + (fSlow128 * fTempPerm66)))) % 65536) + 65536) % 65536)])))))))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow45 && (float((fTempPerm8 > 0.001f)) != 0.0f)) {
				fRec77[0] = (fSlow134 * ftbl0[(((int((65536.0f * (fRec52[0] + ((fRec17[0] * fRec77[1]) + (fSlow102 * (fTempPerm57 * ftbl0[(((int((65536.0f * (fRec56[0] + (fSlow88 * fTempPerm68)))) % 65536) + 65536) % 65536)])))))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow46 && (float((fTempPerm8 > 0.001f)) != 0.0f)) {
				fRec78[0] = (fSlow134 * ftbl0[(((int((65536.0f * (fRec52[0] + ((fRec17[0] * fRec78[1]) + (fSlow102 * (fTempPerm57 * ftbl0[(((int((65536.0f * (fRec56[0] + fTempPerm70))) % 65536) + 65536) % 65536)])))))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow47 && (float((fTempPerm8 > 0.001f)) != 0.0f)) {
				fTempPerm72 = (fRec73[0] + fRec51[0]);
			}
			if (iSlow48 && (float((fTempPerm8 > 0.001f)) != 0.0f)) {
				fRec79[0] = (fSlow134 * ftbl0[(((int((65536.0f * (fRec52[0] + (fTempPerm54 + (fRec17[0] * fRec79[1]))))) % 65536) + 65536) % 65536)]);
				fRec80[0] = (fSlow138 * ftbl0[(((int((65536.0f * (fRec56[0] + (fTempPerm54 + (fRec23[0] * fRec80[1]))))) % 65536) + 65536) % 65536)]);
				fTempPerm73 = (fRec80[0] + (fRec57[0] + fRec79[0]));
			}
			if ((float((fTempPerm8 > 0.001f)) != 0.0f)) {
				fTempPerm74 = (faustpower<2>(fTempPerm8) * ((fTempPerm73 + (fTempPerm72 + (fRec78[0] + (fRec77[0] + (fRec76[0] + (fRec75[0] + (fTempPerm71 + (fRec69[0] + (fTempPerm62 + fTempPerm59))))))))) + fTempPerm50));
			}
			if (iSlow48 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow47 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow46 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow45 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow44 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow43 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow42 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow41 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow13 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow40 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow12 && (float((fTempPerm12 > 0.001f)) != 0.0f)) {
				fRec82[0] = (fSlow150 + (fRec82[1] - floorf((fSlow150 + fRec82[1]))));
			}
			if (iSlow13 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow12 && (float((fTempPerm12 > 0.001f)) != 0.0f)) {
				fRec81[0] = (fSlow152 * ftbl0[(((int((65536.0f * (fRec82[0] + (fRec4[0] * fRec81[1])))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow48 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow47 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow46 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow45 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow44 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow43 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow42 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow41 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow13 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow40 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow12 && (float((fTempPerm12 > 0.001f)) != 0.0f)) {
				fRec84[0] = (fSlow153 + (fRec84[1] - floorf((fSlow153 + fRec84[1]))));
			}
			if (iSlow47 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow12 && (float((fTempPerm12 > 0.001f)) != 0.0f)) {
				fRec83[0] = (fSlow154 * ftbl0[(((int((65536.0f * (fRec84[0] + (fRec17[0] * fRec83[1])))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow48 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow47 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow46 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow45 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow44 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow43 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow42 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow41 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow13 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow40 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow12 && (float((fTempPerm12 > 0.001f)) != 0.0f)) {
				fRec86[0] = (fSlow155 + (fRec86[1] - floorf((fSlow155 + fRec86[1]))));
			}
			if (iSlow13 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow12 && (float((fTempPerm12 > 0.001f)) != 0.0f)) {
				fRec85[0] = (fSlow156 * ftbl0[(((int((65536.0f * (fRec86[0] + (fRec20[0] * fRec85[1])))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow48 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow47 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow46 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow45 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow44 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow43 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow42 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow41 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow13 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow40 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow12 && (float((fTempPerm12 > 0.001f)) != 0.0f)) {
				fRec88[0] = (fSlow157 + (fRec88[1] - floorf((fSlow157 + fRec88[1]))));
			}
			if (iSlow12 && (float((fTempPerm12 > 0.001f)) != 0.0f)) {
				fRec87[0] = (fSlow158 * ftbl0[(((int((65536.0f * (fRec88[0] + (fRec23[0] * fRec87[1])))) % 65536) + 65536) % 65536)]);
				fTempPerm75 = (fRec87[0] + (fRec85[0] + (fRec83[0] + fRec81[0])));
			}
			if (iSlow48 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow47 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow46 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow45 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow44 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow43 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow42 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow41 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow40 && (float((fTempPerm12 > 0.001f)) != 0.0f)) {
				fRec91[0] = ((iSlow160)?0.0f:min(fSlow80, (fRec91[1] + 1.0f)));
				iTempPerm76 = int((fRec91[0] < fSlow77));
				fRec90[0] = ((iSlow21)?(fSlow22 * ((iTempPerm76)?((int((fRec91[0] < 0.0f)))?0.0f:((iTempPerm76)?(fSlow84 * fRec91[0]):1.0f)):((int((fRec91[0] < fSlow80)))?((fSlow161 * (fRec91[0] - fSlow77)) + 1.0f):fSlow159))):fRec90[1]);
				fRec92[0] = ((iSlow162)?0.0f:min(fSlow85, (fRec92[1] + 1.0f)));
				fTempPerm77 = ((int((fRec92[0] < 0.0f)))?fRec90[0]:((int((fRec92[0] < fSlow85)))?(fRec90[0] + (fSlow87 * (0 - (fRec92[0] * fRec90[0])))):0.0f));
				fbargraph14 = fTempPerm77;
				fTempPerm78 = (fTempPerm77 * ftbl0[(((int((65536.0f * fRec82[0])) % 65536) + 65536) % 65536)]);
			}
			if (iSlow48 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow47 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow46 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow43 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow42 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow40 && (float((fTempPerm12 > 0.001f)) != 0.0f)) {
				fTempPerm79 = (fSlow89 * fTempPerm78);
			}
			if (iSlow48 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow40 && (float((fTempPerm12 > 0.001f)) != 0.0f)) {
				fRec89[0] = (fSlow156 * ftbl0[(((int((65536.0f * (fRec86[0] + (fTempPerm79 + (fRec20[0] * fRec89[1]))))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow46 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow45 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow44 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow43 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow41 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow40 && (float((fTempPerm12 > 0.001f)) != 0.0f)) {
				fRec95[0] = ((iSlow160)?0.0f:min(fSlow96, (fRec95[1] + 1.0f)));
				iTempPerm80 = int((fRec95[0] < fSlow93));
				fRec94[0] = ((iSlow21)?(fSlow22 * ((iTempPerm80)?((int((fRec95[0] < 0.0f)))?0.0f:((iTempPerm80)?(fSlow99 * fRec95[0]):1.0f)):((int((fRec95[0] < fSlow96)))?((fSlow164 * (fRec95[0] - fSlow93)) + 1.0f):fSlow163))):fRec94[1]);
				fRec96[0] = ((iSlow162)?0.0f:min(fSlow100, (fRec96[1] + 1.0f)));
				fTempPerm81 = ((int((fRec96[0] < 0.0f)))?fRec94[0]:((int((fRec96[0] < fSlow100)))?(fRec94[0] + (fSlow101 * (0 - (fRec96[0] * fRec94[0])))):0.0f));
				fbargraph15 = fTempPerm81;
				fTempPerm82 = fTempPerm81;
			}
			if (iSlow41 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow40 && (float((fTempPerm12 > 0.001f)) != 0.0f)) {
				fTempPerm83 = (fTempPerm82 * ftbl0[(((int((65536.0f * fRec88[0])) % 65536) + 65536) % 65536)]);
			}
			if (iSlow40 && (float((fTempPerm12 > 0.001f)) != 0.0f)) {
				fRec93[0] = (fSlow154 * ftbl0[(((int((65536.0f * (fRec84[0] + ((fSlow102 * fTempPerm83) + (fRec17[0] * fRec93[1]))))) % 65536) + 65536) % 65536)]);
				fTempPerm84 = (fRec93[0] + fRec89[0]);
			}
			if (iSlow13 && (float((fTempPerm12 > 0.001f)) != 0.0f)) {
				fRec99[0] = ((iSlow160)?0.0f:min(fSlow109, (fRec99[1] + 1.0f)));
				iTempPerm85 = int((fRec99[0] < fSlow106));
				fRec98[0] = ((iSlow21)?(fSlow22 * ((iTempPerm85)?((int((fRec99[0] < 0.0f)))?0.0f:((iTempPerm85)?(fSlow112 * fRec99[0]):1.0f)):((int((fRec99[0] < fSlow109)))?((fSlow166 * (fRec99[0] - fSlow106)) + 1.0f):fSlow165))):fRec98[1]);
				fRec100[0] = ((iSlow162)?0.0f:min(fSlow113, (fRec100[1] + 1.0f)));
				fTempPerm86 = ((int((fRec100[0] < 0.0f)))?fRec98[0]:((int((fRec100[0] < fSlow113)))?(fRec98[0] + (fSlow114 * (0 - (fRec100[0] * fRec98[0])))):0.0f));
				fbargraph16 = fTempPerm86;
				fRec97[0] = (fSlow158 * ftbl0[(((int((65536.0f * (fRec88[0] + ((fRec23[0] * fRec97[1]) + (fSlow115 * (fTempPerm86 * ftbl0[(((int((65536.0f * fRec84[0])) % 65536) + 65536) % 65536)])))))) % 65536) + 65536) % 65536)]);
				fTempPerm87 = ((fRec81[0] + fRec97[0]) + fRec85[0]);
			}
			if (iSlow47 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow46 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow45 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow44 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow43 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow42 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow41 && (float((fTempPerm12 > 0.001f)) != 0.0f)) {
				fRec103[0] = ((iSlow160)?0.0f:min(fSlow122, (fRec103[1] + 1.0f)));
				iTempPerm88 = int((fRec103[0] < fSlow119));
				fRec102[0] = ((iSlow21)?(fSlow22 * ((iTempPerm88)?((int((fRec103[0] < 0.0f)))?0.0f:((iTempPerm88)?(fSlow125 * fRec103[0]):1.0f)):((int((fRec103[0] < fSlow122)))?((fSlow168 * (fRec103[0] - fSlow119)) + 1.0f):fSlow167))):fRec102[1]);
				fRec104[0] = ((iSlow162)?0.0f:min(fSlow126, (fRec104[1] + 1.0f)));
				fTempPerm89 = ((int((fRec104[0] < 0.0f)))?fRec102[0]:((int((fRec104[0] < fSlow126)))?(fRec102[0] + (fSlow127 * (0 - (fRec104[0] * fRec102[0])))):0.0f));
				fbargraph17 = fTempPerm89;
				fTempPerm90 = fTempPerm89;
			}
			if (iSlow45 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow44 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow41 && (float((fTempPerm12 > 0.001f)) != 0.0f)) {
				fTempPerm91 = (fTempPerm90 * ftbl0[(((int((65536.0f * fRec86[0])) % 65536) + 65536) % 65536)]);
				fTempPerm92 = (fSlow53 * fTempPerm78);
			}
			if (iSlow45 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow41 && (float((fTempPerm12 > 0.001f)) != 0.0f)) {
				fTempPerm93 = (fTempPerm92 + (fSlow66 * fTempPerm91));
			}
			if (iSlow41 && (float((fTempPerm12 > 0.001f)) != 0.0f)) {
				fRec101[0] = (fSlow154 * ftbl0[(((int((65536.0f * (fRec84[0] + ((fRec17[0] * fRec101[1]) + (fSlow88 * (fTempPerm93 + (fSlow72 * fTempPerm83))))))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow47 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow46 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow43 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow42 && (float((fTempPerm12 > 0.001f)) != 0.0f)) {
				fTempPerm94 = (fTempPerm90 * ftbl0[(((int((65536.0f * (fRec86[0] + fTempPerm79))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow47 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow46 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow42 && (float((fTempPerm12 > 0.001f)) != 0.0f)) {
				fTempPerm95 = (fSlow128 * fTempPerm94);
			}
			if (iSlow47 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow42 && (float((fTempPerm12 > 0.001f)) != 0.0f)) {
				fRec105[0] = (fSlow158 * ftbl0[(((int((65536.0f * (fRec88[0] + (fTempPerm95 + (fRec23[0] * fRec105[1]))))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow42 && (float((fTempPerm12 > 0.001f)) != 0.0f)) {
				fRec106[0] = (fSlow154 * ftbl0[(((int((65536.0f * (fRec84[0] + (fTempPerm95 + (fRec17[0] * fRec106[1]))))) % 65536) + 65536) % 65536)]);
				fTempPerm96 = (fRec106[0] + fRec105[0]);
			}
			if (iSlow43 && (float((fTempPerm12 > 0.001f)) != 0.0f)) {
				fRec107[0] = (fSlow154 * ftbl0[(((int((65536.0f * (fRec84[0] + ((fRec17[0] * fRec107[1]) + (fSlow88 * ((fSlow66 * fTempPerm94) + (fSlow72 * (fTempPerm82 * ftbl0[(((int((65536.0f * (fRec88[0] + fTempPerm79))) % 65536) + 65536) % 65536)])))))))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow44 && (float((fTempPerm12 > 0.001f)) != 0.0f)) {
				fRec108[0] = (fSlow154 * ftbl0[(((int((65536.0f * (fRec84[0] + ((fRec17[0] * fRec108[1]) + (fSlow88 * (fTempPerm92 + (fSlow72 * (fTempPerm82 * ftbl0[(((int((65536.0f * (fRec88[0] + (fSlow128 * fTempPerm91)))) % 65536) + 65536) % 65536)])))))))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow45 && (float((fTempPerm12 > 0.001f)) != 0.0f)) {
				fRec109[0] = (fSlow154 * ftbl0[(((int((65536.0f * (fRec84[0] + ((fRec17[0] * fRec109[1]) + (fSlow102 * (fTempPerm82 * ftbl0[(((int((65536.0f * (fRec88[0] + (fSlow88 * fTempPerm93)))) % 65536) + 65536) % 65536)])))))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow46 && (float((fTempPerm12 > 0.001f)) != 0.0f)) {
				fRec110[0] = (fSlow154 * ftbl0[(((int((65536.0f * (fRec84[0] + ((fRec17[0] * fRec110[1]) + (fSlow102 * (fTempPerm82 * ftbl0[(((int((65536.0f * (fRec88[0] + fTempPerm95))) % 65536) + 65536) % 65536)])))))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow47 && (float((fTempPerm12 > 0.001f)) != 0.0f)) {
				fTempPerm97 = (fRec105[0] + fRec83[0]);
			}
			if (iSlow48 && (float((fTempPerm12 > 0.001f)) != 0.0f)) {
				fRec111[0] = (fSlow154 * ftbl0[(((int((65536.0f * (fRec84[0] + (fTempPerm79 + (fRec17[0] * fRec111[1]))))) % 65536) + 65536) % 65536)]);
				fRec112[0] = (fSlow158 * ftbl0[(((int((65536.0f * (fRec88[0] + (fTempPerm79 + (fRec23[0] * fRec112[1]))))) % 65536) + 65536) % 65536)]);
				fTempPerm98 = (fRec112[0] + (fRec89[0] + fRec111[0]));
			}
			if ((float((fTempPerm12 > 0.001f)) != 0.0f)) {
				fTempPerm99 = (faustpower<2>(fTempPerm12) * ((fTempPerm98 + (fTempPerm97 + (fRec110[0] + (fRec109[0] + (fRec108[0] + (fRec107[0] + (fTempPerm96 + (fRec101[0] + (fTempPerm87 + fTempPerm84))))))))) + fTempPerm75));
			}
			if (iSlow48 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow47 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow46 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow45 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow44 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow43 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow42 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow41 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow13 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow40 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow12 && (float((fTempPerm16 > 0.001f)) != 0.0f)) {
				fRec114[0] = (fSlow170 + (fRec114[1] - floorf((fSlow170 + fRec114[1]))));
			}
			if (iSlow13 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow12 && (float((fTempPerm16 > 0.001f)) != 0.0f)) {
				fRec113[0] = (fSlow172 * ftbl0[(((int((65536.0f * (fRec114[0] + (fRec4[0] * fRec113[1])))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow48 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow47 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow46 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow45 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow44 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow43 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow42 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow41 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow13 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow40 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow12 && (float((fTempPerm16 > 0.001f)) != 0.0f)) {
				fRec116[0] = (fSlow173 + (fRec116[1] - floorf((fSlow173 + fRec116[1]))));
			}
			if (iSlow47 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow12 && (float((fTempPerm16 > 0.001f)) != 0.0f)) {
				fRec115[0] = (fSlow174 * ftbl0[(((int((65536.0f * (fRec116[0] + (fRec17[0] * fRec115[1])))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow48 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow47 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow46 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow45 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow44 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow43 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow42 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow41 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow13 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow40 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow12 && (float((fTempPerm16 > 0.001f)) != 0.0f)) {
				fRec118[0] = (fSlow175 + (fRec118[1] - floorf((fSlow175 + fRec118[1]))));
			}
			if (iSlow13 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow12 && (float((fTempPerm16 > 0.001f)) != 0.0f)) {
				fRec117[0] = (fSlow176 * ftbl0[(((int((65536.0f * (fRec118[0] + (fRec20[0] * fRec117[1])))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow48 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow47 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow46 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow45 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow44 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow43 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow42 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow41 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow13 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow40 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow12 && (float((fTempPerm16 > 0.001f)) != 0.0f)) {
				fRec120[0] = (fSlow177 + (fRec120[1] - floorf((fSlow177 + fRec120[1]))));
			}
			if (iSlow12 && (float((fTempPerm16 > 0.001f)) != 0.0f)) {
				fRec119[0] = (fSlow178 * ftbl0[(((int((65536.0f * (fRec120[0] + (fRec23[0] * fRec119[1])))) % 65536) + 65536) % 65536)]);
				fTempPerm100 = (fRec119[0] + (fRec117[0] + (fRec115[0] + fRec113[0])));
			}
			if (iSlow48 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow47 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow46 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow45 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow44 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow43 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow42 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow41 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow40 && (float((fTempPerm16 > 0.001f)) != 0.0f)) {
				fRec123[0] = ((iSlow180)?0.0f:min(fSlow80, (fRec123[1] + 1.0f)));
				iTempPerm101 = int((fRec123[0] < fSlow77));
				fRec122[0] = ((iSlow26)?(fSlow27 * ((iTempPerm101)?((int((fRec123[0] < 0.0f)))?0.0f:((iTempPerm101)?(fSlow84 * fRec123[0]):1.0f)):((int((fRec123[0] < fSlow80)))?((fSlow181 * (fRec123[0] - fSlow77)) + 1.0f):fSlow179))):fRec122[1]);
				fRec124[0] = ((iSlow182)?0.0f:min(fSlow85, (fRec124[1] + 1.0f)));
				fTempPerm102 = ((int((fRec124[0] < 0.0f)))?fRec122[0]:((int((fRec124[0] < fSlow85)))?(fRec122[0] + (fSlow87 * (0 - (fRec124[0] * fRec122[0])))):0.0f));
				fbargraph18 = fTempPerm102;
				fTempPerm103 = (fTempPerm102 * ftbl0[(((int((65536.0f * fRec114[0])) % 65536) + 65536) % 65536)]);
			}
			if (iSlow48 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow47 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow46 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow43 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow42 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow40 && (float((fTempPerm16 > 0.001f)) != 0.0f)) {
				fTempPerm104 = (fSlow89 * fTempPerm103);
			}
			if (iSlow48 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow40 && (float((fTempPerm16 > 0.001f)) != 0.0f)) {
				fRec121[0] = (fSlow176 * ftbl0[(((int((65536.0f * (fRec118[0] + (fTempPerm104 + (fRec20[0] * fRec121[1]))))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow46 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow45 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow44 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow43 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow41 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow40 && (float((fTempPerm16 > 0.001f)) != 0.0f)) {
				fRec127[0] = ((iSlow180)?0.0f:min(fSlow96, (fRec127[1] + 1.0f)));
				iTempPerm105 = int((fRec127[0] < fSlow93));
				fRec126[0] = ((iSlow26)?(fSlow27 * ((iTempPerm105)?((int((fRec127[0] < 0.0f)))?0.0f:((iTempPerm105)?(fSlow99 * fRec127[0]):1.0f)):((int((fRec127[0] < fSlow96)))?((fSlow184 * (fRec127[0] - fSlow93)) + 1.0f):fSlow183))):fRec126[1]);
				fRec128[0] = ((iSlow182)?0.0f:min(fSlow100, (fRec128[1] + 1.0f)));
				fTempPerm106 = ((int((fRec128[0] < 0.0f)))?fRec126[0]:((int((fRec128[0] < fSlow100)))?(fRec126[0] + (fSlow101 * (0 - (fRec128[0] * fRec126[0])))):0.0f));
				fbargraph19 = fTempPerm106;
				fTempPerm107 = fTempPerm106;
			}
			if (iSlow41 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow40 && (float((fTempPerm16 > 0.001f)) != 0.0f)) {
				fTempPerm108 = (fTempPerm107 * ftbl0[(((int((65536.0f * fRec120[0])) % 65536) + 65536) % 65536)]);
			}
			if (iSlow40 && (float((fTempPerm16 > 0.001f)) != 0.0f)) {
				fRec125[0] = (fSlow174 * ftbl0[(((int((65536.0f * (fRec116[0] + ((fSlow102 * fTempPerm108) + (fRec17[0] * fRec125[1]))))) % 65536) + 65536) % 65536)]);
				fTempPerm109 = (fRec125[0] + fRec121[0]);
			}
			if (iSlow13 && (float((fTempPerm16 > 0.001f)) != 0.0f)) {
				fRec131[0] = ((iSlow180)?0.0f:min(fSlow109, (fRec131[1] + 1.0f)));
				iTempPerm110 = int((fRec131[0] < fSlow106));
				fRec130[0] = ((iSlow26)?(fSlow27 * ((iTempPerm110)?((int((fRec131[0] < 0.0f)))?0.0f:((iTempPerm110)?(fSlow112 * fRec131[0]):1.0f)):((int((fRec131[0] < fSlow109)))?((fSlow186 * (fRec131[0] - fSlow106)) + 1.0f):fSlow185))):fRec130[1]);
				fRec132[0] = ((iSlow182)?0.0f:min(fSlow113, (fRec132[1] + 1.0f)));
				fTempPerm111 = ((int((fRec132[0] < 0.0f)))?fRec130[0]:((int((fRec132[0] < fSlow113)))?(fRec130[0] + (fSlow114 * (0 - (fRec132[0] * fRec130[0])))):0.0f));
				fbargraph20 = fTempPerm111;
				fRec129[0] = (fSlow178 * ftbl0[(((int((65536.0f * (fRec120[0] + ((fRec23[0] * fRec129[1]) + (fSlow115 * (fTempPerm111 * ftbl0[(((int((65536.0f * fRec116[0])) % 65536) + 65536) % 65536)])))))) % 65536) + 65536) % 65536)]);
				fTempPerm112 = ((fRec113[0] + fRec129[0]) + fRec117[0]);
			}
			if (iSlow47 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow46 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow45 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow44 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow43 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow42 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow41 && (float((fTempPerm16 > 0.001f)) != 0.0f)) {
				fRec135[0] = ((iSlow180)?0.0f:min(fSlow122, (fRec135[1] + 1.0f)));
				iTempPerm113 = int((fRec135[0] < fSlow119));
				fRec134[0] = ((iSlow26)?(fSlow27 * ((iTempPerm113)?((int((fRec135[0] < 0.0f)))?0.0f:((iTempPerm113)?(fSlow125 * fRec135[0]):1.0f)):((int((fRec135[0] < fSlow122)))?((fSlow188 * (fRec135[0] - fSlow119)) + 1.0f):fSlow187))):fRec134[1]);
				fRec136[0] = ((iSlow182)?0.0f:min(fSlow126, (fRec136[1] + 1.0f)));
				fTempPerm114 = ((int((fRec136[0] < 0.0f)))?fRec134[0]:((int((fRec136[0] < fSlow126)))?(fRec134[0] + (fSlow127 * (0 - (fRec136[0] * fRec134[0])))):0.0f));
				fbargraph21 = fTempPerm114;
				fTempPerm115 = fTempPerm114;
			}
			if (iSlow45 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow44 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow41 && (float((fTempPerm16 > 0.001f)) != 0.0f)) {
				fTempPerm116 = (fTempPerm115 * ftbl0[(((int((65536.0f * fRec118[0])) % 65536) + 65536) % 65536)]);
				fTempPerm117 = (fSlow53 * fTempPerm103);
			}
			if (iSlow45 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow41 && (float((fTempPerm16 > 0.001f)) != 0.0f)) {
				fTempPerm118 = (fTempPerm117 + (fSlow66 * fTempPerm116));
			}
			if (iSlow41 && (float((fTempPerm16 > 0.001f)) != 0.0f)) {
				fRec133[0] = (fSlow174 * ftbl0[(((int((65536.0f * (fRec116[0] + ((fRec17[0] * fRec133[1]) + (fSlow88 * (fTempPerm118 + (fSlow72 * fTempPerm108))))))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow47 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow46 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow43 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow42 && (float((fTempPerm16 > 0.001f)) != 0.0f)) {
				fTempPerm119 = (fTempPerm115 * ftbl0[(((int((65536.0f * (fRec118[0] + fTempPerm104))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow47 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow46 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow42 && (float((fTempPerm16 > 0.001f)) != 0.0f)) {
				fTempPerm120 = (fSlow128 * fTempPerm119);
			}
			if (iSlow47 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow42 && (float((fTempPerm16 > 0.001f)) != 0.0f)) {
				fRec137[0] = (fSlow178 * ftbl0[(((int((65536.0f * (fRec120[0] + (fTempPerm120 + (fRec23[0] * fRec137[1]))))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow42 && (float((fTempPerm16 > 0.001f)) != 0.0f)) {
				fRec138[0] = (fSlow174 * ftbl0[(((int((65536.0f * (fRec116[0] + (fTempPerm120 + (fRec17[0] * fRec138[1]))))) % 65536) + 65536) % 65536)]);
				fTempPerm121 = (fRec138[0] + fRec137[0]);
			}
			if (iSlow43 && (float((fTempPerm16 > 0.001f)) != 0.0f)) {
				fRec139[0] = (fSlow174 * ftbl0[(((int((65536.0f * (fRec116[0] + ((fRec17[0] * fRec139[1]) + (fSlow88 * ((fSlow66 * fTempPerm119) + (fSlow72 * (fTempPerm107 * ftbl0[(((int((65536.0f * (fRec120[0] + fTempPerm104))) % 65536) + 65536) % 65536)])))))))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow44 && (float((fTempPerm16 > 0.001f)) != 0.0f)) {
				fRec140[0] = (fSlow174 * ftbl0[(((int((65536.0f * (fRec116[0] + ((fRec17[0] * fRec140[1]) + (fSlow88 * (fTempPerm117 + (fSlow72 * (fTempPerm107 * ftbl0[(((int((65536.0f * (fRec120[0] + (fSlow128 * fTempPerm116)))) % 65536) + 65536) % 65536)])))))))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow45 && (float((fTempPerm16 > 0.001f)) != 0.0f)) {
				fRec141[0] = (fSlow174 * ftbl0[(((int((65536.0f * (fRec116[0] + ((fRec17[0] * fRec141[1]) + (fSlow102 * (fTempPerm107 * ftbl0[(((int((65536.0f * (fRec120[0] + (fSlow88 * fTempPerm118)))) % 65536) + 65536) % 65536)])))))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow46 && (float((fTempPerm16 > 0.001f)) != 0.0f)) {
				fRec142[0] = (fSlow174 * ftbl0[(((int((65536.0f * (fRec116[0] + ((fRec17[0] * fRec142[1]) + (fSlow102 * (fTempPerm107 * ftbl0[(((int((65536.0f * (fRec120[0] + fTempPerm120))) % 65536) + 65536) % 65536)])))))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow47 && (float((fTempPerm16 > 0.001f)) != 0.0f)) {
				fTempPerm122 = (fRec137[0] + fRec115[0]);
			}
			if (iSlow48 && (float((fTempPerm16 > 0.001f)) != 0.0f)) {
				fRec143[0] = (fSlow174 * ftbl0[(((int((65536.0f * (fRec116[0] + (fTempPerm104 + (fRec17[0] * fRec143[1]))))) % 65536) + 65536) % 65536)]);
				fRec144[0] = (fSlow178 * ftbl0[(((int((65536.0f * (fRec120[0] + (fTempPerm104 + (fRec23[0] * fRec144[1]))))) % 65536) + 65536) % 65536)]);
				fTempPerm123 = (fRec144[0] + (fRec121[0] + fRec143[0]));
			}
			if ((float((fTempPerm16 > 0.001f)) != 0.0f)) {
				fTempPerm124 = (faustpower<2>(fTempPerm16) * ((fTempPerm123 + (fTempPerm122 + (fRec142[0] + (fRec141[0] + (fRec140[0] + (fRec139[0] + (fTempPerm121 + (fRec133[0] + (fTempPerm112 + fTempPerm109))))))))) + fTempPerm100));
			}
			if (iSlow48 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow47 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow46 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow45 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow44 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow43 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow42 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow41 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow13 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow40 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow12 && (float((fTempPerm20 > 0.001f)) != 0.0f)) {
				fRec146[0] = (fSlow190 + (fRec146[1] - floorf((fSlow190 + fRec146[1]))));
			}
			if (iSlow13 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow12 && (float((fTempPerm20 > 0.001f)) != 0.0f)) {
				fRec145[0] = (fSlow192 * ftbl0[(((int((65536.0f * (fRec146[0] + (fRec4[0] * fRec145[1])))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow48 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow47 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow46 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow45 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow44 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow43 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow42 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow41 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow13 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow40 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow12 && (float((fTempPerm20 > 0.001f)) != 0.0f)) {
				fRec148[0] = (fSlow193 + (fRec148[1] - floorf((fSlow193 + fRec148[1]))));
			}
			if (iSlow47 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow12 && (float((fTempPerm20 > 0.001f)) != 0.0f)) {
				fRec147[0] = (fSlow194 * ftbl0[(((int((65536.0f * (fRec148[0] + (fRec17[0] * fRec147[1])))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow48 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow47 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow46 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow45 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow44 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow43 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow42 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow41 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow13 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow40 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow12 && (float((fTempPerm20 > 0.001f)) != 0.0f)) {
				fRec150[0] = (fSlow195 + (fRec150[1] - floorf((fSlow195 + fRec150[1]))));
			}
			if (iSlow13 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow12 && (float((fTempPerm20 > 0.001f)) != 0.0f)) {
				fRec149[0] = (fSlow196 * ftbl0[(((int((65536.0f * (fRec150[0] + (fRec20[0] * fRec149[1])))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow48 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow47 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow46 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow45 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow44 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow43 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow42 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow41 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow13 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow40 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow12 && (float((fTempPerm20 > 0.001f)) != 0.0f)) {
				fRec152[0] = (fSlow197 + (fRec152[1] - floorf((fSlow197 + fRec152[1]))));
			}
			if (iSlow12 && (float((fTempPerm20 > 0.001f)) != 0.0f)) {
				fRec151[0] = (fSlow198 * ftbl0[(((int((65536.0f * (fRec152[0] + (fRec23[0] * fRec151[1])))) % 65536) + 65536) % 65536)]);
				fTempPerm125 = (fRec151[0] + (fRec149[0] + (fRec147[0] + fRec145[0])));
			}
			if (iSlow48 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow47 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow46 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow45 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow44 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow43 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow42 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow41 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow40 && (float((fTempPerm20 > 0.001f)) != 0.0f)) {
				fRec155[0] = ((iSlow200)?0.0f:min(fSlow80, (fRec155[1] + 1.0f)));
				iTempPerm126 = int((fRec155[0] < fSlow77));
				fRec154[0] = ((iSlow31)?(fSlow32 * ((iTempPerm126)?((int((fRec155[0] < 0.0f)))?0.0f:((iTempPerm126)?(fSlow84 * fRec155[0]):1.0f)):((int((fRec155[0] < fSlow80)))?((fSlow201 * (fRec155[0] - fSlow77)) + 1.0f):fSlow199))):fRec154[1]);
				fRec156[0] = ((iSlow202)?0.0f:min(fSlow85, (fRec156[1] + 1.0f)));
				fTempPerm127 = ((int((fRec156[0] < 0.0f)))?fRec154[0]:((int((fRec156[0] < fSlow85)))?(fRec154[0] + (fSlow87 * (0 - (fRec156[0] * fRec154[0])))):0.0f));
				fbargraph22 = fTempPerm127;
				fTempPerm128 = (fTempPerm127 * ftbl0[(((int((65536.0f * fRec146[0])) % 65536) + 65536) % 65536)]);
			}
			if (iSlow48 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow47 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow46 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow43 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow42 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow40 && (float((fTempPerm20 > 0.001f)) != 0.0f)) {
				fTempPerm129 = (fSlow89 * fTempPerm128);
			}
			if (iSlow48 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow40 && (float((fTempPerm20 > 0.001f)) != 0.0f)) {
				fRec153[0] = (fSlow196 * ftbl0[(((int((65536.0f * (fRec150[0] + (fTempPerm129 + (fRec20[0] * fRec153[1]))))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow46 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow45 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow44 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow43 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow41 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow40 && (float((fTempPerm20 > 0.001f)) != 0.0f)) {
				fRec159[0] = ((iSlow200)?0.0f:min(fSlow96, (fRec159[1] + 1.0f)));
				iTempPerm130 = int((fRec159[0] < fSlow93));
				fRec158[0] = ((iSlow31)?(fSlow32 * ((iTempPerm130)?((int((fRec159[0] < 0.0f)))?0.0f:((iTempPerm130)?(fSlow99 * fRec159[0]):1.0f)):((int((fRec159[0] < fSlow96)))?((fSlow204 * (fRec159[0] - fSlow93)) + 1.0f):fSlow203))):fRec158[1]);
				fRec160[0] = ((iSlow202)?0.0f:min(fSlow100, (fRec160[1] + 1.0f)));
				fTempPerm131 = ((int((fRec160[0] < 0.0f)))?fRec158[0]:((int((fRec160[0] < fSlow100)))?(fRec158[0] + (fSlow101 * (0 - (fRec160[0] * fRec158[0])))):0.0f));
				fbargraph23 = fTempPerm131;
				fTempPerm132 = fTempPerm131;
			}
			if (iSlow41 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow40 && (float((fTempPerm20 > 0.001f)) != 0.0f)) {
				fTempPerm133 = (fTempPerm132 * ftbl0[(((int((65536.0f * fRec152[0])) % 65536) + 65536) % 65536)]);
			}
			if (iSlow40 && (float((fTempPerm20 > 0.001f)) != 0.0f)) {
				fRec157[0] = (fSlow194 * ftbl0[(((int((65536.0f * (fRec148[0] + ((fSlow102 * fTempPerm133) + (fRec17[0] * fRec157[1]))))) % 65536) + 65536) % 65536)]);
				fTempPerm134 = (fRec157[0] + fRec153[0]);
			}
			if (iSlow13 && (float((fTempPerm20 > 0.001f)) != 0.0f)) {
				fRec163[0] = ((iSlow200)?0.0f:min(fSlow109, (fRec163[1] + 1.0f)));
				iTempPerm135 = int((fRec163[0] < fSlow106));
				fRec162[0] = ((iSlow31)?(fSlow32 * ((iTempPerm135)?((int((fRec163[0] < 0.0f)))?0.0f:((iTempPerm135)?(fSlow112 * fRec163[0]):1.0f)):((int((fRec163[0] < fSlow109)))?((fSlow206 * (fRec163[0] - fSlow106)) + 1.0f):fSlow205))):fRec162[1]);
				fRec164[0] = ((iSlow202)?0.0f:min(fSlow113, (fRec164[1] + 1.0f)));
				fTempPerm136 = ((int((fRec164[0] < 0.0f)))?fRec162[0]:((int((fRec164[0] < fSlow113)))?(fRec162[0] + (fSlow114 * (0 - (fRec164[0] * fRec162[0])))):0.0f));
				fbargraph24 = fTempPerm136;
				fRec161[0] = (fSlow198 * ftbl0[(((int((65536.0f * (fRec152[0] + ((fRec23[0] * fRec161[1]) + (fSlow115 * (fTempPerm136 * ftbl0[(((int((65536.0f * fRec148[0])) % 65536) + 65536) % 65536)])))))) % 65536) + 65536) % 65536)]);
				fTempPerm137 = ((fRec145[0] + fRec161[0]) + fRec149[0]);
			}
			if (iSlow47 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow46 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow45 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow44 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow43 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow42 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow41 && (float((fTempPerm20 > 0.001f)) != 0.0f)) {
				fRec167[0] = ((iSlow200)?0.0f:min(fSlow122, (fRec167[1] + 1.0f)));
				iTempPerm138 = int((fRec167[0] < fSlow119));
				fRec166[0] = ((iSlow31)?(fSlow32 * ((iTempPerm138)?((int((fRec167[0] < 0.0f)))?0.0f:((iTempPerm138)?(fSlow125 * fRec167[0]):1.0f)):((int((fRec167[0] < fSlow122)))?((fSlow208 * (fRec167[0] - fSlow119)) + 1.0f):fSlow207))):fRec166[1]);
				fRec168[0] = ((iSlow202)?0.0f:min(fSlow126, (fRec168[1] + 1.0f)));
				fTempPerm139 = ((int((fRec168[0] < 0.0f)))?fRec166[0]:((int((fRec168[0] < fSlow126)))?(fRec166[0] + (fSlow127 * (0 - (fRec168[0] * fRec166[0])))):0.0f));
				fbargraph25 = fTempPerm139;
				fTempPerm140 = fTempPerm139;
			}
			if (iSlow45 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow44 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow41 && (float((fTempPerm20 > 0.001f)) != 0.0f)) {
				fTempPerm141 = (fTempPerm140 * ftbl0[(((int((65536.0f * fRec150[0])) % 65536) + 65536) % 65536)]);
				fTempPerm142 = (fSlow53 * fTempPerm128);
			}
			if (iSlow45 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow41 && (float((fTempPerm20 > 0.001f)) != 0.0f)) {
				fTempPerm143 = (fTempPerm142 + (fSlow66 * fTempPerm141));
			}
			if (iSlow41 && (float((fTempPerm20 > 0.001f)) != 0.0f)) {
				fRec165[0] = (fSlow194 * ftbl0[(((int((65536.0f * (fRec148[0] + ((fRec17[0] * fRec165[1]) + (fSlow88 * (fTempPerm143 + (fSlow72 * fTempPerm133))))))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow47 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow46 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow43 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow42 && (float((fTempPerm20 > 0.001f)) != 0.0f)) {
				fTempPerm144 = (fTempPerm140 * ftbl0[(((int((65536.0f * (fRec150[0] + fTempPerm129))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow47 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow46 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow42 && (float((fTempPerm20 > 0.001f)) != 0.0f)) {
				fTempPerm145 = (fSlow128 * fTempPerm144);
			}
			if (iSlow47 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow42 && (float((fTempPerm20 > 0.001f)) != 0.0f)) {
				fRec169[0] = (fSlow198 * ftbl0[(((int((65536.0f * (fRec152[0] + (fTempPerm145 + (fRec23[0] * fRec169[1]))))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow42 && (float((fTempPerm20 > 0.001f)) != 0.0f)) {
				fRec170[0] = (fSlow194 * ftbl0[(((int((65536.0f * (fRec148[0] + (fTempPerm145 + (fRec17[0] * fRec170[1]))))) % 65536) + 65536) % 65536)]);
				fTempPerm146 = (fRec170[0] + fRec169[0]);
			}
			if (iSlow43 && (float((fTempPerm20 > 0.001f)) != 0.0f)) {
				fRec171[0] = (fSlow194 * ftbl0[(((int((65536.0f * (fRec148[0] + ((fRec17[0] * fRec171[1]) + (fSlow88 * ((fSlow66 * fTempPerm144) + (fSlow72 * (fTempPerm132 * ftbl0[(((int((65536.0f * (fRec152[0] + fTempPerm129))) % 65536) + 65536) % 65536)])))))))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow44 && (float((fTempPerm20 > 0.001f)) != 0.0f)) {
				fRec172[0] = (fSlow194 * ftbl0[(((int((65536.0f * (fRec148[0] + ((fRec17[0] * fRec172[1]) + (fSlow88 * (fTempPerm142 + (fSlow72 * (fTempPerm132 * ftbl0[(((int((65536.0f * (fRec152[0] + (fSlow128 * fTempPerm141)))) % 65536) + 65536) % 65536)])))))))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow45 && (float((fTempPerm20 > 0.001f)) != 0.0f)) {
				fRec173[0] = (fSlow194 * ftbl0[(((int((65536.0f * (fRec148[0] + ((fRec17[0] * fRec173[1]) + (fSlow102 * (fTempPerm132 * ftbl0[(((int((65536.0f * (fRec152[0] + (fSlow88 * fTempPerm143)))) % 65536) + 65536) % 65536)])))))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow46 && (float((fTempPerm20 > 0.001f)) != 0.0f)) {
				fRec174[0] = (fSlow194 * ftbl0[(((int((65536.0f * (fRec148[0] + ((fRec17[0] * fRec174[1]) + (fSlow102 * (fTempPerm132 * ftbl0[(((int((65536.0f * (fRec152[0] + fTempPerm145))) % 65536) + 65536) % 65536)])))))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow47 && (float((fTempPerm20 > 0.001f)) != 0.0f)) {
				fTempPerm147 = (fRec169[0] + fRec147[0]);
			}
			if (iSlow48 && (float((fTempPerm20 > 0.001f)) != 0.0f)) {
				fRec175[0] = (fSlow194 * ftbl0[(((int((65536.0f * (fRec148[0] + (fTempPerm129 + (fRec17[0] * fRec175[1]))))) % 65536) + 65536) % 65536)]);
				fRec176[0] = (fSlow198 * ftbl0[(((int((65536.0f * (fRec152[0] + (fTempPerm129 + (fRec23[0] * fRec176[1]))))) % 65536) + 65536) % 65536)]);
				fTempPerm148 = (fRec176[0] + (fRec153[0] + fRec175[0]));
			}
			if ((float((fTempPerm20 > 0.001f)) != 0.0f)) {
				fTempPerm149 = (faustpower<2>(fTempPerm20) * ((fTempPerm148 + (fTempPerm147 + (fRec174[0] + (fRec173[0] + (fRec172[0] + (fRec171[0] + (fTempPerm146 + (fRec165[0] + (fTempPerm137 + fTempPerm134))))))))) + fTempPerm125));
			}
			if (iSlow48 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow47 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow46 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow45 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow44 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow43 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow42 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow41 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow13 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow40 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow12 && (float((fTempPerm24 > 0.001f)) != 0.0f)) {
				fRec178[0] = (fSlow210 + (fRec178[1] - floorf((fSlow210 + fRec178[1]))));
			}
			if (iSlow13 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow12 && (float((fTempPerm24 > 0.001f)) != 0.0f)) {
				fRec177[0] = (fSlow212 * ftbl0[(((int((65536.0f * (fRec178[0] + (fRec4[0] * fRec177[1])))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow48 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow47 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow46 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow45 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow44 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow43 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow42 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow41 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow13 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow40 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow12 && (float((fTempPerm24 > 0.001f)) != 0.0f)) {
				fRec180[0] = (fSlow213 + (fRec180[1] - floorf((fSlow213 + fRec180[1]))));
			}
			if (iSlow47 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow12 && (float((fTempPerm24 > 0.001f)) != 0.0f)) {
				fRec179[0] = (fSlow214 * ftbl0[(((int((65536.0f * (fRec180[0] + (fRec17[0] * fRec179[1])))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow48 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow47 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow46 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow45 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow44 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow43 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow42 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow41 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow13 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow40 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow12 && (float((fTempPerm24 > 0.001f)) != 0.0f)) {
				fRec182[0] = (fSlow215 + (fRec182[1] - floorf((fSlow215 + fRec182[1]))));
			}
			if (iSlow13 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow12 && (float((fTempPerm24 > 0.001f)) != 0.0f)) {
				fRec181[0] = (fSlow216 * ftbl0[(((int((65536.0f * (fRec182[0] + (fRec20[0] * fRec181[1])))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow48 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow47 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow46 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow45 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow44 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow43 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow42 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow41 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow13 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow40 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow12 && (float((fTempPerm24 > 0.001f)) != 0.0f)) {
				fRec184[0] = (fSlow217 + (fRec184[1] - floorf((fSlow217 + fRec184[1]))));
			}
			if (iSlow12 && (float((fTempPerm24 > 0.001f)) != 0.0f)) {
				fRec183[0] = (fSlow218 * ftbl0[(((int((65536.0f * (fRec184[0] + (fRec23[0] * fRec183[1])))) % 65536) + 65536) % 65536)]);
				fTempPerm150 = (fRec183[0] + (fRec181[0] + (fRec179[0] + fRec177[0])));
			}
			if (iSlow48 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow47 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow46 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow45 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow44 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow43 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow42 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow41 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow40 && (float((fTempPerm24 > 0.001f)) != 0.0f)) {
				fRec187[0] = ((iSlow220)?0.0f:min(fSlow80, (fRec187[1] + 1.0f)));
				iTempPerm151 = int((fRec187[0] < fSlow77));
				fRec186[0] = ((iSlow36)?(fSlow37 * ((iTempPerm151)?((int((fRec187[0] < 0.0f)))?0.0f:((iTempPerm151)?(fSlow84 * fRec187[0]):1.0f)):((int((fRec187[0] < fSlow80)))?((fSlow221 * (fRec187[0] - fSlow77)) + 1.0f):fSlow219))):fRec186[1]);
				fRec188[0] = ((iSlow222)?0.0f:min(fSlow85, (fRec188[1] + 1.0f)));
				fTempPerm152 = ((int((fRec188[0] < 0.0f)))?fRec186[0]:((int((fRec188[0] < fSlow85)))?(fRec186[0] + (fSlow87 * (0 - (fRec188[0] * fRec186[0])))):0.0f));
				fbargraph26 = fTempPerm152;
				fTempPerm153 = (fTempPerm152 * ftbl0[(((int((65536.0f * fRec178[0])) % 65536) + 65536) % 65536)]);
			}
			if (iSlow48 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow47 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow46 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow43 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow42 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow40 && (float((fTempPerm24 > 0.001f)) != 0.0f)) {
				fTempPerm154 = (fSlow89 * fTempPerm153);
			}
			if (iSlow48 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow40 && (float((fTempPerm24 > 0.001f)) != 0.0f)) {
				fRec185[0] = (fSlow216 * ftbl0[(((int((65536.0f * (fRec182[0] + (fTempPerm154 + (fRec20[0] * fRec185[1]))))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow46 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow45 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow44 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow43 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow41 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow40 && (float((fTempPerm24 > 0.001f)) != 0.0f)) {
				fRec191[0] = ((iSlow220)?0.0f:min(fSlow96, (fRec191[1] + 1.0f)));
				iTempPerm155 = int((fRec191[0] < fSlow93));
				fRec190[0] = ((iSlow36)?(fSlow37 * ((iTempPerm155)?((int((fRec191[0] < 0.0f)))?0.0f:((iTempPerm155)?(fSlow99 * fRec191[0]):1.0f)):((int((fRec191[0] < fSlow96)))?((fSlow224 * (fRec191[0] - fSlow93)) + 1.0f):fSlow223))):fRec190[1]);
				fRec192[0] = ((iSlow222)?0.0f:min(fSlow100, (fRec192[1] + 1.0f)));
				fTempPerm156 = ((int((fRec192[0] < 0.0f)))?fRec190[0]:((int((fRec192[0] < fSlow100)))?(fRec190[0] + (fSlow101 * (0 - (fRec192[0] * fRec190[0])))):0.0f));
				fbargraph27 = fTempPerm156;
				fTempPerm157 = fTempPerm156;
			}
			if (iSlow41 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow40 && (float((fTempPerm24 > 0.001f)) != 0.0f)) {
				fTempPerm158 = (fTempPerm157 * ftbl0[(((int((65536.0f * fRec184[0])) % 65536) + 65536) % 65536)]);
			}
			if (iSlow40 && (float((fTempPerm24 > 0.001f)) != 0.0f)) {
				fRec189[0] = (fSlow214 * ftbl0[(((int((65536.0f * (fRec180[0] + ((fSlow102 * fTempPerm158) + (fRec17[0] * fRec189[1]))))) % 65536) + 65536) % 65536)]);
				fTempPerm159 = (fRec189[0] + fRec185[0]);
			}
			if (iSlow13 && (float((fTempPerm24 > 0.001f)) != 0.0f)) {
				fRec195[0] = ((iSlow220)?0.0f:min(fSlow109, (fRec195[1] + 1.0f)));
				iTempPerm160 = int((fRec195[0] < fSlow106));
				fRec194[0] = ((iSlow36)?(fSlow37 * ((iTempPerm160)?((int((fRec195[0] < 0.0f)))?0.0f:((iTempPerm160)?(fSlow112 * fRec195[0]):1.0f)):((int((fRec195[0] < fSlow109)))?((fSlow226 * (fRec195[0] - fSlow106)) + 1.0f):fSlow225))):fRec194[1]);
				fRec196[0] = ((iSlow222)?0.0f:min(fSlow113, (fRec196[1] + 1.0f)));
				fTempPerm161 = ((int((fRec196[0] < 0.0f)))?fRec194[0]:((int((fRec196[0] < fSlow113)))?(fRec194[0] + (fSlow114 * (0 - (fRec196[0] * fRec194[0])))):0.0f));
				fbargraph28 = fTempPerm161;
				fRec193[0] = (fSlow218 * ftbl0[(((int((65536.0f * (fRec184[0] + ((fRec23[0] * fRec193[1]) + (fSlow115 * (fTempPerm161 * ftbl0[(((int((65536.0f * fRec180[0])) % 65536) + 65536) % 65536)])))))) % 65536) + 65536) % 65536)]);
				fTempPerm162 = ((fRec177[0] + fRec193[0]) + fRec181[0]);
			}
			if (iSlow47 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow46 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow45 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow44 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow43 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow42 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow41 && (float((fTempPerm24 > 0.001f)) != 0.0f)) {
				fRec199[0] = ((iSlow220)?0.0f:min(fSlow122, (fRec199[1] + 1.0f)));
				iTempPerm163 = int((fRec199[0] < fSlow119));
				fRec198[0] = ((iSlow36)?(fSlow37 * ((iTempPerm163)?((int((fRec199[0] < 0.0f)))?0.0f:((iTempPerm163)?(fSlow125 * fRec199[0]):1.0f)):((int((fRec199[0] < fSlow122)))?((fSlow228 * (fRec199[0] - fSlow119)) + 1.0f):fSlow227))):fRec198[1]);
				fRec200[0] = ((iSlow222)?0.0f:min(fSlow126, (fRec200[1] + 1.0f)));
				fTempPerm164 = ((int((fRec200[0] < 0.0f)))?fRec198[0]:((int((fRec200[0] < fSlow126)))?(fRec198[0] + (fSlow127 * (0 - (fRec200[0] * fRec198[0])))):0.0f));
				fbargraph29 = fTempPerm164;
				fTempPerm165 = fTempPerm164;
			}
			if (iSlow45 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow44 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow41 && (float((fTempPerm24 > 0.001f)) != 0.0f)) {
				fTempPerm166 = (fTempPerm165 * ftbl0[(((int((65536.0f * fRec182[0])) % 65536) + 65536) % 65536)]);
				fTempPerm167 = (fSlow53 * fTempPerm153);
			}
			if (iSlow45 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow41 && (float((fTempPerm24 > 0.001f)) != 0.0f)) {
				fTempPerm168 = (fTempPerm167 + (fSlow66 * fTempPerm166));
			}
			if (iSlow41 && (float((fTempPerm24 > 0.001f)) != 0.0f)) {
				fRec197[0] = (fSlow214 * ftbl0[(((int((65536.0f * (fRec180[0] + ((fRec17[0] * fRec197[1]) + (fSlow88 * (fTempPerm168 + (fSlow72 * fTempPerm158))))))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow47 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow46 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow43 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow42 && (float((fTempPerm24 > 0.001f)) != 0.0f)) {
				fTempPerm169 = (fTempPerm165 * ftbl0[(((int((65536.0f * (fRec182[0] + fTempPerm154))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow47 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow46 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow42 && (float((fTempPerm24 > 0.001f)) != 0.0f)) {
				fTempPerm170 = (fSlow128 * fTempPerm169);
			}
			if (iSlow47 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow42 && (float((fTempPerm24 > 0.001f)) != 0.0f)) {
				fRec201[0] = (fSlow218 * ftbl0[(((int((65536.0f * (fRec184[0] + (fTempPerm170 + (fRec23[0] * fRec201[1]))))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow42 && (float((fTempPerm24 > 0.001f)) != 0.0f)) {
				fRec202[0] = (fSlow214 * ftbl0[(((int((65536.0f * (fRec180[0] + (fTempPerm170 + (fRec17[0] * fRec202[1]))))) % 65536) + 65536) % 65536)]);
				fTempPerm171 = (fRec202[0] + fRec201[0]);
			}
			if (iSlow43 && (float((fTempPerm24 > 0.001f)) != 0.0f)) {
				fRec203[0] = (fSlow214 * ftbl0[(((int((65536.0f * (fRec180[0] + ((fRec17[0] * fRec203[1]) + (fSlow88 * ((fSlow66 * fTempPerm169) + (fSlow72 * (fTempPerm157 * ftbl0[(((int((65536.0f * (fRec184[0] + fTempPerm154))) % 65536) + 65536) % 65536)])))))))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow44 && (float((fTempPerm24 > 0.001f)) != 0.0f)) {
				fRec204[0] = (fSlow214 * ftbl0[(((int((65536.0f * (fRec180[0] + ((fRec17[0] * fRec204[1]) + (fSlow88 * (fTempPerm167 + (fSlow72 * (fTempPerm157 * ftbl0[(((int((65536.0f * (fRec184[0] + (fSlow128 * fTempPerm166)))) % 65536) + 65536) % 65536)])))))))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow45 && (float((fTempPerm24 > 0.001f)) != 0.0f)) {
				fRec205[0] = (fSlow214 * ftbl0[(((int((65536.0f * (fRec180[0] + ((fRec17[0] * fRec205[1]) + (fSlow102 * (fTempPerm157 * ftbl0[(((int((65536.0f * (fRec184[0] + (fSlow88 * fTempPerm168)))) % 65536) + 65536) % 65536)])))))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow46 && (float((fTempPerm24 > 0.001f)) != 0.0f)) {
				fRec206[0] = (fSlow214 * ftbl0[(((int((65536.0f * (fRec180[0] + ((fRec17[0] * fRec206[1]) + (fSlow102 * (fTempPerm157 * ftbl0[(((int((65536.0f * (fRec184[0] + fTempPerm170))) % 65536) + 65536) % 65536)])))))) % 65536) + 65536) % 65536)]);
			}
			if (iSlow47 && (float((fTempPerm24 > 0.001f)) != 0.0f)) {
				fTempPerm172 = (fRec201[0] + fRec179[0]);
			}
			if (iSlow48 && (float((fTempPerm24 > 0.001f)) != 0.0f)) {
				fRec207[0] = (fSlow214 * ftbl0[(((int((65536.0f * (fRec180[0] + (fTempPerm154 + (fRec17[0] * fRec207[1]))))) % 65536) + 65536) % 65536)]);
				fRec208[0] = (fSlow218 * ftbl0[(((int((65536.0f * (fRec184[0] + (fTempPerm154 + (fRec23[0] * fRec208[1]))))) % 65536) + 65536) % 65536)]);
				fTempPerm173 = (fRec208[0] + (fRec185[0] + fRec207[0]));
			}
			if ((float((fTempPerm24 > 0.001f)) != 0.0f)) {
				fTempPerm174 = (faustpower<2>(fTempPerm24) * ((fTempPerm173 + (fTempPerm172 + (fRec206[0] + (fRec205[0] + (fRec204[0] + (fRec203[0] + (fTempPerm171 + (fRec197[0] + (fTempPerm162 + fTempPerm159))))))))) + fTempPerm150));
			}
			output0[i] = (FAUSTFLOAT)(((((fTempPerm174 + fTempPerm149) + fTempPerm124) + fTempPerm99) + fTempPerm74) + fTempPerm49);
			// post processing
			if (iSlow48 && (float((fTempPerm24 > 0.001f)) != 0.0f)) {
				fRec208[1] = fRec208[0];
				fRec207[1] = fRec207[0];
			}
			if (iSlow46 && (float((fTempPerm24 > 0.001f)) != 0.0f)) {
				fRec206[1] = fRec206[0];
			}
			if (iSlow45 && (float((fTempPerm24 > 0.001f)) != 0.0f)) {
				fRec205[1] = fRec205[0];
			}
			if (iSlow44 && (float((fTempPerm24 > 0.001f)) != 0.0f)) {
				fRec204[1] = fRec204[0];
			}
			if (iSlow43 && (float((fTempPerm24 > 0.001f)) != 0.0f)) {
				fRec203[1] = fRec203[0];
			}
			if (iSlow42 && (float((fTempPerm24 > 0.001f)) != 0.0f)) {
				fRec202[1] = fRec202[0];
			}
			if (iSlow47 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow42 && (float((fTempPerm24 > 0.001f)) != 0.0f)) {
				fRec201[1] = fRec201[0];
			}
			if (iSlow41 && (float((fTempPerm24 > 0.001f)) != 0.0f)) {
				fRec197[1] = fRec197[0];
			}
			if (iSlow47 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow46 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow45 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow44 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow43 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow42 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow41 && (float((fTempPerm24 > 0.001f)) != 0.0f)) {
				fRec200[1] = fRec200[0];
				fRec198[1] = fRec198[0];
				fRec199[1] = fRec199[0];
			}
			if (iSlow13 && (float((fTempPerm24 > 0.001f)) != 0.0f)) {
				fRec193[1] = fRec193[0];
				fRec196[1] = fRec196[0];
				fRec194[1] = fRec194[0];
				fRec195[1] = fRec195[0];
			}
			if (iSlow40 && (float((fTempPerm24 > 0.001f)) != 0.0f)) {
				fRec189[1] = fRec189[0];
			}
			if (iSlow46 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow45 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow44 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow43 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow41 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow40 && (float((fTempPerm24 > 0.001f)) != 0.0f)) {
				fRec192[1] = fRec192[0];
				fRec190[1] = fRec190[0];
				fRec191[1] = fRec191[0];
			}
			if (iSlow48 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow40 && (float((fTempPerm24 > 0.001f)) != 0.0f)) {
				fRec185[1] = fRec185[0];
			}
			if (iSlow48 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow47 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow46 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow45 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow44 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow43 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow42 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow41 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow40 && (float((fTempPerm24 > 0.001f)) != 0.0f)) {
				fRec188[1] = fRec188[0];
				fRec186[1] = fRec186[0];
				fRec187[1] = fRec187[0];
			}
			if (iSlow12 && (float((fTempPerm24 > 0.001f)) != 0.0f)) {
				fRec183[1] = fRec183[0];
			}
			if (iSlow48 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow47 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow46 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow45 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow44 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow43 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow42 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow41 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow13 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow40 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow12 && (float((fTempPerm24 > 0.001f)) != 0.0f)) {
				fRec184[1] = fRec184[0];
			}
			if (iSlow13 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow12 && (float((fTempPerm24 > 0.001f)) != 0.0f)) {
				fRec181[1] = fRec181[0];
			}
			if (iSlow48 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow47 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow46 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow45 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow44 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow43 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow42 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow41 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow13 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow40 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow12 && (float((fTempPerm24 > 0.001f)) != 0.0f)) {
				fRec182[1] = fRec182[0];
			}
			if (iSlow47 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow12 && (float((fTempPerm24 > 0.001f)) != 0.0f)) {
				fRec179[1] = fRec179[0];
			}
			if (iSlow48 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow47 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow46 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow45 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow44 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow43 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow42 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow41 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow13 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow40 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow12 && (float((fTempPerm24 > 0.001f)) != 0.0f)) {
				fRec180[1] = fRec180[0];
			}
			if (iSlow13 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow12 && (float((fTempPerm24 > 0.001f)) != 0.0f)) {
				fRec177[1] = fRec177[0];
			}
			if (iSlow48 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow47 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow46 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow45 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow44 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow43 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow42 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow41 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow13 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow40 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow12 && (float((fTempPerm24 > 0.001f)) != 0.0f)) {
				fRec178[1] = fRec178[0];
			}
			if (iSlow48 && (float((fTempPerm20 > 0.001f)) != 0.0f)) {
				fRec176[1] = fRec176[0];
				fRec175[1] = fRec175[0];
			}
			if (iSlow46 && (float((fTempPerm20 > 0.001f)) != 0.0f)) {
				fRec174[1] = fRec174[0];
			}
			if (iSlow45 && (float((fTempPerm20 > 0.001f)) != 0.0f)) {
				fRec173[1] = fRec173[0];
			}
			if (iSlow44 && (float((fTempPerm20 > 0.001f)) != 0.0f)) {
				fRec172[1] = fRec172[0];
			}
			if (iSlow43 && (float((fTempPerm20 > 0.001f)) != 0.0f)) {
				fRec171[1] = fRec171[0];
			}
			if (iSlow42 && (float((fTempPerm20 > 0.001f)) != 0.0f)) {
				fRec170[1] = fRec170[0];
			}
			if (iSlow47 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow42 && (float((fTempPerm20 > 0.001f)) != 0.0f)) {
				fRec169[1] = fRec169[0];
			}
			if (iSlow41 && (float((fTempPerm20 > 0.001f)) != 0.0f)) {
				fRec165[1] = fRec165[0];
			}
			if (iSlow47 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow46 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow45 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow44 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow43 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow42 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow41 && (float((fTempPerm20 > 0.001f)) != 0.0f)) {
				fRec168[1] = fRec168[0];
				fRec166[1] = fRec166[0];
				fRec167[1] = fRec167[0];
			}
			if (iSlow13 && (float((fTempPerm20 > 0.001f)) != 0.0f)) {
				fRec161[1] = fRec161[0];
				fRec164[1] = fRec164[0];
				fRec162[1] = fRec162[0];
				fRec163[1] = fRec163[0];
			}
			if (iSlow40 && (float((fTempPerm20 > 0.001f)) != 0.0f)) {
				fRec157[1] = fRec157[0];
			}
			if (iSlow46 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow45 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow44 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow43 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow41 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow40 && (float((fTempPerm20 > 0.001f)) != 0.0f)) {
				fRec160[1] = fRec160[0];
				fRec158[1] = fRec158[0];
				fRec159[1] = fRec159[0];
			}
			if (iSlow48 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow40 && (float((fTempPerm20 > 0.001f)) != 0.0f)) {
				fRec153[1] = fRec153[0];
			}
			if (iSlow48 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow47 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow46 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow45 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow44 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow43 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow42 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow41 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow40 && (float((fTempPerm20 > 0.001f)) != 0.0f)) {
				fRec156[1] = fRec156[0];
				fRec154[1] = fRec154[0];
				fRec155[1] = fRec155[0];
			}
			if (iSlow12 && (float((fTempPerm20 > 0.001f)) != 0.0f)) {
				fRec151[1] = fRec151[0];
			}
			if (iSlow48 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow47 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow46 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow45 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow44 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow43 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow42 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow41 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow13 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow40 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow12 && (float((fTempPerm20 > 0.001f)) != 0.0f)) {
				fRec152[1] = fRec152[0];
			}
			if (iSlow13 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow12 && (float((fTempPerm20 > 0.001f)) != 0.0f)) {
				fRec149[1] = fRec149[0];
			}
			if (iSlow48 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow47 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow46 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow45 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow44 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow43 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow42 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow41 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow13 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow40 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow12 && (float((fTempPerm20 > 0.001f)) != 0.0f)) {
				fRec150[1] = fRec150[0];
			}
			if (iSlow47 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow12 && (float((fTempPerm20 > 0.001f)) != 0.0f)) {
				fRec147[1] = fRec147[0];
			}
			if (iSlow48 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow47 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow46 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow45 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow44 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow43 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow42 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow41 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow13 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow40 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow12 && (float((fTempPerm20 > 0.001f)) != 0.0f)) {
				fRec148[1] = fRec148[0];
			}
			if (iSlow13 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow12 && (float((fTempPerm20 > 0.001f)) != 0.0f)) {
				fRec145[1] = fRec145[0];
			}
			if (iSlow48 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow47 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow46 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow45 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow44 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow43 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow42 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow41 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow13 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow40 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow12 && (float((fTempPerm20 > 0.001f)) != 0.0f)) {
				fRec146[1] = fRec146[0];
			}
			if (iSlow48 && (float((fTempPerm16 > 0.001f)) != 0.0f)) {
				fRec144[1] = fRec144[0];
				fRec143[1] = fRec143[0];
			}
			if (iSlow46 && (float((fTempPerm16 > 0.001f)) != 0.0f)) {
				fRec142[1] = fRec142[0];
			}
			if (iSlow45 && (float((fTempPerm16 > 0.001f)) != 0.0f)) {
				fRec141[1] = fRec141[0];
			}
			if (iSlow44 && (float((fTempPerm16 > 0.001f)) != 0.0f)) {
				fRec140[1] = fRec140[0];
			}
			if (iSlow43 && (float((fTempPerm16 > 0.001f)) != 0.0f)) {
				fRec139[1] = fRec139[0];
			}
			if (iSlow42 && (float((fTempPerm16 > 0.001f)) != 0.0f)) {
				fRec138[1] = fRec138[0];
			}
			if (iSlow47 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow42 && (float((fTempPerm16 > 0.001f)) != 0.0f)) {
				fRec137[1] = fRec137[0];
			}
			if (iSlow41 && (float((fTempPerm16 > 0.001f)) != 0.0f)) {
				fRec133[1] = fRec133[0];
			}
			if (iSlow47 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow46 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow45 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow44 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow43 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow42 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow41 && (float((fTempPerm16 > 0.001f)) != 0.0f)) {
				fRec136[1] = fRec136[0];
				fRec134[1] = fRec134[0];
				fRec135[1] = fRec135[0];
			}
			if (iSlow13 && (float((fTempPerm16 > 0.001f)) != 0.0f)) {
				fRec129[1] = fRec129[0];
				fRec132[1] = fRec132[0];
				fRec130[1] = fRec130[0];
				fRec131[1] = fRec131[0];
			}
			if (iSlow40 && (float((fTempPerm16 > 0.001f)) != 0.0f)) {
				fRec125[1] = fRec125[0];
			}
			if (iSlow46 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow45 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow44 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow43 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow41 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow40 && (float((fTempPerm16 > 0.001f)) != 0.0f)) {
				fRec128[1] = fRec128[0];
				fRec126[1] = fRec126[0];
				fRec127[1] = fRec127[0];
			}
			if (iSlow48 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow40 && (float((fTempPerm16 > 0.001f)) != 0.0f)) {
				fRec121[1] = fRec121[0];
			}
			if (iSlow48 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow47 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow46 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow45 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow44 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow43 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow42 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow41 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow40 && (float((fTempPerm16 > 0.001f)) != 0.0f)) {
				fRec124[1] = fRec124[0];
				fRec122[1] = fRec122[0];
				fRec123[1] = fRec123[0];
			}
			if (iSlow12 && (float((fTempPerm16 > 0.001f)) != 0.0f)) {
				fRec119[1] = fRec119[0];
			}
			if (iSlow48 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow47 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow46 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow45 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow44 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow43 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow42 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow41 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow13 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow40 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow12 && (float((fTempPerm16 > 0.001f)) != 0.0f)) {
				fRec120[1] = fRec120[0];
			}
			if (iSlow13 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow12 && (float((fTempPerm16 > 0.001f)) != 0.0f)) {
				fRec117[1] = fRec117[0];
			}
			if (iSlow48 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow47 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow46 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow45 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow44 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow43 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow42 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow41 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow13 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow40 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow12 && (float((fTempPerm16 > 0.001f)) != 0.0f)) {
				fRec118[1] = fRec118[0];
			}
			if (iSlow47 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow12 && (float((fTempPerm16 > 0.001f)) != 0.0f)) {
				fRec115[1] = fRec115[0];
			}
			if (iSlow48 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow47 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow46 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow45 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow44 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow43 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow42 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow41 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow13 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow40 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow12 && (float((fTempPerm16 > 0.001f)) != 0.0f)) {
				fRec116[1] = fRec116[0];
			}
			if (iSlow13 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow12 && (float((fTempPerm16 > 0.001f)) != 0.0f)) {
				fRec113[1] = fRec113[0];
			}
			if (iSlow48 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow47 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow46 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow45 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow44 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow43 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow42 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow41 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow13 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow40 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow12 && (float((fTempPerm16 > 0.001f)) != 0.0f)) {
				fRec114[1] = fRec114[0];
			}
			if (iSlow48 && (float((fTempPerm12 > 0.001f)) != 0.0f)) {
				fRec112[1] = fRec112[0];
				fRec111[1] = fRec111[0];
			}
			if (iSlow46 && (float((fTempPerm12 > 0.001f)) != 0.0f)) {
				fRec110[1] = fRec110[0];
			}
			if (iSlow45 && (float((fTempPerm12 > 0.001f)) != 0.0f)) {
				fRec109[1] = fRec109[0];
			}
			if (iSlow44 && (float((fTempPerm12 > 0.001f)) != 0.0f)) {
				fRec108[1] = fRec108[0];
			}
			if (iSlow43 && (float((fTempPerm12 > 0.001f)) != 0.0f)) {
				fRec107[1] = fRec107[0];
			}
			if (iSlow42 && (float((fTempPerm12 > 0.001f)) != 0.0f)) {
				fRec106[1] = fRec106[0];
			}
			if (iSlow47 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow42 && (float((fTempPerm12 > 0.001f)) != 0.0f)) {
				fRec105[1] = fRec105[0];
			}
			if (iSlow41 && (float((fTempPerm12 > 0.001f)) != 0.0f)) {
				fRec101[1] = fRec101[0];
			}
			if (iSlow47 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow46 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow45 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow44 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow43 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow42 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow41 && (float((fTempPerm12 > 0.001f)) != 0.0f)) {
				fRec104[1] = fRec104[0];
				fRec102[1] = fRec102[0];
				fRec103[1] = fRec103[0];
			}
			if (iSlow13 && (float((fTempPerm12 > 0.001f)) != 0.0f)) {
				fRec97[1] = fRec97[0];
				fRec100[1] = fRec100[0];
				fRec98[1] = fRec98[0];
				fRec99[1] = fRec99[0];
			}
			if (iSlow40 && (float((fTempPerm12 > 0.001f)) != 0.0f)) {
				fRec93[1] = fRec93[0];
			}
			if (iSlow46 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow45 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow44 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow43 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow41 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow40 && (float((fTempPerm12 > 0.001f)) != 0.0f)) {
				fRec96[1] = fRec96[0];
				fRec94[1] = fRec94[0];
				fRec95[1] = fRec95[0];
			}
			if (iSlow48 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow40 && (float((fTempPerm12 > 0.001f)) != 0.0f)) {
				fRec89[1] = fRec89[0];
			}
			if (iSlow48 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow47 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow46 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow45 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow44 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow43 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow42 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow41 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow40 && (float((fTempPerm12 > 0.001f)) != 0.0f)) {
				fRec92[1] = fRec92[0];
				fRec90[1] = fRec90[0];
				fRec91[1] = fRec91[0];
			}
			if (iSlow12 && (float((fTempPerm12 > 0.001f)) != 0.0f)) {
				fRec87[1] = fRec87[0];
			}
			if (iSlow48 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow47 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow46 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow45 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow44 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow43 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow42 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow41 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow13 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow40 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow12 && (float((fTempPerm12 > 0.001f)) != 0.0f)) {
				fRec88[1] = fRec88[0];
			}
			if (iSlow13 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow12 && (float((fTempPerm12 > 0.001f)) != 0.0f)) {
				fRec85[1] = fRec85[0];
			}
			if (iSlow48 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow47 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow46 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow45 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow44 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow43 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow42 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow41 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow13 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow40 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow12 && (float((fTempPerm12 > 0.001f)) != 0.0f)) {
				fRec86[1] = fRec86[0];
			}
			if (iSlow47 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow12 && (float((fTempPerm12 > 0.001f)) != 0.0f)) {
				fRec83[1] = fRec83[0];
			}
			if (iSlow48 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow47 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow46 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow45 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow44 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow43 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow42 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow41 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow13 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow40 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow12 && (float((fTempPerm12 > 0.001f)) != 0.0f)) {
				fRec84[1] = fRec84[0];
			}
			if (iSlow13 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow12 && (float((fTempPerm12 > 0.001f)) != 0.0f)) {
				fRec81[1] = fRec81[0];
			}
			if (iSlow48 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow47 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow46 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow45 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow44 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow43 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow42 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow41 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow13 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow40 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow12 && (float((fTempPerm12 > 0.001f)) != 0.0f)) {
				fRec82[1] = fRec82[0];
			}
			if (iSlow48 && (float((fTempPerm8 > 0.001f)) != 0.0f)) {
				fRec80[1] = fRec80[0];
				fRec79[1] = fRec79[0];
			}
			if (iSlow46 && (float((fTempPerm8 > 0.001f)) != 0.0f)) {
				fRec78[1] = fRec78[0];
			}
			if (iSlow45 && (float((fTempPerm8 > 0.001f)) != 0.0f)) {
				fRec77[1] = fRec77[0];
			}
			if (iSlow44 && (float((fTempPerm8 > 0.001f)) != 0.0f)) {
				fRec76[1] = fRec76[0];
			}
			if (iSlow43 && (float((fTempPerm8 > 0.001f)) != 0.0f)) {
				fRec75[1] = fRec75[0];
			}
			if (iSlow42 && (float((fTempPerm8 > 0.001f)) != 0.0f)) {
				fRec74[1] = fRec74[0];
			}
			if (iSlow47 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow42 && (float((fTempPerm8 > 0.001f)) != 0.0f)) {
				fRec73[1] = fRec73[0];
			}
			if (iSlow41 && (float((fTempPerm8 > 0.001f)) != 0.0f)) {
				fRec69[1] = fRec69[0];
			}
			if (iSlow47 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow46 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow45 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow44 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow43 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow42 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow41 && (float((fTempPerm8 > 0.001f)) != 0.0f)) {
				fRec72[1] = fRec72[0];
				fRec70[1] = fRec70[0];
				fRec71[1] = fRec71[0];
			}
			if (iSlow13 && (float((fTempPerm8 > 0.001f)) != 0.0f)) {
				fRec65[1] = fRec65[0];
				fRec68[1] = fRec68[0];
				fRec66[1] = fRec66[0];
				fRec67[1] = fRec67[0];
			}
			if (iSlow40 && (float((fTempPerm8 > 0.001f)) != 0.0f)) {
				fRec61[1] = fRec61[0];
			}
			if (iSlow46 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow45 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow44 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow43 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow41 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow40 && (float((fTempPerm8 > 0.001f)) != 0.0f)) {
				fRec64[1] = fRec64[0];
				fRec62[1] = fRec62[0];
				fRec63[1] = fRec63[0];
			}
			if (iSlow48 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow40 && (float((fTempPerm8 > 0.001f)) != 0.0f)) {
				fRec57[1] = fRec57[0];
			}
			if (iSlow48 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow47 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow46 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow45 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow44 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow43 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow42 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow41 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow40 && (float((fTempPerm8 > 0.001f)) != 0.0f)) {
				fRec60[1] = fRec60[0];
				fRec58[1] = fRec58[0];
				fRec59[1] = fRec59[0];
			}
			if (iSlow12 && (float((fTempPerm8 > 0.001f)) != 0.0f)) {
				fRec55[1] = fRec55[0];
			}
			if (iSlow48 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow47 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow46 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow45 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow44 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow43 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow42 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow41 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow13 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow40 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow12 && (float((fTempPerm8 > 0.001f)) != 0.0f)) {
				fRec56[1] = fRec56[0];
			}
			if (iSlow13 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow12 && (float((fTempPerm8 > 0.001f)) != 0.0f)) {
				fRec53[1] = fRec53[0];
			}
			if (iSlow48 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow47 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow46 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow45 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow44 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow43 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow42 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow41 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow13 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow40 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow12 && (float((fTempPerm8 > 0.001f)) != 0.0f)) {
				fRec54[1] = fRec54[0];
			}
			if (iSlow47 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow12 && (float((fTempPerm8 > 0.001f)) != 0.0f)) {
				fRec51[1] = fRec51[0];
			}
			if (iSlow48 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow47 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow46 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow45 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow44 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow43 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow42 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow41 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow13 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow40 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow12 && (float((fTempPerm8 > 0.001f)) != 0.0f)) {
				fRec52[1] = fRec52[0];
			}
			if (iSlow13 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow12 && (float((fTempPerm8 > 0.001f)) != 0.0f)) {
				fRec49[1] = fRec49[0];
			}
			if (iSlow48 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow47 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow46 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow45 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow44 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow43 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow42 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow41 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow13 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow40 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow12 && (float((fTempPerm8 > 0.001f)) != 0.0f)) {
				fRec50[1] = fRec50[0];
			}
			if ((float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow48) {
				fRec48[1] = fRec48[0];
				fRec47[1] = fRec47[0];
			}
			if ((float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow46) {
				fRec46[1] = fRec46[0];
			}
			if ((float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow45) {
				fRec45[1] = fRec45[0];
			}
			if ((float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow44) {
				fRec44[1] = fRec44[0];
			}
			if ((float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow43) {
				fRec43[1] = fRec43[0];
			}
			if ((float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow42) {
				fRec42[1] = fRec42[0];
			}
			if ((float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow47 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow42) {
				fRec41[1] = fRec41[0];
			}
			if ((float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow41) {
				fRec37[1] = fRec37[0];
			}
			if ((float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow47 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow46 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow45 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow44 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow43 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow42 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow41) {
				fRec40[1] = fRec40[0];
				fRec38[1] = fRec38[0];
				fRec39[1] = fRec39[0];
			}
			if ((float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow13) {
				fRec33[1] = fRec33[0];
				fRec36[1] = fRec36[0];
				fRec34[1] = fRec34[0];
				fRec35[1] = fRec35[0];
			}
			if ((float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow40) {
				fRec29[1] = fRec29[0];
			}
			if ((float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow46 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow45 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow44 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow43 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow41 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow40) {
				fRec32[1] = fRec32[0];
				fRec30[1] = fRec30[0];
				fRec31[1] = fRec31[0];
			}
			if ((float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow48 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow40) {
				fRec25[1] = fRec25[0];
			}
			if ((float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow48 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow47 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow46 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow45 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow44 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow43 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow42 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow41 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow40) {
				fRec28[1] = fRec28[0];
				fRec26[1] = fRec26[0];
				fRec27[1] = fRec27[0];
			}
			if ((float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow12) {
				fRec22[1] = fRec22[0];
			}
			if ((float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow48 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow47 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow46 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow45 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow44 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow43 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow42 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow41 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow13 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow40 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow12) {
				fRec24[1] = fRec24[0];
			}
			if (iSlow48 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow47 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow42 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow13 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow12 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow48 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow47 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow42 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow13 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow12 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow48 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow47 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow42 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow13 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow12 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow48 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow47 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow42 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow13 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow12 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow48 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow47 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow42 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow13 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow12 && (float((fTempPerm8 > 0.001f)) != 0.0f) || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow48 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow47 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow42 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow13 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow12) {
				fRec23[1] = fRec23[0];
			}
			if ((float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow13 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow12) {
				fRec19[1] = fRec19[0];
			}
			if ((float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow48 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow47 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow46 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow45 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow44 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow43 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow42 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow41 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow13 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow40 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow12) {
				fRec21[1] = fRec21[0];
			}
			if (iSlow48 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow13 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow40 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow12 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow48 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow13 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow40 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow12 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow48 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow13 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow40 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow12 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow48 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow13 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow40 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow12 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow48 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow13 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow40 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow12 && (float((fTempPerm8 > 0.001f)) != 0.0f) || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow48 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow13 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow40 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow12) {
				fRec20[1] = fRec20[0];
			}
			if ((float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow47 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow12) {
				fRec16[1] = fRec16[0];
			}
			if ((float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow48 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow47 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow46 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow45 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow44 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow43 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow42 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow41 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow13 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow40 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow12) {
				fRec18[1] = fRec18[0];
			}
			if (iSlow48 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow47 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow46 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow45 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow44 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow43 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow42 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow41 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow40 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow12 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow48 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow47 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow46 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow45 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow44 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow43 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow42 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow41 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow40 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow12 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow48 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow47 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow46 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow45 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow44 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow43 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow42 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow41 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow40 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow12 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow48 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow47 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow46 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow45 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow44 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow43 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow42 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow41 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow40 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow12 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow48 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow47 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow46 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow45 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow44 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow43 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow42 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow41 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow40 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow12 && (float((fTempPerm8 > 0.001f)) != 0.0f) || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow48 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow47 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow46 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow45 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow44 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow43 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow42 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow41 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow40 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow12) {
				fRec17[1] = fRec17[0];
			}
			if ((float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow13 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow12) {
				fRec2[1] = fRec2[0];
			}
			if ((float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow48 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow47 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow46 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow45 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow44 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow43 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow42 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow41 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow13 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow40 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow12) {
				fRec15[1] = fRec15[0];
			}
			if (iSlow13 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow12 && (float((fTempPerm24 > 0.001f)) != 0.0f) || iSlow13 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow12 && (float((fTempPerm20 > 0.001f)) != 0.0f) || iSlow13 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow12 && (float((fTempPerm16 > 0.001f)) != 0.0f) || iSlow13 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow12 && (float((fTempPerm12 > 0.001f)) != 0.0f) || iSlow13 && (float((fTempPerm8 > 0.001f)) != 0.0f) || iSlow12 && (float((fTempPerm8 > 0.001f)) != 0.0f) || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow13 || (float((fTempPerm3 > 0.001f)) != 0.0f) && iSlow12) {
				fRec4[1] = fRec4[0];
			}
			fRec13[1] = fRec13[0];
			iRec14[1] = iRec14[0];
			fRec11[1] = fRec11[0];
			iRec12[1] = iRec12[0];
			fRec9[1] = fRec9[0];
			iRec10[1] = iRec10[0];
			fRec7[1] = fRec7[0];
			iRec8[1] = iRec8[0];
			fRec5[1] = fRec5[0];
			iRec6[1] = iRec6[0];
			fRec0[1] = fRec0[0];
			iRec1[1] = iRec1[0];
		}
	}
};


float 	faust_ottofm::ftbl0[65536];
