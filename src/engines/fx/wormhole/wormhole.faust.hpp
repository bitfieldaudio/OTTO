/* ------------------------------------------------------------
name: "wormhole"
Code generated with Faust 2.5.23 (https://faust.grame.fr)
Compilation options: cpp, -scal -ftz 0
------------------------------------------------------------ */

#ifndef  __faust_wormhole_H__
#define  __faust_wormhole_H__

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

float faust_wormhole_faustpower2_f(float value) {
	return (value * value);
	
}

#ifndef FAUSTCLASS 
#define FAUSTCLASS faust_wormhole
#endif
#ifdef __APPLE__ 
#define exp10f __exp10f
#define exp10 __exp10
#endif

class faust_wormhole : public dsp {
	
 private:
	
	FAUSTFLOAT fHslider0;
	int iVec0[2];
	FAUSTFLOAT fHslider1;
	int fSamplingFreq;
	float fConst0;
	float fConst1;
	FAUSTFLOAT fHslider2;
	float fRec23[2];
	float fRec22[3];
	float fRec21[3];
	int IOTA;
	float fVec1[4096];
	float fConst2;
	float fRec26[2];
	float fRec25[2];
	float fRec24[2];
	float fRec19[2];
	float fVec2[4096];
	float fRec17[2];
	float fVec3[4096];
	float fRec15[2];
	float fVec4[4096];
	float fRec13[2];
	float fVec5[4096];
	float fRec11[2];
	float fVec6[4096];
	float fRec9[2];
	float fVec7[16384];
	float fRec1[2];
	float fRec40[3];
	float fRec39[3];
	float fVec8[4096];
	float fRec37[2];
	float fVec9[4096];
	float fRec35[2];
	float fVec10[4096];
	float fRec33[2];
	float fVec11[4096];
	float fRec31[2];
	float fVec12[4096];
	float fRec29[2];
	float fVec13[4096];
	float fRec27[2];
	float fVec14[16384];
	float fRec2[2];
	float fConst3;
	float fConst4;
	float fConst5;
	float fConst6;
	float fRec55[3];
	float fRec54[3];
	float fVec15[4096];
	float fRec52[2];
	float fVec16[4096];
	float fRec50[2];
	float fVec17[4096];
	float fRec48[2];
	float fVec18[4096];
	float fRec46[2];
	float fVec19[4096];
	float fRec44[2];
	float fVec20[4096];
	float fRec42[2];
	float fVec21[16384];
	float fConst7;
	float fConst8;
	float fRec41[3];
	float fConst9;
	float fRec3[2];
	FAUSTFLOAT fHslider3;
	float fRec69[3];
	float fRec68[3];
	float fVec22[4096];
	float fRec66[2];
	float fVec23[4096];
	float fRec64[2];
	float fVec24[4096];
	float fRec62[2];
	float fVec25[4096];
	float fRec60[2];
	float fVec26[4096];
	float fRec58[2];
	float fVec27[4096];
	float fRec56[2];
	float fVec28[131072];
	float fRec70[2];
	float fRec71[2];
	float fRec4[2];
	float fRec85[3];
	float fRec84[3];
	float fVec29[4096];
	float fRec82[2];
	float fVec30[4096];
	float fRec80[2];
	float fVec31[4096];
	float fRec78[2];
	float fVec32[4096];
	float fRec76[2];
	float fVec33[4096];
	float fRec74[2];
	float fVec34[4096];
	float fRec72[2];
	float fVec35[16384];
	float fRec5[2];
	float fRec99[3];
	float fRec98[3];
	float fVec36[4096];
	float fRec96[2];
	float fVec37[4096];
	float fRec94[2];
	float fVec38[4096];
	float fRec92[2];
	float fVec39[4096];
	float fRec90[2];
	float fVec40[4096];
	float fRec88[2];
	float fVec41[4096];
	float fRec86[2];
	float fVec42[16384];
	float fRec6[2];
	float fRec113[3];
	float fRec112[3];
	float fVec43[4096];
	float fRec110[2];
	float fVec44[4096];
	float fRec108[2];
	float fVec45[4096];
	float fRec106[2];
	float fVec46[4096];
	float fRec104[2];
	float fVec47[4096];
	float fRec102[2];
	float fVec48[4096];
	float fRec100[2];
	float fVec49[16384];
	float fRec7[2];
	float fRec127[3];
	float fRec126[3];
	float fVec50[4096];
	float fRec124[2];
	float fVec51[4096];
	float fRec122[2];
	float fVec52[4096];
	float fRec120[2];
	float fVec53[4096];
	float fRec118[2];
	float fVec54[4096];
	float fRec116[2];
	float fVec55[4096];
	float fRec114[2];
	float fVec56[16384];
	float fRec8[2];
	float fRec0[3];
	float fRec128[3];
	
 public:
	
