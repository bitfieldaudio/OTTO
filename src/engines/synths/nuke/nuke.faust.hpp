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
		ui_interface->openHorizontalBox("envelope");
		ui_interface->addHorizontalSlider("Attack", &fHslider2, 0.00100000005f, 0.00100000005f, 4.0f, 0.00100000005f);
		ui_interface->addHorizontalSlider("Decay", &fHslider3, 0.0f, 0.0f, 4.0f, 0.00999999978f);
		ui_interface->addHorizontalSlider("Release", &fHslider1, 0.0f, 0.0f, 4.0f, 0.00999999978f);
		ui_interface->addHorizontalSlider("Sustain", &fHslider4, 1.0f, 0.0f, 1.0f, 0.100000001f);
		ui_interface->closeBox();
		ui_interface->openHorizontalBox("midi");
		ui_interface->declare(&fHslider6, "unit", "Hz");
		ui_interface->addHorizontalSlider("freq", &fHslider6, 440.0f, 20.0f, 1000.0f, 1.0f);
		ui_interface->addHorizontalSlider("gain", &fHslider0, 0.5f, 0.0f, 10.0f, 0.00999999978f);
		ui_interface->addButton("gate", &fButton0);
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
		float fSlow6 = (float(fHslider4) * float(iSlow1));
		float fSlow7 = (0.00100000005f * float(fHslider5));
		float fSlow8 = float(fHslider6);
		float fSlow9 = max((0.5f * fSlow8), 23.4489498f);
		float fSlow10 = max(20.0f, fabsf(fSlow9));
		float fSlow11 = (fConst2 / fSlow10);
		float fSlow12 = (fConst0 / fSlow9);
		float fSlow13 = (fConst4 * fSlow8);
		float fSlow14 = max(0.0f, min(2047.0f, (fConst5 / fSlow9)));
		float fSlow15 = floorf(fSlow14);
		float fSlow16 = (fSlow15 + (1.0f - fSlow14));
		int iSlow17 = int(fSlow14);
		float fSlow18 = (fSlow14 - fSlow15);
		int iSlow19 = (iSlow17 + 1);
		float fSlow20 = (fConst0 / fSlow8);
		int iSlow21 = int((fConst6 / fSlow8));
		float fSlow22 = (fConst7 * fSlow8);
		float fSlow23 = (0.00100000005f * float(fHslider7));
		fHbargraph0 = FAUSTFLOAT((2.0f * float(fHslider8)));
		float fSlow24 = (0.000500000024f * fHbargraph0);
		float fSlow25 = (fConst8 * fSlow8);
		float fSlow26 = max(fSlow8, 23.4489498f);
		float fSlow27 = max(20.0f, fabsf(fSlow26));
		float fSlow28 = (fConst2 / fSlow27);
		float fSlow29 = (fConst0 / fSlow26);
		float fSlow30 = max(0.0f, min(2047.0f, (fConst5 / fSlow26)));
		float fSlow31 = floorf(fSlow30);
		float fSlow32 = (fSlow31 + (1.0f - fSlow30));
		int iSlow33 = int(fSlow30);
		float fSlow34 = (fSlow30 - fSlow31);
		int iSlow35 = (iSlow33 + 1);
		int iSlow36 = int(fSlow20);
		float fSlow37 = (0.00100000005f * float(fHslider9));
		for (int i = 0; (i < count); i = (i + 1)) {
			iVec0[0] = 1;
			iRec1[0] = (iSlow1 * (iRec1[1] + 1));
			int iTemp0 = (iRec1[0] < iSlow4);
			float fTemp1 = expf((0.0f - (fConst1 / (iSlow1?(iTemp0?fSlow3:fSlow5):fSlow2))));
			fRec0[0] = ((fRec0[1] * fTemp1) + ((iSlow1?(iTemp0?float(iSlow1):fSlow6):0.0f) * (1.0f - fTemp1)));
			fRec4[0] = (fSlow7 + (0.999000013f * fRec4[1]));
			float fTemp2 = min(1.0f, max(0.0f, (2.0f - fRec4[0])));
			fVec1[0] = 0.25f;
			fVec2[0] = fSlow10;
			float fTemp3 = (fRec5[1] + (fConst3 * fVec2[1]));
			fRec5[0] = (fTemp3 - floorf(fTemp3));
			float fTemp4 = faust_nuke_faustpower2_f(((2.0f * fRec5[0]) + -1.0f));
			fVec3[0] = fTemp4;
			float fTemp5 = (fSlow11 * ((fTemp4 - fVec3[1]) * float(iVec0[1])));
			fVec4[(IOTA & 4095)] = fTemp5;
			float fTemp6 = min(0.5f, (0.5f * fRec4[0]));
			float fTemp7 = max(0.0f, min(2047.0f, (fSlow12 * fTemp6)));
			int iTemp8 = int(fTemp7);
			float fTemp9 = floorf(fTemp7);
			fRec6[0] = ((fTemp5 + (0.999000013f * fRec6[1])) - ((fSlow16 * fVec4[((IOTA - iSlow17) & 4095)]) + (fSlow18 * fVec4[((IOTA - iSlow19) & 4095)])));
			float fTemp10 = min(1.0f, max(0.0f, (fRec4[0] + -2.0f)));
			float fTemp11 = (1.0f - (fTemp2 + fTemp10));
			float fTemp12 = (fTemp10 * fVec1[1]);
			iRec8[0] = ((iRec8[1] + iVec0[1]) % iSlow21);
			float fTemp13 = (0.100000001f * (max(3.0f, fRec4[0]) + -3.0f));
			float fTemp14 = (fTemp13 + 0.5f);
			float fTemp15 = ((fRec7[1] * float((1 - ((iRec8[0] == 0) > 0)))) + (fSlow22 * fTemp14));
			fRec7[0] = (fTemp15 - floorf(fTemp15));
			float fTemp16 = faust_nuke_faustpower2_f(((2.0f * fRec7[0]) + -1.0f));
			fVec5[0] = fTemp16;
			fRec9[0] = (fSlow23 + (0.999000013f * fRec9[1]));
			int iTemp17 = (1 - (fRec9[0] <= 0.00999999978f));
			fRec10[0] = (fSlow24 + (0.999000013f * fRec10[1]));
			int iTemp18 = (fRec10[0] >= 3.0f);
			float fTemp19 = (((fRec10[0] == 0.0f) + iTemp18)?1.0f:max(max(1.0f, ((0.0593999997f * (fRec10[0] + -2.0999999f)) + 1.0f)), ((0.0593999997f * (1.0f - fRec10[0])) + 1.0f)));
			float fTemp20 = max((fSlow8 * fTemp19), 23.4489498f);
			float fTemp21 = max(20.0f, fabsf(fTemp20));
			fVec6[0] = fTemp21;
			float fTemp22 = (fRec11[1] + (fConst3 * fVec6[1]));
			fRec11[0] = (fTemp22 - floorf(fTemp22));
			float fTemp23 = faust_nuke_faustpower2_f(((2.0f * fRec11[0]) + -1.0f));
			fVec7[0] = fTemp23;
			float fTemp24 = (((fTemp23 - fVec7[1]) * float(iVec0[1])) / fTemp21);
			fVec8[(IOTA & 4095)] = fTemp24;
			float fTemp25 = max(0.0f, min(2047.0f, (fConst0 * (fTemp6 / fTemp20))));
			int iTemp26 = int(fTemp25);
			float fTemp27 = floorf(fTemp25);
			float fTemp28 = max(0.0f, min(2047.0f, (fConst5 / fTemp20)));
			int iTemp29 = int(fTemp28);
			float fTemp30 = floorf(fTemp28);
			fRec12[0] = ((0.999000013f * fRec12[1]) + (fConst2 * ((fTemp24 - (fVec8[((IOTA - iTemp29) & 4095)] * (fTemp30 + (1.0f - fTemp28)))) - ((fTemp28 - fTemp30) * fVec8[((IOTA - (iTemp29 + 1)) & 4095)]))));
			iRec14[0] = ((iRec14[1] + iVec0[1]) % int((fSlow20 / fTemp19)));
			float fTemp31 = (fTemp19 + fTemp13);
			float fTemp32 = ((fRec13[1] * float((1 - ((iRec14[0] == 0) > 0)))) + (fSlow22 * fTemp31));
			fRec13[0] = (fTemp32 - floorf(fTemp32));
			float fTemp33 = faust_nuke_faustpower2_f(((2.0f * fRec13[0]) + -1.0f));
			fVec9[0] = fTemp33;
			float fTemp34 = (((fConst2 * (fTemp2 * ((fTemp24 - (fVec8[((IOTA - iTemp26) & 4095)] * (fTemp27 + (1.0f - fTemp25)))) - ((fTemp25 - fTemp27) * fVec8[((IOTA - (iTemp26 + 1)) & 4095)])))) + (fSlow25 * ((fRec12[0] * fTemp19) * fTemp11))) + (fSlow20 * (((fTemp10 * (fTemp33 - fVec9[1])) * fVec1[1]) / fTemp31)));
			float fTemp35 = (iTemp18?1.49829996f:1.0f);
			float fTemp36 = (fTemp35 / fTemp19);
			float fTemp37 = max((fSlow8 * fTemp36), 23.4489498f);
			float fTemp38 = max(20.0f, fabsf(fTemp37));
			fVec10[0] = fTemp38;
			float fTemp39 = (fRec15[1] + (fConst3 * fVec10[1]));
			fRec15[0] = (fTemp39 - floorf(fTemp39));
			float fTemp40 = faust_nuke_faustpower2_f(((2.0f * fRec15[0]) + -1.0f));
			fVec11[0] = fTemp40;
			float fTemp41 = (((fTemp40 - fVec11[1]) * float(iVec0[1])) / fTemp38);
			fVec12[(IOTA & 4095)] = fTemp41;
			float fTemp42 = max(0.0f, min(2047.0f, (fConst0 * (fTemp6 / fTemp37))));
			int iTemp43 = int(fTemp42);
			float fTemp44 = floorf(fTemp42);
			float fTemp45 = max(0.0f, min(2047.0f, (fConst5 / fTemp37)));
			int iTemp46 = int(fTemp45);
			float fTemp47 = floorf(fTemp45);
			fRec16[0] = ((0.999000013f * fRec16[1]) + (fConst2 * ((fTemp41 - (fVec12[((IOTA - iTemp46) & 4095)] * (fTemp47 + (1.0f - fTemp45)))) - ((fTemp45 - fTemp47) * fVec12[((IOTA - (iTemp46 + 1)) & 4095)]))));
			iRec18[0] = ((iRec18[1] + iVec0[1]) % int((fSlow20 * (fTemp19 / fTemp35))));
			float fTemp48 = (fTemp13 + fTemp36);
			float fTemp49 = ((fRec17[1] * float((1 - ((iRec18[0] == 0) > 0)))) + (fSlow22 * fTemp48));
			fRec17[0] = (fTemp49 - floorf(fTemp49));
			float fTemp50 = faust_nuke_faustpower2_f(((2.0f * fRec17[0]) + -1.0f));
			fVec13[0] = fTemp50;
			float fTemp51 = (((fConst2 * (fTemp2 * ((fTemp41 - (fVec12[((IOTA - iTemp43) & 4095)] * (fTemp44 + (1.0f - fTemp42)))) - ((fTemp42 - fTemp44) * fVec12[((IOTA - (iTemp43 + 1)) & 4095)])))) + (fSlow25 * (((fTemp35 * fRec16[0]) * fTemp11) / fTemp19))) + (fSlow20 * ((fTemp12 * (fTemp50 - fVec13[1])) / fTemp48)));
			float fTemp52 = min(1.0f, max(0.0f, (2.0f - fRec10[0])));
			fVec14[0] = fSlow27;
			float fTemp53 = (fRec19[1] + (fConst3 * fVec14[1]));
			fRec19[0] = (fTemp53 - floorf(fTemp53));
			float fTemp54 = faust_nuke_faustpower2_f(((2.0f * fRec19[0]) + -1.0f));
			fVec15[0] = fTemp54;
			float fTemp55 = (fSlow28 * ((fTemp54 - fVec15[1]) * float(iVec0[1])));
			fVec16[(IOTA & 4095)] = fTemp55;
			float fTemp56 = max(0.0f, min(2047.0f, (fSlow29 * fTemp6)));
			int iTemp57 = int(fTemp56);
			float fTemp58 = floorf(fTemp56);
			fRec20[0] = ((fTemp55 + (0.999000013f * fRec20[1])) - ((fSlow32 * fVec16[((IOTA - iSlow33) & 4095)]) + (fSlow34 * fVec16[((IOTA - iSlow35) & 4095)])));
			iRec22[0] = ((iRec22[1] + iVec0[1]) % iSlow36);
			float fTemp59 = (fTemp13 + 1.0f);
			float fTemp60 = ((fRec21[1] * float((1 - ((iRec22[0] == 0) > 0)))) + (fSlow22 * fTemp59));
			fRec21[0] = (fTemp60 - floorf(fTemp60));
			float fTemp61 = faust_nuke_faustpower2_f(((2.0f * fRec21[0]) + -1.0f));
			fVec17[0] = fTemp61;
			iRec23[0] = ((1103515245 * iRec23[1]) + 12345);
			fRec24[0] = (fSlow37 + (0.999000013f * fRec24[1]));
			int iTemp62 = int(floorf((0.0404040404f * (fRec24[0] + -1.0f))));
			float fTemp63 = (0.0399999991f * fRec24[0]);
			fHbargraph1 = FAUSTFLOAT((4.5f * ((iTemp62 >= 2)?((iTemp62 >= 3)?(4.0f - fTemp63):(0.0399999991f * (fRec24[0] + -50.0f))):((iTemp62 >= 1)?(2.0f - fTemp63):fTemp63))));
			float fTemp64 = tanf((fConst9 * ((2222.0f * fHbargraph1) + 300.0f)));
			float fTemp65 = (1.0f / fTemp64);
			fRec25[0] = ((0.999000013f * fRec25[1]) + (0.00100000005f * ((0.075000003f * (max(40.0f, min(60.0f, fRec24[0])) + -40.0f)) + 1.0f)));
			float fTemp66 = (1.0f / fRec25[0]);
			float fTemp67 = (((fTemp65 - fTemp66) / fTemp64) + 1.0f);
			float fTemp68 = (1.0f - (1.0f / faust_nuke_faustpower2_f(fTemp64)));
			float fTemp69 = (((fTemp65 + fTemp66) / fTemp64) + 1.0f);
			fRec3[0] = (((((((fTemp2 * (fTemp5 - ((fVec4[((IOTA - iTemp8) & 4095)] * (fTemp9 + (1.0f - fTemp7))) + ((fTemp7 - fTemp9) * fVec4[((IOTA - (iTemp8 + 1)) & 4095)])))) + (fSlow13 * (fRec6[0] * fTemp11))) + (fSlow20 * ((fTemp12 * (fTemp16 - fVec5[1])) / fTemp14))) * max(0.0f, (fRec9[0] + -2.0f))) + ((float(iTemp17) * ((float((fRec10[0] >= 2.0f)) * (fTemp34 + fTemp51)) + ((float((fRec10[0] < 2.0f)) * fTemp34) * ((1.0f - fTemp52) + ((float(iTemp17) * fTemp52) * fTemp51))))) + (max(0.0f, ((fRec9[0] <= 1.0f)?fRec9[0]:(2.0f - fRec9[0]))) * (((fTemp2 * (fTemp55 - ((fVec16[((IOTA - iTemp57) & 4095)] * (fTemp58 + (1.0f - fTemp56))) + ((fTemp56 - fTemp58) * fVec16[((IOTA - (iTemp57 + 1)) & 4095)])))) + (fSlow25 * (fRec20[0] * fTemp11))) + (fSlow20 * ((fTemp12 * (fTemp61 - fVec17[1])) / fTemp59)))))) + (4.65661287e-10f * (float(iRec23[0]) * max((1.0f - fRec9[0]), 0.0f)))) - (((fRec3[2] * fTemp67) + (2.0f * (fRec3[1] * fTemp68))) / fTemp69));
			fRec2[0] = ((((fRec3[1] + (0.5f * fRec3[0])) + (0.5f * fRec3[2])) - ((fTemp67 * fRec2[2]) + (2.0f * (fTemp68 * fRec2[1])))) / fTemp69);
			output0[i] = FAUSTFLOAT((fSlow0 * ((fRec0[0] * ((fRec2[1] + (0.5f * fRec2[0])) + (0.5f * fRec2[2]))) / fTemp69)));
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
			
		}
		
	}

	
};

#endif
