/* ------------------------------------------------------------
name: "wormhole"
Code generated with Faust 2.13.11 (https://faust.grame.fr)
Compilation options: cpp, -vec -lv 0 -vs 32 -ftz 0 -mcd 16
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
	
	int iRec18[2];
	
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
		for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			iRec18[l6] = 0;
			
		}
		
	}
	
	void fillfaust_wormholeSIG0(int count, float* output) {
		for (int i = 0; (i < count); i = (i + 1)) {
			iRec18[0] = (iRec18[1] + 1);
			output[i] = std::sin((9.58738019e-05f * float((iRec18[0] + -1))));
			iRec18[1] = iRec18[0];
			
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
	float fRec15_perm[4];
	FAUSTFLOAT fHslider1;
	float fRec16_perm[4];
	int fSamplingFreq;
	float fConst0;
	float fConst1;
	float fRec14_perm[4];
	float fRec13_perm[4];
	float fConst2;
	float fRec17_perm[4];
	float fYec0[512];
	int fYec0_idx;
	int fYec0_idx_save;
	float fRec11_perm[4];
	float fYec1[512];
	int fYec1_idx;
	int fYec1_idx_save;
	float fRec9_perm[4];
	float fYec2[1024];
	int fYec2_idx;
	int fYec2_idx_save;
	float fRec7_perm[4];
	float fYec3[1024];
	int fYec3_idx;
	int fYec3_idx_save;
	float fRec5_perm[4];
	float fYec4[2048];
	int fYec4_idx;
	int fYec4_idx_save;
	float fRec1_perm[4];
	float fRec28_perm[4];
	float fRec27_perm[4];
	float fYec5[512];
	int fYec5_idx;
	int fYec5_idx_save;
	float fRec25_perm[4];
	float fYec6[512];
	int fYec6_idx;
	int fYec6_idx_save;
	float fRec23_perm[4];
	float fYec7[1024];
	int fYec7_idx;
	int fYec7_idx_save;
	float fRec21_perm[4];
	float fYec8[1024];
	int fYec8_idx;
	int fYec8_idx_save;
	float fRec19_perm[4];
	float fYec9[2048];
	int fYec9_idx;
	int fYec9_idx_save;
	float fRec2_perm[4];
	float fRec39_perm[4];
	float fRec38_perm[4];
	float fYec10[512];
	int fYec10_idx;
	int fYec10_idx_save;
	float fRec36_perm[4];
	float fYec11[512];
	int fYec11_idx;
	int fYec11_idx_save;
	float fRec34_perm[4];
	float fYec12[1024];
	int fYec12_idx;
	int fYec12_idx_save;
	float fRec32_perm[4];
	float fYec13[1024];
	int fYec13_idx;
	int fYec13_idx_save;
	float fRec30_perm[4];
	float fYec14[2048];
	int fYec14_idx;
	int fYec14_idx_save;
	float fConst3;
	float fConst4;
	float fConst5;
	float fConst6;
	float fConst7;
	float fConst8;
	float fConst9;
	float fRec29_perm[4];
	float fConst10;
	float fRec3_perm[4];
	float fRec49_perm[4];
	float fRec48_perm[4];
	float fYec15[512];
	int fYec15_idx;
	int fYec15_idx_save;
	float fRec46_perm[4];
	float fYec16[512];
	int fYec16_idx;
	int fYec16_idx_save;
	float fRec44_perm[4];
	float fYec17[1024];
	int fYec17_idx;
	int fYec17_idx_save;
	float fRec42_perm[4];
	float fYec18[1024];
	int fYec18_idx;
	int fYec18_idx_save;
	float fRec40_perm[4];
	float fRec50_perm[4];
	FAUSTFLOAT fHslider2;
	float fYec19[131072];
	int fYec19_idx;
	int fYec19_idx_save;
	float fRec4_perm[4];
	float fRec0_perm[4];
	float fRec51_perm[4];
	FAUSTFLOAT fHslider3;
	
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
		return 1;
		
	}
	virtual int getNumOutputs() {
		return 2;
		
	}
	virtual int getInputRate(int channel) {
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
		fConst0 = std::min<float>(192000.0f, std::max<float>(1.0f, float(fSamplingFreq)));
		fConst1 = (3.14159274f / fConst0);
		fConst2 = (0.25f / fConst0);
		fConst3 = std::tan((314.159271f / fConst0));
		fConst4 = (1.0f / fConst3);
		fConst5 = (1.0f / (((fConst4 + 1.41421354f) / fConst3) + 1.0f));
		fConst6 = (((fConst4 + -1.41421354f) / fConst3) + 1.0f);
		fConst7 = faust_wormhole_faustpower2_f(fConst3);
		fConst8 = (1.0f / fConst7);
		fConst9 = (2.0f * (1.0f - fConst8));
		fConst10 = (0.0f - (2.0f / fConst7));
		
	}
	
	virtual void instanceResetUserInterface() {
		fHslider0 = FAUSTFLOAT(0.5f);
		fHslider1 = FAUSTFLOAT(4000.0f);
		fHslider2 = FAUSTFLOAT(0.0f);
		fHslider3 = FAUSTFLOAT(0.5f);
		
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; (l0 < 4); l0 = (l0 + 1)) {
			fRec15_perm[l0] = 0.0f;
			
		}
		for (int l1 = 0; (l1 < 4); l1 = (l1 + 1)) {
			fRec16_perm[l1] = 0.0f;
			
		}
		for (int l2 = 0; (l2 < 4); l2 = (l2 + 1)) {
			fRec14_perm[l2] = 0.0f;
			
		}
		for (int l3 = 0; (l3 < 4); l3 = (l3 + 1)) {
			fRec13_perm[l3] = 0.0f;
			
		}
		for (int l4 = 0; (l4 < 4); l4 = (l4 + 1)) {
			fRec17_perm[l4] = 0.0f;
			
		}
		for (int l5 = 0; (l5 < 512); l5 = (l5 + 1)) {
			fYec0[l5] = 0.0f;
			
		}
		fYec0_idx = 0;
		fYec0_idx_save = 0;
		for (int l7 = 0; (l7 < 4); l7 = (l7 + 1)) {
			fRec11_perm[l7] = 0.0f;
			
		}
		for (int l8 = 0; (l8 < 512); l8 = (l8 + 1)) {
			fYec1[l8] = 0.0f;
			
		}
		fYec1_idx = 0;
		fYec1_idx_save = 0;
		for (int l9 = 0; (l9 < 4); l9 = (l9 + 1)) {
			fRec9_perm[l9] = 0.0f;
			
		}
		for (int l10 = 0; (l10 < 1024); l10 = (l10 + 1)) {
			fYec2[l10] = 0.0f;
			
		}
		fYec2_idx = 0;
		fYec2_idx_save = 0;
		for (int l11 = 0; (l11 < 4); l11 = (l11 + 1)) {
			fRec7_perm[l11] = 0.0f;
			
		}
		for (int l12 = 0; (l12 < 1024); l12 = (l12 + 1)) {
			fYec3[l12] = 0.0f;
			
		}
		fYec3_idx = 0;
		fYec3_idx_save = 0;
		for (int l13 = 0; (l13 < 4); l13 = (l13 + 1)) {
			fRec5_perm[l13] = 0.0f;
			
		}
		for (int l14 = 0; (l14 < 2048); l14 = (l14 + 1)) {
			fYec4[l14] = 0.0f;
			
		}
		fYec4_idx = 0;
		fYec4_idx_save = 0;
		for (int l15 = 0; (l15 < 4); l15 = (l15 + 1)) {
			fRec1_perm[l15] = 0.0f;
			
		}
		for (int l16 = 0; (l16 < 4); l16 = (l16 + 1)) {
			fRec28_perm[l16] = 0.0f;
			
		}
		for (int l17 = 0; (l17 < 4); l17 = (l17 + 1)) {
			fRec27_perm[l17] = 0.0f;
			
		}
		for (int l18 = 0; (l18 < 512); l18 = (l18 + 1)) {
			fYec5[l18] = 0.0f;
			
		}
		fYec5_idx = 0;
		fYec5_idx_save = 0;
		for (int l19 = 0; (l19 < 4); l19 = (l19 + 1)) {
			fRec25_perm[l19] = 0.0f;
			
		}
		for (int l20 = 0; (l20 < 512); l20 = (l20 + 1)) {
			fYec6[l20] = 0.0f;
			
		}
		fYec6_idx = 0;
		fYec6_idx_save = 0;
		for (int l21 = 0; (l21 < 4); l21 = (l21 + 1)) {
			fRec23_perm[l21] = 0.0f;
			
		}
		for (int l22 = 0; (l22 < 1024); l22 = (l22 + 1)) {
			fYec7[l22] = 0.0f;
			
		}
		fYec7_idx = 0;
		fYec7_idx_save = 0;
		for (int l23 = 0; (l23 < 4); l23 = (l23 + 1)) {
			fRec21_perm[l23] = 0.0f;
			
		}
		for (int l24 = 0; (l24 < 1024); l24 = (l24 + 1)) {
			fYec8[l24] = 0.0f;
			
		}
		fYec8_idx = 0;
		fYec8_idx_save = 0;
		for (int l25 = 0; (l25 < 4); l25 = (l25 + 1)) {
			fRec19_perm[l25] = 0.0f;
			
		}
		for (int l26 = 0; (l26 < 2048); l26 = (l26 + 1)) {
			fYec9[l26] = 0.0f;
			
		}
		fYec9_idx = 0;
		fYec9_idx_save = 0;
		for (int l27 = 0; (l27 < 4); l27 = (l27 + 1)) {
			fRec2_perm[l27] = 0.0f;
			
		}
		for (int l28 = 0; (l28 < 4); l28 = (l28 + 1)) {
			fRec39_perm[l28] = 0.0f;
			
		}
		for (int l29 = 0; (l29 < 4); l29 = (l29 + 1)) {
			fRec38_perm[l29] = 0.0f;
			
		}
		for (int l30 = 0; (l30 < 512); l30 = (l30 + 1)) {
			fYec10[l30] = 0.0f;
			
		}
		fYec10_idx = 0;
		fYec10_idx_save = 0;
		for (int l31 = 0; (l31 < 4); l31 = (l31 + 1)) {
			fRec36_perm[l31] = 0.0f;
			
		}
		for (int l32 = 0; (l32 < 512); l32 = (l32 + 1)) {
			fYec11[l32] = 0.0f;
			
		}
		fYec11_idx = 0;
		fYec11_idx_save = 0;
		for (int l33 = 0; (l33 < 4); l33 = (l33 + 1)) {
			fRec34_perm[l33] = 0.0f;
			
		}
		for (int l34 = 0; (l34 < 1024); l34 = (l34 + 1)) {
			fYec12[l34] = 0.0f;
			
		}
		fYec12_idx = 0;
		fYec12_idx_save = 0;
		for (int l35 = 0; (l35 < 4); l35 = (l35 + 1)) {
			fRec32_perm[l35] = 0.0f;
			
		}
		for (int l36 = 0; (l36 < 1024); l36 = (l36 + 1)) {
			fYec13[l36] = 0.0f;
			
		}
		fYec13_idx = 0;
		fYec13_idx_save = 0;
		for (int l37 = 0; (l37 < 4); l37 = (l37 + 1)) {
			fRec30_perm[l37] = 0.0f;
			
		}
		for (int l38 = 0; (l38 < 2048); l38 = (l38 + 1)) {
			fYec14[l38] = 0.0f;
			
		}
		fYec14_idx = 0;
		fYec14_idx_save = 0;
		for (int l39 = 0; (l39 < 4); l39 = (l39 + 1)) {
			fRec29_perm[l39] = 0.0f;
			
		}
		for (int l40 = 0; (l40 < 4); l40 = (l40 + 1)) {
			fRec3_perm[l40] = 0.0f;
			
		}
		for (int l41 = 0; (l41 < 4); l41 = (l41 + 1)) {
			fRec49_perm[l41] = 0.0f;
			
		}
		for (int l42 = 0; (l42 < 4); l42 = (l42 + 1)) {
			fRec48_perm[l42] = 0.0f;
			
		}
		for (int l43 = 0; (l43 < 512); l43 = (l43 + 1)) {
			fYec15[l43] = 0.0f;
			
		}
		fYec15_idx = 0;
		fYec15_idx_save = 0;
		for (int l44 = 0; (l44 < 4); l44 = (l44 + 1)) {
			fRec46_perm[l44] = 0.0f;
			
		}
		for (int l45 = 0; (l45 < 512); l45 = (l45 + 1)) {
			fYec16[l45] = 0.0f;
			
		}
		fYec16_idx = 0;
		fYec16_idx_save = 0;
		for (int l46 = 0; (l46 < 4); l46 = (l46 + 1)) {
			fRec44_perm[l46] = 0.0f;
			
		}
		for (int l47 = 0; (l47 < 1024); l47 = (l47 + 1)) {
			fYec17[l47] = 0.0f;
			
		}
		fYec17_idx = 0;
		fYec17_idx_save = 0;
		for (int l48 = 0; (l48 < 4); l48 = (l48 + 1)) {
			fRec42_perm[l48] = 0.0f;
			
		}
		for (int l49 = 0; (l49 < 1024); l49 = (l49 + 1)) {
			fYec18[l49] = 0.0f;
			
		}
		fYec18_idx = 0;
		fYec18_idx_save = 0;
		for (int l50 = 0; (l50 < 4); l50 = (l50 + 1)) {
			fRec40_perm[l50] = 0.0f;
			
		}
		for (int l51 = 0; (l51 < 4); l51 = (l51 + 1)) {
			fRec50_perm[l51] = 0.0f;
			
		}
		for (int l52 = 0; (l52 < 131072); l52 = (l52 + 1)) {
			fYec19[l52] = 0.0f;
			
		}
		fYec19_idx = 0;
		fYec19_idx_save = 0;
		for (int l53 = 0; (l53 < 4); l53 = (l53 + 1)) {
			fRec4_perm[l53] = 0.0f;
			
		}
		for (int l54 = 0; (l54 < 4); l54 = (l54 + 1)) {
			fRec0_perm[l54] = 0.0f;
			
		}
		for (int l55 = 0; (l55 < 4); l55 = (l55 + 1)) {
			fRec51_perm[l55] = 0.0f;
			
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
		ui_interface->addHorizontalSlider("LENGTH", &fHslider0, 0.5f, 0.0f, 1.5f, 0.00999999978f);
		ui_interface->addHorizontalSlider("MIX", &fHslider3, 0.5f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface->declare(&fHslider1, "scale", "log");
		ui_interface->addHorizontalSlider("SHAPE", &fHslider1, 4000.0f, 100.0f, 14000.0f, 0.00999999978f);
		ui_interface->addHorizontalSlider("SHIMMER", &fHslider2, 0.0f, 0.0f, 1.20000005f, 0.00999999978f);
		ui_interface->closeBox();
		
	}
	
	virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
		FAUSTFLOAT* input0_ptr = inputs[0];
		FAUSTFLOAT* output0_ptr = outputs[0];
		FAUSTFLOAT* output1_ptr = outputs[1];
		float fSlow0 = (0.00100000005f * float(fHslider0));
		float fRec15_tmp[36];
		float* fRec15 = &fRec15_tmp[4];
		float fSlow1 = (0.00100000005f * float(fHslider1));
		float fRec16_tmp[36];
		float* fRec16 = &fRec16_tmp[4];
		float fZec0[32];
		float fZec1[32];
		float fZec2[32];
		float fZec3[32];
		float fZec4[32];
		float fZec5[32];
		float fZec6[32];
		float fZec7[32];
		float fZec8[32];
		float fZec9[32];
		float fZec10[32];
		float fZec11[32];
		float fRec14_tmp[36];
		float* fRec14 = &fRec14_tmp[4];
		float fZec12[32];
		float fZec13[32];
		float fZec14[32];
		float fZec15[32];
		float fRec13_tmp[36];
		float* fRec13 = &fRec13_tmp[4];
		float fZec16[32];
		float fRec17_tmp[36];
		float* fRec17 = &fRec17_tmp[4];
		float fZec17[32];
		float fZec18[32];
		float fZec19[32];
		float fZec20[32];
		int iZec21[32];
		int iZec22[32];
		float fZec23[32];
		float fZec24[32];
		float fZec25[32];
		int iZec26[32];
		float fRec11_tmp[36];
		float* fRec11 = &fRec11_tmp[4];
		float fRec12[32];
		float fZec27[32];
		float fZec28[32];
		float fZec29[32];
		int iZec30[32];
		int iZec31[32];
		float fZec32[32];
		float fZec33[32];
		float fZec34[32];
		int iZec35[32];
		float fRec9_tmp[36];
		float* fRec9 = &fRec9_tmp[4];
		float fRec10[32];
		float fZec36[32];
		float fZec37[32];
		float fZec38[32];
		int iZec39[32];
		int iZec40[32];
		float fZec41[32];
		float fZec42[32];
		float fZec43[32];
		int iZec44[32];
		float fRec7_tmp[36];
		float* fRec7 = &fRec7_tmp[4];
		float fRec8[32];
		float fZec45[32];
		float fZec46[32];
		float fZec47[32];
		int iZec48[32];
		int iZec49[32];
		float fZec50[32];
		float fZec51[32];
		float fZec52[32];
		int iZec53[32];
		float fRec5_tmp[36];
		float* fRec5 = &fRec5_tmp[4];
		float fRec6[32];
		float fZec54[32];
		int iZec55[32];
		float fZec56[32];
		float fRec1_tmp[36];
		float* fRec1 = &fRec1_tmp[4];
		float fZec57[32];
		float fZec58[32];
		float fRec28_tmp[36];
		float* fRec28 = &fRec28_tmp[4];
		float fZec59[32];
		float fZec60[32];
		float fRec27_tmp[36];
		float* fRec27 = &fRec27_tmp[4];
		float fZec61[32];
		float fRec25_tmp[36];
		float* fRec25 = &fRec25_tmp[4];
		float fRec26[32];
		float fZec62[32];
		float fRec23_tmp[36];
		float* fRec23 = &fRec23_tmp[4];
		float fRec24[32];
		float fZec63[32];
		float fRec21_tmp[36];
		float* fRec21 = &fRec21_tmp[4];
		float fRec22[32];
		float fZec64[32];
		float fRec19_tmp[36];
		float* fRec19 = &fRec19_tmp[4];
		float fRec20[32];
		float fZec65[32];
		int iZec66[32];
		float fZec67[32];
		float fRec2_tmp[36];
		float* fRec2 = &fRec2_tmp[4];
		float fZec68[32];
		float fZec69[32];
		float fRec39_tmp[36];
		float* fRec39 = &fRec39_tmp[4];
		float fZec70[32];
		float fZec71[32];
		float fRec38_tmp[36];
		float* fRec38 = &fRec38_tmp[4];
		float fZec72[32];
		float fRec36_tmp[36];
		float* fRec36 = &fRec36_tmp[4];
		float fRec37[32];
		float fZec73[32];
		float fRec34_tmp[36];
		float* fRec34 = &fRec34_tmp[4];
		float fRec35[32];
		float fZec74[32];
		float fRec32_tmp[36];
		float* fRec32 = &fRec32_tmp[4];
		float fRec33[32];
		float fZec75[32];
		float fRec30_tmp[36];
		float* fRec30 = &fRec30_tmp[4];
		float fRec31[32];
		float fZec76[32];
		int iZec77[32];
		float fZec78[32];
		float fZec79[32];
		float fZec80[32];
		float fRec29_tmp[36];
		float* fRec29 = &fRec29_tmp[4];
		float fRec3_tmp[36];
		float* fRec3 = &fRec3_tmp[4];
		float fZec81[32];
		float fZec82[32];
		float fRec49_tmp[36];
		float* fRec49 = &fRec49_tmp[4];
		float fZec83[32];
		float fZec84[32];
		float fRec48_tmp[36];
		float* fRec48 = &fRec48_tmp[4];
		float fZec85[32];
		float fRec46_tmp[36];
		float* fRec46 = &fRec46_tmp[4];
		float fRec47[32];
		float fZec86[32];
		float fRec44_tmp[36];
		float* fRec44 = &fRec44_tmp[4];
		float fRec45[32];
		float fZec87[32];
		float fRec42_tmp[36];
		float* fRec42 = &fRec42_tmp[4];
		float fRec43[32];
		float fZec88[32];
		float fRec40_tmp[36];
		float* fRec40 = &fRec40_tmp[4];
		float fRec41[32];
		float fZec89[32];
		float fZec90[32];
		float fRec50_tmp[36];
		float* fRec50 = &fRec50_tmp[4];
		float fSlow2 = float(fHslider2);
		float fSlow3 = (1.0f - fSlow2);
		int iZec91[32];
		float fZec92[32];
		float fZec93[32];
		float fZec94[32];
		float fZec95[32];
		int iZec96[32];
		float fZec97[32];
		float fRec4_tmp[36];
		float* fRec4 = &fRec4_tmp[4];
		float fZec98[32];
		float fZec99[32];
		float fZec100[32];
		float fZec101[32];
		float fRec0_tmp[36];
		float* fRec0 = &fRec0_tmp[4];
		float fZec102[32];
		float fZec103[32];
		float fRec51_tmp[36];
		float* fRec51 = &fRec51_tmp[4];
		float fSlow4 = float(fHslider3);
		float fSlow5 = (2.0f * (1.0f - fSlow4));
		float fZec104[32];
		int fullcount = count;
		int vindex = 0;
		/* Main loop */
		for (vindex = 0; (vindex <= (fullcount - 32)); vindex = (vindex + 32)) {
			FAUSTFLOAT* input0 = &input0_ptr[vindex];
			FAUSTFLOAT* output0 = &output0_ptr[vindex];
			FAUSTFLOAT* output1 = &output1_ptr[vindex];
			int vsize = 32;
			/* Recursive loop 0 */
			/* Pre code */
			for (int j8 = 0; (j8 < 4); j8 = (j8 + 1)) {
				fRec17_tmp[j8] = fRec17_perm[j8];
				
			}
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec16[i] = fRec17[(i - 1)];
				fRec17[i] = (fConst2 + (fZec16[i] - std::floor((fConst2 + fZec16[i]))));
				
			}
			/* Post code */
			for (int j9 = 0; (j9 < 4); j9 = (j9 + 1)) {
				fRec17_perm[j9] = fRec17_tmp[(vsize + j9)];
				
			}
			/* Vectorizable loop 1 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec18[i] = ((0.00100000005f * ftbl0faust_wormholeSIG0[int((65536.0f * fRec17[i]))]) + 1.0f);
				
			}
			/* Vectorizable loop 2 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec89[i] = (1617.0f * fZec18[i]);
				
			}
			/* Vectorizable loop 3 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec90[i] = (fZec89[i] + 8192.0f);
				
			}
			/* Recursive loop 4 */
			/* Pre code */
			for (int j2 = 0; (j2 < 4); j2 = (j2 + 1)) {
				fRec16_tmp[j2] = fRec16_perm[j2];
				
			}
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fRec16[i] = (fSlow1 + (0.999000013f * fRec16[(i - 1)]));
				
			}
			/* Post code */
			for (int j3 = 0; (j3 < 4); j3 = (j3 + 1)) {
				fRec16_perm[j3] = fRec16_tmp[(vsize + j3)];
				
			}
			/* Vectorizable loop 5 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec19[i] = (343.0f * fZec18[i]);
				
			}
			/* Vectorizable loop 6 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec28[i] = (441.0f * fZec18[i]);
				
			}
			/* Vectorizable loop 7 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec37[i] = (625.0f * fZec18[i]);
				
			}
			/* Vectorizable loop 8 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec46[i] = (727.0f * fZec18[i]);
				
			}
			/* Recursive loop 9 */
			/* Pre code */
			for (int j62 = 0; (j62 < 4); j62 = (j62 + 1)) {
				fRec50_tmp[j62] = fRec50_perm[j62];
				
			}
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fRec50[i] = std::fmod(((fZec89[i] + fRec50[(i - 1)]) + 8191.0f), fZec90[i]);
				
			}
			/* Post code */
			for (int j63 = 0; (j63 < 4); j63 = (j63 + 1)) {
				fRec50_perm[j63] = fRec50_tmp[(vsize + j63)];
				
			}
			/* Vectorizable loop 10 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec6[i] = std::tan((fConst1 * fRec16[i]));
				
			}
			/* Vectorizable loop 11 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec20[i] = (fZec19[i] + -1.0f);
				
			}
			/* Vectorizable loop 12 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec29[i] = (fZec28[i] + -1.0f);
				
			}
			/* Vectorizable loop 13 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec38[i] = (fZec37[i] + -1.0f);
				
			}
			/* Vectorizable loop 14 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec47[i] = (fZec46[i] + -1.0f);
				
			}
			/* Vectorizable loop 15 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec94[i] = (fRec50[i] + fZec89[i]);
				
			}
			/* Vectorizable loop 16 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec7[i] = (1.0f / fZec6[i]);
				
			}
			/* Vectorizable loop 17 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec23[i] = std::floor(fZec20[i]);
				
			}
			/* Vectorizable loop 18 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				iZec21[i] = int(fZec20[i]);
				
			}
			/* Vectorizable loop 19 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				iZec30[i] = int(fZec29[i]);
				
			}
			/* Vectorizable loop 20 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec32[i] = std::floor(fZec29[i]);
				
			}
			/* Vectorizable loop 21 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				iZec39[i] = int(fZec38[i]);
				
			}
			/* Vectorizable loop 22 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec41[i] = std::floor(fZec38[i]);
				
			}
			/* Vectorizable loop 23 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				iZec48[i] = int(fZec47[i]);
				
			}
			/* Vectorizable loop 24 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec50[i] = std::floor(fZec47[i]);
				
			}
			/* Vectorizable loop 25 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec54[i] = (1356.0f * fZec18[i]);
				
			}
			/* Vectorizable loop 26 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec65[i] = (1422.0f * fZec18[i]);
				
			}
			/* Vectorizable loop 27 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec76[i] = (1557.0f * fZec18[i]);
				
			}
			/* Vectorizable loop 28 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec95[i] = (fZec94[i] + 8192.0f);
				
			}
			/* Recursive loop 29 */
			/* Pre code */
			for (int j0 = 0; (j0 < 4); j0 = (j0 + 1)) {
				fRec15_tmp[j0] = fRec15_perm[j0];
				
			}
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fRec15[i] = (fSlow0 + (0.999000013f * fRec15[(i - 1)]));
				
			}
			/* Post code */
			for (int j1 = 0; (j1 < 4); j1 = (j1 + 1)) {
				fRec15_perm[j1] = fRec15_tmp[(vsize + j1)];
				
			}
			/* Vectorizable loop 30 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec10[i] = (1.0f - (1.0f / faust_wormhole_faustpower2_f(fZec6[i])));
				
			}
			/* Vectorizable loop 31 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec11[i] = (((fZec7[i] + 1.84775901f) / fZec6[i]) + 1.0f);
				
			}
			/* Vectorizable loop 32 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec8[i] = (((fZec7[i] + -1.84775901f) / fZec6[i]) + 1.0f);
				
			}
			/* Vectorizable loop 33 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec24[i] = (fZec23[i] + (2.0f - fZec19[i]));
				
			}
			/* Vectorizable loop 34 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec13[i] = (((fZec7[i] + -0.765366852f) / fZec6[i]) + 1.0f);
				
			}
			/* Vectorizable loop 35 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec15[i] = (((fZec7[i] + 0.765366852f) / fZec6[i]) + 1.0f);
				
			}
			/* Vectorizable loop 36 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				iZec22[i] = std::min<int>(2049, std::max<int>(0, iZec21[i]));
				
			}
			/* Vectorizable loop 37 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec25[i] = (fZec19[i] + (-1.0f - fZec23[i]));
				
			}
			/* Vectorizable loop 38 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				iZec26[i] = std::min<int>(2049, std::max<int>(0, (iZec21[i] + 1)));
				
			}
			/* Vectorizable loop 39 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				iZec31[i] = std::min<int>(2049, std::max<int>(0, iZec30[i]));
				
			}
			/* Vectorizable loop 40 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec33[i] = (fZec32[i] + (2.0f - fZec28[i]));
				
			}
			/* Vectorizable loop 41 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec34[i] = (fZec28[i] + (-1.0f - fZec32[i]));
				
			}
			/* Vectorizable loop 42 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				iZec35[i] = std::min<int>(2049, std::max<int>(0, (iZec30[i] + 1)));
				
			}
			/* Vectorizable loop 43 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				iZec40[i] = std::min<int>(2049, std::max<int>(0, iZec39[i]));
				
			}
			/* Vectorizable loop 44 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec42[i] = (fZec41[i] + (2.0f - fZec37[i]));
				
			}
			/* Vectorizable loop 45 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec43[i] = (fZec37[i] + (-1.0f - fZec41[i]));
				
			}
			/* Vectorizable loop 46 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				iZec44[i] = std::min<int>(2049, std::max<int>(0, (iZec39[i] + 1)));
				
			}
			/* Vectorizable loop 47 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				iZec49[i] = std::min<int>(2049, std::max<int>(0, iZec48[i]));
				
			}
			/* Vectorizable loop 48 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec51[i] = (fZec50[i] + (2.0f - fZec46[i]));
				
			}
			/* Vectorizable loop 49 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec52[i] = (fZec46[i] + (-1.0f - fZec50[i]));
				
			}
			/* Vectorizable loop 50 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				iZec53[i] = std::min<int>(2049, std::max<int>(0, (iZec48[i] + 1)));
				
			}
			/* Vectorizable loop 51 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				iZec55[i] = int(fZec54[i]);
				
			}
			/* Vectorizable loop 52 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec56[i] = std::floor(fZec54[i]);
				
			}
			/* Vectorizable loop 53 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				iZec66[i] = int(fZec65[i]);
				
			}
			/* Vectorizable loop 54 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec67[i] = std::floor(fZec65[i]);
				
			}
			/* Vectorizable loop 55 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				iZec77[i] = int(fZec76[i]);
				
			}
			/* Vectorizable loop 56 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec78[i] = std::floor(fZec76[i]);
				
			}
			/* Vectorizable loop 57 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				iZec91[i] = int(fRec50[i]);
				
			}
			/* Vectorizable loop 58 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec92[i] = std::floor(fRec50[i]);
				
			}
			/* Vectorizable loop 59 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec93[i] = std::min<float>((fRec50[i] / fZec90[i]), 1.0f);
				
			}
			/* Vectorizable loop 60 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				iZec96[i] = int(fZec95[i]);
				
			}
			/* Vectorizable loop 61 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec97[i] = std::floor(fZec95[i]);
				
			}
			/* Recursive loop 62 */
			/* Pre code */
			for (int j4 = 0; (j4 < 4); j4 = (j4 + 1)) {
				fRec14_tmp[j4] = fRec14_perm[j4];
				
			}
			for (int j6 = 0; (j6 < 4); j6 = (j6 + 1)) {
				fRec13_tmp[j6] = fRec13_perm[j6];
				
			}
			fYec0_idx = ((fYec0_idx + fYec0_idx_save) & 511);
			for (int j10 = 0; (j10 < 4); j10 = (j10 + 1)) {
				fRec11_tmp[j10] = fRec11_perm[j10];
				
			}
			fYec1_idx = ((fYec1_idx + fYec1_idx_save) & 511);
			for (int j12 = 0; (j12 < 4); j12 = (j12 + 1)) {
				fRec9_tmp[j12] = fRec9_perm[j12];
				
			}
			fYec2_idx = ((fYec2_idx + fYec2_idx_save) & 1023);
			for (int j14 = 0; (j14 < 4); j14 = (j14 + 1)) {
				fRec7_tmp[j14] = fRec7_perm[j14];
				
			}
			fYec3_idx = ((fYec3_idx + fYec3_idx_save) & 1023);
			for (int j16 = 0; (j16 < 4); j16 = (j16 + 1)) {
				fRec5_tmp[j16] = fRec5_perm[j16];
				
			}
			fYec4_idx = ((fYec4_idx + fYec4_idx_save) & 2047);
			for (int j18 = 0; (j18 < 4); j18 = (j18 + 1)) {
				fRec1_tmp[j18] = fRec1_perm[j18];
				
			}
			for (int j20 = 0; (j20 < 4); j20 = (j20 + 1)) {
				fRec28_tmp[j20] = fRec28_perm[j20];
				
			}
			for (int j22 = 0; (j22 < 4); j22 = (j22 + 1)) {
				fRec27_tmp[j22] = fRec27_perm[j22];
				
			}
			fYec5_idx = ((fYec5_idx + fYec5_idx_save) & 511);
			for (int j24 = 0; (j24 < 4); j24 = (j24 + 1)) {
				fRec25_tmp[j24] = fRec25_perm[j24];
				
			}
			fYec6_idx = ((fYec6_idx + fYec6_idx_save) & 511);
			for (int j26 = 0; (j26 < 4); j26 = (j26 + 1)) {
				fRec23_tmp[j26] = fRec23_perm[j26];
				
			}
			fYec7_idx = ((fYec7_idx + fYec7_idx_save) & 1023);
			for (int j28 = 0; (j28 < 4); j28 = (j28 + 1)) {
				fRec21_tmp[j28] = fRec21_perm[j28];
				
			}
			fYec8_idx = ((fYec8_idx + fYec8_idx_save) & 1023);
			for (int j30 = 0; (j30 < 4); j30 = (j30 + 1)) {
				fRec19_tmp[j30] = fRec19_perm[j30];
				
			}
			fYec9_idx = ((fYec9_idx + fYec9_idx_save) & 2047);
			for (int j32 = 0; (j32 < 4); j32 = (j32 + 1)) {
				fRec2_tmp[j32] = fRec2_perm[j32];
				
			}
			for (int j34 = 0; (j34 < 4); j34 = (j34 + 1)) {
				fRec39_tmp[j34] = fRec39_perm[j34];
				
			}
			for (int j36 = 0; (j36 < 4); j36 = (j36 + 1)) {
				fRec38_tmp[j36] = fRec38_perm[j36];
				
			}
			fYec10_idx = ((fYec10_idx + fYec10_idx_save) & 511);
			for (int j38 = 0; (j38 < 4); j38 = (j38 + 1)) {
				fRec36_tmp[j38] = fRec36_perm[j38];
				
			}
			fYec11_idx = ((fYec11_idx + fYec11_idx_save) & 511);
			for (int j40 = 0; (j40 < 4); j40 = (j40 + 1)) {
				fRec34_tmp[j40] = fRec34_perm[j40];
				
			}
			fYec12_idx = ((fYec12_idx + fYec12_idx_save) & 1023);
			for (int j42 = 0; (j42 < 4); j42 = (j42 + 1)) {
				fRec32_tmp[j42] = fRec32_perm[j42];
				
			}
			fYec13_idx = ((fYec13_idx + fYec13_idx_save) & 1023);
			for (int j44 = 0; (j44 < 4); j44 = (j44 + 1)) {
				fRec30_tmp[j44] = fRec30_perm[j44];
				
			}
			fYec14_idx = ((fYec14_idx + fYec14_idx_save) & 2047);
			for (int j46 = 0; (j46 < 4); j46 = (j46 + 1)) {
				fRec29_tmp[j46] = fRec29_perm[j46];
				
			}
			for (int j48 = 0; (j48 < 4); j48 = (j48 + 1)) {
				fRec3_tmp[j48] = fRec3_perm[j48];
				
			}
			for (int j50 = 0; (j50 < 4); j50 = (j50 + 1)) {
				fRec49_tmp[j50] = fRec49_perm[j50];
				
			}
			for (int j52 = 0; (j52 < 4); j52 = (j52 + 1)) {
				fRec48_tmp[j52] = fRec48_perm[j52];
				
			}
			fYec15_idx = ((fYec15_idx + fYec15_idx_save) & 511);
			for (int j54 = 0; (j54 < 4); j54 = (j54 + 1)) {
				fRec46_tmp[j54] = fRec46_perm[j54];
				
			}
			fYec16_idx = ((fYec16_idx + fYec16_idx_save) & 511);
			for (int j56 = 0; (j56 < 4); j56 = (j56 + 1)) {
				fRec44_tmp[j56] = fRec44_perm[j56];
				
			}
			fYec17_idx = ((fYec17_idx + fYec17_idx_save) & 1023);
			for (int j58 = 0; (j58 < 4); j58 = (j58 + 1)) {
				fRec42_tmp[j58] = fRec42_perm[j58];
				
			}
			fYec18_idx = ((fYec18_idx + fYec18_idx_save) & 1023);
			for (int j60 = 0; (j60 < 4); j60 = (j60 + 1)) {
				fRec40_tmp[j60] = fRec40_perm[j60];
				
			}
			fYec19_idx = ((fYec19_idx + fYec19_idx_save) & 131071);
			for (int j64 = 0; (j64 < 4); j64 = (j64 + 1)) {
				fRec4_tmp[j64] = fRec4_perm[j64];
				
			}
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec0[i] = fRec4[(i - 1)];
				fZec1[i] = fRec1[(i - 1)];
				fZec2[i] = fRec3[(i - 1)];
				fZec3[i] = (fZec1[i] + fZec2[i]);
				fZec4[i] = fRec2[(i - 1)];
				fZec5[i] = fRec14[(i - 2)];
				fZec9[i] = fRec14[(i - 1)];
				fRec14[i] = ((fRec15[i] * (fZec0[i] + (fZec3[i] + fZec4[i]))) - (((fZec5[i] * fZec8[i]) + (2.0f * (fZec9[i] * fZec10[i]))) / fZec11[i]));
				fZec12[i] = fRec13[(i - 2)];
				fZec14[i] = fRec13[(i - 1)];
				fRec13[i] = (((fZec5[i] + (fRec14[i] + (2.0f * fZec9[i]))) / fZec11[i]) - (((fZec12[i] * fZec13[i]) + (2.0f * (fZec10[i] * fZec14[i]))) / fZec15[i]));
				fZec17[i] = fRec11[(i - 1)];
				fYec0[((i + fYec0_idx) & 511)] = (((0.600000024f * fZec17[i]) + ((fZec12[i] + (fRec13[i] + (2.0f * fZec14[i]))) / fZec15[i])) + float(input0[i]));
				fRec11[i] = ((fYec0[(((i + fYec0_idx) - iZec22[i]) & 511)] * fZec24[i]) + (fZec25[i] * fYec0[(((i + fYec0_idx) - iZec26[i]) & 511)]));
				fRec12[i] = (0.0f - (0.600000024f * fYec0[((i + fYec0_idx) & 511)]));
				fZec27[i] = fRec9[(i - 1)];
				fYec1[((i + fYec1_idx) & 511)] = (fZec17[i] + (fRec12[i] + (0.600000024f * fZec27[i])));
				fRec9[i] = ((fYec1[(((i + fYec1_idx) - iZec31[i]) & 511)] * fZec33[i]) + (fZec34[i] * fYec1[(((i + fYec1_idx) - iZec35[i]) & 511)]));
				fRec10[i] = (0.0f - (0.600000024f * fYec1[((i + fYec1_idx) & 511)]));
				fZec36[i] = fRec7[(i - 1)];
				fYec2[((i + fYec2_idx) & 1023)] = (fZec27[i] + (fRec10[i] + (0.600000024f * fZec36[i])));
				fRec7[i] = ((fYec2[(((i + fYec2_idx) - iZec40[i]) & 1023)] * fZec42[i]) + (fZec43[i] * fYec2[(((i + fYec2_idx) - iZec44[i]) & 1023)]));
				fRec8[i] = (0.0f - (0.600000024f * fYec2[((i + fYec2_idx) & 1023)]));
				fZec45[i] = fRec5[(i - 1)];
				fYec3[((i + fYec3_idx) & 1023)] = (fZec36[i] + (fRec8[i] + (0.600000024f * fZec45[i])));
				fRec5[i] = ((fYec3[(((i + fYec3_idx) - iZec49[i]) & 1023)] * fZec51[i]) + (fZec52[i] * fYec3[(((i + fYec3_idx) - iZec53[i]) & 1023)]));
				fRec6[i] = (0.0f - (0.600000024f * fYec3[((i + fYec3_idx) & 1023)]));
				fYec4[((i + fYec4_idx) & 2047)] = (fRec6[i] + fZec45[i]);
				fRec1[i] = (0.5f * ((fYec4[(((i + fYec4_idx) - std::min<int>(8193, std::max<int>(0, iZec55[i]))) & 2047)] * (fZec56[i] + (1.0f - fZec54[i]))) + ((fZec54[i] - fZec56[i]) * fYec4[(((i + fYec4_idx) - std::min<int>(8193, std::max<int>(0, (iZec55[i] + 1)))) & 2047)])));
				fZec57[i] = fRec28[(i - 2)];
				fZec58[i] = fRec28[(i - 1)];
				fRec28[i] = ((fRec15[i] * (fZec3[i] - (fZec4[i] + fZec0[i]))) - (((fZec8[i] * fZec57[i]) + (2.0f * (fZec10[i] * fZec58[i]))) / fZec11[i]));
				fZec59[i] = fRec27[(i - 2)];
				fZec60[i] = fRec27[(i - 1)];
				fRec27[i] = (((fZec57[i] + (fRec28[i] + (2.0f * fZec58[i]))) / fZec11[i]) - (((fZec13[i] * fZec59[i]) + (2.0f * (fZec10[i] * fZec60[i]))) / fZec15[i]));
				fZec61[i] = fRec25[(i - 1)];
				fYec5[((i + fYec5_idx) & 511)] = (((0.600000024f * fZec61[i]) + ((fZec59[i] + (fRec27[i] + (2.0f * fZec60[i]))) / fZec15[i])) + float(input0[i]));
				fRec25[i] = ((fZec24[i] * fYec5[(((i + fYec5_idx) - iZec22[i]) & 511)]) + (fZec25[i] * fYec5[(((i + fYec5_idx) - iZec26[i]) & 511)]));
				fRec26[i] = (0.0f - (0.600000024f * fYec5[((i + fYec5_idx) & 511)]));
				fZec62[i] = fRec23[(i - 1)];
				fYec6[((i + fYec6_idx) & 511)] = (fZec61[i] + (fRec26[i] + (0.600000024f * fZec62[i])));
				fRec23[i] = ((fZec33[i] * fYec6[(((i + fYec6_idx) - iZec31[i]) & 511)]) + (fZec34[i] * fYec6[(((i + fYec6_idx) - iZec35[i]) & 511)]));
				fRec24[i] = (0.0f - (0.600000024f * fYec6[((i + fYec6_idx) & 511)]));
				fZec63[i] = fRec21[(i - 1)];
				fYec7[((i + fYec7_idx) & 1023)] = (fZec62[i] + (fRec24[i] + (0.600000024f * fZec63[i])));
				fRec21[i] = ((fZec42[i] * fYec7[(((i + fYec7_idx) - iZec40[i]) & 1023)]) + (fZec43[i] * fYec7[(((i + fYec7_idx) - iZec44[i]) & 1023)]));
				fRec22[i] = (0.0f - (0.600000024f * fYec7[((i + fYec7_idx) & 1023)]));
				fZec64[i] = fRec19[(i - 1)];
				fYec8[((i + fYec8_idx) & 1023)] = (fZec63[i] + (fRec22[i] + (0.600000024f * fZec64[i])));
				fRec19[i] = ((fZec51[i] * fYec8[(((i + fYec8_idx) - iZec49[i]) & 1023)]) + (fZec52[i] * fYec8[(((i + fYec8_idx) - iZec53[i]) & 1023)]));
				fRec20[i] = (0.0f - (0.600000024f * fYec8[((i + fYec8_idx) & 1023)]));
				fYec9[((i + fYec9_idx) & 2047)] = (fRec20[i] + fZec64[i]);
				fRec2[i] = (0.5f * ((fYec9[(((i + fYec9_idx) - std::min<int>(8193, std::max<int>(0, iZec66[i]))) & 2047)] * (fZec67[i] + (1.0f - fZec65[i]))) + ((fZec65[i] - fZec67[i]) * fYec9[(((i + fYec9_idx) - std::min<int>(8193, std::max<int>(0, (iZec66[i] + 1)))) & 2047)])));
				fZec68[i] = fRec39[(i - 2)];
				fZec69[i] = fRec39[(i - 1)];
				fRec39[i] = ((fRec15[i] * ((fZec1[i] + fZec4[i]) - (fZec2[i] + fZec0[i]))) - (((fZec8[i] * fZec68[i]) + (2.0f * (fZec10[i] * fZec69[i]))) / fZec11[i]));
				fZec70[i] = fRec38[(i - 2)];
				fZec71[i] = fRec38[(i - 1)];
				fRec38[i] = (((fZec68[i] + (fRec39[i] + (2.0f * fZec69[i]))) / fZec11[i]) - (((fZec13[i] * fZec70[i]) + (2.0f * (fZec10[i] * fZec71[i]))) / fZec15[i]));
				fZec72[i] = fRec36[(i - 1)];
				fYec10[((i + fYec10_idx) & 511)] = (((0.600000024f * fZec72[i]) + ((fZec70[i] + (fRec38[i] + (2.0f * fZec71[i]))) / fZec15[i])) + float(input0[i]));
				fRec36[i] = ((fZec24[i] * fYec10[(((i + fYec10_idx) - iZec22[i]) & 511)]) + (fZec25[i] * fYec10[(((i + fYec10_idx) - iZec26[i]) & 511)]));
				fRec37[i] = (0.0f - (0.600000024f * fYec10[((i + fYec10_idx) & 511)]));
				fZec73[i] = fRec34[(i - 1)];
				fYec11[((i + fYec11_idx) & 511)] = (fZec72[i] + (fRec37[i] + (0.600000024f * fZec73[i])));
				fRec34[i] = ((fZec33[i] * fYec11[(((i + fYec11_idx) - iZec31[i]) & 511)]) + (fZec34[i] * fYec11[(((i + fYec11_idx) - iZec35[i]) & 511)]));
				fRec35[i] = (0.0f - (0.600000024f * fYec11[((i + fYec11_idx) & 511)]));
				fZec74[i] = fRec32[(i - 1)];
				fYec12[((i + fYec12_idx) & 1023)] = (fZec73[i] + (fRec35[i] + (0.600000024f * fZec74[i])));
				fRec32[i] = ((fZec42[i] * fYec12[(((i + fYec12_idx) - iZec40[i]) & 1023)]) + (fZec43[i] * fYec12[(((i + fYec12_idx) - iZec44[i]) & 1023)]));
				fRec33[i] = (0.0f - (0.600000024f * fYec12[((i + fYec12_idx) & 1023)]));
				fZec75[i] = fRec30[(i - 1)];
				fYec13[((i + fYec13_idx) & 1023)] = (fZec74[i] + (fRec33[i] + (0.600000024f * fZec75[i])));
				fRec30[i] = ((fZec51[i] * fYec13[(((i + fYec13_idx) - iZec49[i]) & 1023)]) + (fZec52[i] * fYec13[(((i + fYec13_idx) - iZec53[i]) & 1023)]));
				fRec31[i] = (0.0f - (0.600000024f * fYec13[((i + fYec13_idx) & 1023)]));
				fYec14[((i + fYec14_idx) & 2047)] = (fRec31[i] + fZec75[i]);
				fZec79[i] = fRec29[(i - 2)];
				fZec80[i] = fRec29[(i - 1)];
				fRec29[i] = ((0.5f * ((fYec14[(((i + fYec14_idx) - std::min<int>(8193, std::max<int>(0, iZec77[i]))) & 2047)] * (fZec78[i] + (1.0f - fZec76[i]))) + ((fZec76[i] - fZec78[i]) * fYec14[(((i + fYec14_idx) - std::min<int>(8193, std::max<int>(0, (iZec77[i] + 1)))) & 2047)]))) - (fConst5 * ((fConst6 * fZec79[i]) + (fConst9 * fZec80[i]))));
				fRec3[i] = (fConst5 * (((fConst8 * fRec29[i]) + (fConst10 * fZec80[i])) + (fConst8 * fZec79[i])));
				fZec81[i] = fRec49[(i - 2)];
				fZec82[i] = fRec49[(i - 1)];
				fRec49[i] = ((fRec15[i] * ((fZec1[i] + fZec0[i]) - (fZec2[i] + fZec4[i]))) - (((fZec8[i] * fZec81[i]) + (2.0f * (fZec10[i] * fZec82[i]))) / fZec11[i]));
				fZec83[i] = fRec48[(i - 2)];
				fZec84[i] = fRec48[(i - 1)];
				fRec48[i] = (((fZec81[i] + (fRec49[i] + (2.0f * fZec82[i]))) / fZec11[i]) - (((fZec13[i] * fZec83[i]) + (2.0f * (fZec10[i] * fZec84[i]))) / fZec15[i]));
				fZec85[i] = fRec46[(i - 1)];
				fYec15[((i + fYec15_idx) & 511)] = (((0.600000024f * fZec85[i]) + ((fZec83[i] + (fRec48[i] + (2.0f * fZec84[i]))) / fZec15[i])) + float(input0[i]));
				fRec46[i] = ((fZec24[i] * fYec15[(((i + fYec15_idx) - iZec22[i]) & 511)]) + (fZec25[i] * fYec15[(((i + fYec15_idx) - iZec26[i]) & 511)]));
				fRec47[i] = (0.0f - (0.600000024f * fYec15[((i + fYec15_idx) & 511)]));
				fZec86[i] = fRec44[(i - 1)];
				fYec16[((i + fYec16_idx) & 511)] = (fZec85[i] + (fRec47[i] + (0.600000024f * fZec86[i])));
				fRec44[i] = ((fZec33[i] * fYec16[(((i + fYec16_idx) - iZec31[i]) & 511)]) + (fZec34[i] * fYec16[(((i + fYec16_idx) - iZec35[i]) & 511)]));
				fRec45[i] = (0.0f - (0.600000024f * fYec16[((i + fYec16_idx) & 511)]));
				fZec87[i] = fRec42[(i - 1)];
				fYec17[((i + fYec17_idx) & 1023)] = (fZec86[i] + (fRec45[i] + (0.600000024f * fZec87[i])));
				fRec42[i] = ((fZec42[i] * fYec17[(((i + fYec17_idx) - iZec40[i]) & 1023)]) + (fZec43[i] * fYec17[(((i + fYec17_idx) - iZec44[i]) & 1023)]));
				fRec43[i] = (0.0f - (0.600000024f * fYec17[((i + fYec17_idx) & 1023)]));
				fZec88[i] = fRec40[(i - 1)];
				fYec18[((i + fYec18_idx) & 1023)] = (fZec87[i] + (fRec43[i] + (0.600000024f * fZec88[i])));
				fRec40[i] = ((fZec51[i] * fYec18[(((i + fYec18_idx) - iZec49[i]) & 1023)]) + (fZec52[i] * fYec18[(((i + fYec18_idx) - iZec53[i]) & 1023)]));
				fRec41[i] = (0.0f - (0.600000024f * fYec18[((i + fYec18_idx) & 1023)]));
				fYec19[((i + fYec19_idx) & 131071)] = (fRec41[i] + fZec88[i]);
				fRec4[i] = (0.5f * ((fSlow3 * fYec19[(((i + fYec19_idx) - int(std::min<float>(8192.0f, std::max<float>(0.0f, fZec90[i])))) & 131071)]) + (fSlow2 * ((((fYec19[(((i + fYec19_idx) - std::min<int>(65537, std::max<int>(0, iZec91[i]))) & 131071)] * (fZec92[i] + (1.0f - fRec50[i]))) + ((fRec50[i] - fZec92[i]) * fYec19[(((i + fYec19_idx) - std::min<int>(65537, std::max<int>(0, (iZec91[i] + 1)))) & 131071)])) * fZec93[i]) + (((fYec19[(((i + fYec19_idx) - std::min<int>(65537, std::max<int>(0, iZec96[i]))) & 131071)] * (fZec97[i] + (-8191.0f - fZec94[i]))) + ((fZec94[i] + (8192.0f - fZec97[i])) * fYec19[(((i + fYec19_idx) - std::min<int>(65537, std::max<int>(0, (iZec96[i] + 1)))) & 131071)])) * (1.0f - fZec93[i]))))));
				
			}
			/* Post code */
			fYec19_idx_save = vsize;
			fYec18_idx_save = vsize;
			fYec17_idx_save = vsize;
			fYec16_idx_save = vsize;
			fYec15_idx_save = vsize;
			for (int j51 = 0; (j51 < 4); j51 = (j51 + 1)) {
				fRec49_perm[j51] = fRec49_tmp[(vsize + j51)];
				
			}
			for (int j53 = 0; (j53 < 4); j53 = (j53 + 1)) {
				fRec48_perm[j53] = fRec48_tmp[(vsize + j53)];
				
			}
			for (int j55 = 0; (j55 < 4); j55 = (j55 + 1)) {
				fRec46_perm[j55] = fRec46_tmp[(vsize + j55)];
				
			}
			for (int j57 = 0; (j57 < 4); j57 = (j57 + 1)) {
				fRec44_perm[j57] = fRec44_tmp[(vsize + j57)];
				
			}
			for (int j59 = 0; (j59 < 4); j59 = (j59 + 1)) {
				fRec42_perm[j59] = fRec42_tmp[(vsize + j59)];
				
			}
			for (int j61 = 0; (j61 < 4); j61 = (j61 + 1)) {
				fRec40_perm[j61] = fRec40_tmp[(vsize + j61)];
				
			}
			fYec14_idx_save = vsize;
			fYec13_idx_save = vsize;
			fYec12_idx_save = vsize;
			fYec11_idx_save = vsize;
			fYec10_idx_save = vsize;
			for (int j35 = 0; (j35 < 4); j35 = (j35 + 1)) {
				fRec39_perm[j35] = fRec39_tmp[(vsize + j35)];
				
			}
			for (int j37 = 0; (j37 < 4); j37 = (j37 + 1)) {
				fRec38_perm[j37] = fRec38_tmp[(vsize + j37)];
				
			}
			for (int j39 = 0; (j39 < 4); j39 = (j39 + 1)) {
				fRec36_perm[j39] = fRec36_tmp[(vsize + j39)];
				
			}
			for (int j41 = 0; (j41 < 4); j41 = (j41 + 1)) {
				fRec34_perm[j41] = fRec34_tmp[(vsize + j41)];
				
			}
			for (int j43 = 0; (j43 < 4); j43 = (j43 + 1)) {
				fRec32_perm[j43] = fRec32_tmp[(vsize + j43)];
				
			}
			for (int j45 = 0; (j45 < 4); j45 = (j45 + 1)) {
				fRec30_perm[j45] = fRec30_tmp[(vsize + j45)];
				
			}
			for (int j47 = 0; (j47 < 4); j47 = (j47 + 1)) {
				fRec29_perm[j47] = fRec29_tmp[(vsize + j47)];
				
			}
			fYec9_idx_save = vsize;
			fYec8_idx_save = vsize;
			fYec7_idx_save = vsize;
			fYec6_idx_save = vsize;
			fYec5_idx_save = vsize;
			for (int j21 = 0; (j21 < 4); j21 = (j21 + 1)) {
				fRec28_perm[j21] = fRec28_tmp[(vsize + j21)];
				
			}
			for (int j23 = 0; (j23 < 4); j23 = (j23 + 1)) {
				fRec27_perm[j23] = fRec27_tmp[(vsize + j23)];
				
			}
			for (int j25 = 0; (j25 < 4); j25 = (j25 + 1)) {
				fRec25_perm[j25] = fRec25_tmp[(vsize + j25)];
				
			}
			for (int j27 = 0; (j27 < 4); j27 = (j27 + 1)) {
				fRec23_perm[j27] = fRec23_tmp[(vsize + j27)];
				
			}
			for (int j29 = 0; (j29 < 4); j29 = (j29 + 1)) {
				fRec21_perm[j29] = fRec21_tmp[(vsize + j29)];
				
			}
			for (int j31 = 0; (j31 < 4); j31 = (j31 + 1)) {
				fRec19_perm[j31] = fRec19_tmp[(vsize + j31)];
				
			}
			fYec4_idx_save = vsize;
			fYec3_idx_save = vsize;
			fYec2_idx_save = vsize;
			fYec1_idx_save = vsize;
			fYec0_idx_save = vsize;
			for (int j5 = 0; (j5 < 4); j5 = (j5 + 1)) {
				fRec14_perm[j5] = fRec14_tmp[(vsize + j5)];
				
			}
			for (int j7 = 0; (j7 < 4); j7 = (j7 + 1)) {
				fRec13_perm[j7] = fRec13_tmp[(vsize + j7)];
				
			}
			for (int j11 = 0; (j11 < 4); j11 = (j11 + 1)) {
				fRec11_perm[j11] = fRec11_tmp[(vsize + j11)];
				
			}
			for (int j13 = 0; (j13 < 4); j13 = (j13 + 1)) {
				fRec9_perm[j13] = fRec9_tmp[(vsize + j13)];
				
			}
			for (int j15 = 0; (j15 < 4); j15 = (j15 + 1)) {
				fRec7_perm[j15] = fRec7_tmp[(vsize + j15)];
				
			}
			for (int j17 = 0; (j17 < 4); j17 = (j17 + 1)) {
				fRec5_perm[j17] = fRec5_tmp[(vsize + j17)];
				
			}
			for (int j19 = 0; (j19 < 4); j19 = (j19 + 1)) {
				fRec1_perm[j19] = fRec1_tmp[(vsize + j19)];
				
			}
			for (int j33 = 0; (j33 < 4); j33 = (j33 + 1)) {
				fRec2_perm[j33] = fRec2_tmp[(vsize + j33)];
				
			}
			for (int j49 = 0; (j49 < 4); j49 = (j49 + 1)) {
				fRec3_perm[j49] = fRec3_tmp[(vsize + j49)];
				
			}
			for (int j65 = 0; (j65 < 4); j65 = (j65 + 1)) {
				fRec4_perm[j65] = fRec4_tmp[(vsize + j65)];
				
			}
			/* Vectorizable loop 63 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec99[i] = (((fZec7[i] + -1.41421354f) / fZec6[i]) + 1.0f);
				
			}
			/* Vectorizable loop 64 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec101[i] = (((fZec7[i] + 1.41421354f) / fZec6[i]) + 1.0f);
				
			}
			/* Recursive loop 65 */
			/* Pre code */
			for (int j66 = 0; (j66 < 4); j66 = (j66 + 1)) {
				fRec0_tmp[j66] = fRec0_perm[j66];
				
			}
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec98[i] = fRec0[(i - 2)];
				fZec100[i] = fRec0[(i - 1)];
				fRec0[i] = ((fRec1[i] + fRec3[i]) - (((fZec98[i] * fZec99[i]) + (2.0f * (fZec10[i] * fZec100[i]))) / fZec101[i]));
				
			}
			/* Post code */
			for (int j67 = 0; (j67 < 4); j67 = (j67 + 1)) {
				fRec0_perm[j67] = fRec0_tmp[(vsize + j67)];
				
			}
			/* Recursive loop 66 */
			/* Pre code */
			for (int j68 = 0; (j68 < 4); j68 = (j68 + 1)) {
				fRec51_tmp[j68] = fRec51_perm[j68];
				
			}
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec102[i] = fRec51[(i - 2)];
				fZec103[i] = fRec51[(i - 1)];
				fRec51[i] = ((fRec2[i] + fRec4[i]) - (((fZec99[i] * fZec102[i]) + (2.0f * (fZec10[i] * fZec103[i]))) / fZec101[i]));
				
			}
			/* Post code */
			for (int j69 = 0; (j69 < 4); j69 = (j69 + 1)) {
				fRec51_perm[j69] = fRec51_tmp[(vsize + j69)];
				
			}
			/* Vectorizable loop 67 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec104[i] = ((fSlow4 * (((fZec98[i] + (fRec0[i] + (2.0f * fZec100[i]))) + (fZec102[i] + (fRec51[i] + (2.0f * fZec103[i])))) / fZec101[i])) + (fSlow5 * float(input0[i])));
				
			}
			/* Vectorizable loop 68 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				output0[i] = FAUSTFLOAT(fZec104[i]);
				
			}
			/* Vectorizable loop 69 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				output1[i] = FAUSTFLOAT(fZec104[i]);
				
			}
			
		}
		/* Remaining frames */
		if (vindex < fullcount) {
			FAUSTFLOAT* input0 = &input0_ptr[vindex];
			FAUSTFLOAT* output0 = &output0_ptr[vindex];
			FAUSTFLOAT* output1 = &output1_ptr[vindex];
			int vsize = (fullcount - vindex);
			/* Recursive loop 0 */
			/* Pre code */
			for (int j8 = 0; (j8 < 4); j8 = (j8 + 1)) {
				fRec17_tmp[j8] = fRec17_perm[j8];
				
			}
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec16[i] = fRec17[(i - 1)];
				fRec17[i] = (fConst2 + (fZec16[i] - std::floor((fConst2 + fZec16[i]))));
				
			}
			/* Post code */
			for (int j9 = 0; (j9 < 4); j9 = (j9 + 1)) {
				fRec17_perm[j9] = fRec17_tmp[(vsize + j9)];
				
			}
			/* Vectorizable loop 1 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec18[i] = ((0.00100000005f * ftbl0faust_wormholeSIG0[int((65536.0f * fRec17[i]))]) + 1.0f);
				
			}
			/* Vectorizable loop 2 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec89[i] = (1617.0f * fZec18[i]);
				
			}
			/* Vectorizable loop 3 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec90[i] = (fZec89[i] + 8192.0f);
				
			}
			/* Recursive loop 4 */
			/* Pre code */
			for (int j2 = 0; (j2 < 4); j2 = (j2 + 1)) {
				fRec16_tmp[j2] = fRec16_perm[j2];
				
			}
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fRec16[i] = (fSlow1 + (0.999000013f * fRec16[(i - 1)]));
				
			}
			/* Post code */
			for (int j3 = 0; (j3 < 4); j3 = (j3 + 1)) {
				fRec16_perm[j3] = fRec16_tmp[(vsize + j3)];
				
			}
			/* Vectorizable loop 5 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec19[i] = (343.0f * fZec18[i]);
				
			}
			/* Vectorizable loop 6 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec28[i] = (441.0f * fZec18[i]);
				
			}
			/* Vectorizable loop 7 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec37[i] = (625.0f * fZec18[i]);
				
			}
			/* Vectorizable loop 8 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec46[i] = (727.0f * fZec18[i]);
				
			}
			/* Recursive loop 9 */
			/* Pre code */
			for (int j62 = 0; (j62 < 4); j62 = (j62 + 1)) {
				fRec50_tmp[j62] = fRec50_perm[j62];
				
			}
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fRec50[i] = std::fmod(((fZec89[i] + fRec50[(i - 1)]) + 8191.0f), fZec90[i]);
				
			}
			/* Post code */
			for (int j63 = 0; (j63 < 4); j63 = (j63 + 1)) {
				fRec50_perm[j63] = fRec50_tmp[(vsize + j63)];
				
			}
			/* Vectorizable loop 10 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec6[i] = std::tan((fConst1 * fRec16[i]));
				
			}
			/* Vectorizable loop 11 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec20[i] = (fZec19[i] + -1.0f);
				
			}
			/* Vectorizable loop 12 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec29[i] = (fZec28[i] + -1.0f);
				
			}
			/* Vectorizable loop 13 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec38[i] = (fZec37[i] + -1.0f);
				
			}
			/* Vectorizable loop 14 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec47[i] = (fZec46[i] + -1.0f);
				
			}
			/* Vectorizable loop 15 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec94[i] = (fRec50[i] + fZec89[i]);
				
			}
			/* Vectorizable loop 16 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec7[i] = (1.0f / fZec6[i]);
				
			}
			/* Vectorizable loop 17 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec23[i] = std::floor(fZec20[i]);
				
			}
			/* Vectorizable loop 18 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				iZec21[i] = int(fZec20[i]);
				
			}
			/* Vectorizable loop 19 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				iZec30[i] = int(fZec29[i]);
				
			}
			/* Vectorizable loop 20 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec32[i] = std::floor(fZec29[i]);
				
			}
			/* Vectorizable loop 21 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				iZec39[i] = int(fZec38[i]);
				
			}
			/* Vectorizable loop 22 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec41[i] = std::floor(fZec38[i]);
				
			}
			/* Vectorizable loop 23 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				iZec48[i] = int(fZec47[i]);
				
			}
			/* Vectorizable loop 24 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec50[i] = std::floor(fZec47[i]);
				
			}
			/* Vectorizable loop 25 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec54[i] = (1356.0f * fZec18[i]);
				
			}
			/* Vectorizable loop 26 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec65[i] = (1422.0f * fZec18[i]);
				
			}
			/* Vectorizable loop 27 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec76[i] = (1557.0f * fZec18[i]);
				
			}
			/* Vectorizable loop 28 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec95[i] = (fZec94[i] + 8192.0f);
				
			}
			/* Recursive loop 29 */
			/* Pre code */
			for (int j0 = 0; (j0 < 4); j0 = (j0 + 1)) {
				fRec15_tmp[j0] = fRec15_perm[j0];
				
			}
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fRec15[i] = (fSlow0 + (0.999000013f * fRec15[(i - 1)]));
				
			}
			/* Post code */
			for (int j1 = 0; (j1 < 4); j1 = (j1 + 1)) {
				fRec15_perm[j1] = fRec15_tmp[(vsize + j1)];
				
			}
			/* Vectorizable loop 30 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec10[i] = (1.0f - (1.0f / faust_wormhole_faustpower2_f(fZec6[i])));
				
			}
			/* Vectorizable loop 31 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec11[i] = (((fZec7[i] + 1.84775901f) / fZec6[i]) + 1.0f);
				
			}
			/* Vectorizable loop 32 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec8[i] = (((fZec7[i] + -1.84775901f) / fZec6[i]) + 1.0f);
				
			}
			/* Vectorizable loop 33 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec24[i] = (fZec23[i] + (2.0f - fZec19[i]));
				
			}
			/* Vectorizable loop 34 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec13[i] = (((fZec7[i] + -0.765366852f) / fZec6[i]) + 1.0f);
				
			}
			/* Vectorizable loop 35 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec15[i] = (((fZec7[i] + 0.765366852f) / fZec6[i]) + 1.0f);
				
			}
			/* Vectorizable loop 36 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				iZec22[i] = std::min<int>(2049, std::max<int>(0, iZec21[i]));
				
			}
			/* Vectorizable loop 37 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec25[i] = (fZec19[i] + (-1.0f - fZec23[i]));
				
			}
			/* Vectorizable loop 38 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				iZec26[i] = std::min<int>(2049, std::max<int>(0, (iZec21[i] + 1)));
				
			}
			/* Vectorizable loop 39 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				iZec31[i] = std::min<int>(2049, std::max<int>(0, iZec30[i]));
				
			}
			/* Vectorizable loop 40 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec33[i] = (fZec32[i] + (2.0f - fZec28[i]));
				
			}
			/* Vectorizable loop 41 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec34[i] = (fZec28[i] + (-1.0f - fZec32[i]));
				
			}
			/* Vectorizable loop 42 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				iZec35[i] = std::min<int>(2049, std::max<int>(0, (iZec30[i] + 1)));
				
			}
			/* Vectorizable loop 43 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				iZec40[i] = std::min<int>(2049, std::max<int>(0, iZec39[i]));
				
			}
			/* Vectorizable loop 44 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec42[i] = (fZec41[i] + (2.0f - fZec37[i]));
				
			}
			/* Vectorizable loop 45 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec43[i] = (fZec37[i] + (-1.0f - fZec41[i]));
				
			}
			/* Vectorizable loop 46 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				iZec44[i] = std::min<int>(2049, std::max<int>(0, (iZec39[i] + 1)));
				
			}
			/* Vectorizable loop 47 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				iZec49[i] = std::min<int>(2049, std::max<int>(0, iZec48[i]));
				
			}
			/* Vectorizable loop 48 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec51[i] = (fZec50[i] + (2.0f - fZec46[i]));
				
			}
			/* Vectorizable loop 49 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec52[i] = (fZec46[i] + (-1.0f - fZec50[i]));
				
			}
			/* Vectorizable loop 50 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				iZec53[i] = std::min<int>(2049, std::max<int>(0, (iZec48[i] + 1)));
				
			}
			/* Vectorizable loop 51 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				iZec55[i] = int(fZec54[i]);
				
			}
			/* Vectorizable loop 52 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec56[i] = std::floor(fZec54[i]);
				
			}
			/* Vectorizable loop 53 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				iZec66[i] = int(fZec65[i]);
				
			}
			/* Vectorizable loop 54 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec67[i] = std::floor(fZec65[i]);
				
			}
			/* Vectorizable loop 55 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				iZec77[i] = int(fZec76[i]);
				
			}
			/* Vectorizable loop 56 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec78[i] = std::floor(fZec76[i]);
				
			}
			/* Vectorizable loop 57 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				iZec91[i] = int(fRec50[i]);
				
			}
			/* Vectorizable loop 58 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec92[i] = std::floor(fRec50[i]);
				
			}
			/* Vectorizable loop 59 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec93[i] = std::min<float>((fRec50[i] / fZec90[i]), 1.0f);
				
			}
			/* Vectorizable loop 60 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				iZec96[i] = int(fZec95[i]);
				
			}
			/* Vectorizable loop 61 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec97[i] = std::floor(fZec95[i]);
				
			}
			/* Recursive loop 62 */
			/* Pre code */
			for (int j4 = 0; (j4 < 4); j4 = (j4 + 1)) {
				fRec14_tmp[j4] = fRec14_perm[j4];
				
			}
			for (int j6 = 0; (j6 < 4); j6 = (j6 + 1)) {
				fRec13_tmp[j6] = fRec13_perm[j6];
				
			}
			fYec0_idx = ((fYec0_idx + fYec0_idx_save) & 511);
			for (int j10 = 0; (j10 < 4); j10 = (j10 + 1)) {
				fRec11_tmp[j10] = fRec11_perm[j10];
				
			}
			fYec1_idx = ((fYec1_idx + fYec1_idx_save) & 511);
			for (int j12 = 0; (j12 < 4); j12 = (j12 + 1)) {
				fRec9_tmp[j12] = fRec9_perm[j12];
				
			}
			fYec2_idx = ((fYec2_idx + fYec2_idx_save) & 1023);
			for (int j14 = 0; (j14 < 4); j14 = (j14 + 1)) {
				fRec7_tmp[j14] = fRec7_perm[j14];
				
			}
			fYec3_idx = ((fYec3_idx + fYec3_idx_save) & 1023);
			for (int j16 = 0; (j16 < 4); j16 = (j16 + 1)) {
				fRec5_tmp[j16] = fRec5_perm[j16];
				
			}
			fYec4_idx = ((fYec4_idx + fYec4_idx_save) & 2047);
			for (int j18 = 0; (j18 < 4); j18 = (j18 + 1)) {
				fRec1_tmp[j18] = fRec1_perm[j18];
				
			}
			for (int j20 = 0; (j20 < 4); j20 = (j20 + 1)) {
				fRec28_tmp[j20] = fRec28_perm[j20];
				
			}
			for (int j22 = 0; (j22 < 4); j22 = (j22 + 1)) {
				fRec27_tmp[j22] = fRec27_perm[j22];
				
			}
			fYec5_idx = ((fYec5_idx + fYec5_idx_save) & 511);
			for (int j24 = 0; (j24 < 4); j24 = (j24 + 1)) {
				fRec25_tmp[j24] = fRec25_perm[j24];
				
			}
			fYec6_idx = ((fYec6_idx + fYec6_idx_save) & 511);
			for (int j26 = 0; (j26 < 4); j26 = (j26 + 1)) {
				fRec23_tmp[j26] = fRec23_perm[j26];
				
			}
			fYec7_idx = ((fYec7_idx + fYec7_idx_save) & 1023);
			for (int j28 = 0; (j28 < 4); j28 = (j28 + 1)) {
				fRec21_tmp[j28] = fRec21_perm[j28];
				
			}
			fYec8_idx = ((fYec8_idx + fYec8_idx_save) & 1023);
			for (int j30 = 0; (j30 < 4); j30 = (j30 + 1)) {
				fRec19_tmp[j30] = fRec19_perm[j30];
				
			}
			fYec9_idx = ((fYec9_idx + fYec9_idx_save) & 2047);
			for (int j32 = 0; (j32 < 4); j32 = (j32 + 1)) {
				fRec2_tmp[j32] = fRec2_perm[j32];
				
			}
			for (int j34 = 0; (j34 < 4); j34 = (j34 + 1)) {
				fRec39_tmp[j34] = fRec39_perm[j34];
				
			}
			for (int j36 = 0; (j36 < 4); j36 = (j36 + 1)) {
				fRec38_tmp[j36] = fRec38_perm[j36];
				
			}
			fYec10_idx = ((fYec10_idx + fYec10_idx_save) & 511);
			for (int j38 = 0; (j38 < 4); j38 = (j38 + 1)) {
				fRec36_tmp[j38] = fRec36_perm[j38];
				
			}
			fYec11_idx = ((fYec11_idx + fYec11_idx_save) & 511);
			for (int j40 = 0; (j40 < 4); j40 = (j40 + 1)) {
				fRec34_tmp[j40] = fRec34_perm[j40];
				
			}
			fYec12_idx = ((fYec12_idx + fYec12_idx_save) & 1023);
			for (int j42 = 0; (j42 < 4); j42 = (j42 + 1)) {
				fRec32_tmp[j42] = fRec32_perm[j42];
				
			}
			fYec13_idx = ((fYec13_idx + fYec13_idx_save) & 1023);
			for (int j44 = 0; (j44 < 4); j44 = (j44 + 1)) {
				fRec30_tmp[j44] = fRec30_perm[j44];
				
			}
			fYec14_idx = ((fYec14_idx + fYec14_idx_save) & 2047);
			for (int j46 = 0; (j46 < 4); j46 = (j46 + 1)) {
				fRec29_tmp[j46] = fRec29_perm[j46];
				
			}
			for (int j48 = 0; (j48 < 4); j48 = (j48 + 1)) {
				fRec3_tmp[j48] = fRec3_perm[j48];
				
			}
			for (int j50 = 0; (j50 < 4); j50 = (j50 + 1)) {
				fRec49_tmp[j50] = fRec49_perm[j50];
				
			}
			for (int j52 = 0; (j52 < 4); j52 = (j52 + 1)) {
				fRec48_tmp[j52] = fRec48_perm[j52];
				
			}
			fYec15_idx = ((fYec15_idx + fYec15_idx_save) & 511);
			for (int j54 = 0; (j54 < 4); j54 = (j54 + 1)) {
				fRec46_tmp[j54] = fRec46_perm[j54];
				
			}
			fYec16_idx = ((fYec16_idx + fYec16_idx_save) & 511);
			for (int j56 = 0; (j56 < 4); j56 = (j56 + 1)) {
				fRec44_tmp[j56] = fRec44_perm[j56];
				
			}
			fYec17_idx = ((fYec17_idx + fYec17_idx_save) & 1023);
			for (int j58 = 0; (j58 < 4); j58 = (j58 + 1)) {
				fRec42_tmp[j58] = fRec42_perm[j58];
				
			}
			fYec18_idx = ((fYec18_idx + fYec18_idx_save) & 1023);
			for (int j60 = 0; (j60 < 4); j60 = (j60 + 1)) {
				fRec40_tmp[j60] = fRec40_perm[j60];
				
			}
			fYec19_idx = ((fYec19_idx + fYec19_idx_save) & 131071);
			for (int j64 = 0; (j64 < 4); j64 = (j64 + 1)) {
				fRec4_tmp[j64] = fRec4_perm[j64];
				
			}
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec0[i] = fRec4[(i - 1)];
				fZec1[i] = fRec1[(i - 1)];
				fZec2[i] = fRec3[(i - 1)];
				fZec3[i] = (fZec1[i] + fZec2[i]);
				fZec4[i] = fRec2[(i - 1)];
				fZec5[i] = fRec14[(i - 2)];
				fZec9[i] = fRec14[(i - 1)];
				fRec14[i] = ((fRec15[i] * (fZec0[i] + (fZec3[i] + fZec4[i]))) - (((fZec5[i] * fZec8[i]) + (2.0f * (fZec9[i] * fZec10[i]))) / fZec11[i]));
				fZec12[i] = fRec13[(i - 2)];
				fZec14[i] = fRec13[(i - 1)];
				fRec13[i] = (((fZec5[i] + (fRec14[i] + (2.0f * fZec9[i]))) / fZec11[i]) - (((fZec12[i] * fZec13[i]) + (2.0f * (fZec10[i] * fZec14[i]))) / fZec15[i]));
				fZec17[i] = fRec11[(i - 1)];
				fYec0[((i + fYec0_idx) & 511)] = (((0.600000024f * fZec17[i]) + ((fZec12[i] + (fRec13[i] + (2.0f * fZec14[i]))) / fZec15[i])) + float(input0[i]));
				fRec11[i] = ((fYec0[(((i + fYec0_idx) - iZec22[i]) & 511)] * fZec24[i]) + (fZec25[i] * fYec0[(((i + fYec0_idx) - iZec26[i]) & 511)]));
				fRec12[i] = (0.0f - (0.600000024f * fYec0[((i + fYec0_idx) & 511)]));
				fZec27[i] = fRec9[(i - 1)];
				fYec1[((i + fYec1_idx) & 511)] = (fZec17[i] + (fRec12[i] + (0.600000024f * fZec27[i])));
				fRec9[i] = ((fYec1[(((i + fYec1_idx) - iZec31[i]) & 511)] * fZec33[i]) + (fZec34[i] * fYec1[(((i + fYec1_idx) - iZec35[i]) & 511)]));
				fRec10[i] = (0.0f - (0.600000024f * fYec1[((i + fYec1_idx) & 511)]));
				fZec36[i] = fRec7[(i - 1)];
				fYec2[((i + fYec2_idx) & 1023)] = (fZec27[i] + (fRec10[i] + (0.600000024f * fZec36[i])));
				fRec7[i] = ((fYec2[(((i + fYec2_idx) - iZec40[i]) & 1023)] * fZec42[i]) + (fZec43[i] * fYec2[(((i + fYec2_idx) - iZec44[i]) & 1023)]));
				fRec8[i] = (0.0f - (0.600000024f * fYec2[((i + fYec2_idx) & 1023)]));
				fZec45[i] = fRec5[(i - 1)];
				fYec3[((i + fYec3_idx) & 1023)] = (fZec36[i] + (fRec8[i] + (0.600000024f * fZec45[i])));
				fRec5[i] = ((fYec3[(((i + fYec3_idx) - iZec49[i]) & 1023)] * fZec51[i]) + (fZec52[i] * fYec3[(((i + fYec3_idx) - iZec53[i]) & 1023)]));
				fRec6[i] = (0.0f - (0.600000024f * fYec3[((i + fYec3_idx) & 1023)]));
				fYec4[((i + fYec4_idx) & 2047)] = (fRec6[i] + fZec45[i]);
				fRec1[i] = (0.5f * ((fYec4[(((i + fYec4_idx) - std::min<int>(8193, std::max<int>(0, iZec55[i]))) & 2047)] * (fZec56[i] + (1.0f - fZec54[i]))) + ((fZec54[i] - fZec56[i]) * fYec4[(((i + fYec4_idx) - std::min<int>(8193, std::max<int>(0, (iZec55[i] + 1)))) & 2047)])));
				fZec57[i] = fRec28[(i - 2)];
				fZec58[i] = fRec28[(i - 1)];
				fRec28[i] = ((fRec15[i] * (fZec3[i] - (fZec4[i] + fZec0[i]))) - (((fZec8[i] * fZec57[i]) + (2.0f * (fZec10[i] * fZec58[i]))) / fZec11[i]));
				fZec59[i] = fRec27[(i - 2)];
				fZec60[i] = fRec27[(i - 1)];
				fRec27[i] = (((fZec57[i] + (fRec28[i] + (2.0f * fZec58[i]))) / fZec11[i]) - (((fZec13[i] * fZec59[i]) + (2.0f * (fZec10[i] * fZec60[i]))) / fZec15[i]));
				fZec61[i] = fRec25[(i - 1)];
				fYec5[((i + fYec5_idx) & 511)] = (((0.600000024f * fZec61[i]) + ((fZec59[i] + (fRec27[i] + (2.0f * fZec60[i]))) / fZec15[i])) + float(input0[i]));
				fRec25[i] = ((fZec24[i] * fYec5[(((i + fYec5_idx) - iZec22[i]) & 511)]) + (fZec25[i] * fYec5[(((i + fYec5_idx) - iZec26[i]) & 511)]));
				fRec26[i] = (0.0f - (0.600000024f * fYec5[((i + fYec5_idx) & 511)]));
				fZec62[i] = fRec23[(i - 1)];
				fYec6[((i + fYec6_idx) & 511)] = (fZec61[i] + (fRec26[i] + (0.600000024f * fZec62[i])));
				fRec23[i] = ((fZec33[i] * fYec6[(((i + fYec6_idx) - iZec31[i]) & 511)]) + (fZec34[i] * fYec6[(((i + fYec6_idx) - iZec35[i]) & 511)]));
				fRec24[i] = (0.0f - (0.600000024f * fYec6[((i + fYec6_idx) & 511)]));
				fZec63[i] = fRec21[(i - 1)];
				fYec7[((i + fYec7_idx) & 1023)] = (fZec62[i] + (fRec24[i] + (0.600000024f * fZec63[i])));
				fRec21[i] = ((fZec42[i] * fYec7[(((i + fYec7_idx) - iZec40[i]) & 1023)]) + (fZec43[i] * fYec7[(((i + fYec7_idx) - iZec44[i]) & 1023)]));
				fRec22[i] = (0.0f - (0.600000024f * fYec7[((i + fYec7_idx) & 1023)]));
				fZec64[i] = fRec19[(i - 1)];
				fYec8[((i + fYec8_idx) & 1023)] = (fZec63[i] + (fRec22[i] + (0.600000024f * fZec64[i])));
				fRec19[i] = ((fZec51[i] * fYec8[(((i + fYec8_idx) - iZec49[i]) & 1023)]) + (fZec52[i] * fYec8[(((i + fYec8_idx) - iZec53[i]) & 1023)]));
				fRec20[i] = (0.0f - (0.600000024f * fYec8[((i + fYec8_idx) & 1023)]));
				fYec9[((i + fYec9_idx) & 2047)] = (fRec20[i] + fZec64[i]);
				fRec2[i] = (0.5f * ((fYec9[(((i + fYec9_idx) - std::min<int>(8193, std::max<int>(0, iZec66[i]))) & 2047)] * (fZec67[i] + (1.0f - fZec65[i]))) + ((fZec65[i] - fZec67[i]) * fYec9[(((i + fYec9_idx) - std::min<int>(8193, std::max<int>(0, (iZec66[i] + 1)))) & 2047)])));
				fZec68[i] = fRec39[(i - 2)];
				fZec69[i] = fRec39[(i - 1)];
				fRec39[i] = ((fRec15[i] * ((fZec1[i] + fZec4[i]) - (fZec2[i] + fZec0[i]))) - (((fZec8[i] * fZec68[i]) + (2.0f * (fZec10[i] * fZec69[i]))) / fZec11[i]));
				fZec70[i] = fRec38[(i - 2)];
				fZec71[i] = fRec38[(i - 1)];
				fRec38[i] = (((fZec68[i] + (fRec39[i] + (2.0f * fZec69[i]))) / fZec11[i]) - (((fZec13[i] * fZec70[i]) + (2.0f * (fZec10[i] * fZec71[i]))) / fZec15[i]));
				fZec72[i] = fRec36[(i - 1)];
				fYec10[((i + fYec10_idx) & 511)] = (((0.600000024f * fZec72[i]) + ((fZec70[i] + (fRec38[i] + (2.0f * fZec71[i]))) / fZec15[i])) + float(input0[i]));
				fRec36[i] = ((fZec24[i] * fYec10[(((i + fYec10_idx) - iZec22[i]) & 511)]) + (fZec25[i] * fYec10[(((i + fYec10_idx) - iZec26[i]) & 511)]));
				fRec37[i] = (0.0f - (0.600000024f * fYec10[((i + fYec10_idx) & 511)]));
				fZec73[i] = fRec34[(i - 1)];
				fYec11[((i + fYec11_idx) & 511)] = (fZec72[i] + (fRec37[i] + (0.600000024f * fZec73[i])));
				fRec34[i] = ((fZec33[i] * fYec11[(((i + fYec11_idx) - iZec31[i]) & 511)]) + (fZec34[i] * fYec11[(((i + fYec11_idx) - iZec35[i]) & 511)]));
				fRec35[i] = (0.0f - (0.600000024f * fYec11[((i + fYec11_idx) & 511)]));
				fZec74[i] = fRec32[(i - 1)];
				fYec12[((i + fYec12_idx) & 1023)] = (fZec73[i] + (fRec35[i] + (0.600000024f * fZec74[i])));
				fRec32[i] = ((fZec42[i] * fYec12[(((i + fYec12_idx) - iZec40[i]) & 1023)]) + (fZec43[i] * fYec12[(((i + fYec12_idx) - iZec44[i]) & 1023)]));
				fRec33[i] = (0.0f - (0.600000024f * fYec12[((i + fYec12_idx) & 1023)]));
				fZec75[i] = fRec30[(i - 1)];
				fYec13[((i + fYec13_idx) & 1023)] = (fZec74[i] + (fRec33[i] + (0.600000024f * fZec75[i])));
				fRec30[i] = ((fZec51[i] * fYec13[(((i + fYec13_idx) - iZec49[i]) & 1023)]) + (fZec52[i] * fYec13[(((i + fYec13_idx) - iZec53[i]) & 1023)]));
				fRec31[i] = (0.0f - (0.600000024f * fYec13[((i + fYec13_idx) & 1023)]));
				fYec14[((i + fYec14_idx) & 2047)] = (fRec31[i] + fZec75[i]);
				fZec79[i] = fRec29[(i - 2)];
				fZec80[i] = fRec29[(i - 1)];
				fRec29[i] = ((0.5f * ((fYec14[(((i + fYec14_idx) - std::min<int>(8193, std::max<int>(0, iZec77[i]))) & 2047)] * (fZec78[i] + (1.0f - fZec76[i]))) + ((fZec76[i] - fZec78[i]) * fYec14[(((i + fYec14_idx) - std::min<int>(8193, std::max<int>(0, (iZec77[i] + 1)))) & 2047)]))) - (fConst5 * ((fConst6 * fZec79[i]) + (fConst9 * fZec80[i]))));
				fRec3[i] = (fConst5 * (((fConst8 * fRec29[i]) + (fConst10 * fZec80[i])) + (fConst8 * fZec79[i])));
				fZec81[i] = fRec49[(i - 2)];
				fZec82[i] = fRec49[(i - 1)];
				fRec49[i] = ((fRec15[i] * ((fZec1[i] + fZec0[i]) - (fZec2[i] + fZec4[i]))) - (((fZec8[i] * fZec81[i]) + (2.0f * (fZec10[i] * fZec82[i]))) / fZec11[i]));
				fZec83[i] = fRec48[(i - 2)];
				fZec84[i] = fRec48[(i - 1)];
				fRec48[i] = (((fZec81[i] + (fRec49[i] + (2.0f * fZec82[i]))) / fZec11[i]) - (((fZec13[i] * fZec83[i]) + (2.0f * (fZec10[i] * fZec84[i]))) / fZec15[i]));
				fZec85[i] = fRec46[(i - 1)];
				fYec15[((i + fYec15_idx) & 511)] = (((0.600000024f * fZec85[i]) + ((fZec83[i] + (fRec48[i] + (2.0f * fZec84[i]))) / fZec15[i])) + float(input0[i]));
				fRec46[i] = ((fZec24[i] * fYec15[(((i + fYec15_idx) - iZec22[i]) & 511)]) + (fZec25[i] * fYec15[(((i + fYec15_idx) - iZec26[i]) & 511)]));
				fRec47[i] = (0.0f - (0.600000024f * fYec15[((i + fYec15_idx) & 511)]));
				fZec86[i] = fRec44[(i - 1)];
				fYec16[((i + fYec16_idx) & 511)] = (fZec85[i] + (fRec47[i] + (0.600000024f * fZec86[i])));
				fRec44[i] = ((fZec33[i] * fYec16[(((i + fYec16_idx) - iZec31[i]) & 511)]) + (fZec34[i] * fYec16[(((i + fYec16_idx) - iZec35[i]) & 511)]));
				fRec45[i] = (0.0f - (0.600000024f * fYec16[((i + fYec16_idx) & 511)]));
				fZec87[i] = fRec42[(i - 1)];
				fYec17[((i + fYec17_idx) & 1023)] = (fZec86[i] + (fRec45[i] + (0.600000024f * fZec87[i])));
				fRec42[i] = ((fZec42[i] * fYec17[(((i + fYec17_idx) - iZec40[i]) & 1023)]) + (fZec43[i] * fYec17[(((i + fYec17_idx) - iZec44[i]) & 1023)]));
				fRec43[i] = (0.0f - (0.600000024f * fYec17[((i + fYec17_idx) & 1023)]));
				fZec88[i] = fRec40[(i - 1)];
				fYec18[((i + fYec18_idx) & 1023)] = (fZec87[i] + (fRec43[i] + (0.600000024f * fZec88[i])));
				fRec40[i] = ((fZec51[i] * fYec18[(((i + fYec18_idx) - iZec49[i]) & 1023)]) + (fZec52[i] * fYec18[(((i + fYec18_idx) - iZec53[i]) & 1023)]));
				fRec41[i] = (0.0f - (0.600000024f * fYec18[((i + fYec18_idx) & 1023)]));
				fYec19[((i + fYec19_idx) & 131071)] = (fRec41[i] + fZec88[i]);
				fRec4[i] = (0.5f * ((fSlow3 * fYec19[(((i + fYec19_idx) - int(std::min<float>(8192.0f, std::max<float>(0.0f, fZec90[i])))) & 131071)]) + (fSlow2 * ((((fYec19[(((i + fYec19_idx) - std::min<int>(65537, std::max<int>(0, iZec91[i]))) & 131071)] * (fZec92[i] + (1.0f - fRec50[i]))) + ((fRec50[i] - fZec92[i]) * fYec19[(((i + fYec19_idx) - std::min<int>(65537, std::max<int>(0, (iZec91[i] + 1)))) & 131071)])) * fZec93[i]) + (((fYec19[(((i + fYec19_idx) - std::min<int>(65537, std::max<int>(0, iZec96[i]))) & 131071)] * (fZec97[i] + (-8191.0f - fZec94[i]))) + ((fZec94[i] + (8192.0f - fZec97[i])) * fYec19[(((i + fYec19_idx) - std::min<int>(65537, std::max<int>(0, (iZec96[i] + 1)))) & 131071)])) * (1.0f - fZec93[i]))))));
				
			}
			/* Post code */
			fYec19_idx_save = vsize;
			fYec18_idx_save = vsize;
			fYec17_idx_save = vsize;
			fYec16_idx_save = vsize;
			fYec15_idx_save = vsize;
			for (int j51 = 0; (j51 < 4); j51 = (j51 + 1)) {
				fRec49_perm[j51] = fRec49_tmp[(vsize + j51)];
				
			}
			for (int j53 = 0; (j53 < 4); j53 = (j53 + 1)) {
				fRec48_perm[j53] = fRec48_tmp[(vsize + j53)];
				
			}
			for (int j55 = 0; (j55 < 4); j55 = (j55 + 1)) {
				fRec46_perm[j55] = fRec46_tmp[(vsize + j55)];
				
			}
			for (int j57 = 0; (j57 < 4); j57 = (j57 + 1)) {
				fRec44_perm[j57] = fRec44_tmp[(vsize + j57)];
				
			}
			for (int j59 = 0; (j59 < 4); j59 = (j59 + 1)) {
				fRec42_perm[j59] = fRec42_tmp[(vsize + j59)];
				
			}
			for (int j61 = 0; (j61 < 4); j61 = (j61 + 1)) {
				fRec40_perm[j61] = fRec40_tmp[(vsize + j61)];
				
			}
			fYec14_idx_save = vsize;
			fYec13_idx_save = vsize;
			fYec12_idx_save = vsize;
			fYec11_idx_save = vsize;
			fYec10_idx_save = vsize;
			for (int j35 = 0; (j35 < 4); j35 = (j35 + 1)) {
				fRec39_perm[j35] = fRec39_tmp[(vsize + j35)];
				
			}
			for (int j37 = 0; (j37 < 4); j37 = (j37 + 1)) {
				fRec38_perm[j37] = fRec38_tmp[(vsize + j37)];
				
			}
			for (int j39 = 0; (j39 < 4); j39 = (j39 + 1)) {
				fRec36_perm[j39] = fRec36_tmp[(vsize + j39)];
				
			}
			for (int j41 = 0; (j41 < 4); j41 = (j41 + 1)) {
				fRec34_perm[j41] = fRec34_tmp[(vsize + j41)];
				
			}
			for (int j43 = 0; (j43 < 4); j43 = (j43 + 1)) {
				fRec32_perm[j43] = fRec32_tmp[(vsize + j43)];
				
			}
			for (int j45 = 0; (j45 < 4); j45 = (j45 + 1)) {
				fRec30_perm[j45] = fRec30_tmp[(vsize + j45)];
				
			}
			for (int j47 = 0; (j47 < 4); j47 = (j47 + 1)) {
				fRec29_perm[j47] = fRec29_tmp[(vsize + j47)];
				
			}
			fYec9_idx_save = vsize;
			fYec8_idx_save = vsize;
			fYec7_idx_save = vsize;
			fYec6_idx_save = vsize;
			fYec5_idx_save = vsize;
			for (int j21 = 0; (j21 < 4); j21 = (j21 + 1)) {
				fRec28_perm[j21] = fRec28_tmp[(vsize + j21)];
				
			}
			for (int j23 = 0; (j23 < 4); j23 = (j23 + 1)) {
				fRec27_perm[j23] = fRec27_tmp[(vsize + j23)];
				
			}
			for (int j25 = 0; (j25 < 4); j25 = (j25 + 1)) {
				fRec25_perm[j25] = fRec25_tmp[(vsize + j25)];
				
			}
			for (int j27 = 0; (j27 < 4); j27 = (j27 + 1)) {
				fRec23_perm[j27] = fRec23_tmp[(vsize + j27)];
				
			}
			for (int j29 = 0; (j29 < 4); j29 = (j29 + 1)) {
				fRec21_perm[j29] = fRec21_tmp[(vsize + j29)];
				
			}
			for (int j31 = 0; (j31 < 4); j31 = (j31 + 1)) {
				fRec19_perm[j31] = fRec19_tmp[(vsize + j31)];
				
			}
			fYec4_idx_save = vsize;
			fYec3_idx_save = vsize;
			fYec2_idx_save = vsize;
			fYec1_idx_save = vsize;
			fYec0_idx_save = vsize;
			for (int j5 = 0; (j5 < 4); j5 = (j5 + 1)) {
				fRec14_perm[j5] = fRec14_tmp[(vsize + j5)];
				
			}
			for (int j7 = 0; (j7 < 4); j7 = (j7 + 1)) {
				fRec13_perm[j7] = fRec13_tmp[(vsize + j7)];
				
			}
			for (int j11 = 0; (j11 < 4); j11 = (j11 + 1)) {
				fRec11_perm[j11] = fRec11_tmp[(vsize + j11)];
				
			}
			for (int j13 = 0; (j13 < 4); j13 = (j13 + 1)) {
				fRec9_perm[j13] = fRec9_tmp[(vsize + j13)];
				
			}
			for (int j15 = 0; (j15 < 4); j15 = (j15 + 1)) {
				fRec7_perm[j15] = fRec7_tmp[(vsize + j15)];
				
			}
			for (int j17 = 0; (j17 < 4); j17 = (j17 + 1)) {
				fRec5_perm[j17] = fRec5_tmp[(vsize + j17)];
				
			}
			for (int j19 = 0; (j19 < 4); j19 = (j19 + 1)) {
				fRec1_perm[j19] = fRec1_tmp[(vsize + j19)];
				
			}
			for (int j33 = 0; (j33 < 4); j33 = (j33 + 1)) {
				fRec2_perm[j33] = fRec2_tmp[(vsize + j33)];
				
			}
			for (int j49 = 0; (j49 < 4); j49 = (j49 + 1)) {
				fRec3_perm[j49] = fRec3_tmp[(vsize + j49)];
				
			}
			for (int j65 = 0; (j65 < 4); j65 = (j65 + 1)) {
				fRec4_perm[j65] = fRec4_tmp[(vsize + j65)];
				
			}
			/* Vectorizable loop 63 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec99[i] = (((fZec7[i] + -1.41421354f) / fZec6[i]) + 1.0f);
				
			}
			/* Vectorizable loop 64 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec101[i] = (((fZec7[i] + 1.41421354f) / fZec6[i]) + 1.0f);
				
			}
			/* Recursive loop 65 */
			/* Pre code */
			for (int j66 = 0; (j66 < 4); j66 = (j66 + 1)) {
				fRec0_tmp[j66] = fRec0_perm[j66];
				
			}
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec98[i] = fRec0[(i - 2)];
				fZec100[i] = fRec0[(i - 1)];
				fRec0[i] = ((fRec1[i] + fRec3[i]) - (((fZec98[i] * fZec99[i]) + (2.0f * (fZec10[i] * fZec100[i]))) / fZec101[i]));
				
			}
			/* Post code */
			for (int j67 = 0; (j67 < 4); j67 = (j67 + 1)) {
				fRec0_perm[j67] = fRec0_tmp[(vsize + j67)];
				
			}
			/* Recursive loop 66 */
			/* Pre code */
			for (int j68 = 0; (j68 < 4); j68 = (j68 + 1)) {
				fRec51_tmp[j68] = fRec51_perm[j68];
				
			}
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec102[i] = fRec51[(i - 2)];
				fZec103[i] = fRec51[(i - 1)];
				fRec51[i] = ((fRec2[i] + fRec4[i]) - (((fZec99[i] * fZec102[i]) + (2.0f * (fZec10[i] * fZec103[i]))) / fZec101[i]));
				
			}
			/* Post code */
			for (int j69 = 0; (j69 < 4); j69 = (j69 + 1)) {
				fRec51_perm[j69] = fRec51_tmp[(vsize + j69)];
				
			}
			/* Vectorizable loop 67 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec104[i] = ((fSlow4 * (((fZec98[i] + (fRec0[i] + (2.0f * fZec100[i]))) + (fZec102[i] + (fRec51[i] + (2.0f * fZec103[i])))) / fZec101[i])) + (fSlow5 * float(input0[i])));
				
			}
			/* Vectorizable loop 68 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				output0[i] = FAUSTFLOAT(fZec104[i]);
				
			}
			/* Vectorizable loop 69 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				output1[i] = FAUSTFLOAT(fZec104[i]);
				
			}
			
		}
		
	}

	
};

#endif