	void metadata(Meta* m) { 
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.0");
		m->declare("delays.lib/name", "Faust Delay Library");
		m->declare("delays.lib/version", "0.0");
		m->declare("filename", "wormhole");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/version", "0.0");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.1");
		m->declare("misceffects.lib/name", "Faust Math Library");
		m->declare("misceffects.lib/version", "2.0");
		m->declare("name", "wormhole");
		m->declare("oscillators.lib/name", "Faust Oscillator Library");
		m->declare("oscillators.lib/version", "0.0");
		m->declare("routes.lib/name", "Faust Signal Routing Library");
		m->declare("routes.lib/version", "0.0");
		m->declare("signals.lib/name", "Faust Signal Routing Library");
		m->declare("signals.lib/version", "0.0");
	}

	virtual int getNumInputs() {
		return 2;
		
	}
	virtual int getNumOutputs() {
		return 2;
		
	}
	virtual int getInputRate(int channel) {
		int rate;
		switch (channel) {
			case 0: {
				rate = 1;
				break;
			}
			case 1: {
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
	virtual int getOutputRate(int channel) {
		int rate;
		switch (channel) {
			case 0: {
				rate = 1;
				break;
			}
			case 1: {
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
		fConst1 = (3.14159274f / fConst0);
		fConst2 = (1.57079637f / fConst0);
		fConst3 = tanf((314.159271f / fConst0));
		fConst4 = (1.0f / fConst3);
		fConst5 = (1.0f / (((fConst4 + 1.41421354f) / fConst3) + 1.0f));
		fConst6 = (1.0f / faust_wormhole_faustpower2_f(fConst3));
		fConst7 = (((fConst4 + -1.41421354f) / fConst3) + 1.0f);
		fConst8 = (2.0f * (1.0f - fConst6));
		fConst9 = (2.0f * (0.0f - fConst6));
		
	}
	
	virtual void instanceResetUserInterface() {
		fHslider0 = FAUSTFLOAT(0.5f);
		fHslider1 = FAUSTFLOAT(0.5f);
		fHslider2 = FAUSTFLOAT(4000.0f);
		fHslider3 = FAUSTFLOAT(0.0f);
		
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			iVec0[l0] = 0;
			
		}
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			fRec23[l1] = 0.0f;
			
		}
		for (int l2 = 0; (l2 < 3); l2 = (l2 + 1)) {
			fRec22[l2] = 0.0f;
			
		}
		for (int l3 = 0; (l3 < 3); l3 = (l3 + 1)) {
			fRec21[l3] = 0.0f;
			
		}
		IOTA = 0;
		for (int l4 = 0; (l4 < 4096); l4 = (l4 + 1)) {
			fVec1[l4] = 0.0f;
			
		}
		for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			fRec26[l5] = 0.0f;
			
		}
		for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			fRec25[l6] = 0.0f;
			
		}
		for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			fRec24[l7] = 0.0f;
			
		}
		for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			fRec19[l8] = 0.0f;
			
		}
		for (int l9 = 0; (l9 < 4096); l9 = (l9 + 1)) {
			fVec2[l9] = 0.0f;
			
		}
		for (int l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
			fRec17[l10] = 0.0f;
			
		}
		for (int l11 = 0; (l11 < 4096); l11 = (l11 + 1)) {
			fVec3[l11] = 0.0f;
			
		}
		for (int l12 = 0; (l12 < 2); l12 = (l12 + 1)) {
			fRec15[l12] = 0.0f;
			
		}
		for (int l13 = 0; (l13 < 4096); l13 = (l13 + 1)) {
			fVec4[l13] = 0.0f;
			
		}
		for (int l14 = 0; (l14 < 2); l14 = (l14 + 1)) {
			fRec13[l14] = 0.0f;
			
		}
		for (int l15 = 0; (l15 < 4096); l15 = (l15 + 1)) {
			fVec5[l15] = 0.0f;
			
		}
		for (int l16 = 0; (l16 < 2); l16 = (l16 + 1)) {
			fRec11[l16] = 0.0f;
			
		}
		for (int l17 = 0; (l17 < 4096); l17 = (l17 + 1)) {
			fVec6[l17] = 0.0f;
			
		}
		for (int l18 = 0; (l18 < 2); l18 = (l18 + 1)) {
			fRec9[l18] = 0.0f;
			
		}
		for (int l19 = 0; (l19 < 16384); l19 = (l19 + 1)) {
			fVec7[l19] = 0.0f;
			
		}
		for (int l20 = 0; (l20 < 2); l20 = (l20 + 1)) {
			fRec1[l20] = 0.0f;
			
		}
		for (int l21 = 0; (l21 < 3); l21 = (l21 + 1)) {
			fRec40[l21] = 0.0f;
			
		}
		for (int l22 = 0; (l22 < 3); l22 = (l22 + 1)) {
			fRec39[l22] = 0.0f;
			
		}
		for (int l23 = 0; (l23 < 4096); l23 = (l23 + 1)) {
			fVec8[l23] = 0.0f;
			
		}
		for (int l24 = 0; (l24 < 2); l24 = (l24 + 1)) {
			fRec37[l24] = 0.0f;
			
		}
		for (int l25 = 0; (l25 < 4096); l25 = (l25 + 1)) {
			fVec9[l25] = 0.0f;
			
		}
		for (int l26 = 0; (l26 < 2); l26 = (l26 + 1)) {
			fRec35[l26] = 0.0f;
			
		}
		for (int l27 = 0; (l27 < 4096); l27 = (l27 + 1)) {
			fVec10[l27] = 0.0f;
			
		}
		for (int l28 = 0; (l28 < 2); l28 = (l28 + 1)) {
			fRec33[l28] = 0.0f;
			
		}
		for (int l29 = 0; (l29 < 4096); l29 = (l29 + 1)) {
			fVec11[l29] = 0.0f;
			
		}
		for (int l30 = 0; (l30 < 2); l30 = (l30 + 1)) {
			fRec31[l30] = 0.0f;
			
		}
		for (int l31 = 0; (l31 < 4096); l31 = (l31 + 1)) {
			fVec12[l31] = 0.0f;
			
		}
		for (int l32 = 0; (l32 < 2); l32 = (l32 + 1)) {
			fRec29[l32] = 0.0f;
			
		}
		for (int l33 = 0; (l33 < 4096); l33 = (l33 + 1)) {
			fVec13[l33] = 0.0f;
			
		}
		for (int l34 = 0; (l34 < 2); l34 = (l34 + 1)) {
			fRec27[l34] = 0.0f;
			
		}
		for (int l35 = 0; (l35 < 16384); l35 = (l35 + 1)) {
			fVec14[l35] = 0.0f;
			
		}
		for (int l36 = 0; (l36 < 2); l36 = (l36 + 1)) {
			fRec2[l36] = 0.0f;
			
		}
		for (int l37 = 0; (l37 < 3); l37 = (l37 + 1)) {
			fRec55[l37] = 0.0f;
			
		}
		for (int l38 = 0; (l38 < 3); l38 = (l38 + 1)) {
			fRec54[l38] = 0.0f;
			
		}
		for (int l39 = 0; (l39 < 4096); l39 = (l39 + 1)) {
			fVec15[l39] = 0.0f;
			
		}
		for (int l40 = 0; (l40 < 2); l40 = (l40 + 1)) {
			fRec52[l40] = 0.0f;
			
		}
		for (int l41 = 0; (l41 < 4096); l41 = (l41 + 1)) {
			fVec16[l41] = 0.0f;
			
		}
		for (int l42 = 0; (l42 < 2); l42 = (l42 + 1)) {
			fRec50[l42] = 0.0f;
			
		}
		for (int l43 = 0; (l43 < 4096); l43 = (l43 + 1)) {
			fVec17[l43] = 0.0f;
			
		}
		for (int l44 = 0; (l44 < 2); l44 = (l44 + 1)) {
			fRec48[l44] = 0.0f;
			
		}
		for (int l45 = 0; (l45 < 4096); l45 = (l45 + 1)) {
			fVec18[l45] = 0.0f;
			
		}
		for (int l46 = 0; (l46 < 2); l46 = (l46 + 1)) {
			fRec46[l46] = 0.0f;
			
		}
		for (int l47 = 0; (l47 < 4096); l47 = (l47 + 1)) {
			fVec19[l47] = 0.0f;
			
		}
		for (int l48 = 0; (l48 < 2); l48 = (l48 + 1)) {
			fRec44[l48] = 0.0f;
			
		}
		for (int l49 = 0; (l49 < 4096); l49 = (l49 + 1)) {
			fVec20[l49] = 0.0f;
			
		}
		for (int l50 = 0; (l50 < 2); l50 = (l50 + 1)) {
			fRec42[l50] = 0.0f;
			
		}
		for (int l51 = 0; (l51 < 16384); l51 = (l51 + 1)) {
			fVec21[l51] = 0.0f;
			
		}
		for (int l52 = 0; (l52 < 3); l52 = (l52 + 1)) {
			fRec41[l52] = 0.0f;
			
		}
		for (int l53 = 0; (l53 < 2); l53 = (l53 + 1)) {
			fRec3[l53] = 0.0f;
			
		}
		for (int l54 = 0; (l54 < 3); l54 = (l54 + 1)) {
			fRec69[l54] = 0.0f;
			
		}
		for (int l55 = 0; (l55 < 3); l55 = (l55 + 1)) {
			fRec68[l55] = 0.0f;
			
		}
		for (int l56 = 0; (l56 < 4096); l56 = (l56 + 1)) {
			fVec22[l56] = 0.0f;
			
		}
		for (int l57 = 0; (l57 < 2); l57 = (l57 + 1)) {
			fRec66[l57] = 0.0f;
			
		}
		for (int l58 = 0; (l58 < 4096); l58 = (l58 + 1)) {
			fVec23[l58] = 0.0f;
			
		}
		for (int l59 = 0; (l59 < 2); l59 = (l59 + 1)) {
			fRec64[l59] = 0.0f;
			
		}
		for (int l60 = 0; (l60 < 4096); l60 = (l60 + 1)) {
			fVec24[l60] = 0.0f;
			
		}
		for (int l61 = 0; (l61 < 2); l61 = (l61 + 1)) {
			fRec62[l61] = 0.0f;
			
		}
		for (int l62 = 0; (l62 < 4096); l62 = (l62 + 1)) {
			fVec25[l62] = 0.0f;
			
		}
		for (int l63 = 0; (l63 < 2); l63 = (l63 + 1)) {
			fRec60[l63] = 0.0f;
			
		}
		for (int l64 = 0; (l64 < 4096); l64 = (l64 + 1)) {
			fVec26[l64] = 0.0f;
			
		}
		for (int l65 = 0; (l65 < 2); l65 = (l65 + 1)) {
			fRec58[l65] = 0.0f;
			
		}
		for (int l66 = 0; (l66 < 4096); l66 = (l66 + 1)) {
			fVec27[l66] = 0.0f;
			
		}
		for (int l67 = 0; (l67 < 2); l67 = (l67 + 1)) {
			fRec56[l67] = 0.0f;
			
		}
		for (int l68 = 0; (l68 < 131072); l68 = (l68 + 1)) {
			fVec28[l68] = 0.0f;
			
		}
		for (int l69 = 0; (l69 < 2); l69 = (l69 + 1)) {
			fRec70[l69] = 0.0f;
			
		}
		for (int l70 = 0; (l70 < 2); l70 = (l70 + 1)) {
			fRec71[l70] = 0.0f;
			
		}
		for (int l71 = 0; (l71 < 2); l71 = (l71 + 1)) {
			fRec4[l71] = 0.0f;
			
		}
		for (int l72 = 0; (l72 < 3); l72 = (l72 + 1)) {
			fRec85[l72] = 0.0f;
			
		}
		for (int l73 = 0; (l73 < 3); l73 = (l73 + 1)) {
			fRec84[l73] = 0.0f;
			
		}
		for (int l74 = 0; (l74 < 4096); l74 = (l74 + 1)) {
			fVec29[l74] = 0.0f;
			
		}
		for (int l75 = 0; (l75 < 2); l75 = (l75 + 1)) {
			fRec82[l75] = 0.0f;
			
		}
		for (int l76 = 0; (l76 < 4096); l76 = (l76 + 1)) {
			fVec30[l76] = 0.0f;
			
		}
		for (int l77 = 0; (l77 < 2); l77 = (l77 + 1)) {
			fRec80[l77] = 0.0f;
			
		}
		for (int l78 = 0; (l78 < 4096); l78 = (l78 + 1)) {
			fVec31[l78] = 0.0f;
			
		}
		for (int l79 = 0; (l79 < 2); l79 = (l79 + 1)) {
			fRec78[l79] = 0.0f;
			
		}
		for (int l80 = 0; (l80 < 4096); l80 = (l80 + 1)) {
			fVec32[l80] = 0.0f;
			
		}
		for (int l81 = 0; (l81 < 2); l81 = (l81 + 1)) {
			fRec76[l81] = 0.0f;
			
		}
		for (int l82 = 0; (l82 < 4096); l82 = (l82 + 1)) {
			fVec33[l82] = 0.0f;
			
		}
		for (int l83 = 0; (l83 < 2); l83 = (l83 + 1)) {
			fRec74[l83] = 0.0f;
			
		}
		for (int l84 = 0; (l84 < 4096); l84 = (l84 + 1)) {
			fVec34[l84] = 0.0f;
			
		}
		for (int l85 = 0; (l85 < 2); l85 = (l85 + 1)) {
			fRec72[l85] = 0.0f;
			
		}
		for (int l86 = 0; (l86 < 16384); l86 = (l86 + 1)) {
			fVec35[l86] = 0.0f;
			
		}
		for (int l87 = 0; (l87 < 2); l87 = (l87 + 1)) {
			fRec5[l87] = 0.0f;
			
		}
		for (int l88 = 0; (l88 < 3); l88 = (l88 + 1)) {
			fRec99[l88] = 0.0f;
			
		}
		for (int l89 = 0; (l89 < 3); l89 = (l89 + 1)) {
			fRec98[l89] = 0.0f;
			
		}
		for (int l90 = 0; (l90 < 4096); l90 = (l90 + 1)) {
			fVec36[l90] = 0.0f;
			
		}
		for (int l91 = 0; (l91 < 2); l91 = (l91 + 1)) {
			fRec96[l91] = 0.0f;
			
		}
		for (int l92 = 0; (l92 < 4096); l92 = (l92 + 1)) {
			fVec37[l92] = 0.0f;
			
		}
		for (int l93 = 0; (l93 < 2); l93 = (l93 + 1)) {
			fRec94[l93] = 0.0f;
			
		}
		for (int l94 = 0; (l94 < 4096); l94 = (l94 + 1)) {
			fVec38[l94] = 0.0f;
			
		}
		for (int l95 = 0; (l95 < 2); l95 = (l95 + 1)) {
			fRec92[l95] = 0.0f;
			
		}
		for (int l96 = 0; (l96 < 4096); l96 = (l96 + 1)) {
			fVec39[l96] = 0.0f;
			
		}
		for (int l97 = 0; (l97 < 2); l97 = (l97 + 1)) {
			fRec90[l97] = 0.0f;
			
		}
		for (int l98 = 0; (l98 < 4096); l98 = (l98 + 1)) {
			fVec40[l98] = 0.0f;
			
		}
		for (int l99 = 0; (l99 < 2); l99 = (l99 + 1)) {
			fRec88[l99] = 0.0f;
			
		}
		for (int l100 = 0; (l100 < 4096); l100 = (l100 + 1)) {
			fVec41[l100] = 0.0f;
			
		}
		for (int l101 = 0; (l101 < 2); l101 = (l101 + 1)) {
			fRec86[l101] = 0.0f;
			
		}
		for (int l102 = 0; (l102 < 16384); l102 = (l102 + 1)) {
			fVec42[l102] = 0.0f;
			
		}
		for (int l103 = 0; (l103 < 2); l103 = (l103 + 1)) {
			fRec6[l103] = 0.0f;
			
		}
		for (int l104 = 0; (l104 < 3); l104 = (l104 + 1)) {
			fRec113[l104] = 0.0f;
			
		}
		for (int l105 = 0; (l105 < 3); l105 = (l105 + 1)) {
			fRec112[l105] = 0.0f;
			
		}
		for (int l106 = 0; (l106 < 4096); l106 = (l106 + 1)) {
			fVec43[l106] = 0.0f;
			
		}
		for (int l107 = 0; (l107 < 2); l107 = (l107 + 1)) {
			fRec110[l107] = 0.0f;
			
		}
		for (int l108 = 0; (l108 < 4096); l108 = (l108 + 1)) {
			fVec44[l108] = 0.0f;
			
		}
		for (int l109 = 0; (l109 < 2); l109 = (l109 + 1)) {
			fRec108[l109] = 0.0f;
			
		}
		for (int l110 = 0; (l110 < 4096); l110 = (l110 + 1)) {
			fVec45[l110] = 0.0f;
			
		}
		for (int l111 = 0; (l111 < 2); l111 = (l111 + 1)) {
			fRec106[l111] = 0.0f;
			
		}
		for (int l112 = 0; (l112 < 4096); l112 = (l112 + 1)) {
			fVec46[l112] = 0.0f;
			
		}
		for (int l113 = 0; (l113 < 2); l113 = (l113 + 1)) {
			fRec104[l113] = 0.0f;
			
		}
		for (int l114 = 0; (l114 < 4096); l114 = (l114 + 1)) {
			fVec47[l114] = 0.0f;
			
		}
		for (int l115 = 0; (l115 < 2); l115 = (l115 + 1)) {
			fRec102[l115] = 0.0f;
			
		}
		for (int l116 = 0; (l116 < 4096); l116 = (l116 + 1)) {
			fVec48[l116] = 0.0f;
			
		}
		for (int l117 = 0; (l117 < 2); l117 = (l117 + 1)) {
			fRec100[l117] = 0.0f;
			
		}
		for (int l118 = 0; (l118 < 16384); l118 = (l118 + 1)) {
			fVec49[l118] = 0.0f;
			
		}
		for (int l119 = 0; (l119 < 2); l119 = (l119 + 1)) {
			fRec7[l119] = 0.0f;
			
		}
		for (int l120 = 0; (l120 < 3); l120 = (l120 + 1)) {
			fRec127[l120] = 0.0f;
			
		}
		for (int l121 = 0; (l121 < 3); l121 = (l121 + 1)) {
			fRec126[l121] = 0.0f;
			
		}
		for (int l122 = 0; (l122 < 4096); l122 = (l122 + 1)) {
			fVec50[l122] = 0.0f;
			
		}
		for (int l123 = 0; (l123 < 2); l123 = (l123 + 1)) {
			fRec124[l123] = 0.0f;
			
		}
		for (int l124 = 0; (l124 < 4096); l124 = (l124 + 1)) {
			fVec51[l124] = 0.0f;
			
		}
		for (int l125 = 0; (l125 < 2); l125 = (l125 + 1)) {
			fRec122[l125] = 0.0f;
			
		}
		for (int l126 = 0; (l126 < 4096); l126 = (l126 + 1)) {
			fVec52[l126] = 0.0f;
			
		}
		for (int l127 = 0; (l127 < 2); l127 = (l127 + 1)) {
			fRec120[l127] = 0.0f;
			
		}
		for (int l128 = 0; (l128 < 4096); l128 = (l128 + 1)) {
			fVec53[l128] = 0.0f;
			
		}
		for (int l129 = 0; (l129 < 2); l129 = (l129 + 1)) {
			fRec118[l129] = 0.0f;
			
		}
		for (int l130 = 0; (l130 < 4096); l130 = (l130 + 1)) {
			fVec54[l130] = 0.0f;
			
		}
		for (int l131 = 0; (l131 < 2); l131 = (l131 + 1)) {
			fRec116[l131] = 0.0f;
			
		}
		for (int l132 = 0; (l132 < 4096); l132 = (l132 + 1)) {
			fVec55[l132] = 0.0f;
			
		}
		for (int l133 = 0; (l133 < 2); l133 = (l133 + 1)) {
			fRec114[l133] = 0.0f;
			
		}
		for (int l134 = 0; (l134 < 16384); l134 = (l134 + 1)) {
			fVec56[l134] = 0.0f;
			
		}
		for (int l135 = 0; (l135 < 2); l135 = (l135 + 1)) {
			fRec8[l135] = 0.0f;
			
		}
		for (int l136 = 0; (l136 < 3); l136 = (l136 + 1)) {
			fRec0[l136] = 0.0f;
			
		}
		for (int l137 = 0; (l137 < 3); l137 = (l137 + 1)) {
			fRec128[l137] = 0.0f;
			
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
	
	virtual faust_wormhole* clone() {
		return new faust_wormhole();
	}
	virtual int getSampleRate() {
		return fSamplingFreq;
		
	}
	
	virtual void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("wormhole");
		ui_interface->addHorizontalSlider("LENGTH", &fHslider1, 0.5f, 0.0500000007f, 1.0f, 0.00999999978f);
		ui_interface->addHorizontalSlider("MIX", &fHslider0, 0.5f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface->declare(&fHslider2, "scale", "log");
		ui_interface->addHorizontalSlider("SHAPE", &fHslider2, 4000.0f, 100.0f, 14000.0f, 0.00999999978f);
		ui_interface->addHorizontalSlider("SHIMMER", &fHslider3, 0.0f, 0.0f, 1.20000005f, 0.00999999978f);
		ui_interface->closeBox();
		
	}
	
	virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* input1 = inputs[1];
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		float fSlow0 = float(fHslider0);
		float fSlow1 = (0.5f * (float(fHslider1) + 1.0f));
		float fSlow2 = (0.00100000005f * float(fHslider2));
		float fSlow3 = float(fHslider3);
		float fSlow4 = (1.0f - fSlow3);
		float fSlow5 = (2.0f * (1.0f - fSlow0));
		for (int i = 0; (i < count); i = (i + 1)) {
			iVec0[0] = 1;
			float fTemp0 = (fRec1[1] + fRec5[1]);
			float fTemp1 = (fRec7[1] + (fTemp0 + fRec3[1]));
			fRec23[0] = (fSlow2 + (0.999000013f * fRec23[1]));
			float fTemp2 = tanf((fConst1 * fRec23[0]));
			float fTemp3 = (1.0f / fTemp2);
			float fTemp4 = (((fTemp3 + -1.84775901f) / fTemp2) + 1.0f);
			float fTemp5 = (1.0f - (1.0f / faust_wormhole_faustpower2_f(fTemp2)));
			float fTemp6 = (((fTemp3 + 1.84775901f) / fTemp2) + 1.0f);
			fRec22[0] = ((fSlow1 * (fRec8[1] + (fRec4[1] + (fRec6[1] + (fTemp1 + fRec2[1]))))) - (((fRec22[2] * fTemp4) + (2.0f * (fRec22[1] * fTemp5))) / fTemp6));
			float fTemp7 = (((fTemp3 + -0.765366852f) / fTemp2) + 1.0f);
			float fTemp8 = (((fTemp3 + 0.765366852f) / fTemp2) + 1.0f);
			fRec21[0] = (((fRec22[2] + (fRec22[0] + (2.0f * fRec22[1]))) / fTemp6) - (((fRec21[2] * fTemp7) + (2.0f * (fTemp5 * fRec21[1]))) / fTemp8));
			float fTemp9 = float(input1[i]);
			float fTemp10 = float(input0[i]);
			float fTemp11 = ((((0.600000024f * fRec19[1]) + ((fRec21[2] + (fRec21[0] + (2.0f * fRec21[1]))) / fTemp8)) + fTemp9) + fTemp10);
			fVec1[(IOTA & 4095)] = fTemp11;
			fRec26[0] = (fRec26[1] + (fConst2 * (0.0f - fRec24[1])));
			fRec25[0] = ((fRec25[1] + (fConst2 * fRec26[0])) + float((1 - iVec0[1])));
			fRec24[0] = fRec25[0];
			float fTemp12 = ((0.00100000005f * fRec24[0]) + 1.0f);
			float fTemp13 = (343.0f * fTemp12);
			float fTemp14 = (fTemp13 + -1.0f);
			int iTemp15 = int(fTemp14);
			int iTemp16 = min(2049, max(0, iTemp15));
			float fTemp17 = floorf(fTemp14);
			float fTemp18 = (fTemp17 + (2.0f - fTemp13));
			float fTemp19 = (fTemp13 + (-1.0f - fTemp17));
			int iTemp20 = min(2049, max(0, (iTemp15 + 1)));
			fRec19[0] = ((fVec1[((IOTA - iTemp16) & 4095)] * fTemp18) + (fTemp19 * fVec1[((IOTA - iTemp20) & 4095)]));
			float fRec20 = (0.0f - (0.600000024f * fTemp11));
			float fTemp21 = (fRec19[1] + (fRec20 + (0.600000024f * fRec17[1])));
			fVec2[(IOTA & 4095)] = fTemp21;
			float fTemp22 = (441.0f * fTemp12);
			float fTemp23 = (fTemp22 + -1.0f);
			int iTemp24 = int(fTemp23);
			int iTemp25 = min(2049, max(0, iTemp24));
			float fTemp26 = floorf(fTemp23);
			float fTemp27 = (fTemp26 + (2.0f - fTemp22));
			float fTemp28 = (fTemp22 + (-1.0f - fTemp26));
			int iTemp29 = min(2049, max(0, (iTemp24 + 1)));
			fRec17[0] = ((fVec2[((IOTA - iTemp25) & 4095)] * fTemp27) + (fTemp28 * fVec2[((IOTA - iTemp29) & 4095)]));
			float fRec18 = (0.0f - (0.600000024f * fTemp21));
			float fTemp30 = (fRec17[1] + (fRec18 + (0.600000024f * fRec15[1])));
			fVec3[(IOTA & 4095)] = fTemp30;
			float fTemp31 = (625.0f * fTemp12);
			float fTemp32 = (fTemp31 + -1.0f);
			int iTemp33 = int(fTemp32);
			int iTemp34 = min(2049, max(0, iTemp33));
			float fTemp35 = floorf(fTemp32);
			float fTemp36 = (fTemp35 + (2.0f - fTemp31));
			float fTemp37 = (fTemp31 + (-1.0f - fTemp35));
			int iTemp38 = min(2049, max(0, (iTemp33 + 1)));
			fRec15[0] = ((fVec3[((IOTA - iTemp34) & 4095)] * fTemp36) + (fTemp37 * fVec3[((IOTA - iTemp38) & 4095)]));
			float fRec16 = (0.0f - (0.600000024f * fTemp30));
			float fTemp39 = (fRec15[1] + (fRec16 + (0.600000024f * fRec13[1])));
			fVec4[(IOTA & 4095)] = fTemp39;
			float fTemp40 = (727.0f * fTemp12);
			float fTemp41 = (fTemp40 + -1.0f);
			int iTemp42 = int(fTemp41);
			int iTemp43 = min(2049, max(0, iTemp42));
			float fTemp44 = floorf(fTemp41);
			float fTemp45 = (fTemp44 + (2.0f - fTemp40));
			float fTemp46 = (fTemp40 + (-1.0f - fTemp44));
			int iTemp47 = min(2049, max(0, (iTemp42 + 1)));
			fRec13[0] = ((fVec4[((IOTA - iTemp43) & 4095)] * fTemp45) + (fTemp46 * fVec4[((IOTA - iTemp47) & 4095)]));
			float fRec14 = (0.0f - (0.600000024f * fTemp39));
			float fTemp48 = (fRec13[1] + (fRec14 + (0.600000024f * fRec11[1])));
			fVec5[(IOTA & 4095)] = fTemp48;
			float fTemp49 = (1331.0f * fTemp12);
			float fTemp50 = (fTemp49 + -1.0f);
			int iTemp51 = int(fTemp50);
			int iTemp52 = min(2049, max(0, iTemp51));
			float fTemp53 = floorf(fTemp50);
			float fTemp54 = (fTemp53 + (2.0f - fTemp49));
			float fTemp55 = (fTemp49 + (-1.0f - fTemp53));
			int iTemp56 = min(2049, max(0, (iTemp51 + 1)));
			fRec11[0] = ((fVec5[((IOTA - iTemp52) & 4095)] * fTemp54) + (fTemp55 * fVec5[((IOTA - iTemp56) & 4095)]));
			float fRec12 = (0.0f - (0.600000024f * fTemp48));
			float fTemp57 = (fRec11[1] + (fRec12 + (0.600000024f * fRec9[1])));
			fVec6[(IOTA & 4095)] = fTemp57;
			float fTemp58 = (2403.0f * fTemp12);
			float fTemp59 = (fTemp58 + -1.0f);
			int iTemp60 = int(fTemp59);
			int iTemp61 = min(2049, max(0, iTemp60));
			float fTemp62 = floorf(fTemp59);
			float fTemp63 = (fTemp62 + (2.0f - fTemp58));
			float fTemp64 = (fTemp58 + (-1.0f - fTemp62));
			int iTemp65 = min(2049, max(0, (iTemp60 + 1)));
			fRec9[0] = ((fVec6[((IOTA - iTemp61) & 4095)] * fTemp63) + (fTemp64 * fVec6[((IOTA - iTemp65) & 4095)]));
			float fRec10 = (0.0f - (0.600000024f * fTemp57));
			float fTemp66 = (fRec10 + fRec9[1]);
			fVec7[(IOTA & 16383)] = fTemp66;
			float fTemp67 = (1356.0f * fTemp12);
			int iTemp68 = int(fTemp67);
			float fTemp69 = floorf(fTemp67);
			fRec1[0] = (0.353553385f * ((fVec7[((IOTA - min(8193, max(0, iTemp68))) & 16383)] * (fTemp69 + (1.0f - fTemp67))) + ((fTemp67 - fTemp69) * fVec7[((IOTA - min(8193, max(0, (iTemp68 + 1)))) & 16383)])));
			fRec40[0] = ((fSlow1 * (fTemp1 - (fRec8[1] + ((fRec2[1] + fRec6[1]) + fRec4[1])))) - (((fTemp4 * fRec40[2]) + (2.0f * (fTemp5 * fRec40[1]))) / fTemp6));
			fRec39[0] = (((fRec40[2] + (fRec40[0] + (2.0f * fRec40[1]))) / fTemp6) - (((fTemp7 * fRec39[2]) + (2.0f * (fTemp5 * fRec39[1]))) / fTemp8));
			float fTemp70 = ((((0.600000024f * fRec37[1]) + ((fRec39[2] + (fRec39[0] + (2.0f * fRec39[1]))) / fTemp8)) + fTemp9) + fTemp10);
			fVec8[(IOTA & 4095)] = fTemp70;
			fRec37[0] = ((fTemp18 * fVec8[((IOTA - iTemp16) & 4095)]) + (fTemp19 * fVec8[((IOTA - iTemp20) & 4095)]));
			float fRec38 = (0.0f - (0.600000024f * fTemp70));
			float fTemp71 = (fRec37[1] + (fRec38 + (0.600000024f * fRec35[1])));
			fVec9[(IOTA & 4095)] = fTemp71;
			fRec35[0] = ((fTemp27 * fVec9[((IOTA - iTemp25) & 4095)]) + (fTemp28 * fVec9[((IOTA - iTemp29) & 4095)]));
			float fRec36 = (0.0f - (0.600000024f * fTemp71));
			float fTemp72 = (fRec35[1] + (fRec36 + (0.600000024f * fRec33[1])));
			fVec10[(IOTA & 4095)] = fTemp72;
			fRec33[0] = ((fTemp36 * fVec10[((IOTA - iTemp34) & 4095)]) + (fTemp37 * fVec10[((IOTA - iTemp38) & 4095)]));
			float fRec34 = (0.0f - (0.600000024f * fTemp72));
			float fTemp73 = (fRec33[1] + (fRec34 + (0.600000024f * fRec31[1])));
			fVec11[(IOTA & 4095)] = fTemp73;
			fRec31[0] = ((fTemp45 * fVec11[((IOTA - iTemp43) & 4095)]) + (fTemp46 * fVec11[((IOTA - iTemp47) & 4095)]));
			float fRec32 = (0.0f - (0.600000024f * fTemp73));
			float fTemp74 = (fRec31[1] + (fRec32 + (0.600000024f * fRec29[1])));
			fVec12[(IOTA & 4095)] = fTemp74;
			fRec29[0] = ((fTemp54 * fVec12[((IOTA - iTemp52) & 4095)]) + (fTemp55 * fVec12[((IOTA - iTemp56) & 4095)]));
			float fRec30 = (0.0f - (0.600000024f * fTemp74));
			float fTemp75 = (fRec29[1] + (fRec30 + (0.600000024f * fRec27[1])));
			fVec13[(IOTA & 4095)] = fTemp75;
			fRec27[0] = ((fTemp63 * fVec13[((IOTA - iTemp61) & 4095)]) + (fTemp64 * fVec13[((IOTA - iTemp65) & 4095)]));
			float fRec28 = (0.0f - (0.600000024f * fTemp75));
			float fTemp76 = (fRec28 + fRec27[1]);
			fVec14[(IOTA & 16383)] = fTemp76;
			float fTemp77 = (1422.0f * fTemp12);
			int iTemp78 = int(fTemp77);
			float fTemp79 = floorf(fTemp77);
			fRec2[0] = (0.353553385f * ((fVec14[((IOTA - min(8193, max(0, iTemp78))) & 16383)] * (fTemp79 + (1.0f - fTemp77))) + ((fTemp77 - fTemp79) * fVec14[((IOTA - min(8193, max(0, (iTemp78 + 1)))) & 16383)])));
			float fTemp80 = (fRec3[1] + fRec7[1]);
			fRec55[0] = ((fSlow1 * ((fRec6[1] + (fTemp0 + fRec2[1])) - (fRec8[1] + (fTemp80 + fRec4[1])))) - (((fTemp4 * fRec55[2]) + (2.0f * (fTemp5 * fRec55[1]))) / fTemp6));
			fRec54[0] = (((fRec55[2] + (fRec55[0] + (2.0f * fRec55[1]))) / fTemp6) - (((fTemp7 * fRec54[2]) + (2.0f * (fTemp5 * fRec54[1]))) / fTemp8));
			float fTemp81 = ((((0.600000024f * fRec52[1]) + ((fRec54[2] + (fRec54[0] + (2.0f * fRec54[1]))) / fTemp8)) + fTemp9) + fTemp10);
			fVec15[(IOTA & 4095)] = fTemp81;
			fRec52[0] = ((fTemp18 * fVec15[((IOTA - iTemp16) & 4095)]) + (fTemp19 * fVec15[((IOTA - iTemp20) & 4095)]));
			float fRec53 = (0.0f - (0.600000024f * fTemp81));
			float fTemp82 = (fRec52[1] + (fRec53 + (0.600000024f * fRec50[1])));
			fVec16[(IOTA & 4095)] = fTemp82;
			fRec50[0] = ((fTemp27 * fVec16[((IOTA - iTemp25) & 4095)]) + (fTemp28 * fVec16[((IOTA - iTemp29) & 4095)]));
			float fRec51 = (0.0f - (0.600000024f * fTemp82));
			float fTemp83 = (fRec50[1] + (fRec51 + (0.600000024f * fRec48[1])));
			fVec17[(IOTA & 4095)] = fTemp83;
			fRec48[0] = ((fTemp36 * fVec17[((IOTA - iTemp34) & 4095)]) + (fTemp37 * fVec17[((IOTA - iTemp38) & 4095)]));
			float fRec49 = (0.0f - (0.600000024f * fTemp83));
			float fTemp84 = (fRec48[1] + (fRec49 + (0.600000024f * fRec46[1])));
			fVec18[(IOTA & 4095)] = fTemp84;
			fRec46[0] = ((fTemp45 * fVec18[((IOTA - iTemp43) & 4095)]) + (fTemp46 * fVec18[((IOTA - iTemp47) & 4095)]));
			float fRec47 = (0.0f - (0.600000024f * fTemp84));
			float fTemp85 = (fRec46[1] + (fRec47 + (0.600000024f * fRec44[1])));
			fVec19[(IOTA & 4095)] = fTemp85;
			fRec44[0] = ((fTemp54 * fVec19[((IOTA - iTemp52) & 4095)]) + (fTemp55 * fVec19[((IOTA - iTemp56) & 4095)]));
			float fRec45 = (0.0f - (0.600000024f * fTemp85));
			float fTemp86 = (fRec44[1] + (fRec45 + (0.600000024f * fRec42[1])));
			fVec20[(IOTA & 4095)] = fTemp86;
			fRec42[0] = ((fTemp63 * fVec20[((IOTA - iTemp61) & 4095)]) + (fTemp64 * fVec20[((IOTA - iTemp65) & 4095)]));
			float fRec43 = (0.0f - (0.600000024f * fTemp86));
			float fTemp87 = (fRec43 + fRec42[1]);
			fVec21[(IOTA & 16383)] = fTemp87;
			float fTemp88 = (1557.0f * fTemp12);
			int iTemp89 = int(fTemp88);
			float fTemp90 = floorf(fTemp88);
			fRec41[0] = ((0.353553385f * ((fVec21[((IOTA - min(8193, max(0, iTemp89))) & 16383)] * (fTemp90 + (1.0f - fTemp88))) + ((fTemp88 - fTemp90) * fVec21[((IOTA - min(8193, max(0, (iTemp89 + 1)))) & 16383)]))) - (fConst5 * ((fConst7 * fRec41[2]) + (fConst8 * fRec41[1]))));
			fRec3[0] = (fConst5 * (((fConst6 * fRec41[0]) + (fConst9 * fRec41[1])) + (fConst6 * fRec41[2])));
			fRec69[0] = ((fSlow1 * ((fRec8[1] + (fTemp0 + fRec4[1])) - (fRec6[1] + (fTemp80 + fRec2[1])))) - (((fTemp4 * fRec69[2]) + (2.0f * (fTemp5 * fRec69[1]))) / fTemp6));
			fRec68[0] = (((fRec69[2] + (fRec69[0] + (2.0f * fRec69[1]))) / fTemp6) - (((fTemp7 * fRec68[2]) + (2.0f * (fTemp5 * fRec68[1]))) / fTemp8));
			float fTemp91 = ((((0.600000024f * fRec66[1]) + ((fRec68[2] + (fRec68[0] + (2.0f * fRec68[1]))) / fTemp8)) + fTemp9) + fTemp10);
			fVec22[(IOTA & 4095)] = fTemp91;
			fRec66[0] = ((fTemp18 * fVec22[((IOTA - iTemp16) & 4095)]) + (fTemp19 * fVec22[((IOTA - iTemp20) & 4095)]));
			float fRec67 = (0.0f - (0.600000024f * fTemp91));
			float fTemp92 = (fRec66[1] + (fRec67 + (0.600000024f * fRec64[1])));
			fVec23[(IOTA & 4095)] = fTemp92;
			fRec64[0] = ((fTemp27 * fVec23[((IOTA - iTemp25) & 4095)]) + (fTemp28 * fVec23[((IOTA - iTemp29) & 4095)]));
			float fRec65 = (0.0f - (0.600000024f * fTemp92));
			float fTemp93 = (fRec64[1] + (fRec65 + (0.600000024f * fRec62[1])));
			fVec24[(IOTA & 4095)] = fTemp93;
			fRec62[0] = ((fTemp36 * fVec24[((IOTA - iTemp34) & 4095)]) + (fTemp37 * fVec24[((IOTA - iTemp38) & 4095)]));
			float fRec63 = (0.0f - (0.600000024f * fTemp93));
			float fTemp94 = (fRec62[1] + (fRec63 + (0.600000024f * fRec60[1])));
			fVec25[(IOTA & 4095)] = fTemp94;
			fRec60[0] = ((fTemp45 * fVec25[((IOTA - iTemp43) & 4095)]) + (fTemp46 * fVec25[((IOTA - iTemp47) & 4095)]));
			float fRec61 = (0.0f - (0.600000024f * fTemp94));
			float fTemp95 = (fRec60[1] + (fRec61 + (0.600000024f * fRec58[1])));
			fVec26[(IOTA & 4095)] = fTemp95;
			fRec58[0] = ((fTemp54 * fVec26[((IOTA - iTemp52) & 4095)]) + (fTemp55 * fVec26[((IOTA - iTemp56) & 4095)]));
			float fRec59 = (0.0f - (0.600000024f * fTemp95));
			float fTemp96 = (fRec58[1] + (fRec59 + (0.600000024f * fRec56[1])));
			fVec27[(IOTA & 4095)] = fTemp96;
			fRec56[0] = ((fTemp63 * fVec27[((IOTA - iTemp61) & 4095)]) + (fTemp64 * fVec27[((IOTA - iTemp65) & 4095)]));
			float fRec57 = (0.0f - (0.600000024f * fTemp96));
			float fTemp97 = (fRec57 + fRec56[1]);
			fVec28[(IOTA & 131071)] = fTemp97;
			float fTemp98 = (1617.0f * fTemp12);
			float fTemp99 = (fTemp98 + 8192.0f);
			fRec70[0] = fmodf(((fTemp98 + fRec70[1]) + 8191.0f), fTemp99);
			int iTemp100 = int(fRec70[0]);
			float fTemp101 = floorf(fRec70[0]);
			fRec71[0] = fmodf(((fTemp98 + fRec71[1]) + 8191.0f), fTemp99);
			float fTemp102 = min((fRec71[0] / fTemp99), 1.0f);
			float fTemp103 = (fRec70[0] + fTemp98);
			float fTemp104 = (fTemp103 + 8192.0f);
			int iTemp105 = int(fTemp104);
			float fTemp106 = floorf(fTemp104);
			fRec4[0] = (0.353553385f * ((fSlow4 * fVec28[((IOTA - int(min(8192.0f, max(0.0f, fTemp99)))) & 131071)]) + (fSlow3 * ((((fVec28[((IOTA - min(65537, max(0, iTemp100))) & 131071)] * (fTemp101 + (1.0f - fRec70[0]))) + ((fRec70[0] - fTemp101) * fVec28[((IOTA - min(65537, max(0, (iTemp100 + 1)))) & 131071)])) * fTemp102) + (((fVec28[((IOTA - min(65537, max(0, iTemp105))) & 131071)] * (fTemp106 + (-8191.0f - fTemp103))) + ((fTemp103 + (8192.0f - fTemp106)) * fVec28[((IOTA - min(65537, max(0, (iTemp105 + 1)))) & 131071)])) * (1.0f - fTemp102))))));
			float fTemp107 = (fRec1[1] + fRec3[1]);
			float fTemp108 = (fRec5[1] + fRec7[1]);
			fRec85[0] = ((fSlow1 * ((fRec4[1] + (fRec2[1] + fTemp107)) - (fRec8[1] + (fRec6[1] + fTemp108)))) - (((fTemp4 * fRec85[2]) + (2.0f * (fTemp5 * fRec85[1]))) / fTemp6));
			fRec84[0] = (((fRec85[2] + (fRec85[0] + (2.0f * fRec85[1]))) / fTemp6) - (((fTemp7 * fRec84[2]) + (2.0f * (fTemp5 * fRec84[1]))) / fTemp8));
			float fTemp109 = ((((0.600000024f * fRec82[1]) + ((fRec84[2] + (fRec84[0] + (2.0f * fRec84[1]))) / fTemp8)) + fTemp9) + fTemp10);
			fVec29[(IOTA & 4095)] = fTemp109;
			fRec82[0] = ((fTemp18 * fVec29[((IOTA - iTemp16) & 4095)]) + (fTemp19 * fVec29[((IOTA - iTemp20) & 4095)]));
			float fRec83 = (0.0f - (0.600000024f * fTemp109));
			float fTemp110 = (fRec82[1] + (fRec83 + (0.600000024f * fRec80[1])));
			fVec30[(IOTA & 4095)] = fTemp110;
			fRec80[0] = ((fTemp27 * fVec30[((IOTA - iTemp25) & 4095)]) + (fTemp28 * fVec30[((IOTA - iTemp29) & 4095)]));
			float fRec81 = (0.0f - (0.600000024f * fTemp110));
			float fTemp111 = (fRec80[1] + (fRec81 + (0.600000024f * fRec78[1])));
			fVec31[(IOTA & 4095)] = fTemp111;
			fRec78[0] = ((fTemp36 * fVec31[((IOTA - iTemp34) & 4095)]) + (fTemp37 * fVec31[((IOTA - iTemp38) & 4095)]));
			float fRec79 = (0.0f - (0.600000024f * fTemp111));
			float fTemp112 = (fRec78[1] + (fRec79 + (0.600000024f * fRec76[1])));
			fVec32[(IOTA & 4095)] = fTemp112;
			fRec76[0] = ((fTemp45 * fVec32[((IOTA - iTemp43) & 4095)]) + (fTemp46 * fVec32[((IOTA - iTemp47) & 4095)]));
			float fRec77 = (0.0f - (0.600000024f * fTemp112));
			float fTemp113 = (fRec76[1] + (fRec77 + (0.600000024f * fRec74[1])));
			fVec33[(IOTA & 4095)] = fTemp113;
			fRec74[0] = ((fTemp54 * fVec33[((IOTA - iTemp52) & 4095)]) + (fTemp55 * fVec33[((IOTA - iTemp56) & 4095)]));
			float fRec75 = (0.0f - (0.600000024f * fTemp113));
			float fTemp114 = (fRec74[1] + (fRec75 + (0.600000024f * fRec72[1])));
			fVec34[(IOTA & 4095)] = fTemp114;
			fRec72[0] = ((fTemp63 * fVec34[((IOTA - iTemp61) & 4095)]) + (fTemp64 * fVec34[((IOTA - iTemp65) & 4095)]));
			float fRec73 = (0.0f - (0.600000024f * fTemp114));
			float fTemp115 = (fRec73 + fRec72[1]);
			fVec35[(IOTA & 16383)] = fTemp115;
			float fTemp116 = (1933.0f * fTemp12);
			int iTemp117 = int(fTemp116);
			float fTemp118 = floorf(fTemp116);
			fRec5[0] = (0.353553385f * ((fVec35[((IOTA - min(8193, max(0, iTemp117))) & 16383)] * (fTemp118 + (1.0f - fTemp116))) + ((fTemp116 - fTemp118) * fVec35[((IOTA - min(8193, max(0, (iTemp117 + 1)))) & 16383)])));
			fRec99[0] = ((fSlow1 * ((fRec8[1] + (fRec6[1] + fTemp107)) - (fRec4[1] + (fRec2[1] + fTemp108)))) - (((fTemp4 * fRec99[2]) + (2.0f * (fTemp5 * fRec99[1]))) / fTemp6));
			fRec98[0] = (((fRec99[2] + (fRec99[0] + (2.0f * fRec99[1]))) / fTemp6) - (((fTemp7 * fRec98[2]) + (2.0f * (fTemp5 * fRec98[1]))) / fTemp8));
			float fTemp119 = ((((0.600000024f * fRec96[1]) + ((fRec98[2] + (fRec98[0] + (2.0f * fRec98[1]))) / fTemp8)) + fTemp9) + fTemp10);
			fVec36[(IOTA & 4095)] = fTemp119;
			fRec96[0] = ((fTemp18 * fVec36[((IOTA - iTemp16) & 4095)]) + (fTemp19 * fVec36[((IOTA - iTemp20) & 4095)]));
			float fRec97 = (0.0f - (0.600000024f * fTemp119));
			float fTemp120 = (fRec96[1] + (fRec97 + (0.600000024f * fRec94[1])));
			fVec37[(IOTA & 4095)] = fTemp120;
			fRec94[0] = ((fTemp27 * fVec37[((IOTA - iTemp25) & 4095)]) + (fTemp28 * fVec37[((IOTA - iTemp29) & 4095)]));
			float fRec95 = (0.0f - (0.600000024f * fTemp120));
			float fTemp121 = (fRec94[1] + (fRec95 + (0.600000024f * fRec92[1])));
			fVec38[(IOTA & 4095)] = fTemp121;
			fRec92[0] = ((fTemp36 * fVec38[((IOTA - iTemp34) & 4095)]) + (fTemp37 * fVec38[((IOTA - iTemp38) & 4095)]));
			float fRec93 = (0.0f - (0.600000024f * fTemp121));
			float fTemp122 = (fRec92[1] + (fRec93 + (0.600000024f * fRec90[1])));
			fVec39[(IOTA & 4095)] = fTemp122;
			fRec90[0] = ((fTemp45 * fVec39[((IOTA - iTemp43) & 4095)]) + (fTemp46 * fVec39[((IOTA - iTemp47) & 4095)]));
			float fRec91 = (0.0f - (0.600000024f * fTemp122));
			float fTemp123 = (fRec90[1] + (fRec91 + (0.600000024f * fRec88[1])));
			fVec40[(IOTA & 4095)] = fTemp123;
			fRec88[0] = ((fTemp54 * fVec40[((IOTA - iTemp52) & 4095)]) + (fTemp55 * fVec40[((IOTA - iTemp56) & 4095)]));
			float fRec89 = (0.0f - (0.600000024f * fTemp123));
			float fTemp124 = (fRec88[1] + (fRec89 + (0.600000024f * fRec86[1])));
			fVec41[(IOTA & 4095)] = fTemp124;
			fRec86[0] = ((fTemp63 * fVec41[((IOTA - iTemp61) & 4095)]) + (fTemp64 * fVec41[((IOTA - iTemp65) & 4095)]));
			float fRec87 = (0.0f - (0.600000024f * fTemp124));
			float fTemp125 = (fRec87 + fRec86[1]);
			fVec42[(IOTA & 16383)] = fTemp125;
			float fTemp126 = (2401.0f * fTemp12);
			int iTemp127 = int(fTemp126);
			float fTemp128 = floorf(fTemp126);
			fRec6[0] = (0.353553385f * ((fVec42[((IOTA - min(8193, max(0, iTemp127))) & 16383)] * (fTemp128 + (1.0f - fTemp126))) + ((fTemp126 - fTemp128) * fVec42[((IOTA - min(8193, max(0, (iTemp127 + 1)))) & 16383)])));
			float fTemp129 = (fRec1[1] + fRec7[1]);
			float fTemp130 = (fRec5[1] + fRec3[1]);
			fRec113[0] = ((fSlow1 * ((fRec8[1] + (fRec2[1] + fTemp129)) - (fRec4[1] + (fRec6[1] + fTemp130)))) - (((fTemp4 * fRec113[2]) + (2.0f * (fTemp5 * fRec113[1]))) / fTemp6));
			fRec112[0] = (((fRec113[2] + (fRec113[0] + (2.0f * fRec113[1]))) / fTemp6) - (((fTemp7 * fRec112[2]) + (2.0f * (fTemp5 * fRec112[1]))) / fTemp8));
			float fTemp131 = ((((0.600000024f * fRec110[1]) + ((fRec112[2] + (fRec112[0] + (2.0f * fRec112[1]))) / fTemp8)) + fTemp9) + fTemp10);
			fVec43[(IOTA & 4095)] = fTemp131;
			fRec110[0] = ((fTemp18 * fVec43[((IOTA - iTemp16) & 4095)]) + (fTemp19 * fVec43[((IOTA - iTemp20) & 4095)]));
			float fRec111 = (0.0f - (0.600000024f * fTemp131));
			float fTemp132 = (fRec110[1] + (fRec111 + (0.600000024f * fRec108[1])));
			fVec44[(IOTA & 4095)] = fTemp132;
			fRec108[0] = ((fTemp27 * fVec44[((IOTA - iTemp25) & 4095)]) + (fTemp28 * fVec44[((IOTA - iTemp29) & 4095)]));
			float fRec109 = (0.0f - (0.600000024f * fTemp132));
			float fTemp133 = (fRec108[1] + (fRec109 + (0.600000024f * fRec106[1])));
			fVec45[(IOTA & 4095)] = fTemp133;
			fRec106[0] = ((fTemp36 * fVec45[((IOTA - iTemp34) & 4095)]) + (fTemp37 * fVec45[((IOTA - iTemp38) & 4095)]));
			float fRec107 = (0.0f - (0.600000024f * fTemp133));
			float fTemp134 = (fRec106[1] + (fRec107 + (0.600000024f * fRec104[1])));
			fVec46[(IOTA & 4095)] = fTemp134;
			fRec104[0] = ((fTemp45 * fVec46[((IOTA - iTemp43) & 4095)]) + (fTemp46 * fVec46[((IOTA - iTemp47) & 4095)]));
			float fRec105 = (0.0f - (0.600000024f * fTemp134));
			float fTemp135 = (fRec104[1] + (fRec105 + (0.600000024f * fRec102[1])));
			fVec47[(IOTA & 4095)] = fTemp135;
			fRec102[0] = ((fTemp54 * fVec47[((IOTA - iTemp52) & 4095)]) + (fTemp55 * fVec47[((IOTA - iTemp56) & 4095)]));
			float fRec103 = (0.0f - (0.600000024f * fTemp135));
			float fTemp136 = (fRec102[1] + (fRec103 + (0.600000024f * fRec100[1])));
			fVec48[(IOTA & 4095)] = fTemp136;
			fRec100[0] = ((fTemp63 * fVec48[((IOTA - iTemp61) & 4095)]) + (fTemp64 * fVec48[((IOTA - iTemp65) & 4095)]));
			float fRec101 = (0.0f - (0.600000024f * fTemp136));
			float fTemp137 = (fRec101 + fRec100[1]);
			fVec49[(IOTA & 16383)] = fTemp137;
			float fTemp138 = (3125.0f * fTemp12);
			int iTemp139 = int(fTemp138);
			float fTemp140 = floorf(fTemp138);
			fRec7[0] = (0.353553385f * ((fVec49[((IOTA - min(8193, max(0, iTemp139))) & 16383)] * (fTemp140 + (1.0f - fTemp138))) + ((fTemp138 - fTemp140) * fVec49[((IOTA - min(8193, max(0, (iTemp139 + 1)))) & 16383)])));
			fRec127[0] = ((fSlow1 * ((fRec4[1] + (fRec6[1] + fTemp129)) - (fRec8[1] + (fRec2[1] + fTemp130)))) - (((fTemp4 * fRec127[2]) + (2.0f * (fTemp5 * fRec127[1]))) / fTemp6));
			fRec126[0] = (((fRec127[2] + (fRec127[0] + (2.0f * fRec127[1]))) / fTemp6) - (((fTemp7 * fRec126[2]) + (2.0f * (fTemp5 * fRec126[1]))) / fTemp8));
			float fTemp141 = ((((0.600000024f * fRec124[1]) + ((fRec126[2] + (fRec126[0] + (2.0f * fRec126[1]))) / fTemp8)) + fTemp9) + fTemp10);
			fVec50[(IOTA & 4095)] = fTemp141;
			fRec124[0] = ((fTemp18 * fVec50[((IOTA - iTemp16) & 4095)]) + (fTemp19 * fVec50[((IOTA - iTemp20) & 4095)]));
			float fRec125 = (0.0f - (0.600000024f * fTemp141));
			float fTemp142 = (fRec124[1] + (fRec125 + (0.600000024f * fRec122[1])));
			fVec51[(IOTA & 4095)] = fTemp142;
			fRec122[0] = ((fTemp27 * fVec51[((IOTA - iTemp25) & 4095)]) + (fTemp28 * fVec51[((IOTA - iTemp29) & 4095)]));
			float fRec123 = (0.0f - (0.600000024f * fTemp142));
			float fTemp143 = (fRec122[1] + (fRec123 + (0.600000024f * fRec120[1])));
			fVec52[(IOTA & 4095)] = fTemp143;
			fRec120[0] = ((fTemp36 * fVec52[((IOTA - iTemp34) & 4095)]) + (fTemp37 * fVec52[((IOTA - iTemp38) & 4095)]));
			float fRec121 = (0.0f - (0.600000024f * fTemp143));
			float fTemp144 = (fRec120[1] + (fRec121 + (0.600000024f * fRec118[1])));
			fVec53[(IOTA & 4095)] = fTemp144;
			fRec118[0] = ((fTemp45 * fVec53[((IOTA - iTemp43) & 4095)]) + (fTemp46 * fVec53[((IOTA - iTemp47) & 4095)]));
			float fRec119 = (0.0f - (0.600000024f * fTemp144));
			float fTemp145 = (fRec118[1] + (fRec119 + (0.600000024f * fRec116[1])));
			fVec54[(IOTA & 4095)] = fTemp145;
			fRec116[0] = ((fTemp54 * fVec54[((IOTA - iTemp52) & 4095)]) + (fTemp55 * fVec54[((IOTA - iTemp56) & 4095)]));
			float fRec117 = (0.0f - (0.600000024f * fTemp145));
			float fTemp146 = (fRec116[1] + (fRec117 + (0.600000024f * fRec114[1])));
			fVec55[(IOTA & 4095)] = fTemp146;
			fRec114[0] = ((fTemp63 * fVec55[((IOTA - iTemp61) & 4095)]) + (fTemp64 * fVec55[((IOTA - iTemp65) & 4095)]));
			float fRec115 = (0.0f - (0.600000024f * fTemp146));
			float fTemp147 = (fRec115 + fRec114[1]);
			fVec56[(IOTA & 16383)] = fTemp147;
			float fTemp148 = (6561.0f * fTemp12);
			int iTemp149 = int(fTemp148);
			float fTemp150 = floorf(fTemp148);
			fRec8[0] = (0.353553385f * ((fVec56[((IOTA - min(8193, max(0, iTemp149))) & 16383)] * (fTemp150 + (1.0f - fTemp148))) + ((fTemp148 - fTemp150) * fVec56[((IOTA - min(8193, max(0, (iTemp149 + 1)))) & 16383)])));
			float fTemp151 = (((fTemp3 + -1.41421354f) / fTemp2) + 1.0f);
			float fTemp152 = (((fTemp3 + 1.41421354f) / fTemp2) + 1.0f);
			fRec0[0] = ((((fRec1[0] + fRec3[0]) + fRec5[0]) + fRec7[0]) - (((fRec0[2] * fTemp151) + (2.0f * (fTemp5 * fRec0[1]))) / fTemp152));
			fRec128[0] = ((((fRec2[0] + fRec4[0]) + fRec6[0]) + fRec8[0]) - (((fTemp151 * fRec128[2]) + (2.0f * (fTemp5 * fRec128[1]))) / fTemp152));
			float fTemp153 = ((fSlow0 * (((fRec0[2] + (fRec0[0] + (2.0f * fRec0[1]))) + (fRec128[2] + (fRec128[0] + (2.0f * fRec128[1])))) / fTemp152)) + (fSlow5 * (fTemp9 + fTemp10)));
			output0[i] = FAUSTFLOAT(fTemp153);
			output1[i] = FAUSTFLOAT(fTemp153);
			iVec0[1] = iVec0[0];
			fRec23[1] = fRec23[0];
			fRec22[2] = fRec22[1];
			fRec22[1] = fRec22[0];
			fRec21[2] = fRec21[1];
			fRec21[1] = fRec21[0];
			IOTA = (IOTA + 1);
			fRec26[1] = fRec26[0];
			fRec25[1] = fRec25[0];
			fRec24[1] = fRec24[0];
			fRec19[1] = fRec19[0];
			fRec17[1] = fRec17[0];
			fRec15[1] = fRec15[0];
			fRec13[1] = fRec13[0];
			fRec11[1] = fRec11[0];
			fRec9[1] = fRec9[0];
			fRec1[1] = fRec1[0];
			fRec40[2] = fRec40[1];
			fRec40[1] = fRec40[0];
			fRec39[2] = fRec39[1];
			fRec39[1] = fRec39[0];
			fRec37[1] = fRec37[0];
			fRec35[1] = fRec35[0];
			fRec33[1] = fRec33[0];
			fRec31[1] = fRec31[0];
			fRec29[1] = fRec29[0];
			fRec27[1] = fRec27[0];
			fRec2[1] = fRec2[0];
			fRec55[2] = fRec55[1];
			fRec55[1] = fRec55[0];
			fRec54[2] = fRec54[1];
			fRec54[1] = fRec54[0];
			fRec52[1] = fRec52[0];
			fRec50[1] = fRec50[0];
			fRec48[1] = fRec48[0];
			fRec46[1] = fRec46[0];
			fRec44[1] = fRec44[0];
			fRec42[1] = fRec42[0];
			fRec41[2] = fRec41[1];
			fRec41[1] = fRec41[0];
			fRec3[1] = fRec3[0];
			fRec69[2] = fRec69[1];
			fRec69[1] = fRec69[0];
			fRec68[2] = fRec68[1];
			fRec68[1] = fRec68[0];
			fRec66[1] = fRec66[0];
			fRec64[1] = fRec64[0];
			fRec62[1] = fRec62[0];
			fRec60[1] = fRec60[0];
			fRec58[1] = fRec58[0];
			fRec56[1] = fRec56[0];
			fRec70[1] = fRec70[0];
			fRec71[1] = fRec71[0];
			fRec4[1] = fRec4[0];
			fRec85[2] = fRec85[1];
			fRec85[1] = fRec85[0];
			fRec84[2] = fRec84[1];
			fRec84[1] = fRec84[0];
			fRec82[1] = fRec82[0];
			fRec80[1] = fRec80[0];
			fRec78[1] = fRec78[0];
			fRec76[1] = fRec76[0];
			fRec74[1] = fRec74[0];
			fRec72[1] = fRec72[0];
			fRec5[1] = fRec5[0];
			fRec99[2] = fRec99[1];
			fRec99[1] = fRec99[0];
			fRec98[2] = fRec98[1];
			fRec98[1] = fRec98[0];
			fRec96[1] = fRec96[0];
			fRec94[1] = fRec94[0];
			fRec92[1] = fRec92[0];
			fRec90[1] = fRec90[0];
			fRec88[1] = fRec88[0];
			fRec86[1] = fRec86[0];
			fRec6[1] = fRec6[0];
			fRec113[2] = fRec113[1];
			fRec113[1] = fRec113[0];
			fRec112[2] = fRec112[1];
			fRec112[1] = fRec112[0];
			fRec110[1] = fRec110[0];
			fRec108[1] = fRec108[0];
			fRec106[1] = fRec106[0];
			fRec104[1] = fRec104[0];
			fRec102[1] = fRec102[0];
			fRec100[1] = fRec100[0];
			fRec7[1] = fRec7[0];
			fRec127[2] = fRec127[1];
			fRec127[1] = fRec127[0];
			fRec126[2] = fRec126[1];
			fRec126[1] = fRec126[0];
			fRec124[1] = fRec124[0];
			fRec122[1] = fRec122[0];
			fRec120[1] = fRec120[0];
			fRec118[1] = fRec118[0];
			fRec116[1] = fRec116[0];
			fRec114[1] = fRec114[0];
			fRec8[1] = fRec8[0];
			fRec0[2] = fRec0[1];
			fRec0[1] = fRec0[0];
			fRec128[2] = fRec128[1];
			fRec128[1] = fRec128[0];
			
		}
		
	}

	
};

#endif
