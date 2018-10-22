/* ------------------------------------------------------------
name: "nuke"
Code generated with Faust 2.10.0 (https://faust.grame.fr)
Compilation options: cpp, -scal -ftz 0
------------------------------------------------------------ */

#ifndef  __faust_nuke_H__
#define  __faust_nuke_H__

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

#include <algorithm>
#include <cmath>
#include <math.h>

static float faust_nuke_faustpower2_f(float value) {
	return (value * value);
	
}

#ifndef FAUSTCLASS 
#define FAUSTCLASS faust_nuke
#endif
#ifdef __APPLE__ 
#define exp10f __exp10f
#define exp10 __exp10
#endif

class faust_nuke : public dsp {
	
 private:
	
	FAUSTFLOAT fHslider0;
	int iVec0[2];
	int fSamplingFreq;
	float fConst0;
	float fConst1;
	FAUSTFLOAT fButton0;
	FAUSTFLOAT fHslider1;
	int iRec1[2];
	FAUSTFLOAT fHslider2;
	FAUSTFLOAT fHslider3;
	FAUSTFLOAT fHslider4;
	float fRec0[2];
	FAUSTFLOAT fHslider5;
	float fRec4[2];
	FAUSTFLOAT fHslider6;
	float fRec5[2];
	float fVec1[2];
	float fConst2;
	FAUSTFLOAT fHslider7;
	float fVec2[2];
	float fConst3;
	float fRec6[2];
	float fVec3[2];
	int IOTA;
	float fVec4[4096];
	float fConst4;
	float fConst5;
	float fRec7[2];
	float fConst6;
	int iRec9[2];
	float fRec8[2];
	float fVec5[2];
	FAUSTFLOAT fHslider8;
	float fRec10[2];
	int iRec12[2];
	float fRec11[2];
	float fVec6[2];
	float fVec7[2];
	float fRec13[2];
	float fVec8[2];
	float fVec9[4096];
	int iRec15[2];
	float fRec14[2];
	float fVec10[2];
	float fVec11[2];
	float fRec16[2];
	float fVec12[2];
	float fVec13[4096];
	float fConst7;
	float fRec17[2];
	float fRec18[2];
	float fVec14[2];
	float fRec19[2];
	float fVec15[2];
	float fVec16[4096];
	float fRec20[2];
	int iRec22[2];
	float fRec21[2];
	float fVec17[2];
	float fConst8;
	FAUSTFLOAT fHslider9;
	float fRec23[2];
	float fRec3[3];
	float fRec2[3];
	FAUSTFLOAT fHslider10;
	FAUSTFLOAT fButton1;
	int iRec25[2];
	float fRec24[2];
	FAUSTFLOAT fHslider11;
	float fVec18[2];
	float fRec28[2];
	float fVec19[2];
	float fVec20[4096];
	float fRec29[2];
	int iRec31[2];
	float fRec30[2];
	float fVec21[2];
	int iRec33[2];
	float fRec32[2];
	float fVec22[2];
	float fVec23[2];
	float fRec34[2];
	float fVec24[2];
	float fVec25[4096];
	int iRec36[2];
	float fRec35[2];
	float fVec26[2];
	float fVec27[2];
	float fRec37[2];
	float fVec28[2];
	float fVec29[4096];
	float fRec38[2];
	float fRec39[2];
	float fVec30[2];
	float fRec40[2];
	float fVec31[2];
	float fVec32[4096];
	float fRec41[2];
	int iRec43[2];
	float fRec42[2];
	float fVec33[2];
	float fRec27[3];
	float fRec26[3];
	FAUSTFLOAT fHslider12;
	FAUSTFLOAT fButton2;
	int iRec45[2];
	float fRec44[2];
	FAUSTFLOAT fHslider13;
	float fVec34[2];
	float fRec48[2];
	float fVec35[2];
	float fVec36[4096];
	float fRec49[2];
	int iRec51[2];
	float fRec50[2];
	float fVec37[2];
	int iRec53[2];
	float fRec52[2];
	float fVec38[2];
	float fVec39[2];
	float fRec54[2];
	float fVec40[2];
	float fVec41[4096];
	int iRec56[2];
	float fRec55[2];
	float fVec42[2];
	float fVec43[2];
	float fRec57[2];
	float fVec44[2];
	float fVec45[4096];
	float fRec58[2];
	float fRec59[2];
	float fVec46[2];
	float fRec60[2];
	float fVec47[2];
	float fVec48[4096];
	float fRec61[2];
	int iRec63[2];
	float fRec62[2];
	float fVec49[2];
	float fRec47[3];
	float fRec46[3];
	FAUSTFLOAT fHslider14;
	FAUSTFLOAT fButton3;
	int iRec65[2];
	float fRec64[2];
	FAUSTFLOAT fHslider15;
	float fVec50[2];
	float fRec68[2];
	float fVec51[2];
	float fVec52[4096];
	float fRec69[2];
	int iRec71[2];
	float fRec70[2];
	float fVec53[2];
	int iRec73[2];
	float fRec72[2];
	float fVec54[2];
	float fVec55[2];
	float fRec74[2];
	float fVec56[2];
	float fVec57[4096];
	int iRec76[2];
	float fRec75[2];
	float fVec58[2];
	float fVec59[2];
	float fRec77[2];
	float fVec60[2];
	float fVec61[4096];
	float fRec78[2];
	float fRec79[2];
	float fVec62[2];
	float fRec80[2];
	float fVec63[2];
	float fVec64[4096];
	float fRec81[2];
	int iRec83[2];
	float fRec82[2];
	float fVec65[2];
	float fRec67[3];
	float fRec66[3];
	FAUSTFLOAT fHslider16;
	FAUSTFLOAT fButton4;
	int iRec85[2];
	float fRec84[2];
	FAUSTFLOAT fHslider17;
	float fVec66[2];
	float fRec88[2];
	float fVec67[2];
	float fVec68[4096];
	float fRec89[2];
	int iRec91[2];
	float fRec90[2];
	float fVec69[2];
	int iRec93[2];
	float fRec92[2];
	float fVec70[2];
	float fVec71[2];
	float fRec94[2];
	float fVec72[2];
	float fVec73[4096];
	int iRec96[2];
	float fRec95[2];
	float fVec74[2];
	float fVec75[2];
	float fRec97[2];
	float fVec76[2];
	float fVec77[4096];
	float fRec98[2];
	float fRec99[2];
	float fVec78[2];
	float fRec100[2];
	float fVec79[2];
	float fVec80[4096];
	float fRec101[2];
	int iRec103[2];
	float fRec102[2];
	float fVec81[2];
	float fRec87[3];
	float fRec86[3];
	FAUSTFLOAT fHslider18;
	FAUSTFLOAT fButton5;
	int iRec105[2];
	float fRec104[2];
	FAUSTFLOAT fHslider19;
	float fVec82[2];
	float fRec108[2];
	float fVec83[2];
	float fVec84[4096];
	float fRec109[2];
	int iRec111[2];
	float fRec110[2];
	float fVec85[2];
	int iRec113[2];
	float fRec112[2];
	float fVec86[2];
	float fVec87[2];
	float fRec114[2];
	float fVec88[2];
	float fVec89[4096];
	int iRec116[2];
	float fRec115[2];
	float fVec90[2];
	float fVec91[2];
	float fRec117[2];
	float fVec92[2];
	float fVec93[4096];
	float fRec118[2];
	float fRec119[2];
	float fVec94[2];
	float fRec120[2];
	float fVec95[2];
	float fVec96[4096];
	float fRec121[2];
	int iRec123[2];
	float fRec122[2];
	float fVec97[2];
	float fRec107[3];
	float fRec106[3];
	
 public:
	
