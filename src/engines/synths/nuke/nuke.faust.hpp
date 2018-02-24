/* ------------------------------------------------------------
name: "nuke"
Code generated with Faust 2.5.16 (https://faust.grame.fr)
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

#include <cmath>
#include <math.h>

float faust_nuke_faustpower2_f(float value) {
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
	float fVec1[2];
	float fConst2;
	FAUSTFLOAT fHslider6;
	float fVec2[2];
	float fConst3;
	float fRec5[2];
	float fVec3[2];
	int IOTA;
	float fVec4[4096];
	float fConst4;
	float fConst5;
	float fRec6[2];
	float fConst6;
	int iRec8[2];
	float fConst7;
	float fRec7[2];
	float fVec5[2];
	FAUSTFLOAT fHslider7;
	float fRec9[2];
	FAUSTFLOAT fHslider8;
	FAUSTFLOAT fHbargraph0;
	float fRec10[2];
	float fVec6[2];
	float fRec11[2];
	float fVec7[2];
	float fVec8[4096];
	float fConst8;
	float fRec12[2];
	int iRec14[2];
	float fRec13[2];
	float fVec9[2];
	float fVec10[2];
	float fRec15[2];
	float fVec11[2];
	float fVec12[4096];
	float fRec16[2];
	int iRec18[2];
	float fRec17[2];
	float fVec13[2];
	float fVec14[2];
	float fRec19[2];
	float fVec15[2];
	float fVec16[4096];
	float fRec20[2];
	int iRec22[2];
	float fRec21[2];
	float fVec17[2];
	int iRec23[2];
	float fConst9;
	FAUSTFLOAT fHslider9;
	float fRec24[2];
	FAUSTFLOAT fHbargraph1;
	float fRec25[2];
	float fRec3[3];
	float fRec2[3];
	FAUSTFLOAT fHslider10;
	FAUSTFLOAT fButton1;
	int iRec27[2];
	float fRec26[2];
	FAUSTFLOAT fHslider11;
	float fVec18[2];
	float fRec30[2];
	float fVec19[2];
	float fVec20[4096];
	float fRec31[2];
	int iRec33[2];
	float fRec32[2];
	float fVec21[2];
	float fVec22[2];
	float fRec34[2];
	float fVec23[2];
	float fVec24[4096];
	float fRec35[2];
	int iRec37[2];
	float fRec36[2];
	float fVec25[2];
	float fVec26[2];
	float fRec38[2];
	float fVec27[2];
	float fVec28[4096];
	float fRec39[2];
	int iRec41[2];
	float fRec40[2];
	float fVec29[2];
	float fVec30[2];
	float fRec42[2];
	float fVec31[2];
	float fVec32[4096];
	float fRec43[2];
	int iRec45[2];
	float fRec44[2];
	float fVec33[2];
	float fRec29[3];
	float fRec28[3];
	FAUSTFLOAT fHslider12;
	FAUSTFLOAT fButton2;
	int iRec47[2];
	float fRec46[2];
	FAUSTFLOAT fHslider13;
	float fVec34[2];
	float fRec50[2];
	float fVec35[2];
	float fVec36[4096];
	float fRec51[2];
	int iRec53[2];
	float fRec52[2];
	float fVec37[2];
	float fVec38[2];
	float fRec54[2];
	float fVec39[2];
	float fVec40[4096];
	float fRec55[2];
	int iRec57[2];
	float fRec56[2];
	float fVec41[2];
	float fVec42[2];
	float fRec58[2];
	float fVec43[2];
	float fVec44[4096];
	float fRec59[2];
	int iRec61[2];
	float fRec60[2];
	float fVec45[2];
	float fVec46[2];
	float fRec62[2];
	float fVec47[2];
	float fVec48[4096];
	float fRec63[2];
	int iRec65[2];
	float fRec64[2];
	float fVec49[2];
	float fRec49[3];
	float fRec48[3];
	FAUSTFLOAT fHslider14;
	FAUSTFLOAT fButton3;
	int iRec67[2];
	float fRec66[2];
	FAUSTFLOAT fHslider15;
	float fVec50[2];
	float fRec70[2];
	float fVec51[2];
	float fVec52[4096];
	float fRec71[2];
	int iRec73[2];
	float fRec72[2];
	float fVec53[2];
	float fVec54[2];
	float fRec74[2];
	float fVec55[2];
	float fVec56[4096];
	float fRec75[2];
	int iRec77[2];
	float fRec76[2];
	float fVec57[2];
	float fVec58[2];
	float fRec78[2];
	float fVec59[2];
	float fVec60[4096];
	float fRec79[2];
	int iRec81[2];
	float fRec80[2];
	float fVec61[2];
	float fVec62[2];
	float fRec82[2];
	float fVec63[2];
	float fVec64[4096];
	float fRec83[2];
	int iRec85[2];
	float fRec84[2];
	float fVec65[2];
	float fRec69[3];
	float fRec68[3];
	FAUSTFLOAT fHslider16;
	FAUSTFLOAT fButton4;
	int iRec87[2];
	float fRec86[2];
	FAUSTFLOAT fHslider17;
	float fVec66[2];
	float fRec90[2];
	float fVec67[2];
	float fVec68[4096];
	float fRec91[2];
	int iRec93[2];
	float fRec92[2];
	float fVec69[2];
	float fVec70[2];
	float fRec94[2];
	float fVec71[2];
	float fVec72[4096];
	float fRec95[2];
	int iRec97[2];
	float fRec96[2];
	float fVec73[2];
	float fVec74[2];
	float fRec98[2];
	float fVec75[2];
	float fVec76[4096];
	float fRec99[2];
	int iRec101[2];
	float fRec100[2];
	float fVec77[2];
	float fVec78[2];
	float fRec102[2];
	float fVec79[2];
	float fVec80[4096];
	float fRec103[2];
	int iRec105[2];
	float fRec104[2];
	float fVec81[2];
	float fRec89[3];
	float fRec88[3];
	FAUSTFLOAT fHslider18;
	FAUSTFLOAT fButton5;
	int iRec107[2];
	float fRec106[2];
	FAUSTFLOAT fHslider19;
	float fVec82[2];
	float fRec110[2];
	float fVec83[2];
	float fVec84[4096];
	float fRec111[2];
	int iRec113[2];
	float fRec112[2];
	float fVec85[2];
	float fVec86[2];
	float fRec114[2];
	float fVec87[2];
	float fVec88[4096];
	float fRec115[2];
	int iRec117[2];
	float fRec116[2];
	float fVec89[2];
	float fVec90[2];
	float fRec118[2];
	float fVec91[2];
	float fVec92[4096];
	float fRec119[2];
	int iRec121[2];
	float fRec120[2];
	float fVec93[2];
	float fVec94[2];
	float fRec122[2];
	float fVec95[2];
	float fVec96[4096];
	float fRec123[2];
	int iRec125[2];
	float fRec124[2];
	float fVec97[2];
	float fRec109[3];
	float fRec108[3];
	
 public:
	
	void metadata(Meta* m) { 
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.0");
		m->declare("envelopes.lib/author", "GRAME");
		m->declare("envelopes.lib/copyright", "GRAME");
		m->declare("envelopes.lib/license", "LGPL with exception");
		m->declare("envelopes.lib/name", "Faust Envelope Library");
		m->declare("envelopes.lib/version", "0.0");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/version", "0.0");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.1");
		m->declare("name", "nuke");
		m->declare("noises.lib/name", "Faust Noise Generator Library");
		m->declare("noises.lib/version", "0.0");
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
		fConst0 = min(192000.0f, max(1.0f, float(fSamplingFreq)));
		fConst1 = (6.90999985f / fConst0);
		fConst2 = (0.25f * fConst0);
		fConst3 = (1.0f / fConst0);
		fConst4 = (2.5999999f / fConst0);
		fConst5 = (0.5f * fConst0);
		fConst6 = (2.0f * fConst0);
		fConst7 = (1.0f / fConst0);
		fConst8 = (5.19999981f / fConst0);
		fConst9 = (3.14159274f / fConst0);
		
	}
	
	virtual void instanceResetUserInterface() {
		fHslider0 = FAUSTFLOAT(0.5f);
		fButton0 = FAUSTFLOAT(0.0f);
		fHslider1 = FAUSTFLOAT(0.0f);
		fHslider2 = FAUSTFLOAT(0.001f);
		fHslider3 = FAUSTFLOAT(0.0f);
		fHslider4 = FAUSTFLOAT(1.0f);
		fHslider5 = FAUSTFLOAT(0.0f);
		fHslider6 = FAUSTFLOAT(440.0f);
		fHslider7 = FAUSTFLOAT(0.0f);
		fHslider8 = FAUSTFLOAT(2.0f);
		fHslider9 = FAUSTFLOAT(20.0f);
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
			fVec1[l4] = 0.0f;
			
		}
		for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			fVec2[l5] = 0.0f;
			
		}
		for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			fRec5[l6] = 0.0f;
			
		}
		for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			fVec3[l7] = 0.0f;
			
		}
		IOTA = 0;
		for (int l8 = 0; (l8 < 4096); l8 = (l8 + 1)) {
			fVec4[l8] = 0.0f;
			
		}
		for (int l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			fRec6[l9] = 0.0f;
			
		}
		for (int l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
			iRec8[l10] = 0;
			
		}
		for (int l11 = 0; (l11 < 2); l11 = (l11 + 1)) {
			fRec7[l11] = 0.0f;
			
		}
		for (int l12 = 0; (l12 < 2); l12 = (l12 + 1)) {
			fVec5[l12] = 0.0f;
			
		}
		for (int l13 = 0; (l13 < 2); l13 = (l13 + 1)) {
			fRec9[l13] = 0.0f;
			
		}
		for (int l14 = 0; (l14 < 2); l14 = (l14 + 1)) {
			fRec10[l14] = 0.0f;
			
		}
		for (int l15 = 0; (l15 < 2); l15 = (l15 + 1)) {
			fVec6[l15] = 0.0f;
			
		}
		for (int l16 = 0; (l16 < 2); l16 = (l16 + 1)) {
			fRec11[l16] = 0.0f;
			
		}
		for (int l17 = 0; (l17 < 2); l17 = (l17 + 1)) {
			fVec7[l17] = 0.0f;
			
		}
		for (int l18 = 0; (l18 < 4096); l18 = (l18 + 1)) {
			fVec8[l18] = 0.0f;
			
		}
		for (int l19 = 0; (l19 < 2); l19 = (l19 + 1)) {
			fRec12[l19] = 0.0f;
			
		}
		for (int l20 = 0; (l20 < 2); l20 = (l20 + 1)) {
			iRec14[l20] = 0;
			
		}
		for (int l21 = 0; (l21 < 2); l21 = (l21 + 1)) {
			fRec13[l21] = 0.0f;
			
		}
		for (int l22 = 0; (l22 < 2); l22 = (l22 + 1)) {
			fVec9[l22] = 0.0f;
			
		}
		for (int l23 = 0; (l23 < 2); l23 = (l23 + 1)) {
			fVec10[l23] = 0.0f;
			
		}
		for (int l24 = 0; (l24 < 2); l24 = (l24 + 1)) {
			fRec15[l24] = 0.0f;
			
		}
		for (int l25 = 0; (l25 < 2); l25 = (l25 + 1)) {
			fVec11[l25] = 0.0f;
			
		}
		for (int l26 = 0; (l26 < 4096); l26 = (l26 + 1)) {
			fVec12[l26] = 0.0f;
			
		}
		for (int l27 = 0; (l27 < 2); l27 = (l27 + 1)) {
			fRec16[l27] = 0.0f;
			
		}
		for (int l28 = 0; (l28 < 2); l28 = (l28 + 1)) {
			iRec18[l28] = 0;
			
		}
		for (int l29 = 0; (l29 < 2); l29 = (l29 + 1)) {
			fRec17[l29] = 0.0f;
			
		}
		for (int l30 = 0; (l30 < 2); l30 = (l30 + 1)) {
			fVec13[l30] = 0.0f;
			
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
			iRec23[l39] = 0;
			
		}
		for (int l40 = 0; (l40 < 2); l40 = (l40 + 1)) {
			fRec24[l40] = 0.0f;
			
		}
		for (int l41 = 0; (l41 < 2); l41 = (l41 + 1)) {
			fRec25[l41] = 0.0f;
			
		}
		for (int l42 = 0; (l42 < 3); l42 = (l42 + 1)) {
			fRec3[l42] = 0.0f;
			
		}
		for (int l43 = 0; (l43 < 3); l43 = (l43 + 1)) {
			fRec2[l43] = 0.0f;
			
		}
		for (int l44 = 0; (l44 < 2); l44 = (l44 + 1)) {
			iRec27[l44] = 0;
			
		}
		for (int l45 = 0; (l45 < 2); l45 = (l45 + 1)) {
			fRec26[l45] = 0.0f;
			
		}
		for (int l46 = 0; (l46 < 2); l46 = (l46 + 1)) {
			fVec18[l46] = 0.0f;
			
		}
		for (int l47 = 0; (l47 < 2); l47 = (l47 + 1)) {
			fRec30[l47] = 0.0f;
			
		}
		for (int l48 = 0; (l48 < 2); l48 = (l48 + 1)) {
			fVec19[l48] = 0.0f;
			
		}
		for (int l49 = 0; (l49 < 4096); l49 = (l49 + 1)) {
			fVec20[l49] = 0.0f;
			
		}
		for (int l50 = 0; (l50 < 2); l50 = (l50 + 1)) {
			fRec31[l50] = 0.0f;
			
		}
		for (int l51 = 0; (l51 < 2); l51 = (l51 + 1)) {
			iRec33[l51] = 0;
			
		}
		for (int l52 = 0; (l52 < 2); l52 = (l52 + 1)) {
			fRec32[l52] = 0.0f;
			
		}
		for (int l53 = 0; (l53 < 2); l53 = (l53 + 1)) {
			fVec21[l53] = 0.0f;
			
		}
		for (int l54 = 0; (l54 < 2); l54 = (l54 + 1)) {
			fVec22[l54] = 0.0f;
			
		}
		for (int l55 = 0; (l55 < 2); l55 = (l55 + 1)) {
			fRec34[l55] = 0.0f;
			
		}
		for (int l56 = 0; (l56 < 2); l56 = (l56 + 1)) {
			fVec23[l56] = 0.0f;
			
		}
		for (int l57 = 0; (l57 < 4096); l57 = (l57 + 1)) {
			fVec24[l57] = 0.0f;
			
		}
		for (int l58 = 0; (l58 < 2); l58 = (l58 + 1)) {
			fRec35[l58] = 0.0f;
			
		}
		for (int l59 = 0; (l59 < 2); l59 = (l59 + 1)) {
			iRec37[l59] = 0;
			
		}
		for (int l60 = 0; (l60 < 2); l60 = (l60 + 1)) {
			fRec36[l60] = 0.0f;
			
		}
		for (int l61 = 0; (l61 < 2); l61 = (l61 + 1)) {
			fVec25[l61] = 0.0f;
			
		}
		for (int l62 = 0; (l62 < 2); l62 = (l62 + 1)) {
			fVec26[l62] = 0.0f;
			
		}
		for (int l63 = 0; (l63 < 2); l63 = (l63 + 1)) {
			fRec38[l63] = 0.0f;
			
		}
		for (int l64 = 0; (l64 < 2); l64 = (l64 + 1)) {
			fVec27[l64] = 0.0f;
			
		}
		for (int l65 = 0; (l65 < 4096); l65 = (l65 + 1)) {
			fVec28[l65] = 0.0f;
			
		}
		for (int l66 = 0; (l66 < 2); l66 = (l66 + 1)) {
			fRec39[l66] = 0.0f;
			
		}
		for (int l67 = 0; (l67 < 2); l67 = (l67 + 1)) {
			iRec41[l67] = 0;
			
		}
		for (int l68 = 0; (l68 < 2); l68 = (l68 + 1)) {
			fRec40[l68] = 0.0f;
			
		}
		for (int l69 = 0; (l69 < 2); l69 = (l69 + 1)) {
			fVec29[l69] = 0.0f;
			
		}
		for (int l70 = 0; (l70 < 2); l70 = (l70 + 1)) {
			fVec30[l70] = 0.0f;
			
		}
		for (int l71 = 0; (l71 < 2); l71 = (l71 + 1)) {
			fRec42[l71] = 0.0f;
			
		}
		for (int l72 = 0; (l72 < 2); l72 = (l72 + 1)) {
			fVec31[l72] = 0.0f;
			
		}
		for (int l73 = 0; (l73 < 4096); l73 = (l73 + 1)) {
			fVec32[l73] = 0.0f;
			
		}
		for (int l74 = 0; (l74 < 2); l74 = (l74 + 1)) {
			fRec43[l74] = 0.0f;
			
		}
		for (int l75 = 0; (l75 < 2); l75 = (l75 + 1)) {
			iRec45[l75] = 0;
			
		}
		for (int l76 = 0; (l76 < 2); l76 = (l76 + 1)) {
			fRec44[l76] = 0.0f;
			
		}
		for (int l77 = 0; (l77 < 2); l77 = (l77 + 1)) {
			fVec33[l77] = 0.0f;
			
		}
		for (int l78 = 0; (l78 < 3); l78 = (l78 + 1)) {
			fRec29[l78] = 0.0f;
			
		}
		for (int l79 = 0; (l79 < 3); l79 = (l79 + 1)) {
			fRec28[l79] = 0.0f;
			
		}
		for (int l80 = 0; (l80 < 2); l80 = (l80 + 1)) {
			iRec47[l80] = 0;
			
		}
		for (int l81 = 0; (l81 < 2); l81 = (l81 + 1)) {
			fRec46[l81] = 0.0f;
			
		}
		for (int l82 = 0; (l82 < 2); l82 = (l82 + 1)) {
			fVec34[l82] = 0.0f;
			
		}
		for (int l83 = 0; (l83 < 2); l83 = (l83 + 1)) {
			fRec50[l83] = 0.0f;
			
		}
		for (int l84 = 0; (l84 < 2); l84 = (l84 + 1)) {
			fVec35[l84] = 0.0f;
			
		}
		for (int l85 = 0; (l85 < 4096); l85 = (l85 + 1)) {
			fVec36[l85] = 0.0f;
			
		}
		for (int l86 = 0; (l86 < 2); l86 = (l86 + 1)) {
			fRec51[l86] = 0.0f;
			
		}
		for (int l87 = 0; (l87 < 2); l87 = (l87 + 1)) {
			iRec53[l87] = 0;
			
		}
		for (int l88 = 0; (l88 < 2); l88 = (l88 + 1)) {
			fRec52[l88] = 0.0f;
			
		}
		for (int l89 = 0; (l89 < 2); l89 = (l89 + 1)) {
			fVec37[l89] = 0.0f;
			
		}
		for (int l90 = 0; (l90 < 2); l90 = (l90 + 1)) {
			fVec38[l90] = 0.0f;
			
		}
		for (int l91 = 0; (l91 < 2); l91 = (l91 + 1)) {
			fRec54[l91] = 0.0f;
			
		}
		for (int l92 = 0; (l92 < 2); l92 = (l92 + 1)) {
			fVec39[l92] = 0.0f;
			
		}
		for (int l93 = 0; (l93 < 4096); l93 = (l93 + 1)) {
			fVec40[l93] = 0.0f;
			
		}
		for (int l94 = 0; (l94 < 2); l94 = (l94 + 1)) {
			fRec55[l94] = 0.0f;
			
		}
		for (int l95 = 0; (l95 < 2); l95 = (l95 + 1)) {
			iRec57[l95] = 0;
			
		}
		for (int l96 = 0; (l96 < 2); l96 = (l96 + 1)) {
			fRec56[l96] = 0.0f;
			
		}
		for (int l97 = 0; (l97 < 2); l97 = (l97 + 1)) {
			fVec41[l97] = 0.0f;
			
		}
		for (int l98 = 0; (l98 < 2); l98 = (l98 + 1)) {
			fVec42[l98] = 0.0f;
			
		}
		for (int l99 = 0; (l99 < 2); l99 = (l99 + 1)) {
			fRec58[l99] = 0.0f;
			
		}
		for (int l100 = 0; (l100 < 2); l100 = (l100 + 1)) {
			fVec43[l100] = 0.0f;
			
		}
		for (int l101 = 0; (l101 < 4096); l101 = (l101 + 1)) {
			fVec44[l101] = 0.0f;
			
		}
		for (int l102 = 0; (l102 < 2); l102 = (l102 + 1)) {
			fRec59[l102] = 0.0f;
			
		}
		for (int l103 = 0; (l103 < 2); l103 = (l103 + 1)) {
			iRec61[l103] = 0;
			
		}
		for (int l104 = 0; (l104 < 2); l104 = (l104 + 1)) {
			fRec60[l104] = 0.0f;
			
		}
		for (int l105 = 0; (l105 < 2); l105 = (l105 + 1)) {
			fVec45[l105] = 0.0f;
			
		}
		for (int l106 = 0; (l106 < 2); l106 = (l106 + 1)) {
			fVec46[l106] = 0.0f;
			
		}
		for (int l107 = 0; (l107 < 2); l107 = (l107 + 1)) {
			fRec62[l107] = 0.0f;
			
		}
		for (int l108 = 0; (l108 < 2); l108 = (l108 + 1)) {
			fVec47[l108] = 0.0f;
			
		}
		for (int l109 = 0; (l109 < 4096); l109 = (l109 + 1)) {
			fVec48[l109] = 0.0f;
			
		}
		for (int l110 = 0; (l110 < 2); l110 = (l110 + 1)) {
			fRec63[l110] = 0.0f;
			
		}
		for (int l111 = 0; (l111 < 2); l111 = (l111 + 1)) {
			iRec65[l111] = 0;
			
		}
		for (int l112 = 0; (l112 < 2); l112 = (l112 + 1)) {
			fRec64[l112] = 0.0f;
			
		}
		for (int l113 = 0; (l113 < 2); l113 = (l113 + 1)) {
			fVec49[l113] = 0.0f;
			
		}
		for (int l114 = 0; (l114 < 3); l114 = (l114 + 1)) {
			fRec49[l114] = 0.0f;
			
		}
		for (int l115 = 0; (l115 < 3); l115 = (l115 + 1)) {
			fRec48[l115] = 0.0f;
			
		}
		for (int l116 = 0; (l116 < 2); l116 = (l116 + 1)) {
			iRec67[l116] = 0;
			
		}
		for (int l117 = 0; (l117 < 2); l117 = (l117 + 1)) {
			fRec66[l117] = 0.0f;
			
		}
		for (int l118 = 0; (l118 < 2); l118 = (l118 + 1)) {
			fVec50[l118] = 0.0f;
			
		}
		for (int l119 = 0; (l119 < 2); l119 = (l119 + 1)) {
			fRec70[l119] = 0.0f;
			
		}
		for (int l120 = 0; (l120 < 2); l120 = (l120 + 1)) {
			fVec51[l120] = 0.0f;
			
		}
		for (int l121 = 0; (l121 < 4096); l121 = (l121 + 1)) {
			fVec52[l121] = 0.0f;
			
		}
		for (int l122 = 0; (l122 < 2); l122 = (l122 + 1)) {
			fRec71[l122] = 0.0f;
			
		}
		for (int l123 = 0; (l123 < 2); l123 = (l123 + 1)) {
			iRec73[l123] = 0;
			
		}
		for (int l124 = 0; (l124 < 2); l124 = (l124 + 1)) {
			fRec72[l124] = 0.0f;
			
		}
		for (int l125 = 0; (l125 < 2); l125 = (l125 + 1)) {
			fVec53[l125] = 0.0f;
			
		}
		for (int l126 = 0; (l126 < 2); l126 = (l126 + 1)) {
			fVec54[l126] = 0.0f;
			
		}
		for (int l127 = 0; (l127 < 2); l127 = (l127 + 1)) {
			fRec74[l127] = 0.0f;
			
		}
		for (int l128 = 0; (l128 < 2); l128 = (l128 + 1)) {
			fVec55[l128] = 0.0f;
			
		}
		for (int l129 = 0; (l129 < 4096); l129 = (l129 + 1)) {
			fVec56[l129] = 0.0f;
			
		}
		for (int l130 = 0; (l130 < 2); l130 = (l130 + 1)) {
			fRec75[l130] = 0.0f;
			
		}
		for (int l131 = 0; (l131 < 2); l131 = (l131 + 1)) {
			iRec77[l131] = 0;
			
		}
		for (int l132 = 0; (l132 < 2); l132 = (l132 + 1)) {
			fRec76[l132] = 0.0f;
			
		}
		for (int l133 = 0; (l133 < 2); l133 = (l133 + 1)) {
			fVec57[l133] = 0.0f;
			
		}
		for (int l134 = 0; (l134 < 2); l134 = (l134 + 1)) {
			fVec58[l134] = 0.0f;
			
		}
		for (int l135 = 0; (l135 < 2); l135 = (l135 + 1)) {
			fRec78[l135] = 0.0f;
			
		}
		for (int l136 = 0; (l136 < 2); l136 = (l136 + 1)) {
			fVec59[l136] = 0.0f;
			
		}
		for (int l137 = 0; (l137 < 4096); l137 = (l137 + 1)) {
			fVec60[l137] = 0.0f;
			
		}
		for (int l138 = 0; (l138 < 2); l138 = (l138 + 1)) {
			fRec79[l138] = 0.0f;
			
		}
		for (int l139 = 0; (l139 < 2); l139 = (l139 + 1)) {
			iRec81[l139] = 0;
			
		}
		for (int l140 = 0; (l140 < 2); l140 = (l140 + 1)) {
			fRec80[l140] = 0.0f;
			
		}
		for (int l141 = 0; (l141 < 2); l141 = (l141 + 1)) {
			fVec61[l141] = 0.0f;
			
		}
		for (int l142 = 0; (l142 < 2); l142 = (l142 + 1)) {
			fVec62[l142] = 0.0f;
			
		}
		for (int l143 = 0; (l143 < 2); l143 = (l143 + 1)) {
			fRec82[l143] = 0.0f;
			
		}
		for (int l144 = 0; (l144 < 2); l144 = (l144 + 1)) {
			fVec63[l144] = 0.0f;
			
		}
		for (int l145 = 0; (l145 < 4096); l145 = (l145 + 1)) {
			fVec64[l145] = 0.0f;
			
		}
		for (int l146 = 0; (l146 < 2); l146 = (l146 + 1)) {
			fRec83[l146] = 0.0f;
			
		}
		for (int l147 = 0; (l147 < 2); l147 = (l147 + 1)) {
			iRec85[l147] = 0;
			
		}
		for (int l148 = 0; (l148 < 2); l148 = (l148 + 1)) {
			fRec84[l148] = 0.0f;
			
		}
		for (int l149 = 0; (l149 < 2); l149 = (l149 + 1)) {
			fVec65[l149] = 0.0f;
			
		}
		for (int l150 = 0; (l150 < 3); l150 = (l150 + 1)) {
			fRec69[l150] = 0.0f;
			
		}
		for (int l151 = 0; (l151 < 3); l151 = (l151 + 1)) {
			fRec68[l151] = 0.0f;
			
		}
		for (int l152 = 0; (l152 < 2); l152 = (l152 + 1)) {
			iRec87[l152] = 0;
			
		}
		for (int l153 = 0; (l153 < 2); l153 = (l153 + 1)) {
			fRec86[l153] = 0.0f;
			
		}
		for (int l154 = 0; (l154 < 2); l154 = (l154 + 1)) {
			fVec66[l154] = 0.0f;
			
		}
		for (int l155 = 0; (l155 < 2); l155 = (l155 + 1)) {
			fRec90[l155] = 0.0f;
			
		}
		for (int l156 = 0; (l156 < 2); l156 = (l156 + 1)) {
			fVec67[l156] = 0.0f;
			
		}
		for (int l157 = 0; (l157 < 4096); l157 = (l157 + 1)) {
			fVec68[l157] = 0.0f;
			
		}
		for (int l158 = 0; (l158 < 2); l158 = (l158 + 1)) {
			fRec91[l158] = 0.0f;
			
		}
		for (int l159 = 0; (l159 < 2); l159 = (l159 + 1)) {
			iRec93[l159] = 0;
			
		}
		for (int l160 = 0; (l160 < 2); l160 = (l160 + 1)) {
			fRec92[l160] = 0.0f;
			
		}
		for (int l161 = 0; (l161 < 2); l161 = (l161 + 1)) {
			fVec69[l161] = 0.0f;
			
		}
		for (int l162 = 0; (l162 < 2); l162 = (l162 + 1)) {
			fVec70[l162] = 0.0f;
			
		}
		for (int l163 = 0; (l163 < 2); l163 = (l163 + 1)) {
			fRec94[l163] = 0.0f;
			
		}
		for (int l164 = 0; (l164 < 2); l164 = (l164 + 1)) {
			fVec71[l164] = 0.0f;
			
		}
		for (int l165 = 0; (l165 < 4096); l165 = (l165 + 1)) {
			fVec72[l165] = 0.0f;
			
		}
		for (int l166 = 0; (l166 < 2); l166 = (l166 + 1)) {
			fRec95[l166] = 0.0f;
			
		}
		for (int l167 = 0; (l167 < 2); l167 = (l167 + 1)) {
			iRec97[l167] = 0;
			
		}
		for (int l168 = 0; (l168 < 2); l168 = (l168 + 1)) {
			fRec96[l168] = 0.0f;
			
		}
		for (int l169 = 0; (l169 < 2); l169 = (l169 + 1)) {
			fVec73[l169] = 0.0f;
			
		}
		for (int l170 = 0; (l170 < 2); l170 = (l170 + 1)) {
			fVec74[l170] = 0.0f;
			
		}
		for (int l171 = 0; (l171 < 2); l171 = (l171 + 1)) {
			fRec98[l171] = 0.0f;
			
		}
		for (int l172 = 0; (l172 < 2); l172 = (l172 + 1)) {
			fVec75[l172] = 0.0f;
			
		}
		for (int l173 = 0; (l173 < 4096); l173 = (l173 + 1)) {
			fVec76[l173] = 0.0f;
			
		}
		for (int l174 = 0; (l174 < 2); l174 = (l174 + 1)) {
			fRec99[l174] = 0.0f;
			
		}
		for (int l175 = 0; (l175 < 2); l175 = (l175 + 1)) {
			iRec101[l175] = 0;
			
		}
		for (int l176 = 0; (l176 < 2); l176 = (l176 + 1)) {
			fRec100[l176] = 0.0f;
			
		}
		for (int l177 = 0; (l177 < 2); l177 = (l177 + 1)) {
			fVec77[l177] = 0.0f;
			
		}
		for (int l178 = 0; (l178 < 2); l178 = (l178 + 1)) {
			fVec78[l178] = 0.0f;
			
		}
		for (int l179 = 0; (l179 < 2); l179 = (l179 + 1)) {
			fRec102[l179] = 0.0f;
			
		}
		for (int l180 = 0; (l180 < 2); l180 = (l180 + 1)) {
			fVec79[l180] = 0.0f;
			
		}
		for (int l181 = 0; (l181 < 4096); l181 = (l181 + 1)) {
			fVec80[l181] = 0.0f;
			
		}
		for (int l182 = 0; (l182 < 2); l182 = (l182 + 1)) {
			fRec103[l182] = 0.0f;
			
		}
		for (int l183 = 0; (l183 < 2); l183 = (l183 + 1)) {
			iRec105[l183] = 0;
			
		}
		for (int l184 = 0; (l184 < 2); l184 = (l184 + 1)) {
			fRec104[l184] = 0.0f;
			
		}
		for (int l185 = 0; (l185 < 2); l185 = (l185 + 1)) {
			fVec81[l185] = 0.0f;
			
		}
		for (int l186 = 0; (l186 < 3); l186 = (l186 + 1)) {
			fRec89[l186] = 0.0f;
			
		}
		for (int l187 = 0; (l187 < 3); l187 = (l187 + 1)) {
			fRec88[l187] = 0.0f;
			
		}
		for (int l188 = 0; (l188 < 2); l188 = (l188 + 1)) {
			iRec107[l188] = 0;
			
		}
		for (int l189 = 0; (l189 < 2); l189 = (l189 + 1)) {
			fRec106[l189] = 0.0f;
			
		}
		for (int l190 = 0; (l190 < 2); l190 = (l190 + 1)) {
			fVec82[l190] = 0.0f;
			
		}
		for (int l191 = 0; (l191 < 2); l191 = (l191 + 1)) {
			fRec110[l191] = 0.0f;
			
		}
		for (int l192 = 0; (l192 < 2); l192 = (l192 + 1)) {
			fVec83[l192] = 0.0f;
			
		}
		for (int l193 = 0; (l193 < 4096); l193 = (l193 + 1)) {
			fVec84[l193] = 0.0f;
			
		}
		for (int l194 = 0; (l194 < 2); l194 = (l194 + 1)) {
			fRec111[l194] = 0.0f;
			
		}
		for (int l195 = 0; (l195 < 2); l195 = (l195 + 1)) {
			iRec113[l195] = 0;
			
		}
		for (int l196 = 0; (l196 < 2); l196 = (l196 + 1)) {
			fRec112[l196] = 0.0f;
			
		}
		for (int l197 = 0; (l197 < 2); l197 = (l197 + 1)) {
			fVec85[l197] = 0.0f;
			
		}
		for (int l198 = 0; (l198 < 2); l198 = (l198 + 1)) {
			fVec86[l198] = 0.0f;
			
		}
		for (int l199 = 0; (l199 < 2); l199 = (l199 + 1)) {
			fRec114[l199] = 0.0f;
			
		}
		for (int l200 = 0; (l200 < 2); l200 = (l200 + 1)) {
			fVec87[l200] = 0.0f;
			
		}
		for (int l201 = 0; (l201 < 4096); l201 = (l201 + 1)) {
			fVec88[l201] = 0.0f;
			
		}
		for (int l202 = 0; (l202 < 2); l202 = (l202 + 1)) {
			fRec115[l202] = 0.0f;
			
		}
		for (int l203 = 0; (l203 < 2); l203 = (l203 + 1)) {
			iRec117[l203] = 0;
			
		}
		for (int l204 = 0; (l204 < 2); l204 = (l204 + 1)) {
			fRec116[l204] = 0.0f;
			
		}
		for (int l205 = 0; (l205 < 2); l205 = (l205 + 1)) {
			fVec89[l205] = 0.0f;
			
		}
		for (int l206 = 0; (l206 < 2); l206 = (l206 + 1)) {
			fVec90[l206] = 0.0f;
			
		}
		for (int l207 = 0; (l207 < 2); l207 = (l207 + 1)) {
			fRec118[l207] = 0.0f;
			
		}
		for (int l208 = 0; (l208 < 2); l208 = (l208 + 1)) {
			fVec91[l208] = 0.0f;
			
		}
		for (int l209 = 0; (l209 < 4096); l209 = (l209 + 1)) {
			fVec92[l209] = 0.0f;
			
		}
		for (int l210 = 0; (l210 < 2); l210 = (l210 + 1)) {
			fRec119[l210] = 0.0f;
			
		}
		for (int l211 = 0; (l211 < 2); l211 = (l211 + 1)) {
			iRec121[l211] = 0;
			
		}
		for (int l212 = 0; (l212 < 2); l212 = (l212 + 1)) {
			fRec120[l212] = 0.0f;
			
		}
		for (int l213 = 0; (l213 < 2); l213 = (l213 + 1)) {
			fVec93[l213] = 0.0f;
			
		}
		for (int l214 = 0; (l214 < 2); l214 = (l214 + 1)) {
			fVec94[l214] = 0.0f;
			
		}
		for (int l215 = 0; (l215 < 2); l215 = (l215 + 1)) {
			fRec122[l215] = 0.0f;
			
		}
		for (int l216 = 0; (l216 < 2); l216 = (l216 + 1)) {
			fVec95[l216] = 0.0f;
			
		}
		for (int l217 = 0; (l217 < 4096); l217 = (l217 + 1)) {
			fVec96[l217] = 0.0f;
			
		}
		for (int l218 = 0; (l218 < 2); l218 = (l218 + 1)) {
			fRec123[l218] = 0.0f;
			
		}
		for (int l219 = 0; (l219 < 2); l219 = (l219 + 1)) {
			iRec125[l219] = 0;
			
		}
		for (int l220 = 0; (l220 < 2); l220 = (l220 + 1)) {
			fRec124[l220] = 0.0f;
			
		}
		for (int l221 = 0; (l221 < 2); l221 = (l221 + 1)) {
			fVec97[l221] = 0.0f;
			
		}
		for (int l222 = 0; (l222 < 3); l222 = (l222 + 1)) {
			fRec109[l222] = 0.0f;
			
		}
		for (int l223 = 0; (l223 < 3); l223 = (l223 + 1)) {
			fRec108[l223] = 0.0f;
			
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
		ui_interface->addHorizontalSlider("Aux", &fHslider7, 0.0f, 0.0f, 3.0f, 0.00100000005f);
		ui_interface->addHorizontalBargraph("Bars", &fHbargraph1, 0.0f, 5.0f);
		ui_interface->addHorizontalBargraph("Dots", &fHbargraph0, 0.0f, 6.0f);
		ui_interface->addHorizontalSlider("Filter", &fHslider9, 20.0f, 0.0f, 99.0f, 1.0f);
		ui_interface->addHorizontalSlider("Relation", &fHslider8, 2.0f, 0.0f, 3.00099993f, 0.00100000005f);
		ui_interface->addHorizontalSlider("Wave", &fHslider5, 0.0f, 0.0f, 4.0f, 0.00999999978f);
		ui_interface->openVerticalBox("envelope");
		ui_interface->addHorizontalSlider("Attack", &fHslider2, 0.00100000005f, 0.00100000005f, 4.0f, 0.00100000005f);
		ui_interface->addHorizontalSlider("Decay", &fHslider3, 0.0f, 0.0f, 4.0f, 0.00999999978f);
		ui_interface->addHorizontalSlider("Release", &fHslider1, 0.0f, 0.0f, 4.0f, 0.00999999978f);
		ui_interface->addHorizontalSlider("Sustain", &fHslider4, 1.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface->closeBox();
		ui_interface->openHorizontalBox("voices");
		ui_interface->openVerticalBox("0");
		ui_interface->openHorizontalBox("midi");
		ui_interface->addHorizontalSlider("freq", &fHslider6, 440.0f, 20.0f, 1000.0f, 1.0f);
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
		float fSlow3 = float(fHslider2);
		int iSlow4 = int((fConst0 * fSlow3));
		float fSlow5 = float(fHslider3);
		float fSlow6 = float(fHslider4);
		float fSlow7 = (fSlow6 * float(iSlow1));
		float fSlow8 = (0.00100000005f * float(fHslider5));
		float fSlow9 = float(fHslider6);
		float fSlow10 = max((0.5f * fSlow9), 23.4489498f);
		float fSlow11 = max(20.0f, fabsf(fSlow10));
		float fSlow12 = (fConst2 / fSlow11);
		float fSlow13 = (fConst0 / fSlow10);
		float fSlow14 = (fConst4 * fSlow9);
		float fSlow15 = max(0.0f, min(2047.0f, (fConst5 / fSlow10)));
		float fSlow16 = floorf(fSlow15);
		float fSlow17 = (fSlow16 + (1.0f - fSlow15));
		int iSlow18 = int(fSlow15);
		float fSlow19 = (fSlow15 - fSlow16);
		int iSlow20 = (iSlow18 + 1);
		float fSlow21 = (fConst0 / fSlow9);
		int iSlow22 = int((fConst6 / fSlow9));
		float fSlow23 = (fConst7 * fSlow9);
		float fSlow24 = (0.00100000005f * float(fHslider7));
		fHbargraph0 = FAUSTFLOAT((2.0f * float(fHslider8)));
		float fSlow25 = (0.000500000024f * fHbargraph0);
		float fSlow26 = (fConst8 * fSlow9);
		float fSlow27 = max(fSlow9, 23.4489498f);
		float fSlow28 = max(20.0f, fabsf(fSlow27));
		float fSlow29 = (fConst2 / fSlow28);
		float fSlow30 = (fConst0 / fSlow27);
		float fSlow31 = max(0.0f, min(2047.0f, (fConst5 / fSlow27)));
		float fSlow32 = floorf(fSlow31);
		float fSlow33 = (fSlow32 + (1.0f - fSlow31));
		int iSlow34 = int(fSlow31);
		float fSlow35 = (fSlow31 - fSlow32);
		int iSlow36 = (iSlow34 + 1);
		int iSlow37 = int(fSlow21);
		float fSlow38 = (0.00100000005f * float(fHslider9));
		float fSlow39 = float(fHslider10);
		int iSlow40 = (float(fButton1) > 0.0f);
		float fSlow41 = (fSlow6 * float(iSlow40));
		float fSlow42 = float(fHslider11);
		float fSlow43 = max((0.5f * fSlow42), 23.4489498f);
		float fSlow44 = max(20.0f, fabsf(fSlow43));
		float fSlow45 = (fConst2 / fSlow44);
		float fSlow46 = (fConst0 / fSlow43);
		float fSlow47 = (fConst4 * fSlow42);
		float fSlow48 = max(0.0f, min(2047.0f, (fConst5 / fSlow43)));
		float fSlow49 = floorf(fSlow48);
		float fSlow50 = (fSlow49 + (1.0f - fSlow48));
		int iSlow51 = int(fSlow48);
		float fSlow52 = (fSlow48 - fSlow49);
		int iSlow53 = (iSlow51 + 1);
		float fSlow54 = (fConst0 / fSlow42);
		int iSlow55 = int((fConst6 / fSlow42));
		float fSlow56 = (fConst7 * fSlow42);
		float fSlow57 = max(fSlow42, 23.4489498f);
		float fSlow58 = max(20.0f, fabsf(fSlow57));
		float fSlow59 = (fConst2 / fSlow58);
		float fSlow60 = (fConst0 / fSlow57);
		float fSlow61 = (fConst8 * fSlow42);
		float fSlow62 = max(0.0f, min(2047.0f, (fConst5 / fSlow57)));
		float fSlow63 = floorf(fSlow62);
		float fSlow64 = (fSlow63 + (1.0f - fSlow62));
		int iSlow65 = int(fSlow62);
		float fSlow66 = (fSlow62 - fSlow63);
		int iSlow67 = (iSlow65 + 1);
		int iSlow68 = int(fSlow54);
		float fSlow69 = float(fHslider12);
		int iSlow70 = (float(fButton2) > 0.0f);
		float fSlow71 = (fSlow6 * float(iSlow70));
		float fSlow72 = float(fHslider13);
		float fSlow73 = max((0.5f * fSlow72), 23.4489498f);
		float fSlow74 = max(20.0f, fabsf(fSlow73));
		float fSlow75 = (fConst2 / fSlow74);
		float fSlow76 = (fConst0 / fSlow73);
		float fSlow77 = (fConst4 * fSlow72);
		float fSlow78 = max(0.0f, min(2047.0f, (fConst5 / fSlow73)));
		float fSlow79 = floorf(fSlow78);
		float fSlow80 = (fSlow79 + (1.0f - fSlow78));
		int iSlow81 = int(fSlow78);
		float fSlow82 = (fSlow78 - fSlow79);
		int iSlow83 = (iSlow81 + 1);
		float fSlow84 = (fConst0 / fSlow72);
		int iSlow85 = int((fConst6 / fSlow72));
		float fSlow86 = (fConst7 * fSlow72);
		float fSlow87 = max(fSlow72, 23.4489498f);
		float fSlow88 = max(20.0f, fabsf(fSlow87));
		float fSlow89 = (fConst2 / fSlow88);
		float fSlow90 = (fConst0 / fSlow87);
		float fSlow91 = (fConst8 * fSlow72);
		float fSlow92 = max(0.0f, min(2047.0f, (fConst5 / fSlow87)));
		float fSlow93 = floorf(fSlow92);
		float fSlow94 = (fSlow93 + (1.0f - fSlow92));
		int iSlow95 = int(fSlow92);
		float fSlow96 = (fSlow92 - fSlow93);
		int iSlow97 = (iSlow95 + 1);
		int iSlow98 = int(fSlow84);
		float fSlow99 = float(fHslider14);
		int iSlow100 = (float(fButton3) > 0.0f);
		float fSlow101 = (fSlow6 * float(iSlow100));
		float fSlow102 = float(fHslider15);
		float fSlow103 = max((0.5f * fSlow102), 23.4489498f);
		float fSlow104 = max(20.0f, fabsf(fSlow103));
		float fSlow105 = (fConst2 / fSlow104);
		float fSlow106 = (fConst0 / fSlow103);
		float fSlow107 = (fConst4 * fSlow102);
		float fSlow108 = max(0.0f, min(2047.0f, (fConst5 / fSlow103)));
		float fSlow109 = floorf(fSlow108);
		float fSlow110 = (fSlow109 + (1.0f - fSlow108));
		int iSlow111 = int(fSlow108);
		float fSlow112 = (fSlow108 - fSlow109);
		int iSlow113 = (iSlow111 + 1);
		float fSlow114 = (fConst0 / fSlow102);
		int iSlow115 = int((fConst6 / fSlow102));
		float fSlow116 = (fConst7 * fSlow102);
		float fSlow117 = max(fSlow102, 23.4489498f);
		float fSlow118 = max(20.0f, fabsf(fSlow117));
		float fSlow119 = (fConst2 / fSlow118);
		float fSlow120 = (fConst0 / fSlow117);
		float fSlow121 = (fConst8 * fSlow102);
		float fSlow122 = max(0.0f, min(2047.0f, (fConst5 / fSlow117)));
		float fSlow123 = floorf(fSlow122);
		float fSlow124 = (fSlow123 + (1.0f - fSlow122));
		int iSlow125 = int(fSlow122);
		float fSlow126 = (fSlow122 - fSlow123);
		int iSlow127 = (iSlow125 + 1);
		int iSlow128 = int(fSlow114);
		float fSlow129 = float(fHslider16);
		int iSlow130 = (float(fButton4) > 0.0f);
		float fSlow131 = (fSlow6 * float(iSlow130));
		float fSlow132 = float(fHslider17);
		float fSlow133 = max((0.5f * fSlow132), 23.4489498f);
		float fSlow134 = max(20.0f, fabsf(fSlow133));
		float fSlow135 = (fConst2 / fSlow134);
		float fSlow136 = (fConst0 / fSlow133);
		float fSlow137 = (fConst4 * fSlow132);
		float fSlow138 = max(0.0f, min(2047.0f, (fConst5 / fSlow133)));
		float fSlow139 = floorf(fSlow138);
		float fSlow140 = (fSlow139 + (1.0f - fSlow138));
		int iSlow141 = int(fSlow138);
		float fSlow142 = (fSlow138 - fSlow139);
		int iSlow143 = (iSlow141 + 1);
		float fSlow144 = (fConst0 / fSlow132);
		int iSlow145 = int((fConst6 / fSlow132));
		float fSlow146 = (fConst7 * fSlow132);
		float fSlow147 = max(fSlow132, 23.4489498f);
		float fSlow148 = max(20.0f, fabsf(fSlow147));
		float fSlow149 = (fConst2 / fSlow148);
		float fSlow150 = (fConst0 / fSlow147);
		float fSlow151 = (fConst8 * fSlow132);
		float fSlow152 = max(0.0f, min(2047.0f, (fConst5 / fSlow147)));
		float fSlow153 = floorf(fSlow152);
		float fSlow154 = (fSlow153 + (1.0f - fSlow152));
		int iSlow155 = int(fSlow152);
		float fSlow156 = (fSlow152 - fSlow153);
		int iSlow157 = (iSlow155 + 1);
		int iSlow158 = int(fSlow144);
		float fSlow159 = float(fHslider18);
		int iSlow160 = (float(fButton5) > 0.0f);
		float fSlow161 = (fSlow6 * float(iSlow160));
		float fSlow162 = float(fHslider19);
		float fSlow163 = max((0.5f * fSlow162), 23.4489498f);
		float fSlow164 = max(20.0f, fabsf(fSlow163));
		float fSlow165 = (fConst2 / fSlow164);
		float fSlow166 = (fConst0 / fSlow163);
		float fSlow167 = (fConst4 * fSlow162);
		float fSlow168 = max(0.0f, min(2047.0f, (fConst5 / fSlow163)));
		float fSlow169 = floorf(fSlow168);
		float fSlow170 = (fSlow169 + (1.0f - fSlow168));
		int iSlow171 = int(fSlow168);
		float fSlow172 = (fSlow168 - fSlow169);
		int iSlow173 = (iSlow171 + 1);
		float fSlow174 = (fConst0 / fSlow162);
		int iSlow175 = int((fConst6 / fSlow162));
		float fSlow176 = (fConst7 * fSlow162);
		float fSlow177 = max(fSlow162, 23.4489498f);
		float fSlow178 = max(20.0f, fabsf(fSlow177));
		float fSlow179 = (fConst2 / fSlow178);
		float fSlow180 = (fConst0 / fSlow177);
		float fSlow181 = (fConst8 * fSlow162);
		float fSlow182 = max(0.0f, min(2047.0f, (fConst5 / fSlow177)));
		float fSlow183 = floorf(fSlow182);
		float fSlow184 = (fSlow183 + (1.0f - fSlow182));
		int iSlow185 = int(fSlow182);
		float fSlow186 = (fSlow182 - fSlow183);
		int iSlow187 = (iSlow185 + 1);
		int iSlow188 = int(fSlow174);
		for (int i = 0; (i < count); i = (i + 1)) {
			iVec0[0] = 1;
			iRec1[0] = (iSlow1 * (iRec1[1] + 1));
			int iTemp0 = (iRec1[0] < iSlow4);
			float fTemp1 = expf((0.0f - (fConst1 / (iSlow1?(iTemp0?fSlow3:fSlow5):fSlow2))));
			fRec0[0] = ((fRec0[1] * fTemp1) + ((iSlow1?(iTemp0?float(iSlow1):fSlow7):0.0f) * (1.0f - fTemp1)));
			fRec4[0] = (fSlow8 + (0.999000013f * fRec4[1]));
			float fTemp2 = min(1.0f, max(0.0f, (2.0f - fRec4[0])));
			fVec1[0] = 0.25f;
			fVec2[0] = fSlow11;
			float fTemp3 = (fRec5[1] + (fConst3 * fVec2[1]));
			fRec5[0] = (fTemp3 - floorf(fTemp3));
			float fTemp4 = faust_nuke_faustpower2_f(((2.0f * fRec5[0]) + -1.0f));
			fVec3[0] = fTemp4;
			float fTemp5 = (fSlow12 * ((fTemp4 - fVec3[1]) * float(iVec0[1])));
			fVec4[(IOTA & 4095)] = fTemp5;
			float fTemp6 = min(0.5f, (0.5f * fRec4[0]));
			float fTemp7 = max(0.0f, min(2047.0f, (fSlow13 * fTemp6)));
			int iTemp8 = int(fTemp7);
			float fTemp9 = floorf(fTemp7);
			fRec6[0] = ((fTemp5 + (0.999000013f * fRec6[1])) - ((fSlow17 * fVec4[((IOTA - iSlow18) & 4095)]) + (fSlow19 * fVec4[((IOTA - iSlow20) & 4095)])));
			float fTemp10 = min(1.0f, max(0.0f, (fRec4[0] + -2.0f)));
			float fTemp11 = (1.0f - (fTemp2 + fTemp10));
			float fTemp12 = (fTemp10 * fVec1[1]);
			iRec8[0] = ((iRec8[1] + iVec0[1]) % iSlow22);
			float fTemp13 = (0.100000001f * (max(3.0f, fRec4[0]) + -3.0f));
			float fTemp14 = (fTemp13 + 0.5f);
			float fTemp15 = ((fRec7[1] * float((1 - ((iRec8[0] == 0) > 0)))) + (fSlow23 * fTemp14));
			fRec7[0] = (fTemp15 - floorf(fTemp15));
			float fTemp16 = faust_nuke_faustpower2_f(((2.0f * fRec7[0]) + -1.0f));
			fVec5[0] = fTemp16;
			fRec9[0] = (fSlow24 + (0.999000013f * fRec9[1]));
			float fTemp17 = max(0.0f, (fRec9[0] + -2.0f));
			int iTemp18 = (1 - (fRec9[0] <= 0.00999999978f));
			fRec10[0] = (fSlow25 + (0.999000013f * fRec10[1]));
			int iTemp19 = (fRec10[0] >= 2.0f);
			int iTemp20 = (fRec10[0] >= 3.0f);
			float fTemp21 = (((fRec10[0] == 0.0f) + iTemp20)?1.0f:max(max(1.0f, ((0.0593999997f * (fRec10[0] + -2.0999999f)) + 1.0f)), ((0.0593999997f * (1.0f - fRec10[0])) + 1.0f)));
			float fTemp22 = max((fSlow9 * fTemp21), 23.4489498f);
			float fTemp23 = max(20.0f, fabsf(fTemp22));
			fVec6[0] = fTemp23;
			float fTemp24 = (fRec11[1] + (fConst3 * fVec6[1]));
			fRec11[0] = (fTemp24 - floorf(fTemp24));
			float fTemp25 = faust_nuke_faustpower2_f(((2.0f * fRec11[0]) + -1.0f));
			fVec7[0] = fTemp25;
			float fTemp26 = (((fTemp25 - fVec7[1]) * float(iVec0[1])) / fTemp23);
			fVec8[(IOTA & 4095)] = fTemp26;
			float fTemp27 = max(0.0f, min(2047.0f, (fConst0 * (fTemp6 / fTemp22))));
			int iTemp28 = int(fTemp27);
			float fTemp29 = floorf(fTemp27);
			float fTemp30 = max(0.0f, min(2047.0f, (fConst5 / fTemp22)));
			int iTemp31 = int(fTemp30);
			float fTemp32 = floorf(fTemp30);
			fRec12[0] = ((0.999000013f * fRec12[1]) + (fConst2 * ((fTemp26 - (fVec8[((IOTA - iTemp31) & 4095)] * (fTemp32 + (1.0f - fTemp30)))) - ((fTemp30 - fTemp32) * fVec8[((IOTA - (iTemp31 + 1)) & 4095)]))));
			iRec14[0] = ((iRec14[1] + iVec0[1]) % int((fSlow21 / fTemp21)));
			float fTemp33 = (fTemp21 + fTemp13);
			float fTemp34 = ((fRec13[1] * float((1 - ((iRec14[0] == 0) > 0)))) + (fSlow23 * fTemp33));
			fRec13[0] = (fTemp34 - floorf(fTemp34));
			float fTemp35 = faust_nuke_faustpower2_f(((2.0f * fRec13[0]) + -1.0f));
			fVec9[0] = fTemp35;
			float fTemp36 = (((fConst2 * (fTemp2 * ((fTemp26 - (fVec8[((IOTA - iTemp28) & 4095)] * (fTemp29 + (1.0f - fTemp27)))) - ((fTemp27 - fTemp29) * fVec8[((IOTA - (iTemp28 + 1)) & 4095)])))) + (fSlow26 * ((fRec12[0] * fTemp21) * fTemp11))) + (fSlow21 * (((fTemp10 * (fTemp35 - fVec9[1])) * fVec1[1]) / fTemp33)));
			float fTemp37 = (iTemp20?1.49829996f:1.0f);
			float fTemp38 = (fTemp37 / fTemp21);
			float fTemp39 = max((fSlow9 * fTemp38), 23.4489498f);
			float fTemp40 = max(20.0f, fabsf(fTemp39));
			fVec10[0] = fTemp40;
			float fTemp41 = (fRec15[1] + (fConst3 * fVec10[1]));
			fRec15[0] = (fTemp41 - floorf(fTemp41));
			float fTemp42 = faust_nuke_faustpower2_f(((2.0f * fRec15[0]) + -1.0f));
			fVec11[0] = fTemp42;
			float fTemp43 = (((fTemp42 - fVec11[1]) * float(iVec0[1])) / fTemp40);
			fVec12[(IOTA & 4095)] = fTemp43;
			float fTemp44 = max(0.0f, min(2047.0f, (fConst0 * (fTemp6 / fTemp39))));
			int iTemp45 = int(fTemp44);
			float fTemp46 = floorf(fTemp44);
			float fTemp47 = max(0.0f, min(2047.0f, (fConst5 / fTemp39)));
			int iTemp48 = int(fTemp47);
			float fTemp49 = floorf(fTemp47);
			fRec16[0] = ((0.999000013f * fRec16[1]) + (fConst2 * ((fTemp43 - (fVec12[((IOTA - iTemp48) & 4095)] * (fTemp49 + (1.0f - fTemp47)))) - ((fTemp47 - fTemp49) * fVec12[((IOTA - (iTemp48 + 1)) & 4095)]))));
			float fTemp50 = (fTemp21 / fTemp37);
			iRec18[0] = ((iRec18[1] + iVec0[1]) % int((fSlow21 * fTemp50)));
			float fTemp51 = (fTemp13 + fTemp38);
			float fTemp52 = ((fRec17[1] * float((1 - ((iRec18[0] == 0) > 0)))) + (fSlow23 * fTemp51));
			fRec17[0] = (fTemp52 - floorf(fTemp52));
			float fTemp53 = faust_nuke_faustpower2_f(((2.0f * fRec17[0]) + -1.0f));
			fVec13[0] = fTemp53;
			float fTemp54 = (((fConst2 * (fTemp2 * ((fTemp43 - (fVec12[((IOTA - iTemp45) & 4095)] * (fTemp46 + (1.0f - fTemp44)))) - ((fTemp44 - fTemp46) * fVec12[((IOTA - (iTemp45 + 1)) & 4095)])))) + (fSlow26 * (((fTemp37 * fRec16[0]) * fTemp11) / fTemp21))) + (fSlow21 * ((fTemp12 * (fTemp53 - fVec13[1])) / fTemp51)));
			int iTemp55 = (fRec10[0] < 2.0f);
			float fTemp56 = min(1.0f, max(0.0f, (2.0f - fRec10[0])));
			float fTemp57 = (1.0f - fTemp56);
			float fTemp58 = (float(iTemp18) * fTemp56);
			float fTemp59 = max(0.0f, ((fRec9[0] <= 1.0f)?fRec9[0]:(2.0f - fRec9[0])));
			fVec14[0] = fSlow28;
			float fTemp60 = (fRec19[1] + (fConst3 * fVec14[1]));
			fRec19[0] = (fTemp60 - floorf(fTemp60));
			float fTemp61 = faust_nuke_faustpower2_f(((2.0f * fRec19[0]) + -1.0f));
			fVec15[0] = fTemp61;
			float fTemp62 = (fSlow29 * ((fTemp61 - fVec15[1]) * float(iVec0[1])));
			fVec16[(IOTA & 4095)] = fTemp62;
			float fTemp63 = max(0.0f, min(2047.0f, (fSlow30 * fTemp6)));
			int iTemp64 = int(fTemp63);
			float fTemp65 = floorf(fTemp63);
			fRec20[0] = ((fTemp62 + (0.999000013f * fRec20[1])) - ((fSlow33 * fVec16[((IOTA - iSlow34) & 4095)]) + (fSlow35 * fVec16[((IOTA - iSlow36) & 4095)])));
			iRec22[0] = ((iRec22[1] + iVec0[1]) % iSlow37);
			float fTemp66 = (fTemp13 + 1.0f);
			float fTemp67 = ((fRec21[1] * float((1 - ((iRec22[0] == 0) > 0)))) + (fSlow23 * fTemp66));
			fRec21[0] = (fTemp67 - floorf(fTemp67));
			float fTemp68 = faust_nuke_faustpower2_f(((2.0f * fRec21[0]) + -1.0f));
			fVec17[0] = fTemp68;
			iRec23[0] = ((1103515245 * iRec23[1]) + 12345);
			float fTemp69 = (4.65661287e-10f * (float(iRec23[0]) * max((1.0f - fRec9[0]), 0.0f)));
			fRec24[0] = (fSlow38 + (0.999000013f * fRec24[1]));
			int iTemp70 = int(floorf((0.0404040404f * (fRec24[0] + -1.0f))));
			float fTemp71 = (0.0399999991f * fRec24[0]);
			fHbargraph1 = FAUSTFLOAT((4.5f * ((iTemp70 >= 2)?((iTemp70 >= 3)?(4.0f - fTemp71):(0.0399999991f * (fRec24[0] + -50.0f))):((iTemp70 >= 1)?(2.0f - fTemp71):fTemp71))));
			float fTemp72 = tanf((fConst9 * ((2222.0f * fHbargraph1) + 300.0f)));
			float fTemp73 = (1.0f / fTemp72);
			fRec25[0] = ((0.999000013f * fRec25[1]) + (0.00100000005f * ((0.075000003f * (max(40.0f, min(60.0f, fRec24[0])) + -40.0f)) + 1.0f)));
			float fTemp74 = (1.0f / fRec25[0]);
			float fTemp75 = (((fTemp73 - fTemp74) / fTemp72) + 1.0f);
			float fTemp76 = (1.0f - (1.0f / faust_nuke_faustpower2_f(fTemp72)));
			float fTemp77 = (((fTemp73 + fTemp74) / fTemp72) + 1.0f);
			fRec3[0] = (((((((fTemp2 * (fTemp5 - ((fVec4[((IOTA - iTemp8) & 4095)] * (fTemp9 + (1.0f - fTemp7))) + ((fTemp7 - fTemp9) * fVec4[((IOTA - (iTemp8 + 1)) & 4095)])))) + (fSlow14 * (fRec6[0] * fTemp11))) + (fSlow21 * ((fTemp12 * (fTemp16 - fVec5[1])) / fTemp14))) * fTemp17) + ((float(iTemp18) * ((float(iTemp19) * (fTemp36 + fTemp54)) + ((float(iTemp55) * fTemp36) * (fTemp57 + (fTemp58 * fTemp54))))) + (fTemp59 * (((fTemp2 * (fTemp62 - ((fVec16[((IOTA - iTemp64) & 4095)] * (fTemp65 + (1.0f - fTemp63))) + ((fTemp63 - fTemp65) * fVec16[((IOTA - (iTemp64 + 1)) & 4095)])))) + (fSlow26 * (fRec20[0] * fTemp11))) + (fSlow21 * ((fTemp12 * (fTemp68 - fVec17[1])) / fTemp66)))))) + fTemp69) - (((fRec3[2] * fTemp75) + (2.0f * (fRec3[1] * fTemp76))) / fTemp77));
			fRec2[0] = ((((fRec3[1] + (0.5f * fRec3[0])) + (0.5f * fRec3[2])) - ((fTemp75 * fRec2[2]) + (2.0f * (fTemp76 * fRec2[1])))) / fTemp77);
			iRec27[0] = (iSlow40 * (iRec27[1] + 1));
			int iTemp78 = (iRec27[0] < iSlow4);
			float fTemp79 = expf((0.0f - (fConst1 / (iSlow40?(iTemp78?fSlow3:fSlow5):fSlow2))));
			fRec26[0] = ((fRec26[1] * fTemp79) + ((iSlow40?(iTemp78?float(iSlow40):fSlow41):0.0f) * (1.0f - fTemp79)));
			fVec18[0] = fSlow44;
			float fTemp80 = (fRec30[1] + (fConst3 * fVec18[1]));
			fRec30[0] = (fTemp80 - floorf(fTemp80));
			float fTemp81 = faust_nuke_faustpower2_f(((2.0f * fRec30[0]) + -1.0f));
			fVec19[0] = fTemp81;
			float fTemp82 = (fSlow45 * ((fTemp81 - fVec19[1]) * float(iVec0[1])));
			fVec20[(IOTA & 4095)] = fTemp82;
			float fTemp83 = max(0.0f, min(2047.0f, (fSlow46 * fTemp6)));
			int iTemp84 = int(fTemp83);
			float fTemp85 = floorf(fTemp83);
			fRec31[0] = ((fTemp82 + (0.999000013f * fRec31[1])) - ((fSlow50 * fVec20[((IOTA - iSlow51) & 4095)]) + (fSlow52 * fVec20[((IOTA - iSlow53) & 4095)])));
			iRec33[0] = ((iRec33[1] + iVec0[1]) % iSlow55);
			float fTemp86 = ((fRec32[1] * float((1 - ((iRec33[0] == 0) > 0)))) + (fSlow56 * fTemp14));
			fRec32[0] = (fTemp86 - floorf(fTemp86));
			float fTemp87 = faust_nuke_faustpower2_f(((2.0f * fRec32[0]) + -1.0f));
			fVec21[0] = fTemp87;
			fVec22[0] = fSlow58;
			float fTemp88 = (fRec34[1] + (fConst3 * fVec22[1]));
			fRec34[0] = (fTemp88 - floorf(fTemp88));
			float fTemp89 = faust_nuke_faustpower2_f(((2.0f * fRec34[0]) + -1.0f));
			fVec23[0] = fTemp89;
			float fTemp90 = (fSlow59 * ((fTemp89 - fVec23[1]) * float(iVec0[1])));
			fVec24[(IOTA & 4095)] = fTemp90;
			float fTemp91 = max(0.0f, min(2047.0f, (fSlow60 * fTemp6)));
			int iTemp92 = int(fTemp91);
			float fTemp93 = floorf(fTemp91);
			fRec35[0] = ((fTemp90 + (0.999000013f * fRec35[1])) - ((fSlow64 * fVec24[((IOTA - iSlow65) & 4095)]) + (fSlow66 * fVec24[((IOTA - iSlow67) & 4095)])));
			iRec37[0] = ((iRec37[1] + iVec0[1]) % iSlow68);
			float fTemp94 = ((fRec36[1] * float((1 - ((iRec37[0] == 0) > 0)))) + (fSlow56 * fTemp66));
			fRec36[0] = (fTemp94 - floorf(fTemp94));
			float fTemp95 = faust_nuke_faustpower2_f(((2.0f * fRec36[0]) + -1.0f));
			fVec25[0] = fTemp95;
			float fTemp96 = max((fSlow42 * fTemp21), 23.4489498f);
			float fTemp97 = max(20.0f, fabsf(fTemp96));
			fVec26[0] = fTemp97;
			float fTemp98 = (fRec38[1] + (fConst3 * fVec26[1]));
			fRec38[0] = (fTemp98 - floorf(fTemp98));
			float fTemp99 = faust_nuke_faustpower2_f(((2.0f * fRec38[0]) + -1.0f));
			fVec27[0] = fTemp99;
			float fTemp100 = (((fTemp99 - fVec27[1]) * float(iVec0[1])) / fTemp97);
			fVec28[(IOTA & 4095)] = fTemp100;
			float fTemp101 = max(0.0f, min(2047.0f, (fConst0 * (fTemp6 / fTemp96))));
			int iTemp102 = int(fTemp101);
			float fTemp103 = floorf(fTemp101);
			float fTemp104 = max(0.0f, min(2047.0f, (fConst5 / fTemp96)));
			int iTemp105 = int(fTemp104);
			float fTemp106 = floorf(fTemp104);
			fRec39[0] = ((0.999000013f * fRec39[1]) + (fConst2 * ((fTemp100 - (fVec28[((IOTA - iTemp105) & 4095)] * (fTemp106 + (1.0f - fTemp104)))) - ((fTemp104 - fTemp106) * fVec28[((IOTA - (iTemp105 + 1)) & 4095)]))));
			iRec41[0] = ((iRec41[1] + iVec0[1]) % int((fSlow54 / fTemp21)));
			float fTemp107 = ((fRec40[1] * float((1 - ((iRec41[0] == 0) > 0)))) + (fSlow56 * fTemp33));
			fRec40[0] = (fTemp107 - floorf(fTemp107));
			float fTemp108 = faust_nuke_faustpower2_f(((2.0f * fRec40[0]) + -1.0f));
			fVec29[0] = fTemp108;
			float fTemp109 = (((fConst2 * (fTemp2 * ((fTemp100 - (fVec28[((IOTA - iTemp102) & 4095)] * (fTemp103 + (1.0f - fTemp101)))) - ((fTemp101 - fTemp103) * fVec28[((IOTA - (iTemp102 + 1)) & 4095)])))) + (fSlow61 * ((fRec39[0] * fTemp21) * fTemp11))) + (fSlow54 * ((fTemp12 * (fTemp108 - fVec29[1])) / fTemp33)));
			float fTemp110 = max((fSlow42 * fTemp38), 23.4489498f);
			float fTemp111 = max(20.0f, fabsf(fTemp110));
			fVec30[0] = fTemp111;
			float fTemp112 = (fRec42[1] + (fConst3 * fVec30[1]));
			fRec42[0] = (fTemp112 - floorf(fTemp112));
			float fTemp113 = faust_nuke_faustpower2_f(((2.0f * fRec42[0]) + -1.0f));
			fVec31[0] = fTemp113;
			float fTemp114 = (((fTemp113 - fVec31[1]) * float(iVec0[1])) / fTemp111);
			fVec32[(IOTA & 4095)] = fTemp114;
			float fTemp115 = max(0.0f, min(2047.0f, (fConst0 * (fTemp6 / fTemp110))));
			int iTemp116 = int(fTemp115);
			float fTemp117 = floorf(fTemp115);
			float fTemp118 = max(0.0f, min(2047.0f, (fConst5 / fTemp110)));
			int iTemp119 = int(fTemp118);
			float fTemp120 = floorf(fTemp118);
			fRec43[0] = ((0.999000013f * fRec43[1]) + (fConst2 * ((fTemp114 - (fVec32[((IOTA - iTemp119) & 4095)] * (fTemp120 + (1.0f - fTemp118)))) - ((fTemp118 - fTemp120) * fVec32[((IOTA - (iTemp119 + 1)) & 4095)]))));
			iRec45[0] = ((iRec45[1] + iVec0[1]) % int((fSlow54 * fTemp50)));
			float fTemp121 = ((fRec44[1] * float((1 - ((iRec45[0] == 0) > 0)))) + (fSlow56 * fTemp51));
			fRec44[0] = (fTemp121 - floorf(fTemp121));
			float fTemp122 = faust_nuke_faustpower2_f(((2.0f * fRec44[0]) + -1.0f));
			fVec33[0] = fTemp122;
			float fTemp123 = (((fConst2 * (fTemp2 * ((fTemp114 - (fVec32[((IOTA - iTemp116) & 4095)] * (fTemp117 + (1.0f - fTemp115)))) - ((fTemp115 - fTemp117) * fVec32[((IOTA - (iTemp116 + 1)) & 4095)])))) + (fSlow61 * (((fTemp37 * fRec43[0]) * fTemp11) / fTemp21))) + (fSlow54 * ((fTemp12 * (fTemp122 - fVec33[1])) / fTemp51)));
			fRec29[0] = (((fTemp17 * (((fTemp2 * (fTemp82 - ((fVec20[((IOTA - iTemp84) & 4095)] * (fTemp85 + (1.0f - fTemp83))) + ((fTemp83 - fTemp85) * fVec20[((IOTA - (iTemp84 + 1)) & 4095)])))) + (fSlow47 * (fRec31[0] * fTemp11))) + (fSlow54 * ((fTemp12 * (fTemp87 - fVec21[1])) / fTemp14)))) + ((fTemp59 * (((fTemp2 * (fTemp90 - ((fVec24[((IOTA - iTemp92) & 4095)] * (fTemp93 + (1.0f - fTemp91))) + ((fTemp91 - fTemp93) * fVec24[((IOTA - (iTemp92 + 1)) & 4095)])))) + (fSlow61 * (fRec35[0] * fTemp11))) + (fSlow54 * ((fTemp12 * (fTemp95 - fVec25[1])) / fTemp66)))) + (fTemp69 + (float(iTemp18) * ((float(iTemp19) * (fTemp109 + fTemp123)) + ((float(iTemp55) * fTemp109) * (fTemp57 + (fTemp58 * fTemp123)))))))) - (((fTemp75 * fRec29[2]) + (2.0f * (fTemp76 * fRec29[1]))) / fTemp77));
			fRec28[0] = ((((fRec29[1] + (0.5f * fRec29[0])) + (0.5f * fRec29[2])) - ((fTemp75 * fRec28[2]) + (2.0f * (fTemp76 * fRec28[1])))) / fTemp77);
			iRec47[0] = (iSlow70 * (iRec47[1] + 1));
			int iTemp124 = (iRec47[0] < iSlow4);
			float fTemp125 = expf((0.0f - (fConst1 / (iSlow70?(iTemp124?fSlow3:fSlow5):fSlow2))));
			fRec46[0] = ((fRec46[1] * fTemp125) + ((iSlow70?(iTemp124?float(iSlow70):fSlow71):0.0f) * (1.0f - fTemp125)));
			fVec34[0] = fSlow74;
			float fTemp126 = (fRec50[1] + (fConst3 * fVec34[1]));
			fRec50[0] = (fTemp126 - floorf(fTemp126));
			float fTemp127 = faust_nuke_faustpower2_f(((2.0f * fRec50[0]) + -1.0f));
			fVec35[0] = fTemp127;
			float fTemp128 = (fSlow75 * ((fTemp127 - fVec35[1]) * float(iVec0[1])));
			fVec36[(IOTA & 4095)] = fTemp128;
			float fTemp129 = max(0.0f, min(2047.0f, (fSlow76 * fTemp6)));
			int iTemp130 = int(fTemp129);
			float fTemp131 = floorf(fTemp129);
			fRec51[0] = ((fTemp128 + (0.999000013f * fRec51[1])) - ((fSlow80 * fVec36[((IOTA - iSlow81) & 4095)]) + (fSlow82 * fVec36[((IOTA - iSlow83) & 4095)])));
			iRec53[0] = ((iRec53[1] + iVec0[1]) % iSlow85);
			float fTemp132 = ((fRec52[1] * float((1 - ((iRec53[0] == 0) > 0)))) + (fSlow86 * fTemp14));
			fRec52[0] = (fTemp132 - floorf(fTemp132));
			float fTemp133 = faust_nuke_faustpower2_f(((2.0f * fRec52[0]) + -1.0f));
			fVec37[0] = fTemp133;
			fVec38[0] = fSlow88;
			float fTemp134 = (fRec54[1] + (fConst3 * fVec38[1]));
			fRec54[0] = (fTemp134 - floorf(fTemp134));
			float fTemp135 = faust_nuke_faustpower2_f(((2.0f * fRec54[0]) + -1.0f));
			fVec39[0] = fTemp135;
			float fTemp136 = (fSlow89 * ((fTemp135 - fVec39[1]) * float(iVec0[1])));
			fVec40[(IOTA & 4095)] = fTemp136;
			float fTemp137 = max(0.0f, min(2047.0f, (fSlow90 * fTemp6)));
			int iTemp138 = int(fTemp137);
			float fTemp139 = floorf(fTemp137);
			fRec55[0] = ((fTemp136 + (0.999000013f * fRec55[1])) - ((fSlow94 * fVec40[((IOTA - iSlow95) & 4095)]) + (fSlow96 * fVec40[((IOTA - iSlow97) & 4095)])));
			iRec57[0] = ((iRec57[1] + iVec0[1]) % iSlow98);
			float fTemp140 = ((fRec56[1] * float((1 - ((iRec57[0] == 0) > 0)))) + (fSlow86 * fTemp66));
			fRec56[0] = (fTemp140 - floorf(fTemp140));
			float fTemp141 = faust_nuke_faustpower2_f(((2.0f * fRec56[0]) + -1.0f));
			fVec41[0] = fTemp141;
			float fTemp142 = max((fSlow72 * fTemp21), 23.4489498f);
			float fTemp143 = max(20.0f, fabsf(fTemp142));
			fVec42[0] = fTemp143;
			float fTemp144 = (fRec58[1] + (fConst3 * fVec42[1]));
			fRec58[0] = (fTemp144 - floorf(fTemp144));
			float fTemp145 = faust_nuke_faustpower2_f(((2.0f * fRec58[0]) + -1.0f));
			fVec43[0] = fTemp145;
			float fTemp146 = (((fTemp145 - fVec43[1]) * float(iVec0[1])) / fTemp143);
			fVec44[(IOTA & 4095)] = fTemp146;
			float fTemp147 = max(0.0f, min(2047.0f, (fConst0 * (fTemp6 / fTemp142))));
			int iTemp148 = int(fTemp147);
			float fTemp149 = floorf(fTemp147);
			float fTemp150 = max(0.0f, min(2047.0f, (fConst5 / fTemp142)));
			int iTemp151 = int(fTemp150);
			float fTemp152 = floorf(fTemp150);
			fRec59[0] = ((0.999000013f * fRec59[1]) + (fConst2 * ((fTemp146 - (fVec44[((IOTA - iTemp151) & 4095)] * (fTemp152 + (1.0f - fTemp150)))) - ((fTemp150 - fTemp152) * fVec44[((IOTA - (iTemp151 + 1)) & 4095)]))));
			iRec61[0] = ((iRec61[1] + iVec0[1]) % int((fSlow84 / fTemp21)));
			float fTemp153 = ((fRec60[1] * float((1 - ((iRec61[0] == 0) > 0)))) + (fSlow86 * fTemp33));
			fRec60[0] = (fTemp153 - floorf(fTemp153));
			float fTemp154 = faust_nuke_faustpower2_f(((2.0f * fRec60[0]) + -1.0f));
			fVec45[0] = fTemp154;
			float fTemp155 = (((fConst2 * (fTemp2 * ((fTemp146 - (fVec44[((IOTA - iTemp148) & 4095)] * (fTemp149 + (1.0f - fTemp147)))) - ((fTemp147 - fTemp149) * fVec44[((IOTA - (iTemp148 + 1)) & 4095)])))) + (fSlow91 * ((fRec59[0] * fTemp21) * fTemp11))) + (fSlow84 * ((fTemp12 * (fTemp154 - fVec45[1])) / fTemp33)));
			float fTemp156 = max((fSlow72 * fTemp38), 23.4489498f);
			float fTemp157 = max(20.0f, fabsf(fTemp156));
			fVec46[0] = fTemp157;
			float fTemp158 = (fRec62[1] + (fConst3 * fVec46[1]));
			fRec62[0] = (fTemp158 - floorf(fTemp158));
			float fTemp159 = faust_nuke_faustpower2_f(((2.0f * fRec62[0]) + -1.0f));
			fVec47[0] = fTemp159;
			float fTemp160 = (((fTemp159 - fVec47[1]) * float(iVec0[1])) / fTemp157);
			fVec48[(IOTA & 4095)] = fTemp160;
			float fTemp161 = max(0.0f, min(2047.0f, (fConst0 * (fTemp6 / fTemp156))));
			int iTemp162 = int(fTemp161);
			float fTemp163 = floorf(fTemp161);
			float fTemp164 = max(0.0f, min(2047.0f, (fConst5 / fTemp156)));
			int iTemp165 = int(fTemp164);
			float fTemp166 = floorf(fTemp164);
			fRec63[0] = ((0.999000013f * fRec63[1]) + (fConst2 * ((fTemp160 - (fVec48[((IOTA - iTemp165) & 4095)] * (fTemp166 + (1.0f - fTemp164)))) - ((fTemp164 - fTemp166) * fVec48[((IOTA - (iTemp165 + 1)) & 4095)]))));
			iRec65[0] = ((iRec65[1] + iVec0[1]) % int((fSlow84 * fTemp50)));
			float fTemp167 = ((fRec64[1] * float((1 - ((iRec65[0] == 0) > 0)))) + (fSlow86 * fTemp51));
			fRec64[0] = (fTemp167 - floorf(fTemp167));
			float fTemp168 = faust_nuke_faustpower2_f(((2.0f * fRec64[0]) + -1.0f));
			fVec49[0] = fTemp168;
			float fTemp169 = (((fConst2 * (fTemp2 * ((fTemp160 - (fVec48[((IOTA - iTemp162) & 4095)] * (fTemp163 + (1.0f - fTemp161)))) - ((fTemp161 - fTemp163) * fVec48[((IOTA - (iTemp162 + 1)) & 4095)])))) + (fSlow91 * (((fTemp37 * fRec63[0]) * fTemp11) / fTemp21))) + (fSlow84 * ((fTemp12 * (fTemp168 - fVec49[1])) / fTemp51)));
			fRec49[0] = (((fTemp17 * (((fTemp2 * (fTemp128 - ((fVec36[((IOTA - iTemp130) & 4095)] * (fTemp131 + (1.0f - fTemp129))) + ((fTemp129 - fTemp131) * fVec36[((IOTA - (iTemp130 + 1)) & 4095)])))) + (fSlow77 * (fRec51[0] * fTemp11))) + (fSlow84 * ((fTemp12 * (fTemp133 - fVec37[1])) / fTemp14)))) + ((fTemp59 * (((fTemp2 * (fTemp136 - ((fVec40[((IOTA - iTemp138) & 4095)] * (fTemp139 + (1.0f - fTemp137))) + ((fTemp137 - fTemp139) * fVec40[((IOTA - (iTemp138 + 1)) & 4095)])))) + (fSlow91 * (fRec55[0] * fTemp11))) + (fSlow84 * ((fTemp12 * (fTemp141 - fVec41[1])) / fTemp66)))) + (fTemp69 + (float(iTemp18) * ((float(iTemp19) * (fTemp155 + fTemp169)) + ((float(iTemp55) * fTemp155) * (fTemp57 + (fTemp58 * fTemp169)))))))) - (((fTemp75 * fRec49[2]) + (2.0f * (fTemp76 * fRec49[1]))) / fTemp77));
			fRec48[0] = ((((fRec49[1] + (0.5f * fRec49[0])) + (0.5f * fRec49[2])) - ((fTemp75 * fRec48[2]) + (2.0f * (fTemp76 * fRec48[1])))) / fTemp77);
			iRec67[0] = (iSlow100 * (iRec67[1] + 1));
			int iTemp170 = (iRec67[0] < iSlow4);
			float fTemp171 = expf((0.0f - (fConst1 / (iSlow100?(iTemp170?fSlow3:fSlow5):fSlow2))));
			fRec66[0] = ((fRec66[1] * fTemp171) + ((iSlow100?(iTemp170?float(iSlow100):fSlow101):0.0f) * (1.0f - fTemp171)));
			fVec50[0] = fSlow104;
			float fTemp172 = (fRec70[1] + (fConst3 * fVec50[1]));
			fRec70[0] = (fTemp172 - floorf(fTemp172));
			float fTemp173 = faust_nuke_faustpower2_f(((2.0f * fRec70[0]) + -1.0f));
			fVec51[0] = fTemp173;
			float fTemp174 = (fSlow105 * ((fTemp173 - fVec51[1]) * float(iVec0[1])));
			fVec52[(IOTA & 4095)] = fTemp174;
			float fTemp175 = max(0.0f, min(2047.0f, (fSlow106 * fTemp6)));
			int iTemp176 = int(fTemp175);
			float fTemp177 = floorf(fTemp175);
			fRec71[0] = ((fTemp174 + (0.999000013f * fRec71[1])) - ((fSlow110 * fVec52[((IOTA - iSlow111) & 4095)]) + (fSlow112 * fVec52[((IOTA - iSlow113) & 4095)])));
			iRec73[0] = ((iRec73[1] + iVec0[1]) % iSlow115);
			float fTemp178 = ((fRec72[1] * float((1 - ((iRec73[0] == 0) > 0)))) + (fSlow116 * fTemp14));
			fRec72[0] = (fTemp178 - floorf(fTemp178));
			float fTemp179 = faust_nuke_faustpower2_f(((2.0f * fRec72[0]) + -1.0f));
			fVec53[0] = fTemp179;
			fVec54[0] = fSlow118;
			float fTemp180 = (fRec74[1] + (fConst3 * fVec54[1]));
			fRec74[0] = (fTemp180 - floorf(fTemp180));
			float fTemp181 = faust_nuke_faustpower2_f(((2.0f * fRec74[0]) + -1.0f));
			fVec55[0] = fTemp181;
			float fTemp182 = (fSlow119 * ((fTemp181 - fVec55[1]) * float(iVec0[1])));
			fVec56[(IOTA & 4095)] = fTemp182;
			float fTemp183 = max(0.0f, min(2047.0f, (fSlow120 * fTemp6)));
			int iTemp184 = int(fTemp183);
			float fTemp185 = floorf(fTemp183);
			fRec75[0] = ((fTemp182 + (0.999000013f * fRec75[1])) - ((fSlow124 * fVec56[((IOTA - iSlow125) & 4095)]) + (fSlow126 * fVec56[((IOTA - iSlow127) & 4095)])));
			iRec77[0] = ((iRec77[1] + iVec0[1]) % iSlow128);
			float fTemp186 = ((fRec76[1] * float((1 - ((iRec77[0] == 0) > 0)))) + (fSlow116 * fTemp66));
			fRec76[0] = (fTemp186 - floorf(fTemp186));
			float fTemp187 = faust_nuke_faustpower2_f(((2.0f * fRec76[0]) + -1.0f));
			fVec57[0] = fTemp187;
			float fTemp188 = max((fSlow102 * fTemp21), 23.4489498f);
			float fTemp189 = max(20.0f, fabsf(fTemp188));
			fVec58[0] = fTemp189;
			float fTemp190 = (fRec78[1] + (fConst3 * fVec58[1]));
			fRec78[0] = (fTemp190 - floorf(fTemp190));
			float fTemp191 = faust_nuke_faustpower2_f(((2.0f * fRec78[0]) + -1.0f));
			fVec59[0] = fTemp191;
			float fTemp192 = (((fTemp191 - fVec59[1]) * float(iVec0[1])) / fTemp189);
			fVec60[(IOTA & 4095)] = fTemp192;
			float fTemp193 = max(0.0f, min(2047.0f, (fConst0 * (fTemp6 / fTemp188))));
			int iTemp194 = int(fTemp193);
			float fTemp195 = floorf(fTemp193);
			float fTemp196 = max(0.0f, min(2047.0f, (fConst5 / fTemp188)));
			int iTemp197 = int(fTemp196);
			float fTemp198 = floorf(fTemp196);
			fRec79[0] = ((0.999000013f * fRec79[1]) + (fConst2 * ((fTemp192 - (fVec60[((IOTA - iTemp197) & 4095)] * (fTemp198 + (1.0f - fTemp196)))) - ((fTemp196 - fTemp198) * fVec60[((IOTA - (iTemp197 + 1)) & 4095)]))));
			iRec81[0] = ((iRec81[1] + iVec0[1]) % int((fSlow114 / fTemp21)));
			float fTemp199 = ((fRec80[1] * float((1 - ((iRec81[0] == 0) > 0)))) + (fSlow116 * fTemp33));
			fRec80[0] = (fTemp199 - floorf(fTemp199));
			float fTemp200 = faust_nuke_faustpower2_f(((2.0f * fRec80[0]) + -1.0f));
			fVec61[0] = fTemp200;
			float fTemp201 = (((fConst2 * (fTemp2 * ((fTemp192 - (fVec60[((IOTA - iTemp194) & 4095)] * (fTemp195 + (1.0f - fTemp193)))) - ((fTemp193 - fTemp195) * fVec60[((IOTA - (iTemp194 + 1)) & 4095)])))) + (fSlow121 * ((fRec79[0] * fTemp21) * fTemp11))) + (fSlow114 * ((fTemp12 * (fTemp200 - fVec61[1])) / fTemp33)));
			float fTemp202 = max((fSlow102 * fTemp38), 23.4489498f);
			float fTemp203 = max(20.0f, fabsf(fTemp202));
			fVec62[0] = fTemp203;
			float fTemp204 = (fRec82[1] + (fConst3 * fVec62[1]));
			fRec82[0] = (fTemp204 - floorf(fTemp204));
			float fTemp205 = faust_nuke_faustpower2_f(((2.0f * fRec82[0]) + -1.0f));
			fVec63[0] = fTemp205;
			float fTemp206 = (((fTemp205 - fVec63[1]) * float(iVec0[1])) / fTemp203);
			fVec64[(IOTA & 4095)] = fTemp206;
			float fTemp207 = max(0.0f, min(2047.0f, (fConst0 * (fTemp6 / fTemp202))));
			int iTemp208 = int(fTemp207);
			float fTemp209 = floorf(fTemp207);
			float fTemp210 = max(0.0f, min(2047.0f, (fConst5 / fTemp202)));
			int iTemp211 = int(fTemp210);
			float fTemp212 = floorf(fTemp210);
			fRec83[0] = ((0.999000013f * fRec83[1]) + (fConst2 * ((fTemp206 - (fVec64[((IOTA - iTemp211) & 4095)] * (fTemp212 + (1.0f - fTemp210)))) - ((fTemp210 - fTemp212) * fVec64[((IOTA - (iTemp211 + 1)) & 4095)]))));
			iRec85[0] = ((iRec85[1] + iVec0[1]) % int((fSlow114 * fTemp50)));
			float fTemp213 = ((fRec84[1] * float((1 - ((iRec85[0] == 0) > 0)))) + (fSlow116 * fTemp51));
			fRec84[0] = (fTemp213 - floorf(fTemp213));
			float fTemp214 = faust_nuke_faustpower2_f(((2.0f * fRec84[0]) + -1.0f));
			fVec65[0] = fTemp214;
			float fTemp215 = (((fConst2 * (fTemp2 * ((fTemp206 - (fVec64[((IOTA - iTemp208) & 4095)] * (fTemp209 + (1.0f - fTemp207)))) - ((fTemp207 - fTemp209) * fVec64[((IOTA - (iTemp208 + 1)) & 4095)])))) + (fSlow121 * (((fTemp37 * fRec83[0]) * fTemp11) / fTemp21))) + (fSlow114 * ((fTemp12 * (fTemp214 - fVec65[1])) / fTemp51)));
			fRec69[0] = (((fTemp17 * (((fTemp2 * (fTemp174 - ((fVec52[((IOTA - iTemp176) & 4095)] * (fTemp177 + (1.0f - fTemp175))) + ((fTemp175 - fTemp177) * fVec52[((IOTA - (iTemp176 + 1)) & 4095)])))) + (fSlow107 * (fRec71[0] * fTemp11))) + (fSlow114 * ((fTemp12 * (fTemp179 - fVec53[1])) / fTemp14)))) + ((fTemp59 * (((fTemp2 * (fTemp182 - ((fVec56[((IOTA - iTemp184) & 4095)] * (fTemp185 + (1.0f - fTemp183))) + ((fTemp183 - fTemp185) * fVec56[((IOTA - (iTemp184 + 1)) & 4095)])))) + (fSlow121 * (fRec75[0] * fTemp11))) + (fSlow114 * ((fTemp12 * (fTemp187 - fVec57[1])) / fTemp66)))) + (fTemp69 + (float(iTemp18) * ((float(iTemp19) * (fTemp201 + fTemp215)) + ((float(iTemp55) * fTemp201) * (fTemp57 + (fTemp58 * fTemp215)))))))) - (((fTemp75 * fRec69[2]) + (2.0f * (fTemp76 * fRec69[1]))) / fTemp77));
			fRec68[0] = ((((fRec69[1] + (0.5f * fRec69[0])) + (0.5f * fRec69[2])) - ((fTemp75 * fRec68[2]) + (2.0f * (fTemp76 * fRec68[1])))) / fTemp77);
			iRec87[0] = (iSlow130 * (iRec87[1] + 1));
			int iTemp216 = (iRec87[0] < iSlow4);
			float fTemp217 = expf((0.0f - (fConst1 / (iSlow130?(iTemp216?fSlow3:fSlow5):fSlow2))));
			fRec86[0] = ((fRec86[1] * fTemp217) + ((iSlow130?(iTemp216?float(iSlow130):fSlow131):0.0f) * (1.0f - fTemp217)));
			fVec66[0] = fSlow134;
			float fTemp218 = (fRec90[1] + (fConst3 * fVec66[1]));
			fRec90[0] = (fTemp218 - floorf(fTemp218));
			float fTemp219 = faust_nuke_faustpower2_f(((2.0f * fRec90[0]) + -1.0f));
			fVec67[0] = fTemp219;
			float fTemp220 = (fSlow135 * ((fTemp219 - fVec67[1]) * float(iVec0[1])));
			fVec68[(IOTA & 4095)] = fTemp220;
			float fTemp221 = max(0.0f, min(2047.0f, (fSlow136 * fTemp6)));
			int iTemp222 = int(fTemp221);
			float fTemp223 = floorf(fTemp221);
			fRec91[0] = ((fTemp220 + (0.999000013f * fRec91[1])) - ((fSlow140 * fVec68[((IOTA - iSlow141) & 4095)]) + (fSlow142 * fVec68[((IOTA - iSlow143) & 4095)])));
			iRec93[0] = ((iRec93[1] + iVec0[1]) % iSlow145);
			float fTemp224 = ((fRec92[1] * float((1 - ((iRec93[0] == 0) > 0)))) + (fSlow146 * fTemp14));
			fRec92[0] = (fTemp224 - floorf(fTemp224));
			float fTemp225 = faust_nuke_faustpower2_f(((2.0f * fRec92[0]) + -1.0f));
			fVec69[0] = fTemp225;
			fVec70[0] = fSlow148;
			float fTemp226 = (fRec94[1] + (fConst3 * fVec70[1]));
			fRec94[0] = (fTemp226 - floorf(fTemp226));
			float fTemp227 = faust_nuke_faustpower2_f(((2.0f * fRec94[0]) + -1.0f));
			fVec71[0] = fTemp227;
			float fTemp228 = (fSlow149 * ((fTemp227 - fVec71[1]) * float(iVec0[1])));
			fVec72[(IOTA & 4095)] = fTemp228;
			float fTemp229 = max(0.0f, min(2047.0f, (fSlow150 * fTemp6)));
			int iTemp230 = int(fTemp229);
			float fTemp231 = floorf(fTemp229);
			fRec95[0] = ((fTemp228 + (0.999000013f * fRec95[1])) - ((fSlow154 * fVec72[((IOTA - iSlow155) & 4095)]) + (fSlow156 * fVec72[((IOTA - iSlow157) & 4095)])));
			iRec97[0] = ((iRec97[1] + iVec0[1]) % iSlow158);
			float fTemp232 = ((fRec96[1] * float((1 - ((iRec97[0] == 0) > 0)))) + (fSlow146 * fTemp66));
			fRec96[0] = (fTemp232 - floorf(fTemp232));
			float fTemp233 = faust_nuke_faustpower2_f(((2.0f * fRec96[0]) + -1.0f));
			fVec73[0] = fTemp233;
			float fTemp234 = max((fSlow132 * fTemp21), 23.4489498f);
			float fTemp235 = max(20.0f, fabsf(fTemp234));
			fVec74[0] = fTemp235;
			float fTemp236 = (fRec98[1] + (fConst3 * fVec74[1]));
			fRec98[0] = (fTemp236 - floorf(fTemp236));
			float fTemp237 = faust_nuke_faustpower2_f(((2.0f * fRec98[0]) + -1.0f));
			fVec75[0] = fTemp237;
			float fTemp238 = (((fTemp237 - fVec75[1]) * float(iVec0[1])) / fTemp235);
			fVec76[(IOTA & 4095)] = fTemp238;
			float fTemp239 = max(0.0f, min(2047.0f, (fConst0 * (fTemp6 / fTemp234))));
			int iTemp240 = int(fTemp239);
			float fTemp241 = floorf(fTemp239);
			float fTemp242 = max(0.0f, min(2047.0f, (fConst5 / fTemp234)));
			int iTemp243 = int(fTemp242);
			float fTemp244 = floorf(fTemp242);
			fRec99[0] = ((0.999000013f * fRec99[1]) + (fConst2 * ((fTemp238 - (fVec76[((IOTA - iTemp243) & 4095)] * (fTemp244 + (1.0f - fTemp242)))) - ((fTemp242 - fTemp244) * fVec76[((IOTA - (iTemp243 + 1)) & 4095)]))));
			iRec101[0] = ((iRec101[1] + iVec0[1]) % int((fSlow144 / fTemp21)));
			float fTemp245 = ((fRec100[1] * float((1 - ((iRec101[0] == 0) > 0)))) + (fSlow146 * fTemp33));
			fRec100[0] = (fTemp245 - floorf(fTemp245));
			float fTemp246 = faust_nuke_faustpower2_f(((2.0f * fRec100[0]) + -1.0f));
			fVec77[0] = fTemp246;
			float fTemp247 = (((fConst2 * (fTemp2 * ((fTemp238 - (fVec76[((IOTA - iTemp240) & 4095)] * (fTemp241 + (1.0f - fTemp239)))) - ((fTemp239 - fTemp241) * fVec76[((IOTA - (iTemp240 + 1)) & 4095)])))) + (fSlow151 * ((fRec99[0] * fTemp21) * fTemp11))) + (fSlow144 * ((fTemp12 * (fTemp246 - fVec77[1])) / fTemp33)));
			float fTemp248 = max((fSlow132 * fTemp38), 23.4489498f);
			float fTemp249 = max(20.0f, fabsf(fTemp248));
			fVec78[0] = fTemp249;
			float fTemp250 = (fRec102[1] + (fConst3 * fVec78[1]));
			fRec102[0] = (fTemp250 - floorf(fTemp250));
			float fTemp251 = faust_nuke_faustpower2_f(((2.0f * fRec102[0]) + -1.0f));
			fVec79[0] = fTemp251;
			float fTemp252 = (((fTemp251 - fVec79[1]) * float(iVec0[1])) / fTemp249);
			fVec80[(IOTA & 4095)] = fTemp252;
			float fTemp253 = max(0.0f, min(2047.0f, (fConst0 * (fTemp6 / fTemp248))));
			int iTemp254 = int(fTemp253);
			float fTemp255 = floorf(fTemp253);
			float fTemp256 = max(0.0f, min(2047.0f, (fConst5 / fTemp248)));
			int iTemp257 = int(fTemp256);
			float fTemp258 = floorf(fTemp256);
			fRec103[0] = ((0.999000013f * fRec103[1]) + (fConst2 * ((fTemp252 - (fVec80[((IOTA - iTemp257) & 4095)] * (fTemp258 + (1.0f - fTemp256)))) - ((fTemp256 - fTemp258) * fVec80[((IOTA - (iTemp257 + 1)) & 4095)]))));
			iRec105[0] = ((iRec105[1] + iVec0[1]) % int((fSlow144 * fTemp50)));
			float fTemp259 = ((fRec104[1] * float((1 - ((iRec105[0] == 0) > 0)))) + (fSlow146 * fTemp51));
			fRec104[0] = (fTemp259 - floorf(fTemp259));
			float fTemp260 = faust_nuke_faustpower2_f(((2.0f * fRec104[0]) + -1.0f));
			fVec81[0] = fTemp260;
			float fTemp261 = (((fConst2 * (fTemp2 * ((fTemp252 - (fVec80[((IOTA - iTemp254) & 4095)] * (fTemp255 + (1.0f - fTemp253)))) - ((fTemp253 - fTemp255) * fVec80[((IOTA - (iTemp254 + 1)) & 4095)])))) + (fSlow151 * (((fTemp37 * fRec103[0]) * fTemp11) / fTemp21))) + (fSlow144 * ((fTemp12 * (fTemp260 - fVec81[1])) / fTemp51)));
			fRec89[0] = (((fTemp17 * (((fTemp2 * (fTemp220 - ((fVec68[((IOTA - iTemp222) & 4095)] * (fTemp223 + (1.0f - fTemp221))) + ((fTemp221 - fTemp223) * fVec68[((IOTA - (iTemp222 + 1)) & 4095)])))) + (fSlow137 * (fRec91[0] * fTemp11))) + (fSlow144 * ((fTemp12 * (fTemp225 - fVec69[1])) / fTemp14)))) + ((fTemp59 * (((fTemp2 * (fTemp228 - ((fVec72[((IOTA - iTemp230) & 4095)] * (fTemp231 + (1.0f - fTemp229))) + ((fTemp229 - fTemp231) * fVec72[((IOTA - (iTemp230 + 1)) & 4095)])))) + (fSlow151 * (fRec95[0] * fTemp11))) + (fSlow144 * ((fTemp12 * (fTemp233 - fVec73[1])) / fTemp66)))) + (fTemp69 + (float(iTemp18) * ((float(iTemp19) * (fTemp247 + fTemp261)) + ((float(iTemp55) * fTemp247) * (fTemp57 + (fTemp58 * fTemp261)))))))) - (((fTemp75 * fRec89[2]) + (2.0f * (fTemp76 * fRec89[1]))) / fTemp77));
			fRec88[0] = ((((fRec89[1] + (0.5f * fRec89[0])) + (0.5f * fRec89[2])) - ((fTemp75 * fRec88[2]) + (2.0f * (fTemp76 * fRec88[1])))) / fTemp77);
			iRec107[0] = (iSlow160 * (iRec107[1] + 1));
			int iTemp262 = (iRec107[0] < iSlow4);
			float fTemp263 = expf((0.0f - (fConst1 / (iSlow160?(iTemp262?fSlow3:fSlow5):fSlow2))));
			fRec106[0] = ((fRec106[1] * fTemp263) + ((iSlow160?(iTemp262?float(iSlow160):fSlow161):0.0f) * (1.0f - fTemp263)));
			fVec82[0] = fSlow164;
			float fTemp264 = (fRec110[1] + (fConst3 * fVec82[1]));
			fRec110[0] = (fTemp264 - floorf(fTemp264));
			float fTemp265 = faust_nuke_faustpower2_f(((2.0f * fRec110[0]) + -1.0f));
			fVec83[0] = fTemp265;
			float fTemp266 = (fSlow165 * ((fTemp265 - fVec83[1]) * float(iVec0[1])));
			fVec84[(IOTA & 4095)] = fTemp266;
			float fTemp267 = max(0.0f, min(2047.0f, (fSlow166 * fTemp6)));
			int iTemp268 = int(fTemp267);
			float fTemp269 = floorf(fTemp267);
			fRec111[0] = ((fTemp266 + (0.999000013f * fRec111[1])) - ((fSlow170 * fVec84[((IOTA - iSlow171) & 4095)]) + (fSlow172 * fVec84[((IOTA - iSlow173) & 4095)])));
			iRec113[0] = ((iRec113[1] + iVec0[1]) % iSlow175);
			float fTemp270 = ((fRec112[1] * float((1 - ((iRec113[0] == 0) > 0)))) + (fSlow176 * fTemp14));
			fRec112[0] = (fTemp270 - floorf(fTemp270));
			float fTemp271 = faust_nuke_faustpower2_f(((2.0f * fRec112[0]) + -1.0f));
			fVec85[0] = fTemp271;
			fVec86[0] = fSlow178;
			float fTemp272 = (fRec114[1] + (fConst3 * fVec86[1]));
			fRec114[0] = (fTemp272 - floorf(fTemp272));
			float fTemp273 = faust_nuke_faustpower2_f(((2.0f * fRec114[0]) + -1.0f));
			fVec87[0] = fTemp273;
			float fTemp274 = (fSlow179 * ((fTemp273 - fVec87[1]) * float(iVec0[1])));
			fVec88[(IOTA & 4095)] = fTemp274;
			float fTemp275 = max(0.0f, min(2047.0f, (fSlow180 * fTemp6)));
			int iTemp276 = int(fTemp275);
			float fTemp277 = floorf(fTemp275);
			fRec115[0] = ((fTemp274 + (0.999000013f * fRec115[1])) - ((fSlow184 * fVec88[((IOTA - iSlow185) & 4095)]) + (fSlow186 * fVec88[((IOTA - iSlow187) & 4095)])));
			iRec117[0] = ((iRec117[1] + iVec0[1]) % iSlow188);
			float fTemp278 = ((fRec116[1] * float((1 - ((iRec117[0] == 0) > 0)))) + (fSlow176 * fTemp66));
			fRec116[0] = (fTemp278 - floorf(fTemp278));
			float fTemp279 = faust_nuke_faustpower2_f(((2.0f * fRec116[0]) + -1.0f));
			fVec89[0] = fTemp279;
			float fTemp280 = max((fSlow162 * fTemp21), 23.4489498f);
			float fTemp281 = max(20.0f, fabsf(fTemp280));
			fVec90[0] = fTemp281;
			float fTemp282 = (fRec118[1] + (fConst3 * fVec90[1]));
			fRec118[0] = (fTemp282 - floorf(fTemp282));
			float fTemp283 = faust_nuke_faustpower2_f(((2.0f * fRec118[0]) + -1.0f));
			fVec91[0] = fTemp283;
			float fTemp284 = (((fTemp283 - fVec91[1]) * float(iVec0[1])) / fTemp281);
			fVec92[(IOTA & 4095)] = fTemp284;
			float fTemp285 = max(0.0f, min(2047.0f, (fConst0 * (fTemp6 / fTemp280))));
			int iTemp286 = int(fTemp285);
			float fTemp287 = floorf(fTemp285);
			float fTemp288 = max(0.0f, min(2047.0f, (fConst5 / fTemp280)));
			int iTemp289 = int(fTemp288);
			float fTemp290 = floorf(fTemp288);
			fRec119[0] = ((0.999000013f * fRec119[1]) + (fConst2 * ((fTemp284 - (fVec92[((IOTA - iTemp289) & 4095)] * (fTemp290 + (1.0f - fTemp288)))) - ((fTemp288 - fTemp290) * fVec92[((IOTA - (iTemp289 + 1)) & 4095)]))));
			iRec121[0] = ((iRec121[1] + iVec0[1]) % int((fSlow174 / fTemp21)));
			float fTemp291 = ((fRec120[1] * float((1 - ((iRec121[0] == 0) > 0)))) + (fSlow176 * fTemp33));
			fRec120[0] = (fTemp291 - floorf(fTemp291));
			float fTemp292 = faust_nuke_faustpower2_f(((2.0f * fRec120[0]) + -1.0f));
			fVec93[0] = fTemp292;
			float fTemp293 = (((fConst2 * (fTemp2 * ((fTemp284 - (fVec92[((IOTA - iTemp286) & 4095)] * (fTemp287 + (1.0f - fTemp285)))) - ((fTemp285 - fTemp287) * fVec92[((IOTA - (iTemp286 + 1)) & 4095)])))) + (fSlow181 * ((fRec119[0] * fTemp21) * fTemp11))) + (fSlow174 * ((fTemp12 * (fTemp292 - fVec93[1])) / fTemp33)));
			float fTemp294 = max((fSlow162 * fTemp38), 23.4489498f);
			float fTemp295 = max(20.0f, fabsf(fTemp294));
			fVec94[0] = fTemp295;
			float fTemp296 = (fRec122[1] + (fConst3 * fVec94[1]));
			fRec122[0] = (fTemp296 - floorf(fTemp296));
			float fTemp297 = faust_nuke_faustpower2_f(((2.0f * fRec122[0]) + -1.0f));
			fVec95[0] = fTemp297;
			float fTemp298 = (((fTemp297 - fVec95[1]) * float(iVec0[1])) / fTemp295);
			fVec96[(IOTA & 4095)] = fTemp298;
			float fTemp299 = max(0.0f, min(2047.0f, (fConst0 * (fTemp6 / fTemp294))));
			int iTemp300 = int(fTemp299);
			float fTemp301 = floorf(fTemp299);
			float fTemp302 = max(0.0f, min(2047.0f, (fConst5 / fTemp294)));
			int iTemp303 = int(fTemp302);
			float fTemp304 = floorf(fTemp302);
			fRec123[0] = ((0.999000013f * fRec123[1]) + (fConst2 * ((fTemp298 - (fVec96[((IOTA - iTemp303) & 4095)] * (fTemp304 + (1.0f - fTemp302)))) - ((fTemp302 - fTemp304) * fVec96[((IOTA - (iTemp303 + 1)) & 4095)]))));
			iRec125[0] = ((iRec125[1] + iVec0[1]) % int((fSlow174 * fTemp50)));
			float fTemp305 = ((fRec124[1] * float((1 - ((iRec125[0] == 0) > 0)))) + (fSlow176 * fTemp51));
			fRec124[0] = (fTemp305 - floorf(fTemp305));
			float fTemp306 = faust_nuke_faustpower2_f(((2.0f * fRec124[0]) + -1.0f));
			fVec97[0] = fTemp306;
			float fTemp307 = (((fConst2 * (fTemp2 * ((fTemp298 - (fVec96[((IOTA - iTemp300) & 4095)] * (fTemp301 + (1.0f - fTemp299)))) - ((fTemp299 - fTemp301) * fVec96[((IOTA - (iTemp300 + 1)) & 4095)])))) + (fSlow181 * (((fTemp37 * fRec123[0]) * fTemp11) / fTemp21))) + (fSlow174 * ((fTemp12 * (fTemp306 - fVec97[1])) / fTemp51)));
			fRec109[0] = (((fTemp17 * (((fTemp2 * (fTemp266 - ((fVec84[((IOTA - iTemp268) & 4095)] * (fTemp269 + (1.0f - fTemp267))) + ((fTemp267 - fTemp269) * fVec84[((IOTA - (iTemp268 + 1)) & 4095)])))) + (fSlow167 * (fRec111[0] * fTemp11))) + (fSlow174 * ((fTemp12 * (fTemp271 - fVec85[1])) / fTemp14)))) + ((fTemp59 * (((fTemp2 * (fTemp274 - ((fVec88[((IOTA - iTemp276) & 4095)] * (fTemp277 + (1.0f - fTemp275))) + ((fTemp275 - fTemp277) * fVec88[((IOTA - (iTemp276 + 1)) & 4095)])))) + (fSlow181 * (fRec115[0] * fTemp11))) + (fSlow174 * ((fTemp12 * (fTemp279 - fVec89[1])) / fTemp66)))) + (fTemp69 + (float(iTemp18) * ((float(iTemp19) * (fTemp293 + fTemp307)) + ((float(iTemp55) * fTemp293) * (fTemp57 + (fTemp58 * fTemp307)))))))) - (((fTemp75 * fRec109[2]) + (2.0f * (fTemp76 * fRec109[1]))) / fTemp77));
			fRec108[0] = ((((fRec109[1] + (0.5f * fRec109[0])) + (0.5f * fRec109[2])) - ((fTemp75 * fRec108[2]) + (2.0f * (fTemp76 * fRec108[1])))) / fTemp77);
			output0[i] = FAUSTFLOAT((10.0f * (((((((fSlow0 * (fRec0[0] * ((fRec2[1] + (0.5f * fRec2[0])) + (0.5f * fRec2[2])))) + (fSlow39 * (fRec26[0] * ((fRec28[1] + (0.5f * fRec28[0])) + (0.5f * fRec28[2]))))) + (fSlow69 * (fRec46[0] * ((fRec48[1] + (0.5f * fRec48[0])) + (0.5f * fRec48[2]))))) + (fSlow99 * (fRec66[0] * ((fRec68[1] + (0.5f * fRec68[0])) + (0.5f * fRec68[2]))))) + (fSlow129 * (fRec86[0] * ((fRec88[1] + (0.5f * fRec88[0])) + (0.5f * fRec88[2]))))) + (fSlow159 * (fRec106[0] * ((fRec108[1] + (0.5f * fRec108[0])) + (0.5f * fRec108[2]))))) / fTemp77)));
			iVec0[1] = iVec0[0];
			iRec1[1] = iRec1[0];
			fRec0[1] = fRec0[0];
			fRec4[1] = fRec4[0];
			fVec1[1] = fVec1[0];
			fVec2[1] = fVec2[0];
			fRec5[1] = fRec5[0];
			fVec3[1] = fVec3[0];
			IOTA = (IOTA + 1);
			fRec6[1] = fRec6[0];
			iRec8[1] = iRec8[0];
			fRec7[1] = fRec7[0];
			fVec5[1] = fVec5[0];
			fRec9[1] = fRec9[0];
			fRec10[1] = fRec10[0];
			fVec6[1] = fVec6[0];
			fRec11[1] = fRec11[0];
			fVec7[1] = fVec7[0];
			fRec12[1] = fRec12[0];
			iRec14[1] = iRec14[0];
			fRec13[1] = fRec13[0];
			fVec9[1] = fVec9[0];
			fVec10[1] = fVec10[0];
			fRec15[1] = fRec15[0];
			fVec11[1] = fVec11[0];
			fRec16[1] = fRec16[0];
			iRec18[1] = iRec18[0];
			fRec17[1] = fRec17[0];
			fVec13[1] = fVec13[0];
			fVec14[1] = fVec14[0];
			fRec19[1] = fRec19[0];
			fVec15[1] = fVec15[0];
			fRec20[1] = fRec20[0];
			iRec22[1] = iRec22[0];
			fRec21[1] = fRec21[0];
			fVec17[1] = fVec17[0];
			iRec23[1] = iRec23[0];
			fRec24[1] = fRec24[0];
			fRec25[1] = fRec25[0];
			fRec3[2] = fRec3[1];
			fRec3[1] = fRec3[0];
			fRec2[2] = fRec2[1];
			fRec2[1] = fRec2[0];
			iRec27[1] = iRec27[0];
			fRec26[1] = fRec26[0];
			fVec18[1] = fVec18[0];
			fRec30[1] = fRec30[0];
			fVec19[1] = fVec19[0];
			fRec31[1] = fRec31[0];
			iRec33[1] = iRec33[0];
			fRec32[1] = fRec32[0];
			fVec21[1] = fVec21[0];
			fVec22[1] = fVec22[0];
			fRec34[1] = fRec34[0];
			fVec23[1] = fVec23[0];
			fRec35[1] = fRec35[0];
			iRec37[1] = iRec37[0];
			fRec36[1] = fRec36[0];
			fVec25[1] = fVec25[0];
			fVec26[1] = fVec26[0];
			fRec38[1] = fRec38[0];
			fVec27[1] = fVec27[0];
			fRec39[1] = fRec39[0];
			iRec41[1] = iRec41[0];
			fRec40[1] = fRec40[0];
			fVec29[1] = fVec29[0];
			fVec30[1] = fVec30[0];
			fRec42[1] = fRec42[0];
			fVec31[1] = fVec31[0];
			fRec43[1] = fRec43[0];
			iRec45[1] = iRec45[0];
			fRec44[1] = fRec44[0];
			fVec33[1] = fVec33[0];
			fRec29[2] = fRec29[1];
			fRec29[1] = fRec29[0];
			fRec28[2] = fRec28[1];
			fRec28[1] = fRec28[0];
			iRec47[1] = iRec47[0];
			fRec46[1] = fRec46[0];
			fVec34[1] = fVec34[0];
			fRec50[1] = fRec50[0];
			fVec35[1] = fVec35[0];
			fRec51[1] = fRec51[0];
			iRec53[1] = iRec53[0];
			fRec52[1] = fRec52[0];
			fVec37[1] = fVec37[0];
			fVec38[1] = fVec38[0];
			fRec54[1] = fRec54[0];
			fVec39[1] = fVec39[0];
			fRec55[1] = fRec55[0];
			iRec57[1] = iRec57[0];
			fRec56[1] = fRec56[0];
			fVec41[1] = fVec41[0];
			fVec42[1] = fVec42[0];
			fRec58[1] = fRec58[0];
			fVec43[1] = fVec43[0];
			fRec59[1] = fRec59[0];
			iRec61[1] = iRec61[0];
			fRec60[1] = fRec60[0];
			fVec45[1] = fVec45[0];
			fVec46[1] = fVec46[0];
			fRec62[1] = fRec62[0];
			fVec47[1] = fVec47[0];
			fRec63[1] = fRec63[0];
			iRec65[1] = iRec65[0];
			fRec64[1] = fRec64[0];
			fVec49[1] = fVec49[0];
			fRec49[2] = fRec49[1];
			fRec49[1] = fRec49[0];
			fRec48[2] = fRec48[1];
			fRec48[1] = fRec48[0];
			iRec67[1] = iRec67[0];
			fRec66[1] = fRec66[0];
			fVec50[1] = fVec50[0];
			fRec70[1] = fRec70[0];
			fVec51[1] = fVec51[0];
			fRec71[1] = fRec71[0];
			iRec73[1] = iRec73[0];
			fRec72[1] = fRec72[0];
			fVec53[1] = fVec53[0];
			fVec54[1] = fVec54[0];
			fRec74[1] = fRec74[0];
			fVec55[1] = fVec55[0];
			fRec75[1] = fRec75[0];
			iRec77[1] = iRec77[0];
			fRec76[1] = fRec76[0];
			fVec57[1] = fVec57[0];
			fVec58[1] = fVec58[0];
			fRec78[1] = fRec78[0];
			fVec59[1] = fVec59[0];
			fRec79[1] = fRec79[0];
			iRec81[1] = iRec81[0];
			fRec80[1] = fRec80[0];
			fVec61[1] = fVec61[0];
			fVec62[1] = fVec62[0];
			fRec82[1] = fRec82[0];
			fVec63[1] = fVec63[0];
			fRec83[1] = fRec83[0];
			iRec85[1] = iRec85[0];
			fRec84[1] = fRec84[0];
			fVec65[1] = fVec65[0];
			fRec69[2] = fRec69[1];
			fRec69[1] = fRec69[0];
			fRec68[2] = fRec68[1];
			fRec68[1] = fRec68[0];
			iRec87[1] = iRec87[0];
			fRec86[1] = fRec86[0];
			fVec66[1] = fVec66[0];
			fRec90[1] = fRec90[0];
			fVec67[1] = fVec67[0];
			fRec91[1] = fRec91[0];
			iRec93[1] = iRec93[0];
			fRec92[1] = fRec92[0];
			fVec69[1] = fVec69[0];
			fVec70[1] = fVec70[0];
			fRec94[1] = fRec94[0];
			fVec71[1] = fVec71[0];
			fRec95[1] = fRec95[0];
			iRec97[1] = iRec97[0];
			fRec96[1] = fRec96[0];
			fVec73[1] = fVec73[0];
			fVec74[1] = fVec74[0];
			fRec98[1] = fRec98[0];
			fVec75[1] = fVec75[0];
			fRec99[1] = fRec99[0];
			iRec101[1] = iRec101[0];
			fRec100[1] = fRec100[0];
			fVec77[1] = fVec77[0];
			fVec78[1] = fVec78[0];
			fRec102[1] = fRec102[0];
			fVec79[1] = fVec79[0];
			fRec103[1] = fRec103[0];
			iRec105[1] = iRec105[0];
			fRec104[1] = fRec104[0];
			fVec81[1] = fVec81[0];
			fRec89[2] = fRec89[1];
			fRec89[1] = fRec89[0];
			fRec88[2] = fRec88[1];
			fRec88[1] = fRec88[0];
			iRec107[1] = iRec107[0];
			fRec106[1] = fRec106[0];
			fVec82[1] = fVec82[0];
			fRec110[1] = fRec110[0];
			fVec83[1] = fVec83[0];
			fRec111[1] = fRec111[0];
			iRec113[1] = iRec113[0];
			fRec112[1] = fRec112[0];
			fVec85[1] = fVec85[0];
			fVec86[1] = fVec86[0];
			fRec114[1] = fRec114[0];
			fVec87[1] = fVec87[0];
			fRec115[1] = fRec115[0];
			iRec117[1] = iRec117[0];
			fRec116[1] = fRec116[0];
			fVec89[1] = fVec89[0];
			fVec90[1] = fVec90[0];
			fRec118[1] = fRec118[0];
			fVec91[1] = fVec91[0];
			fRec119[1] = fRec119[0];
			iRec121[1] = iRec121[0];
			fRec120[1] = fRec120[0];
			fVec93[1] = fVec93[0];
			fVec94[1] = fVec94[0];
			fRec122[1] = fRec122[0];
			fVec95[1] = fVec95[0];
			fRec123[1] = fRec123[0];
			iRec125[1] = iRec125[0];
			fRec124[1] = fRec124[0];
			fVec97[1] = fVec97[0];
			fRec109[2] = fRec109[1];
			fRec109[1] = fRec109[0];
			fRec108[2] = fRec108[1];
			fRec108[1] = fRec108[0];
			
		}
		
	}

	
};

#endif
