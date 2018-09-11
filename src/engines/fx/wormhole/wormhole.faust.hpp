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
	float fRec151[3];
	float fRec150[3];
	float fVec57[4096];
	float fRec148[2];
	float fVec58[4096];
	float fRec146[2];
	float fVec59[4096];
	float fRec144[2];
	float fVec60[4096];
	float fRec142[2];
	float fVec61[4096];
	float fRec140[2];
	float fVec62[4096];
	float fRec138[2];
	float fVec63[16384];
	float fRec130[2];
	float fRec165[3];
	float fRec164[3];
	float fVec64[4096];
	float fRec162[2];
	float fVec65[4096];
	float fRec160[2];
	float fVec66[4096];
	float fRec158[2];
	float fVec67[4096];
	float fRec156[2];
	float fVec68[4096];
	float fRec154[2];
	float fVec69[4096];
	float fRec152[2];
	float fVec70[16384];
	float fRec131[2];
	float fRec180[3];
	float fRec179[3];
	float fVec71[4096];
	float fRec177[2];
	float fVec72[4096];
	float fRec175[2];
	float fVec73[4096];
	float fRec173[2];
	float fVec74[4096];
	float fRec171[2];
	float fVec75[4096];
	float fRec169[2];
	float fVec76[4096];
	float fRec167[2];
	float fVec77[16384];
	float fRec166[3];
	float fRec132[2];
	float fRec194[3];
	float fRec193[3];
	float fVec78[4096];
	float fRec191[2];
	float fVec79[4096];
	float fRec189[2];
	float fVec80[4096];
	float fRec187[2];
	float fVec81[4096];
	float fRec185[2];
	float fVec82[4096];
	float fRec183[2];
	float fVec83[4096];
	float fRec181[2];
	float fVec84[131072];
	float fRec133[2];
	float fRec208[3];
	float fRec207[3];
	float fVec85[4096];
	float fRec205[2];
	float fVec86[4096];
	float fRec203[2];
	float fVec87[4096];
	float fRec201[2];
	float fVec88[4096];
	float fRec199[2];
	float fVec89[4096];
	float fRec197[2];
	float fVec90[4096];
	float fRec195[2];
	float fVec91[16384];
	float fRec134[2];
	float fRec222[3];
	float fRec221[3];
	float fVec92[4096];
	float fRec219[2];
	float fVec93[4096];
	float fRec217[2];
	float fVec94[4096];
	float fRec215[2];
	float fVec95[4096];
	float fRec213[2];
	float fVec96[4096];
	float fRec211[2];
	float fVec97[4096];
	float fRec209[2];
	float fVec98[16384];
	float fRec135[2];
	float fRec236[3];
	float fRec235[3];
	float fVec99[4096];
	float fRec233[2];
	float fVec100[4096];
	float fRec231[2];
	float fVec101[4096];
	float fRec229[2];
	float fVec102[4096];
	float fRec227[2];
	float fVec103[4096];
	float fRec225[2];
	float fVec104[4096];
	float fRec223[2];
	float fVec105[16384];
	float fRec136[2];
	float fRec250[3];
	float fRec249[3];
	float fVec106[4096];
	float fRec247[2];
	float fVec107[4096];
	float fRec245[2];
	float fVec108[4096];
	float fRec243[2];
	float fVec109[4096];
	float fRec241[2];
	float fVec110[4096];
	float fRec239[2];
	float fVec111[4096];
	float fRec237[2];
	float fVec112[16384];
	float fRec137[2];
	float fRec129[3];
	float fRec251[3];
	
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
		for (int l138 = 0; (l138 < 3); l138 = (l138 + 1)) {
			fRec151[l138] = 0.0f;
			
		}
		for (int l139 = 0; (l139 < 3); l139 = (l139 + 1)) {
			fRec150[l139] = 0.0f;
			
		}
		for (int l140 = 0; (l140 < 4096); l140 = (l140 + 1)) {
			fVec57[l140] = 0.0f;
			
		}
		for (int l141 = 0; (l141 < 2); l141 = (l141 + 1)) {
			fRec148[l141] = 0.0f;
			
		}
		for (int l142 = 0; (l142 < 4096); l142 = (l142 + 1)) {
			fVec58[l142] = 0.0f;
			
		}
		for (int l143 = 0; (l143 < 2); l143 = (l143 + 1)) {
			fRec146[l143] = 0.0f;
			
		}
		for (int l144 = 0; (l144 < 4096); l144 = (l144 + 1)) {
			fVec59[l144] = 0.0f;
			
		}
		for (int l145 = 0; (l145 < 2); l145 = (l145 + 1)) {
			fRec144[l145] = 0.0f;
			
		}
		for (int l146 = 0; (l146 < 4096); l146 = (l146 + 1)) {
			fVec60[l146] = 0.0f;
			
		}
		for (int l147 = 0; (l147 < 2); l147 = (l147 + 1)) {
			fRec142[l147] = 0.0f;
			
		}
		for (int l148 = 0; (l148 < 4096); l148 = (l148 + 1)) {
			fVec61[l148] = 0.0f;
			
		}
		for (int l149 = 0; (l149 < 2); l149 = (l149 + 1)) {
			fRec140[l149] = 0.0f;
			
		}
		for (int l150 = 0; (l150 < 4096); l150 = (l150 + 1)) {
			fVec62[l150] = 0.0f;
			
		}
		for (int l151 = 0; (l151 < 2); l151 = (l151 + 1)) {
			fRec138[l151] = 0.0f;
			
		}
		for (int l152 = 0; (l152 < 16384); l152 = (l152 + 1)) {
			fVec63[l152] = 0.0f;
			
		}
		for (int l153 = 0; (l153 < 2); l153 = (l153 + 1)) {
			fRec130[l153] = 0.0f;
			
		}
		for (int l154 = 0; (l154 < 3); l154 = (l154 + 1)) {
			fRec165[l154] = 0.0f;
			
		}
		for (int l155 = 0; (l155 < 3); l155 = (l155 + 1)) {
			fRec164[l155] = 0.0f;
			
		}
		for (int l156 = 0; (l156 < 4096); l156 = (l156 + 1)) {
			fVec64[l156] = 0.0f;
			
		}
		for (int l157 = 0; (l157 < 2); l157 = (l157 + 1)) {
			fRec162[l157] = 0.0f;
			
		}
		for (int l158 = 0; (l158 < 4096); l158 = (l158 + 1)) {
			fVec65[l158] = 0.0f;
			
		}
		for (int l159 = 0; (l159 < 2); l159 = (l159 + 1)) {
			fRec160[l159] = 0.0f;
			
		}
		for (int l160 = 0; (l160 < 4096); l160 = (l160 + 1)) {
			fVec66[l160] = 0.0f;
			
		}
		for (int l161 = 0; (l161 < 2); l161 = (l161 + 1)) {
			fRec158[l161] = 0.0f;
			
		}
		for (int l162 = 0; (l162 < 4096); l162 = (l162 + 1)) {
			fVec67[l162] = 0.0f;
			
		}
		for (int l163 = 0; (l163 < 2); l163 = (l163 + 1)) {
			fRec156[l163] = 0.0f;
			
		}
		for (int l164 = 0; (l164 < 4096); l164 = (l164 + 1)) {
			fVec68[l164] = 0.0f;
			
		}
		for (int l165 = 0; (l165 < 2); l165 = (l165 + 1)) {
			fRec154[l165] = 0.0f;
			
		}
		for (int l166 = 0; (l166 < 4096); l166 = (l166 + 1)) {
			fVec69[l166] = 0.0f;
			
		}
		for (int l167 = 0; (l167 < 2); l167 = (l167 + 1)) {
			fRec152[l167] = 0.0f;
			
		}
		for (int l168 = 0; (l168 < 16384); l168 = (l168 + 1)) {
			fVec70[l168] = 0.0f;
			
		}
		for (int l169 = 0; (l169 < 2); l169 = (l169 + 1)) {
			fRec131[l169] = 0.0f;
			
		}
		for (int l170 = 0; (l170 < 3); l170 = (l170 + 1)) {
			fRec180[l170] = 0.0f;
			
		}
		for (int l171 = 0; (l171 < 3); l171 = (l171 + 1)) {
			fRec179[l171] = 0.0f;
			
		}
		for (int l172 = 0; (l172 < 4096); l172 = (l172 + 1)) {
			fVec71[l172] = 0.0f;
			
		}
		for (int l173 = 0; (l173 < 2); l173 = (l173 + 1)) {
			fRec177[l173] = 0.0f;
			
		}
		for (int l174 = 0; (l174 < 4096); l174 = (l174 + 1)) {
			fVec72[l174] = 0.0f;
			
		}
		for (int l175 = 0; (l175 < 2); l175 = (l175 + 1)) {
			fRec175[l175] = 0.0f;
			
		}
		for (int l176 = 0; (l176 < 4096); l176 = (l176 + 1)) {
			fVec73[l176] = 0.0f;
			
		}
		for (int l177 = 0; (l177 < 2); l177 = (l177 + 1)) {
			fRec173[l177] = 0.0f;
			
		}
		for (int l178 = 0; (l178 < 4096); l178 = (l178 + 1)) {
			fVec74[l178] = 0.0f;
			
		}
		for (int l179 = 0; (l179 < 2); l179 = (l179 + 1)) {
			fRec171[l179] = 0.0f;
			
		}
		for (int l180 = 0; (l180 < 4096); l180 = (l180 + 1)) {
			fVec75[l180] = 0.0f;
			
		}
		for (int l181 = 0; (l181 < 2); l181 = (l181 + 1)) {
			fRec169[l181] = 0.0f;
			
		}
		for (int l182 = 0; (l182 < 4096); l182 = (l182 + 1)) {
			fVec76[l182] = 0.0f;
			
		}
		for (int l183 = 0; (l183 < 2); l183 = (l183 + 1)) {
			fRec167[l183] = 0.0f;
			
		}
		for (int l184 = 0; (l184 < 16384); l184 = (l184 + 1)) {
			fVec77[l184] = 0.0f;
			
		}
		for (int l185 = 0; (l185 < 3); l185 = (l185 + 1)) {
			fRec166[l185] = 0.0f;
			
		}
		for (int l186 = 0; (l186 < 2); l186 = (l186 + 1)) {
			fRec132[l186] = 0.0f;
			
		}
		for (int l187 = 0; (l187 < 3); l187 = (l187 + 1)) {
			fRec194[l187] = 0.0f;
			
		}
		for (int l188 = 0; (l188 < 3); l188 = (l188 + 1)) {
			fRec193[l188] = 0.0f;
			
		}
		for (int l189 = 0; (l189 < 4096); l189 = (l189 + 1)) {
			fVec78[l189] = 0.0f;
			
		}
		for (int l190 = 0; (l190 < 2); l190 = (l190 + 1)) {
			fRec191[l190] = 0.0f;
			
		}
		for (int l191 = 0; (l191 < 4096); l191 = (l191 + 1)) {
			fVec79[l191] = 0.0f;
			
		}
		for (int l192 = 0; (l192 < 2); l192 = (l192 + 1)) {
			fRec189[l192] = 0.0f;
			
		}
		for (int l193 = 0; (l193 < 4096); l193 = (l193 + 1)) {
			fVec80[l193] = 0.0f;
			
		}
		for (int l194 = 0; (l194 < 2); l194 = (l194 + 1)) {
			fRec187[l194] = 0.0f;
			
		}
		for (int l195 = 0; (l195 < 4096); l195 = (l195 + 1)) {
			fVec81[l195] = 0.0f;
			
		}
		for (int l196 = 0; (l196 < 2); l196 = (l196 + 1)) {
			fRec185[l196] = 0.0f;
			
		}
		for (int l197 = 0; (l197 < 4096); l197 = (l197 + 1)) {
			fVec82[l197] = 0.0f;
			
		}
		for (int l198 = 0; (l198 < 2); l198 = (l198 + 1)) {
			fRec183[l198] = 0.0f;
			
		}
		for (int l199 = 0; (l199 < 4096); l199 = (l199 + 1)) {
			fVec83[l199] = 0.0f;
			
		}
		for (int l200 = 0; (l200 < 2); l200 = (l200 + 1)) {
			fRec181[l200] = 0.0f;
			
		}
		for (int l201 = 0; (l201 < 131072); l201 = (l201 + 1)) {
			fVec84[l201] = 0.0f;
			
		}
		for (int l202 = 0; (l202 < 2); l202 = (l202 + 1)) {
			fRec133[l202] = 0.0f;
			
		}
		for (int l203 = 0; (l203 < 3); l203 = (l203 + 1)) {
			fRec208[l203] = 0.0f;
			
		}
		for (int l204 = 0; (l204 < 3); l204 = (l204 + 1)) {
			fRec207[l204] = 0.0f;
			
		}
		for (int l205 = 0; (l205 < 4096); l205 = (l205 + 1)) {
			fVec85[l205] = 0.0f;
			
		}
		for (int l206 = 0; (l206 < 2); l206 = (l206 + 1)) {
			fRec205[l206] = 0.0f;
			
		}
		for (int l207 = 0; (l207 < 4096); l207 = (l207 + 1)) {
			fVec86[l207] = 0.0f;
			
		}
		for (int l208 = 0; (l208 < 2); l208 = (l208 + 1)) {
			fRec203[l208] = 0.0f;
			
		}
		for (int l209 = 0; (l209 < 4096); l209 = (l209 + 1)) {
			fVec87[l209] = 0.0f;
			
		}
		for (int l210 = 0; (l210 < 2); l210 = (l210 + 1)) {
			fRec201[l210] = 0.0f;
			
		}
		for (int l211 = 0; (l211 < 4096); l211 = (l211 + 1)) {
			fVec88[l211] = 0.0f;
			
		}
		for (int l212 = 0; (l212 < 2); l212 = (l212 + 1)) {
			fRec199[l212] = 0.0f;
			
		}
		for (int l213 = 0; (l213 < 4096); l213 = (l213 + 1)) {
			fVec89[l213] = 0.0f;
			
		}
		for (int l214 = 0; (l214 < 2); l214 = (l214 + 1)) {
			fRec197[l214] = 0.0f;
			
		}
		for (int l215 = 0; (l215 < 4096); l215 = (l215 + 1)) {
			fVec90[l215] = 0.0f;
			
		}
		for (int l216 = 0; (l216 < 2); l216 = (l216 + 1)) {
			fRec195[l216] = 0.0f;
			
		}
		for (int l217 = 0; (l217 < 16384); l217 = (l217 + 1)) {
			fVec91[l217] = 0.0f;
			
		}
		for (int l218 = 0; (l218 < 2); l218 = (l218 + 1)) {
			fRec134[l218] = 0.0f;
			
		}
		for (int l219 = 0; (l219 < 3); l219 = (l219 + 1)) {
			fRec222[l219] = 0.0f;
			
		}
		for (int l220 = 0; (l220 < 3); l220 = (l220 + 1)) {
			fRec221[l220] = 0.0f;
			
		}
		for (int l221 = 0; (l221 < 4096); l221 = (l221 + 1)) {
			fVec92[l221] = 0.0f;
			
		}
		for (int l222 = 0; (l222 < 2); l222 = (l222 + 1)) {
			fRec219[l222] = 0.0f;
			
		}
		for (int l223 = 0; (l223 < 4096); l223 = (l223 + 1)) {
			fVec93[l223] = 0.0f;
			
		}
		for (int l224 = 0; (l224 < 2); l224 = (l224 + 1)) {
			fRec217[l224] = 0.0f;
			
		}
		for (int l225 = 0; (l225 < 4096); l225 = (l225 + 1)) {
			fVec94[l225] = 0.0f;
			
		}
		for (int l226 = 0; (l226 < 2); l226 = (l226 + 1)) {
			fRec215[l226] = 0.0f;
			
		}
		for (int l227 = 0; (l227 < 4096); l227 = (l227 + 1)) {
			fVec95[l227] = 0.0f;
			
		}
		for (int l228 = 0; (l228 < 2); l228 = (l228 + 1)) {
			fRec213[l228] = 0.0f;
			
		}
		for (int l229 = 0; (l229 < 4096); l229 = (l229 + 1)) {
			fVec96[l229] = 0.0f;
			
		}
		for (int l230 = 0; (l230 < 2); l230 = (l230 + 1)) {
			fRec211[l230] = 0.0f;
			
		}
		for (int l231 = 0; (l231 < 4096); l231 = (l231 + 1)) {
			fVec97[l231] = 0.0f;
			
		}
		for (int l232 = 0; (l232 < 2); l232 = (l232 + 1)) {
			fRec209[l232] = 0.0f;
			
		}
		for (int l233 = 0; (l233 < 16384); l233 = (l233 + 1)) {
			fVec98[l233] = 0.0f;
			
		}
		for (int l234 = 0; (l234 < 2); l234 = (l234 + 1)) {
			fRec135[l234] = 0.0f;
			
		}
		for (int l235 = 0; (l235 < 3); l235 = (l235 + 1)) {
			fRec236[l235] = 0.0f;
			
		}
		for (int l236 = 0; (l236 < 3); l236 = (l236 + 1)) {
			fRec235[l236] = 0.0f;
			
		}
		for (int l237 = 0; (l237 < 4096); l237 = (l237 + 1)) {
			fVec99[l237] = 0.0f;
			
		}
		for (int l238 = 0; (l238 < 2); l238 = (l238 + 1)) {
			fRec233[l238] = 0.0f;
			
		}
		for (int l239 = 0; (l239 < 4096); l239 = (l239 + 1)) {
			fVec100[l239] = 0.0f;
			
		}
		for (int l240 = 0; (l240 < 2); l240 = (l240 + 1)) {
			fRec231[l240] = 0.0f;
			
		}
		for (int l241 = 0; (l241 < 4096); l241 = (l241 + 1)) {
			fVec101[l241] = 0.0f;
			
		}
		for (int l242 = 0; (l242 < 2); l242 = (l242 + 1)) {
			fRec229[l242] = 0.0f;
			
		}
		for (int l243 = 0; (l243 < 4096); l243 = (l243 + 1)) {
			fVec102[l243] = 0.0f;
			
		}
		for (int l244 = 0; (l244 < 2); l244 = (l244 + 1)) {
			fRec227[l244] = 0.0f;
			
		}
		for (int l245 = 0; (l245 < 4096); l245 = (l245 + 1)) {
			fVec103[l245] = 0.0f;
			
		}
		for (int l246 = 0; (l246 < 2); l246 = (l246 + 1)) {
			fRec225[l246] = 0.0f;
			
		}
		for (int l247 = 0; (l247 < 4096); l247 = (l247 + 1)) {
			fVec104[l247] = 0.0f;
			
		}
		for (int l248 = 0; (l248 < 2); l248 = (l248 + 1)) {
			fRec223[l248] = 0.0f;
			
		}
		for (int l249 = 0; (l249 < 16384); l249 = (l249 + 1)) {
			fVec105[l249] = 0.0f;
			
		}
		for (int l250 = 0; (l250 < 2); l250 = (l250 + 1)) {
			fRec136[l250] = 0.0f;
			
		}
		for (int l251 = 0; (l251 < 3); l251 = (l251 + 1)) {
			fRec250[l251] = 0.0f;
			
		}
		for (int l252 = 0; (l252 < 3); l252 = (l252 + 1)) {
			fRec249[l252] = 0.0f;
			
		}
		for (int l253 = 0; (l253 < 4096); l253 = (l253 + 1)) {
			fVec106[l253] = 0.0f;
			
		}
		for (int l254 = 0; (l254 < 2); l254 = (l254 + 1)) {
			fRec247[l254] = 0.0f;
			
		}
		for (int l255 = 0; (l255 < 4096); l255 = (l255 + 1)) {
			fVec107[l255] = 0.0f;
			
		}
		for (int l256 = 0; (l256 < 2); l256 = (l256 + 1)) {
			fRec245[l256] = 0.0f;
			
		}
		for (int l257 = 0; (l257 < 4096); l257 = (l257 + 1)) {
			fVec108[l257] = 0.0f;
			
		}
		for (int l258 = 0; (l258 < 2); l258 = (l258 + 1)) {
			fRec243[l258] = 0.0f;
			
		}
		for (int l259 = 0; (l259 < 4096); l259 = (l259 + 1)) {
			fVec109[l259] = 0.0f;
			
		}
		for (int l260 = 0; (l260 < 2); l260 = (l260 + 1)) {
			fRec241[l260] = 0.0f;
			
		}
		for (int l261 = 0; (l261 < 4096); l261 = (l261 + 1)) {
			fVec110[l261] = 0.0f;
			
		}
		for (int l262 = 0; (l262 < 2); l262 = (l262 + 1)) {
			fRec239[l262] = 0.0f;
			
		}
		for (int l263 = 0; (l263 < 4096); l263 = (l263 + 1)) {
			fVec111[l263] = 0.0f;
			
		}
		for (int l264 = 0; (l264 < 2); l264 = (l264 + 1)) {
			fRec237[l264] = 0.0f;
			
		}
		for (int l265 = 0; (l265 < 16384); l265 = (l265 + 1)) {
			fVec112[l265] = 0.0f;
			
		}
		for (int l266 = 0; (l266 < 2); l266 = (l266 + 1)) {
			fRec137[l266] = 0.0f;
			
		}
		for (int l267 = 0; (l267 < 3); l267 = (l267 + 1)) {
			fRec129[l267] = 0.0f;
			
		}
		for (int l268 = 0; (l268 < 3); l268 = (l268 + 1)) {
			fRec251[l268] = 0.0f;
			
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
		ui_interface->addHorizontalSlider("DECAY", &fHslider1, 0.5f, 0.0500000007f, 1.0f, 0.00999999978f);
		ui_interface->addHorizontalSlider("MIX", &fHslider0, 0.5f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface->addHorizontalSlider("SHIMMER", &fHslider3, 0.0f, 0.0f, 1.20000005f, 0.00999999978f);
		ui_interface->declare(&fHslider2, "scale", "log");
		ui_interface->addHorizontalSlider("TONE", &fHslider2, 4000.0f, 100.0f, 14000.0f, 0.00999999978f);
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
			float fTemp9 = float(input0[i]);
			float fTemp10 = (((0.600000024f * fRec19[1]) + ((fRec21[2] + (fRec21[0] + (2.0f * fRec21[1]))) / fTemp8)) + fTemp9);
			fVec1[(IOTA & 4095)] = fTemp10;
			fRec26[0] = (fRec26[1] + (fConst2 * (0.0f - fRec24[1])));
			fRec25[0] = ((fRec25[1] + (fConst2 * fRec26[0])) + float((1 - iVec0[1])));
			fRec24[0] = fRec25[0];
			float fTemp11 = ((0.00100000005f * fRec24[0]) + 1.0f);
			float fTemp12 = (343.0f * fTemp11);
			float fTemp13 = (fTemp12 + -1.0f);
			int iTemp14 = int(fTemp13);
			int iTemp15 = min(2049, max(0, iTemp14));
			float fTemp16 = floorf(fTemp13);
			float fTemp17 = (fTemp16 + (2.0f - fTemp12));
			float fTemp18 = (fTemp12 + (-1.0f - fTemp16));
			int iTemp19 = min(2049, max(0, (iTemp14 + 1)));
			fRec19[0] = ((fVec1[((IOTA - iTemp15) & 4095)] * fTemp17) + (fTemp18 * fVec1[((IOTA - iTemp19) & 4095)]));
			float fRec20 = (0.0f - (0.600000024f * fTemp10));
			float fTemp20 = (fRec19[1] + (fRec20 + (0.600000024f * fRec17[1])));
			fVec2[(IOTA & 4095)] = fTemp20;
			float fTemp21 = (441.0f * fTemp11);
			float fTemp22 = (fTemp21 + -1.0f);
			int iTemp23 = int(fTemp22);
			int iTemp24 = min(2049, max(0, iTemp23));
			float fTemp25 = floorf(fTemp22);
			float fTemp26 = (fTemp25 + (2.0f - fTemp21));
			float fTemp27 = (fTemp21 + (-1.0f - fTemp25));
			int iTemp28 = min(2049, max(0, (iTemp23 + 1)));
			fRec17[0] = ((fVec2[((IOTA - iTemp24) & 4095)] * fTemp26) + (fTemp27 * fVec2[((IOTA - iTemp28) & 4095)]));
			float fRec18 = (0.0f - (0.600000024f * fTemp20));
			float fTemp29 = (fRec17[1] + (fRec18 + (0.600000024f * fRec15[1])));
			fVec3[(IOTA & 4095)] = fTemp29;
			float fTemp30 = (625.0f * fTemp11);
			float fTemp31 = (fTemp30 + -1.0f);
			int iTemp32 = int(fTemp31);
			int iTemp33 = min(2049, max(0, iTemp32));
			float fTemp34 = floorf(fTemp31);
			float fTemp35 = (fTemp34 + (2.0f - fTemp30));
			float fTemp36 = (fTemp30 + (-1.0f - fTemp34));
			int iTemp37 = min(2049, max(0, (iTemp32 + 1)));
			fRec15[0] = ((fVec3[((IOTA - iTemp33) & 4095)] * fTemp35) + (fTemp36 * fVec3[((IOTA - iTemp37) & 4095)]));
			float fRec16 = (0.0f - (0.600000024f * fTemp29));
			float fTemp38 = (fRec15[1] + (fRec16 + (0.600000024f * fRec13[1])));
			fVec4[(IOTA & 4095)] = fTemp38;
			float fTemp39 = (727.0f * fTemp11);
			float fTemp40 = (fTemp39 + -1.0f);
			int iTemp41 = int(fTemp40);
			int iTemp42 = min(2049, max(0, iTemp41));
			float fTemp43 = floorf(fTemp40);
			float fTemp44 = (fTemp43 + (2.0f - fTemp39));
			float fTemp45 = (fTemp39 + (-1.0f - fTemp43));
			int iTemp46 = min(2049, max(0, (iTemp41 + 1)));
			fRec13[0] = ((fVec4[((IOTA - iTemp42) & 4095)] * fTemp44) + (fTemp45 * fVec4[((IOTA - iTemp46) & 4095)]));
			float fRec14 = (0.0f - (0.600000024f * fTemp38));
			float fTemp47 = (fRec13[1] + (fRec14 + (0.600000024f * fRec11[1])));
			fVec5[(IOTA & 4095)] = fTemp47;
			float fTemp48 = (1331.0f * fTemp11);
			float fTemp49 = (fTemp48 + -1.0f);
			int iTemp50 = int(fTemp49);
			int iTemp51 = min(2049, max(0, iTemp50));
			float fTemp52 = floorf(fTemp49);
			float fTemp53 = (fTemp52 + (2.0f - fTemp48));
			float fTemp54 = (fTemp48 + (-1.0f - fTemp52));
			int iTemp55 = min(2049, max(0, (iTemp50 + 1)));
			fRec11[0] = ((fVec5[((IOTA - iTemp51) & 4095)] * fTemp53) + (fTemp54 * fVec5[((IOTA - iTemp55) & 4095)]));
			float fRec12 = (0.0f - (0.600000024f * fTemp47));
			float fTemp56 = (fRec11[1] + (fRec12 + (0.600000024f * fRec9[1])));
			fVec6[(IOTA & 4095)] = fTemp56;
			float fTemp57 = (2403.0f * fTemp11);
			float fTemp58 = (fTemp57 + -1.0f);
			int iTemp59 = int(fTemp58);
			int iTemp60 = min(2049, max(0, iTemp59));
			float fTemp61 = floorf(fTemp58);
			float fTemp62 = (fTemp61 + (2.0f - fTemp57));
			float fTemp63 = (fTemp57 + (-1.0f - fTemp61));
			int iTemp64 = min(2049, max(0, (iTemp59 + 1)));
			fRec9[0] = ((fVec6[((IOTA - iTemp60) & 4095)] * fTemp62) + (fTemp63 * fVec6[((IOTA - iTemp64) & 4095)]));
			float fRec10 = (0.0f - (0.600000024f * fTemp56));
			float fTemp65 = (fRec10 + fRec9[1]);
			fVec7[(IOTA & 16383)] = fTemp65;
			float fTemp66 = (1356.0f * fTemp11);
			int iTemp67 = int(fTemp66);
			int iTemp68 = min(8193, max(0, iTemp67));
			float fTemp69 = floorf(fTemp66);
			float fTemp70 = (fTemp69 + (1.0f - fTemp66));
			float fTemp71 = (fTemp66 - fTemp69);
			int iTemp72 = min(8193, max(0, (iTemp67 + 1)));
			fRec1[0] = (0.353553385f * ((fVec7[((IOTA - iTemp68) & 16383)] * fTemp70) + (fTemp71 * fVec7[((IOTA - iTemp72) & 16383)])));
			fRec40[0] = ((fSlow1 * (fTemp1 - (fRec8[1] + ((fRec2[1] + fRec6[1]) + fRec4[1])))) - (((fTemp4 * fRec40[2]) + (2.0f * (fTemp5 * fRec40[1]))) / fTemp6));
			fRec39[0] = (((fRec40[2] + (fRec40[0] + (2.0f * fRec40[1]))) / fTemp6) - (((fTemp7 * fRec39[2]) + (2.0f * (fTemp5 * fRec39[1]))) / fTemp8));
			float fTemp73 = (((0.600000024f * fRec37[1]) + ((fRec39[2] + (fRec39[0] + (2.0f * fRec39[1]))) / fTemp8)) + fTemp9);
			fVec8[(IOTA & 4095)] = fTemp73;
			fRec37[0] = ((fTemp17 * fVec8[((IOTA - iTemp15) & 4095)]) + (fTemp18 * fVec8[((IOTA - iTemp19) & 4095)]));
			float fRec38 = (0.0f - (0.600000024f * fTemp73));
			float fTemp74 = (fRec37[1] + (fRec38 + (0.600000024f * fRec35[1])));
			fVec9[(IOTA & 4095)] = fTemp74;
			fRec35[0] = ((fTemp26 * fVec9[((IOTA - iTemp24) & 4095)]) + (fTemp27 * fVec9[((IOTA - iTemp28) & 4095)]));
			float fRec36 = (0.0f - (0.600000024f * fTemp74));
			float fTemp75 = (fRec35[1] + (fRec36 + (0.600000024f * fRec33[1])));
			fVec10[(IOTA & 4095)] = fTemp75;
			fRec33[0] = ((fTemp35 * fVec10[((IOTA - iTemp33) & 4095)]) + (fTemp36 * fVec10[((IOTA - iTemp37) & 4095)]));
			float fRec34 = (0.0f - (0.600000024f * fTemp75));
			float fTemp76 = (fRec33[1] + (fRec34 + (0.600000024f * fRec31[1])));
			fVec11[(IOTA & 4095)] = fTemp76;
			fRec31[0] = ((fTemp44 * fVec11[((IOTA - iTemp42) & 4095)]) + (fTemp45 * fVec11[((IOTA - iTemp46) & 4095)]));
			float fRec32 = (0.0f - (0.600000024f * fTemp76));
			float fTemp77 = (fRec31[1] + (fRec32 + (0.600000024f * fRec29[1])));
			fVec12[(IOTA & 4095)] = fTemp77;
			fRec29[0] = ((fTemp53 * fVec12[((IOTA - iTemp51) & 4095)]) + (fTemp54 * fVec12[((IOTA - iTemp55) & 4095)]));
			float fRec30 = (0.0f - (0.600000024f * fTemp77));
			float fTemp78 = (fRec29[1] + (fRec30 + (0.600000024f * fRec27[1])));
			fVec13[(IOTA & 4095)] = fTemp78;
			fRec27[0] = ((fTemp62 * fVec13[((IOTA - iTemp60) & 4095)]) + (fTemp63 * fVec13[((IOTA - iTemp64) & 4095)]));
			float fRec28 = (0.0f - (0.600000024f * fTemp78));
			float fTemp79 = (fRec28 + fRec27[1]);
			fVec14[(IOTA & 16383)] = fTemp79;
			float fTemp80 = (1422.0f * fTemp11);
			int iTemp81 = int(fTemp80);
			int iTemp82 = min(8193, max(0, iTemp81));
			float fTemp83 = floorf(fTemp80);
			float fTemp84 = (fTemp83 + (1.0f - fTemp80));
			float fTemp85 = (fTemp80 - fTemp83);
			int iTemp86 = min(8193, max(0, (iTemp81 + 1)));
			fRec2[0] = (0.353553385f * ((fVec14[((IOTA - iTemp82) & 16383)] * fTemp84) + (fTemp85 * fVec14[((IOTA - iTemp86) & 16383)])));
			float fTemp87 = (fRec3[1] + fRec7[1]);
			fRec55[0] = ((fSlow1 * ((fRec6[1] + (fTemp0 + fRec2[1])) - (fRec8[1] + (fTemp87 + fRec4[1])))) - (((fTemp4 * fRec55[2]) + (2.0f * (fTemp5 * fRec55[1]))) / fTemp6));
			fRec54[0] = (((fRec55[2] + (fRec55[0] + (2.0f * fRec55[1]))) / fTemp6) - (((fTemp7 * fRec54[2]) + (2.0f * (fTemp5 * fRec54[1]))) / fTemp8));
			float fTemp88 = (((0.600000024f * fRec52[1]) + ((fRec54[2] + (fRec54[0] + (2.0f * fRec54[1]))) / fTemp8)) + fTemp9);
			fVec15[(IOTA & 4095)] = fTemp88;
			fRec52[0] = ((fTemp17 * fVec15[((IOTA - iTemp15) & 4095)]) + (fTemp18 * fVec15[((IOTA - iTemp19) & 4095)]));
			float fRec53 = (0.0f - (0.600000024f * fTemp88));
			float fTemp89 = (fRec52[1] + (fRec53 + (0.600000024f * fRec50[1])));
			fVec16[(IOTA & 4095)] = fTemp89;
			fRec50[0] = ((fTemp26 * fVec16[((IOTA - iTemp24) & 4095)]) + (fTemp27 * fVec16[((IOTA - iTemp28) & 4095)]));
			float fRec51 = (0.0f - (0.600000024f * fTemp89));
			float fTemp90 = (fRec50[1] + (fRec51 + (0.600000024f * fRec48[1])));
			fVec17[(IOTA & 4095)] = fTemp90;
			fRec48[0] = ((fTemp35 * fVec17[((IOTA - iTemp33) & 4095)]) + (fTemp36 * fVec17[((IOTA - iTemp37) & 4095)]));
			float fRec49 = (0.0f - (0.600000024f * fTemp90));
			float fTemp91 = (fRec48[1] + (fRec49 + (0.600000024f * fRec46[1])));
			fVec18[(IOTA & 4095)] = fTemp91;
			fRec46[0] = ((fTemp44 * fVec18[((IOTA - iTemp42) & 4095)]) + (fTemp45 * fVec18[((IOTA - iTemp46) & 4095)]));
			float fRec47 = (0.0f - (0.600000024f * fTemp91));
			float fTemp92 = (fRec46[1] + (fRec47 + (0.600000024f * fRec44[1])));
			fVec19[(IOTA & 4095)] = fTemp92;
			fRec44[0] = ((fTemp53 * fVec19[((IOTA - iTemp51) & 4095)]) + (fTemp54 * fVec19[((IOTA - iTemp55) & 4095)]));
			float fRec45 = (0.0f - (0.600000024f * fTemp92));
			float fTemp93 = (fRec44[1] + (fRec45 + (0.600000024f * fRec42[1])));
			fVec20[(IOTA & 4095)] = fTemp93;
			fRec42[0] = ((fTemp62 * fVec20[((IOTA - iTemp60) & 4095)]) + (fTemp63 * fVec20[((IOTA - iTemp64) & 4095)]));
			float fRec43 = (0.0f - (0.600000024f * fTemp93));
			float fTemp94 = (fRec43 + fRec42[1]);
			fVec21[(IOTA & 16383)] = fTemp94;
			float fTemp95 = (1557.0f * fTemp11);
			int iTemp96 = int(fTemp95);
			int iTemp97 = min(8193, max(0, iTemp96));
			float fTemp98 = floorf(fTemp95);
			float fTemp99 = (fTemp98 + (1.0f - fTemp95));
			float fTemp100 = (fTemp95 - fTemp98);
			int iTemp101 = min(8193, max(0, (iTemp96 + 1)));
			fRec41[0] = ((0.353553385f * ((fVec21[((IOTA - iTemp97) & 16383)] * fTemp99) + (fTemp100 * fVec21[((IOTA - iTemp101) & 16383)]))) - (fConst5 * ((fConst7 * fRec41[2]) + (fConst8 * fRec41[1]))));
			fRec3[0] = (fConst5 * (((fConst6 * fRec41[0]) + (fConst9 * fRec41[1])) + (fConst6 * fRec41[2])));
			fRec69[0] = ((fSlow1 * ((fRec8[1] + (fTemp0 + fRec4[1])) - (fRec6[1] + (fTemp87 + fRec2[1])))) - (((fTemp4 * fRec69[2]) + (2.0f * (fTemp5 * fRec69[1]))) / fTemp6));
			fRec68[0] = (((fRec69[2] + (fRec69[0] + (2.0f * fRec69[1]))) / fTemp6) - (((fTemp7 * fRec68[2]) + (2.0f * (fTemp5 * fRec68[1]))) / fTemp8));
			float fTemp102 = (((0.600000024f * fRec66[1]) + ((fRec68[2] + (fRec68[0] + (2.0f * fRec68[1]))) / fTemp8)) + fTemp9);
			fVec22[(IOTA & 4095)] = fTemp102;
			fRec66[0] = ((fTemp17 * fVec22[((IOTA - iTemp15) & 4095)]) + (fTemp18 * fVec22[((IOTA - iTemp19) & 4095)]));
			float fRec67 = (0.0f - (0.600000024f * fTemp102));
			float fTemp103 = (fRec66[1] + (fRec67 + (0.600000024f * fRec64[1])));
			fVec23[(IOTA & 4095)] = fTemp103;
			fRec64[0] = ((fTemp26 * fVec23[((IOTA - iTemp24) & 4095)]) + (fTemp27 * fVec23[((IOTA - iTemp28) & 4095)]));
			float fRec65 = (0.0f - (0.600000024f * fTemp103));
			float fTemp104 = (fRec64[1] + (fRec65 + (0.600000024f * fRec62[1])));
			fVec24[(IOTA & 4095)] = fTemp104;
			fRec62[0] = ((fTemp35 * fVec24[((IOTA - iTemp33) & 4095)]) + (fTemp36 * fVec24[((IOTA - iTemp37) & 4095)]));
			float fRec63 = (0.0f - (0.600000024f * fTemp104));
			float fTemp105 = (fRec62[1] + (fRec63 + (0.600000024f * fRec60[1])));
			fVec25[(IOTA & 4095)] = fTemp105;
			fRec60[0] = ((fTemp44 * fVec25[((IOTA - iTemp42) & 4095)]) + (fTemp45 * fVec25[((IOTA - iTemp46) & 4095)]));
			float fRec61 = (0.0f - (0.600000024f * fTemp105));
			float fTemp106 = (fRec60[1] + (fRec61 + (0.600000024f * fRec58[1])));
			fVec26[(IOTA & 4095)] = fTemp106;
			fRec58[0] = ((fTemp53 * fVec26[((IOTA - iTemp51) & 4095)]) + (fTemp54 * fVec26[((IOTA - iTemp55) & 4095)]));
			float fRec59 = (0.0f - (0.600000024f * fTemp106));
			float fTemp107 = (fRec58[1] + (fRec59 + (0.600000024f * fRec56[1])));
			fVec27[(IOTA & 4095)] = fTemp107;
			fRec56[0] = ((fTemp62 * fVec27[((IOTA - iTemp60) & 4095)]) + (fTemp63 * fVec27[((IOTA - iTemp64) & 4095)]));
			float fRec57 = (0.0f - (0.600000024f * fTemp107));
			float fTemp108 = (fRec57 + fRec56[1]);
			fVec28[(IOTA & 131071)] = fTemp108;
			float fTemp109 = (1617.0f * fTemp11);
			float fTemp110 = (fTemp109 + 8192.0f);
			int iTemp111 = int(min(8192.0f, max(0.0f, fTemp110)));
			fRec70[0] = fmodf(((fTemp109 + fRec70[1]) + 8191.0f), fTemp110);
			int iTemp112 = int(fRec70[0]);
			int iTemp113 = min(65537, max(0, iTemp112));
			float fTemp114 = floorf(fRec70[0]);
			float fTemp115 = (fTemp114 + (1.0f - fRec70[0]));
			float fTemp116 = (fRec70[0] - fTemp114);
			int iTemp117 = min(65537, max(0, (iTemp112 + 1)));
			fRec71[0] = fmodf(((fTemp109 + fRec71[1]) + 8191.0f), fTemp110);
			float fTemp118 = min((fRec71[0] / fTemp110), 1.0f);
			float fTemp119 = (fRec70[0] + fTemp109);
			float fTemp120 = (fTemp119 + 8192.0f);
			int iTemp121 = int(fTemp120);
			int iTemp122 = min(65537, max(0, iTemp121));
			float fTemp123 = floorf(fTemp120);
			float fTemp124 = (fTemp123 + (-8191.0f - fTemp119));
			float fTemp125 = (fTemp119 + (8192.0f - fTemp123));
			int iTemp126 = min(65537, max(0, (iTemp121 + 1)));
			float fTemp127 = (1.0f - fTemp118);
			fRec4[0] = (0.353553385f * ((fSlow4 * fVec28[((IOTA - iTemp111) & 131071)]) + (fSlow3 * ((((fVec28[((IOTA - iTemp113) & 131071)] * fTemp115) + (fTemp116 * fVec28[((IOTA - iTemp117) & 131071)])) * fTemp118) + (((fVec28[((IOTA - iTemp122) & 131071)] * fTemp124) + (fTemp125 * fVec28[((IOTA - iTemp126) & 131071)])) * fTemp127)))));
			float fTemp128 = (fRec1[1] + fRec3[1]);
			float fTemp129 = (fRec5[1] + fRec7[1]);
			fRec85[0] = ((fSlow1 * ((fRec4[1] + (fRec2[1] + fTemp128)) - (fRec8[1] + (fRec6[1] + fTemp129)))) - (((fTemp4 * fRec85[2]) + (2.0f * (fTemp5 * fRec85[1]))) / fTemp6));
			fRec84[0] = (((fRec85[2] + (fRec85[0] + (2.0f * fRec85[1]))) / fTemp6) - (((fTemp7 * fRec84[2]) + (2.0f * (fTemp5 * fRec84[1]))) / fTemp8));
			float fTemp130 = (((0.600000024f * fRec82[1]) + ((fRec84[2] + (fRec84[0] + (2.0f * fRec84[1]))) / fTemp8)) + fTemp9);
			fVec29[(IOTA & 4095)] = fTemp130;
			fRec82[0] = ((fTemp17 * fVec29[((IOTA - iTemp15) & 4095)]) + (fTemp18 * fVec29[((IOTA - iTemp19) & 4095)]));
			float fRec83 = (0.0f - (0.600000024f * fTemp130));
			float fTemp131 = (fRec82[1] + (fRec83 + (0.600000024f * fRec80[1])));
			fVec30[(IOTA & 4095)] = fTemp131;
			fRec80[0] = ((fTemp26 * fVec30[((IOTA - iTemp24) & 4095)]) + (fTemp27 * fVec30[((IOTA - iTemp28) & 4095)]));
			float fRec81 = (0.0f - (0.600000024f * fTemp131));
			float fTemp132 = (fRec80[1] + (fRec81 + (0.600000024f * fRec78[1])));
			fVec31[(IOTA & 4095)] = fTemp132;
			fRec78[0] = ((fTemp35 * fVec31[((IOTA - iTemp33) & 4095)]) + (fTemp36 * fVec31[((IOTA - iTemp37) & 4095)]));
			float fRec79 = (0.0f - (0.600000024f * fTemp132));
			float fTemp133 = (fRec78[1] + (fRec79 + (0.600000024f * fRec76[1])));
			fVec32[(IOTA & 4095)] = fTemp133;
			fRec76[0] = ((fTemp44 * fVec32[((IOTA - iTemp42) & 4095)]) + (fTemp45 * fVec32[((IOTA - iTemp46) & 4095)]));
			float fRec77 = (0.0f - (0.600000024f * fTemp133));
			float fTemp134 = (fRec76[1] + (fRec77 + (0.600000024f * fRec74[1])));
			fVec33[(IOTA & 4095)] = fTemp134;
			fRec74[0] = ((fTemp53 * fVec33[((IOTA - iTemp51) & 4095)]) + (fTemp54 * fVec33[((IOTA - iTemp55) & 4095)]));
			float fRec75 = (0.0f - (0.600000024f * fTemp134));
			float fTemp135 = (fRec74[1] + (fRec75 + (0.600000024f * fRec72[1])));
			fVec34[(IOTA & 4095)] = fTemp135;
			fRec72[0] = ((fTemp62 * fVec34[((IOTA - iTemp60) & 4095)]) + (fTemp63 * fVec34[((IOTA - iTemp64) & 4095)]));
			float fRec73 = (0.0f - (0.600000024f * fTemp135));
			float fTemp136 = (fRec73 + fRec72[1]);
			fVec35[(IOTA & 16383)] = fTemp136;
			float fTemp137 = (1933.0f * fTemp11);
			int iTemp138 = int(fTemp137);
			int iTemp139 = min(8193, max(0, iTemp138));
			float fTemp140 = floorf(fTemp137);
			float fTemp141 = (fTemp140 + (1.0f - fTemp137));
			float fTemp142 = (fTemp137 - fTemp140);
			int iTemp143 = min(8193, max(0, (iTemp138 + 1)));
			fRec5[0] = (0.353553385f * ((fVec35[((IOTA - iTemp139) & 16383)] * fTemp141) + (fTemp142 * fVec35[((IOTA - iTemp143) & 16383)])));
			fRec99[0] = ((fSlow1 * ((fRec8[1] + (fRec6[1] + fTemp128)) - (fRec4[1] + (fRec2[1] + fTemp129)))) - (((fTemp4 * fRec99[2]) + (2.0f * (fTemp5 * fRec99[1]))) / fTemp6));
			fRec98[0] = (((fRec99[2] + (fRec99[0] + (2.0f * fRec99[1]))) / fTemp6) - (((fTemp7 * fRec98[2]) + (2.0f * (fTemp5 * fRec98[1]))) / fTemp8));
			float fTemp144 = (((0.600000024f * fRec96[1]) + ((fRec98[2] + (fRec98[0] + (2.0f * fRec98[1]))) / fTemp8)) + fTemp9);
			fVec36[(IOTA & 4095)] = fTemp144;
			fRec96[0] = ((fTemp17 * fVec36[((IOTA - iTemp15) & 4095)]) + (fTemp18 * fVec36[((IOTA - iTemp19) & 4095)]));
			float fRec97 = (0.0f - (0.600000024f * fTemp144));
			float fTemp145 = (fRec96[1] + (fRec97 + (0.600000024f * fRec94[1])));
			fVec37[(IOTA & 4095)] = fTemp145;
			fRec94[0] = ((fTemp26 * fVec37[((IOTA - iTemp24) & 4095)]) + (fTemp27 * fVec37[((IOTA - iTemp28) & 4095)]));
			float fRec95 = (0.0f - (0.600000024f * fTemp145));
			float fTemp146 = (fRec94[1] + (fRec95 + (0.600000024f * fRec92[1])));
			fVec38[(IOTA & 4095)] = fTemp146;
			fRec92[0] = ((fTemp35 * fVec38[((IOTA - iTemp33) & 4095)]) + (fTemp36 * fVec38[((IOTA - iTemp37) & 4095)]));
			float fRec93 = (0.0f - (0.600000024f * fTemp146));
			float fTemp147 = (fRec92[1] + (fRec93 + (0.600000024f * fRec90[1])));
			fVec39[(IOTA & 4095)] = fTemp147;
			fRec90[0] = ((fTemp44 * fVec39[((IOTA - iTemp42) & 4095)]) + (fTemp45 * fVec39[((IOTA - iTemp46) & 4095)]));
			float fRec91 = (0.0f - (0.600000024f * fTemp147));
			float fTemp148 = (fRec90[1] + (fRec91 + (0.600000024f * fRec88[1])));
			fVec40[(IOTA & 4095)] = fTemp148;
			fRec88[0] = ((fTemp53 * fVec40[((IOTA - iTemp51) & 4095)]) + (fTemp54 * fVec40[((IOTA - iTemp55) & 4095)]));
			float fRec89 = (0.0f - (0.600000024f * fTemp148));
			float fTemp149 = (fRec88[1] + (fRec89 + (0.600000024f * fRec86[1])));
			fVec41[(IOTA & 4095)] = fTemp149;
			fRec86[0] = ((fTemp62 * fVec41[((IOTA - iTemp60) & 4095)]) + (fTemp63 * fVec41[((IOTA - iTemp64) & 4095)]));
			float fRec87 = (0.0f - (0.600000024f * fTemp149));
			float fTemp150 = (fRec87 + fRec86[1]);
			fVec42[(IOTA & 16383)] = fTemp150;
			float fTemp151 = (2401.0f * fTemp11);
			int iTemp152 = int(fTemp151);
			int iTemp153 = min(8193, max(0, iTemp152));
			float fTemp154 = floorf(fTemp151);
			float fTemp155 = (fTemp154 + (1.0f - fTemp151));
			float fTemp156 = (fTemp151 - fTemp154);
			int iTemp157 = min(8193, max(0, (iTemp152 + 1)));
			fRec6[0] = (0.353553385f * ((fVec42[((IOTA - iTemp153) & 16383)] * fTemp155) + (fTemp156 * fVec42[((IOTA - iTemp157) & 16383)])));
			float fTemp158 = (fRec1[1] + fRec7[1]);
			float fTemp159 = (fRec5[1] + fRec3[1]);
			fRec113[0] = ((fSlow1 * ((fRec8[1] + (fRec2[1] + fTemp158)) - (fRec4[1] + (fRec6[1] + fTemp159)))) - (((fTemp4 * fRec113[2]) + (2.0f * (fTemp5 * fRec113[1]))) / fTemp6));
			fRec112[0] = (((fRec113[2] + (fRec113[0] + (2.0f * fRec113[1]))) / fTemp6) - (((fTemp7 * fRec112[2]) + (2.0f * (fTemp5 * fRec112[1]))) / fTemp8));
			float fTemp160 = (((0.600000024f * fRec110[1]) + ((fRec112[2] + (fRec112[0] + (2.0f * fRec112[1]))) / fTemp8)) + fTemp9);
			fVec43[(IOTA & 4095)] = fTemp160;
			fRec110[0] = ((fTemp17 * fVec43[((IOTA - iTemp15) & 4095)]) + (fTemp18 * fVec43[((IOTA - iTemp19) & 4095)]));
			float fRec111 = (0.0f - (0.600000024f * fTemp160));
			float fTemp161 = (fRec110[1] + (fRec111 + (0.600000024f * fRec108[1])));
			fVec44[(IOTA & 4095)] = fTemp161;
			fRec108[0] = ((fTemp26 * fVec44[((IOTA - iTemp24) & 4095)]) + (fTemp27 * fVec44[((IOTA - iTemp28) & 4095)]));
			float fRec109 = (0.0f - (0.600000024f * fTemp161));
			float fTemp162 = (fRec108[1] + (fRec109 + (0.600000024f * fRec106[1])));
			fVec45[(IOTA & 4095)] = fTemp162;
			fRec106[0] = ((fTemp35 * fVec45[((IOTA - iTemp33) & 4095)]) + (fTemp36 * fVec45[((IOTA - iTemp37) & 4095)]));
			float fRec107 = (0.0f - (0.600000024f * fTemp162));
			float fTemp163 = (fRec106[1] + (fRec107 + (0.600000024f * fRec104[1])));
			fVec46[(IOTA & 4095)] = fTemp163;
			fRec104[0] = ((fTemp44 * fVec46[((IOTA - iTemp42) & 4095)]) + (fTemp45 * fVec46[((IOTA - iTemp46) & 4095)]));
			float fRec105 = (0.0f - (0.600000024f * fTemp163));
			float fTemp164 = (fRec104[1] + (fRec105 + (0.600000024f * fRec102[1])));
			fVec47[(IOTA & 4095)] = fTemp164;
			fRec102[0] = ((fTemp53 * fVec47[((IOTA - iTemp51) & 4095)]) + (fTemp54 * fVec47[((IOTA - iTemp55) & 4095)]));
			float fRec103 = (0.0f - (0.600000024f * fTemp164));
			float fTemp165 = (fRec102[1] + (fRec103 + (0.600000024f * fRec100[1])));
			fVec48[(IOTA & 4095)] = fTemp165;
			fRec100[0] = ((fTemp62 * fVec48[((IOTA - iTemp60) & 4095)]) + (fTemp63 * fVec48[((IOTA - iTemp64) & 4095)]));
			float fRec101 = (0.0f - (0.600000024f * fTemp165));
			float fTemp166 = (fRec101 + fRec100[1]);
			fVec49[(IOTA & 16383)] = fTemp166;
			float fTemp167 = (3125.0f * fTemp11);
			int iTemp168 = int(fTemp167);
			int iTemp169 = min(8193, max(0, iTemp168));
			float fTemp170 = floorf(fTemp167);
			float fTemp171 = (fTemp170 + (1.0f - fTemp167));
			float fTemp172 = (fTemp167 - fTemp170);
			int iTemp173 = min(8193, max(0, (iTemp168 + 1)));
			fRec7[0] = (0.353553385f * ((fVec49[((IOTA - iTemp169) & 16383)] * fTemp171) + (fTemp172 * fVec49[((IOTA - iTemp173) & 16383)])));
			fRec127[0] = ((fSlow1 * ((fRec4[1] + (fRec6[1] + fTemp158)) - (fRec8[1] + (fRec2[1] + fTemp159)))) - (((fTemp4 * fRec127[2]) + (2.0f * (fTemp5 * fRec127[1]))) / fTemp6));
			fRec126[0] = (((fRec127[2] + (fRec127[0] + (2.0f * fRec127[1]))) / fTemp6) - (((fTemp7 * fRec126[2]) + (2.0f * (fTemp5 * fRec126[1]))) / fTemp8));
			float fTemp174 = (((0.600000024f * fRec124[1]) + ((fRec126[2] + (fRec126[0] + (2.0f * fRec126[1]))) / fTemp8)) + fTemp9);
			fVec50[(IOTA & 4095)] = fTemp174;
			fRec124[0] = ((fTemp17 * fVec50[((IOTA - iTemp15) & 4095)]) + (fTemp18 * fVec50[((IOTA - iTemp19) & 4095)]));
			float fRec125 = (0.0f - (0.600000024f * fTemp174));
			float fTemp175 = (fRec124[1] + (fRec125 + (0.600000024f * fRec122[1])));
			fVec51[(IOTA & 4095)] = fTemp175;
			fRec122[0] = ((fTemp26 * fVec51[((IOTA - iTemp24) & 4095)]) + (fTemp27 * fVec51[((IOTA - iTemp28) & 4095)]));
			float fRec123 = (0.0f - (0.600000024f * fTemp175));
			float fTemp176 = (fRec122[1] + (fRec123 + (0.600000024f * fRec120[1])));
			fVec52[(IOTA & 4095)] = fTemp176;
			fRec120[0] = ((fTemp35 * fVec52[((IOTA - iTemp33) & 4095)]) + (fTemp36 * fVec52[((IOTA - iTemp37) & 4095)]));
			float fRec121 = (0.0f - (0.600000024f * fTemp176));
			float fTemp177 = (fRec120[1] + (fRec121 + (0.600000024f * fRec118[1])));
			fVec53[(IOTA & 4095)] = fTemp177;
			fRec118[0] = ((fTemp44 * fVec53[((IOTA - iTemp42) & 4095)]) + (fTemp45 * fVec53[((IOTA - iTemp46) & 4095)]));
			float fRec119 = (0.0f - (0.600000024f * fTemp177));
			float fTemp178 = (fRec118[1] + (fRec119 + (0.600000024f * fRec116[1])));
			fVec54[(IOTA & 4095)] = fTemp178;
			fRec116[0] = ((fTemp53 * fVec54[((IOTA - iTemp51) & 4095)]) + (fTemp54 * fVec54[((IOTA - iTemp55) & 4095)]));
			float fRec117 = (0.0f - (0.600000024f * fTemp178));
			float fTemp179 = (fRec116[1] + (fRec117 + (0.600000024f * fRec114[1])));
			fVec55[(IOTA & 4095)] = fTemp179;
			fRec114[0] = ((fTemp62 * fVec55[((IOTA - iTemp60) & 4095)]) + (fTemp63 * fVec55[((IOTA - iTemp64) & 4095)]));
			float fRec115 = (0.0f - (0.600000024f * fTemp179));
			float fTemp180 = (fRec115 + fRec114[1]);
			fVec56[(IOTA & 16383)] = fTemp180;
			float fTemp181 = (6561.0f * fTemp11);
			int iTemp182 = int(fTemp181);
			int iTemp183 = min(8193, max(0, iTemp182));
			float fTemp184 = floorf(fTemp181);
			float fTemp185 = (fTemp184 + (1.0f - fTemp181));
			float fTemp186 = (fTemp181 - fTemp184);
			int iTemp187 = min(8193, max(0, (iTemp182 + 1)));
			fRec8[0] = (0.353553385f * ((fVec56[((IOTA - iTemp183) & 16383)] * fTemp185) + (fTemp186 * fVec56[((IOTA - iTemp187) & 16383)])));
			float fTemp188 = (((fTemp3 + -1.41421354f) / fTemp2) + 1.0f);
			float fTemp189 = (((fTemp3 + 1.41421354f) / fTemp2) + 1.0f);
			fRec0[0] = ((((fRec1[0] + fRec3[0]) + fRec5[0]) + fRec7[0]) - (((fRec0[2] * fTemp188) + (2.0f * (fTemp5 * fRec0[1]))) / fTemp189));
			fRec128[0] = ((((fRec2[0] + fRec4[0]) + fRec6[0]) + fRec8[0]) - (((fTemp188 * fRec128[2]) + (2.0f * (fTemp5 * fRec128[1]))) / fTemp189));
			output0[i] = FAUSTFLOAT(((fSlow0 * (((fRec0[2] + (fRec0[0] + (2.0f * fRec0[1]))) + (fRec128[2] + (fRec128[0] + (2.0f * fRec128[1])))) / fTemp189)) + (fSlow5 * fTemp9)));
			float fTemp190 = (fRec130[1] + fRec134[1]);
			float fTemp191 = (fRec136[1] + (fTemp190 + fRec132[1]));
			fRec151[0] = ((fSlow1 * (fRec137[1] + (fRec133[1] + (fRec135[1] + (fTemp191 + fRec131[1]))))) - (((fTemp4 * fRec151[2]) + (2.0f * (fTemp5 * fRec151[1]))) / fTemp6));
			fRec150[0] = (((fRec151[2] + (fRec151[0] + (2.0f * fRec151[1]))) / fTemp6) - (((fTemp7 * fRec150[2]) + (2.0f * (fTemp5 * fRec150[1]))) / fTemp8));
			float fTemp192 = float(input1[i]);
			float fTemp193 = (((0.600000024f * fRec148[1]) + ((fRec150[2] + (fRec150[0] + (2.0f * fRec150[1]))) / fTemp8)) + fTemp192);
			fVec57[(IOTA & 4095)] = fTemp193;
			fRec148[0] = ((fTemp17 * fVec57[((IOTA - iTemp15) & 4095)]) + (fTemp18 * fVec57[((IOTA - iTemp19) & 4095)]));
			float fRec149 = (0.0f - (0.600000024f * fTemp193));
			float fTemp194 = (fRec148[1] + (fRec149 + (0.600000024f * fRec146[1])));
			fVec58[(IOTA & 4095)] = fTemp194;
			fRec146[0] = ((fTemp26 * fVec58[((IOTA - iTemp24) & 4095)]) + (fTemp27 * fVec58[((IOTA - iTemp28) & 4095)]));
			float fRec147 = (0.0f - (0.600000024f * fTemp194));
			float fTemp195 = (fRec146[1] + (fRec147 + (0.600000024f * fRec144[1])));
			fVec59[(IOTA & 4095)] = fTemp195;
			fRec144[0] = ((fTemp35 * fVec59[((IOTA - iTemp33) & 4095)]) + (fTemp36 * fVec59[((IOTA - iTemp37) & 4095)]));
			float fRec145 = (0.0f - (0.600000024f * fTemp195));
			float fTemp196 = (fRec144[1] + (fRec145 + (0.600000024f * fRec142[1])));
			fVec60[(IOTA & 4095)] = fTemp196;
			fRec142[0] = ((fTemp44 * fVec60[((IOTA - iTemp42) & 4095)]) + (fTemp45 * fVec60[((IOTA - iTemp46) & 4095)]));
			float fRec143 = (0.0f - (0.600000024f * fTemp196));
			float fTemp197 = (fRec142[1] + (fRec143 + (0.600000024f * fRec140[1])));
			fVec61[(IOTA & 4095)] = fTemp197;
			fRec140[0] = ((fTemp53 * fVec61[((IOTA - iTemp51) & 4095)]) + (fTemp54 * fVec61[((IOTA - iTemp55) & 4095)]));
			float fRec141 = (0.0f - (0.600000024f * fTemp197));
			float fTemp198 = (fRec140[1] + (fRec141 + (0.600000024f * fRec138[1])));
			fVec62[(IOTA & 4095)] = fTemp198;
			fRec138[0] = ((fTemp62 * fVec62[((IOTA - iTemp60) & 4095)]) + (fTemp63 * fVec62[((IOTA - iTemp64) & 4095)]));
			float fRec139 = (0.0f - (0.600000024f * fTemp198));
			float fTemp199 = (fRec139 + fRec138[1]);
			fVec63[(IOTA & 16383)] = fTemp199;
			fRec130[0] = (0.353553385f * ((fTemp70 * fVec63[((IOTA - iTemp68) & 16383)]) + (fTemp71 * fVec63[((IOTA - iTemp72) & 16383)])));
			fRec165[0] = ((fSlow1 * (fTemp191 - (fRec137[1] + ((fRec131[1] + fRec135[1]) + fRec133[1])))) - (((fTemp4 * fRec165[2]) + (2.0f * (fTemp5 * fRec165[1]))) / fTemp6));
			fRec164[0] = (((fRec165[2] + (fRec165[0] + (2.0f * fRec165[1]))) / fTemp6) - (((fTemp7 * fRec164[2]) + (2.0f * (fTemp5 * fRec164[1]))) / fTemp8));
			float fTemp200 = (((0.600000024f * fRec162[1]) + ((fRec164[2] + (fRec164[0] + (2.0f * fRec164[1]))) / fTemp8)) + fTemp192);
			fVec64[(IOTA & 4095)] = fTemp200;
			fRec162[0] = ((fTemp17 * fVec64[((IOTA - iTemp15) & 4095)]) + (fTemp18 * fVec64[((IOTA - iTemp19) & 4095)]));
			float fRec163 = (0.0f - (0.600000024f * fTemp200));
			float fTemp201 = (fRec162[1] + (fRec163 + (0.600000024f * fRec160[1])));
			fVec65[(IOTA & 4095)] = fTemp201;
			fRec160[0] = ((fTemp26 * fVec65[((IOTA - iTemp24) & 4095)]) + (fTemp27 * fVec65[((IOTA - iTemp28) & 4095)]));
			float fRec161 = (0.0f - (0.600000024f * fTemp201));
			float fTemp202 = (fRec160[1] + (fRec161 + (0.600000024f * fRec158[1])));
			fVec66[(IOTA & 4095)] = fTemp202;
			fRec158[0] = ((fTemp35 * fVec66[((IOTA - iTemp33) & 4095)]) + (fTemp36 * fVec66[((IOTA - iTemp37) & 4095)]));
			float fRec159 = (0.0f - (0.600000024f * fTemp202));
			float fTemp203 = (fRec158[1] + (fRec159 + (0.600000024f * fRec156[1])));
			fVec67[(IOTA & 4095)] = fTemp203;
			fRec156[0] = ((fTemp44 * fVec67[((IOTA - iTemp42) & 4095)]) + (fTemp45 * fVec67[((IOTA - iTemp46) & 4095)]));
			float fRec157 = (0.0f - (0.600000024f * fTemp203));
			float fTemp204 = (fRec156[1] + (fRec157 + (0.600000024f * fRec154[1])));
			fVec68[(IOTA & 4095)] = fTemp204;
			fRec154[0] = ((fTemp53 * fVec68[((IOTA - iTemp51) & 4095)]) + (fTemp54 * fVec68[((IOTA - iTemp55) & 4095)]));
			float fRec155 = (0.0f - (0.600000024f * fTemp204));
			float fTemp205 = (fRec154[1] + (fRec155 + (0.600000024f * fRec152[1])));
			fVec69[(IOTA & 4095)] = fTemp205;
			fRec152[0] = ((fTemp62 * fVec69[((IOTA - iTemp60) & 4095)]) + (fTemp63 * fVec69[((IOTA - iTemp64) & 4095)]));
			float fRec153 = (0.0f - (0.600000024f * fTemp205));
			float fTemp206 = (fRec153 + fRec152[1]);
			fVec70[(IOTA & 16383)] = fTemp206;
			fRec131[0] = (0.353553385f * ((fTemp84 * fVec70[((IOTA - iTemp82) & 16383)]) + (fTemp85 * fVec70[((IOTA - iTemp86) & 16383)])));
			float fTemp207 = (fRec132[1] + fRec136[1]);
			fRec180[0] = ((fSlow1 * ((fRec135[1] + (fTemp190 + fRec131[1])) - (fRec137[1] + (fTemp207 + fRec133[1])))) - (((fTemp4 * fRec180[2]) + (2.0f * (fTemp5 * fRec180[1]))) / fTemp6));
			fRec179[0] = (((fRec180[2] + (fRec180[0] + (2.0f * fRec180[1]))) / fTemp6) - (((fTemp7 * fRec179[2]) + (2.0f * (fTemp5 * fRec179[1]))) / fTemp8));
			float fTemp208 = (((0.600000024f * fRec177[1]) + ((fRec179[2] + (fRec179[0] + (2.0f * fRec179[1]))) / fTemp8)) + fTemp192);
			fVec71[(IOTA & 4095)] = fTemp208;
			fRec177[0] = ((fTemp17 * fVec71[((IOTA - iTemp15) & 4095)]) + (fTemp18 * fVec71[((IOTA - iTemp19) & 4095)]));
			float fRec178 = (0.0f - (0.600000024f * fTemp208));
			float fTemp209 = (fRec177[1] + (fRec178 + (0.600000024f * fRec175[1])));
			fVec72[(IOTA & 4095)] = fTemp209;
			fRec175[0] = ((fTemp26 * fVec72[((IOTA - iTemp24) & 4095)]) + (fTemp27 * fVec72[((IOTA - iTemp28) & 4095)]));
			float fRec176 = (0.0f - (0.600000024f * fTemp209));
			float fTemp210 = (fRec175[1] + (fRec176 + (0.600000024f * fRec173[1])));
			fVec73[(IOTA & 4095)] = fTemp210;
			fRec173[0] = ((fTemp35 * fVec73[((IOTA - iTemp33) & 4095)]) + (fTemp36 * fVec73[((IOTA - iTemp37) & 4095)]));
			float fRec174 = (0.0f - (0.600000024f * fTemp210));
			float fTemp211 = (fRec173[1] + (fRec174 + (0.600000024f * fRec171[1])));
			fVec74[(IOTA & 4095)] = fTemp211;
			fRec171[0] = ((fTemp44 * fVec74[((IOTA - iTemp42) & 4095)]) + (fTemp45 * fVec74[((IOTA - iTemp46) & 4095)]));
			float fRec172 = (0.0f - (0.600000024f * fTemp211));
			float fTemp212 = (fRec171[1] + (fRec172 + (0.600000024f * fRec169[1])));
			fVec75[(IOTA & 4095)] = fTemp212;
			fRec169[0] = ((fTemp53 * fVec75[((IOTA - iTemp51) & 4095)]) + (fTemp54 * fVec75[((IOTA - iTemp55) & 4095)]));
			float fRec170 = (0.0f - (0.600000024f * fTemp212));
			float fTemp213 = (fRec169[1] + (fRec170 + (0.600000024f * fRec167[1])));
			fVec76[(IOTA & 4095)] = fTemp213;
			fRec167[0] = ((fTemp62 * fVec76[((IOTA - iTemp60) & 4095)]) + (fTemp63 * fVec76[((IOTA - iTemp64) & 4095)]));
			float fRec168 = (0.0f - (0.600000024f * fTemp213));
			float fTemp214 = (fRec168 + fRec167[1]);
			fVec77[(IOTA & 16383)] = fTemp214;
			fRec166[0] = ((0.353553385f * ((fTemp99 * fVec77[((IOTA - iTemp97) & 16383)]) + (fTemp100 * fVec77[((IOTA - iTemp101) & 16383)]))) - (fConst5 * ((fConst7 * fRec166[2]) + (fConst8 * fRec166[1]))));
			fRec132[0] = (fConst5 * (((fConst6 * fRec166[0]) + (fConst9 * fRec166[1])) + (fConst6 * fRec166[2])));
			fRec194[0] = ((fSlow1 * ((fRec137[1] + (fTemp190 + fRec133[1])) - (fRec135[1] + (fTemp207 + fRec131[1])))) - (((fTemp4 * fRec194[2]) + (2.0f * (fTemp5 * fRec194[1]))) / fTemp6));
			fRec193[0] = (((fRec194[2] + (fRec194[0] + (2.0f * fRec194[1]))) / fTemp6) - (((fTemp7 * fRec193[2]) + (2.0f * (fTemp5 * fRec193[1]))) / fTemp8));
			float fTemp215 = (((0.600000024f * fRec191[1]) + ((fRec193[2] + (fRec193[0] + (2.0f * fRec193[1]))) / fTemp8)) + fTemp192);
			fVec78[(IOTA & 4095)] = fTemp215;
			fRec191[0] = ((fTemp17 * fVec78[((IOTA - iTemp15) & 4095)]) + (fTemp18 * fVec78[((IOTA - iTemp19) & 4095)]));
			float fRec192 = (0.0f - (0.600000024f * fTemp215));
			float fTemp216 = (fRec191[1] + (fRec192 + (0.600000024f * fRec189[1])));
			fVec79[(IOTA & 4095)] = fTemp216;
			fRec189[0] = ((fTemp26 * fVec79[((IOTA - iTemp24) & 4095)]) + (fTemp27 * fVec79[((IOTA - iTemp28) & 4095)]));
			float fRec190 = (0.0f - (0.600000024f * fTemp216));
			float fTemp217 = (fRec189[1] + (fRec190 + (0.600000024f * fRec187[1])));
			fVec80[(IOTA & 4095)] = fTemp217;
			fRec187[0] = ((fTemp35 * fVec80[((IOTA - iTemp33) & 4095)]) + (fTemp36 * fVec80[((IOTA - iTemp37) & 4095)]));
			float fRec188 = (0.0f - (0.600000024f * fTemp217));
			float fTemp218 = (fRec187[1] + (fRec188 + (0.600000024f * fRec185[1])));
			fVec81[(IOTA & 4095)] = fTemp218;
			fRec185[0] = ((fTemp44 * fVec81[((IOTA - iTemp42) & 4095)]) + (fTemp45 * fVec81[((IOTA - iTemp46) & 4095)]));
			float fRec186 = (0.0f - (0.600000024f * fTemp218));
			float fTemp219 = (fRec185[1] + (fRec186 + (0.600000024f * fRec183[1])));
			fVec82[(IOTA & 4095)] = fTemp219;
			fRec183[0] = ((fTemp53 * fVec82[((IOTA - iTemp51) & 4095)]) + (fTemp54 * fVec82[((IOTA - iTemp55) & 4095)]));
			float fRec184 = (0.0f - (0.600000024f * fTemp219));
			float fTemp220 = (fRec183[1] + (fRec184 + (0.600000024f * fRec181[1])));
			fVec83[(IOTA & 4095)] = fTemp220;
			fRec181[0] = ((fTemp62 * fVec83[((IOTA - iTemp60) & 4095)]) + (fTemp63 * fVec83[((IOTA - iTemp64) & 4095)]));
			float fRec182 = (0.0f - (0.600000024f * fTemp220));
			float fTemp221 = (fRec182 + fRec181[1]);
			fVec84[(IOTA & 131071)] = fTemp221;
			fRec133[0] = (0.353553385f * ((fSlow4 * fVec84[((IOTA - iTemp111) & 131071)]) + (fSlow3 * ((fTemp118 * ((fTemp115 * fVec84[((IOTA - iTemp113) & 131071)]) + (fTemp116 * fVec84[((IOTA - iTemp117) & 131071)]))) + (fTemp127 * ((fTemp124 * fVec84[((IOTA - iTemp122) & 131071)]) + (fTemp125 * fVec84[((IOTA - iTemp126) & 131071)])))))));
			float fTemp222 = (fRec130[1] + fRec132[1]);
			float fTemp223 = (fRec134[1] + fRec136[1]);
			fRec208[0] = ((fSlow1 * ((fRec133[1] + (fRec131[1] + fTemp222)) - (fRec137[1] + (fRec135[1] + fTemp223)))) - (((fTemp4 * fRec208[2]) + (2.0f * (fTemp5 * fRec208[1]))) / fTemp6));
			fRec207[0] = (((fRec208[2] + (fRec208[0] + (2.0f * fRec208[1]))) / fTemp6) - (((fTemp7 * fRec207[2]) + (2.0f * (fTemp5 * fRec207[1]))) / fTemp8));
			float fTemp224 = (((0.600000024f * fRec205[1]) + ((fRec207[2] + (fRec207[0] + (2.0f * fRec207[1]))) / fTemp8)) + fTemp192);
			fVec85[(IOTA & 4095)] = fTemp224;
			fRec205[0] = ((fTemp17 * fVec85[((IOTA - iTemp15) & 4095)]) + (fTemp18 * fVec85[((IOTA - iTemp19) & 4095)]));
			float fRec206 = (0.0f - (0.600000024f * fTemp224));
			float fTemp225 = (fRec205[1] + (fRec206 + (0.600000024f * fRec203[1])));
			fVec86[(IOTA & 4095)] = fTemp225;
			fRec203[0] = ((fTemp26 * fVec86[((IOTA - iTemp24) & 4095)]) + (fTemp27 * fVec86[((IOTA - iTemp28) & 4095)]));
			float fRec204 = (0.0f - (0.600000024f * fTemp225));
			float fTemp226 = (fRec203[1] + (fRec204 + (0.600000024f * fRec201[1])));
			fVec87[(IOTA & 4095)] = fTemp226;
			fRec201[0] = ((fTemp35 * fVec87[((IOTA - iTemp33) & 4095)]) + (fTemp36 * fVec87[((IOTA - iTemp37) & 4095)]));
			float fRec202 = (0.0f - (0.600000024f * fTemp226));
			float fTemp227 = (fRec201[1] + (fRec202 + (0.600000024f * fRec199[1])));
			fVec88[(IOTA & 4095)] = fTemp227;
			fRec199[0] = ((fTemp44 * fVec88[((IOTA - iTemp42) & 4095)]) + (fTemp45 * fVec88[((IOTA - iTemp46) & 4095)]));
			float fRec200 = (0.0f - (0.600000024f * fTemp227));
			float fTemp228 = (fRec199[1] + (fRec200 + (0.600000024f * fRec197[1])));
			fVec89[(IOTA & 4095)] = fTemp228;
			fRec197[0] = ((fTemp53 * fVec89[((IOTA - iTemp51) & 4095)]) + (fTemp54 * fVec89[((IOTA - iTemp55) & 4095)]));
			float fRec198 = (0.0f - (0.600000024f * fTemp228));
			float fTemp229 = (fRec197[1] + (fRec198 + (0.600000024f * fRec195[1])));
			fVec90[(IOTA & 4095)] = fTemp229;
			fRec195[0] = ((fTemp62 * fVec90[((IOTA - iTemp60) & 4095)]) + (fTemp63 * fVec90[((IOTA - iTemp64) & 4095)]));
			float fRec196 = (0.0f - (0.600000024f * fTemp229));
			float fTemp230 = (fRec196 + fRec195[1]);
			fVec91[(IOTA & 16383)] = fTemp230;
			fRec134[0] = (0.353553385f * ((fTemp141 * fVec91[((IOTA - iTemp139) & 16383)]) + (fTemp142 * fVec91[((IOTA - iTemp143) & 16383)])));
			fRec222[0] = ((fSlow1 * ((fRec137[1] + (fRec135[1] + fTemp222)) - (fRec133[1] + (fRec131[1] + fTemp223)))) - (((fTemp4 * fRec222[2]) + (2.0f * (fTemp5 * fRec222[1]))) / fTemp6));
			fRec221[0] = (((fRec222[2] + (fRec222[0] + (2.0f * fRec222[1]))) / fTemp6) - (((fTemp7 * fRec221[2]) + (2.0f * (fTemp5 * fRec221[1]))) / fTemp8));
			float fTemp231 = (((0.600000024f * fRec219[1]) + ((fRec221[2] + (fRec221[0] + (2.0f * fRec221[1]))) / fTemp8)) + fTemp192);
			fVec92[(IOTA & 4095)] = fTemp231;
			fRec219[0] = ((fTemp17 * fVec92[((IOTA - iTemp15) & 4095)]) + (fTemp18 * fVec92[((IOTA - iTemp19) & 4095)]));
			float fRec220 = (0.0f - (0.600000024f * fTemp231));
			float fTemp232 = (fRec219[1] + (fRec220 + (0.600000024f * fRec217[1])));
			fVec93[(IOTA & 4095)] = fTemp232;
			fRec217[0] = ((fTemp26 * fVec93[((IOTA - iTemp24) & 4095)]) + (fTemp27 * fVec93[((IOTA - iTemp28) & 4095)]));
			float fRec218 = (0.0f - (0.600000024f * fTemp232));
			float fTemp233 = (fRec217[1] + (fRec218 + (0.600000024f * fRec215[1])));
			fVec94[(IOTA & 4095)] = fTemp233;
			fRec215[0] = ((fTemp35 * fVec94[((IOTA - iTemp33) & 4095)]) + (fTemp36 * fVec94[((IOTA - iTemp37) & 4095)]));
			float fRec216 = (0.0f - (0.600000024f * fTemp233));
			float fTemp234 = (fRec215[1] + (fRec216 + (0.600000024f * fRec213[1])));
			fVec95[(IOTA & 4095)] = fTemp234;
			fRec213[0] = ((fTemp44 * fVec95[((IOTA - iTemp42) & 4095)]) + (fTemp45 * fVec95[((IOTA - iTemp46) & 4095)]));
			float fRec214 = (0.0f - (0.600000024f * fTemp234));
			float fTemp235 = (fRec213[1] + (fRec214 + (0.600000024f * fRec211[1])));
			fVec96[(IOTA & 4095)] = fTemp235;
			fRec211[0] = ((fTemp53 * fVec96[((IOTA - iTemp51) & 4095)]) + (fTemp54 * fVec96[((IOTA - iTemp55) & 4095)]));
			float fRec212 = (0.0f - (0.600000024f * fTemp235));
			float fTemp236 = (fRec211[1] + (fRec212 + (0.600000024f * fRec209[1])));
			fVec97[(IOTA & 4095)] = fTemp236;
			fRec209[0] = ((fTemp62 * fVec97[((IOTA - iTemp60) & 4095)]) + (fTemp63 * fVec97[((IOTA - iTemp64) & 4095)]));
			float fRec210 = (0.0f - (0.600000024f * fTemp236));
			float fTemp237 = (fRec210 + fRec209[1]);
			fVec98[(IOTA & 16383)] = fTemp237;
			fRec135[0] = (0.353553385f * ((fTemp155 * fVec98[((IOTA - iTemp153) & 16383)]) + (fTemp156 * fVec98[((IOTA - iTemp157) & 16383)])));
			float fTemp238 = (fRec130[1] + fRec136[1]);
			float fTemp239 = (fRec134[1] + fRec132[1]);
			fRec236[0] = ((fSlow1 * ((fRec137[1] + (fRec131[1] + fTemp238)) - (fRec133[1] + (fRec135[1] + fTemp239)))) - (((fTemp4 * fRec236[2]) + (2.0f * (fTemp5 * fRec236[1]))) / fTemp6));
			fRec235[0] = (((fRec236[2] + (fRec236[0] + (2.0f * fRec236[1]))) / fTemp6) - (((fTemp7 * fRec235[2]) + (2.0f * (fTemp5 * fRec235[1]))) / fTemp8));
			float fTemp240 = (((0.600000024f * fRec233[1]) + ((fRec235[2] + (fRec235[0] + (2.0f * fRec235[1]))) / fTemp8)) + fTemp192);
			fVec99[(IOTA & 4095)] = fTemp240;
			fRec233[0] = ((fTemp17 * fVec99[((IOTA - iTemp15) & 4095)]) + (fTemp18 * fVec99[((IOTA - iTemp19) & 4095)]));
			float fRec234 = (0.0f - (0.600000024f * fTemp240));
			float fTemp241 = (fRec233[1] + (fRec234 + (0.600000024f * fRec231[1])));
			fVec100[(IOTA & 4095)] = fTemp241;
			fRec231[0] = ((fTemp26 * fVec100[((IOTA - iTemp24) & 4095)]) + (fTemp27 * fVec100[((IOTA - iTemp28) & 4095)]));
			float fRec232 = (0.0f - (0.600000024f * fTemp241));
			float fTemp242 = (fRec231[1] + (fRec232 + (0.600000024f * fRec229[1])));
			fVec101[(IOTA & 4095)] = fTemp242;
			fRec229[0] = ((fTemp35 * fVec101[((IOTA - iTemp33) & 4095)]) + (fTemp36 * fVec101[((IOTA - iTemp37) & 4095)]));
			float fRec230 = (0.0f - (0.600000024f * fTemp242));
			float fTemp243 = (fRec229[1] + (fRec230 + (0.600000024f * fRec227[1])));
			fVec102[(IOTA & 4095)] = fTemp243;
			fRec227[0] = ((fTemp44 * fVec102[((IOTA - iTemp42) & 4095)]) + (fTemp45 * fVec102[((IOTA - iTemp46) & 4095)]));
			float fRec228 = (0.0f - (0.600000024f * fTemp243));
			float fTemp244 = (fRec227[1] + (fRec228 + (0.600000024f * fRec225[1])));
			fVec103[(IOTA & 4095)] = fTemp244;
			fRec225[0] = ((fTemp53 * fVec103[((IOTA - iTemp51) & 4095)]) + (fTemp54 * fVec103[((IOTA - iTemp55) & 4095)]));
			float fRec226 = (0.0f - (0.600000024f * fTemp244));
			float fTemp245 = (fRec225[1] + (fRec226 + (0.600000024f * fRec223[1])));
			fVec104[(IOTA & 4095)] = fTemp245;
			fRec223[0] = ((fTemp62 * fVec104[((IOTA - iTemp60) & 4095)]) + (fTemp63 * fVec104[((IOTA - iTemp64) & 4095)]));
			float fRec224 = (0.0f - (0.600000024f * fTemp245));
			float fTemp246 = (fRec224 + fRec223[1]);
			fVec105[(IOTA & 16383)] = fTemp246;
			fRec136[0] = (0.353553385f * ((fTemp171 * fVec105[((IOTA - iTemp169) & 16383)]) + (fTemp172 * fVec105[((IOTA - iTemp173) & 16383)])));
			fRec250[0] = ((fSlow1 * ((fRec133[1] + (fRec135[1] + fTemp238)) - (fRec137[1] + (fRec131[1] + fTemp239)))) - (((fTemp4 * fRec250[2]) + (2.0f * (fTemp5 * fRec250[1]))) / fTemp6));
			fRec249[0] = (((fRec250[2] + (fRec250[0] + (2.0f * fRec250[1]))) / fTemp6) - (((fTemp7 * fRec249[2]) + (2.0f * (fTemp5 * fRec249[1]))) / fTemp8));
			float fTemp247 = (((0.600000024f * fRec247[1]) + ((fRec249[2] + (fRec249[0] + (2.0f * fRec249[1]))) / fTemp8)) + fTemp192);
			fVec106[(IOTA & 4095)] = fTemp247;
			fRec247[0] = ((fTemp17 * fVec106[((IOTA - iTemp15) & 4095)]) + (fTemp18 * fVec106[((IOTA - iTemp19) & 4095)]));
			float fRec248 = (0.0f - (0.600000024f * fTemp247));
			float fTemp248 = (fRec247[1] + (fRec248 + (0.600000024f * fRec245[1])));
			fVec107[(IOTA & 4095)] = fTemp248;
			fRec245[0] = ((fTemp26 * fVec107[((IOTA - iTemp24) & 4095)]) + (fTemp27 * fVec107[((IOTA - iTemp28) & 4095)]));
			float fRec246 = (0.0f - (0.600000024f * fTemp248));
			float fTemp249 = (fRec245[1] + (fRec246 + (0.600000024f * fRec243[1])));
			fVec108[(IOTA & 4095)] = fTemp249;
			fRec243[0] = ((fTemp35 * fVec108[((IOTA - iTemp33) & 4095)]) + (fTemp36 * fVec108[((IOTA - iTemp37) & 4095)]));
			float fRec244 = (0.0f - (0.600000024f * fTemp249));
			float fTemp250 = (fRec243[1] + (fRec244 + (0.600000024f * fRec241[1])));
			fVec109[(IOTA & 4095)] = fTemp250;
			fRec241[0] = ((fTemp44 * fVec109[((IOTA - iTemp42) & 4095)]) + (fTemp45 * fVec109[((IOTA - iTemp46) & 4095)]));
			float fRec242 = (0.0f - (0.600000024f * fTemp250));
			float fTemp251 = (fRec241[1] + (fRec242 + (0.600000024f * fRec239[1])));
			fVec110[(IOTA & 4095)] = fTemp251;
			fRec239[0] = ((fTemp53 * fVec110[((IOTA - iTemp51) & 4095)]) + (fTemp54 * fVec110[((IOTA - iTemp55) & 4095)]));
			float fRec240 = (0.0f - (0.600000024f * fTemp251));
			float fTemp252 = (fRec239[1] + (fRec240 + (0.600000024f * fRec237[1])));
			fVec111[(IOTA & 4095)] = fTemp252;
			fRec237[0] = ((fTemp62 * fVec111[((IOTA - iTemp60) & 4095)]) + (fTemp63 * fVec111[((IOTA - iTemp64) & 4095)]));
			float fRec238 = (0.0f - (0.600000024f * fTemp252));
			float fTemp253 = (fRec238 + fRec237[1]);
			fVec112[(IOTA & 16383)] = fTemp253;
			fRec137[0] = (0.353553385f * ((fTemp185 * fVec112[((IOTA - iTemp183) & 16383)]) + (fTemp186 * fVec112[((IOTA - iTemp187) & 16383)])));
			fRec129[0] = ((((fRec130[0] + fRec132[0]) + fRec134[0]) + fRec136[0]) - (((fTemp188 * fRec129[2]) + (2.0f * (fTemp5 * fRec129[1]))) / fTemp189));
			fRec251[0] = ((((fRec131[0] + fRec133[0]) + fRec135[0]) + fRec137[0]) - (((fTemp188 * fRec251[2]) + (2.0f * (fTemp5 * fRec251[1]))) / fTemp189));
			output1[i] = FAUSTFLOAT(((fSlow0 * (((fRec129[2] + (fRec129[0] + (2.0f * fRec129[1]))) + (fRec251[2] + (fRec251[0] + (2.0f * fRec251[1])))) / fTemp189)) + (fSlow5 * fTemp192)));
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
			fRec151[2] = fRec151[1];
			fRec151[1] = fRec151[0];
			fRec150[2] = fRec150[1];
			fRec150[1] = fRec150[0];
			fRec148[1] = fRec148[0];
			fRec146[1] = fRec146[0];
			fRec144[1] = fRec144[0];
			fRec142[1] = fRec142[0];
			fRec140[1] = fRec140[0];
			fRec138[1] = fRec138[0];
			fRec130[1] = fRec130[0];
			fRec165[2] = fRec165[1];
			fRec165[1] = fRec165[0];
			fRec164[2] = fRec164[1];
			fRec164[1] = fRec164[0];
			fRec162[1] = fRec162[0];
			fRec160[1] = fRec160[0];
			fRec158[1] = fRec158[0];
			fRec156[1] = fRec156[0];
			fRec154[1] = fRec154[0];
			fRec152[1] = fRec152[0];
			fRec131[1] = fRec131[0];
			fRec180[2] = fRec180[1];
			fRec180[1] = fRec180[0];
			fRec179[2] = fRec179[1];
			fRec179[1] = fRec179[0];
			fRec177[1] = fRec177[0];
			fRec175[1] = fRec175[0];
			fRec173[1] = fRec173[0];
			fRec171[1] = fRec171[0];
			fRec169[1] = fRec169[0];
			fRec167[1] = fRec167[0];
			fRec166[2] = fRec166[1];
			fRec166[1] = fRec166[0];
			fRec132[1] = fRec132[0];
			fRec194[2] = fRec194[1];
			fRec194[1] = fRec194[0];
			fRec193[2] = fRec193[1];
			fRec193[1] = fRec193[0];
			fRec191[1] = fRec191[0];
			fRec189[1] = fRec189[0];
			fRec187[1] = fRec187[0];
			fRec185[1] = fRec185[0];
			fRec183[1] = fRec183[0];
			fRec181[1] = fRec181[0];
			fRec133[1] = fRec133[0];
			fRec208[2] = fRec208[1];
			fRec208[1] = fRec208[0];
			fRec207[2] = fRec207[1];
			fRec207[1] = fRec207[0];
			fRec205[1] = fRec205[0];
			fRec203[1] = fRec203[0];
			fRec201[1] = fRec201[0];
			fRec199[1] = fRec199[0];
			fRec197[1] = fRec197[0];
			fRec195[1] = fRec195[0];
			fRec134[1] = fRec134[0];
			fRec222[2] = fRec222[1];
			fRec222[1] = fRec222[0];
			fRec221[2] = fRec221[1];
			fRec221[1] = fRec221[0];
			fRec219[1] = fRec219[0];
			fRec217[1] = fRec217[0];
			fRec215[1] = fRec215[0];
			fRec213[1] = fRec213[0];
			fRec211[1] = fRec211[0];
			fRec209[1] = fRec209[0];
			fRec135[1] = fRec135[0];
			fRec236[2] = fRec236[1];
			fRec236[1] = fRec236[0];
			fRec235[2] = fRec235[1];
			fRec235[1] = fRec235[0];
			fRec233[1] = fRec233[0];
			fRec231[1] = fRec231[0];
			fRec229[1] = fRec229[0];
			fRec227[1] = fRec227[0];
			fRec225[1] = fRec225[0];
			fRec223[1] = fRec223[0];
			fRec136[1] = fRec136[0];
			fRec250[2] = fRec250[1];
			fRec250[1] = fRec250[0];
			fRec249[2] = fRec249[1];
			fRec249[1] = fRec249[0];
			fRec247[1] = fRec247[0];
			fRec245[1] = fRec245[0];
			fRec243[1] = fRec243[0];
			fRec241[1] = fRec241[0];
			fRec239[1] = fRec239[0];
			fRec237[1] = fRec237[0];
			fRec137[1] = fRec137[0];
			fRec129[2] = fRec129[1];
			fRec129[1] = fRec129[0];
			fRec251[2] = fRec251[1];
			fRec251[1] = fRec251[0];
			
		}
		
	}

	
};

#endif