	void metadata(Meta* m) { 
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.0");
		m->declare("filename", "nuke");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/version", "0.0");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.1");
		m->declare("name", "nuke");
		m->declare("oscillators.lib/name", "Faust Oscillator Library");
		m->declare("oscillators.lib/version", "0.0");
		m->declare("signals.lib/name", "Faust Signal Routing Library");
		m->declare("signals.lib/version", "0.0");
	}

	virtual int getNumInputs() {
		return 0;
		
	}
	virtual int getNumOutputs() {
		return 1;
		
	}
	virtual int getInputRate(int channel) {
		int rate;
		switch (channel) {
			default: {
				rate = -1;
				break;
			}
			
		}
		return rate;
		
	}
	virtual int getOutputRate(int channel) {
		int rate;
		switch (channel) {
			case 0: {
				rate = 1;
				break;
			}
			default: {
				rate = -1;
				break;
			}
			
		}
		return rate;
		
	}
	
	static void classInit(int samplingFreq) {
		
	}
	
	virtual void instanceConstants(int samplingFreq) {
		fSamplingFreq = samplingFreq;
		fConst0 = std::min(192000.0f, std::max(1.0f, float(fSamplingFreq)));
		fConst1 = (6.90999985f / fConst0);
		fConst2 = (0.25f * fConst0);
		fConst3 = (1.0f / fConst0);
		fConst4 = (3.0f / fConst0);
		fConst5 = (0.5f * fConst0);
		fConst6 = (2.0f * fConst0);
		fConst7 = (6.0f / fConst0);
		fConst8 = (3.14159274f / fConst0);
		
	}
	
	virtual void instanceResetUserInterface() {
		fHslider0 = FAUSTFLOAT(0.5f);
		fButton0 = FAUSTFLOAT(0.0f);
		fHslider1 = FAUSTFLOAT(0.0f);
		fHslider2 = FAUSTFLOAT(0.001f);
		fHslider3 = FAUSTFLOAT(0.0f);
		fHslider4 = FAUSTFLOAT(1.0f);
		fHslider5 = FAUSTFLOAT(0.0f);
		fHslider6 = FAUSTFLOAT(1.0f);
		fHslider7 = FAUSTFLOAT(440.0f);
		fHslider8 = FAUSTFLOAT(2.0f);
		fHslider9 = FAUSTFLOAT(0.5f);
		fHslider10 = FAUSTFLOAT(0.5f);
		fButton1 = FAUSTFLOAT(0.0f);
		fHslider11 = FAUSTFLOAT(440.0f);
		fHslider12 = FAUSTFLOAT(0.5f);
		fButton2 = FAUSTFLOAT(0.0f);
		fHslider13 = FAUSTFLOAT(440.0f);
		fHslider14 = FAUSTFLOAT(0.5f);
		fButton3 = FAUSTFLOAT(0.0f);
		fHslider15 = FAUSTFLOAT(440.0f);
		fHslider16 = FAUSTFLOAT(0.5f);
		fButton4 = FAUSTFLOAT(0.0f);
		fHslider17 = FAUSTFLOAT(440.0f);
		fHslider18 = FAUSTFLOAT(0.5f);
		fButton5 = FAUSTFLOAT(0.0f);
		fHslider19 = FAUSTFLOAT(440.0f);
		
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			iVec0[l0] = 0;
			
		}
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			iRec1[l1] = 0;
			
		}
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			fRec0[l2] = 0.0f;
			
		}
		for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			fRec4[l3] = 0.0f;
			
		}
		for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			fRec5[l4] = 0.0f;
			
		}
		for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			fVec1[l5] = 0.0f;
			
		}
		for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			fVec2[l6] = 0.0f;
			
		}
		for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			fRec6[l7] = 0.0f;
			
		}
		for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			fVec3[l8] = 0.0f;
			
		}
		IOTA = 0;
		for (int l9 = 0; (l9 < 4096); l9 = (l9 + 1)) {
			fVec4[l9] = 0.0f;
			
		}
		for (int l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
			fRec7[l10] = 0.0f;
			
		}
		for (int l11 = 0; (l11 < 2); l11 = (l11 + 1)) {
			iRec9[l11] = 0;
			
		}
		for (int l12 = 0; (l12 < 2); l12 = (l12 + 1)) {
			fRec8[l12] = 0.0f;
			
		}
		for (int l13 = 0; (l13 < 2); l13 = (l13 + 1)) {
			fVec5[l13] = 0.0f;
			
		}
		for (int l14 = 0; (l14 < 2); l14 = (l14 + 1)) {
			fRec10[l14] = 0.0f;
			
		}
		for (int l15 = 0; (l15 < 2); l15 = (l15 + 1)) {
			iRec12[l15] = 0;
			
		}
		for (int l16 = 0; (l16 < 2); l16 = (l16 + 1)) {
			fRec11[l16] = 0.0f;
			
		}
		for (int l17 = 0; (l17 < 2); l17 = (l17 + 1)) {
			fVec6[l17] = 0.0f;
			
		}
		for (int l18 = 0; (l18 < 2); l18 = (l18 + 1)) {
			fVec7[l18] = 0.0f;
			
		}
		for (int l19 = 0; (l19 < 2); l19 = (l19 + 1)) {
			fRec13[l19] = 0.0f;
			
		}
		for (int l20 = 0; (l20 < 2); l20 = (l20 + 1)) {
			fVec8[l20] = 0.0f;
			
		}
		for (int l21 = 0; (l21 < 4096); l21 = (l21 + 1)) {
			fVec9[l21] = 0.0f;
			
		}
		for (int l22 = 0; (l22 < 2); l22 = (l22 + 1)) {
			iRec15[l22] = 0;
			
		}
		for (int l23 = 0; (l23 < 2); l23 = (l23 + 1)) {
			fRec14[l23] = 0.0f;
			
		}
		for (int l24 = 0; (l24 < 2); l24 = (l24 + 1)) {
			fVec10[l24] = 0.0f;
			
		}
		for (int l25 = 0; (l25 < 2); l25 = (l25 + 1)) {
			fVec11[l25] = 0.0f;
			
		}
		for (int l26 = 0; (l26 < 2); l26 = (l26 + 1)) {
			fRec16[l26] = 0.0f;
			
		}
		for (int l27 = 0; (l27 < 2); l27 = (l27 + 1)) {
			fVec12[l27] = 0.0f;
			
		}
		for (int l28 = 0; (l28 < 4096); l28 = (l28 + 1)) {
			fVec13[l28] = 0.0f;
			
		}
		for (int l29 = 0; (l29 < 2); l29 = (l29 + 1)) {
			fRec17[l29] = 0.0f;
			
		}
		for (int l30 = 0; (l30 < 2); l30 = (l30 + 1)) {
			fRec18[l30] = 0.0f;
			
		}
		for (int l31 = 0; (l31 < 2); l31 = (l31 + 1)) {
			fVec14[l31] = 0.0f;
			
		}
		for (int l32 = 0; (l32 < 2); l32 = (l32 + 1)) {
			fRec19[l32] = 0.0f;
			
		}
		for (int l33 = 0; (l33 < 2); l33 = (l33 + 1)) {
			fVec15[l33] = 0.0f;
			
		}
		for (int l34 = 0; (l34 < 4096); l34 = (l34 + 1)) {
			fVec16[l34] = 0.0f;
			
		}
		for (int l35 = 0; (l35 < 2); l35 = (l35 + 1)) {
			fRec20[l35] = 0.0f;
			
		}
		for (int l36 = 0; (l36 < 2); l36 = (l36 + 1)) {
			iRec22[l36] = 0;
			
		}
		for (int l37 = 0; (l37 < 2); l37 = (l37 + 1)) {
			fRec21[l37] = 0.0f;
			
		}
		for (int l38 = 0; (l38 < 2); l38 = (l38 + 1)) {
			fVec17[l38] = 0.0f;
			
		}
		for (int l39 = 0; (l39 < 2); l39 = (l39 + 1)) {
			fRec23[l39] = 0.0f;
			
		}
		for (int l40 = 0; (l40 < 3); l40 = (l40 + 1)) {
			fRec3[l40] = 0.0f;
			
		}
		for (int l41 = 0; (l41 < 3); l41 = (l41 + 1)) {
			fRec2[l41] = 0.0f;
			
		}
		for (int l42 = 0; (l42 < 2); l42 = (l42 + 1)) {
			iRec25[l42] = 0;
			
		}
		for (int l43 = 0; (l43 < 2); l43 = (l43 + 1)) {
			fRec24[l43] = 0.0f;
			
		}
		for (int l44 = 0; (l44 < 2); l44 = (l44 + 1)) {
			fVec18[l44] = 0.0f;
			
		}
		for (int l45 = 0; (l45 < 2); l45 = (l45 + 1)) {
			fRec28[l45] = 0.0f;
			
		}
		for (int l46 = 0; (l46 < 2); l46 = (l46 + 1)) {
			fVec19[l46] = 0.0f;
			
		}
		for (int l47 = 0; (l47 < 4096); l47 = (l47 + 1)) {
			fVec20[l47] = 0.0f;
			
		}
		for (int l48 = 0; (l48 < 2); l48 = (l48 + 1)) {
			fRec29[l48] = 0.0f;
			
		}
		for (int l49 = 0; (l49 < 2); l49 = (l49 + 1)) {
			iRec31[l49] = 0;
			
		}
		for (int l50 = 0; (l50 < 2); l50 = (l50 + 1)) {
			fRec30[l50] = 0.0f;
			
		}
		for (int l51 = 0; (l51 < 2); l51 = (l51 + 1)) {
			fVec21[l51] = 0.0f;
			
		}
		for (int l52 = 0; (l52 < 2); l52 = (l52 + 1)) {
			iRec33[l52] = 0;
			
		}
		for (int l53 = 0; (l53 < 2); l53 = (l53 + 1)) {
			fRec32[l53] = 0.0f;
			
		}
		for (int l54 = 0; (l54 < 2); l54 = (l54 + 1)) {
			fVec22[l54] = 0.0f;
			
		}
		for (int l55 = 0; (l55 < 2); l55 = (l55 + 1)) {
			fVec23[l55] = 0.0f;
			
		}
		for (int l56 = 0; (l56 < 2); l56 = (l56 + 1)) {
			fRec34[l56] = 0.0f;
			
		}
		for (int l57 = 0; (l57 < 2); l57 = (l57 + 1)) {
			fVec24[l57] = 0.0f;
			
		}
		for (int l58 = 0; (l58 < 4096); l58 = (l58 + 1)) {
			fVec25[l58] = 0.0f;
			
		}
		for (int l59 = 0; (l59 < 2); l59 = (l59 + 1)) {
			iRec36[l59] = 0;
			
		}
		for (int l60 = 0; (l60 < 2); l60 = (l60 + 1)) {
			fRec35[l60] = 0.0f;
			
		}
		for (int l61 = 0; (l61 < 2); l61 = (l61 + 1)) {
			fVec26[l61] = 0.0f;
			
		}
		for (int l62 = 0; (l62 < 2); l62 = (l62 + 1)) {
			fVec27[l62] = 0.0f;
			
		}
		for (int l63 = 0; (l63 < 2); l63 = (l63 + 1)) {
			fRec37[l63] = 0.0f;
			
		}
		for (int l64 = 0; (l64 < 2); l64 = (l64 + 1)) {
			fVec28[l64] = 0.0f;
			
		}
		for (int l65 = 0; (l65 < 4096); l65 = (l65 + 1)) {
			fVec29[l65] = 0.0f;
			
		}
		for (int l66 = 0; (l66 < 2); l66 = (l66 + 1)) {
			fRec38[l66] = 0.0f;
			
		}
		for (int l67 = 0; (l67 < 2); l67 = (l67 + 1)) {
			fRec39[l67] = 0.0f;
			
		}
		for (int l68 = 0; (l68 < 2); l68 = (l68 + 1)) {
			fVec30[l68] = 0.0f;
			
		}
		for (int l69 = 0; (l69 < 2); l69 = (l69 + 1)) {
			fRec40[l69] = 0.0f;
			
		}
		for (int l70 = 0; (l70 < 2); l70 = (l70 + 1)) {
			fVec31[l70] = 0.0f;
			
		}
		for (int l71 = 0; (l71 < 4096); l71 = (l71 + 1)) {
			fVec32[l71] = 0.0f;
			
		}
		for (int l72 = 0; (l72 < 2); l72 = (l72 + 1)) {
			fRec41[l72] = 0.0f;
			
		}
		for (int l73 = 0; (l73 < 2); l73 = (l73 + 1)) {
			iRec43[l73] = 0;
			
		}
		for (int l74 = 0; (l74 < 2); l74 = (l74 + 1)) {
			fRec42[l74] = 0.0f;
			
		}
		for (int l75 = 0; (l75 < 2); l75 = (l75 + 1)) {
			fVec33[l75] = 0.0f;
			
		}
		for (int l76 = 0; (l76 < 3); l76 = (l76 + 1)) {
			fRec27[l76] = 0.0f;
			
		}
		for (int l77 = 0; (l77 < 3); l77 = (l77 + 1)) {
			fRec26[l77] = 0.0f;
			
		}
		for (int l78 = 0; (l78 < 2); l78 = (l78 + 1)) {
			iRec45[l78] = 0;
			
		}
		for (int l79 = 0; (l79 < 2); l79 = (l79 + 1)) {
			fRec44[l79] = 0.0f;
			
		}
		for (int l80 = 0; (l80 < 2); l80 = (l80 + 1)) {
			fVec34[l80] = 0.0f;
			
		}
		for (int l81 = 0; (l81 < 2); l81 = (l81 + 1)) {
			fRec48[l81] = 0.0f;
			
		}
		for (int l82 = 0; (l82 < 2); l82 = (l82 + 1)) {
			fVec35[l82] = 0.0f;
			
		}
		for (int l83 = 0; (l83 < 4096); l83 = (l83 + 1)) {
			fVec36[l83] = 0.0f;
			
		}
		for (int l84 = 0; (l84 < 2); l84 = (l84 + 1)) {
			fRec49[l84] = 0.0f;
			
		}
		for (int l85 = 0; (l85 < 2); l85 = (l85 + 1)) {
			iRec51[l85] = 0;
			
		}
		for (int l86 = 0; (l86 < 2); l86 = (l86 + 1)) {
			fRec50[l86] = 0.0f;
			
		}
		for (int l87 = 0; (l87 < 2); l87 = (l87 + 1)) {
			fVec37[l87] = 0.0f;
			
		}
		for (int l88 = 0; (l88 < 2); l88 = (l88 + 1)) {
			iRec53[l88] = 0;
			
		}
		for (int l89 = 0; (l89 < 2); l89 = (l89 + 1)) {
			fRec52[l89] = 0.0f;
			
		}
		for (int l90 = 0; (l90 < 2); l90 = (l90 + 1)) {
			fVec38[l90] = 0.0f;
			
		}
		for (int l91 = 0; (l91 < 2); l91 = (l91 + 1)) {
			fVec39[l91] = 0.0f;
			
		}
		for (int l92 = 0; (l92 < 2); l92 = (l92 + 1)) {
			fRec54[l92] = 0.0f;
			
		}
		for (int l93 = 0; (l93 < 2); l93 = (l93 + 1)) {
			fVec40[l93] = 0.0f;
			
		}
		for (int l94 = 0; (l94 < 4096); l94 = (l94 + 1)) {
			fVec41[l94] = 0.0f;
			
		}
		for (int l95 = 0; (l95 < 2); l95 = (l95 + 1)) {
			iRec56[l95] = 0;
			
		}
		for (int l96 = 0; (l96 < 2); l96 = (l96 + 1)) {
			fRec55[l96] = 0.0f;
			
		}
		for (int l97 = 0; (l97 < 2); l97 = (l97 + 1)) {
			fVec42[l97] = 0.0f;
			
		}
		for (int l98 = 0; (l98 < 2); l98 = (l98 + 1)) {
			fVec43[l98] = 0.0f;
			
		}
		for (int l99 = 0; (l99 < 2); l99 = (l99 + 1)) {
			fRec57[l99] = 0.0f;
			
		}
		for (int l100 = 0; (l100 < 2); l100 = (l100 + 1)) {
			fVec44[l100] = 0.0f;
			
		}
		for (int l101 = 0; (l101 < 4096); l101 = (l101 + 1)) {
			fVec45[l101] = 0.0f;
			
		}
		for (int l102 = 0; (l102 < 2); l102 = (l102 + 1)) {
			fRec58[l102] = 0.0f;
			
		}
		for (int l103 = 0; (l103 < 2); l103 = (l103 + 1)) {
			fRec59[l103] = 0.0f;
			
		}
		for (int l104 = 0; (l104 < 2); l104 = (l104 + 1)) {
			fVec46[l104] = 0.0f;
			
		}
		for (int l105 = 0; (l105 < 2); l105 = (l105 + 1)) {
			fRec60[l105] = 0.0f;
			
		}
		for (int l106 = 0; (l106 < 2); l106 = (l106 + 1)) {
			fVec47[l106] = 0.0f;
			
		}
		for (int l107 = 0; (l107 < 4096); l107 = (l107 + 1)) {
			fVec48[l107] = 0.0f;
			
		}
		for (int l108 = 0; (l108 < 2); l108 = (l108 + 1)) {
			fRec61[l108] = 0.0f;
			
		}
		for (int l109 = 0; (l109 < 2); l109 = (l109 + 1)) {
			iRec63[l109] = 0;
			
		}
		for (int l110 = 0; (l110 < 2); l110 = (l110 + 1)) {
			fRec62[l110] = 0.0f;
			
		}
		for (int l111 = 0; (l111 < 2); l111 = (l111 + 1)) {
			fVec49[l111] = 0.0f;
			
		}
		for (int l112 = 0; (l112 < 3); l112 = (l112 + 1)) {
			fRec47[l112] = 0.0f;
			
		}
		for (int l113 = 0; (l113 < 3); l113 = (l113 + 1)) {
			fRec46[l113] = 0.0f;
			
		}
		for (int l114 = 0; (l114 < 2); l114 = (l114 + 1)) {
			iRec65[l114] = 0;
			
		}
		for (int l115 = 0; (l115 < 2); l115 = (l115 + 1)) {
			fRec64[l115] = 0.0f;
			
		}
		for (int l116 = 0; (l116 < 2); l116 = (l116 + 1)) {
			fVec50[l116] = 0.0f;
			
		}
		for (int l117 = 0; (l117 < 2); l117 = (l117 + 1)) {
			fRec68[l117] = 0.0f;
			
		}
		for (int l118 = 0; (l118 < 2); l118 = (l118 + 1)) {
			fVec51[l118] = 0.0f;
			
		}
		for (int l119 = 0; (l119 < 4096); l119 = (l119 + 1)) {
			fVec52[l119] = 0.0f;
			
		}
		for (int l120 = 0; (l120 < 2); l120 = (l120 + 1)) {
			fRec69[l120] = 0.0f;
			
		}
		for (int l121 = 0; (l121 < 2); l121 = (l121 + 1)) {
			iRec71[l121] = 0;
			
		}
		for (int l122 = 0; (l122 < 2); l122 = (l122 + 1)) {
			fRec70[l122] = 0.0f;
			
		}
		for (int l123 = 0; (l123 < 2); l123 = (l123 + 1)) {
			fVec53[l123] = 0.0f;
			
		}
		for (int l124 = 0; (l124 < 2); l124 = (l124 + 1)) {
			iRec73[l124] = 0;
			
		}
		for (int l125 = 0; (l125 < 2); l125 = (l125 + 1)) {
			fRec72[l125] = 0.0f;
			
		}
		for (int l126 = 0; (l126 < 2); l126 = (l126 + 1)) {
			fVec54[l126] = 0.0f;
			
		}
		for (int l127 = 0; (l127 < 2); l127 = (l127 + 1)) {
			fVec55[l127] = 0.0f;
			
		}
		for (int l128 = 0; (l128 < 2); l128 = (l128 + 1)) {
			fRec74[l128] = 0.0f;
			
		}
		for (int l129 = 0; (l129 < 2); l129 = (l129 + 1)) {
			fVec56[l129] = 0.0f;
			
		}
		for (int l130 = 0; (l130 < 4096); l130 = (l130 + 1)) {
			fVec57[l130] = 0.0f;
			
		}
		for (int l131 = 0; (l131 < 2); l131 = (l131 + 1)) {
			iRec76[l131] = 0;
			
		}
		for (int l132 = 0; (l132 < 2); l132 = (l132 + 1)) {
			fRec75[l132] = 0.0f;
			
		}
		for (int l133 = 0; (l133 < 2); l133 = (l133 + 1)) {
			fVec58[l133] = 0.0f;
			
		}
		for (int l134 = 0; (l134 < 2); l134 = (l134 + 1)) {
			fVec59[l134] = 0.0f;
			
		}
		for (int l135 = 0; (l135 < 2); l135 = (l135 + 1)) {
			fRec77[l135] = 0.0f;
			
		}
		for (int l136 = 0; (l136 < 2); l136 = (l136 + 1)) {
			fVec60[l136] = 0.0f;
			
		}
		for (int l137 = 0; (l137 < 4096); l137 = (l137 + 1)) {
			fVec61[l137] = 0.0f;
			
		}
		for (int l138 = 0; (l138 < 2); l138 = (l138 + 1)) {
			fRec78[l138] = 0.0f;
			
		}
		for (int l139 = 0; (l139 < 2); l139 = (l139 + 1)) {
			fRec79[l139] = 0.0f;
			
		}
		for (int l140 = 0; (l140 < 2); l140 = (l140 + 1)) {
			fVec62[l140] = 0.0f;
			
		}
		for (int l141 = 0; (l141 < 2); l141 = (l141 + 1)) {
			fRec80[l141] = 0.0f;
			
		}
		for (int l142 = 0; (l142 < 2); l142 = (l142 + 1)) {
			fVec63[l142] = 0.0f;
			
		}
		for (int l143 = 0; (l143 < 4096); l143 = (l143 + 1)) {
			fVec64[l143] = 0.0f;
			
		}
		for (int l144 = 0; (l144 < 2); l144 = (l144 + 1)) {
			fRec81[l144] = 0.0f;
			
		}
		for (int l145 = 0; (l145 < 2); l145 = (l145 + 1)) {
			iRec83[l145] = 0;
			
		}
		for (int l146 = 0; (l146 < 2); l146 = (l146 + 1)) {
			fRec82[l146] = 0.0f;
			
		}
		for (int l147 = 0; (l147 < 2); l147 = (l147 + 1)) {
			fVec65[l147] = 0.0f;
			
		}
		for (int l148 = 0; (l148 < 3); l148 = (l148 + 1)) {
			fRec67[l148] = 0.0f;
			
		}
		for (int l149 = 0; (l149 < 3); l149 = (l149 + 1)) {
			fRec66[l149] = 0.0f;
			
		}
		for (int l150 = 0; (l150 < 2); l150 = (l150 + 1)) {
			iRec85[l150] = 0;
			
		}
		for (int l151 = 0; (l151 < 2); l151 = (l151 + 1)) {
			fRec84[l151] = 0.0f;
			
		}
		for (int l152 = 0; (l152 < 2); l152 = (l152 + 1)) {
			fVec66[l152] = 0.0f;
			
		}
		for (int l153 = 0; (l153 < 2); l153 = (l153 + 1)) {
			fRec88[l153] = 0.0f;
			
		}
		for (int l154 = 0; (l154 < 2); l154 = (l154 + 1)) {
			fVec67[l154] = 0.0f;
			
		}
		for (int l155 = 0; (l155 < 4096); l155 = (l155 + 1)) {
			fVec68[l155] = 0.0f;
			
		}
		for (int l156 = 0; (l156 < 2); l156 = (l156 + 1)) {
			fRec89[l156] = 0.0f;
			
		}
		for (int l157 = 0; (l157 < 2); l157 = (l157 + 1)) {
			iRec91[l157] = 0;
			
		}
		for (int l158 = 0; (l158 < 2); l158 = (l158 + 1)) {
			fRec90[l158] = 0.0f;
			
		}
		for (int l159 = 0; (l159 < 2); l159 = (l159 + 1)) {
			fVec69[l159] = 0.0f;
			
		}
		for (int l160 = 0; (l160 < 2); l160 = (l160 + 1)) {
			iRec93[l160] = 0;
			
		}
		for (int l161 = 0; (l161 < 2); l161 = (l161 + 1)) {
			fRec92[l161] = 0.0f;
			
		}
		for (int l162 = 0; (l162 < 2); l162 = (l162 + 1)) {
			fVec70[l162] = 0.0f;
			
		}
		for (int l163 = 0; (l163 < 2); l163 = (l163 + 1)) {
			fVec71[l163] = 0.0f;
			
		}
		for (int l164 = 0; (l164 < 2); l164 = (l164 + 1)) {
			fRec94[l164] = 0.0f;
			
		}
		for (int l165 = 0; (l165 < 2); l165 = (l165 + 1)) {
			fVec72[l165] = 0.0f;
			
		}
		for (int l166 = 0; (l166 < 4096); l166 = (l166 + 1)) {
			fVec73[l166] = 0.0f;
			
		}
		for (int l167 = 0; (l167 < 2); l167 = (l167 + 1)) {
			iRec96[l167] = 0;
			
		}
		for (int l168 = 0; (l168 < 2); l168 = (l168 + 1)) {
			fRec95[l168] = 0.0f;
			
		}
		for (int l169 = 0; (l169 < 2); l169 = (l169 + 1)) {
			fVec74[l169] = 0.0f;
			
		}
		for (int l170 = 0; (l170 < 2); l170 = (l170 + 1)) {
			fVec75[l170] = 0.0f;
			
		}
		for (int l171 = 0; (l171 < 2); l171 = (l171 + 1)) {
			fRec97[l171] = 0.0f;
			
		}
		for (int l172 = 0; (l172 < 2); l172 = (l172 + 1)) {
			fVec76[l172] = 0.0f;
			
		}
		for (int l173 = 0; (l173 < 4096); l173 = (l173 + 1)) {
			fVec77[l173] = 0.0f;
			
		}
		for (int l174 = 0; (l174 < 2); l174 = (l174 + 1)) {
			fRec98[l174] = 0.0f;
			
		}
		for (int l175 = 0; (l175 < 2); l175 = (l175 + 1)) {
			fRec99[l175] = 0.0f;
			
		}
		for (int l176 = 0; (l176 < 2); l176 = (l176 + 1)) {
			fVec78[l176] = 0.0f;
			
		}
		for (int l177 = 0; (l177 < 2); l177 = (l177 + 1)) {
			fRec100[l177] = 0.0f;
			
		}
		for (int l178 = 0; (l178 < 2); l178 = (l178 + 1)) {
			fVec79[l178] = 0.0f;
			
		}
		for (int l179 = 0; (l179 < 4096); l179 = (l179 + 1)) {
			fVec80[l179] = 0.0f;
			
		}
		for (int l180 = 0; (l180 < 2); l180 = (l180 + 1)) {
			fRec101[l180] = 0.0f;
			
		}
		for (int l181 = 0; (l181 < 2); l181 = (l181 + 1)) {
			iRec103[l181] = 0;
			
		}
		for (int l182 = 0; (l182 < 2); l182 = (l182 + 1)) {
			fRec102[l182] = 0.0f;
			
		}
		for (int l183 = 0; (l183 < 2); l183 = (l183 + 1)) {
			fVec81[l183] = 0.0f;
			
		}
		for (int l184 = 0; (l184 < 3); l184 = (l184 + 1)) {
			fRec87[l184] = 0.0f;
			
		}
		for (int l185 = 0; (l185 < 3); l185 = (l185 + 1)) {
			fRec86[l185] = 0.0f;
			
		}
		for (int l186 = 0; (l186 < 2); l186 = (l186 + 1)) {
			iRec105[l186] = 0;
			
		}
		for (int l187 = 0; (l187 < 2); l187 = (l187 + 1)) {
			fRec104[l187] = 0.0f;
			
		}
		for (int l188 = 0; (l188 < 2); l188 = (l188 + 1)) {
			fVec82[l188] = 0.0f;
			
		}
		for (int l189 = 0; (l189 < 2); l189 = (l189 + 1)) {
			fRec108[l189] = 0.0f;
			
		}
		for (int l190 = 0; (l190 < 2); l190 = (l190 + 1)) {
			fVec83[l190] = 0.0f;
			
		}
		for (int l191 = 0; (l191 < 4096); l191 = (l191 + 1)) {
			fVec84[l191] = 0.0f;
			
		}
		for (int l192 = 0; (l192 < 2); l192 = (l192 + 1)) {
			fRec109[l192] = 0.0f;
			
		}
		for (int l193 = 0; (l193 < 2); l193 = (l193 + 1)) {
			iRec111[l193] = 0;
			
		}
		for (int l194 = 0; (l194 < 2); l194 = (l194 + 1)) {
			fRec110[l194] = 0.0f;
			
		}
		for (int l195 = 0; (l195 < 2); l195 = (l195 + 1)) {
			fVec85[l195] = 0.0f;
			
		}
		for (int l196 = 0; (l196 < 2); l196 = (l196 + 1)) {
			iRec113[l196] = 0;
			
		}
		for (int l197 = 0; (l197 < 2); l197 = (l197 + 1)) {
			fRec112[l197] = 0.0f;
			
		}
		for (int l198 = 0; (l198 < 2); l198 = (l198 + 1)) {
			fVec86[l198] = 0.0f;
			
		}
		for (int l199 = 0; (l199 < 2); l199 = (l199 + 1)) {
			fVec87[l199] = 0.0f;
			
		}
		for (int l200 = 0; (l200 < 2); l200 = (l200 + 1)) {
			fRec114[l200] = 0.0f;
			
		}
		for (int l201 = 0; (l201 < 2); l201 = (l201 + 1)) {
			fVec88[l201] = 0.0f;
			
		}
		for (int l202 = 0; (l202 < 4096); l202 = (l202 + 1)) {
			fVec89[l202] = 0.0f;
			
		}
		for (int l203 = 0; (l203 < 2); l203 = (l203 + 1)) {
			iRec116[l203] = 0;
			
		}
		for (int l204 = 0; (l204 < 2); l204 = (l204 + 1)) {
			fRec115[l204] = 0.0f;
			
		}
		for (int l205 = 0; (l205 < 2); l205 = (l205 + 1)) {
			fVec90[l205] = 0.0f;
			
		}
		for (int l206 = 0; (l206 < 2); l206 = (l206 + 1)) {
			fVec91[l206] = 0.0f;
			
		}
		for (int l207 = 0; (l207 < 2); l207 = (l207 + 1)) {
			fRec117[l207] = 0.0f;
			
		}
		for (int l208 = 0; (l208 < 2); l208 = (l208 + 1)) {
			fVec92[l208] = 0.0f;
			
		}
		for (int l209 = 0; (l209 < 4096); l209 = (l209 + 1)) {
			fVec93[l209] = 0.0f;
			
		}
		for (int l210 = 0; (l210 < 2); l210 = (l210 + 1)) {
			fRec118[l210] = 0.0f;
			
		}
		for (int l211 = 0; (l211 < 2); l211 = (l211 + 1)) {
			fRec119[l211] = 0.0f;
			
		}
		for (int l212 = 0; (l212 < 2); l212 = (l212 + 1)) {
			fVec94[l212] = 0.0f;
			
		}
		for (int l213 = 0; (l213 < 2); l213 = (l213 + 1)) {
			fRec120[l213] = 0.0f;
			
		}
		for (int l214 = 0; (l214 < 2); l214 = (l214 + 1)) {
			fVec95[l214] = 0.0f;
			
		}
		for (int l215 = 0; (l215 < 4096); l215 = (l215 + 1)) {
			fVec96[l215] = 0.0f;
			
		}
		for (int l216 = 0; (l216 < 2); l216 = (l216 + 1)) {
			fRec121[l216] = 0.0f;
			
		}
		for (int l217 = 0; (l217 < 2); l217 = (l217 + 1)) {
			iRec123[l217] = 0;
			
		}
		for (int l218 = 0; (l218 < 2); l218 = (l218 + 1)) {
			fRec122[l218] = 0.0f;
			
		}
		for (int l219 = 0; (l219 < 2); l219 = (l219 + 1)) {
			fVec97[l219] = 0.0f;
			
		}
		for (int l220 = 0; (l220 < 3); l220 = (l220 + 1)) {
			fRec107[l220] = 0.0f;
			
		}
		for (int l221 = 0; (l221 < 3); l221 = (l221 + 1)) {
			fRec106[l221] = 0.0f;
			
		}
		
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
	
	virtual faust_nuke* clone() {
		return new faust_nuke();
	}
	virtual int getSampleRate() {
		return fSamplingFreq;
		
	}
	
	virtual void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("nuke");
		ui_interface->addHorizontalSlider("Filter", &fHslider9, 0.5f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface->addHorizontalSlider("Relation", &fHslider8, 2.0f, 0.0f, 3.00099993f, 0.00100000005f);
		ui_interface->addHorizontalSlider("Sub", &fHslider5, 0.0f, 0.0f, 1.0f, 0.00100000005f);
		ui_interface->addHorizontalSlider("Wave", &fHslider6, 1.0f, 0.0799999982f, 4.0f, 0.00999999978f);
		ui_interface->openVerticalBox("envelope");
		ui_interface->addHorizontalSlider("Attack", &fHslider2, 0.00100000005f, 0.00100000005f, 4.0f, 0.00100000005f);
		ui_interface->addHorizontalSlider("Decay", &fHslider3, 0.0f, 0.0f, 4.0f, 0.00100000005f);
		ui_interface->addHorizontalSlider("Release", &fHslider1, 0.0f, 0.0f, 4.0f, 0.00999999978f);
		ui_interface->addHorizontalSlider("Sustain", &fHslider4, 1.0f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface->closeBox();
		ui_interface->openHorizontalBox("voices");
		ui_interface->openVerticalBox("0");
		ui_interface->openHorizontalBox("midi");
		ui_interface->addHorizontalSlider("freq", &fHslider7, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addButton("trigger", &fButton0);
		ui_interface->addHorizontalSlider("velocity", &fHslider0, 0.5f, 0.0f, 1.0f, 0.00787401572f);
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->openVerticalBox("1");
		ui_interface->openHorizontalBox("midi");
		ui_interface->addHorizontalSlider("freq", &fHslider13, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addButton("trigger", &fButton2);
		ui_interface->addHorizontalSlider("velocity", &fHslider12, 0.5f, 0.0f, 1.0f, 0.00787401572f);
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->openVerticalBox("2");
		ui_interface->openHorizontalBox("midi");
		ui_interface->addHorizontalSlider("freq", &fHslider17, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addButton("trigger", &fButton4);
		ui_interface->addHorizontalSlider("velocity", &fHslider16, 0.5f, 0.0f, 1.0f, 0.00787401572f);
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->openVerticalBox("3");
		ui_interface->openHorizontalBox("midi");
		ui_interface->addHorizontalSlider("freq", &fHslider11, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addButton("trigger", &fButton1);
		ui_interface->addHorizontalSlider("velocity", &fHslider10, 0.5f, 0.0f, 1.0f, 0.00787401572f);
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->openVerticalBox("4");
		ui_interface->openHorizontalBox("midi");
		ui_interface->addHorizontalSlider("freq", &fHslider15, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addButton("trigger", &fButton3);
		ui_interface->addHorizontalSlider("velocity", &fHslider14, 0.5f, 0.0f, 1.0f, 0.00787401572f);
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->openVerticalBox("5");
		ui_interface->openHorizontalBox("midi");
		ui_interface->addHorizontalSlider("freq", &fHslider19, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addButton("trigger", &fButton5);
		ui_interface->addHorizontalSlider("velocity", &fHslider18, 0.5f, 0.0f, 1.0f, 0.00787401572f);
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->closeBox();
		
	}
	
	virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
		FAUSTFLOAT* output0 = outputs[0];
		float fSlow0 = float(fHslider0);
		int iSlow1 = (float(fButton0) > 0.0f);
		float fSlow2 = float(fHslider1);
		int iSlow3 = int((fConst0 * float(fHslider2)));
		float fSlow4 = float(fHslider3);
		float fSlow5 = float(fHslider4);
		float fSlow6 = (float(iSlow1) * fSlow5);
		float fSlow7 = (1.0f / float(iSlow3));
		float fSlow8 = (0.00100000005f * float(fHslider5));
		float fSlow9 = (0.00100000005f * float(fHslider6));
		float fSlow10 = float(fHslider7);
		float fSlow11 = std::max((0.5f * fSlow10), 23.4489498f);
		float fSlow12 = std::max(20.0f, std::fabs(fSlow11));
		float fSlow13 = (fConst2 / fSlow12);
		float fSlow14 = (fConst0 / fSlow11);
		float fSlow15 = (fConst4 * fSlow10);
		float fSlow16 = std::max(0.0f, std::min(2047.0f, (fConst5 / fSlow11)));
		float fSlow17 = std::floor(fSlow16);
		float fSlow18 = (fSlow17 + (1.0f - fSlow16));
		int iSlow19 = int(fSlow16);
		float fSlow20 = (fSlow16 - fSlow17);
		int iSlow21 = (iSlow19 + 1);
		float fSlow22 = (fConst0 / fSlow10);
		int iSlow23 = int((fConst6 / fSlow10));
		float fSlow24 = (fConst3 * fSlow10);
		float fSlow25 = (0.00100000005f * float(fHslider8));
		float fSlow26 = (1.0f / fSlow10);
		float fSlow27 = (fConst7 * fSlow10);
		float fSlow28 = std::max(fSlow10, 23.4489498f);
		float fSlow29 = std::max(20.0f, std::fabs(fSlow28));
		float fSlow30 = (fConst2 / fSlow29);
		float fSlow31 = (fConst0 / fSlow28);
		float fSlow32 = std::max(0.0f, std::min(2047.0f, (fConst5 / fSlow28)));
		float fSlow33 = std::floor(fSlow32);
		float fSlow34 = (fSlow33 + (1.0f - fSlow32));
		int iSlow35 = int(fSlow32);
		float fSlow36 = (fSlow32 - fSlow33);
		int iSlow37 = (iSlow35 + 1);
		int iSlow38 = int(fSlow22);
		float fSlow39 = (0.00100000005f * float(fHslider9));
		float fSlow40 = float(fHslider10);
		int iSlow41 = (float(fButton1) > 0.0f);
		float fSlow42 = (float(iSlow41) * fSlow5);
		float fSlow43 = float(fHslider11);
		float fSlow44 = std::max((0.5f * fSlow43), 23.4489498f);
		float fSlow45 = std::max(20.0f, std::fabs(fSlow44));
		float fSlow46 = (fConst2 / fSlow45);
		float fSlow47 = (fConst0 / fSlow44);
		float fSlow48 = (fConst4 * fSlow43);
		float fSlow49 = std::max(0.0f, std::min(2047.0f, (fConst5 / fSlow44)));
		float fSlow50 = std::floor(fSlow49);
		float fSlow51 = (fSlow50 + (1.0f - fSlow49));
		int iSlow52 = int(fSlow49);
		float fSlow53 = (fSlow49 - fSlow50);
		int iSlow54 = (iSlow52 + 1);
		float fSlow55 = (fConst0 / fSlow43);
		int iSlow56 = int((fConst6 / fSlow43));
		float fSlow57 = (fConst3 * fSlow43);
		float fSlow58 = (1.0f / fSlow43);
		float fSlow59 = (fConst7 * fSlow43);
		float fSlow60 = std::max(fSlow43, 23.4489498f);
		float fSlow61 = std::max(20.0f, std::fabs(fSlow60));
		float fSlow62 = (fConst2 / fSlow61);
		float fSlow63 = (fConst0 / fSlow60);
		float fSlow64 = std::max(0.0f, std::min(2047.0f, (fConst5 / fSlow60)));
		float fSlow65 = std::floor(fSlow64);
		float fSlow66 = (fSlow65 + (1.0f - fSlow64));
		int iSlow67 = int(fSlow64);
		float fSlow68 = (fSlow64 - fSlow65);
		int iSlow69 = (iSlow67 + 1);
		int iSlow70 = int(fSlow55);
		float fSlow71 = float(fHslider12);
		int iSlow72 = (float(fButton2) > 0.0f);
		float fSlow73 = (float(iSlow72) * fSlow5);
		float fSlow74 = float(fHslider13);
		float fSlow75 = std::max((0.5f * fSlow74), 23.4489498f);
		float fSlow76 = std::max(20.0f, std::fabs(fSlow75));
		float fSlow77 = (fConst2 / fSlow76);
		float fSlow78 = (fConst0 / fSlow75);
		float fSlow79 = (fConst4 * fSlow74);
		float fSlow80 = std::max(0.0f, std::min(2047.0f, (fConst5 / fSlow75)));
		float fSlow81 = std::floor(fSlow80);
		float fSlow82 = (fSlow81 + (1.0f - fSlow80));
		int iSlow83 = int(fSlow80);
		float fSlow84 = (fSlow80 - fSlow81);
		int iSlow85 = (iSlow83 + 1);
		float fSlow86 = (fConst0 / fSlow74);
		int iSlow87 = int((fConst6 / fSlow74));
		float fSlow88 = (fConst3 * fSlow74);
		float fSlow89 = (1.0f / fSlow74);
		float fSlow90 = (fConst7 * fSlow74);
		float fSlow91 = std::max(fSlow74, 23.4489498f);
		float fSlow92 = std::max(20.0f, std::fabs(fSlow91));
		float fSlow93 = (fConst2 / fSlow92);
		float fSlow94 = (fConst0 / fSlow91);
		float fSlow95 = std::max(0.0f, std::min(2047.0f, (fConst5 / fSlow91)));
		float fSlow96 = std::floor(fSlow95);
		float fSlow97 = (fSlow96 + (1.0f - fSlow95));
		int iSlow98 = int(fSlow95);
		float fSlow99 = (fSlow95 - fSlow96);
		int iSlow100 = (iSlow98 + 1);
		int iSlow101 = int(fSlow86);
		float fSlow102 = float(fHslider14);
		int iSlow103 = (float(fButton3) > 0.0f);
		float fSlow104 = (float(iSlow103) * fSlow5);
		float fSlow105 = float(fHslider15);
		float fSlow106 = std::max((0.5f * fSlow105), 23.4489498f);
		float fSlow107 = std::max(20.0f, std::fabs(fSlow106));
		float fSlow108 = (fConst2 / fSlow107);
		float fSlow109 = (fConst0 / fSlow106);
		float fSlow110 = (fConst4 * fSlow105);
		float fSlow111 = std::max(0.0f, std::min(2047.0f, (fConst5 / fSlow106)));
		float fSlow112 = std::floor(fSlow111);
		float fSlow113 = (fSlow112 + (1.0f - fSlow111));
		int iSlow114 = int(fSlow111);
		float fSlow115 = (fSlow111 - fSlow112);
		int iSlow116 = (iSlow114 + 1);
		float fSlow117 = (fConst0 / fSlow105);
		int iSlow118 = int((fConst6 / fSlow105));
		float fSlow119 = (fConst3 * fSlow105);
		float fSlow120 = (1.0f / fSlow105);
		float fSlow121 = (fConst7 * fSlow105);
		float fSlow122 = std::max(fSlow105, 23.4489498f);
		float fSlow123 = std::max(20.0f, std::fabs(fSlow122));
		float fSlow124 = (fConst2 / fSlow123);
		float fSlow125 = (fConst0 / fSlow122);
		float fSlow126 = std::max(0.0f, std::min(2047.0f, (fConst5 / fSlow122)));
		float fSlow127 = std::floor(fSlow126);
		float fSlow128 = (fSlow127 + (1.0f - fSlow126));
		int iSlow129 = int(fSlow126);
		float fSlow130 = (fSlow126 - fSlow127);
		int iSlow131 = (iSlow129 + 1);
		int iSlow132 = int(fSlow117);
		float fSlow133 = float(fHslider16);
		int iSlow134 = (float(fButton4) > 0.0f);
		float fSlow135 = (float(iSlow134) * fSlow5);
		float fSlow136 = float(fHslider17);
		float fSlow137 = std::max((0.5f * fSlow136), 23.4489498f);
		float fSlow138 = std::max(20.0f, std::fabs(fSlow137));
		float fSlow139 = (fConst2 / fSlow138);
		float fSlow140 = (fConst0 / fSlow137);
		float fSlow141 = (fConst4 * fSlow136);
		float fSlow142 = std::max(0.0f, std::min(2047.0f, (fConst5 / fSlow137)));
		float fSlow143 = std::floor(fSlow142);
		float fSlow144 = (fSlow143 + (1.0f - fSlow142));
		int iSlow145 = int(fSlow142);
		float fSlow146 = (fSlow142 - fSlow143);
		int iSlow147 = (iSlow145 + 1);
		float fSlow148 = (fConst0 / fSlow136);
		int iSlow149 = int((fConst6 / fSlow136));
		float fSlow150 = (fConst3 * fSlow136);
		float fSlow151 = (1.0f / fSlow136);
		float fSlow152 = (fConst7 * fSlow136);
		float fSlow153 = std::max(fSlow136, 23.4489498f);
		float fSlow154 = std::max(20.0f, std::fabs(fSlow153));
		float fSlow155 = (fConst2 / fSlow154);
		float fSlow156 = (fConst0 / fSlow153);
		float fSlow157 = std::max(0.0f, std::min(2047.0f, (fConst5 / fSlow153)));
		float fSlow158 = std::floor(fSlow157);
		float fSlow159 = (fSlow158 + (1.0f - fSlow157));
		int iSlow160 = int(fSlow157);
		float fSlow161 = (fSlow157 - fSlow158);
		int iSlow162 = (iSlow160 + 1);
		int iSlow163 = int(fSlow148);
		float fSlow164 = float(fHslider18);
		int iSlow165 = (float(fButton5) > 0.0f);
		float fSlow166 = (float(iSlow165) * fSlow5);
		float fSlow167 = float(fHslider19);
		float fSlow168 = std::max((0.5f * fSlow167), 23.4489498f);
		float fSlow169 = std::max(20.0f, std::fabs(fSlow168));
		float fSlow170 = (fConst2 / fSlow169);
		float fSlow171 = (fConst0 / fSlow168);
		float fSlow172 = (fConst4 * fSlow167);
		float fSlow173 = std::max(0.0f, std::min(2047.0f, (fConst5 / fSlow168)));
		float fSlow174 = std::floor(fSlow173);
		float fSlow175 = (fSlow174 + (1.0f - fSlow173));
		int iSlow176 = int(fSlow173);
		float fSlow177 = (fSlow173 - fSlow174);
		int iSlow178 = (iSlow176 + 1);
		float fSlow179 = (fConst0 / fSlow167);
		int iSlow180 = int((fConst6 / fSlow167));
		float fSlow181 = (fConst3 * fSlow167);
		float fSlow182 = (1.0f / fSlow167);
		float fSlow183 = (fConst7 * fSlow167);
		float fSlow184 = std::max(fSlow167, 23.4489498f);
		float fSlow185 = std::max(20.0f, std::fabs(fSlow184));
		float fSlow186 = (fConst2 / fSlow185);
		float fSlow187 = (fConst0 / fSlow184);
		float fSlow188 = std::max(0.0f, std::min(2047.0f, (fConst5 / fSlow184)));
		float fSlow189 = std::floor(fSlow188);
		float fSlow190 = (fSlow189 + (1.0f - fSlow188));
		int iSlow191 = int(fSlow188);
		float fSlow192 = (fSlow188 - fSlow189);
		int iSlow193 = (iSlow191 + 1);
		int iSlow194 = int(fSlow179);
		for (int i = 0; (i < count); i = (i + 1)) {
			iVec0[0] = 1;
			iRec1[0] = (iSlow1 * (iRec1[1] + 1));
			int iTemp0 = (iRec1[0] < iSlow3);
			float fTemp1 = std::exp((0.0f - (fConst1 / (iSlow1?(iTemp0?1.00000001e-07f:fSlow4):fSlow2))));
			fRec0[0] = ((fRec0[1] * fTemp1) + ((iSlow1?(iTemp0?(fSlow7 * float(iRec1[0])):fSlow6):0.0f) * (1.0f - fTemp1)));
			fRec4[0] = (fSlow8 + (0.999000013f * fRec4[1]));
			fRec5[0] = (fSlow9 + (0.999000013f * fRec5[1]));
			float fTemp2 = std::min(1.0f, std::max(0.0f, (2.0f - fRec5[0])));
			fVec1[0] = 0.25f;
			fVec2[0] = fSlow12;
			float fTemp3 = float(iVec0[1]);
			float fTemp4 = (fRec6[1] + (fConst3 * fVec2[1]));
			fRec6[0] = (fTemp4 - std::floor(fTemp4));
			float fTemp5 = faust_nuke_faustpower2_f(((2.0f * fRec6[0]) + -1.0f));
			fVec3[0] = fTemp5;
			float fTemp6 = (fSlow13 * (fTemp3 * (fTemp5 - fVec3[1])));
			fVec4[(IOTA & 4095)] = fTemp6;
			float fTemp7 = std::min(0.5f, (0.5f * fRec5[0]));
			float fTemp8 = std::max(0.0f, std::min(2047.0f, (fSlow14 * fTemp7)));
			int iTemp9 = int(fTemp8);
			float fTemp10 = std::floor(fTemp8);
			fRec7[0] = ((fTemp6 + (0.999000013f * fRec7[1])) - ((fSlow18 * fVec4[((IOTA - iSlow19) & 4095)]) + (fSlow20 * fVec4[((IOTA - iSlow21) & 4095)])));
			float fTemp11 = std::min(1.0f, std::max(0.0f, (fRec5[0] + -2.0f)));
			float fTemp12 = (1.0f - (fTemp2 + fTemp11));
			iRec9[0] = ((iRec9[1] + iVec0[1]) % iSlow23);
			float fTemp13 = (0.100000001f * (std::max(3.0f, fRec5[0]) + -3.0f));
			float fTemp14 = (fTemp13 + 0.5f);
			float fTemp15 = ((fRec8[1] * (1.0f - float(((iRec9[0] == 0) > 0)))) + (fSlow24 * fTemp14));
			fRec8[0] = (fTemp15 - std::floor(fTemp15));
			float fTemp16 = faust_nuke_faustpower2_f(((2.0f * fRec8[0]) + -1.0f));
			fVec5[0] = fTemp16;
			fRec10[0] = (fSlow25 + (0.999000013f * fRec10[1]));
			float fTemp17 = float((fRec10[0] >= 2.0f));
			int iTemp18 = (fRec10[0] >= 3.0f);
			float fTemp19 = ((iTemp18 + (fRec10[0] == 0.0f))?1.0f:std::max(std::max(1.0f, ((0.0199999996f * (fRec10[0] + -2.0999999f)) + 1.0f)), ((0.0199999996f * (1.0f - fRec10[0])) + 1.0f)));
			iRec12[0] = ((iRec12[1] + iVec0[1]) % int((fSlow22 / fTemp19)));
			float fTemp20 = (fTemp19 + fTemp13);
			float fTemp21 = ((fRec11[1] * (1.0f - float(((iRec12[0] == 0) > 0)))) + (fSlow24 * fTemp20));
			fRec11[0] = (fTemp21 - std::floor(fTemp21));
			float fTemp22 = faust_nuke_faustpower2_f(((2.0f * fRec11[0]) + -1.0f));
			fVec6[0] = fTemp22;
			float fTemp23 = std::max((fSlow10 * fTemp19), 23.4489498f);
			float fTemp24 = std::max(20.0f, std::fabs(fTemp23));
			fVec7[0] = fTemp24;
			float fTemp25 = (fRec13[1] + (fConst3 * fVec7[1]));
			fRec13[0] = (fTemp25 - std::floor(fTemp25));
			float fTemp26 = faust_nuke_faustpower2_f(((2.0f * fRec13[0]) + -1.0f));
			fVec8[0] = fTemp26;
			float fTemp27 = ((fTemp3 * (fTemp26 - fVec8[1])) / fTemp24);
			fVec9[(IOTA & 4095)] = fTemp27;
			float fTemp28 = std::max(0.0f, std::min(2047.0f, (fConst0 * (fTemp7 / fTemp23))));
			int iTemp29 = int(fTemp28);
			float fTemp30 = std::floor(fTemp28);
			float fTemp31 = ((fSlow26 * (((fTemp11 * (fTemp22 - fVec6[1])) * fVec1[1]) / fTemp20)) + (0.25f * (fTemp2 * ((fTemp27 - (fVec9[((IOTA - iTemp29) & 4095)] * (fTemp30 + (1.0f - fTemp28)))) - ((fTemp28 - fTemp30) * fVec9[((IOTA - (iTemp29 + 1)) & 4095)])))));
			float fTemp32 = (iTemp18?1.49829996f:1.0f);
			float fTemp33 = (fTemp19 / fTemp32);
			iRec15[0] = ((iRec15[1] + iVec0[1]) % int((fSlow22 * fTemp33)));
			float fTemp34 = (fTemp32 / fTemp19);
			float fTemp35 = (fTemp13 + fTemp34);
			float fTemp36 = ((fRec14[1] * (1.0f - float(((iRec15[0] == 0) > 0)))) + (fSlow24 * fTemp35));
			fRec14[0] = (fTemp36 - std::floor(fTemp36));
			float fTemp37 = faust_nuke_faustpower2_f(((2.0f * fRec14[0]) + -1.0f));
			fVec10[0] = fTemp37;
			float fTemp38 = std::max((fSlow10 * fTemp34), 23.4489498f);
			float fTemp39 = std::max(20.0f, std::fabs(fTemp38));
			fVec11[0] = fTemp39;
			float fTemp40 = (fRec16[1] + (fConst3 * fVec11[1]));
			fRec16[0] = (fTemp40 - std::floor(fTemp40));
			float fTemp41 = faust_nuke_faustpower2_f(((2.0f * fRec16[0]) + -1.0f));
			fVec12[0] = fTemp41;
			float fTemp42 = ((fTemp3 * (fTemp41 - fVec12[1])) / fTemp39);
			fVec13[(IOTA & 4095)] = fTemp42;
			float fTemp43 = std::max(0.0f, std::min(2047.0f, (fConst0 * (fTemp7 / fTemp38))));
			int iTemp44 = int(fTemp43);
			float fTemp45 = std::floor(fTemp43);
			float fTemp46 = ((fSlow26 * (((fTemp11 * (fTemp37 - fVec10[1])) * fVec1[1]) / fTemp35)) + (0.25f * (fTemp2 * ((fTemp42 - (fVec13[((IOTA - iTemp44) & 4095)] * (fTemp45 + (1.0f - fTemp43)))) - ((fTemp43 - fTemp45) * fVec13[((IOTA - (iTemp44 + 1)) & 4095)])))));
			float fTemp47 = std::max(0.0f, std::min(2047.0f, (fConst5 / fTemp23)));
			int iTemp48 = int(fTemp47);
			float fTemp49 = std::floor(fTemp47);
			fRec17[0] = ((0.999000013f * fRec17[1]) + (fConst2 * ((fTemp27 - (fVec9[((IOTA - iTemp48) & 4095)] * (fTemp49 + (1.0f - fTemp47)))) - ((fTemp47 - fTemp49) * fVec9[((IOTA - (iTemp48 + 1)) & 4095)]))));
			float fTemp50 = (fRec17[0] * fTemp19);
			float fTemp51 = std::max(0.0f, std::min(2047.0f, (fConst5 / fTemp38)));
			int iTemp52 = int(fTemp51);
			float fTemp53 = std::floor(fTemp51);
			fRec18[0] = ((0.999000013f * fRec18[1]) + (fConst2 * ((fTemp42 - (fVec13[((IOTA - iTemp52) & 4095)] * (fTemp53 + (1.0f - fTemp51)))) - ((fTemp51 - fTemp53) * fVec13[((IOTA - (iTemp52 + 1)) & 4095)]))));
			float fTemp54 = (fRec18[0] * fTemp32);
			float fTemp55 = float((fRec10[0] < 2.0f));
			float fTemp56 = std::min(1.0f, std::max(0.0f, (2.0f - fRec10[0])));
			float fTemp57 = (1.0f - fTemp56);
			float fTemp58 = (1.0f - fRec4[0]);
			fVec14[0] = fSlow29;
			float fTemp59 = (fRec19[1] + (fConst3 * fVec14[1]));
			fRec19[0] = (fTemp59 - std::floor(fTemp59));
			float fTemp60 = faust_nuke_faustpower2_f(((2.0f * fRec19[0]) + -1.0f));
			fVec15[0] = fTemp60;
			float fTemp61 = (fSlow30 * (fTemp3 * (fTemp60 - fVec15[1])));
			fVec16[(IOTA & 4095)] = fTemp61;
			float fTemp62 = std::max(0.0f, std::min(2047.0f, (fSlow31 * fTemp7)));
			int iTemp63 = int(fTemp62);
			float fTemp64 = std::floor(fTemp62);
			fRec20[0] = ((fTemp61 + (0.999000013f * fRec20[1])) - ((fSlow34 * fVec16[((IOTA - iSlow35) & 4095)]) + (fSlow36 * fVec16[((IOTA - iSlow37) & 4095)])));
			iRec22[0] = ((iRec22[1] + iVec0[1]) % iSlow38);
			float fTemp65 = (fTemp13 + 1.0f);
			float fTemp66 = ((fRec21[1] * (1.0f - float(((iRec22[0] == 0) > 0)))) + (fSlow24 * fTemp65));
			fRec21[0] = (fTemp66 - std::floor(fTemp66));
			float fTemp67 = faust_nuke_faustpower2_f(((2.0f * fRec21[0]) + -1.0f));
			fVec17[0] = fTemp67;
			fRec23[0] = (fSlow39 + (0.999000013f * fRec23[1]));
			float fTemp68 = std::tan((fConst8 * ((10000.0f * faust_nuke_faustpower2_f(fRec23[0])) + 100.0f)));
			float fTemp69 = (1.0f / fTemp68);
			float fTemp70 = (((fTemp69 + -0.800000012f) / fTemp68) + 1.0f);
			float fTemp71 = (1.0f - (1.0f / faust_nuke_faustpower2_f(fTemp68)));
			float fTemp72 = (((fTemp69 + 0.800000012f) / fTemp68) + 1.0f);
			fRec3[0] = (((fRec4[0] * (((fTemp2 * (fTemp6 - ((fVec4[((IOTA - iTemp9) & 4095)] * (fTemp10 + (1.0f - fTemp8))) + ((fTemp8 - fTemp10) * fVec4[((IOTA - (iTemp9 + 1)) & 4095)])))) + (fSlow15 * (fRec7[0] * fTemp12))) + (fSlow22 * (((fTemp11 * (fTemp16 - fVec5[1])) * fVec1[1]) / fTemp14)))) + (((fTemp17 * ((fConst0 * (fTemp31 + fTemp46)) + (fSlow27 * (fTemp12 * (fTemp50 + (fTemp54 / fTemp19)))))) + ((fTemp55 * ((fSlow27 * (fTemp50 * fTemp12)) + (fConst0 * fTemp31))) * (fTemp57 + (fTemp56 * ((fSlow27 * ((fTemp54 * fTemp12) / fTemp19)) + (fConst0 * fTemp46)))))) + (fTemp58 * (((fTemp2 * (fTemp61 - ((fVec16[((IOTA - iTemp63) & 4095)] * (fTemp64 + (1.0f - fTemp62))) + ((fTemp62 - fTemp64) * fVec16[((IOTA - (iTemp63 + 1)) & 4095)])))) + (fSlow27 * (fRec20[0] * fTemp12))) + (fSlow22 * (((fTemp11 * (fTemp67 - fVec17[1])) * fVec1[1]) / fTemp65)))))) - (((fRec3[2] * fTemp70) + (2.0f * (fRec3[1] * fTemp71))) / fTemp72));
			fRec2[0] = ((((fRec3[1] + (0.5f * fRec3[0])) + (0.5f * fRec3[2])) - ((fTemp70 * fRec2[2]) + (2.0f * (fTemp71 * fRec2[1])))) / fTemp72);
			iRec25[0] = (iSlow41 * (iRec25[1] + 1));
			int iTemp73 = (iRec25[0] < iSlow3);
			float fTemp74 = std::exp((0.0f - (fConst1 / (iSlow41?(iTemp73?1.00000001e-07f:fSlow4):fSlow2))));
			fRec24[0] = ((fRec24[1] * fTemp74) + ((iSlow41?(iTemp73?(fSlow7 * float(iRec25[0])):fSlow42):0.0f) * (1.0f - fTemp74)));
			fVec18[0] = fSlow45;
			float fTemp75 = (fRec28[1] + (fConst3 * fVec18[1]));
			fRec28[0] = (fTemp75 - std::floor(fTemp75));
			float fTemp76 = faust_nuke_faustpower2_f(((2.0f * fRec28[0]) + -1.0f));
			fVec19[0] = fTemp76;
			float fTemp77 = (fSlow46 * (fTemp3 * (fTemp76 - fVec19[1])));
			fVec20[(IOTA & 4095)] = fTemp77;
			float fTemp78 = std::max(0.0f, std::min(2047.0f, (fSlow47 * fTemp7)));
			int iTemp79 = int(fTemp78);
			float fTemp80 = std::floor(fTemp78);
			fRec29[0] = ((fTemp77 + (0.999000013f * fRec29[1])) - ((fSlow51 * fVec20[((IOTA - iSlow52) & 4095)]) + (fSlow53 * fVec20[((IOTA - iSlow54) & 4095)])));
			iRec31[0] = ((iRec31[1] + iVec0[1]) % iSlow56);
			float fTemp81 = ((fRec30[1] * (1.0f - float(((iRec31[0] == 0) > 0)))) + (fSlow57 * fTemp14));
			fRec30[0] = (fTemp81 - std::floor(fTemp81));
			float fTemp82 = faust_nuke_faustpower2_f(((2.0f * fRec30[0]) + -1.0f));
			fVec21[0] = fTemp82;
			iRec33[0] = ((iRec33[1] + iVec0[1]) % int((fSlow55 / fTemp19)));
			float fTemp83 = ((fRec32[1] * (1.0f - float(((iRec33[0] == 0) > 0)))) + (fSlow57 * fTemp20));
			fRec32[0] = (fTemp83 - std::floor(fTemp83));
			float fTemp84 = faust_nuke_faustpower2_f(((2.0f * fRec32[0]) + -1.0f));
			fVec22[0] = fTemp84;
			float fTemp85 = std::max((fSlow43 * fTemp19), 23.4489498f);
			float fTemp86 = std::max(20.0f, std::fabs(fTemp85));
			fVec23[0] = fTemp86;
			float fTemp87 = (fRec34[1] + (fConst3 * fVec23[1]));
			fRec34[0] = (fTemp87 - std::floor(fTemp87));
			float fTemp88 = faust_nuke_faustpower2_f(((2.0f * fRec34[0]) + -1.0f));
			fVec24[0] = fTemp88;
			float fTemp89 = ((fTemp3 * (fTemp88 - fVec24[1])) / fTemp86);
			fVec25[(IOTA & 4095)] = fTemp89;
			float fTemp90 = std::max(0.0f, std::min(2047.0f, (fConst0 * (fTemp7 / fTemp85))));
			int iTemp91 = int(fTemp90);
			float fTemp92 = std::floor(fTemp90);
			float fTemp93 = ((fSlow58 * (((fTemp11 * (fTemp84 - fVec22[1])) * fVec1[1]) / fTemp20)) + (0.25f * (fTemp2 * ((fTemp89 - (fVec25[((IOTA - iTemp91) & 4095)] * (fTemp92 + (1.0f - fTemp90)))) - ((fTemp90 - fTemp92) * fVec25[((IOTA - (iTemp91 + 1)) & 4095)])))));
			iRec36[0] = ((iRec36[1] + iVec0[1]) % int((fSlow55 * fTemp33)));
			float fTemp94 = ((fRec35[1] * (1.0f - float(((iRec36[0] == 0) > 0)))) + (fSlow57 * fTemp35));
			fRec35[0] = (fTemp94 - std::floor(fTemp94));
			float fTemp95 = faust_nuke_faustpower2_f(((2.0f * fRec35[0]) + -1.0f));
			fVec26[0] = fTemp95;
			float fTemp96 = std::max((fSlow43 * fTemp34), 23.4489498f);
			float fTemp97 = std::max(20.0f, std::fabs(fTemp96));
			fVec27[0] = fTemp97;
			float fTemp98 = (fRec37[1] + (fConst3 * fVec27[1]));
			fRec37[0] = (fTemp98 - std::floor(fTemp98));
			float fTemp99 = faust_nuke_faustpower2_f(((2.0f * fRec37[0]) + -1.0f));
			fVec28[0] = fTemp99;
			float fTemp100 = ((fTemp3 * (fTemp99 - fVec28[1])) / fTemp97);
			fVec29[(IOTA & 4095)] = fTemp100;
			float fTemp101 = std::max(0.0f, std::min(2047.0f, (fConst0 * (fTemp7 / fTemp96))));
			int iTemp102 = int(fTemp101);
			float fTemp103 = std::floor(fTemp101);
			float fTemp104 = ((fSlow58 * (((fTemp11 * (fTemp95 - fVec26[1])) * fVec1[1]) / fTemp35)) + (0.25f * (fTemp2 * ((fTemp100 - (fVec29[((IOTA - iTemp102) & 4095)] * (fTemp103 + (1.0f - fTemp101)))) - ((fTemp101 - fTemp103) * fVec29[((IOTA - (iTemp102 + 1)) & 4095)])))));
			float fTemp105 = std::max(0.0f, std::min(2047.0f, (fConst5 / fTemp85)));
			int iTemp106 = int(fTemp105);
			float fTemp107 = std::floor(fTemp105);
			fRec38[0] = ((0.999000013f * fRec38[1]) + (fConst2 * ((fTemp89 - (fVec25[((IOTA - iTemp106) & 4095)] * (fTemp107 + (1.0f - fTemp105)))) - ((fTemp105 - fTemp107) * fVec25[((IOTA - (iTemp106 + 1)) & 4095)]))));
			float fTemp108 = (fRec38[0] * fTemp19);
			float fTemp109 = std::max(0.0f, std::min(2047.0f, (fConst5 / fTemp96)));
			int iTemp110 = int(fTemp109);
			float fTemp111 = std::floor(fTemp109);
			fRec39[0] = ((0.999000013f * fRec39[1]) + (fConst2 * ((fTemp100 - (fVec29[((IOTA - iTemp110) & 4095)] * (fTemp111 + (1.0f - fTemp109)))) - ((fTemp109 - fTemp111) * fVec29[((IOTA - (iTemp110 + 1)) & 4095)]))));
			float fTemp112 = (fRec39[0] * fTemp32);
			fVec30[0] = fSlow61;
			float fTemp113 = (fRec40[1] + (fConst3 * fVec30[1]));
			fRec40[0] = (fTemp113 - std::floor(fTemp113));
			float fTemp114 = faust_nuke_faustpower2_f(((2.0f * fRec40[0]) + -1.0f));
			fVec31[0] = fTemp114;
			float fTemp115 = (fSlow62 * (fTemp3 * (fTemp114 - fVec31[1])));
			fVec32[(IOTA & 4095)] = fTemp115;
			float fTemp116 = std::max(0.0f, std::min(2047.0f, (fSlow63 * fTemp7)));
			int iTemp117 = int(fTemp116);
			float fTemp118 = std::floor(fTemp116);
			fRec41[0] = ((fTemp115 + (0.999000013f * fRec41[1])) - ((fSlow66 * fVec32[((IOTA - iSlow67) & 4095)]) + (fSlow68 * fVec32[((IOTA - iSlow69) & 4095)])));
			iRec43[0] = ((iRec43[1] + iVec0[1]) % iSlow70);
			float fTemp119 = ((fRec42[1] * (1.0f - float(((iRec43[0] == 0) > 0)))) + (fSlow57 * fTemp65));
			fRec42[0] = (fTemp119 - std::floor(fTemp119));
			float fTemp120 = faust_nuke_faustpower2_f(((2.0f * fRec42[0]) + -1.0f));
			fVec33[0] = fTemp120;
			fRec27[0] = (((fRec4[0] * (((fTemp2 * (fTemp77 - ((fVec20[((IOTA - iTemp79) & 4095)] * (fTemp80 + (1.0f - fTemp78))) + ((fTemp78 - fTemp80) * fVec20[((IOTA - (iTemp79 + 1)) & 4095)])))) + (fSlow48 * (fRec29[0] * fTemp12))) + (fSlow55 * (((fTemp11 * (fTemp82 - fVec21[1])) * fVec1[1]) / fTemp14)))) + (((fTemp17 * ((fConst0 * (fTemp93 + fTemp104)) + (fSlow59 * (fTemp12 * (fTemp108 + (fTemp112 / fTemp19)))))) + ((fTemp55 * ((fSlow59 * (fTemp108 * fTemp12)) + (fConst0 * fTemp93))) * (fTemp57 + (fTemp56 * ((fSlow59 * ((fTemp112 * fTemp12) / fTemp19)) + (fConst0 * fTemp104)))))) + (fTemp58 * (((fTemp2 * (fTemp115 - ((fVec32[((IOTA - iTemp117) & 4095)] * (fTemp118 + (1.0f - fTemp116))) + ((fTemp116 - fTemp118) * fVec32[((IOTA - (iTemp117 + 1)) & 4095)])))) + (fSlow59 * (fRec41[0] * fTemp12))) + (fSlow55 * (((fTemp11 * (fTemp120 - fVec33[1])) * fVec1[1]) / fTemp65)))))) - (((fTemp70 * fRec27[2]) + (2.0f * (fTemp71 * fRec27[1]))) / fTemp72));
			fRec26[0] = ((((fRec27[1] + (0.5f * fRec27[0])) + (0.5f * fRec27[2])) - ((fTemp70 * fRec26[2]) + (2.0f * (fTemp71 * fRec26[1])))) / fTemp72);
			iRec45[0] = (iSlow72 * (iRec45[1] + 1));
			int iTemp121 = (iRec45[0] < iSlow3);
			float fTemp122 = std::exp((0.0f - (fConst1 / (iSlow72?(iTemp121?1.00000001e-07f:fSlow4):fSlow2))));
			fRec44[0] = ((fRec44[1] * fTemp122) + ((iSlow72?(iTemp121?(fSlow7 * float(iRec45[0])):fSlow73):0.0f) * (1.0f - fTemp122)));
			fVec34[0] = fSlow76;
			float fTemp123 = (fRec48[1] + (fConst3 * fVec34[1]));
			fRec48[0] = (fTemp123 - std::floor(fTemp123));
			float fTemp124 = faust_nuke_faustpower2_f(((2.0f * fRec48[0]) + -1.0f));
			fVec35[0] = fTemp124;
			float fTemp125 = (fSlow77 * (fTemp3 * (fTemp124 - fVec35[1])));
			fVec36[(IOTA & 4095)] = fTemp125;
			float fTemp126 = std::max(0.0f, std::min(2047.0f, (fSlow78 * fTemp7)));
			int iTemp127 = int(fTemp126);
			float fTemp128 = std::floor(fTemp126);
			fRec49[0] = ((fTemp125 + (0.999000013f * fRec49[1])) - ((fSlow82 * fVec36[((IOTA - iSlow83) & 4095)]) + (fSlow84 * fVec36[((IOTA - iSlow85) & 4095)])));
			iRec51[0] = ((iRec51[1] + iVec0[1]) % iSlow87);
			float fTemp129 = ((fRec50[1] * (1.0f - float(((iRec51[0] == 0) > 0)))) + (fSlow88 * fTemp14));
			fRec50[0] = (fTemp129 - std::floor(fTemp129));
			float fTemp130 = faust_nuke_faustpower2_f(((2.0f * fRec50[0]) + -1.0f));
			fVec37[0] = fTemp130;
			iRec53[0] = ((iRec53[1] + iVec0[1]) % int((fSlow86 / fTemp19)));
			float fTemp131 = ((fRec52[1] * (1.0f - float(((iRec53[0] == 0) > 0)))) + (fSlow88 * fTemp20));
			fRec52[0] = (fTemp131 - std::floor(fTemp131));
			float fTemp132 = faust_nuke_faustpower2_f(((2.0f * fRec52[0]) + -1.0f));
			fVec38[0] = fTemp132;
			float fTemp133 = std::max((fSlow74 * fTemp19), 23.4489498f);
			float fTemp134 = std::max(20.0f, std::fabs(fTemp133));
			fVec39[0] = fTemp134;
			float fTemp135 = (fRec54[1] + (fConst3 * fVec39[1]));
			fRec54[0] = (fTemp135 - std::floor(fTemp135));
			float fTemp136 = faust_nuke_faustpower2_f(((2.0f * fRec54[0]) + -1.0f));
			fVec40[0] = fTemp136;
			float fTemp137 = ((fTemp3 * (fTemp136 - fVec40[1])) / fTemp134);
			fVec41[(IOTA & 4095)] = fTemp137;
			float fTemp138 = std::max(0.0f, std::min(2047.0f, (fConst0 * (fTemp7 / fTemp133))));
			int iTemp139 = int(fTemp138);
			float fTemp140 = std::floor(fTemp138);
			float fTemp141 = ((fSlow89 * (((fTemp11 * (fTemp132 - fVec38[1])) * fVec1[1]) / fTemp20)) + (0.25f * (fTemp2 * ((fTemp137 - (fVec41[((IOTA - iTemp139) & 4095)] * (fTemp140 + (1.0f - fTemp138)))) - ((fTemp138 - fTemp140) * fVec41[((IOTA - (iTemp139 + 1)) & 4095)])))));
			iRec56[0] = ((iRec56[1] + iVec0[1]) % int((fSlow86 * fTemp33)));
			float fTemp142 = ((fRec55[1] * (1.0f - float(((iRec56[0] == 0) > 0)))) + (fSlow88 * fTemp35));
			fRec55[0] = (fTemp142 - std::floor(fTemp142));
			float fTemp143 = faust_nuke_faustpower2_f(((2.0f * fRec55[0]) + -1.0f));
			fVec42[0] = fTemp143;
			float fTemp144 = std::max((fSlow74 * fTemp34), 23.4489498f);
			float fTemp145 = std::max(20.0f, std::fabs(fTemp144));
			fVec43[0] = fTemp145;
			float fTemp146 = (fRec57[1] + (fConst3 * fVec43[1]));
			fRec57[0] = (fTemp146 - std::floor(fTemp146));
			float fTemp147 = faust_nuke_faustpower2_f(((2.0f * fRec57[0]) + -1.0f));
			fVec44[0] = fTemp147;
			float fTemp148 = ((fTemp3 * (fTemp147 - fVec44[1])) / fTemp145);
			fVec45[(IOTA & 4095)] = fTemp148;
			float fTemp149 = std::max(0.0f, std::min(2047.0f, (fConst0 * (fTemp7 / fTemp144))));
			int iTemp150 = int(fTemp149);
			float fTemp151 = std::floor(fTemp149);
			float fTemp152 = ((fSlow89 * (((fTemp11 * (fTemp143 - fVec42[1])) * fVec1[1]) / fTemp35)) + (0.25f * (fTemp2 * ((fTemp148 - (fVec45[((IOTA - iTemp150) & 4095)] * (fTemp151 + (1.0f - fTemp149)))) - ((fTemp149 - fTemp151) * fVec45[((IOTA - (iTemp150 + 1)) & 4095)])))));
			float fTemp153 = std::max(0.0f, std::min(2047.0f, (fConst5 / fTemp133)));
			int iTemp154 = int(fTemp153);
			float fTemp155 = std::floor(fTemp153);
			fRec58[0] = ((0.999000013f * fRec58[1]) + (fConst2 * ((fTemp137 - (fVec41[((IOTA - iTemp154) & 4095)] * (fTemp155 + (1.0f - fTemp153)))) - ((fTemp153 - fTemp155) * fVec41[((IOTA - (iTemp154 + 1)) & 4095)]))));
			float fTemp156 = (fRec58[0] * fTemp19);
			float fTemp157 = std::max(0.0f, std::min(2047.0f, (fConst5 / fTemp144)));
			int iTemp158 = int(fTemp157);
			float fTemp159 = std::floor(fTemp157);
			fRec59[0] = ((0.999000013f * fRec59[1]) + (fConst2 * ((fTemp148 - (fVec45[((IOTA - iTemp158) & 4095)] * (fTemp159 + (1.0f - fTemp157)))) - ((fTemp157 - fTemp159) * fVec45[((IOTA - (iTemp158 + 1)) & 4095)]))));
			float fTemp160 = (fRec59[0] * fTemp32);
			fVec46[0] = fSlow92;
			float fTemp161 = (fRec60[1] + (fConst3 * fVec46[1]));
			fRec60[0] = (fTemp161 - std::floor(fTemp161));
			float fTemp162 = faust_nuke_faustpower2_f(((2.0f * fRec60[0]) + -1.0f));
			fVec47[0] = fTemp162;
			float fTemp163 = (fSlow93 * (fTemp3 * (fTemp162 - fVec47[1])));
			fVec48[(IOTA & 4095)] = fTemp163;
			float fTemp164 = std::max(0.0f, std::min(2047.0f, (fSlow94 * fTemp7)));
			int iTemp165 = int(fTemp164);
			float fTemp166 = std::floor(fTemp164);
			fRec61[0] = ((fTemp163 + (0.999000013f * fRec61[1])) - ((fSlow97 * fVec48[((IOTA - iSlow98) & 4095)]) + (fSlow99 * fVec48[((IOTA - iSlow100) & 4095)])));
			iRec63[0] = ((iRec63[1] + iVec0[1]) % iSlow101);
			float fTemp167 = ((fRec62[1] * (1.0f - float(((iRec63[0] == 0) > 0)))) + (fSlow88 * fTemp65));
			fRec62[0] = (fTemp167 - std::floor(fTemp167));
			float fTemp168 = faust_nuke_faustpower2_f(((2.0f * fRec62[0]) + -1.0f));
			fVec49[0] = fTemp168;
			fRec47[0] = (((fRec4[0] * (((fTemp2 * (fTemp125 - ((fVec36[((IOTA - iTemp127) & 4095)] * (fTemp128 + (1.0f - fTemp126))) + ((fTemp126 - fTemp128) * fVec36[((IOTA - (iTemp127 + 1)) & 4095)])))) + (fSlow79 * (fRec49[0] * fTemp12))) + (fSlow86 * (((fTemp11 * (fTemp130 - fVec37[1])) * fVec1[1]) / fTemp14)))) + (((fTemp17 * ((fConst0 * (fTemp141 + fTemp152)) + (fSlow90 * (fTemp12 * (fTemp156 + (fTemp160 / fTemp19)))))) + ((fTemp55 * ((fSlow90 * (fTemp156 * fTemp12)) + (fConst0 * fTemp141))) * (fTemp57 + (fTemp56 * ((fSlow90 * ((fTemp160 * fTemp12) / fTemp19)) + (fConst0 * fTemp152)))))) + (fTemp58 * (((fTemp2 * (fTemp163 - ((fVec48[((IOTA - iTemp165) & 4095)] * (fTemp166 + (1.0f - fTemp164))) + ((fTemp164 - fTemp166) * fVec48[((IOTA - (iTemp165 + 1)) & 4095)])))) + (fSlow90 * (fRec61[0] * fTemp12))) + (fSlow86 * (((fTemp11 * (fTemp168 - fVec49[1])) * fVec1[1]) / fTemp65)))))) - (((fTemp70 * fRec47[2]) + (2.0f * (fTemp71 * fRec47[1]))) / fTemp72));
			fRec46[0] = ((((fRec47[1] + (0.5f * fRec47[0])) + (0.5f * fRec47[2])) - ((fTemp70 * fRec46[2]) + (2.0f * (fTemp71 * fRec46[1])))) / fTemp72);
			iRec65[0] = (iSlow103 * (iRec65[1] + 1));
			int iTemp169 = (iRec65[0] < iSlow3);
			float fTemp170 = std::exp((0.0f - (fConst1 / (iSlow103?(iTemp169?1.00000001e-07f:fSlow4):fSlow2))));
			fRec64[0] = ((fRec64[1] * fTemp170) + ((iSlow103?(iTemp169?(fSlow7 * float(iRec65[0])):fSlow104):0.0f) * (1.0f - fTemp170)));
			fVec50[0] = fSlow107;
			float fTemp171 = (fRec68[1] + (fConst3 * fVec50[1]));
			fRec68[0] = (fTemp171 - std::floor(fTemp171));
			float fTemp172 = faust_nuke_faustpower2_f(((2.0f * fRec68[0]) + -1.0f));
			fVec51[0] = fTemp172;
			float fTemp173 = (fSlow108 * (fTemp3 * (fTemp172 - fVec51[1])));
			fVec52[(IOTA & 4095)] = fTemp173;
			float fTemp174 = std::max(0.0f, std::min(2047.0f, (fSlow109 * fTemp7)));
			int iTemp175 = int(fTemp174);
			float fTemp176 = std::floor(fTemp174);
			fRec69[0] = ((fTemp173 + (0.999000013f * fRec69[1])) - ((fSlow113 * fVec52[((IOTA - iSlow114) & 4095)]) + (fSlow115 * fVec52[((IOTA - iSlow116) & 4095)])));
			iRec71[0] = ((iRec71[1] + iVec0[1]) % iSlow118);
			float fTemp177 = ((fRec70[1] * (1.0f - float(((iRec71[0] == 0) > 0)))) + (fSlow119 * fTemp14));
			fRec70[0] = (fTemp177 - std::floor(fTemp177));
			float fTemp178 = faust_nuke_faustpower2_f(((2.0f * fRec70[0]) + -1.0f));
			fVec53[0] = fTemp178;
			iRec73[0] = ((iRec73[1] + iVec0[1]) % int((fSlow117 / fTemp19)));
			float fTemp179 = ((fRec72[1] * (1.0f - float(((iRec73[0] == 0) > 0)))) + (fSlow119 * fTemp20));
			fRec72[0] = (fTemp179 - std::floor(fTemp179));
			float fTemp180 = faust_nuke_faustpower2_f(((2.0f * fRec72[0]) + -1.0f));
			fVec54[0] = fTemp180;
			float fTemp181 = std::max((fSlow105 * fTemp19), 23.4489498f);
			float fTemp182 = std::max(20.0f, std::fabs(fTemp181));
			fVec55[0] = fTemp182;
			float fTemp183 = (fRec74[1] + (fConst3 * fVec55[1]));
			fRec74[0] = (fTemp183 - std::floor(fTemp183));
			float fTemp184 = faust_nuke_faustpower2_f(((2.0f * fRec74[0]) + -1.0f));
			fVec56[0] = fTemp184;
			float fTemp185 = ((fTemp3 * (fTemp184 - fVec56[1])) / fTemp182);
			fVec57[(IOTA & 4095)] = fTemp185;
			float fTemp186 = std::max(0.0f, std::min(2047.0f, (fConst0 * (fTemp7 / fTemp181))));
			int iTemp187 = int(fTemp186);
			float fTemp188 = std::floor(fTemp186);
			float fTemp189 = ((fSlow120 * (((fTemp11 * (fTemp180 - fVec54[1])) * fVec1[1]) / fTemp20)) + (0.25f * (fTemp2 * ((fTemp185 - (fVec57[((IOTA - iTemp187) & 4095)] * (fTemp188 + (1.0f - fTemp186)))) - ((fTemp186 - fTemp188) * fVec57[((IOTA - (iTemp187 + 1)) & 4095)])))));
			iRec76[0] = ((iRec76[1] + iVec0[1]) % int((fSlow117 * fTemp33)));
			float fTemp190 = ((fRec75[1] * (1.0f - float(((iRec76[0] == 0) > 0)))) + (fSlow119 * fTemp35));
			fRec75[0] = (fTemp190 - std::floor(fTemp190));
			float fTemp191 = faust_nuke_faustpower2_f(((2.0f * fRec75[0]) + -1.0f));
			fVec58[0] = fTemp191;
			float fTemp192 = std::max((fSlow105 * fTemp34), 23.4489498f);
			float fTemp193 = std::max(20.0f, std::fabs(fTemp192));
			fVec59[0] = fTemp193;
			float fTemp194 = (fRec77[1] + (fConst3 * fVec59[1]));
			fRec77[0] = (fTemp194 - std::floor(fTemp194));
			float fTemp195 = faust_nuke_faustpower2_f(((2.0f * fRec77[0]) + -1.0f));
			fVec60[0] = fTemp195;
			float fTemp196 = ((fTemp3 * (fTemp195 - fVec60[1])) / fTemp193);
			fVec61[(IOTA & 4095)] = fTemp196;
			float fTemp197 = std::max(0.0f, std::min(2047.0f, (fConst0 * (fTemp7 / fTemp192))));
			int iTemp198 = int(fTemp197);
			float fTemp199 = std::floor(fTemp197);
			float fTemp200 = ((fSlow120 * (((fTemp11 * (fTemp191 - fVec58[1])) * fVec1[1]) / fTemp35)) + (0.25f * (fTemp2 * ((fTemp196 - (fVec61[((IOTA - iTemp198) & 4095)] * (fTemp199 + (1.0f - fTemp197)))) - ((fTemp197 - fTemp199) * fVec61[((IOTA - (iTemp198 + 1)) & 4095)])))));
			float fTemp201 = std::max(0.0f, std::min(2047.0f, (fConst5 / fTemp181)));
			int iTemp202 = int(fTemp201);
			float fTemp203 = std::floor(fTemp201);
			fRec78[0] = ((0.999000013f * fRec78[1]) + (fConst2 * ((fTemp185 - (fVec57[((IOTA - iTemp202) & 4095)] * (fTemp203 + (1.0f - fTemp201)))) - ((fTemp201 - fTemp203) * fVec57[((IOTA - (iTemp202 + 1)) & 4095)]))));
			float fTemp204 = (fRec78[0] * fTemp19);
			float fTemp205 = std::max(0.0f, std::min(2047.0f, (fConst5 / fTemp192)));
			int iTemp206 = int(fTemp205);
			float fTemp207 = std::floor(fTemp205);
			fRec79[0] = ((0.999000013f * fRec79[1]) + (fConst2 * ((fTemp196 - (fVec61[((IOTA - iTemp206) & 4095)] * (fTemp207 + (1.0f - fTemp205)))) - ((fTemp205 - fTemp207) * fVec61[((IOTA - (iTemp206 + 1)) & 4095)]))));
			float fTemp208 = (fRec79[0] * fTemp32);
			fVec62[0] = fSlow123;
			float fTemp209 = (fRec80[1] + (fConst3 * fVec62[1]));
			fRec80[0] = (fTemp209 - std::floor(fTemp209));
			float fTemp210 = faust_nuke_faustpower2_f(((2.0f * fRec80[0]) + -1.0f));
			fVec63[0] = fTemp210;
			float fTemp211 = (fSlow124 * (fTemp3 * (fTemp210 - fVec63[1])));
			fVec64[(IOTA & 4095)] = fTemp211;
			float fTemp212 = std::max(0.0f, std::min(2047.0f, (fSlow125 * fTemp7)));
			int iTemp213 = int(fTemp212);
			float fTemp214 = std::floor(fTemp212);
			fRec81[0] = ((fTemp211 + (0.999000013f * fRec81[1])) - ((fSlow128 * fVec64[((IOTA - iSlow129) & 4095)]) + (fSlow130 * fVec64[((IOTA - iSlow131) & 4095)])));
			iRec83[0] = ((iRec83[1] + iVec0[1]) % iSlow132);
			float fTemp215 = ((fRec82[1] * (1.0f - float(((iRec83[0] == 0) > 0)))) + (fSlow119 * fTemp65));
			fRec82[0] = (fTemp215 - std::floor(fTemp215));
			float fTemp216 = faust_nuke_faustpower2_f(((2.0f * fRec82[0]) + -1.0f));
			fVec65[0] = fTemp216;
			fRec67[0] = (((fRec4[0] * (((fTemp2 * (fTemp173 - ((fVec52[((IOTA - iTemp175) & 4095)] * (fTemp176 + (1.0f - fTemp174))) + ((fTemp174 - fTemp176) * fVec52[((IOTA - (iTemp175 + 1)) & 4095)])))) + (fSlow110 * (fRec69[0] * fTemp12))) + (fSlow117 * (((fTemp11 * (fTemp178 - fVec53[1])) * fVec1[1]) / fTemp14)))) + (((fTemp17 * ((fConst0 * (fTemp189 + fTemp200)) + (fSlow121 * (fTemp12 * (fTemp204 + (fTemp208 / fTemp19)))))) + ((fTemp55 * ((fSlow121 * (fTemp204 * fTemp12)) + (fConst0 * fTemp189))) * (fTemp57 + (fTemp56 * ((fSlow121 * ((fTemp208 * fTemp12) / fTemp19)) + (fConst0 * fTemp200)))))) + (fTemp58 * (((fTemp2 * (fTemp211 - ((fVec64[((IOTA - iTemp213) & 4095)] * (fTemp214 + (1.0f - fTemp212))) + ((fTemp212 - fTemp214) * fVec64[((IOTA - (iTemp213 + 1)) & 4095)])))) + (fSlow121 * (fRec81[0] * fTemp12))) + (fSlow117 * (((fTemp11 * (fTemp216 - fVec65[1])) * fVec1[1]) / fTemp65)))))) - (((fTemp70 * fRec67[2]) + (2.0f * (fTemp71 * fRec67[1]))) / fTemp72));
			fRec66[0] = ((((fRec67[1] + (0.5f * fRec67[0])) + (0.5f * fRec67[2])) - ((fTemp70 * fRec66[2]) + (2.0f * (fTemp71 * fRec66[1])))) / fTemp72);
			iRec85[0] = (iSlow134 * (iRec85[1] + 1));
			int iTemp217 = (iRec85[0] < iSlow3);
			float fTemp218 = std::exp((0.0f - (fConst1 / (iSlow134?(iTemp217?1.00000001e-07f:fSlow4):fSlow2))));
			fRec84[0] = ((fRec84[1] * fTemp218) + ((iSlow134?(iTemp217?(fSlow7 * float(iRec85[0])):fSlow135):0.0f) * (1.0f - fTemp218)));
			fVec66[0] = fSlow138;
			float fTemp219 = (fRec88[1] + (fConst3 * fVec66[1]));
			fRec88[0] = (fTemp219 - std::floor(fTemp219));
			float fTemp220 = faust_nuke_faustpower2_f(((2.0f * fRec88[0]) + -1.0f));
			fVec67[0] = fTemp220;
			float fTemp221 = (fSlow139 * (fTemp3 * (fTemp220 - fVec67[1])));
			fVec68[(IOTA & 4095)] = fTemp221;
			float fTemp222 = std::max(0.0f, std::min(2047.0f, (fSlow140 * fTemp7)));
			int iTemp223 = int(fTemp222);
			float fTemp224 = std::floor(fTemp222);
			fRec89[0] = ((fTemp221 + (0.999000013f * fRec89[1])) - ((fSlow144 * fVec68[((IOTA - iSlow145) & 4095)]) + (fSlow146 * fVec68[((IOTA - iSlow147) & 4095)])));
			iRec91[0] = ((iRec91[1] + iVec0[1]) % iSlow149);
			float fTemp225 = ((fRec90[1] * (1.0f - float(((iRec91[0] == 0) > 0)))) + (fSlow150 * fTemp14));
			fRec90[0] = (fTemp225 - std::floor(fTemp225));
			float fTemp226 = faust_nuke_faustpower2_f(((2.0f * fRec90[0]) + -1.0f));
			fVec69[0] = fTemp226;
			iRec93[0] = ((iRec93[1] + iVec0[1]) % int((fSlow148 / fTemp19)));
			float fTemp227 = ((fRec92[1] * (1.0f - float(((iRec93[0] == 0) > 0)))) + (fSlow150 * fTemp20));
			fRec92[0] = (fTemp227 - std::floor(fTemp227));
			float fTemp228 = faust_nuke_faustpower2_f(((2.0f * fRec92[0]) + -1.0f));
			fVec70[0] = fTemp228;
			float fTemp229 = std::max((fSlow136 * fTemp19), 23.4489498f);
			float fTemp230 = std::max(20.0f, std::fabs(fTemp229));
			fVec71[0] = fTemp230;
			float fTemp231 = (fRec94[1] + (fConst3 * fVec71[1]));
			fRec94[0] = (fTemp231 - std::floor(fTemp231));
			float fTemp232 = faust_nuke_faustpower2_f(((2.0f * fRec94[0]) + -1.0f));
			fVec72[0] = fTemp232;
			float fTemp233 = ((fTemp3 * (fTemp232 - fVec72[1])) / fTemp230);
			fVec73[(IOTA & 4095)] = fTemp233;
			float fTemp234 = std::max(0.0f, std::min(2047.0f, (fConst0 * (fTemp7 / fTemp229))));
			int iTemp235 = int(fTemp234);
			float fTemp236 = std::floor(fTemp234);
			float fTemp237 = ((fSlow151 * (((fTemp11 * (fTemp228 - fVec70[1])) * fVec1[1]) / fTemp20)) + (0.25f * (fTemp2 * ((fTemp233 - (fVec73[((IOTA - iTemp235) & 4095)] * (fTemp236 + (1.0f - fTemp234)))) - ((fTemp234 - fTemp236) * fVec73[((IOTA - (iTemp235 + 1)) & 4095)])))));
			iRec96[0] = ((iRec96[1] + iVec0[1]) % int((fSlow148 * fTemp33)));
			float fTemp238 = ((fRec95[1] * (1.0f - float(((iRec96[0] == 0) > 0)))) + (fSlow150 * fTemp35));
			fRec95[0] = (fTemp238 - std::floor(fTemp238));
			float fTemp239 = faust_nuke_faustpower2_f(((2.0f * fRec95[0]) + -1.0f));
			fVec74[0] = fTemp239;
			float fTemp240 = std::max((fSlow136 * fTemp34), 23.4489498f);
			float fTemp241 = std::max(20.0f, std::fabs(fTemp240));
			fVec75[0] = fTemp241;
			float fTemp242 = (fRec97[1] + (fConst3 * fVec75[1]));
			fRec97[0] = (fTemp242 - std::floor(fTemp242));
			float fTemp243 = faust_nuke_faustpower2_f(((2.0f * fRec97[0]) + -1.0f));
			fVec76[0] = fTemp243;
			float fTemp244 = ((fTemp3 * (fTemp243 - fVec76[1])) / fTemp241);
			fVec77[(IOTA & 4095)] = fTemp244;
			float fTemp245 = std::max(0.0f, std::min(2047.0f, (fConst0 * (fTemp7 / fTemp240))));
			int iTemp246 = int(fTemp245);
			float fTemp247 = std::floor(fTemp245);
			float fTemp248 = ((fSlow151 * (((fTemp11 * (fTemp239 - fVec74[1])) * fVec1[1]) / fTemp35)) + (0.25f * (fTemp2 * ((fTemp244 - (fVec77[((IOTA - iTemp246) & 4095)] * (fTemp247 + (1.0f - fTemp245)))) - ((fTemp245 - fTemp247) * fVec77[((IOTA - (iTemp246 + 1)) & 4095)])))));
			float fTemp249 = std::max(0.0f, std::min(2047.0f, (fConst5 / fTemp229)));
			int iTemp250 = int(fTemp249);
			float fTemp251 = std::floor(fTemp249);
			fRec98[0] = ((0.999000013f * fRec98[1]) + (fConst2 * ((fTemp233 - (fVec73[((IOTA - iTemp250) & 4095)] * (fTemp251 + (1.0f - fTemp249)))) - ((fTemp249 - fTemp251) * fVec73[((IOTA - (iTemp250 + 1)) & 4095)]))));
			float fTemp252 = (fRec98[0] * fTemp19);
			float fTemp253 = std::max(0.0f, std::min(2047.0f, (fConst5 / fTemp240)));
			int iTemp254 = int(fTemp253);
			float fTemp255 = std::floor(fTemp253);
			fRec99[0] = ((0.999000013f * fRec99[1]) + (fConst2 * ((fTemp244 - (fVec77[((IOTA - iTemp254) & 4095)] * (fTemp255 + (1.0f - fTemp253)))) - ((fTemp253 - fTemp255) * fVec77[((IOTA - (iTemp254 + 1)) & 4095)]))));
			float fTemp256 = (fRec99[0] * fTemp32);
			fVec78[0] = fSlow154;
			float fTemp257 = (fRec100[1] + (fConst3 * fVec78[1]));
			fRec100[0] = (fTemp257 - std::floor(fTemp257));
			float fTemp258 = faust_nuke_faustpower2_f(((2.0f * fRec100[0]) + -1.0f));
			fVec79[0] = fTemp258;
			float fTemp259 = (fSlow155 * (fTemp3 * (fTemp258 - fVec79[1])));
			fVec80[(IOTA & 4095)] = fTemp259;
			float fTemp260 = std::max(0.0f, std::min(2047.0f, (fSlow156 * fTemp7)));
			int iTemp261 = int(fTemp260);
			float fTemp262 = std::floor(fTemp260);
			fRec101[0] = ((fTemp259 + (0.999000013f * fRec101[1])) - ((fSlow159 * fVec80[((IOTA - iSlow160) & 4095)]) + (fSlow161 * fVec80[((IOTA - iSlow162) & 4095)])));
			iRec103[0] = ((iRec103[1] + iVec0[1]) % iSlow163);
			float fTemp263 = ((fRec102[1] * (1.0f - float(((iRec103[0] == 0) > 0)))) + (fSlow150 * fTemp65));
			fRec102[0] = (fTemp263 - std::floor(fTemp263));
			float fTemp264 = faust_nuke_faustpower2_f(((2.0f * fRec102[0]) + -1.0f));
			fVec81[0] = fTemp264;
			fRec87[0] = (((fRec4[0] * (((fTemp2 * (fTemp221 - ((fVec68[((IOTA - iTemp223) & 4095)] * (fTemp224 + (1.0f - fTemp222))) + ((fTemp222 - fTemp224) * fVec68[((IOTA - (iTemp223 + 1)) & 4095)])))) + (fSlow141 * (fRec89[0] * fTemp12))) + (fSlow148 * (((fTemp11 * (fTemp226 - fVec69[1])) * fVec1[1]) / fTemp14)))) + (((fTemp17 * ((fConst0 * (fTemp237 + fTemp248)) + (fSlow152 * (fTemp12 * (fTemp252 + (fTemp256 / fTemp19)))))) + ((fTemp55 * ((fSlow152 * (fTemp252 * fTemp12)) + (fConst0 * fTemp237))) * (fTemp57 + (fTemp56 * ((fSlow152 * ((fTemp256 * fTemp12) / fTemp19)) + (fConst0 * fTemp248)))))) + (fTemp58 * (((fTemp2 * (fTemp259 - ((fVec80[((IOTA - iTemp261) & 4095)] * (fTemp262 + (1.0f - fTemp260))) + ((fTemp260 - fTemp262) * fVec80[((IOTA - (iTemp261 + 1)) & 4095)])))) + (fSlow152 * (fRec101[0] * fTemp12))) + (fSlow148 * (((fTemp11 * (fTemp264 - fVec81[1])) * fVec1[1]) / fTemp65)))))) - (((fTemp70 * fRec87[2]) + (2.0f * (fTemp71 * fRec87[1]))) / fTemp72));
			fRec86[0] = ((((fRec87[1] + (0.5f * fRec87[0])) + (0.5f * fRec87[2])) - ((fTemp70 * fRec86[2]) + (2.0f * (fTemp71 * fRec86[1])))) / fTemp72);
			iRec105[0] = (iSlow165 * (iRec105[1] + 1));
			int iTemp265 = (iRec105[0] < iSlow3);
			float fTemp266 = std::exp((0.0f - (fConst1 / (iSlow165?(iTemp265?1.00000001e-07f:fSlow4):fSlow2))));
			fRec104[0] = ((fRec104[1] * fTemp266) + ((iSlow165?(iTemp265?(fSlow7 * float(iRec105[0])):fSlow166):0.0f) * (1.0f - fTemp266)));
			fVec82[0] = fSlow169;
			float fTemp267 = (fRec108[1] + (fConst3 * fVec82[1]));
			fRec108[0] = (fTemp267 - std::floor(fTemp267));
			float fTemp268 = faust_nuke_faustpower2_f(((2.0f * fRec108[0]) + -1.0f));
			fVec83[0] = fTemp268;
			float fTemp269 = (fSlow170 * (fTemp3 * (fTemp268 - fVec83[1])));
			fVec84[(IOTA & 4095)] = fTemp269;
			float fTemp270 = std::max(0.0f, std::min(2047.0f, (fSlow171 * fTemp7)));
			int iTemp271 = int(fTemp270);
			float fTemp272 = std::floor(fTemp270);
			fRec109[0] = ((fTemp269 + (0.999000013f * fRec109[1])) - ((fSlow175 * fVec84[((IOTA - iSlow176) & 4095)]) + (fSlow177 * fVec84[((IOTA - iSlow178) & 4095)])));
			iRec111[0] = ((iRec111[1] + iVec0[1]) % iSlow180);
			float fTemp273 = ((fRec110[1] * (1.0f - float(((iRec111[0] == 0) > 0)))) + (fSlow181 * fTemp14));
			fRec110[0] = (fTemp273 - std::floor(fTemp273));
			float fTemp274 = faust_nuke_faustpower2_f(((2.0f * fRec110[0]) + -1.0f));
			fVec85[0] = fTemp274;
			iRec113[0] = ((iRec113[1] + iVec0[1]) % int((fSlow179 / fTemp19)));
			float fTemp275 = ((fRec112[1] * (1.0f - float(((iRec113[0] == 0) > 0)))) + (fSlow181 * fTemp20));
			fRec112[0] = (fTemp275 - std::floor(fTemp275));
			float fTemp276 = faust_nuke_faustpower2_f(((2.0f * fRec112[0]) + -1.0f));
			fVec86[0] = fTemp276;
			float fTemp277 = std::max((fSlow167 * fTemp19), 23.4489498f);
			float fTemp278 = std::max(20.0f, std::fabs(fTemp277));
			fVec87[0] = fTemp278;
			float fTemp279 = (fRec114[1] + (fConst3 * fVec87[1]));
			fRec114[0] = (fTemp279 - std::floor(fTemp279));
			float fTemp280 = faust_nuke_faustpower2_f(((2.0f * fRec114[0]) + -1.0f));
			fVec88[0] = fTemp280;
			float fTemp281 = ((fTemp3 * (fTemp280 - fVec88[1])) / fTemp278);
			fVec89[(IOTA & 4095)] = fTemp281;
			float fTemp282 = std::max(0.0f, std::min(2047.0f, (fConst0 * (fTemp7 / fTemp277))));
			int iTemp283 = int(fTemp282);
			float fTemp284 = std::floor(fTemp282);
			float fTemp285 = ((fSlow182 * (((fTemp11 * (fTemp276 - fVec86[1])) * fVec1[1]) / fTemp20)) + (0.25f * (fTemp2 * ((fTemp281 - (fVec89[((IOTA - iTemp283) & 4095)] * (fTemp284 + (1.0f - fTemp282)))) - ((fTemp282 - fTemp284) * fVec89[((IOTA - (iTemp283 + 1)) & 4095)])))));
			iRec116[0] = ((iRec116[1] + iVec0[1]) % int((fSlow179 * fTemp33)));
			float fTemp286 = ((fRec115[1] * (1.0f - float(((iRec116[0] == 0) > 0)))) + (fSlow181 * fTemp35));
			fRec115[0] = (fTemp286 - std::floor(fTemp286));
			float fTemp287 = faust_nuke_faustpower2_f(((2.0f * fRec115[0]) + -1.0f));
			fVec90[0] = fTemp287;
			float fTemp288 = std::max((fSlow167 * fTemp34), 23.4489498f);
			float fTemp289 = std::max(20.0f, std::fabs(fTemp288));
			fVec91[0] = fTemp289;
			float fTemp290 = (fRec117[1] + (fConst3 * fVec91[1]));
			fRec117[0] = (fTemp290 - std::floor(fTemp290));
			float fTemp291 = faust_nuke_faustpower2_f(((2.0f * fRec117[0]) + -1.0f));
			fVec92[0] = fTemp291;
			float fTemp292 = ((fTemp3 * (fTemp291 - fVec92[1])) / fTemp289);
			fVec93[(IOTA & 4095)] = fTemp292;
			float fTemp293 = std::max(0.0f, std::min(2047.0f, (fConst0 * (fTemp7 / fTemp288))));
			int iTemp294 = int(fTemp293);
			float fTemp295 = std::floor(fTemp293);
			float fTemp296 = ((fSlow182 * (((fTemp11 * (fTemp287 - fVec90[1])) * fVec1[1]) / fTemp35)) + (0.25f * (fTemp2 * ((fTemp292 - (fVec93[((IOTA - iTemp294) & 4095)] * (fTemp295 + (1.0f - fTemp293)))) - ((fTemp293 - fTemp295) * fVec93[((IOTA - (iTemp294 + 1)) & 4095)])))));
			float fTemp297 = std::max(0.0f, std::min(2047.0f, (fConst5 / fTemp277)));
			int iTemp298 = int(fTemp297);
			float fTemp299 = std::floor(fTemp297);
			fRec118[0] = ((0.999000013f * fRec118[1]) + (fConst2 * ((fTemp281 - (fVec89[((IOTA - iTemp298) & 4095)] * (fTemp299 + (1.0f - fTemp297)))) - ((fTemp297 - fTemp299) * fVec89[((IOTA - (iTemp298 + 1)) & 4095)]))));
			float fTemp300 = (fRec118[0] * fTemp19);
			float fTemp301 = std::max(0.0f, std::min(2047.0f, (fConst5 / fTemp288)));
			int iTemp302 = int(fTemp301);
			float fTemp303 = std::floor(fTemp301);
			fRec119[0] = ((0.999000013f * fRec119[1]) + (fConst2 * ((fTemp292 - (fVec93[((IOTA - iTemp302) & 4095)] * (fTemp303 + (1.0f - fTemp301)))) - ((fTemp301 - fTemp303) * fVec93[((IOTA - (iTemp302 + 1)) & 4095)]))));
			float fTemp304 = (fRec119[0] * fTemp32);
			fVec94[0] = fSlow185;
			float fTemp305 = (fRec120[1] + (fConst3 * fVec94[1]));
			fRec120[0] = (fTemp305 - std::floor(fTemp305));
			float fTemp306 = faust_nuke_faustpower2_f(((2.0f * fRec120[0]) + -1.0f));
			fVec95[0] = fTemp306;
			float fTemp307 = (fSlow186 * (fTemp3 * (fTemp306 - fVec95[1])));
			fVec96[(IOTA & 4095)] = fTemp307;
			float fTemp308 = std::max(0.0f, std::min(2047.0f, (fSlow187 * fTemp7)));
			int iTemp309 = int(fTemp308);
			float fTemp310 = std::floor(fTemp308);
			fRec121[0] = ((fTemp307 + (0.999000013f * fRec121[1])) - ((fSlow190 * fVec96[((IOTA - iSlow191) & 4095)]) + (fSlow192 * fVec96[((IOTA - iSlow193) & 4095)])));
			iRec123[0] = ((iRec123[1] + iVec0[1]) % iSlow194);
			float fTemp311 = ((fRec122[1] * (1.0f - float(((iRec123[0] == 0) > 0)))) + (fSlow181 * fTemp65));
			fRec122[0] = (fTemp311 - std::floor(fTemp311));
			float fTemp312 = faust_nuke_faustpower2_f(((2.0f * fRec122[0]) + -1.0f));
			fVec97[0] = fTemp312;
			fRec107[0] = (((fRec4[0] * (((fTemp2 * (fTemp269 - ((fVec84[((IOTA - iTemp271) & 4095)] * (fTemp272 + (1.0f - fTemp270))) + ((fTemp270 - fTemp272) * fVec84[((IOTA - (iTemp271 + 1)) & 4095)])))) + (fSlow172 * (fRec109[0] * fTemp12))) + (fSlow179 * (((fTemp11 * (fTemp274 - fVec85[1])) * fVec1[1]) / fTemp14)))) + (((fTemp17 * ((fConst0 * (fTemp285 + fTemp296)) + (fSlow183 * (fTemp12 * (fTemp300 + (fTemp304 / fTemp19)))))) + ((fTemp55 * ((fSlow183 * (fTemp300 * fTemp12)) + (fConst0 * fTemp285))) * (fTemp57 + (fTemp56 * ((fSlow183 * ((fTemp304 * fTemp12) / fTemp19)) + (fConst0 * fTemp296)))))) + (fTemp58 * (((fTemp2 * (fTemp307 - ((fVec96[((IOTA - iTemp309) & 4095)] * (fTemp310 + (1.0f - fTemp308))) + ((fTemp308 - fTemp310) * fVec96[((IOTA - (iTemp309 + 1)) & 4095)])))) + (fSlow183 * (fRec121[0] * fTemp12))) + (fSlow179 * (((fTemp11 * (fTemp312 - fVec97[1])) * fVec1[1]) / fTemp65)))))) - (((fTemp70 * fRec107[2]) + (2.0f * (fTemp71 * fRec107[1]))) / fTemp72));
			fRec106[0] = ((((fRec107[1] + (0.5f * fRec107[0])) + (0.5f * fRec107[2])) - ((fTemp70 * fRec106[2]) + (2.0f * (fTemp71 * fRec106[1])))) / fTemp72);
			output0[i] = FAUSTFLOAT((((((((fSlow0 * (fRec0[0] * ((fRec2[1] + (0.5f * fRec2[0])) + (0.5f * fRec2[2])))) + (fSlow40 * (fRec24[0] * ((fRec26[1] + (0.5f * fRec26[0])) + (0.5f * fRec26[2]))))) + (fSlow71 * (fRec44[0] * ((fRec46[1] + (0.5f * fRec46[0])) + (0.5f * fRec46[2]))))) + (fSlow102 * (fRec64[0] * ((fRec66[1] + (0.5f * fRec66[0])) + (0.5f * fRec66[2]))))) + (fSlow133 * (fRec84[0] * ((fRec86[1] + (0.5f * fRec86[0])) + (0.5f * fRec86[2]))))) + (fSlow164 * (fRec104[0] * ((fRec106[1] + (0.5f * fRec106[0])) + (0.5f * fRec106[2]))))) / fTemp72));
			iVec0[1] = iVec0[0];
			iRec1[1] = iRec1[0];
			fRec0[1] = fRec0[0];
			fRec4[1] = fRec4[0];
			fRec5[1] = fRec5[0];
			fVec1[1] = fVec1[0];
			fVec2[1] = fVec2[0];
			fRec6[1] = fRec6[0];
			fVec3[1] = fVec3[0];
			IOTA = (IOTA + 1);
			fRec7[1] = fRec7[0];
			iRec9[1] = iRec9[0];
			fRec8[1] = fRec8[0];
			fVec5[1] = fVec5[0];
			fRec10[1] = fRec10[0];
			iRec12[1] = iRec12[0];
			fRec11[1] = fRec11[0];
			fVec6[1] = fVec6[0];
			fVec7[1] = fVec7[0];
			fRec13[1] = fRec13[0];
			fVec8[1] = fVec8[0];
			iRec15[1] = iRec15[0];
			fRec14[1] = fRec14[0];
			fVec10[1] = fVec10[0];
			fVec11[1] = fVec11[0];
			fRec16[1] = fRec16[0];
			fVec12[1] = fVec12[0];
			fRec17[1] = fRec17[0];
			fRec18[1] = fRec18[0];
			fVec14[1] = fVec14[0];
			fRec19[1] = fRec19[0];
			fVec15[1] = fVec15[0];
			fRec20[1] = fRec20[0];
			iRec22[1] = iRec22[0];
			fRec21[1] = fRec21[0];
			fVec17[1] = fVec17[0];
			fRec23[1] = fRec23[0];
			fRec3[2] = fRec3[1];
			fRec3[1] = fRec3[0];
			fRec2[2] = fRec2[1];
			fRec2[1] = fRec2[0];
			iRec25[1] = iRec25[0];
			fRec24[1] = fRec24[0];
			fVec18[1] = fVec18[0];
			fRec28[1] = fRec28[0];
			fVec19[1] = fVec19[0];
			fRec29[1] = fRec29[0];
			iRec31[1] = iRec31[0];
			fRec30[1] = fRec30[0];
			fVec21[1] = fVec21[0];
			iRec33[1] = iRec33[0];
			fRec32[1] = fRec32[0];
			fVec22[1] = fVec22[0];
			fVec23[1] = fVec23[0];
			fRec34[1] = fRec34[0];
			fVec24[1] = fVec24[0];
			iRec36[1] = iRec36[0];
			fRec35[1] = fRec35[0];
			fVec26[1] = fVec26[0];
			fVec27[1] = fVec27[0];
			fRec37[1] = fRec37[0];
			fVec28[1] = fVec28[0];
			fRec38[1] = fRec38[0];
			fRec39[1] = fRec39[0];
			fVec30[1] = fVec30[0];
			fRec40[1] = fRec40[0];
			fVec31[1] = fVec31[0];
			fRec41[1] = fRec41[0];
			iRec43[1] = iRec43[0];
			fRec42[1] = fRec42[0];
			fVec33[1] = fVec33[0];
			fRec27[2] = fRec27[1];
			fRec27[1] = fRec27[0];
			fRec26[2] = fRec26[1];
			fRec26[1] = fRec26[0];
			iRec45[1] = iRec45[0];
			fRec44[1] = fRec44[0];
			fVec34[1] = fVec34[0];
			fRec48[1] = fRec48[0];
			fVec35[1] = fVec35[0];
			fRec49[1] = fRec49[0];
			iRec51[1] = iRec51[0];
			fRec50[1] = fRec50[0];
			fVec37[1] = fVec37[0];
			iRec53[1] = iRec53[0];
			fRec52[1] = fRec52[0];
			fVec38[1] = fVec38[0];
			fVec39[1] = fVec39[0];
			fRec54[1] = fRec54[0];
			fVec40[1] = fVec40[0];
			iRec56[1] = iRec56[0];
			fRec55[1] = fRec55[0];
			fVec42[1] = fVec42[0];
			fVec43[1] = fVec43[0];
			fRec57[1] = fRec57[0];
			fVec44[1] = fVec44[0];
			fRec58[1] = fRec58[0];
			fRec59[1] = fRec59[0];
			fVec46[1] = fVec46[0];
			fRec60[1] = fRec60[0];
			fVec47[1] = fVec47[0];
			fRec61[1] = fRec61[0];
			iRec63[1] = iRec63[0];
			fRec62[1] = fRec62[0];
			fVec49[1] = fVec49[0];
			fRec47[2] = fRec47[1];
			fRec47[1] = fRec47[0];
			fRec46[2] = fRec46[1];
			fRec46[1] = fRec46[0];
			iRec65[1] = iRec65[0];
			fRec64[1] = fRec64[0];
			fVec50[1] = fVec50[0];
			fRec68[1] = fRec68[0];
			fVec51[1] = fVec51[0];
			fRec69[1] = fRec69[0];
			iRec71[1] = iRec71[0];
			fRec70[1] = fRec70[0];
			fVec53[1] = fVec53[0];
			iRec73[1] = iRec73[0];
			fRec72[1] = fRec72[0];
			fVec54[1] = fVec54[0];
			fVec55[1] = fVec55[0];
			fRec74[1] = fRec74[0];
			fVec56[1] = fVec56[0];
			iRec76[1] = iRec76[0];
			fRec75[1] = fRec75[0];
			fVec58[1] = fVec58[0];
			fVec59[1] = fVec59[0];
			fRec77[1] = fRec77[0];
			fVec60[1] = fVec60[0];
			fRec78[1] = fRec78[0];
			fRec79[1] = fRec79[0];
			fVec62[1] = fVec62[0];
			fRec80[1] = fRec80[0];
			fVec63[1] = fVec63[0];
			fRec81[1] = fRec81[0];
			iRec83[1] = iRec83[0];
			fRec82[1] = fRec82[0];
			fVec65[1] = fVec65[0];
			fRec67[2] = fRec67[1];
			fRec67[1] = fRec67[0];
			fRec66[2] = fRec66[1];
			fRec66[1] = fRec66[0];
			iRec85[1] = iRec85[0];
			fRec84[1] = fRec84[0];
			fVec66[1] = fVec66[0];
			fRec88[1] = fRec88[0];
			fVec67[1] = fVec67[0];
			fRec89[1] = fRec89[0];
			iRec91[1] = iRec91[0];
			fRec90[1] = fRec90[0];
			fVec69[1] = fVec69[0];
			iRec93[1] = iRec93[0];
			fRec92[1] = fRec92[0];
			fVec70[1] = fVec70[0];
			fVec71[1] = fVec71[0];
			fRec94[1] = fRec94[0];
			fVec72[1] = fVec72[0];
			iRec96[1] = iRec96[0];
			fRec95[1] = fRec95[0];
			fVec74[1] = fVec74[0];
			fVec75[1] = fVec75[0];
			fRec97[1] = fRec97[0];
			fVec76[1] = fVec76[0];
			fRec98[1] = fRec98[0];
			fRec99[1] = fRec99[0];
			fVec78[1] = fVec78[0];
			fRec100[1] = fRec100[0];
			fVec79[1] = fVec79[0];
			fRec101[1] = fRec101[0];
			iRec103[1] = iRec103[0];
			fRec102[1] = fRec102[0];
			fVec81[1] = fVec81[0];
			fRec87[2] = fRec87[1];
			fRec87[1] = fRec87[0];
			fRec86[2] = fRec86[1];
			fRec86[1] = fRec86[0];
			iRec105[1] = iRec105[0];
			fRec104[1] = fRec104[0];
			fVec82[1] = fVec82[0];
			fRec108[1] = fRec108[0];
			fVec83[1] = fVec83[0];
			fRec109[1] = fRec109[0];
			iRec111[1] = iRec111[0];
			fRec110[1] = fRec110[0];
			fVec85[1] = fVec85[0];
			iRec113[1] = iRec113[0];
			fRec112[1] = fRec112[0];
			fVec86[1] = fVec86[0];
			fVec87[1] = fVec87[0];
			fRec114[1] = fRec114[0];
			fVec88[1] = fVec88[0];
			iRec116[1] = iRec116[0];
			fRec115[1] = fRec115[0];
			fVec90[1] = fVec90[0];
			fVec91[1] = fVec91[0];
			fRec117[1] = fRec117[0];
			fVec92[1] = fVec92[0];
			fRec118[1] = fRec118[0];
			fRec119[1] = fRec119[0];
			fVec94[1] = fVec94[0];
			fRec120[1] = fRec120[0];
			fVec95[1] = fVec95[0];
			fRec121[1] = fRec121[0];
			iRec123[1] = iRec123[0];
			fRec122[1] = fRec122[0];
			fVec97[1] = fVec97[0];
			fRec107[2] = fRec107[1];
			fRec107[1] = fRec107[0];
			fRec106[2] = fRec106[1];
			fRec106[1] = fRec106[0];
			
		}
		
	}

	
};

#endif
