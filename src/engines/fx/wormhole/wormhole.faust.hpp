/* ------------------------------------------------------------
name: "wormhole"
Code generated with Faust 2.10.0 (https://faust.grame.fr)
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

#include <algorithm>
#include <cmath>
#include <math.h>


class faust_wormholeSIG0 {
	
  private:
	
	int iRec24[2];
	
  public:
	
	int getNumInputsfaust_wormholeSIG0() {
		return 0;
		
	}
	int getNumOutputsfaust_wormholeSIG0() {
		return 1;
		
	}
	int getInputRatefaust_wormholeSIG0(int channel) {
		int rate;
		switch (channel) {
			default: {
				rate = -1;
				break;
			}
			
		}
		return rate;
		
	}
	int getOutputRatefaust_wormholeSIG0(int channel) {
		int rate;
		switch (channel) {
			case 0: {
				rate = 0;
				break;
			}
			default: {
				rate = -1;
				break;
			}
			
		}
		return rate;
		
	}
	
	void instanceInitfaust_wormholeSIG0(int samplingFreq) {
		for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			iRec24[l4] = 0;
			
		}
		
	}
	
	void fillfaust_wormholeSIG0(int count, float* output) {
		for (int i = 0; (i < count); i = (i + 1)) {
			iRec24[0] = (iRec24[1] + 1);
			output[i] = std::sin((9.58738019e-05f * float((iRec24[0] + -1))));
			iRec24[1] = iRec24[0];
			
		}
		
	}
};

faust_wormholeSIG0* newfaust_wormholeSIG0() { return (faust_wormholeSIG0*)new faust_wormholeSIG0(); }
void deletefaust_wormholeSIG0(faust_wormholeSIG0* dsp) { delete dsp; }

static float faust_wormhole_faustpower2_f(float value) {
	return (value * value);
	
}
static float ftbl0faust_wormholeSIG0[65536];

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
	FAUSTFLOAT fHslider1;
	int fSamplingFreq;
	float fConst0;
	float fConst1;
	FAUSTFLOAT fHslider2;
	float fRec23[2];
	float fRec22[3];
	float fRec21[3];
	int IOTA;
	float fVec0[512];
	float fConst2;
	float fRec25[2];
	float fRec19[2];
	float fVec1[512];
	float fRec17[2];
	float fVec2[1024];
	float fRec15[2];
	float fVec3[1024];
	float fRec13[2];
	float fVec4[2048];
	float fRec11[2];
	float fVec5[4096];
	float fRec9[2];
	float fVec6[2048];
	float fRec1[2];
	float fRec39[3];
	float fRec38[3];
	float fVec7[512];
	float fRec36[2];
	float fVec8[512];
	float fRec34[2];
	float fVec9[1024];
	float fRec32[2];
	float fVec10[1024];
	float fRec30[2];
	float fVec11[2048];
	float fRec28[2];
	float fVec12[4096];
	float fRec26[2];
	float fVec13[2048];
	float fRec2[2];
	float fConst3;
	float fConst4;
	float fConst5;
	float fConst6;
	float fRec54[3];
	float fRec53[3];
	float fVec14[512];
	float fRec51[2];
	float fVec15[512];
	float fRec49[2];
	float fVec16[1024];
	float fRec47[2];
	float fVec17[1024];
	float fRec45[2];
	float fVec18[2048];
	float fRec43[2];
	float fVec19[4096];
	float fRec41[2];
	float fVec20[2048];
	float fConst7;
	float fConst8;
	float fRec40[3];
	float fConst9;
	float fRec3[2];
	FAUSTFLOAT fHslider3;
	float fRec68[3];
	float fRec67[3];
	float fVec21[512];
	float fRec65[2];
	float fVec22[512];
	float fRec63[2];
	float fVec23[1024];
	float fRec61[2];
	float fVec24[1024];
	float fRec59[2];
	float fVec25[2048];
	float fRec57[2];
	float fVec26[4096];
	float fRec55[2];
	float fVec27[131072];
	float fRec69[2];
	float fRec4[2];
	float fRec83[3];
	float fRec82[3];
	float fVec28[512];
	float fRec80[2];
	float fVec29[512];
	float fRec78[2];
	float fVec30[1024];
	float fRec76[2];
	float fVec31[1024];
	float fRec74[2];
	float fVec32[2048];
	float fRec72[2];
	float fVec33[4096];
	float fRec70[2];
	float fVec34[2048];
	float fRec5[2];
	float fRec97[3];
	float fRec96[3];
	float fVec35[512];
	float fRec94[2];
	float fVec36[512];
	float fRec92[2];
	float fVec37[1024];
	float fRec90[2];
	float fVec38[1024];
	float fRec88[2];
	float fVec39[2048];
	float fRec86[2];
	float fVec40[4096];
	float fRec84[2];
	float fVec41[4096];
	float fRec6[2];
	float fRec111[3];
	float fRec110[3];
	float fVec42[512];
	float fRec108[2];
	float fVec43[512];
	float fRec106[2];
	float fVec44[1024];
	float fRec104[2];
	float fVec45[1024];
	float fRec102[2];
	float fVec46[2048];
	float fRec100[2];
	float fVec47[4096];
	float fRec98[2];
	float fVec48[4096];
	float fRec7[2];
	float fRec125[3];
	float fRec124[3];
	float fVec49[512];
	float fRec122[2];
	float fVec50[512];
	float fRec120[2];
	float fVec51[1024];
	float fRec118[2];
	float fVec52[1024];
	float fRec116[2];
	float fVec53[2048];
	float fRec114[2];
	float fVec54[4096];
	float fRec112[2];
	float fVec55[8192];
	float fRec8[2];
	float fRec0[3];
	float fRec126[3];
	
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
		faust_wormholeSIG0* sig0 = newfaust_wormholeSIG0();
		sig0->instanceInitfaust_wormholeSIG0(samplingFreq);
		sig0->fillfaust_wormholeSIG0(65536, ftbl0faust_wormholeSIG0);
		deletefaust_wormholeSIG0(sig0);
		
	}
	
	virtual void instanceConstants(int samplingFreq) {
		fSamplingFreq = samplingFreq;
		fConst0 = std::min(192000.0f, std::max(1.0f, float(fSamplingFreq)));
		fConst1 = (3.14159274f / fConst0);
		fConst2 = (0.25f / fConst0);
		fConst3 = std::tan((314.159271f / fConst0));
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
			fRec23[l0] = 0.0f;
			
		}
		for (int l1 = 0; (l1 < 3); l1 = (l1 + 1)) {
			fRec22[l1] = 0.0f;
			
		}
		for (int l2 = 0; (l2 < 3); l2 = (l2 + 1)) {
			fRec21[l2] = 0.0f;
			
		}
		IOTA = 0;
		for (int l3 = 0; (l3 < 512); l3 = (l3 + 1)) {
			fVec0[l3] = 0.0f;
			
		}
		for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			fRec25[l5] = 0.0f;
			
		}
		for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			fRec19[l6] = 0.0f;
			
		}
		for (int l7 = 0; (l7 < 512); l7 = (l7 + 1)) {
			fVec1[l7] = 0.0f;
			
		}
		for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			fRec17[l8] = 0.0f;
			
		}
		for (int l9 = 0; (l9 < 1024); l9 = (l9 + 1)) {
			fVec2[l9] = 0.0f;
			
		}
		for (int l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
			fRec15[l10] = 0.0f;
			
		}
		for (int l11 = 0; (l11 < 1024); l11 = (l11 + 1)) {
			fVec3[l11] = 0.0f;
			
		}
		for (int l12 = 0; (l12 < 2); l12 = (l12 + 1)) {
			fRec13[l12] = 0.0f;
			
		}
		for (int l13 = 0; (l13 < 2048); l13 = (l13 + 1)) {
			fVec4[l13] = 0.0f;
			
		}
		for (int l14 = 0; (l14 < 2); l14 = (l14 + 1)) {
			fRec11[l14] = 0.0f;
			
		}
		for (int l15 = 0; (l15 < 4096); l15 = (l15 + 1)) {
			fVec5[l15] = 0.0f;
			
		}
		for (int l16 = 0; (l16 < 2); l16 = (l16 + 1)) {
			fRec9[l16] = 0.0f;
			
		}
		for (int l17 = 0; (l17 < 2048); l17 = (l17 + 1)) {
			fVec6[l17] = 0.0f;
			
		}
		for (int l18 = 0; (l18 < 2); l18 = (l18 + 1)) {
			fRec1[l18] = 0.0f;
			
		}
		for (int l19 = 0; (l19 < 3); l19 = (l19 + 1)) {
			fRec39[l19] = 0.0f;
			
		}
		for (int l20 = 0; (l20 < 3); l20 = (l20 + 1)) {
			fRec38[l20] = 0.0f;
			
		}
		for (int l21 = 0; (l21 < 512); l21 = (l21 + 1)) {
			fVec7[l21] = 0.0f;
			
		}
		for (int l22 = 0; (l22 < 2); l22 = (l22 + 1)) {
			fRec36[l22] = 0.0f;
			
		}
		for (int l23 = 0; (l23 < 512); l23 = (l23 + 1)) {
			fVec8[l23] = 0.0f;
			
		}
		for (int l24 = 0; (l24 < 2); l24 = (l24 + 1)) {
			fRec34[l24] = 0.0f;
			
		}
		for (int l25 = 0; (l25 < 1024); l25 = (l25 + 1)) {
			fVec9[l25] = 0.0f;
			
		}
		for (int l26 = 0; (l26 < 2); l26 = (l26 + 1)) {
			fRec32[l26] = 0.0f;
			
		}
		for (int l27 = 0; (l27 < 1024); l27 = (l27 + 1)) {
			fVec10[l27] = 0.0f;
			
		}
		for (int l28 = 0; (l28 < 2); l28 = (l28 + 1)) {
			fRec30[l28] = 0.0f;
			
		}
		for (int l29 = 0; (l29 < 2048); l29 = (l29 + 1)) {
			fVec11[l29] = 0.0f;
			
		}
		for (int l30 = 0; (l30 < 2); l30 = (l30 + 1)) {
			fRec28[l30] = 0.0f;
			
		}
		for (int l31 = 0; (l31 < 4096); l31 = (l31 + 1)) {
			fVec12[l31] = 0.0f;
			
		}
		for (int l32 = 0; (l32 < 2); l32 = (l32 + 1)) {
			fRec26[l32] = 0.0f;
			
		}
		for (int l33 = 0; (l33 < 2048); l33 = (l33 + 1)) {
			fVec13[l33] = 0.0f;
			
		}
		for (int l34 = 0; (l34 < 2); l34 = (l34 + 1)) {
			fRec2[l34] = 0.0f;
			
		}
		for (int l35 = 0; (l35 < 3); l35 = (l35 + 1)) {
			fRec54[l35] = 0.0f;
			
		}
		for (int l36 = 0; (l36 < 3); l36 = (l36 + 1)) {
			fRec53[l36] = 0.0f;
			
		}
		for (int l37 = 0; (l37 < 512); l37 = (l37 + 1)) {
			fVec14[l37] = 0.0f;
			
		}
		for (int l38 = 0; (l38 < 2); l38 = (l38 + 1)) {
			fRec51[l38] = 0.0f;
			
		}
		for (int l39 = 0; (l39 < 512); l39 = (l39 + 1)) {
			fVec15[l39] = 0.0f;
			
		}
		for (int l40 = 0; (l40 < 2); l40 = (l40 + 1)) {
			fRec49[l40] = 0.0f;
			
		}
		for (int l41 = 0; (l41 < 1024); l41 = (l41 + 1)) {
			fVec16[l41] = 0.0f;
			
		}
		for (int l42 = 0; (l42 < 2); l42 = (l42 + 1)) {
			fRec47[l42] = 0.0f;
			
		}
		for (int l43 = 0; (l43 < 1024); l43 = (l43 + 1)) {
			fVec17[l43] = 0.0f;
			
		}
		for (int l44 = 0; (l44 < 2); l44 = (l44 + 1)) {
			fRec45[l44] = 0.0f;
			
		}
		for (int l45 = 0; (l45 < 2048); l45 = (l45 + 1)) {
			fVec18[l45] = 0.0f;
			
		}
		for (int l46 = 0; (l46 < 2); l46 = (l46 + 1)) {
			fRec43[l46] = 0.0f;
			
		}
		for (int l47 = 0; (l47 < 4096); l47 = (l47 + 1)) {
			fVec19[l47] = 0.0f;
			
		}
		for (int l48 = 0; (l48 < 2); l48 = (l48 + 1)) {
			fRec41[l48] = 0.0f;
			
		}
		for (int l49 = 0; (l49 < 2048); l49 = (l49 + 1)) {
			fVec20[l49] = 0.0f;
			
		}
		for (int l50 = 0; (l50 < 3); l50 = (l50 + 1)) {
			fRec40[l50] = 0.0f;
			
		}
		for (int l51 = 0; (l51 < 2); l51 = (l51 + 1)) {
			fRec3[l51] = 0.0f;
			
		}
		for (int l52 = 0; (l52 < 3); l52 = (l52 + 1)) {
			fRec68[l52] = 0.0f;
			
		}
		for (int l53 = 0; (l53 < 3); l53 = (l53 + 1)) {
			fRec67[l53] = 0.0f;
			
		}
		for (int l54 = 0; (l54 < 512); l54 = (l54 + 1)) {
			fVec21[l54] = 0.0f;
			
		}
		for (int l55 = 0; (l55 < 2); l55 = (l55 + 1)) {
			fRec65[l55] = 0.0f;
			
		}
		for (int l56 = 0; (l56 < 512); l56 = (l56 + 1)) {
			fVec22[l56] = 0.0f;
			
		}
		for (int l57 = 0; (l57 < 2); l57 = (l57 + 1)) {
			fRec63[l57] = 0.0f;
			
		}
		for (int l58 = 0; (l58 < 1024); l58 = (l58 + 1)) {
			fVec23[l58] = 0.0f;
			
		}
		for (int l59 = 0; (l59 < 2); l59 = (l59 + 1)) {
			fRec61[l59] = 0.0f;
			
		}
		for (int l60 = 0; (l60 < 1024); l60 = (l60 + 1)) {
			fVec24[l60] = 0.0f;
			
		}
		for (int l61 = 0; (l61 < 2); l61 = (l61 + 1)) {
			fRec59[l61] = 0.0f;
			
		}
		for (int l62 = 0; (l62 < 2048); l62 = (l62 + 1)) {
			fVec25[l62] = 0.0f;
			
		}
		for (int l63 = 0; (l63 < 2); l63 = (l63 + 1)) {
			fRec57[l63] = 0.0f;
			
		}
		for (int l64 = 0; (l64 < 4096); l64 = (l64 + 1)) {
			fVec26[l64] = 0.0f;
			
		}
		for (int l65 = 0; (l65 < 2); l65 = (l65 + 1)) {
			fRec55[l65] = 0.0f;
			
		}
		for (int l66 = 0; (l66 < 131072); l66 = (l66 + 1)) {
			fVec27[l66] = 0.0f;
			
		}
		for (int l67 = 0; (l67 < 2); l67 = (l67 + 1)) {
			fRec69[l67] = 0.0f;
			
		}
		for (int l68 = 0; (l68 < 2); l68 = (l68 + 1)) {
			fRec4[l68] = 0.0f;
			
		}
		for (int l69 = 0; (l69 < 3); l69 = (l69 + 1)) {
			fRec83[l69] = 0.0f;
			
		}
		for (int l70 = 0; (l70 < 3); l70 = (l70 + 1)) {
			fRec82[l70] = 0.0f;
			
		}
		for (int l71 = 0; (l71 < 512); l71 = (l71 + 1)) {
			fVec28[l71] = 0.0f;
			
		}
		for (int l72 = 0; (l72 < 2); l72 = (l72 + 1)) {
			fRec80[l72] = 0.0f;
			
		}
		for (int l73 = 0; (l73 < 512); l73 = (l73 + 1)) {
			fVec29[l73] = 0.0f;
			
		}
		for (int l74 = 0; (l74 < 2); l74 = (l74 + 1)) {
			fRec78[l74] = 0.0f;
			
		}
		for (int l75 = 0; (l75 < 1024); l75 = (l75 + 1)) {
			fVec30[l75] = 0.0f;
			
		}
		for (int l76 = 0; (l76 < 2); l76 = (l76 + 1)) {
			fRec76[l76] = 0.0f;
			
		}
		for (int l77 = 0; (l77 < 1024); l77 = (l77 + 1)) {
			fVec31[l77] = 0.0f;
			
		}
		for (int l78 = 0; (l78 < 2); l78 = (l78 + 1)) {
			fRec74[l78] = 0.0f;
			
		}
		for (int l79 = 0; (l79 < 2048); l79 = (l79 + 1)) {
			fVec32[l79] = 0.0f;
			
		}
		for (int l80 = 0; (l80 < 2); l80 = (l80 + 1)) {
			fRec72[l80] = 0.0f;
			
		}
		for (int l81 = 0; (l81 < 4096); l81 = (l81 + 1)) {
			fVec33[l81] = 0.0f;
			
		}
		for (int l82 = 0; (l82 < 2); l82 = (l82 + 1)) {
			fRec70[l82] = 0.0f;
			
		}
		for (int l83 = 0; (l83 < 2048); l83 = (l83 + 1)) {
			fVec34[l83] = 0.0f;
			
		}
		for (int l84 = 0; (l84 < 2); l84 = (l84 + 1)) {
			fRec5[l84] = 0.0f;
			
		}
		for (int l85 = 0; (l85 < 3); l85 = (l85 + 1)) {
			fRec97[l85] = 0.0f;
			
		}
		for (int l86 = 0; (l86 < 3); l86 = (l86 + 1)) {
			fRec96[l86] = 0.0f;
			
		}
		for (int l87 = 0; (l87 < 512); l87 = (l87 + 1)) {
			fVec35[l87] = 0.0f;
			
		}
		for (int l88 = 0; (l88 < 2); l88 = (l88 + 1)) {
			fRec94[l88] = 0.0f;
			
		}
		for (int l89 = 0; (l89 < 512); l89 = (l89 + 1)) {
			fVec36[l89] = 0.0f;
			
		}
		for (int l90 = 0; (l90 < 2); l90 = (l90 + 1)) {
			fRec92[l90] = 0.0f;
			
		}
		for (int l91 = 0; (l91 < 1024); l91 = (l91 + 1)) {
			fVec37[l91] = 0.0f;
			
		}
		for (int l92 = 0; (l92 < 2); l92 = (l92 + 1)) {
			fRec90[l92] = 0.0f;
			
		}
		for (int l93 = 0; (l93 < 1024); l93 = (l93 + 1)) {
			fVec38[l93] = 0.0f;
			
		}
		for (int l94 = 0; (l94 < 2); l94 = (l94 + 1)) {
			fRec88[l94] = 0.0f;
			
		}
		for (int l95 = 0; (l95 < 2048); l95 = (l95 + 1)) {
			fVec39[l95] = 0.0f;
			
		}
		for (int l96 = 0; (l96 < 2); l96 = (l96 + 1)) {
			fRec86[l96] = 0.0f;
			
		}
		for (int l97 = 0; (l97 < 4096); l97 = (l97 + 1)) {
			fVec40[l97] = 0.0f;
			
		}
		for (int l98 = 0; (l98 < 2); l98 = (l98 + 1)) {
			fRec84[l98] = 0.0f;
			
		}
		for (int l99 = 0; (l99 < 4096); l99 = (l99 + 1)) {
			fVec41[l99] = 0.0f;
			
		}
		for (int l100 = 0; (l100 < 2); l100 = (l100 + 1)) {
			fRec6[l100] = 0.0f;
			
		}
		for (int l101 = 0; (l101 < 3); l101 = (l101 + 1)) {
			fRec111[l101] = 0.0f;
			
		}
		for (int l102 = 0; (l102 < 3); l102 = (l102 + 1)) {
			fRec110[l102] = 0.0f;
			
		}
		for (int l103 = 0; (l103 < 512); l103 = (l103 + 1)) {
			fVec42[l103] = 0.0f;
			
		}
		for (int l104 = 0; (l104 < 2); l104 = (l104 + 1)) {
			fRec108[l104] = 0.0f;
			
		}
		for (int l105 = 0; (l105 < 512); l105 = (l105 + 1)) {
			fVec43[l105] = 0.0f;
			
		}
		for (int l106 = 0; (l106 < 2); l106 = (l106 + 1)) {
			fRec106[l106] = 0.0f;
			
		}
		for (int l107 = 0; (l107 < 1024); l107 = (l107 + 1)) {
			fVec44[l107] = 0.0f;
			
		}
		for (int l108 = 0; (l108 < 2); l108 = (l108 + 1)) {
			fRec104[l108] = 0.0f;
			
		}
		for (int l109 = 0; (l109 < 1024); l109 = (l109 + 1)) {
			fVec45[l109] = 0.0f;
			
		}
		for (int l110 = 0; (l110 < 2); l110 = (l110 + 1)) {
			fRec102[l110] = 0.0f;
			
		}
		for (int l111 = 0; (l111 < 2048); l111 = (l111 + 1)) {
			fVec46[l111] = 0.0f;
			
		}
		for (int l112 = 0; (l112 < 2); l112 = (l112 + 1)) {
			fRec100[l112] = 0.0f;
			
		}
		for (int l113 = 0; (l113 < 4096); l113 = (l113 + 1)) {
			fVec47[l113] = 0.0f;
			
		}
		for (int l114 = 0; (l114 < 2); l114 = (l114 + 1)) {
			fRec98[l114] = 0.0f;
			
		}
		for (int l115 = 0; (l115 < 4096); l115 = (l115 + 1)) {
			fVec48[l115] = 0.0f;
			
		}
		for (int l116 = 0; (l116 < 2); l116 = (l116 + 1)) {
			fRec7[l116] = 0.0f;
			
		}
		for (int l117 = 0; (l117 < 3); l117 = (l117 + 1)) {
			fRec125[l117] = 0.0f;
			
		}
		for (int l118 = 0; (l118 < 3); l118 = (l118 + 1)) {
			fRec124[l118] = 0.0f;
			
		}
		for (int l119 = 0; (l119 < 512); l119 = (l119 + 1)) {
			fVec49[l119] = 0.0f;
			
		}
		for (int l120 = 0; (l120 < 2); l120 = (l120 + 1)) {
			fRec122[l120] = 0.0f;
			
		}
		for (int l121 = 0; (l121 < 512); l121 = (l121 + 1)) {
			fVec50[l121] = 0.0f;
			
		}
		for (int l122 = 0; (l122 < 2); l122 = (l122 + 1)) {
			fRec120[l122] = 0.0f;
			
		}
		for (int l123 = 0; (l123 < 1024); l123 = (l123 + 1)) {
			fVec51[l123] = 0.0f;
			
		}
		for (int l124 = 0; (l124 < 2); l124 = (l124 + 1)) {
			fRec118[l124] = 0.0f;
			
		}
		for (int l125 = 0; (l125 < 1024); l125 = (l125 + 1)) {
			fVec52[l125] = 0.0f;
			
		}
		for (int l126 = 0; (l126 < 2); l126 = (l126 + 1)) {
			fRec116[l126] = 0.0f;
			
		}
		for (int l127 = 0; (l127 < 2048); l127 = (l127 + 1)) {
			fVec53[l127] = 0.0f;
			
		}
		for (int l128 = 0; (l128 < 2); l128 = (l128 + 1)) {
			fRec114[l128] = 0.0f;
			
		}
		for (int l129 = 0; (l129 < 4096); l129 = (l129 + 1)) {
			fVec54[l129] = 0.0f;
			
		}
		for (int l130 = 0; (l130 < 2); l130 = (l130 + 1)) {
			fRec112[l130] = 0.0f;
			
		}
		for (int l131 = 0; (l131 < 8192); l131 = (l131 + 1)) {
			fVec55[l131] = 0.0f;
			
		}
		for (int l132 = 0; (l132 < 2); l132 = (l132 + 1)) {
			fRec8[l132] = 0.0f;
			
		}
		for (int l133 = 0; (l133 < 3); l133 = (l133 + 1)) {
			fRec0[l133] = 0.0f;
			
		}
		for (int l134 = 0; (l134 < 3); l134 = (l134 + 1)) {
			fRec126[l134] = 0.0f;
			
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
			float fTemp0 = (fRec1[1] + fRec5[1]);
			float fTemp1 = (fRec7[1] + (fTemp0 + fRec3[1]));
			fRec23[0] = (fSlow2 + (0.999000013f * fRec23[1]));
			float fTemp2 = std::tan((fConst1 * fRec23[0]));
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
			fVec0[(IOTA & 511)] = fTemp11;
			fRec25[0] = (fConst2 + (fRec25[1] - std::floor((fConst2 + fRec25[1]))));
			float fTemp12 = ((0.00100000005f * ftbl0faust_wormholeSIG0[int((65536.0f * fRec25[0]))]) + 1.0f);
			float fTemp13 = (343.0f * fTemp12);
			float fTemp14 = (fTemp13 + -1.0f);
			int iTemp15 = int(fTemp14);
			int iTemp16 = std::min(2049, std::max(0, iTemp15));
			float fTemp17 = std::floor(fTemp14);
			float fTemp18 = (fTemp17 + (2.0f - fTemp13));
			float fTemp19 = (fTemp13 + (-1.0f - fTemp17));
			int iTemp20 = std::min(2049, std::max(0, (iTemp15 + 1)));
			fRec19[0] = ((fVec0[((IOTA - iTemp16) & 511)] * fTemp18) + (fTemp19 * fVec0[((IOTA - iTemp20) & 511)]));
			float fRec20 = (0.0f - (0.600000024f * fTemp11));
			float fTemp21 = (fRec19[1] + (fRec20 + (0.600000024f * fRec17[1])));
			fVec1[(IOTA & 511)] = fTemp21;
			float fTemp22 = (441.0f * fTemp12);
			float fTemp23 = (fTemp22 + -1.0f);
			int iTemp24 = int(fTemp23);
			int iTemp25 = std::min(2049, std::max(0, iTemp24));
			float fTemp26 = std::floor(fTemp23);
			float fTemp27 = (fTemp26 + (2.0f - fTemp22));
			float fTemp28 = (fTemp22 + (-1.0f - fTemp26));
			int iTemp29 = std::min(2049, std::max(0, (iTemp24 + 1)));
			fRec17[0] = ((fVec1[((IOTA - iTemp25) & 511)] * fTemp27) + (fTemp28 * fVec1[((IOTA - iTemp29) & 511)]));
			float fRec18 = (0.0f - (0.600000024f * fTemp21));
			float fTemp30 = (fRec17[1] + (fRec18 + (0.600000024f * fRec15[1])));
			fVec2[(IOTA & 1023)] = fTemp30;
			float fTemp31 = (625.0f * fTemp12);
			float fTemp32 = (fTemp31 + -1.0f);
			int iTemp33 = int(fTemp32);
			int iTemp34 = std::min(2049, std::max(0, iTemp33));
			float fTemp35 = std::floor(fTemp32);
			float fTemp36 = (fTemp35 + (2.0f - fTemp31));
			float fTemp37 = (fTemp31 + (-1.0f - fTemp35));
			int iTemp38 = std::min(2049, std::max(0, (iTemp33 + 1)));
			fRec15[0] = ((fVec2[((IOTA - iTemp34) & 1023)] * fTemp36) + (fTemp37 * fVec2[((IOTA - iTemp38) & 1023)]));
			float fRec16 = (0.0f - (0.600000024f * fTemp30));
			float fTemp39 = (fRec15[1] + (fRec16 + (0.600000024f * fRec13[1])));
			fVec3[(IOTA & 1023)] = fTemp39;
			float fTemp40 = (727.0f * fTemp12);
			float fTemp41 = (fTemp40 + -1.0f);
			int iTemp42 = int(fTemp41);
			int iTemp43 = std::min(2049, std::max(0, iTemp42));
			float fTemp44 = std::floor(fTemp41);
			float fTemp45 = (fTemp44 + (2.0f - fTemp40));
			float fTemp46 = (fTemp40 + (-1.0f - fTemp44));
			int iTemp47 = std::min(2049, std::max(0, (iTemp42 + 1)));
			fRec13[0] = ((fVec3[((IOTA - iTemp43) & 1023)] * fTemp45) + (fTemp46 * fVec3[((IOTA - iTemp47) & 1023)]));
			float fRec14 = (0.0f - (0.600000024f * fTemp39));
			float fTemp48 = (fRec13[1] + (fRec14 + (0.600000024f * fRec11[1])));
			fVec4[(IOTA & 2047)] = fTemp48;
			float fTemp49 = (1331.0f * fTemp12);
			float fTemp50 = (fTemp49 + -1.0f);
			int iTemp51 = int(fTemp50);
			int iTemp52 = std::min(2049, std::max(0, iTemp51));
			float fTemp53 = std::floor(fTemp50);
			float fTemp54 = (fTemp53 + (2.0f - fTemp49));
			float fTemp55 = (fTemp49 + (-1.0f - fTemp53));
			int iTemp56 = std::min(2049, std::max(0, (iTemp51 + 1)));
			fRec11[0] = ((fVec4[((IOTA - iTemp52) & 2047)] * fTemp54) + (fTemp55 * fVec4[((IOTA - iTemp56) & 2047)]));
			float fRec12 = (0.0f - (0.600000024f * fTemp48));
			float fTemp57 = (fRec11[1] + (fRec12 + (0.600000024f * fRec9[1])));
			fVec5[(IOTA & 4095)] = fTemp57;
			float fTemp58 = (2403.0f * fTemp12);
			float fTemp59 = (fTemp58 + -1.0f);
			int iTemp60 = int(fTemp59);
			int iTemp61 = std::min(2049, std::max(0, iTemp60));
			float fTemp62 = std::floor(fTemp59);
			float fTemp63 = (fTemp62 + (2.0f - fTemp58));
			float fTemp64 = (fTemp58 + (-1.0f - fTemp62));
			int iTemp65 = std::min(2049, std::max(0, (iTemp60 + 1)));
			fRec9[0] = ((fVec5[((IOTA - iTemp61) & 4095)] * fTemp63) + (fTemp64 * fVec5[((IOTA - iTemp65) & 4095)]));
			float fRec10 = (0.0f - (0.600000024f * fTemp57));
			float fTemp66 = (fRec10 + fRec9[1]);
			fVec6[(IOTA & 2047)] = fTemp66;
			float fTemp67 = (1356.0f * fTemp12);
			int iTemp68 = int(fTemp67);
			float fTemp69 = std::floor(fTemp67);
			fRec1[0] = (0.353553385f * ((fVec6[((IOTA - std::min(8193, std::max(0, iTemp68))) & 2047)] * (fTemp69 + (1.0f - fTemp67))) + ((fTemp67 - fTemp69) * fVec6[((IOTA - std::min(8193, std::max(0, (iTemp68 + 1)))) & 2047)])));
			fRec39[0] = ((fSlow1 * (fTemp1 - (fRec8[1] + ((fRec2[1] + fRec6[1]) + fRec4[1])))) - (((fTemp4 * fRec39[2]) + (2.0f * (fTemp5 * fRec39[1]))) / fTemp6));
			fRec38[0] = (((fRec39[2] + (fRec39[0] + (2.0f * fRec39[1]))) / fTemp6) - (((fTemp7 * fRec38[2]) + (2.0f * (fTemp5 * fRec38[1]))) / fTemp8));
			float fTemp70 = ((((0.600000024f * fRec36[1]) + ((fRec38[2] + (fRec38[0] + (2.0f * fRec38[1]))) / fTemp8)) + fTemp9) + fTemp10);
			fVec7[(IOTA & 511)] = fTemp70;
			fRec36[0] = ((fTemp18 * fVec7[((IOTA - iTemp16) & 511)]) + (fTemp19 * fVec7[((IOTA - iTemp20) & 511)]));
			float fRec37 = (0.0f - (0.600000024f * fTemp70));
			float fTemp71 = (fRec36[1] + (fRec37 + (0.600000024f * fRec34[1])));
			fVec8[(IOTA & 511)] = fTemp71;
			fRec34[0] = ((fTemp27 * fVec8[((IOTA - iTemp25) & 511)]) + (fTemp28 * fVec8[((IOTA - iTemp29) & 511)]));
			float fRec35 = (0.0f - (0.600000024f * fTemp71));
			float fTemp72 = (fRec34[1] + (fRec35 + (0.600000024f * fRec32[1])));
			fVec9[(IOTA & 1023)] = fTemp72;
			fRec32[0] = ((fTemp36 * fVec9[((IOTA - iTemp34) & 1023)]) + (fTemp37 * fVec9[((IOTA - iTemp38) & 1023)]));
			float fRec33 = (0.0f - (0.600000024f * fTemp72));
			float fTemp73 = (fRec32[1] + (fRec33 + (0.600000024f * fRec30[1])));
			fVec10[(IOTA & 1023)] = fTemp73;
			fRec30[0] = ((fTemp45 * fVec10[((IOTA - iTemp43) & 1023)]) + (fTemp46 * fVec10[((IOTA - iTemp47) & 1023)]));
			float fRec31 = (0.0f - (0.600000024f * fTemp73));
			float fTemp74 = (fRec30[1] + (fRec31 + (0.600000024f * fRec28[1])));
			fVec11[(IOTA & 2047)] = fTemp74;
			fRec28[0] = ((fTemp54 * fVec11[((IOTA - iTemp52) & 2047)]) + (fTemp55 * fVec11[((IOTA - iTemp56) & 2047)]));
			float fRec29 = (0.0f - (0.600000024f * fTemp74));
			float fTemp75 = (fRec28[1] + (fRec29 + (0.600000024f * fRec26[1])));
			fVec12[(IOTA & 4095)] = fTemp75;
			fRec26[0] = ((fTemp63 * fVec12[((IOTA - iTemp61) & 4095)]) + (fTemp64 * fVec12[((IOTA - iTemp65) & 4095)]));
			float fRec27 = (0.0f - (0.600000024f * fTemp75));
			float fTemp76 = (fRec27 + fRec26[1]);
			fVec13[(IOTA & 2047)] = fTemp76;
			float fTemp77 = (1422.0f * fTemp12);
			int iTemp78 = int(fTemp77);
			float fTemp79 = std::floor(fTemp77);
			fRec2[0] = (0.353553385f * ((fVec13[((IOTA - std::min(8193, std::max(0, iTemp78))) & 2047)] * (fTemp79 + (1.0f - fTemp77))) + ((fTemp77 - fTemp79) * fVec13[((IOTA - std::min(8193, std::max(0, (iTemp78 + 1)))) & 2047)])));
			float fTemp80 = (fRec3[1] + fRec7[1]);
			fRec54[0] = ((fSlow1 * ((fRec6[1] + (fTemp0 + fRec2[1])) - (fRec8[1] + (fTemp80 + fRec4[1])))) - (((fTemp4 * fRec54[2]) + (2.0f * (fTemp5 * fRec54[1]))) / fTemp6));
			fRec53[0] = (((fRec54[2] + (fRec54[0] + (2.0f * fRec54[1]))) / fTemp6) - (((fTemp7 * fRec53[2]) + (2.0f * (fTemp5 * fRec53[1]))) / fTemp8));
			float fTemp81 = ((((0.600000024f * fRec51[1]) + ((fRec53[2] + (fRec53[0] + (2.0f * fRec53[1]))) / fTemp8)) + fTemp9) + fTemp10);
			fVec14[(IOTA & 511)] = fTemp81;
			fRec51[0] = ((fTemp18 * fVec14[((IOTA - iTemp16) & 511)]) + (fTemp19 * fVec14[((IOTA - iTemp20) & 511)]));
			float fRec52 = (0.0f - (0.600000024f * fTemp81));
			float fTemp82 = (fRec51[1] + (fRec52 + (0.600000024f * fRec49[1])));
			fVec15[(IOTA & 511)] = fTemp82;
			fRec49[0] = ((fTemp27 * fVec15[((IOTA - iTemp25) & 511)]) + (fTemp28 * fVec15[((IOTA - iTemp29) & 511)]));
			float fRec50 = (0.0f - (0.600000024f * fTemp82));
			float fTemp83 = (fRec49[1] + (fRec50 + (0.600000024f * fRec47[1])));
			fVec16[(IOTA & 1023)] = fTemp83;
			fRec47[0] = ((fTemp36 * fVec16[((IOTA - iTemp34) & 1023)]) + (fTemp37 * fVec16[((IOTA - iTemp38) & 1023)]));
			float fRec48 = (0.0f - (0.600000024f * fTemp83));
			float fTemp84 = (fRec47[1] + (fRec48 + (0.600000024f * fRec45[1])));
			fVec17[(IOTA & 1023)] = fTemp84;
			fRec45[0] = ((fTemp45 * fVec17[((IOTA - iTemp43) & 1023)]) + (fTemp46 * fVec17[((IOTA - iTemp47) & 1023)]));
			float fRec46 = (0.0f - (0.600000024f * fTemp84));
			float fTemp85 = (fRec45[1] + (fRec46 + (0.600000024f * fRec43[1])));
			fVec18[(IOTA & 2047)] = fTemp85;
			fRec43[0] = ((fTemp54 * fVec18[((IOTA - iTemp52) & 2047)]) + (fTemp55 * fVec18[((IOTA - iTemp56) & 2047)]));
			float fRec44 = (0.0f - (0.600000024f * fTemp85));
			float fTemp86 = (fRec43[1] + (fRec44 + (0.600000024f * fRec41[1])));
			fVec19[(IOTA & 4095)] = fTemp86;
			fRec41[0] = ((fTemp63 * fVec19[((IOTA - iTemp61) & 4095)]) + (fTemp64 * fVec19[((IOTA - iTemp65) & 4095)]));
			float fRec42 = (0.0f - (0.600000024f * fTemp86));
			float fTemp87 = (fRec42 + fRec41[1]);
			fVec20[(IOTA & 2047)] = fTemp87;
			float fTemp88 = (1557.0f * fTemp12);
			int iTemp89 = int(fTemp88);
			float fTemp90 = std::floor(fTemp88);
			fRec40[0] = ((0.353553385f * ((fVec20[((IOTA - std::min(8193, std::max(0, iTemp89))) & 2047)] * (fTemp90 + (1.0f - fTemp88))) + ((fTemp88 - fTemp90) * fVec20[((IOTA - std::min(8193, std::max(0, (iTemp89 + 1)))) & 2047)]))) - (fConst5 * ((fConst7 * fRec40[2]) + (fConst8 * fRec40[1]))));
			fRec3[0] = (fConst5 * (((fConst6 * fRec40[0]) + (fConst9 * fRec40[1])) + (fConst6 * fRec40[2])));
			fRec68[0] = ((fSlow1 * ((fRec8[1] + (fTemp0 + fRec4[1])) - (fRec6[1] + (fTemp80 + fRec2[1])))) - (((fTemp4 * fRec68[2]) + (2.0f * (fTemp5 * fRec68[1]))) / fTemp6));
			fRec67[0] = (((fRec68[2] + (fRec68[0] + (2.0f * fRec68[1]))) / fTemp6) - (((fTemp7 * fRec67[2]) + (2.0f * (fTemp5 * fRec67[1]))) / fTemp8));
			float fTemp91 = ((((0.600000024f * fRec65[1]) + ((fRec67[2] + (fRec67[0] + (2.0f * fRec67[1]))) / fTemp8)) + fTemp9) + fTemp10);
			fVec21[(IOTA & 511)] = fTemp91;
			fRec65[0] = ((fTemp18 * fVec21[((IOTA - iTemp16) & 511)]) + (fTemp19 * fVec21[((IOTA - iTemp20) & 511)]));
			float fRec66 = (0.0f - (0.600000024f * fTemp91));
			float fTemp92 = (fRec65[1] + (fRec66 + (0.600000024f * fRec63[1])));
			fVec22[(IOTA & 511)] = fTemp92;
			fRec63[0] = ((fTemp27 * fVec22[((IOTA - iTemp25) & 511)]) + (fTemp28 * fVec22[((IOTA - iTemp29) & 511)]));
			float fRec64 = (0.0f - (0.600000024f * fTemp92));
			float fTemp93 = (fRec63[1] + (fRec64 + (0.600000024f * fRec61[1])));
			fVec23[(IOTA & 1023)] = fTemp93;
			fRec61[0] = ((fTemp36 * fVec23[((IOTA - iTemp34) & 1023)]) + (fTemp37 * fVec23[((IOTA - iTemp38) & 1023)]));
			float fRec62 = (0.0f - (0.600000024f * fTemp93));
			float fTemp94 = (fRec61[1] + (fRec62 + (0.600000024f * fRec59[1])));
			fVec24[(IOTA & 1023)] = fTemp94;
			fRec59[0] = ((fTemp45 * fVec24[((IOTA - iTemp43) & 1023)]) + (fTemp46 * fVec24[((IOTA - iTemp47) & 1023)]));
			float fRec60 = (0.0f - (0.600000024f * fTemp94));
			float fTemp95 = (fRec59[1] + (fRec60 + (0.600000024f * fRec57[1])));
			fVec25[(IOTA & 2047)] = fTemp95;
			fRec57[0] = ((fTemp54 * fVec25[((IOTA - iTemp52) & 2047)]) + (fTemp55 * fVec25[((IOTA - iTemp56) & 2047)]));
			float fRec58 = (0.0f - (0.600000024f * fTemp95));
			float fTemp96 = (fRec57[1] + (fRec58 + (0.600000024f * fRec55[1])));
			fVec26[(IOTA & 4095)] = fTemp96;
			fRec55[0] = ((fTemp63 * fVec26[((IOTA - iTemp61) & 4095)]) + (fTemp64 * fVec26[((IOTA - iTemp65) & 4095)]));
			float fRec56 = (0.0f - (0.600000024f * fTemp96));
			float fTemp97 = (fRec56 + fRec55[1]);
			fVec27[(IOTA & 131071)] = fTemp97;
			float fTemp98 = (1617.0f * fTemp12);
			float fTemp99 = (fTemp98 + 8192.0f);
			fRec69[0] = std::fmod(((fTemp98 + fRec69[1]) + 8191.0f), fTemp99);
			int iTemp100 = int(fRec69[0]);
			float fTemp101 = std::floor(fRec69[0]);
			float fTemp102 = std::min((fRec69[0] / fTemp99), 1.0f);
			float fTemp103 = (fRec69[0] + fTemp98);
			float fTemp104 = (fTemp103 + 8192.0f);
			int iTemp105 = int(fTemp104);
			float fTemp106 = std::floor(fTemp104);
			fRec4[0] = (0.353553385f * ((fSlow4 * fVec27[((IOTA - int(std::min(8192.0f, std::max(0.0f, fTemp99)))) & 131071)]) + (fSlow3 * ((((fVec27[((IOTA - std::min(65537, std::max(0, iTemp100))) & 131071)] * (fTemp101 + (1.0f - fRec69[0]))) + ((fRec69[0] - fTemp101) * fVec27[((IOTA - std::min(65537, std::max(0, (iTemp100 + 1)))) & 131071)])) * fTemp102) + (((fVec27[((IOTA - std::min(65537, std::max(0, iTemp105))) & 131071)] * (fTemp106 + (-8191.0f - fTemp103))) + ((fTemp103 + (8192.0f - fTemp106)) * fVec27[((IOTA - std::min(65537, std::max(0, (iTemp105 + 1)))) & 131071)])) * (1.0f - fTemp102))))));
			float fTemp107 = (fRec1[1] + fRec3[1]);
			float fTemp108 = (fRec5[1] + fRec7[1]);
			fRec83[0] = ((fSlow1 * ((fRec4[1] + (fRec2[1] + fTemp107)) - (fRec8[1] + (fRec6[1] + fTemp108)))) - (((fTemp4 * fRec83[2]) + (2.0f * (fTemp5 * fRec83[1]))) / fTemp6));
			fRec82[0] = (((fRec83[2] + (fRec83[0] + (2.0f * fRec83[1]))) / fTemp6) - (((fTemp7 * fRec82[2]) + (2.0f * (fTemp5 * fRec82[1]))) / fTemp8));
			float fTemp109 = ((((0.600000024f * fRec80[1]) + ((fRec82[2] + (fRec82[0] + (2.0f * fRec82[1]))) / fTemp8)) + fTemp9) + fTemp10);
			fVec28[(IOTA & 511)] = fTemp109;
			fRec80[0] = ((fTemp18 * fVec28[((IOTA - iTemp16) & 511)]) + (fTemp19 * fVec28[((IOTA - iTemp20) & 511)]));
			float fRec81 = (0.0f - (0.600000024f * fTemp109));
			float fTemp110 = (fRec80[1] + (fRec81 + (0.600000024f * fRec78[1])));
			fVec29[(IOTA & 511)] = fTemp110;
			fRec78[0] = ((fTemp27 * fVec29[((IOTA - iTemp25) & 511)]) + (fTemp28 * fVec29[((IOTA - iTemp29) & 511)]));
			float fRec79 = (0.0f - (0.600000024f * fTemp110));
			float fTemp111 = (fRec78[1] + (fRec79 + (0.600000024f * fRec76[1])));
			fVec30[(IOTA & 1023)] = fTemp111;
			fRec76[0] = ((fTemp36 * fVec30[((IOTA - iTemp34) & 1023)]) + (fTemp37 * fVec30[((IOTA - iTemp38) & 1023)]));
			float fRec77 = (0.0f - (0.600000024f * fTemp111));
			float fTemp112 = (fRec76[1] + (fRec77 + (0.600000024f * fRec74[1])));
			fVec31[(IOTA & 1023)] = fTemp112;
			fRec74[0] = ((fTemp45 * fVec31[((IOTA - iTemp43) & 1023)]) + (fTemp46 * fVec31[((IOTA - iTemp47) & 1023)]));
			float fRec75 = (0.0f - (0.600000024f * fTemp112));
			float fTemp113 = (fRec74[1] + (fRec75 + (0.600000024f * fRec72[1])));
			fVec32[(IOTA & 2047)] = fTemp113;
			fRec72[0] = ((fTemp54 * fVec32[((IOTA - iTemp52) & 2047)]) + (fTemp55 * fVec32[((IOTA - iTemp56) & 2047)]));
			float fRec73 = (0.0f - (0.600000024f * fTemp113));
			float fTemp114 = (fRec72[1] + (fRec73 + (0.600000024f * fRec70[1])));
			fVec33[(IOTA & 4095)] = fTemp114;
			fRec70[0] = ((fTemp63 * fVec33[((IOTA - iTemp61) & 4095)]) + (fTemp64 * fVec33[((IOTA - iTemp65) & 4095)]));
			float fRec71 = (0.0f - (0.600000024f * fTemp114));
			float fTemp115 = (fRec71 + fRec70[1]);
			fVec34[(IOTA & 2047)] = fTemp115;
			float fTemp116 = (1933.0f * fTemp12);
			int iTemp117 = int(fTemp116);
			float fTemp118 = std::floor(fTemp116);
			fRec5[0] = (0.353553385f * ((fVec34[((IOTA - std::min(8193, std::max(0, iTemp117))) & 2047)] * (fTemp118 + (1.0f - fTemp116))) + ((fTemp116 - fTemp118) * fVec34[((IOTA - std::min(8193, std::max(0, (iTemp117 + 1)))) & 2047)])));
			fRec97[0] = ((fSlow1 * ((fRec8[1] + (fRec6[1] + fTemp107)) - (fRec4[1] + (fRec2[1] + fTemp108)))) - (((fTemp4 * fRec97[2]) + (2.0f * (fTemp5 * fRec97[1]))) / fTemp6));
			fRec96[0] = (((fRec97[2] + (fRec97[0] + (2.0f * fRec97[1]))) / fTemp6) - (((fTemp7 * fRec96[2]) + (2.0f * (fTemp5 * fRec96[1]))) / fTemp8));
			float fTemp119 = ((((0.600000024f * fRec94[1]) + ((fRec96[2] + (fRec96[0] + (2.0f * fRec96[1]))) / fTemp8)) + fTemp9) + fTemp10);
			fVec35[(IOTA & 511)] = fTemp119;
			fRec94[0] = ((fTemp18 * fVec35[((IOTA - iTemp16) & 511)]) + (fTemp19 * fVec35[((IOTA - iTemp20) & 511)]));
			float fRec95 = (0.0f - (0.600000024f * fTemp119));
			float fTemp120 = (fRec94[1] + (fRec95 + (0.600000024f * fRec92[1])));
			fVec36[(IOTA & 511)] = fTemp120;
			fRec92[0] = ((fTemp27 * fVec36[((IOTA - iTemp25) & 511)]) + (fTemp28 * fVec36[((IOTA - iTemp29) & 511)]));
			float fRec93 = (0.0f - (0.600000024f * fTemp120));
			float fTemp121 = (fRec92[1] + (fRec93 + (0.600000024f * fRec90[1])));
			fVec37[(IOTA & 1023)] = fTemp121;
			fRec90[0] = ((fTemp36 * fVec37[((IOTA - iTemp34) & 1023)]) + (fTemp37 * fVec37[((IOTA - iTemp38) & 1023)]));
			float fRec91 = (0.0f - (0.600000024f * fTemp121));
			float fTemp122 = (fRec90[1] + (fRec91 + (0.600000024f * fRec88[1])));
			fVec38[(IOTA & 1023)] = fTemp122;
			fRec88[0] = ((fTemp45 * fVec38[((IOTA - iTemp43) & 1023)]) + (fTemp46 * fVec38[((IOTA - iTemp47) & 1023)]));
			float fRec89 = (0.0f - (0.600000024f * fTemp122));
			float fTemp123 = (fRec88[1] + (fRec89 + (0.600000024f * fRec86[1])));
			fVec39[(IOTA & 2047)] = fTemp123;
			fRec86[0] = ((fTemp54 * fVec39[((IOTA - iTemp52) & 2047)]) + (fTemp55 * fVec39[((IOTA - iTemp56) & 2047)]));
			float fRec87 = (0.0f - (0.600000024f * fTemp123));
			float fTemp124 = (fRec86[1] + (fRec87 + (0.600000024f * fRec84[1])));
			fVec40[(IOTA & 4095)] = fTemp124;
			fRec84[0] = ((fTemp63 * fVec40[((IOTA - iTemp61) & 4095)]) + (fTemp64 * fVec40[((IOTA - iTemp65) & 4095)]));
			float fRec85 = (0.0f - (0.600000024f * fTemp124));
			float fTemp125 = (fRec85 + fRec84[1]);
			fVec41[(IOTA & 4095)] = fTemp125;
			float fTemp126 = (2401.0f * fTemp12);
			int iTemp127 = int(fTemp126);
			float fTemp128 = std::floor(fTemp126);
			fRec6[0] = (0.353553385f * ((fVec41[((IOTA - std::min(8193, std::max(0, iTemp127))) & 4095)] * (fTemp128 + (1.0f - fTemp126))) + ((fTemp126 - fTemp128) * fVec41[((IOTA - std::min(8193, std::max(0, (iTemp127 + 1)))) & 4095)])));
			float fTemp129 = (fRec1[1] + fRec7[1]);
			float fTemp130 = (fRec5[1] + fRec3[1]);
			fRec111[0] = ((fSlow1 * ((fRec8[1] + (fRec2[1] + fTemp129)) - (fRec4[1] + (fRec6[1] + fTemp130)))) - (((fTemp4 * fRec111[2]) + (2.0f * (fTemp5 * fRec111[1]))) / fTemp6));
			fRec110[0] = (((fRec111[2] + (fRec111[0] + (2.0f * fRec111[1]))) / fTemp6) - (((fTemp7 * fRec110[2]) + (2.0f * (fTemp5 * fRec110[1]))) / fTemp8));
			float fTemp131 = ((((0.600000024f * fRec108[1]) + ((fRec110[2] + (fRec110[0] + (2.0f * fRec110[1]))) / fTemp8)) + fTemp9) + fTemp10);
			fVec42[(IOTA & 511)] = fTemp131;
			fRec108[0] = ((fTemp18 * fVec42[((IOTA - iTemp16) & 511)]) + (fTemp19 * fVec42[((IOTA - iTemp20) & 511)]));
			float fRec109 = (0.0f - (0.600000024f * fTemp131));
			float fTemp132 = (fRec108[1] + (fRec109 + (0.600000024f * fRec106[1])));
			fVec43[(IOTA & 511)] = fTemp132;
			fRec106[0] = ((fTemp27 * fVec43[((IOTA - iTemp25) & 511)]) + (fTemp28 * fVec43[((IOTA - iTemp29) & 511)]));
			float fRec107 = (0.0f - (0.600000024f * fTemp132));
			float fTemp133 = (fRec106[1] + (fRec107 + (0.600000024f * fRec104[1])));
			fVec44[(IOTA & 1023)] = fTemp133;
			fRec104[0] = ((fTemp36 * fVec44[((IOTA - iTemp34) & 1023)]) + (fTemp37 * fVec44[((IOTA - iTemp38) & 1023)]));
			float fRec105 = (0.0f - (0.600000024f * fTemp133));
			float fTemp134 = (fRec104[1] + (fRec105 + (0.600000024f * fRec102[1])));
			fVec45[(IOTA & 1023)] = fTemp134;
			fRec102[0] = ((fTemp45 * fVec45[((IOTA - iTemp43) & 1023)]) + (fTemp46 * fVec45[((IOTA - iTemp47) & 1023)]));
			float fRec103 = (0.0f - (0.600000024f * fTemp134));
			float fTemp135 = (fRec102[1] + (fRec103 + (0.600000024f * fRec100[1])));
			fVec46[(IOTA & 2047)] = fTemp135;
			fRec100[0] = ((fTemp54 * fVec46[((IOTA - iTemp52) & 2047)]) + (fTemp55 * fVec46[((IOTA - iTemp56) & 2047)]));
			float fRec101 = (0.0f - (0.600000024f * fTemp135));
			float fTemp136 = (fRec100[1] + (fRec101 + (0.600000024f * fRec98[1])));
			fVec47[(IOTA & 4095)] = fTemp136;
			fRec98[0] = ((fTemp63 * fVec47[((IOTA - iTemp61) & 4095)]) + (fTemp64 * fVec47[((IOTA - iTemp65) & 4095)]));
			float fRec99 = (0.0f - (0.600000024f * fTemp136));
			float fTemp137 = (fRec99 + fRec98[1]);
			fVec48[(IOTA & 4095)] = fTemp137;
			float fTemp138 = (3125.0f * fTemp12);
			int iTemp139 = int(fTemp138);
			float fTemp140 = std::floor(fTemp138);
			fRec7[0] = (0.353553385f * ((fVec48[((IOTA - std::min(8193, std::max(0, iTemp139))) & 4095)] * (fTemp140 + (1.0f - fTemp138))) + ((fTemp138 - fTemp140) * fVec48[((IOTA - std::min(8193, std::max(0, (iTemp139 + 1)))) & 4095)])));
			fRec125[0] = ((fSlow1 * ((fRec4[1] + (fRec6[1] + fTemp129)) - (fRec8[1] + (fRec2[1] + fTemp130)))) - (((fTemp4 * fRec125[2]) + (2.0f * (fTemp5 * fRec125[1]))) / fTemp6));
			fRec124[0] = (((fRec125[2] + (fRec125[0] + (2.0f * fRec125[1]))) / fTemp6) - (((fTemp7 * fRec124[2]) + (2.0f * (fTemp5 * fRec124[1]))) / fTemp8));
			float fTemp141 = ((((0.600000024f * fRec122[1]) + ((fRec124[2] + (fRec124[0] + (2.0f * fRec124[1]))) / fTemp8)) + fTemp9) + fTemp10);
			fVec49[(IOTA & 511)] = fTemp141;
			fRec122[0] = ((fTemp18 * fVec49[((IOTA - iTemp16) & 511)]) + (fTemp19 * fVec49[((IOTA - iTemp20) & 511)]));
			float fRec123 = (0.0f - (0.600000024f * fTemp141));
			float fTemp142 = (fRec122[1] + (fRec123 + (0.600000024f * fRec120[1])));
			fVec50[(IOTA & 511)] = fTemp142;
			fRec120[0] = ((fTemp27 * fVec50[((IOTA - iTemp25) & 511)]) + (fTemp28 * fVec50[((IOTA - iTemp29) & 511)]));
			float fRec121 = (0.0f - (0.600000024f * fTemp142));
			float fTemp143 = (fRec120[1] + (fRec121 + (0.600000024f * fRec118[1])));
			fVec51[(IOTA & 1023)] = fTemp143;
			fRec118[0] = ((fTemp36 * fVec51[((IOTA - iTemp34) & 1023)]) + (fTemp37 * fVec51[((IOTA - iTemp38) & 1023)]));
			float fRec119 = (0.0f - (0.600000024f * fTemp143));
			float fTemp144 = (fRec118[1] + (fRec119 + (0.600000024f * fRec116[1])));
			fVec52[(IOTA & 1023)] = fTemp144;
			fRec116[0] = ((fTemp45 * fVec52[((IOTA - iTemp43) & 1023)]) + (fTemp46 * fVec52[((IOTA - iTemp47) & 1023)]));
			float fRec117 = (0.0f - (0.600000024f * fTemp144));
			float fTemp145 = (fRec116[1] + (fRec117 + (0.600000024f * fRec114[1])));
			fVec53[(IOTA & 2047)] = fTemp145;
			fRec114[0] = ((fTemp54 * fVec53[((IOTA - iTemp52) & 2047)]) + (fTemp55 * fVec53[((IOTA - iTemp56) & 2047)]));
			float fRec115 = (0.0f - (0.600000024f * fTemp145));
			float fTemp146 = (fRec114[1] + (fRec115 + (0.600000024f * fRec112[1])));
			fVec54[(IOTA & 4095)] = fTemp146;
			fRec112[0] = ((fTemp63 * fVec54[((IOTA - iTemp61) & 4095)]) + (fTemp64 * fVec54[((IOTA - iTemp65) & 4095)]));
			float fRec113 = (0.0f - (0.600000024f * fTemp146));
			float fTemp147 = (fRec113 + fRec112[1]);
			fVec55[(IOTA & 8191)] = fTemp147;
			float fTemp148 = (6561.0f * fTemp12);
			int iTemp149 = int(fTemp148);
			float fTemp150 = std::floor(fTemp148);
			fRec8[0] = (0.353553385f * ((fVec55[((IOTA - std::min(8193, std::max(0, iTemp149))) & 8191)] * (fTemp150 + (1.0f - fTemp148))) + ((fTemp148 - fTemp150) * fVec55[((IOTA - std::min(8193, std::max(0, (iTemp149 + 1)))) & 8191)])));
			float fTemp151 = (((fTemp3 + -1.41421354f) / fTemp2) + 1.0f);
			float fTemp152 = (((fTemp3 + 1.41421354f) / fTemp2) + 1.0f);
			fRec0[0] = ((((fRec1[0] + fRec3[0]) + fRec5[0]) + fRec7[0]) - (((fRec0[2] * fTemp151) + (2.0f * (fTemp5 * fRec0[1]))) / fTemp152));
			fRec126[0] = ((((fRec2[0] + fRec4[0]) + fRec6[0]) + fRec8[0]) - (((fTemp151 * fRec126[2]) + (2.0f * (fTemp5 * fRec126[1]))) / fTemp152));
			float fTemp153 = ((fSlow0 * (((fRec0[2] + (fRec0[0] + (2.0f * fRec0[1]))) + (fRec126[2] + (fRec126[0] + (2.0f * fRec126[1])))) / fTemp152)) + (fSlow5 * (fTemp9 + fTemp10)));
			output0[i] = FAUSTFLOAT(fTemp153);
			output1[i] = FAUSTFLOAT(fTemp153);
			fRec23[1] = fRec23[0];
			fRec22[2] = fRec22[1];
			fRec22[1] = fRec22[0];
			fRec21[2] = fRec21[1];
			fRec21[1] = fRec21[0];
			IOTA = (IOTA + 1);
			fRec25[1] = fRec25[0];
			fRec19[1] = fRec19[0];
			fRec17[1] = fRec17[0];
			fRec15[1] = fRec15[0];
			fRec13[1] = fRec13[0];
			fRec11[1] = fRec11[0];
			fRec9[1] = fRec9[0];
			fRec1[1] = fRec1[0];
			fRec39[2] = fRec39[1];
			fRec39[1] = fRec39[0];
			fRec38[2] = fRec38[1];
			fRec38[1] = fRec38[0];
			fRec36[1] = fRec36[0];
			fRec34[1] = fRec34[0];
			fRec32[1] = fRec32[0];
			fRec30[1] = fRec30[0];
			fRec28[1] = fRec28[0];
			fRec26[1] = fRec26[0];
			fRec2[1] = fRec2[0];
			fRec54[2] = fRec54[1];
			fRec54[1] = fRec54[0];
			fRec53[2] = fRec53[1];
			fRec53[1] = fRec53[0];
			fRec51[1] = fRec51[0];
			fRec49[1] = fRec49[0];
			fRec47[1] = fRec47[0];
			fRec45[1] = fRec45[0];
			fRec43[1] = fRec43[0];
			fRec41[1] = fRec41[0];
			fRec40[2] = fRec40[1];
			fRec40[1] = fRec40[0];
			fRec3[1] = fRec3[0];
			fRec68[2] = fRec68[1];
			fRec68[1] = fRec68[0];
			fRec67[2] = fRec67[1];
			fRec67[1] = fRec67[0];
			fRec65[1] = fRec65[0];
			fRec63[1] = fRec63[0];
			fRec61[1] = fRec61[0];
			fRec59[1] = fRec59[0];
			fRec57[1] = fRec57[0];
			fRec55[1] = fRec55[0];
			fRec69[1] = fRec69[0];
			fRec4[1] = fRec4[0];
			fRec83[2] = fRec83[1];
			fRec83[1] = fRec83[0];
			fRec82[2] = fRec82[1];
			fRec82[1] = fRec82[0];
			fRec80[1] = fRec80[0];
			fRec78[1] = fRec78[0];
			fRec76[1] = fRec76[0];
			fRec74[1] = fRec74[0];
			fRec72[1] = fRec72[0];
			fRec70[1] = fRec70[0];
			fRec5[1] = fRec5[0];
			fRec97[2] = fRec97[1];
			fRec97[1] = fRec97[0];
			fRec96[2] = fRec96[1];
			fRec96[1] = fRec96[0];
			fRec94[1] = fRec94[0];
			fRec92[1] = fRec92[0];
			fRec90[1] = fRec90[0];
			fRec88[1] = fRec88[0];
			fRec86[1] = fRec86[0];
			fRec84[1] = fRec84[0];
			fRec6[1] = fRec6[0];
			fRec111[2] = fRec111[1];
			fRec111[1] = fRec111[0];
			fRec110[2] = fRec110[1];
			fRec110[1] = fRec110[0];
			fRec108[1] = fRec108[0];
			fRec106[1] = fRec106[0];
			fRec104[1] = fRec104[0];
			fRec102[1] = fRec102[0];
			fRec100[1] = fRec100[0];
			fRec98[1] = fRec98[0];
			fRec7[1] = fRec7[0];
			fRec125[2] = fRec125[1];
			fRec125[1] = fRec125[0];
			fRec124[2] = fRec124[1];
			fRec124[1] = fRec124[0];
			fRec122[1] = fRec122[0];
			fRec120[1] = fRec120[0];
			fRec118[1] = fRec118[0];
			fRec116[1] = fRec116[0];
			fRec114[1] = fRec114[0];
			fRec112[1] = fRec112[0];
			fRec8[1] = fRec8[0];
			fRec0[2] = fRec0[1];
			fRec0[1] = fRec0[0];
			fRec126[2] = fRec126[1];
			fRec126[1] = fRec126[0];
			
		}
		
	}

	
};

#endif
