/* ------------------------------------------------------------
name: "nuke"
Code generated with Faust 2.5.23 (https://faust.grame.fr)
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
	FAUSTFLOAT fHslider1;
	float fRec2[2];
	float fVec1[2];
	int fSamplingFreq;
	float fConst0;
	float fConst1;
	FAUSTFLOAT fHslider2;
	float fVec2[2];
	float fConst2;
	float fRec3[2];
	float fVec3[2];
	int IOTA;
	float fVec4[4096];
	float fConst3;
	float fConst4;
	float fRec4[2];
	float fConst5;
	int iRec6[2];
	float fConst6;
	float fRec5[2];
	float fVec5[2];
	FAUSTFLOAT fHslider3;
	float fRec7[2];
	FAUSTFLOAT fHslider4;
	FAUSTFLOAT fHbargraph0;
	float fRec8[2];
	float fVec6[2];
	float fRec9[2];
	float fVec7[2];
	float fVec8[4096];
	float fConst7;
	float fRec10[2];
	int iRec12[2];
	float fRec11[2];
	float fVec9[2];
	float fVec10[2];
	float fRec13[2];
	float fVec11[2];
	float fVec12[4096];
	float fRec14[2];
	int iRec16[2];
	float fRec15[2];
	float fVec13[2];
	float fVec14[2];
	float fRec17[2];
	float fVec15[2];
	float fVec16[4096];
	float fRec18[2];
	int iRec20[2];
	float fRec19[2];
	float fVec17[2];
	int iRec21[2];
	float fConst8;
	FAUSTFLOAT fHslider5;
	float fRec22[2];
	FAUSTFLOAT fHbargraph1;
	float fRec23[2];
	float fRec1[3];
	float fRec0[3];
	FAUSTFLOAT fButton0;
	FAUSTFLOAT fHslider6;
	float fRec24[2];
	FAUSTFLOAT fHslider7;
	FAUSTFLOAT fHslider8;
	float fRec26[2];
	FAUSTFLOAT fHslider9;
	float fRec25[2];
	FAUSTFLOAT fHslider10;
	FAUSTFLOAT fHslider11;
	float fVec18[2];
	float fRec29[2];
	float fVec19[2];
	float fVec20[4096];
	float fRec30[2];
	int iRec32[2];
	float fRec31[2];
	float fVec21[2];
	float fVec22[2];
	float fRec33[2];
	float fVec23[2];
	float fVec24[4096];
	float fRec34[2];
	int iRec36[2];
	float fRec35[2];
	float fVec25[2];
	float fVec26[2];
	float fRec37[2];
	float fVec27[2];
	float fVec28[4096];
	float fRec38[2];
	int iRec40[2];
	float fRec39[2];
	float fVec29[2];
	float fVec30[2];
	float fRec41[2];
	float fVec31[2];
	float fVec32[4096];
	float fRec42[2];
	int iRec44[2];
	float fRec43[2];
	float fVec33[2];
	float fRec28[3];
	float fRec27[3];
	FAUSTFLOAT fButton1;
	float fRec45[2];
	float fRec47[2];
	float fRec46[2];
	FAUSTFLOAT fHslider12;
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
	FAUSTFLOAT fButton2;
	float fRec66[2];
	float fRec68[2];
	float fRec67[2];
	FAUSTFLOAT fHslider14;
	FAUSTFLOAT fHslider15;
	float fVec50[2];
	float fRec71[2];
	float fVec51[2];
	float fVec52[4096];
	float fRec72[2];
	int iRec74[2];
	float fRec73[2];
	float fVec53[2];
	float fVec54[2];
	float fRec75[2];
	float fVec55[2];
	float fVec56[4096];
	float fRec76[2];
	int iRec78[2];
	float fRec77[2];
	float fVec57[2];
	float fVec58[2];
	float fRec79[2];
	float fVec59[2];
	float fVec60[4096];
	float fRec80[2];
	int iRec82[2];
	float fRec81[2];
	float fVec61[2];
	float fVec62[2];
	float fRec83[2];
	float fVec63[2];
	float fVec64[4096];
	float fRec84[2];
	int iRec86[2];
	float fRec85[2];
	float fVec65[2];
	float fRec70[3];
	float fRec69[3];
	FAUSTFLOAT fButton3;
	float fRec87[2];
	float fRec89[2];
	float fRec88[2];
	FAUSTFLOAT fHslider16;
	FAUSTFLOAT fHslider17;
	float fVec66[2];
	float fRec92[2];
	float fVec67[2];
	float fVec68[4096];
	float fRec93[2];
	int iRec95[2];
	float fRec94[2];
	float fVec69[2];
	float fVec70[2];
	float fRec96[2];
	float fVec71[2];
	float fVec72[4096];
	float fRec97[2];
	int iRec99[2];
	float fRec98[2];
	float fVec73[2];
	float fVec74[2];
	float fRec100[2];
	float fVec75[2];
	float fVec76[4096];
	float fRec101[2];
	int iRec103[2];
	float fRec102[2];
	float fVec77[2];
	float fVec78[2];
	float fRec104[2];
	float fVec79[2];
	float fVec80[4096];
	float fRec105[2];
	int iRec107[2];
	float fRec106[2];
	float fVec81[2];
	float fRec91[3];
	float fRec90[3];
	FAUSTFLOAT fButton4;
	float fRec108[2];
	float fRec110[2];
	float fRec109[2];
	FAUSTFLOAT fHslider18;
	FAUSTFLOAT fHslider19;
	float fVec82[2];
	float fRec113[2];
	float fVec83[2];
	float fVec84[4096];
	float fRec114[2];
	int iRec116[2];
	float fRec115[2];
	float fVec85[2];
	float fVec86[2];
	float fRec117[2];
	float fVec87[2];
	float fVec88[4096];
	float fRec118[2];
	int iRec120[2];
	float fRec119[2];
	float fVec89[2];
	float fVec90[2];
	float fRec121[2];
	float fVec91[2];
	float fVec92[4096];
	float fRec122[2];
	int iRec124[2];
	float fRec123[2];
	float fVec93[2];
	float fVec94[2];
	float fRec125[2];
	float fVec95[2];
	float fVec96[4096];
	float fRec126[2];
	int iRec128[2];
	float fRec127[2];
	float fVec97[2];
	float fRec112[3];
	float fRec111[3];
	FAUSTFLOAT fButton5;
	float fRec129[2];
	float fRec131[2];
	float fRec130[2];
	
 public:
	
	void metadata(Meta* m) { 
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.0");
		m->declare("envelopes.lib/author", "GRAME");
		m->declare("envelopes.lib/copyright", "GRAME");
		m->declare("envelopes.lib/license", "LGPL with exception");
		m->declare("envelopes.lib/name", "Faust Envelope Library");
		m->declare("envelopes.lib/version", "0.0");
		m->declare("filename", "nuke");
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
		fConst1 = (0.25f * fConst0);
		fConst2 = (1.0f / fConst0);
		fConst3 = (2.5999999f / fConst0);
		fConst4 = (0.5f * fConst0);
		fConst5 = (2.0f * fConst0);
		fConst6 = (1.0f / fConst0);
		fConst7 = (5.19999981f / fConst0);
		fConst8 = (3.14159274f / fConst0);
		
	}
	
	virtual void instanceResetUserInterface() {
		fHslider0 = FAUSTFLOAT(0.5f);
		fHslider1 = FAUSTFLOAT(0.0f);
		fHslider2 = FAUSTFLOAT(440.0f);
		fHslider3 = FAUSTFLOAT(0.0f);
		fHslider4 = FAUSTFLOAT(2.0f);
		fHslider5 = FAUSTFLOAT(20.0f);
		fButton0 = FAUSTFLOAT(0.0f);
		fHslider6 = FAUSTFLOAT(0.0f);
		fHslider7 = FAUSTFLOAT(0.001f);
		fHslider8 = FAUSTFLOAT(0.0f);
		fHslider9 = FAUSTFLOAT(1.0f);
		fHslider10 = FAUSTFLOAT(0.5f);
		fHslider11 = FAUSTFLOAT(440.0f);
		fButton1 = FAUSTFLOAT(0.0f);
		fHslider12 = FAUSTFLOAT(0.5f);
		fHslider13 = FAUSTFLOAT(440.0f);
		fButton2 = FAUSTFLOAT(0.0f);
		fHslider14 = FAUSTFLOAT(0.5f);
		fHslider15 = FAUSTFLOAT(440.0f);
		fButton3 = FAUSTFLOAT(0.0f);
		fHslider16 = FAUSTFLOAT(0.5f);
		fHslider17 = FAUSTFLOAT(440.0f);
		fButton4 = FAUSTFLOAT(0.0f);
		fHslider18 = FAUSTFLOAT(0.5f);
		fHslider19 = FAUSTFLOAT(440.0f);
		fButton5 = FAUSTFLOAT(0.0f);
		
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			iVec0[l0] = 0;
			
		}
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			fRec2[l1] = 0.0f;
			
		}
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			fVec1[l2] = 0.0f;
			
		}
		for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			fVec2[l3] = 0.0f;
			
		}
		for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			fRec3[l4] = 0.0f;
			
		}
		for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			fVec3[l5] = 0.0f;
			
		}
		IOTA = 0;
		for (int l6 = 0; (l6 < 4096); l6 = (l6 + 1)) {
			fVec4[l6] = 0.0f;
			
		}
		for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			fRec4[l7] = 0.0f;
			
		}
		for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			iRec6[l8] = 0;
			
		}
		for (int l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			fRec5[l9] = 0.0f;
			
		}
		for (int l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
			fVec5[l10] = 0.0f;
			
		}
		for (int l11 = 0; (l11 < 2); l11 = (l11 + 1)) {
			fRec7[l11] = 0.0f;
			
		}
		for (int l12 = 0; (l12 < 2); l12 = (l12 + 1)) {
			fRec8[l12] = 0.0f;
			
		}
		for (int l13 = 0; (l13 < 2); l13 = (l13 + 1)) {
			fVec6[l13] = 0.0f;
			
		}
		for (int l14 = 0; (l14 < 2); l14 = (l14 + 1)) {
			fRec9[l14] = 0.0f;
			
		}
		for (int l15 = 0; (l15 < 2); l15 = (l15 + 1)) {
			fVec7[l15] = 0.0f;
			
		}
		for (int l16 = 0; (l16 < 4096); l16 = (l16 + 1)) {
			fVec8[l16] = 0.0f;
			
		}
		for (int l17 = 0; (l17 < 2); l17 = (l17 + 1)) {
			fRec10[l17] = 0.0f;
			
		}
		for (int l18 = 0; (l18 < 2); l18 = (l18 + 1)) {
			iRec12[l18] = 0;
			
		}
		for (int l19 = 0; (l19 < 2); l19 = (l19 + 1)) {
			fRec11[l19] = 0.0f;
			
		}
		for (int l20 = 0; (l20 < 2); l20 = (l20 + 1)) {
			fVec9[l20] = 0.0f;
			
		}
		for (int l21 = 0; (l21 < 2); l21 = (l21 + 1)) {
			fVec10[l21] = 0.0f;
			
		}
		for (int l22 = 0; (l22 < 2); l22 = (l22 + 1)) {
			fRec13[l22] = 0.0f;
			
		}
		for (int l23 = 0; (l23 < 2); l23 = (l23 + 1)) {
			fVec11[l23] = 0.0f;
			
		}
		for (int l24 = 0; (l24 < 4096); l24 = (l24 + 1)) {
			fVec12[l24] = 0.0f;
			
		}
		for (int l25 = 0; (l25 < 2); l25 = (l25 + 1)) {
			fRec14[l25] = 0.0f;
			
		}
		for (int l26 = 0; (l26 < 2); l26 = (l26 + 1)) {
			iRec16[l26] = 0;
			
		}
		for (int l27 = 0; (l27 < 2); l27 = (l27 + 1)) {
			fRec15[l27] = 0.0f;
			
		}
		for (int l28 = 0; (l28 < 2); l28 = (l28 + 1)) {
			fVec13[l28] = 0.0f;
			
		}
		for (int l29 = 0; (l29 < 2); l29 = (l29 + 1)) {
			fVec14[l29] = 0.0f;
			
		}
		for (int l30 = 0; (l30 < 2); l30 = (l30 + 1)) {
			fRec17[l30] = 0.0f;
			
		}
		for (int l31 = 0; (l31 < 2); l31 = (l31 + 1)) {
			fVec15[l31] = 0.0f;
			
		}
		for (int l32 = 0; (l32 < 4096); l32 = (l32 + 1)) {
			fVec16[l32] = 0.0f;
			
		}
		for (int l33 = 0; (l33 < 2); l33 = (l33 + 1)) {
			fRec18[l33] = 0.0f;
			
		}
		for (int l34 = 0; (l34 < 2); l34 = (l34 + 1)) {
			iRec20[l34] = 0;
			
		}
		for (int l35 = 0; (l35 < 2); l35 = (l35 + 1)) {
			fRec19[l35] = 0.0f;
			
		}
		for (int l36 = 0; (l36 < 2); l36 = (l36 + 1)) {
			fVec17[l36] = 0.0f;
			
		}
		for (int l37 = 0; (l37 < 2); l37 = (l37 + 1)) {
			iRec21[l37] = 0;
			
		}
		for (int l38 = 0; (l38 < 2); l38 = (l38 + 1)) {
			fRec22[l38] = 0.0f;
			
		}
		for (int l39 = 0; (l39 < 2); l39 = (l39 + 1)) {
			fRec23[l39] = 0.0f;
			
		}
		for (int l40 = 0; (l40 < 3); l40 = (l40 + 1)) {
			fRec1[l40] = 0.0f;
			
		}
		for (int l41 = 0; (l41 < 3); l41 = (l41 + 1)) {
			fRec0[l41] = 0.0f;
			
		}
		for (int l42 = 0; (l42 < 2); l42 = (l42 + 1)) {
			fRec24[l42] = 0.0f;
			
		}
		for (int l43 = 0; (l43 < 2); l43 = (l43 + 1)) {
			fRec26[l43] = 0.0f;
			
		}
		for (int l44 = 0; (l44 < 2); l44 = (l44 + 1)) {
			fRec25[l44] = 0.0f;
			
		}
		for (int l45 = 0; (l45 < 2); l45 = (l45 + 1)) {
			fVec18[l45] = 0.0f;
			
		}
		for (int l46 = 0; (l46 < 2); l46 = (l46 + 1)) {
			fRec29[l46] = 0.0f;
			
		}
		for (int l47 = 0; (l47 < 2); l47 = (l47 + 1)) {
			fVec19[l47] = 0.0f;
			
		}
		for (int l48 = 0; (l48 < 4096); l48 = (l48 + 1)) {
			fVec20[l48] = 0.0f;
			
		}
		for (int l49 = 0; (l49 < 2); l49 = (l49 + 1)) {
			fRec30[l49] = 0.0f;
			
		}
		for (int l50 = 0; (l50 < 2); l50 = (l50 + 1)) {
			iRec32[l50] = 0;
			
		}
		for (int l51 = 0; (l51 < 2); l51 = (l51 + 1)) {
			fRec31[l51] = 0.0f;
			
		}
		for (int l52 = 0; (l52 < 2); l52 = (l52 + 1)) {
			fVec21[l52] = 0.0f;
			
		}
		for (int l53 = 0; (l53 < 2); l53 = (l53 + 1)) {
			fVec22[l53] = 0.0f;
			
		}
		for (int l54 = 0; (l54 < 2); l54 = (l54 + 1)) {
			fRec33[l54] = 0.0f;
			
		}
		for (int l55 = 0; (l55 < 2); l55 = (l55 + 1)) {
			fVec23[l55] = 0.0f;
			
		}
		for (int l56 = 0; (l56 < 4096); l56 = (l56 + 1)) {
			fVec24[l56] = 0.0f;
			
		}
		for (int l57 = 0; (l57 < 2); l57 = (l57 + 1)) {
			fRec34[l57] = 0.0f;
			
		}
		for (int l58 = 0; (l58 < 2); l58 = (l58 + 1)) {
			iRec36[l58] = 0;
			
		}
		for (int l59 = 0; (l59 < 2); l59 = (l59 + 1)) {
			fRec35[l59] = 0.0f;
			
		}
		for (int l60 = 0; (l60 < 2); l60 = (l60 + 1)) {
			fVec25[l60] = 0.0f;
			
		}
		for (int l61 = 0; (l61 < 2); l61 = (l61 + 1)) {
			fVec26[l61] = 0.0f;
			
		}
		for (int l62 = 0; (l62 < 2); l62 = (l62 + 1)) {
			fRec37[l62] = 0.0f;
			
		}
		for (int l63 = 0; (l63 < 2); l63 = (l63 + 1)) {
			fVec27[l63] = 0.0f;
			
		}
		for (int l64 = 0; (l64 < 4096); l64 = (l64 + 1)) {
			fVec28[l64] = 0.0f;
			
		}
		for (int l65 = 0; (l65 < 2); l65 = (l65 + 1)) {
			fRec38[l65] = 0.0f;
			
		}
		for (int l66 = 0; (l66 < 2); l66 = (l66 + 1)) {
			iRec40[l66] = 0;
			
		}
		for (int l67 = 0; (l67 < 2); l67 = (l67 + 1)) {
			fRec39[l67] = 0.0f;
			
		}
		for (int l68 = 0; (l68 < 2); l68 = (l68 + 1)) {
			fVec29[l68] = 0.0f;
			
		}
		for (int l69 = 0; (l69 < 2); l69 = (l69 + 1)) {
			fVec30[l69] = 0.0f;
			
		}
		for (int l70 = 0; (l70 < 2); l70 = (l70 + 1)) {
			fRec41[l70] = 0.0f;
			
		}
		for (int l71 = 0; (l71 < 2); l71 = (l71 + 1)) {
			fVec31[l71] = 0.0f;
			
		}
		for (int l72 = 0; (l72 < 4096); l72 = (l72 + 1)) {
			fVec32[l72] = 0.0f;
			
		}
		for (int l73 = 0; (l73 < 2); l73 = (l73 + 1)) {
			fRec42[l73] = 0.0f;
			
		}
		for (int l74 = 0; (l74 < 2); l74 = (l74 + 1)) {
			iRec44[l74] = 0;
			
		}
		for (int l75 = 0; (l75 < 2); l75 = (l75 + 1)) {
			fRec43[l75] = 0.0f;
			
		}
		for (int l76 = 0; (l76 < 2); l76 = (l76 + 1)) {
			fVec33[l76] = 0.0f;
			
		}
		for (int l77 = 0; (l77 < 3); l77 = (l77 + 1)) {
			fRec28[l77] = 0.0f;
			
		}
		for (int l78 = 0; (l78 < 3); l78 = (l78 + 1)) {
			fRec27[l78] = 0.0f;
			
		}
		for (int l79 = 0; (l79 < 2); l79 = (l79 + 1)) {
			fRec45[l79] = 0.0f;
			
		}
		for (int l80 = 0; (l80 < 2); l80 = (l80 + 1)) {
			fRec47[l80] = 0.0f;
			
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
			fRec66[l116] = 0.0f;
			
		}
		for (int l117 = 0; (l117 < 2); l117 = (l117 + 1)) {
			fRec68[l117] = 0.0f;
			
		}
		for (int l118 = 0; (l118 < 2); l118 = (l118 + 1)) {
			fRec67[l118] = 0.0f;
			
		}
		for (int l119 = 0; (l119 < 2); l119 = (l119 + 1)) {
			fVec50[l119] = 0.0f;
			
		}
		for (int l120 = 0; (l120 < 2); l120 = (l120 + 1)) {
			fRec71[l120] = 0.0f;
			
		}
		for (int l121 = 0; (l121 < 2); l121 = (l121 + 1)) {
			fVec51[l121] = 0.0f;
			
		}
		for (int l122 = 0; (l122 < 4096); l122 = (l122 + 1)) {
			fVec52[l122] = 0.0f;
			
		}
		for (int l123 = 0; (l123 < 2); l123 = (l123 + 1)) {
			fRec72[l123] = 0.0f;
			
		}
		for (int l124 = 0; (l124 < 2); l124 = (l124 + 1)) {
			iRec74[l124] = 0;
			
		}
		for (int l125 = 0; (l125 < 2); l125 = (l125 + 1)) {
			fRec73[l125] = 0.0f;
			
		}
		for (int l126 = 0; (l126 < 2); l126 = (l126 + 1)) {
			fVec53[l126] = 0.0f;
			
		}
		for (int l127 = 0; (l127 < 2); l127 = (l127 + 1)) {
			fVec54[l127] = 0.0f;
			
		}
		for (int l128 = 0; (l128 < 2); l128 = (l128 + 1)) {
			fRec75[l128] = 0.0f;
			
		}
		for (int l129 = 0; (l129 < 2); l129 = (l129 + 1)) {
			fVec55[l129] = 0.0f;
			
		}
		for (int l130 = 0; (l130 < 4096); l130 = (l130 + 1)) {
			fVec56[l130] = 0.0f;
			
		}
		for (int l131 = 0; (l131 < 2); l131 = (l131 + 1)) {
			fRec76[l131] = 0.0f;
			
		}
		for (int l132 = 0; (l132 < 2); l132 = (l132 + 1)) {
			iRec78[l132] = 0;
			
		}
		for (int l133 = 0; (l133 < 2); l133 = (l133 + 1)) {
			fRec77[l133] = 0.0f;
			
		}
		for (int l134 = 0; (l134 < 2); l134 = (l134 + 1)) {
			fVec57[l134] = 0.0f;
			
		}
		for (int l135 = 0; (l135 < 2); l135 = (l135 + 1)) {
			fVec58[l135] = 0.0f;
			
		}
		for (int l136 = 0; (l136 < 2); l136 = (l136 + 1)) {
			fRec79[l136] = 0.0f;
			
		}
		for (int l137 = 0; (l137 < 2); l137 = (l137 + 1)) {
			fVec59[l137] = 0.0f;
			
		}
		for (int l138 = 0; (l138 < 4096); l138 = (l138 + 1)) {
			fVec60[l138] = 0.0f;
			
		}
		for (int l139 = 0; (l139 < 2); l139 = (l139 + 1)) {
			fRec80[l139] = 0.0f;
			
		}
		for (int l140 = 0; (l140 < 2); l140 = (l140 + 1)) {
			iRec82[l140] = 0;
			
		}
		for (int l141 = 0; (l141 < 2); l141 = (l141 + 1)) {
			fRec81[l141] = 0.0f;
			
		}
		for (int l142 = 0; (l142 < 2); l142 = (l142 + 1)) {
			fVec61[l142] = 0.0f;
			
		}
		for (int l143 = 0; (l143 < 2); l143 = (l143 + 1)) {
			fVec62[l143] = 0.0f;
			
		}
		for (int l144 = 0; (l144 < 2); l144 = (l144 + 1)) {
			fRec83[l144] = 0.0f;
			
		}
		for (int l145 = 0; (l145 < 2); l145 = (l145 + 1)) {
			fVec63[l145] = 0.0f;
			
		}
		for (int l146 = 0; (l146 < 4096); l146 = (l146 + 1)) {
			fVec64[l146] = 0.0f;
			
		}
		for (int l147 = 0; (l147 < 2); l147 = (l147 + 1)) {
			fRec84[l147] = 0.0f;
			
		}
		for (int l148 = 0; (l148 < 2); l148 = (l148 + 1)) {
			iRec86[l148] = 0;
			
		}
		for (int l149 = 0; (l149 < 2); l149 = (l149 + 1)) {
			fRec85[l149] = 0.0f;
			
		}
		for (int l150 = 0; (l150 < 2); l150 = (l150 + 1)) {
			fVec65[l150] = 0.0f;
			
		}
		for (int l151 = 0; (l151 < 3); l151 = (l151 + 1)) {
			fRec70[l151] = 0.0f;
			
		}
		for (int l152 = 0; (l152 < 3); l152 = (l152 + 1)) {
			fRec69[l152] = 0.0f;
			
		}
		for (int l153 = 0; (l153 < 2); l153 = (l153 + 1)) {
			fRec87[l153] = 0.0f;
			
		}
		for (int l154 = 0; (l154 < 2); l154 = (l154 + 1)) {
			fRec89[l154] = 0.0f;
			
		}
		for (int l155 = 0; (l155 < 2); l155 = (l155 + 1)) {
			fRec88[l155] = 0.0f;
			
		}
		for (int l156 = 0; (l156 < 2); l156 = (l156 + 1)) {
			fVec66[l156] = 0.0f;
			
		}
		for (int l157 = 0; (l157 < 2); l157 = (l157 + 1)) {
			fRec92[l157] = 0.0f;
			
		}
		for (int l158 = 0; (l158 < 2); l158 = (l158 + 1)) {
			fVec67[l158] = 0.0f;
			
		}
		for (int l159 = 0; (l159 < 4096); l159 = (l159 + 1)) {
			fVec68[l159] = 0.0f;
			
		}
		for (int l160 = 0; (l160 < 2); l160 = (l160 + 1)) {
			fRec93[l160] = 0.0f;
			
		}
		for (int l161 = 0; (l161 < 2); l161 = (l161 + 1)) {
			iRec95[l161] = 0;
			
		}
		for (int l162 = 0; (l162 < 2); l162 = (l162 + 1)) {
			fRec94[l162] = 0.0f;
			
		}
		for (int l163 = 0; (l163 < 2); l163 = (l163 + 1)) {
			fVec69[l163] = 0.0f;
			
		}
		for (int l164 = 0; (l164 < 2); l164 = (l164 + 1)) {
			fVec70[l164] = 0.0f;
			
		}
		for (int l165 = 0; (l165 < 2); l165 = (l165 + 1)) {
			fRec96[l165] = 0.0f;
			
		}
		for (int l166 = 0; (l166 < 2); l166 = (l166 + 1)) {
			fVec71[l166] = 0.0f;
			
		}
		for (int l167 = 0; (l167 < 4096); l167 = (l167 + 1)) {
			fVec72[l167] = 0.0f;
			
		}
		for (int l168 = 0; (l168 < 2); l168 = (l168 + 1)) {
			fRec97[l168] = 0.0f;
			
		}
		for (int l169 = 0; (l169 < 2); l169 = (l169 + 1)) {
			iRec99[l169] = 0;
			
		}
		for (int l170 = 0; (l170 < 2); l170 = (l170 + 1)) {
			fRec98[l170] = 0.0f;
			
		}
		for (int l171 = 0; (l171 < 2); l171 = (l171 + 1)) {
			fVec73[l171] = 0.0f;
			
		}
		for (int l172 = 0; (l172 < 2); l172 = (l172 + 1)) {
			fVec74[l172] = 0.0f;
			
		}
		for (int l173 = 0; (l173 < 2); l173 = (l173 + 1)) {
			fRec100[l173] = 0.0f;
			
		}
		for (int l174 = 0; (l174 < 2); l174 = (l174 + 1)) {
			fVec75[l174] = 0.0f;
			
		}
		for (int l175 = 0; (l175 < 4096); l175 = (l175 + 1)) {
			fVec76[l175] = 0.0f;
			
		}
		for (int l176 = 0; (l176 < 2); l176 = (l176 + 1)) {
			fRec101[l176] = 0.0f;
			
		}
		for (int l177 = 0; (l177 < 2); l177 = (l177 + 1)) {
			iRec103[l177] = 0;
			
		}
		for (int l178 = 0; (l178 < 2); l178 = (l178 + 1)) {
			fRec102[l178] = 0.0f;
			
		}
		for (int l179 = 0; (l179 < 2); l179 = (l179 + 1)) {
			fVec77[l179] = 0.0f;
			
		}
		for (int l180 = 0; (l180 < 2); l180 = (l180 + 1)) {
			fVec78[l180] = 0.0f;
			
		}
		for (int l181 = 0; (l181 < 2); l181 = (l181 + 1)) {
			fRec104[l181] = 0.0f;
			
		}
		for (int l182 = 0; (l182 < 2); l182 = (l182 + 1)) {
			fVec79[l182] = 0.0f;
			
		}
		for (int l183 = 0; (l183 < 4096); l183 = (l183 + 1)) {
			fVec80[l183] = 0.0f;
			
		}
		for (int l184 = 0; (l184 < 2); l184 = (l184 + 1)) {
			fRec105[l184] = 0.0f;
			
		}
		for (int l185 = 0; (l185 < 2); l185 = (l185 + 1)) {
			iRec107[l185] = 0;
			
		}
		for (int l186 = 0; (l186 < 2); l186 = (l186 + 1)) {
			fRec106[l186] = 0.0f;
			
		}
		for (int l187 = 0; (l187 < 2); l187 = (l187 + 1)) {
			fVec81[l187] = 0.0f;
			
		}
		for (int l188 = 0; (l188 < 3); l188 = (l188 + 1)) {
			fRec91[l188] = 0.0f;
			
		}
		for (int l189 = 0; (l189 < 3); l189 = (l189 + 1)) {
			fRec90[l189] = 0.0f;
			
		}
		for (int l190 = 0; (l190 < 2); l190 = (l190 + 1)) {
			fRec108[l190] = 0.0f;
			
		}
		for (int l191 = 0; (l191 < 2); l191 = (l191 + 1)) {
			fRec110[l191] = 0.0f;
			
		}
		for (int l192 = 0; (l192 < 2); l192 = (l192 + 1)) {
			fRec109[l192] = 0.0f;
			
		}
		for (int l193 = 0; (l193 < 2); l193 = (l193 + 1)) {
			fVec82[l193] = 0.0f;
			
		}
		for (int l194 = 0; (l194 < 2); l194 = (l194 + 1)) {
			fRec113[l194] = 0.0f;
			
		}
		for (int l195 = 0; (l195 < 2); l195 = (l195 + 1)) {
			fVec83[l195] = 0.0f;
			
		}
		for (int l196 = 0; (l196 < 4096); l196 = (l196 + 1)) {
			fVec84[l196] = 0.0f;
			
		}
		for (int l197 = 0; (l197 < 2); l197 = (l197 + 1)) {
			fRec114[l197] = 0.0f;
			
		}
		for (int l198 = 0; (l198 < 2); l198 = (l198 + 1)) {
			iRec116[l198] = 0;
			
		}
		for (int l199 = 0; (l199 < 2); l199 = (l199 + 1)) {
			fRec115[l199] = 0.0f;
			
		}
		for (int l200 = 0; (l200 < 2); l200 = (l200 + 1)) {
			fVec85[l200] = 0.0f;
			
		}
		for (int l201 = 0; (l201 < 2); l201 = (l201 + 1)) {
			fVec86[l201] = 0.0f;
			
		}
		for (int l202 = 0; (l202 < 2); l202 = (l202 + 1)) {
			fRec117[l202] = 0.0f;
			
		}
		for (int l203 = 0; (l203 < 2); l203 = (l203 + 1)) {
			fVec87[l203] = 0.0f;
			
		}
		for (int l204 = 0; (l204 < 4096); l204 = (l204 + 1)) {
			fVec88[l204] = 0.0f;
			
		}
		for (int l205 = 0; (l205 < 2); l205 = (l205 + 1)) {
			fRec118[l205] = 0.0f;
			
		}
		for (int l206 = 0; (l206 < 2); l206 = (l206 + 1)) {
			iRec120[l206] = 0;
			
		}
		for (int l207 = 0; (l207 < 2); l207 = (l207 + 1)) {
			fRec119[l207] = 0.0f;
			
		}
		for (int l208 = 0; (l208 < 2); l208 = (l208 + 1)) {
			fVec89[l208] = 0.0f;
			
		}
		for (int l209 = 0; (l209 < 2); l209 = (l209 + 1)) {
			fVec90[l209] = 0.0f;
			
		}
		for (int l210 = 0; (l210 < 2); l210 = (l210 + 1)) {
			fRec121[l210] = 0.0f;
			
		}
		for (int l211 = 0; (l211 < 2); l211 = (l211 + 1)) {
			fVec91[l211] = 0.0f;
			
		}
		for (int l212 = 0; (l212 < 4096); l212 = (l212 + 1)) {
			fVec92[l212] = 0.0f;
			
		}
		for (int l213 = 0; (l213 < 2); l213 = (l213 + 1)) {
			fRec122[l213] = 0.0f;
			
		}
		for (int l214 = 0; (l214 < 2); l214 = (l214 + 1)) {
			iRec124[l214] = 0;
			
		}
		for (int l215 = 0; (l215 < 2); l215 = (l215 + 1)) {
			fRec123[l215] = 0.0f;
			
		}
		for (int l216 = 0; (l216 < 2); l216 = (l216 + 1)) {
			fVec93[l216] = 0.0f;
			
		}
		for (int l217 = 0; (l217 < 2); l217 = (l217 + 1)) {
			fVec94[l217] = 0.0f;
			
		}
		for (int l218 = 0; (l218 < 2); l218 = (l218 + 1)) {
			fRec125[l218] = 0.0f;
			
		}
		for (int l219 = 0; (l219 < 2); l219 = (l219 + 1)) {
			fVec95[l219] = 0.0f;
			
		}
		for (int l220 = 0; (l220 < 4096); l220 = (l220 + 1)) {
			fVec96[l220] = 0.0f;
			
		}
		for (int l221 = 0; (l221 < 2); l221 = (l221 + 1)) {
			fRec126[l221] = 0.0f;
			
		}
		for (int l222 = 0; (l222 < 2); l222 = (l222 + 1)) {
			iRec128[l222] = 0;
			
		}
		for (int l223 = 0; (l223 < 2); l223 = (l223 + 1)) {
			fRec127[l223] = 0.0f;
			
		}
		for (int l224 = 0; (l224 < 2); l224 = (l224 + 1)) {
			fVec97[l224] = 0.0f;
			
		}
		for (int l225 = 0; (l225 < 3); l225 = (l225 + 1)) {
			fRec112[l225] = 0.0f;
			
		}
		for (int l226 = 0; (l226 < 3); l226 = (l226 + 1)) {
			fRec111[l226] = 0.0f;
			
		}
		for (int l227 = 0; (l227 < 2); l227 = (l227 + 1)) {
			fRec129[l227] = 0.0f;
			
		}
		for (int l228 = 0; (l228 < 2); l228 = (l228 + 1)) {
			fRec131[l228] = 0.0f;
			
		}
		for (int l229 = 0; (l229 < 2); l229 = (l229 + 1)) {
			fRec130[l229] = 0.0f;
			
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
		ui_interface->addHorizontalSlider("Aux", &fHslider3, 0.0f, 0.0f, 3.0f, 0.00100000005f);
		ui_interface->addHorizontalBargraph("Bars", &fHbargraph1, 0.0f, 5.0f);
		ui_interface->addHorizontalBargraph("Dots", &fHbargraph0, 0.0f, 6.0f);
		ui_interface->addHorizontalSlider("Filter", &fHslider5, 20.0f, 0.0f, 99.0f, 1.0f);
		ui_interface->addHorizontalSlider("Relation", &fHslider4, 2.0f, 0.0f, 3.00099993f, 0.00100000005f);
		ui_interface->addHorizontalSlider("Wave", &fHslider1, 0.0f, 0.0f, 4.0f, 0.00999999978f);
		ui_interface->openVerticalBox("envelope");
		ui_interface->addHorizontalSlider("Attack", &fHslider7, 0.00100000005f, 0.00100000005f, 4.0f, 0.00100000005f);
		ui_interface->addHorizontalSlider("Decay", &fHslider8, 0.0f, 0.0f, 4.0f, 0.00100000005f);
		ui_interface->addHorizontalSlider("Release", &fHslider6, 0.0f, 0.0f, 4.0f, 0.00999999978f);
		ui_interface->addHorizontalSlider("Sustain", &fHslider9, 1.0f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface->closeBox();
		ui_interface->openHorizontalBox("voices");
		ui_interface->openVerticalBox("0");
		ui_interface->openHorizontalBox("midi");
		ui_interface->addHorizontalSlider("freq", &fHslider2, 440.0f, 20.0f, 1000.0f, 1.0f);
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
		float fSlow1 = (0.00100000005f * float(fHslider1));
		float fSlow2 = float(fHslider2);
		float fSlow3 = max((0.5f * fSlow2), 23.4489498f);
		float fSlow4 = max(20.0f, fabsf(fSlow3));
		float fSlow5 = (fConst1 / fSlow4);
		float fSlow6 = (fConst0 / fSlow3);
		float fSlow7 = (fConst3 * fSlow2);
		float fSlow8 = max(0.0f, min(2047.0f, (fConst4 / fSlow3)));
		float fSlow9 = floorf(fSlow8);
		float fSlow10 = (fSlow9 + (1.0f - fSlow8));
		int iSlow11 = int(fSlow8);
		float fSlow12 = (fSlow8 - fSlow9);
		int iSlow13 = (iSlow11 + 1);
		float fSlow14 = (fConst0 / fSlow2);
		int iSlow15 = int((fConst5 / fSlow2));
		float fSlow16 = (fConst6 * fSlow2);
		float fSlow17 = (0.00100000005f * float(fHslider3));
		fHbargraph0 = FAUSTFLOAT((2.0f * float(fHslider4)));
		float fSlow18 = (0.000500000024f * fHbargraph0);
		float fSlow19 = (fConst7 * fSlow2);
		float fSlow20 = max(fSlow2, 23.4489498f);
		float fSlow21 = max(20.0f, fabsf(fSlow20));
		float fSlow22 = (fConst1 / fSlow21);
		float fSlow23 = (fConst0 / fSlow20);
		float fSlow24 = max(0.0f, min(2047.0f, (fConst4 / fSlow20)));
		float fSlow25 = floorf(fSlow24);
		float fSlow26 = (fSlow25 + (1.0f - fSlow24));
		int iSlow27 = int(fSlow24);
		float fSlow28 = (fSlow24 - fSlow25);
		int iSlow29 = (iSlow27 + 1);
		int iSlow30 = int(fSlow14);
		float fSlow31 = (0.00100000005f * float(fHslider5));
		float fSlow32 = float(fButton0);
		int iSlow33 = (fSlow32 > 0.0f);
		int iSlow34 = (iSlow33 > 0);
		float fSlow35 = float(fHslider6);
		float fSlow36 = (fConst0 * fSlow35);
		int iSlow37 = ((fSlow32 == 0.0f) > 0);
		float fSlow38 = float(fHslider7);
		float fSlow39 = (fSlow38 + float(fHslider8));
		float fSlow40 = (fConst0 * fSlow39);
		float fSlow41 = (fConst0 * fSlow38);
		float fSlow42 = float(fHslider9);
		float fSlow43 = (100.0f * (fSlow42 * fSlow32));
		float fSlow44 = (0.0f - (fConst0 * (fSlow38 - fSlow39)));
		float fSlow45 = ((fSlow43 + -1.0f) / fSlow44);
		float fSlow46 = (fConst2 / fSlow38);
		float fSlow47 = (fConst2 / fSlow35);
		float fSlow48 = float(fHslider10);
		float fSlow49 = float(fHslider11);
		float fSlow50 = max((0.5f * fSlow49), 23.4489498f);
		float fSlow51 = max(20.0f, fabsf(fSlow50));
		float fSlow52 = (fConst1 / fSlow51);
		float fSlow53 = (fConst0 / fSlow50);
		float fSlow54 = (fConst3 * fSlow49);
		float fSlow55 = max(0.0f, min(2047.0f, (fConst4 / fSlow50)));
		float fSlow56 = floorf(fSlow55);
		float fSlow57 = (fSlow56 + (1.0f - fSlow55));
		int iSlow58 = int(fSlow55);
		float fSlow59 = (fSlow55 - fSlow56);
		int iSlow60 = (iSlow58 + 1);
		float fSlow61 = (fConst0 / fSlow49);
		int iSlow62 = int((fConst5 / fSlow49));
		float fSlow63 = (fConst6 * fSlow49);
		float fSlow64 = max(fSlow49, 23.4489498f);
		float fSlow65 = max(20.0f, fabsf(fSlow64));
		float fSlow66 = (fConst1 / fSlow65);
		float fSlow67 = (fConst0 / fSlow64);
		float fSlow68 = (fConst7 * fSlow49);
		float fSlow69 = max(0.0f, min(2047.0f, (fConst4 / fSlow64)));
		float fSlow70 = floorf(fSlow69);
		float fSlow71 = (fSlow70 + (1.0f - fSlow69));
		int iSlow72 = int(fSlow69);
		float fSlow73 = (fSlow69 - fSlow70);
		int iSlow74 = (iSlow72 + 1);
		int iSlow75 = int(fSlow61);
		float fSlow76 = float(fButton1);
		int iSlow77 = (fSlow76 > 0.0f);
		int iSlow78 = (iSlow77 > 0);
		int iSlow79 = ((fSlow76 == 0.0f) > 0);
		float fSlow80 = (100.0f * (fSlow42 * fSlow76));
		float fSlow81 = ((fSlow80 + -1.0f) / fSlow44);
		float fSlow82 = float(fHslider12);
		float fSlow83 = float(fHslider13);
		float fSlow84 = max((0.5f * fSlow83), 23.4489498f);
		float fSlow85 = max(20.0f, fabsf(fSlow84));
		float fSlow86 = (fConst1 / fSlow85);
		float fSlow87 = (fConst0 / fSlow84);
		float fSlow88 = (fConst3 * fSlow83);
		float fSlow89 = max(0.0f, min(2047.0f, (fConst4 / fSlow84)));
		float fSlow90 = floorf(fSlow89);
		float fSlow91 = (fSlow90 + (1.0f - fSlow89));
		int iSlow92 = int(fSlow89);
		float fSlow93 = (fSlow89 - fSlow90);
		int iSlow94 = (iSlow92 + 1);
		float fSlow95 = (fConst0 / fSlow83);
		int iSlow96 = int((fConst5 / fSlow83));
		float fSlow97 = (fConst6 * fSlow83);
		float fSlow98 = max(fSlow83, 23.4489498f);
		float fSlow99 = max(20.0f, fabsf(fSlow98));
		float fSlow100 = (fConst1 / fSlow99);
		float fSlow101 = (fConst0 / fSlow98);
		float fSlow102 = (fConst7 * fSlow83);
		float fSlow103 = max(0.0f, min(2047.0f, (fConst4 / fSlow98)));
		float fSlow104 = floorf(fSlow103);
		float fSlow105 = (fSlow104 + (1.0f - fSlow103));
		int iSlow106 = int(fSlow103);
		float fSlow107 = (fSlow103 - fSlow104);
		int iSlow108 = (iSlow106 + 1);
		int iSlow109 = int(fSlow95);
		float fSlow110 = float(fButton2);
		int iSlow111 = (fSlow110 > 0.0f);
		int iSlow112 = (iSlow111 > 0);
		int iSlow113 = ((fSlow110 == 0.0f) > 0);
		float fSlow114 = (100.0f * (fSlow42 * fSlow110));
		float fSlow115 = ((fSlow114 + -1.0f) / fSlow44);
		float fSlow116 = float(fHslider14);
		float fSlow117 = float(fHslider15);
		float fSlow118 = max((0.5f * fSlow117), 23.4489498f);
		float fSlow119 = max(20.0f, fabsf(fSlow118));
		float fSlow120 = (fConst1 / fSlow119);
		float fSlow121 = (fConst0 / fSlow118);
		float fSlow122 = (fConst3 * fSlow117);
		float fSlow123 = max(0.0f, min(2047.0f, (fConst4 / fSlow118)));
		float fSlow124 = floorf(fSlow123);
		float fSlow125 = (fSlow124 + (1.0f - fSlow123));
		int iSlow126 = int(fSlow123);
		float fSlow127 = (fSlow123 - fSlow124);
		int iSlow128 = (iSlow126 + 1);
		float fSlow129 = (fConst0 / fSlow117);
		int iSlow130 = int((fConst5 / fSlow117));
		float fSlow131 = (fConst6 * fSlow117);
		float fSlow132 = max(fSlow117, 23.4489498f);
		float fSlow133 = max(20.0f, fabsf(fSlow132));
		float fSlow134 = (fConst1 / fSlow133);
		float fSlow135 = (fConst0 / fSlow132);
		float fSlow136 = (fConst7 * fSlow117);
		float fSlow137 = max(0.0f, min(2047.0f, (fConst4 / fSlow132)));
		float fSlow138 = floorf(fSlow137);
		float fSlow139 = (fSlow138 + (1.0f - fSlow137));
		int iSlow140 = int(fSlow137);
		float fSlow141 = (fSlow137 - fSlow138);
		int iSlow142 = (iSlow140 + 1);
		int iSlow143 = int(fSlow129);
		float fSlow144 = float(fButton3);
		int iSlow145 = (fSlow144 > 0.0f);
		int iSlow146 = (iSlow145 > 0);
		int iSlow147 = ((fSlow144 == 0.0f) > 0);
		float fSlow148 = (100.0f * (fSlow42 * fSlow144));
		float fSlow149 = ((fSlow148 + -1.0f) / fSlow44);
		float fSlow150 = float(fHslider16);
		float fSlow151 = float(fHslider17);
		float fSlow152 = max((0.5f * fSlow151), 23.4489498f);
		float fSlow153 = max(20.0f, fabsf(fSlow152));
		float fSlow154 = (fConst1 / fSlow153);
		float fSlow155 = (fConst0 / fSlow152);
		float fSlow156 = (fConst3 * fSlow151);
		float fSlow157 = max(0.0f, min(2047.0f, (fConst4 / fSlow152)));
		float fSlow158 = floorf(fSlow157);
		float fSlow159 = (fSlow158 + (1.0f - fSlow157));
		int iSlow160 = int(fSlow157);
		float fSlow161 = (fSlow157 - fSlow158);
		int iSlow162 = (iSlow160 + 1);
		float fSlow163 = (fConst0 / fSlow151);
		int iSlow164 = int((fConst5 / fSlow151));
		float fSlow165 = (fConst6 * fSlow151);
		float fSlow166 = max(fSlow151, 23.4489498f);
		float fSlow167 = max(20.0f, fabsf(fSlow166));
		float fSlow168 = (fConst1 / fSlow167);
		float fSlow169 = (fConst0 / fSlow166);
		float fSlow170 = (fConst7 * fSlow151);
		float fSlow171 = max(0.0f, min(2047.0f, (fConst4 / fSlow166)));
		float fSlow172 = floorf(fSlow171);
		float fSlow173 = (fSlow172 + (1.0f - fSlow171));
		int iSlow174 = int(fSlow171);
		float fSlow175 = (fSlow171 - fSlow172);
		int iSlow176 = (iSlow174 + 1);
		int iSlow177 = int(fSlow163);
		float fSlow178 = float(fButton4);
		int iSlow179 = (fSlow178 > 0.0f);
		int iSlow180 = (iSlow179 > 0);
		int iSlow181 = ((fSlow178 == 0.0f) > 0);
		float fSlow182 = (100.0f * (fSlow42 * fSlow178));
		float fSlow183 = ((fSlow182 + -1.0f) / fSlow44);
		float fSlow184 = float(fHslider18);
		float fSlow185 = float(fHslider19);
		float fSlow186 = max((0.5f * fSlow185), 23.4489498f);
		float fSlow187 = max(20.0f, fabsf(fSlow186));
		float fSlow188 = (fConst1 / fSlow187);
		float fSlow189 = (fConst0 / fSlow186);
		float fSlow190 = (fConst3 * fSlow185);
		float fSlow191 = max(0.0f, min(2047.0f, (fConst4 / fSlow186)));
		float fSlow192 = floorf(fSlow191);
		float fSlow193 = (fSlow192 + (1.0f - fSlow191));
		int iSlow194 = int(fSlow191);
		float fSlow195 = (fSlow191 - fSlow192);
		int iSlow196 = (iSlow194 + 1);
		float fSlow197 = (fConst0 / fSlow185);
		int iSlow198 = int((fConst5 / fSlow185));
		float fSlow199 = (fConst6 * fSlow185);
		float fSlow200 = max(fSlow185, 23.4489498f);
		float fSlow201 = max(20.0f, fabsf(fSlow200));
		float fSlow202 = (fConst1 / fSlow201);
		float fSlow203 = (fConst0 / fSlow200);
		float fSlow204 = (fConst7 * fSlow185);
		float fSlow205 = max(0.0f, min(2047.0f, (fConst4 / fSlow200)));
		float fSlow206 = floorf(fSlow205);
		float fSlow207 = (fSlow206 + (1.0f - fSlow205));
		int iSlow208 = int(fSlow205);
		float fSlow209 = (fSlow205 - fSlow206);
		int iSlow210 = (iSlow208 + 1);
		int iSlow211 = int(fSlow197);
		float fSlow212 = float(fButton5);
		int iSlow213 = (fSlow212 > 0.0f);
		int iSlow214 = (iSlow213 > 0);
		int iSlow215 = ((fSlow212 == 0.0f) > 0);
		float fSlow216 = (100.0f * (fSlow42 * fSlow212));
		float fSlow217 = ((fSlow216 + -1.0f) / fSlow44);
		for (int i = 0; (i < count); i = (i + 1)) {
			iVec0[0] = 1;
			fRec2[0] = (fSlow1 + (0.999000013f * fRec2[1]));
			float fTemp0 = min(1.0f, max(0.0f, (2.0f - fRec2[0])));
			fVec1[0] = 0.25f;
			fVec2[0] = fSlow4;
			float fTemp1 = (fRec3[1] + (fConst2 * fVec2[1]));
			fRec3[0] = (fTemp1 - floorf(fTemp1));
			float fTemp2 = faust_nuke_faustpower2_f(((2.0f * fRec3[0]) + -1.0f));
			fVec3[0] = fTemp2;
			float fTemp3 = (fSlow5 * ((fTemp2 - fVec3[1]) * float(iVec0[1])));
			fVec4[(IOTA & 4095)] = fTemp3;
			float fTemp4 = min(0.5f, (0.5f * fRec2[0]));
			float fTemp5 = max(0.0f, min(2047.0f, (fSlow6 * fTemp4)));
			int iTemp6 = int(fTemp5);
			float fTemp7 = floorf(fTemp5);
			fRec4[0] = ((fTemp3 + (0.999000013f * fRec4[1])) - ((fSlow10 * fVec4[((IOTA - iSlow11) & 4095)]) + (fSlow12 * fVec4[((IOTA - iSlow13) & 4095)])));
			float fTemp8 = min(1.0f, max(0.0f, (fRec2[0] + -2.0f)));
			float fTemp9 = (1.0f - (fTemp0 + fTemp8));
			iRec6[0] = ((iRec6[1] + iVec0[1]) % iSlow15);
			float fTemp10 = (0.100000001f * (max(3.0f, fRec2[0]) + -3.0f));
			float fTemp11 = (fTemp10 + 0.5f);
			float fTemp12 = ((fRec5[1] * float((1 - ((iRec6[0] == 0) > 0)))) + (fSlow16 * fTemp11));
			fRec5[0] = (fTemp12 - floorf(fTemp12));
			float fTemp13 = faust_nuke_faustpower2_f(((2.0f * fRec5[0]) + -1.0f));
			fVec5[0] = fTemp13;
			fRec7[0] = (fSlow17 + (0.999000013f * fRec7[1]));
			float fTemp14 = max(0.0f, (fRec7[0] + -2.0f));
			int iTemp15 = (1 - (fRec7[0] <= 0.00999999978f));
			fRec8[0] = (fSlow18 + (0.999000013f * fRec8[1]));
			int iTemp16 = (fRec8[0] >= 2.0f);
			int iTemp17 = (fRec8[0] >= 3.0f);
			float fTemp18 = (((fRec8[0] == 0.0f) + iTemp17)?1.0f:max(max(1.0f, ((0.0593999997f * (fRec8[0] + -2.0999999f)) + 1.0f)), ((0.0593999997f * (1.0f - fRec8[0])) + 1.0f)));
			float fTemp19 = max((fSlow2 * fTemp18), 23.4489498f);
			float fTemp20 = max(20.0f, fabsf(fTemp19));
			fVec6[0] = fTemp20;
			float fTemp21 = (fRec9[1] + (fConst2 * fVec6[1]));
			fRec9[0] = (fTemp21 - floorf(fTemp21));
			float fTemp22 = faust_nuke_faustpower2_f(((2.0f * fRec9[0]) + -1.0f));
			fVec7[0] = fTemp22;
			float fTemp23 = (((fTemp22 - fVec7[1]) * float(iVec0[1])) / fTemp20);
			fVec8[(IOTA & 4095)] = fTemp23;
			float fTemp24 = max(0.0f, min(2047.0f, (fConst0 * (fTemp4 / fTemp19))));
			int iTemp25 = int(fTemp24);
			float fTemp26 = floorf(fTemp24);
			float fTemp27 = max(0.0f, min(2047.0f, (fConst4 / fTemp19)));
			int iTemp28 = int(fTemp27);
			float fTemp29 = floorf(fTemp27);
			fRec10[0] = ((0.999000013f * fRec10[1]) + (fConst1 * ((fTemp23 - (fVec8[((IOTA - iTemp28) & 4095)] * (fTemp29 + (1.0f - fTemp27)))) - ((fTemp27 - fTemp29) * fVec8[((IOTA - (iTemp28 + 1)) & 4095)]))));
			iRec12[0] = ((iRec12[1] + iVec0[1]) % int((fSlow14 / fTemp18)));
			float fTemp30 = (fTemp18 + fTemp10);
			float fTemp31 = ((fRec11[1] * float((1 - ((iRec12[0] == 0) > 0)))) + (fSlow16 * fTemp30));
			fRec11[0] = (fTemp31 - floorf(fTemp31));
			float fTemp32 = faust_nuke_faustpower2_f(((2.0f * fRec11[0]) + -1.0f));
			fVec9[0] = fTemp32;
			float fTemp33 = (((fConst1 * (fTemp0 * ((fTemp23 - (fVec8[((IOTA - iTemp25) & 4095)] * (fTemp26 + (1.0f - fTemp24)))) - ((fTemp24 - fTemp26) * fVec8[((IOTA - (iTemp25 + 1)) & 4095)])))) + (fSlow19 * ((fRec10[0] * fTemp18) * fTemp9))) + (fSlow14 * (((fTemp8 * (fTemp32 - fVec9[1])) * fVec1[1]) / fTemp30)));
			float fTemp34 = (iTemp17?1.49829996f:1.0f);
			float fTemp35 = (fTemp34 / fTemp18);
			float fTemp36 = max((fSlow2 * fTemp35), 23.4489498f);
			float fTemp37 = max(20.0f, fabsf(fTemp36));
			fVec10[0] = fTemp37;
			float fTemp38 = (fRec13[1] + (fConst2 * fVec10[1]));
			fRec13[0] = (fTemp38 - floorf(fTemp38));
			float fTemp39 = faust_nuke_faustpower2_f(((2.0f * fRec13[0]) + -1.0f));
			fVec11[0] = fTemp39;
			float fTemp40 = (((fTemp39 - fVec11[1]) * float(iVec0[1])) / fTemp37);
			fVec12[(IOTA & 4095)] = fTemp40;
			float fTemp41 = max(0.0f, min(2047.0f, (fConst0 * (fTemp4 / fTemp36))));
			int iTemp42 = int(fTemp41);
			float fTemp43 = floorf(fTemp41);
			float fTemp44 = max(0.0f, min(2047.0f, (fConst4 / fTemp36)));
			int iTemp45 = int(fTemp44);
			float fTemp46 = floorf(fTemp44);
			fRec14[0] = ((0.999000013f * fRec14[1]) + (fConst1 * ((fTemp40 - (fVec12[((IOTA - iTemp45) & 4095)] * (fTemp46 + (1.0f - fTemp44)))) - ((fTemp44 - fTemp46) * fVec12[((IOTA - (iTemp45 + 1)) & 4095)]))));
			float fTemp47 = (fTemp18 / fTemp34);
			iRec16[0] = ((iRec16[1] + iVec0[1]) % int((fSlow14 * fTemp47)));
			float fTemp48 = (fTemp10 + fTemp35);
			float fTemp49 = ((fRec15[1] * float((1 - ((iRec16[0] == 0) > 0)))) + (fSlow16 * fTemp48));
			fRec15[0] = (fTemp49 - floorf(fTemp49));
			float fTemp50 = faust_nuke_faustpower2_f(((2.0f * fRec15[0]) + -1.0f));
			fVec13[0] = fTemp50;
			float fTemp51 = (((fConst1 * (fTemp0 * ((fTemp40 - (fVec12[((IOTA - iTemp42) & 4095)] * (fTemp43 + (1.0f - fTemp41)))) - ((fTemp41 - fTemp43) * fVec12[((IOTA - (iTemp42 + 1)) & 4095)])))) + (fSlow19 * (((fTemp34 * fRec14[0]) * fTemp9) / fTemp18))) + (fSlow14 * (((fTemp8 * (fTemp50 - fVec13[1])) * fVec1[1]) / fTemp48)));
			int iTemp52 = (fRec8[0] < 2.0f);
			float fTemp53 = min(1.0f, max(0.0f, (2.0f - fRec8[0])));
			float fTemp54 = (1.0f - fTemp53);
			float fTemp55 = (float(iTemp15) * fTemp53);
			float fTemp56 = max(0.0f, ((fRec7[0] <= 1.0f)?fRec7[0]:(2.0f - fRec7[0])));
			fVec14[0] = fSlow21;
			float fTemp57 = (fRec17[1] + (fConst2 * fVec14[1]));
			fRec17[0] = (fTemp57 - floorf(fTemp57));
			float fTemp58 = faust_nuke_faustpower2_f(((2.0f * fRec17[0]) + -1.0f));
			fVec15[0] = fTemp58;
			float fTemp59 = (fSlow22 * ((fTemp58 - fVec15[1]) * float(iVec0[1])));
			fVec16[(IOTA & 4095)] = fTemp59;
			float fTemp60 = max(0.0f, min(2047.0f, (fSlow23 * fTemp4)));
			int iTemp61 = int(fTemp60);
			float fTemp62 = floorf(fTemp60);
			fRec18[0] = ((fTemp59 + (0.999000013f * fRec18[1])) - ((fSlow26 * fVec16[((IOTA - iSlow27) & 4095)]) + (fSlow28 * fVec16[((IOTA - iSlow29) & 4095)])));
			iRec20[0] = ((iRec20[1] + iVec0[1]) % iSlow30);
			float fTemp63 = (fTemp10 + 1.0f);
			float fTemp64 = ((fRec19[1] * float((1 - ((iRec20[0] == 0) > 0)))) + (fSlow16 * fTemp63));
			fRec19[0] = (fTemp64 - floorf(fTemp64));
			float fTemp65 = faust_nuke_faustpower2_f(((2.0f * fRec19[0]) + -1.0f));
			fVec17[0] = fTemp65;
			iRec21[0] = ((1103515245 * iRec21[1]) + 12345);
			float fTemp66 = (4.65661287e-10f * (float(iRec21[0]) * max((1.0f - fRec7[0]), 0.0f)));
			fRec22[0] = (fSlow31 + (0.999000013f * fRec22[1]));
			int iTemp67 = int(floorf((0.0404040404f * (fRec22[0] + -1.0f))));
			float fTemp68 = (0.0399999991f * fRec22[0]);
			fHbargraph1 = FAUSTFLOAT((4.5f * ((iTemp67 >= 2)?((iTemp67 >= 3)?(4.0f - fTemp68):(0.0399999991f * (fRec22[0] + -50.0f))):((iTemp67 >= 1)?(2.0f - fTemp68):fTemp68))));
			float fTemp69 = tanf((fConst8 * ((2222.0f * fHbargraph1) + 300.0f)));
			float fTemp70 = (1.0f / fTemp69);
			fRec23[0] = ((0.999000013f * fRec23[1]) + (0.00100000005f * ((0.075000003f * (max(40.0f, min(60.0f, fRec22[0])) + -40.0f)) + 1.0f)));
			float fTemp71 = (1.0f / fRec23[0]);
			float fTemp72 = (((fTemp70 - fTemp71) / fTemp69) + 1.0f);
			float fTemp73 = (1.0f - (1.0f / faust_nuke_faustpower2_f(fTemp69)));
			float fTemp74 = (((fTemp70 + fTemp71) / fTemp69) + 1.0f);
			fRec1[0] = (((((((fTemp0 * (fTemp3 - ((fVec4[((IOTA - iTemp6) & 4095)] * (fTemp7 + (1.0f - fTemp5))) + ((fTemp5 - fTemp7) * fVec4[((IOTA - (iTemp6 + 1)) & 4095)])))) + (fSlow7 * (fRec4[0] * fTemp9))) + (fSlow14 * (((fTemp8 * (fTemp13 - fVec5[1])) * fVec1[1]) / fTemp11))) * fTemp14) + ((float(iTemp15) * ((float(iTemp16) * (fTemp33 + fTemp51)) + ((float(iTemp52) * fTemp33) * (fTemp54 + (fTemp55 * fTemp51))))) + (fTemp56 * (((fTemp0 * (fTemp59 - ((fVec16[((IOTA - iTemp61) & 4095)] * (fTemp62 + (1.0f - fTemp60))) + ((fTemp60 - fTemp62) * fVec16[((IOTA - (iTemp61 + 1)) & 4095)])))) + (fSlow19 * (fRec18[0] * fTemp9))) + (fSlow14 * (((fTemp8 * (fTemp65 - fVec17[1])) * fVec1[1]) / fTemp63)))))) + fTemp66) - (((fRec1[2] * fTemp72) + (2.0f * (fRec1[1] * fTemp73))) / fTemp74));
			fRec0[0] = ((((fRec1[1] + (0.5f * fRec1[0])) + (0.5f * fRec1[2])) - ((fTemp72 * fRec0[2]) + (2.0f * (fTemp73 * fRec0[1])))) / fTemp74);
			fRec24[0] = (iSlow34?0.0f:min(fSlow36, (fRec24[1] + 1.0f)));
			fRec26[0] = (iSlow37?0.0f:min(fSlow40, (fRec26[1] + 1.0f)));
			int iTemp75 = (fRec26[0] < fSlow41);
			fRec25[0] = (iSlow33?(float(iSlow33) * (iTemp75?((fRec26[0] < 0.0f)?0.0f:(iTemp75?(fSlow46 * fRec26[0]):1.0f)):((fRec26[0] < fSlow40)?((fSlow45 * (fRec26[0] - fSlow41)) + 1.0f):fSlow43))):fRec25[1]);
			fVec18[0] = fSlow51;
			float fTemp76 = (fRec29[1] + (fConst2 * fVec18[1]));
			fRec29[0] = (fTemp76 - floorf(fTemp76));
			float fTemp77 = faust_nuke_faustpower2_f(((2.0f * fRec29[0]) + -1.0f));
			fVec19[0] = fTemp77;
			float fTemp78 = (fSlow52 * ((fTemp77 - fVec19[1]) * float(iVec0[1])));
			fVec20[(IOTA & 4095)] = fTemp78;
			float fTemp79 = max(0.0f, min(2047.0f, (fSlow53 * fTemp4)));
			int iTemp80 = int(fTemp79);
			float fTemp81 = floorf(fTemp79);
			fRec30[0] = ((fTemp78 + (0.999000013f * fRec30[1])) - ((fSlow57 * fVec20[((IOTA - iSlow58) & 4095)]) + (fSlow59 * fVec20[((IOTA - iSlow60) & 4095)])));
			iRec32[0] = ((iRec32[1] + iVec0[1]) % iSlow62);
			float fTemp82 = ((fRec31[1] * float((1 - ((iRec32[0] == 0) > 0)))) + (fSlow63 * fTemp11));
			fRec31[0] = (fTemp82 - floorf(fTemp82));
			float fTemp83 = faust_nuke_faustpower2_f(((2.0f * fRec31[0]) + -1.0f));
			fVec21[0] = fTemp83;
			fVec22[0] = fSlow65;
			float fTemp84 = (fRec33[1] + (fConst2 * fVec22[1]));
			fRec33[0] = (fTemp84 - floorf(fTemp84));
			float fTemp85 = faust_nuke_faustpower2_f(((2.0f * fRec33[0]) + -1.0f));
			fVec23[0] = fTemp85;
			float fTemp86 = (fSlow66 * ((fTemp85 - fVec23[1]) * float(iVec0[1])));
			fVec24[(IOTA & 4095)] = fTemp86;
			float fTemp87 = max(0.0f, min(2047.0f, (fSlow67 * fTemp4)));
			int iTemp88 = int(fTemp87);
			float fTemp89 = floorf(fTemp87);
			fRec34[0] = ((fTemp86 + (0.999000013f * fRec34[1])) - ((fSlow71 * fVec24[((IOTA - iSlow72) & 4095)]) + (fSlow73 * fVec24[((IOTA - iSlow74) & 4095)])));
			iRec36[0] = ((iRec36[1] + iVec0[1]) % iSlow75);
			float fTemp90 = ((fRec35[1] * float((1 - ((iRec36[0] == 0) > 0)))) + (fSlow63 * fTemp63));
			fRec35[0] = (fTemp90 - floorf(fTemp90));
			float fTemp91 = faust_nuke_faustpower2_f(((2.0f * fRec35[0]) + -1.0f));
			fVec25[0] = fTemp91;
			float fTemp92 = max((fSlow49 * fTemp18), 23.4489498f);
			float fTemp93 = max(20.0f, fabsf(fTemp92));
			fVec26[0] = fTemp93;
			float fTemp94 = (fRec37[1] + (fConst2 * fVec26[1]));
			fRec37[0] = (fTemp94 - floorf(fTemp94));
			float fTemp95 = faust_nuke_faustpower2_f(((2.0f * fRec37[0]) + -1.0f));
			fVec27[0] = fTemp95;
			float fTemp96 = (((fTemp95 - fVec27[1]) * float(iVec0[1])) / fTemp93);
			fVec28[(IOTA & 4095)] = fTemp96;
			float fTemp97 = max(0.0f, min(2047.0f, (fConst0 * (fTemp4 / fTemp92))));
			int iTemp98 = int(fTemp97);
			float fTemp99 = floorf(fTemp97);
			float fTemp100 = max(0.0f, min(2047.0f, (fConst4 / fTemp92)));
			int iTemp101 = int(fTemp100);
			float fTemp102 = floorf(fTemp100);
			fRec38[0] = ((0.999000013f * fRec38[1]) + (fConst1 * ((fTemp96 - (fVec28[((IOTA - iTemp101) & 4095)] * (fTemp102 + (1.0f - fTemp100)))) - ((fTemp100 - fTemp102) * fVec28[((IOTA - (iTemp101 + 1)) & 4095)]))));
			iRec40[0] = ((iRec40[1] + iVec0[1]) % int((fSlow61 / fTemp18)));
			float fTemp103 = ((fRec39[1] * float((1 - ((iRec40[0] == 0) > 0)))) + (fSlow63 * fTemp30));
			fRec39[0] = (fTemp103 - floorf(fTemp103));
			float fTemp104 = faust_nuke_faustpower2_f(((2.0f * fRec39[0]) + -1.0f));
			fVec29[0] = fTemp104;
			float fTemp105 = (((fConst1 * (fTemp0 * ((fTemp96 - (fVec28[((IOTA - iTemp98) & 4095)] * (fTemp99 + (1.0f - fTemp97)))) - ((fTemp97 - fTemp99) * fVec28[((IOTA - (iTemp98 + 1)) & 4095)])))) + (fSlow68 * ((fRec38[0] * fTemp18) * fTemp9))) + (fSlow61 * (((fTemp8 * (fTemp104 - fVec29[1])) * fVec1[1]) / fTemp30)));
			float fTemp106 = max((fSlow49 * fTemp35), 23.4489498f);
			float fTemp107 = max(20.0f, fabsf(fTemp106));
			fVec30[0] = fTemp107;
			float fTemp108 = (fRec41[1] + (fConst2 * fVec30[1]));
			fRec41[0] = (fTemp108 - floorf(fTemp108));
			float fTemp109 = faust_nuke_faustpower2_f(((2.0f * fRec41[0]) + -1.0f));
			fVec31[0] = fTemp109;
			float fTemp110 = (((fTemp109 - fVec31[1]) * float(iVec0[1])) / fTemp107);
			fVec32[(IOTA & 4095)] = fTemp110;
			float fTemp111 = max(0.0f, min(2047.0f, (fConst0 * (fTemp4 / fTemp106))));
			int iTemp112 = int(fTemp111);
			float fTemp113 = floorf(fTemp111);
			float fTemp114 = max(0.0f, min(2047.0f, (fConst4 / fTemp106)));
			int iTemp115 = int(fTemp114);
			float fTemp116 = floorf(fTemp114);
			fRec42[0] = ((0.999000013f * fRec42[1]) + (fConst1 * ((fTemp110 - (fVec32[((IOTA - iTemp115) & 4095)] * (fTemp116 + (1.0f - fTemp114)))) - ((fTemp114 - fTemp116) * fVec32[((IOTA - (iTemp115 + 1)) & 4095)]))));
			iRec44[0] = ((iRec44[1] + iVec0[1]) % int((fSlow61 * fTemp47)));
			float fTemp117 = ((fRec43[1] * float((1 - ((iRec44[0] == 0) > 0)))) + (fSlow63 * fTemp48));
			fRec43[0] = (fTemp117 - floorf(fTemp117));
			float fTemp118 = faust_nuke_faustpower2_f(((2.0f * fRec43[0]) + -1.0f));
			fVec33[0] = fTemp118;
			float fTemp119 = (((fConst1 * (fTemp0 * ((fTemp110 - (fVec32[((IOTA - iTemp112) & 4095)] * (fTemp113 + (1.0f - fTemp111)))) - ((fTemp111 - fTemp113) * fVec32[((IOTA - (iTemp112 + 1)) & 4095)])))) + (fSlow68 * (((fTemp34 * fRec42[0]) * fTemp9) / fTemp18))) + (fSlow61 * (((fTemp8 * (fTemp118 - fVec33[1])) * fVec1[1]) / fTemp48)));
			fRec28[0] = (((fTemp14 * (((fTemp0 * (fTemp78 - ((fVec20[((IOTA - iTemp80) & 4095)] * (fTemp81 + (1.0f - fTemp79))) + ((fTemp79 - fTemp81) * fVec20[((IOTA - (iTemp80 + 1)) & 4095)])))) + (fSlow54 * (fRec30[0] * fTemp9))) + (fSlow61 * (((fTemp8 * (fTemp83 - fVec21[1])) * fVec1[1]) / fTemp11)))) + ((fTemp56 * (((fTemp0 * (fTemp86 - ((fVec24[((IOTA - iTemp88) & 4095)] * (fTemp89 + (1.0f - fTemp87))) + ((fTemp87 - fTemp89) * fVec24[((IOTA - (iTemp88 + 1)) & 4095)])))) + (fSlow68 * (fRec34[0] * fTemp9))) + (fSlow61 * (((fTemp8 * (fTemp91 - fVec25[1])) * fVec1[1]) / fTemp63)))) + (fTemp66 + (float(iTemp15) * ((float(iTemp16) * (fTemp105 + fTemp119)) + ((float(iTemp52) * fTemp105) * (fTemp54 + (fTemp55 * fTemp119)))))))) - (((fTemp72 * fRec28[2]) + (2.0f * (fTemp73 * fRec28[1]))) / fTemp74));
			fRec27[0] = ((((fRec28[1] + (0.5f * fRec28[0])) + (0.5f * fRec28[2])) - ((fTemp72 * fRec27[2]) + (2.0f * (fTemp73 * fRec27[1])))) / fTemp74);
			fRec45[0] = (iSlow78?0.0f:min(fSlow36, (fRec45[1] + 1.0f)));
			fRec47[0] = (iSlow79?0.0f:min(fSlow40, (fRec47[1] + 1.0f)));
			int iTemp120 = (fRec47[0] < fSlow41);
			fRec46[0] = (iSlow77?(float(iSlow77) * (iTemp120?((fRec47[0] < 0.0f)?0.0f:(iTemp120?(fSlow46 * fRec47[0]):1.0f)):((fRec47[0] < fSlow40)?((fSlow81 * (fRec47[0] - fSlow41)) + 1.0f):fSlow80))):fRec46[1]);
			fVec34[0] = fSlow85;
			float fTemp121 = (fRec50[1] + (fConst2 * fVec34[1]));
			fRec50[0] = (fTemp121 - floorf(fTemp121));
			float fTemp122 = faust_nuke_faustpower2_f(((2.0f * fRec50[0]) + -1.0f));
			fVec35[0] = fTemp122;
			float fTemp123 = (fSlow86 * ((fTemp122 - fVec35[1]) * float(iVec0[1])));
			fVec36[(IOTA & 4095)] = fTemp123;
			float fTemp124 = max(0.0f, min(2047.0f, (fSlow87 * fTemp4)));
			int iTemp125 = int(fTemp124);
			float fTemp126 = floorf(fTemp124);
			fRec51[0] = ((fTemp123 + (0.999000013f * fRec51[1])) - ((fSlow91 * fVec36[((IOTA - iSlow92) & 4095)]) + (fSlow93 * fVec36[((IOTA - iSlow94) & 4095)])));
			iRec53[0] = ((iRec53[1] + iVec0[1]) % iSlow96);
			float fTemp127 = ((fRec52[1] * float((1 - ((iRec53[0] == 0) > 0)))) + (fSlow97 * fTemp11));
			fRec52[0] = (fTemp127 - floorf(fTemp127));
			float fTemp128 = faust_nuke_faustpower2_f(((2.0f * fRec52[0]) + -1.0f));
			fVec37[0] = fTemp128;
			fVec38[0] = fSlow99;
			float fTemp129 = (fRec54[1] + (fConst2 * fVec38[1]));
			fRec54[0] = (fTemp129 - floorf(fTemp129));
			float fTemp130 = faust_nuke_faustpower2_f(((2.0f * fRec54[0]) + -1.0f));
			fVec39[0] = fTemp130;
			float fTemp131 = (fSlow100 * ((fTemp130 - fVec39[1]) * float(iVec0[1])));
			fVec40[(IOTA & 4095)] = fTemp131;
			float fTemp132 = max(0.0f, min(2047.0f, (fSlow101 * fTemp4)));
			int iTemp133 = int(fTemp132);
			float fTemp134 = floorf(fTemp132);
			fRec55[0] = ((fTemp131 + (0.999000013f * fRec55[1])) - ((fSlow105 * fVec40[((IOTA - iSlow106) & 4095)]) + (fSlow107 * fVec40[((IOTA - iSlow108) & 4095)])));
			iRec57[0] = ((iRec57[1] + iVec0[1]) % iSlow109);
			float fTemp135 = ((fRec56[1] * float((1 - ((iRec57[0] == 0) > 0)))) + (fSlow97 * fTemp63));
			fRec56[0] = (fTemp135 - floorf(fTemp135));
			float fTemp136 = faust_nuke_faustpower2_f(((2.0f * fRec56[0]) + -1.0f));
			fVec41[0] = fTemp136;
			float fTemp137 = max((fSlow83 * fTemp18), 23.4489498f);
			float fTemp138 = max(20.0f, fabsf(fTemp137));
			fVec42[0] = fTemp138;
			float fTemp139 = (fRec58[1] + (fConst2 * fVec42[1]));
			fRec58[0] = (fTemp139 - floorf(fTemp139));
			float fTemp140 = faust_nuke_faustpower2_f(((2.0f * fRec58[0]) + -1.0f));
			fVec43[0] = fTemp140;
			float fTemp141 = (((fTemp140 - fVec43[1]) * float(iVec0[1])) / fTemp138);
			fVec44[(IOTA & 4095)] = fTemp141;
			float fTemp142 = max(0.0f, min(2047.0f, (fConst0 * (fTemp4 / fTemp137))));
			int iTemp143 = int(fTemp142);
			float fTemp144 = floorf(fTemp142);
			float fTemp145 = max(0.0f, min(2047.0f, (fConst4 / fTemp137)));
			int iTemp146 = int(fTemp145);
			float fTemp147 = floorf(fTemp145);
			fRec59[0] = ((0.999000013f * fRec59[1]) + (fConst1 * ((fTemp141 - (fVec44[((IOTA - iTemp146) & 4095)] * (fTemp147 + (1.0f - fTemp145)))) - ((fTemp145 - fTemp147) * fVec44[((IOTA - (iTemp146 + 1)) & 4095)]))));
			iRec61[0] = ((iRec61[1] + iVec0[1]) % int((fSlow95 / fTemp18)));
			float fTemp148 = ((fRec60[1] * float((1 - ((iRec61[0] == 0) > 0)))) + (fSlow97 * fTemp30));
			fRec60[0] = (fTemp148 - floorf(fTemp148));
			float fTemp149 = faust_nuke_faustpower2_f(((2.0f * fRec60[0]) + -1.0f));
			fVec45[0] = fTemp149;
			float fTemp150 = (((fConst1 * (fTemp0 * ((fTemp141 - (fVec44[((IOTA - iTemp143) & 4095)] * (fTemp144 + (1.0f - fTemp142)))) - ((fTemp142 - fTemp144) * fVec44[((IOTA - (iTemp143 + 1)) & 4095)])))) + (fSlow102 * ((fRec59[0] * fTemp18) * fTemp9))) + (fSlow95 * (((fTemp8 * (fTemp149 - fVec45[1])) * fVec1[1]) / fTemp30)));
			float fTemp151 = max((fSlow83 * fTemp35), 23.4489498f);
			float fTemp152 = max(20.0f, fabsf(fTemp151));
			fVec46[0] = fTemp152;
			float fTemp153 = (fRec62[1] + (fConst2 * fVec46[1]));
			fRec62[0] = (fTemp153 - floorf(fTemp153));
			float fTemp154 = faust_nuke_faustpower2_f(((2.0f * fRec62[0]) + -1.0f));
			fVec47[0] = fTemp154;
			float fTemp155 = (((fTemp154 - fVec47[1]) * float(iVec0[1])) / fTemp152);
			fVec48[(IOTA & 4095)] = fTemp155;
			float fTemp156 = max(0.0f, min(2047.0f, (fConst0 * (fTemp4 / fTemp151))));
			int iTemp157 = int(fTemp156);
			float fTemp158 = floorf(fTemp156);
			float fTemp159 = max(0.0f, min(2047.0f, (fConst4 / fTemp151)));
			int iTemp160 = int(fTemp159);
			float fTemp161 = floorf(fTemp159);
			fRec63[0] = ((0.999000013f * fRec63[1]) + (fConst1 * ((fTemp155 - (fVec48[((IOTA - iTemp160) & 4095)] * (fTemp161 + (1.0f - fTemp159)))) - ((fTemp159 - fTemp161) * fVec48[((IOTA - (iTemp160 + 1)) & 4095)]))));
			iRec65[0] = ((iRec65[1] + iVec0[1]) % int((fSlow95 * fTemp47)));
			float fTemp162 = ((fRec64[1] * float((1 - ((iRec65[0] == 0) > 0)))) + (fSlow97 * fTemp48));
			fRec64[0] = (fTemp162 - floorf(fTemp162));
			float fTemp163 = faust_nuke_faustpower2_f(((2.0f * fRec64[0]) + -1.0f));
			fVec49[0] = fTemp163;
			float fTemp164 = (((fConst1 * (fTemp0 * ((fTemp155 - (fVec48[((IOTA - iTemp157) & 4095)] * (fTemp158 + (1.0f - fTemp156)))) - ((fTemp156 - fTemp158) * fVec48[((IOTA - (iTemp157 + 1)) & 4095)])))) + (fSlow102 * (((fTemp34 * fRec63[0]) * fTemp9) / fTemp18))) + (fSlow95 * (((fTemp8 * (fTemp163 - fVec49[1])) * fVec1[1]) / fTemp48)));
			fRec49[0] = (((fTemp14 * (((fTemp0 * (fTemp123 - ((fVec36[((IOTA - iTemp125) & 4095)] * (fTemp126 + (1.0f - fTemp124))) + ((fTemp124 - fTemp126) * fVec36[((IOTA - (iTemp125 + 1)) & 4095)])))) + (fSlow88 * (fRec51[0] * fTemp9))) + (fSlow95 * (((fTemp8 * (fTemp128 - fVec37[1])) * fVec1[1]) / fTemp11)))) + ((fTemp56 * (((fTemp0 * (fTemp131 - ((fVec40[((IOTA - iTemp133) & 4095)] * (fTemp134 + (1.0f - fTemp132))) + ((fTemp132 - fTemp134) * fVec40[((IOTA - (iTemp133 + 1)) & 4095)])))) + (fSlow102 * (fRec55[0] * fTemp9))) + (fSlow95 * (((fTemp8 * (fTemp136 - fVec41[1])) * fVec1[1]) / fTemp63)))) + (fTemp66 + (float(iTemp15) * ((float(iTemp16) * (fTemp150 + fTemp164)) + ((float(iTemp52) * fTemp150) * (fTemp54 + (fTemp55 * fTemp164)))))))) - (((fTemp72 * fRec49[2]) + (2.0f * (fTemp73 * fRec49[1]))) / fTemp74));
			fRec48[0] = ((((fRec49[1] + (0.5f * fRec49[0])) + (0.5f * fRec49[2])) - ((fTemp72 * fRec48[2]) + (2.0f * (fTemp73 * fRec48[1])))) / fTemp74);
			fRec66[0] = (iSlow112?0.0f:min(fSlow36, (fRec66[1] + 1.0f)));
			fRec68[0] = (iSlow113?0.0f:min(fSlow40, (fRec68[1] + 1.0f)));
			int iTemp165 = (fRec68[0] < fSlow41);
			fRec67[0] = (iSlow111?(float(iSlow111) * (iTemp165?((fRec68[0] < 0.0f)?0.0f:(iTemp165?(fSlow46 * fRec68[0]):1.0f)):((fRec68[0] < fSlow40)?((fSlow115 * (fRec68[0] - fSlow41)) + 1.0f):fSlow114))):fRec67[1]);
			fVec50[0] = fSlow119;
			float fTemp166 = (fRec71[1] + (fConst2 * fVec50[1]));
			fRec71[0] = (fTemp166 - floorf(fTemp166));
			float fTemp167 = faust_nuke_faustpower2_f(((2.0f * fRec71[0]) + -1.0f));
			fVec51[0] = fTemp167;
			float fTemp168 = (fSlow120 * ((fTemp167 - fVec51[1]) * float(iVec0[1])));
			fVec52[(IOTA & 4095)] = fTemp168;
			float fTemp169 = max(0.0f, min(2047.0f, (fSlow121 * fTemp4)));
			int iTemp170 = int(fTemp169);
			float fTemp171 = floorf(fTemp169);
			fRec72[0] = ((fTemp168 + (0.999000013f * fRec72[1])) - ((fSlow125 * fVec52[((IOTA - iSlow126) & 4095)]) + (fSlow127 * fVec52[((IOTA - iSlow128) & 4095)])));
			iRec74[0] = ((iRec74[1] + iVec0[1]) % iSlow130);
			float fTemp172 = ((fRec73[1] * float((1 - ((iRec74[0] == 0) > 0)))) + (fSlow131 * fTemp11));
			fRec73[0] = (fTemp172 - floorf(fTemp172));
			float fTemp173 = faust_nuke_faustpower2_f(((2.0f * fRec73[0]) + -1.0f));
			fVec53[0] = fTemp173;
			fVec54[0] = fSlow133;
			float fTemp174 = (fRec75[1] + (fConst2 * fVec54[1]));
			fRec75[0] = (fTemp174 - floorf(fTemp174));
			float fTemp175 = faust_nuke_faustpower2_f(((2.0f * fRec75[0]) + -1.0f));
			fVec55[0] = fTemp175;
			float fTemp176 = (fSlow134 * ((fTemp175 - fVec55[1]) * float(iVec0[1])));
			fVec56[(IOTA & 4095)] = fTemp176;
			float fTemp177 = max(0.0f, min(2047.0f, (fSlow135 * fTemp4)));
			int iTemp178 = int(fTemp177);
			float fTemp179 = floorf(fTemp177);
			fRec76[0] = ((fTemp176 + (0.999000013f * fRec76[1])) - ((fSlow139 * fVec56[((IOTA - iSlow140) & 4095)]) + (fSlow141 * fVec56[((IOTA - iSlow142) & 4095)])));
			iRec78[0] = ((iRec78[1] + iVec0[1]) % iSlow143);
			float fTemp180 = ((fRec77[1] * float((1 - ((iRec78[0] == 0) > 0)))) + (fSlow131 * fTemp63));
			fRec77[0] = (fTemp180 - floorf(fTemp180));
			float fTemp181 = faust_nuke_faustpower2_f(((2.0f * fRec77[0]) + -1.0f));
			fVec57[0] = fTemp181;
			float fTemp182 = max((fSlow117 * fTemp18), 23.4489498f);
			float fTemp183 = max(20.0f, fabsf(fTemp182));
			fVec58[0] = fTemp183;
			float fTemp184 = (fRec79[1] + (fConst2 * fVec58[1]));
			fRec79[0] = (fTemp184 - floorf(fTemp184));
			float fTemp185 = faust_nuke_faustpower2_f(((2.0f * fRec79[0]) + -1.0f));
			fVec59[0] = fTemp185;
			float fTemp186 = (((fTemp185 - fVec59[1]) * float(iVec0[1])) / fTemp183);
			fVec60[(IOTA & 4095)] = fTemp186;
			float fTemp187 = max(0.0f, min(2047.0f, (fConst0 * (fTemp4 / fTemp182))));
			int iTemp188 = int(fTemp187);
			float fTemp189 = floorf(fTemp187);
			float fTemp190 = max(0.0f, min(2047.0f, (fConst4 / fTemp182)));
			int iTemp191 = int(fTemp190);
			float fTemp192 = floorf(fTemp190);
			fRec80[0] = ((0.999000013f * fRec80[1]) + (fConst1 * ((fTemp186 - (fVec60[((IOTA - iTemp191) & 4095)] * (fTemp192 + (1.0f - fTemp190)))) - ((fTemp190 - fTemp192) * fVec60[((IOTA - (iTemp191 + 1)) & 4095)]))));
			iRec82[0] = ((iRec82[1] + iVec0[1]) % int((fSlow129 / fTemp18)));
			float fTemp193 = ((fRec81[1] * float((1 - ((iRec82[0] == 0) > 0)))) + (fSlow131 * fTemp30));
			fRec81[0] = (fTemp193 - floorf(fTemp193));
			float fTemp194 = faust_nuke_faustpower2_f(((2.0f * fRec81[0]) + -1.0f));
			fVec61[0] = fTemp194;
			float fTemp195 = (((fConst1 * (fTemp0 * ((fTemp186 - (fVec60[((IOTA - iTemp188) & 4095)] * (fTemp189 + (1.0f - fTemp187)))) - ((fTemp187 - fTemp189) * fVec60[((IOTA - (iTemp188 + 1)) & 4095)])))) + (fSlow136 * ((fRec80[0] * fTemp18) * fTemp9))) + (fSlow129 * (((fTemp8 * (fTemp194 - fVec61[1])) * fVec1[1]) / fTemp30)));
			float fTemp196 = max((fSlow117 * fTemp35), 23.4489498f);
			float fTemp197 = max(20.0f, fabsf(fTemp196));
			fVec62[0] = fTemp197;
			float fTemp198 = (fRec83[1] + (fConst2 * fVec62[1]));
			fRec83[0] = (fTemp198 - floorf(fTemp198));
			float fTemp199 = faust_nuke_faustpower2_f(((2.0f * fRec83[0]) + -1.0f));
			fVec63[0] = fTemp199;
			float fTemp200 = (((fTemp199 - fVec63[1]) * float(iVec0[1])) / fTemp197);
			fVec64[(IOTA & 4095)] = fTemp200;
			float fTemp201 = max(0.0f, min(2047.0f, (fConst0 * (fTemp4 / fTemp196))));
			int iTemp202 = int(fTemp201);
			float fTemp203 = floorf(fTemp201);
			float fTemp204 = max(0.0f, min(2047.0f, (fConst4 / fTemp196)));
			int iTemp205 = int(fTemp204);
			float fTemp206 = floorf(fTemp204);
			fRec84[0] = ((0.999000013f * fRec84[1]) + (fConst1 * ((fTemp200 - (fVec64[((IOTA - iTemp205) & 4095)] * (fTemp206 + (1.0f - fTemp204)))) - ((fTemp204 - fTemp206) * fVec64[((IOTA - (iTemp205 + 1)) & 4095)]))));
			iRec86[0] = ((iRec86[1] + iVec0[1]) % int((fSlow129 * fTemp47)));
			float fTemp207 = ((fRec85[1] * float((1 - ((iRec86[0] == 0) > 0)))) + (fSlow131 * fTemp48));
			fRec85[0] = (fTemp207 - floorf(fTemp207));
			float fTemp208 = faust_nuke_faustpower2_f(((2.0f * fRec85[0]) + -1.0f));
			fVec65[0] = fTemp208;
			float fTemp209 = (((fConst1 * (fTemp0 * ((fTemp200 - (fVec64[((IOTA - iTemp202) & 4095)] * (fTemp203 + (1.0f - fTemp201)))) - ((fTemp201 - fTemp203) * fVec64[((IOTA - (iTemp202 + 1)) & 4095)])))) + (fSlow136 * (((fTemp34 * fRec84[0]) * fTemp9) / fTemp18))) + (fSlow129 * (((fTemp8 * (fTemp208 - fVec65[1])) * fVec1[1]) / fTemp48)));
			fRec70[0] = (((fTemp14 * (((fTemp0 * (fTemp168 - ((fVec52[((IOTA - iTemp170) & 4095)] * (fTemp171 + (1.0f - fTemp169))) + ((fTemp169 - fTemp171) * fVec52[((IOTA - (iTemp170 + 1)) & 4095)])))) + (fSlow122 * (fRec72[0] * fTemp9))) + (fSlow129 * (((fTemp8 * (fTemp173 - fVec53[1])) * fVec1[1]) / fTemp11)))) + ((fTemp56 * (((fTemp0 * (fTemp176 - ((fVec56[((IOTA - iTemp178) & 4095)] * (fTemp179 + (1.0f - fTemp177))) + ((fTemp177 - fTemp179) * fVec56[((IOTA - (iTemp178 + 1)) & 4095)])))) + (fSlow136 * (fRec76[0] * fTemp9))) + (fSlow129 * (((fTemp8 * (fTemp181 - fVec57[1])) * fVec1[1]) / fTemp63)))) + (fTemp66 + (float(iTemp15) * ((float(iTemp16) * (fTemp195 + fTemp209)) + ((float(iTemp52) * fTemp195) * (fTemp54 + (fTemp55 * fTemp209)))))))) - (((fTemp72 * fRec70[2]) + (2.0f * (fTemp73 * fRec70[1]))) / fTemp74));
			fRec69[0] = ((((fRec70[1] + (0.5f * fRec70[0])) + (0.5f * fRec70[2])) - ((fTemp72 * fRec69[2]) + (2.0f * (fTemp73 * fRec69[1])))) / fTemp74);
			fRec87[0] = (iSlow146?0.0f:min(fSlow36, (fRec87[1] + 1.0f)));
			fRec89[0] = (iSlow147?0.0f:min(fSlow40, (fRec89[1] + 1.0f)));
			int iTemp210 = (fRec89[0] < fSlow41);
			fRec88[0] = (iSlow145?(float(iSlow145) * (iTemp210?((fRec89[0] < 0.0f)?0.0f:(iTemp210?(fSlow46 * fRec89[0]):1.0f)):((fRec89[0] < fSlow40)?((fSlow149 * (fRec89[0] - fSlow41)) + 1.0f):fSlow148))):fRec88[1]);
			fVec66[0] = fSlow153;
			float fTemp211 = (fRec92[1] + (fConst2 * fVec66[1]));
			fRec92[0] = (fTemp211 - floorf(fTemp211));
			float fTemp212 = faust_nuke_faustpower2_f(((2.0f * fRec92[0]) + -1.0f));
			fVec67[0] = fTemp212;
			float fTemp213 = (fSlow154 * ((fTemp212 - fVec67[1]) * float(iVec0[1])));
			fVec68[(IOTA & 4095)] = fTemp213;
			float fTemp214 = max(0.0f, min(2047.0f, (fSlow155 * fTemp4)));
			int iTemp215 = int(fTemp214);
			float fTemp216 = floorf(fTemp214);
			fRec93[0] = ((fTemp213 + (0.999000013f * fRec93[1])) - ((fSlow159 * fVec68[((IOTA - iSlow160) & 4095)]) + (fSlow161 * fVec68[((IOTA - iSlow162) & 4095)])));
			iRec95[0] = ((iRec95[1] + iVec0[1]) % iSlow164);
			float fTemp217 = ((fRec94[1] * float((1 - ((iRec95[0] == 0) > 0)))) + (fSlow165 * fTemp11));
			fRec94[0] = (fTemp217 - floorf(fTemp217));
			float fTemp218 = faust_nuke_faustpower2_f(((2.0f * fRec94[0]) + -1.0f));
			fVec69[0] = fTemp218;
			fVec70[0] = fSlow167;
			float fTemp219 = (fRec96[1] + (fConst2 * fVec70[1]));
			fRec96[0] = (fTemp219 - floorf(fTemp219));
			float fTemp220 = faust_nuke_faustpower2_f(((2.0f * fRec96[0]) + -1.0f));
			fVec71[0] = fTemp220;
			float fTemp221 = (fSlow168 * ((fTemp220 - fVec71[1]) * float(iVec0[1])));
			fVec72[(IOTA & 4095)] = fTemp221;
			float fTemp222 = max(0.0f, min(2047.0f, (fSlow169 * fTemp4)));
			int iTemp223 = int(fTemp222);
			float fTemp224 = floorf(fTemp222);
			fRec97[0] = ((fTemp221 + (0.999000013f * fRec97[1])) - ((fSlow173 * fVec72[((IOTA - iSlow174) & 4095)]) + (fSlow175 * fVec72[((IOTA - iSlow176) & 4095)])));
			iRec99[0] = ((iRec99[1] + iVec0[1]) % iSlow177);
			float fTemp225 = ((fRec98[1] * float((1 - ((iRec99[0] == 0) > 0)))) + (fSlow165 * fTemp63));
			fRec98[0] = (fTemp225 - floorf(fTemp225));
			float fTemp226 = faust_nuke_faustpower2_f(((2.0f * fRec98[0]) + -1.0f));
			fVec73[0] = fTemp226;
			float fTemp227 = max((fSlow151 * fTemp18), 23.4489498f);
			float fTemp228 = max(20.0f, fabsf(fTemp227));
			fVec74[0] = fTemp228;
			float fTemp229 = (fRec100[1] + (fConst2 * fVec74[1]));
			fRec100[0] = (fTemp229 - floorf(fTemp229));
			float fTemp230 = faust_nuke_faustpower2_f(((2.0f * fRec100[0]) + -1.0f));
			fVec75[0] = fTemp230;
			float fTemp231 = (((fTemp230 - fVec75[1]) * float(iVec0[1])) / fTemp228);
			fVec76[(IOTA & 4095)] = fTemp231;
			float fTemp232 = max(0.0f, min(2047.0f, (fConst0 * (fTemp4 / fTemp227))));
			int iTemp233 = int(fTemp232);
			float fTemp234 = floorf(fTemp232);
			float fTemp235 = max(0.0f, min(2047.0f, (fConst4 / fTemp227)));
			int iTemp236 = int(fTemp235);
			float fTemp237 = floorf(fTemp235);
			fRec101[0] = ((0.999000013f * fRec101[1]) + (fConst1 * ((fTemp231 - (fVec76[((IOTA - iTemp236) & 4095)] * (fTemp237 + (1.0f - fTemp235)))) - ((fTemp235 - fTemp237) * fVec76[((IOTA - (iTemp236 + 1)) & 4095)]))));
			iRec103[0] = ((iRec103[1] + iVec0[1]) % int((fSlow163 / fTemp18)));
			float fTemp238 = ((fRec102[1] * float((1 - ((iRec103[0] == 0) > 0)))) + (fSlow165 * fTemp30));
			fRec102[0] = (fTemp238 - floorf(fTemp238));
			float fTemp239 = faust_nuke_faustpower2_f(((2.0f * fRec102[0]) + -1.0f));
			fVec77[0] = fTemp239;
			float fTemp240 = (((fConst1 * (fTemp0 * ((fTemp231 - (fVec76[((IOTA - iTemp233) & 4095)] * (fTemp234 + (1.0f - fTemp232)))) - ((fTemp232 - fTemp234) * fVec76[((IOTA - (iTemp233 + 1)) & 4095)])))) + (fSlow170 * ((fRec101[0] * fTemp18) * fTemp9))) + (fSlow163 * (((fTemp8 * (fTemp239 - fVec77[1])) * fVec1[1]) / fTemp30)));
			float fTemp241 = max((fSlow151 * fTemp35), 23.4489498f);
			float fTemp242 = max(20.0f, fabsf(fTemp241));
			fVec78[0] = fTemp242;
			float fTemp243 = (fRec104[1] + (fConst2 * fVec78[1]));
			fRec104[0] = (fTemp243 - floorf(fTemp243));
			float fTemp244 = faust_nuke_faustpower2_f(((2.0f * fRec104[0]) + -1.0f));
			fVec79[0] = fTemp244;
			float fTemp245 = (((fTemp244 - fVec79[1]) * float(iVec0[1])) / fTemp242);
			fVec80[(IOTA & 4095)] = fTemp245;
			float fTemp246 = max(0.0f, min(2047.0f, (fConst0 * (fTemp4 / fTemp241))));
			int iTemp247 = int(fTemp246);
			float fTemp248 = floorf(fTemp246);
			float fTemp249 = max(0.0f, min(2047.0f, (fConst4 / fTemp241)));
			int iTemp250 = int(fTemp249);
			float fTemp251 = floorf(fTemp249);
			fRec105[0] = ((0.999000013f * fRec105[1]) + (fConst1 * ((fTemp245 - (fVec80[((IOTA - iTemp250) & 4095)] * (fTemp251 + (1.0f - fTemp249)))) - ((fTemp249 - fTemp251) * fVec80[((IOTA - (iTemp250 + 1)) & 4095)]))));
			iRec107[0] = ((iRec107[1] + iVec0[1]) % int((fSlow163 * fTemp47)));
			float fTemp252 = ((fRec106[1] * float((1 - ((iRec107[0] == 0) > 0)))) + (fSlow165 * fTemp48));
			fRec106[0] = (fTemp252 - floorf(fTemp252));
			float fTemp253 = faust_nuke_faustpower2_f(((2.0f * fRec106[0]) + -1.0f));
			fVec81[0] = fTemp253;
			float fTemp254 = (((fConst1 * (fTemp0 * ((fTemp245 - (fVec80[((IOTA - iTemp247) & 4095)] * (fTemp248 + (1.0f - fTemp246)))) - ((fTemp246 - fTemp248) * fVec80[((IOTA - (iTemp247 + 1)) & 4095)])))) + (fSlow170 * (((fTemp34 * fRec105[0]) * fTemp9) / fTemp18))) + (fSlow163 * (((fTemp8 * (fTemp253 - fVec81[1])) * fVec1[1]) / fTemp48)));
			fRec91[0] = (((fTemp14 * (((fTemp0 * (fTemp213 - ((fVec68[((IOTA - iTemp215) & 4095)] * (fTemp216 + (1.0f - fTemp214))) + ((fTemp214 - fTemp216) * fVec68[((IOTA - (iTemp215 + 1)) & 4095)])))) + (fSlow156 * (fRec93[0] * fTemp9))) + (fSlow163 * (((fTemp8 * (fTemp218 - fVec69[1])) * fVec1[1]) / fTemp11)))) + ((fTemp56 * (((fTemp0 * (fTemp221 - ((fVec72[((IOTA - iTemp223) & 4095)] * (fTemp224 + (1.0f - fTemp222))) + ((fTemp222 - fTemp224) * fVec72[((IOTA - (iTemp223 + 1)) & 4095)])))) + (fSlow170 * (fRec97[0] * fTemp9))) + (fSlow163 * (((fTemp8 * (fTemp226 - fVec73[1])) * fVec1[1]) / fTemp63)))) + (fTemp66 + (float(iTemp15) * ((float(iTemp16) * (fTemp240 + fTemp254)) + ((float(iTemp52) * fTemp240) * (fTemp54 + (fTemp55 * fTemp254)))))))) - (((fTemp72 * fRec91[2]) + (2.0f * (fTemp73 * fRec91[1]))) / fTemp74));
			fRec90[0] = ((((fRec91[1] + (0.5f * fRec91[0])) + (0.5f * fRec91[2])) - ((fTemp72 * fRec90[2]) + (2.0f * (fTemp73 * fRec90[1])))) / fTemp74);
			fRec108[0] = (iSlow180?0.0f:min(fSlow36, (fRec108[1] + 1.0f)));
			fRec110[0] = (iSlow181?0.0f:min(fSlow40, (fRec110[1] + 1.0f)));
			int iTemp255 = (fRec110[0] < fSlow41);
			fRec109[0] = (iSlow179?(float(iSlow179) * (iTemp255?((fRec110[0] < 0.0f)?0.0f:(iTemp255?(fSlow46 * fRec110[0]):1.0f)):((fRec110[0] < fSlow40)?((fSlow183 * (fRec110[0] - fSlow41)) + 1.0f):fSlow182))):fRec109[1]);
			fVec82[0] = fSlow187;
			float fTemp256 = (fRec113[1] + (fConst2 * fVec82[1]));
			fRec113[0] = (fTemp256 - floorf(fTemp256));
			float fTemp257 = faust_nuke_faustpower2_f(((2.0f * fRec113[0]) + -1.0f));
			fVec83[0] = fTemp257;
			float fTemp258 = (fSlow188 * ((fTemp257 - fVec83[1]) * float(iVec0[1])));
			fVec84[(IOTA & 4095)] = fTemp258;
			float fTemp259 = max(0.0f, min(2047.0f, (fSlow189 * fTemp4)));
			int iTemp260 = int(fTemp259);
			float fTemp261 = floorf(fTemp259);
			fRec114[0] = ((fTemp258 + (0.999000013f * fRec114[1])) - ((fSlow193 * fVec84[((IOTA - iSlow194) & 4095)]) + (fSlow195 * fVec84[((IOTA - iSlow196) & 4095)])));
			iRec116[0] = ((iRec116[1] + iVec0[1]) % iSlow198);
			float fTemp262 = ((fRec115[1] * float((1 - ((iRec116[0] == 0) > 0)))) + (fSlow199 * fTemp11));
			fRec115[0] = (fTemp262 - floorf(fTemp262));
			float fTemp263 = faust_nuke_faustpower2_f(((2.0f * fRec115[0]) + -1.0f));
			fVec85[0] = fTemp263;
			fVec86[0] = fSlow201;
			float fTemp264 = (fRec117[1] + (fConst2 * fVec86[1]));
			fRec117[0] = (fTemp264 - floorf(fTemp264));
			float fTemp265 = faust_nuke_faustpower2_f(((2.0f * fRec117[0]) + -1.0f));
			fVec87[0] = fTemp265;
			float fTemp266 = (fSlow202 * ((fTemp265 - fVec87[1]) * float(iVec0[1])));
			fVec88[(IOTA & 4095)] = fTemp266;
			float fTemp267 = max(0.0f, min(2047.0f, (fSlow203 * fTemp4)));
			int iTemp268 = int(fTemp267);
			float fTemp269 = floorf(fTemp267);
			fRec118[0] = ((fTemp266 + (0.999000013f * fRec118[1])) - ((fSlow207 * fVec88[((IOTA - iSlow208) & 4095)]) + (fSlow209 * fVec88[((IOTA - iSlow210) & 4095)])));
			iRec120[0] = ((iRec120[1] + iVec0[1]) % iSlow211);
			float fTemp270 = ((fRec119[1] * float((1 - ((iRec120[0] == 0) > 0)))) + (fSlow199 * fTemp63));
			fRec119[0] = (fTemp270 - floorf(fTemp270));
			float fTemp271 = faust_nuke_faustpower2_f(((2.0f * fRec119[0]) + -1.0f));
			fVec89[0] = fTemp271;
			float fTemp272 = max((fSlow185 * fTemp18), 23.4489498f);
			float fTemp273 = max(20.0f, fabsf(fTemp272));
			fVec90[0] = fTemp273;
			float fTemp274 = (fRec121[1] + (fConst2 * fVec90[1]));
			fRec121[0] = (fTemp274 - floorf(fTemp274));
			float fTemp275 = faust_nuke_faustpower2_f(((2.0f * fRec121[0]) + -1.0f));
			fVec91[0] = fTemp275;
			float fTemp276 = (((fTemp275 - fVec91[1]) * float(iVec0[1])) / fTemp273);
			fVec92[(IOTA & 4095)] = fTemp276;
			float fTemp277 = max(0.0f, min(2047.0f, (fConst0 * (fTemp4 / fTemp272))));
			int iTemp278 = int(fTemp277);
			float fTemp279 = floorf(fTemp277);
			float fTemp280 = max(0.0f, min(2047.0f, (fConst4 / fTemp272)));
			int iTemp281 = int(fTemp280);
			float fTemp282 = floorf(fTemp280);
			fRec122[0] = ((0.999000013f * fRec122[1]) + (fConst1 * ((fTemp276 - (fVec92[((IOTA - iTemp281) & 4095)] * (fTemp282 + (1.0f - fTemp280)))) - ((fTemp280 - fTemp282) * fVec92[((IOTA - (iTemp281 + 1)) & 4095)]))));
			iRec124[0] = ((iRec124[1] + iVec0[1]) % int((fSlow197 / fTemp18)));
			float fTemp283 = ((fRec123[1] * float((1 - ((iRec124[0] == 0) > 0)))) + (fSlow199 * fTemp30));
			fRec123[0] = (fTemp283 - floorf(fTemp283));
			float fTemp284 = faust_nuke_faustpower2_f(((2.0f * fRec123[0]) + -1.0f));
			fVec93[0] = fTemp284;
			float fTemp285 = (((fConst1 * (fTemp0 * ((fTemp276 - (fVec92[((IOTA - iTemp278) & 4095)] * (fTemp279 + (1.0f - fTemp277)))) - ((fTemp277 - fTemp279) * fVec92[((IOTA - (iTemp278 + 1)) & 4095)])))) + (fSlow204 * ((fRec122[0] * fTemp18) * fTemp9))) + (fSlow197 * (((fTemp8 * (fTemp284 - fVec93[1])) * fVec1[1]) / fTemp30)));
			float fTemp286 = max((fSlow185 * fTemp35), 23.4489498f);
			float fTemp287 = max(20.0f, fabsf(fTemp286));
			fVec94[0] = fTemp287;
			float fTemp288 = (fRec125[1] + (fConst2 * fVec94[1]));
			fRec125[0] = (fTemp288 - floorf(fTemp288));
			float fTemp289 = faust_nuke_faustpower2_f(((2.0f * fRec125[0]) + -1.0f));
			fVec95[0] = fTemp289;
			float fTemp290 = (((fTemp289 - fVec95[1]) * float(iVec0[1])) / fTemp287);
			fVec96[(IOTA & 4095)] = fTemp290;
			float fTemp291 = max(0.0f, min(2047.0f, (fConst0 * (fTemp4 / fTemp286))));
			int iTemp292 = int(fTemp291);
			float fTemp293 = floorf(fTemp291);
			float fTemp294 = max(0.0f, min(2047.0f, (fConst4 / fTemp286)));
			int iTemp295 = int(fTemp294);
			float fTemp296 = floorf(fTemp294);
			fRec126[0] = ((0.999000013f * fRec126[1]) + (fConst1 * ((fTemp290 - (fVec96[((IOTA - iTemp295) & 4095)] * (fTemp296 + (1.0f - fTemp294)))) - ((fTemp294 - fTemp296) * fVec96[((IOTA - (iTemp295 + 1)) & 4095)]))));
			iRec128[0] = ((iRec128[1] + iVec0[1]) % int((fSlow197 * fTemp47)));
			float fTemp297 = ((fRec127[1] * float((1 - ((iRec128[0] == 0) > 0)))) + (fSlow199 * fTemp48));
			fRec127[0] = (fTemp297 - floorf(fTemp297));
			float fTemp298 = faust_nuke_faustpower2_f(((2.0f * fRec127[0]) + -1.0f));
			fVec97[0] = fTemp298;
			float fTemp299 = (((fConst1 * (fTemp0 * ((fTemp290 - (fVec96[((IOTA - iTemp292) & 4095)] * (fTemp293 + (1.0f - fTemp291)))) - ((fTemp291 - fTemp293) * fVec96[((IOTA - (iTemp292 + 1)) & 4095)])))) + (fSlow204 * (((fTemp34 * fRec126[0]) * fTemp9) / fTemp18))) + (fSlow197 * (((fTemp8 * (fTemp298 - fVec97[1])) * fVec1[1]) / fTemp48)));
			fRec112[0] = (((fTemp14 * (((fTemp0 * (fTemp258 - ((fVec84[((IOTA - iTemp260) & 4095)] * (fTemp261 + (1.0f - fTemp259))) + ((fTemp259 - fTemp261) * fVec84[((IOTA - (iTemp260 + 1)) & 4095)])))) + (fSlow190 * (fRec114[0] * fTemp9))) + (fSlow197 * (((fTemp8 * (fTemp263 - fVec85[1])) * fVec1[1]) / fTemp11)))) + ((fTemp56 * (((fTemp0 * (fTemp266 - ((fVec88[((IOTA - iTemp268) & 4095)] * (fTemp269 + (1.0f - fTemp267))) + ((fTemp267 - fTemp269) * fVec88[((IOTA - (iTemp268 + 1)) & 4095)])))) + (fSlow204 * (fRec118[0] * fTemp9))) + (fSlow197 * (((fTemp8 * (fTemp271 - fVec89[1])) * fVec1[1]) / fTemp63)))) + (fTemp66 + (float(iTemp15) * ((float(iTemp16) * (fTemp285 + fTemp299)) + ((float(iTemp52) * fTemp285) * (fTemp54 + (fTemp55 * fTemp299)))))))) - (((fTemp72 * fRec112[2]) + (2.0f * (fTemp73 * fRec112[1]))) / fTemp74));
			fRec111[0] = ((((fRec112[1] + (0.5f * fRec112[0])) + (0.5f * fRec112[2])) - ((fTemp72 * fRec111[2]) + (2.0f * (fTemp73 * fRec111[1])))) / fTemp74);
			fRec129[0] = (iSlow214?0.0f:min(fSlow36, (fRec129[1] + 1.0f)));
			fRec131[0] = (iSlow215?0.0f:min(fSlow40, (fRec131[1] + 1.0f)));
			int iTemp300 = (fRec131[0] < fSlow41);
			fRec130[0] = (iSlow213?(float(iSlow213) * (iTemp300?((fRec131[0] < 0.0f)?0.0f:(iTemp300?(fSlow46 * fRec131[0]):1.0f)):((fRec131[0] < fSlow40)?((fSlow217 * (fRec131[0] - fSlow41)) + 1.0f):fSlow216))):fRec130[1]);
			output0[i] = FAUSTFLOAT((((((((fSlow0 * (((fRec0[1] + (0.5f * fRec0[0])) + (0.5f * fRec0[2])) * ((fRec24[0] < 0.0f)?fRec25[0]:((fRec24[0] < fSlow36)?(fRec25[0] + (fSlow47 * (fRec24[0] * (0.0f - fRec25[0])))):0.0f)))) + (fSlow48 * (((fRec27[1] + (0.5f * fRec27[0])) + (0.5f * fRec27[2])) * ((fRec45[0] < 0.0f)?fRec46[0]:((fRec45[0] < fSlow36)?(fRec46[0] + (fSlow47 * (fRec45[0] * (0.0f - fRec46[0])))):0.0f))))) + (fSlow82 * (((fRec48[1] + (0.5f * fRec48[0])) + (0.5f * fRec48[2])) * ((fRec66[0] < 0.0f)?fRec67[0]:((fRec66[0] < fSlow36)?(fRec67[0] + (fSlow47 * (fRec66[0] * (0.0f - fRec67[0])))):0.0f))))) + (fSlow116 * (((fRec69[1] + (0.5f * fRec69[0])) + (0.5f * fRec69[2])) * ((fRec87[0] < 0.0f)?fRec88[0]:((fRec87[0] < fSlow36)?(fRec88[0] + (fSlow47 * (fRec87[0] * (0.0f - fRec88[0])))):0.0f))))) + (fSlow150 * (((fRec90[1] + (0.5f * fRec90[0])) + (0.5f * fRec90[2])) * ((fRec108[0] < 0.0f)?fRec109[0]:((fRec108[0] < fSlow36)?(fRec109[0] + (fSlow47 * (fRec108[0] * (0.0f - fRec109[0])))):0.0f))))) + (fSlow184 * (((fRec111[1] + (0.5f * fRec111[0])) + (0.5f * fRec111[2])) * ((fRec129[0] < 0.0f)?fRec130[0]:((fRec129[0] < fSlow36)?(fRec130[0] + (fSlow47 * (fRec129[0] * (0.0f - fRec130[0])))):0.0f))))) / fTemp74));
			iVec0[1] = iVec0[0];
			fRec2[1] = fRec2[0];
			fVec1[1] = fVec1[0];
			fVec2[1] = fVec2[0];
			fRec3[1] = fRec3[0];
			fVec3[1] = fVec3[0];
			IOTA = (IOTA + 1);
			fRec4[1] = fRec4[0];
			iRec6[1] = iRec6[0];
			fRec5[1] = fRec5[0];
			fVec5[1] = fVec5[0];
			fRec7[1] = fRec7[0];
			fRec8[1] = fRec8[0];
			fVec6[1] = fVec6[0];
			fRec9[1] = fRec9[0];
			fVec7[1] = fVec7[0];
			fRec10[1] = fRec10[0];
			iRec12[1] = iRec12[0];
			fRec11[1] = fRec11[0];
			fVec9[1] = fVec9[0];
			fVec10[1] = fVec10[0];
			fRec13[1] = fRec13[0];
			fVec11[1] = fVec11[0];
			fRec14[1] = fRec14[0];
			iRec16[1] = iRec16[0];
			fRec15[1] = fRec15[0];
			fVec13[1] = fVec13[0];
			fVec14[1] = fVec14[0];
			fRec17[1] = fRec17[0];
			fVec15[1] = fVec15[0];
			fRec18[1] = fRec18[0];
			iRec20[1] = iRec20[0];
			fRec19[1] = fRec19[0];
			fVec17[1] = fVec17[0];
			iRec21[1] = iRec21[0];
			fRec22[1] = fRec22[0];
			fRec23[1] = fRec23[0];
			fRec1[2] = fRec1[1];
			fRec1[1] = fRec1[0];
			fRec0[2] = fRec0[1];
			fRec0[1] = fRec0[0];
			fRec24[1] = fRec24[0];
			fRec26[1] = fRec26[0];
			fRec25[1] = fRec25[0];
			fVec18[1] = fVec18[0];
			fRec29[1] = fRec29[0];
			fVec19[1] = fVec19[0];
			fRec30[1] = fRec30[0];
			iRec32[1] = iRec32[0];
			fRec31[1] = fRec31[0];
			fVec21[1] = fVec21[0];
			fVec22[1] = fVec22[0];
			fRec33[1] = fRec33[0];
			fVec23[1] = fVec23[0];
			fRec34[1] = fRec34[0];
			iRec36[1] = iRec36[0];
			fRec35[1] = fRec35[0];
			fVec25[1] = fVec25[0];
			fVec26[1] = fVec26[0];
			fRec37[1] = fRec37[0];
			fVec27[1] = fVec27[0];
			fRec38[1] = fRec38[0];
			iRec40[1] = iRec40[0];
			fRec39[1] = fRec39[0];
			fVec29[1] = fVec29[0];
			fVec30[1] = fVec30[0];
			fRec41[1] = fRec41[0];
			fVec31[1] = fVec31[0];
			fRec42[1] = fRec42[0];
			iRec44[1] = iRec44[0];
			fRec43[1] = fRec43[0];
			fVec33[1] = fVec33[0];
			fRec28[2] = fRec28[1];
			fRec28[1] = fRec28[0];
			fRec27[2] = fRec27[1];
			fRec27[1] = fRec27[0];
			fRec45[1] = fRec45[0];
			fRec47[1] = fRec47[0];
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
			fRec66[1] = fRec66[0];
			fRec68[1] = fRec68[0];
			fRec67[1] = fRec67[0];
			fVec50[1] = fVec50[0];
			fRec71[1] = fRec71[0];
			fVec51[1] = fVec51[0];
			fRec72[1] = fRec72[0];
			iRec74[1] = iRec74[0];
			fRec73[1] = fRec73[0];
			fVec53[1] = fVec53[0];
			fVec54[1] = fVec54[0];
			fRec75[1] = fRec75[0];
			fVec55[1] = fVec55[0];
			fRec76[1] = fRec76[0];
			iRec78[1] = iRec78[0];
			fRec77[1] = fRec77[0];
			fVec57[1] = fVec57[0];
			fVec58[1] = fVec58[0];
			fRec79[1] = fRec79[0];
			fVec59[1] = fVec59[0];
			fRec80[1] = fRec80[0];
			iRec82[1] = iRec82[0];
			fRec81[1] = fRec81[0];
			fVec61[1] = fVec61[0];
			fVec62[1] = fVec62[0];
			fRec83[1] = fRec83[0];
			fVec63[1] = fVec63[0];
			fRec84[1] = fRec84[0];
			iRec86[1] = iRec86[0];
			fRec85[1] = fRec85[0];
			fVec65[1] = fVec65[0];
			fRec70[2] = fRec70[1];
			fRec70[1] = fRec70[0];
			fRec69[2] = fRec69[1];
			fRec69[1] = fRec69[0];
			fRec87[1] = fRec87[0];
			fRec89[1] = fRec89[0];
			fRec88[1] = fRec88[0];
			fVec66[1] = fVec66[0];
			fRec92[1] = fRec92[0];
			fVec67[1] = fVec67[0];
			fRec93[1] = fRec93[0];
			iRec95[1] = iRec95[0];
			fRec94[1] = fRec94[0];
			fVec69[1] = fVec69[0];
			fVec70[1] = fVec70[0];
			fRec96[1] = fRec96[0];
			fVec71[1] = fVec71[0];
			fRec97[1] = fRec97[0];
			iRec99[1] = iRec99[0];
			fRec98[1] = fRec98[0];
			fVec73[1] = fVec73[0];
			fVec74[1] = fVec74[0];
			fRec100[1] = fRec100[0];
			fVec75[1] = fVec75[0];
			fRec101[1] = fRec101[0];
			iRec103[1] = iRec103[0];
			fRec102[1] = fRec102[0];
			fVec77[1] = fVec77[0];
			fVec78[1] = fVec78[0];
			fRec104[1] = fRec104[0];
			fVec79[1] = fVec79[0];
			fRec105[1] = fRec105[0];
			iRec107[1] = iRec107[0];
			fRec106[1] = fRec106[0];
			fVec81[1] = fVec81[0];
			fRec91[2] = fRec91[1];
			fRec91[1] = fRec91[0];
			fRec90[2] = fRec90[1];
			fRec90[1] = fRec90[0];
			fRec108[1] = fRec108[0];
			fRec110[1] = fRec110[0];
			fRec109[1] = fRec109[0];
			fVec82[1] = fVec82[0];
			fRec113[1] = fRec113[0];
			fVec83[1] = fVec83[0];
			fRec114[1] = fRec114[0];
			iRec116[1] = iRec116[0];
			fRec115[1] = fRec115[0];
			fVec85[1] = fVec85[0];
			fVec86[1] = fVec86[0];
			fRec117[1] = fRec117[0];
			fVec87[1] = fVec87[0];
			fRec118[1] = fRec118[0];
			iRec120[1] = iRec120[0];
			fRec119[1] = fRec119[0];
			fVec89[1] = fVec89[0];
			fVec90[1] = fVec90[0];
			fRec121[1] = fRec121[0];
			fVec91[1] = fVec91[0];
			fRec122[1] = fRec122[0];
			iRec124[1] = iRec124[0];
			fRec123[1] = fRec123[0];
			fVec93[1] = fVec93[0];
			fVec94[1] = fVec94[0];
			fRec125[1] = fRec125[0];
			fVec95[1] = fVec95[0];
			fRec126[1] = fRec126[0];
			iRec128[1] = iRec128[0];
			fRec127[1] = fRec127[0];
			fVec97[1] = fVec97[0];
			fRec112[2] = fRec112[1];
			fRec112[1] = fRec112[0];
			fRec111[2] = fRec111[1];
			fRec111[1] = fRec111[0];
			fRec129[1] = fRec129[0];
			fRec131[1] = fRec131[0];
			fRec130[1] = fRec130[0];
			
		}
		
	}

	
};

#endif
