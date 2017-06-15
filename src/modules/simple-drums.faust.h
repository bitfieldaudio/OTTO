/* ------------------------------------------------------------
name: "simple-drums"
Code generated with Faust 2.0.a73 (http://faust.grame.fr)
------------------------------------------------------------ */

#ifndef  __faust_simple_drums_H__
#define  __faust_simple_drums_H__

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

#include <math.h>

float faust_simple_drums_faustpower2_f(float value) {
	return (value * value);
	
}

#ifndef FAUSTCLASS 
#define FAUSTCLASS faust_simple_drums
#endif

class faust_simple_drums : public dsp {
	
 private:
	
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT fButton0;
	float fVec0[2];
	int iVec1[2];
	int fSamplingFreq;
	float fConst0;
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT fVslider2;
	float fRec0[2];
	float fConst1;
	FAUSTFLOAT fCheckbox0;
	float fConst2;
	FAUSTFLOAT fHslider0;
	FAUSTFLOAT fHslider1;
	FAUSTFLOAT fHslider2;
	float fRec2[2];
	float fConst3;
	float fConst4;
	FAUSTFLOAT fHbargraph0;
	float fRec1[2];
	float fVec2[2];
	int IOTA;
	float fVec3[4096];
	float fConst5;
	int iRec3[2];
	FAUSTFLOAT fCheckbox1;
	float fConst6;
	FAUSTFLOAT fHslider3;
	FAUSTFLOAT fHslider4;
	FAUSTFLOAT fHslider5;
	FAUSTFLOAT fHslider6;
	float fRec6[2];
	FAUSTFLOAT fHbargraph1;
	float fRec5[2];
	float fVec4[2];
	float fVec5[4096];
	float fRec4[3];
	FAUSTFLOAT fHslider7;
	float fRec7[3];
	
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
		m->declare("maths.lib/version", "2.0");
		m->declare("name", "simple-drums");
		m->declare("noises.lib/name", "Faust Noise Generator Library");
		m->declare("noises.lib/version", "0.0");
		m->declare("oscillators.lib/name", "Faust Oscillator Library");
		m->declare("oscillators.lib/version", "0.0");
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
		fConst0 = min(192000.0f, max(1000.0f, float(fSamplingFreq)));
		fConst1 = (1.0f / fConst0);
		fConst2 = (0.25f * fConst0);
		fConst3 = (9.99999975e-05f * fConst0);
		fConst4 = (10000.0f / fConst0);
		fConst5 = (0.5f * fConst0);
		fConst6 = (3.14159274f / fConst0);
		
	}
	
	virtual void instanceResetUserInterface() {
		fVslider0 = FAUSTFLOAT(1.0f);
		fButton0 = FAUSTFLOAT(0.0f);
		fVslider1 = FAUSTFLOAT(0.0f);
		fVslider2 = FAUSTFLOAT(0.20000000000000001f);
		fCheckbox0 = FAUSTFLOAT(0.0f);
		fHslider0 = FAUSTFLOAT(0.20000000000000001f);
		fHslider1 = FAUSTFLOAT(500.0f);
		fHslider2 = FAUSTFLOAT(0.5f);
		fCheckbox1 = FAUSTFLOAT(0.0f);
		fHslider3 = FAUSTFLOAT(1000.0f);
		fHslider4 = FAUSTFLOAT(0.20000000000000001f);
		fHslider5 = FAUSTFLOAT(500.0f);
		fHslider6 = FAUSTFLOAT(0.5f);
		fHslider7 = FAUSTFLOAT(1000.0f);
		
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			fVec0[l0] = 0.0f;
			
		}
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			iVec1[l1] = 0;
			
		}
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			fRec0[l2] = 0.0f;
			
		}
		for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			fRec2[l3] = 0.0f;
			
		}
		for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			fRec1[l4] = 0.0f;
			
		}
		for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			fVec2[l5] = 0.0f;
			
		}
		IOTA = 0;
		for (int l6 = 0; (l6 < 4096); l6 = (l6 + 1)) {
			fVec3[l6] = 0.0f;
			
		}
		for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			iRec3[l7] = 0;
			
		}
		for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			fRec6[l8] = 0.0f;
			
		}
		for (int l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			fRec5[l9] = 0.0f;
			
		}
		for (int l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
			fVec4[l10] = 0.0f;
			
		}
		for (int l11 = 0; (l11 < 4096); l11 = (l11 + 1)) {
			fVec5[l11] = 0.0f;
			
		}
		for (int l12 = 0; (l12 < 3); l12 = (l12 + 1)) {
			fRec4[l12] = 0.0f;
			
		}
		for (int l13 = 0; (l13 < 3); l13 = (l13 + 1)) {
			fRec7[l13] = 0.0f;
			
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
	
	virtual faust_simple_drums* clone() {
		return new faust_simple_drums();
	}
	
	virtual int getSampleRate() {
		return fSamplingFreq;
	}
	
	virtual void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("simple-drums");
		ui_interface->openVerticalBox("D1");
		ui_interface->addHorizontalSlider("CUTOFF", &fHslider3, 1000.0f, 5.0f, 10000.0f, 0.00100000005f);
		ui_interface->addHorizontalBargraph("DECAY_GRAPH", &fHbargraph1, -1.0f, 1.0f);
		ui_interface->addCheckButton("FILTER_SWITCH", &fCheckbox1);
		ui_interface->addHorizontalSlider("FREQ", &fHslider5, 500.0f, 10.0f, 500.0f, 2.9000001f);
		ui_interface->addHorizontalSlider("NOISE", &fHslider4, 0.200000003f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface->addHorizontalSlider("TONE_DECAY", &fHslider6, 0.5f, -1.0f, 1.0f, 0.00999999978f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("D2");
		ui_interface->addHorizontalSlider("CUTOFF", &fHslider7, 1000.0f, 5.0f, 10000.0f, 0.00100000005f);
		ui_interface->addHorizontalBargraph("DECAY_GRAPH", &fHbargraph0, -1.0f, 1.0f);
		ui_interface->addCheckButton("FILTER_SWITCH", &fCheckbox0);
		ui_interface->addHorizontalSlider("FREQ", &fHslider1, 500.0f, 10.0f, 500.0f, 2.9000001f);
		ui_interface->addHorizontalSlider("NOISE", &fHslider0, 0.200000003f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface->addHorizontalSlider("TONE_DECAY", &fHslider2, 0.5f, -1.0f, 1.0f, 0.00999999978f);
		ui_interface->closeBox();
		ui_interface->openHorizontalBox("ENVELOPE");
		ui_interface->addVerticalSlider("ATTACK", &fVslider1, 0.0f, 0.0f, 2.0f, 0.0199999996f);
		ui_interface->addVerticalSlider("RELEASE", &fVslider2, 0.200000003f, 0.0f, 2.0f, 0.0199999996f);
		ui_interface->addVerticalSlider("SUSTAIN", &fVslider0, 1.0f, 0.0f, 2.0f, 0.0199999996f);
		ui_interface->closeBox();
		ui_interface->addButton("TRIGGER", &fButton0);
		ui_interface->closeBox();
		
	}
	
	virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
		FAUSTFLOAT* output0 = outputs[0];
		float fSlow0 = float(fVslider0);
		float fSlow1 = float(fButton0);
		float fSlow2 = (float(fVslider1) + 0.00100000005f);
		float fSlow3 = float(fVslider2);
		float fSlow4 = (fSlow2 + (fSlow3 + 0.00100000005f));
		float fSlow5 = (fConst0 * fSlow4);
		float fSlow6 = (fConst0 * fSlow2);
		float fSlow7 = (1.0f / (0.0f - (fConst0 * (fSlow2 - fSlow4))));
		float fSlow8 = (fConst1 * (fSlow1 / fSlow2));
		float fSlow9 = float(fCheckbox0);
		float fSlow10 = (1.0f - fSlow9);
		float fSlow11 = float(fHslider0);
		float fSlow12 = (fConst2 * (1.0f - fSlow11));
		float fSlow13 = float(fHslider1);
		float fSlow14 = float(fHslider2);
		float fSlow15 = ((fSlow3 * fabsf(fSlow14)) + 9.99999975e-05f);
		float fSlow16 = (fConst0 * fSlow15);
		float fSlow17 = (fConst1 / (fSlow15 + -9.99999975e-05f));
		float fSlow18 = (fConst4 * fSlow1);
		float fSlow19 = (4.65661287e-10f * fSlow11);
		float fSlow20 = float(fCheckbox1);
		float fSlow21 = tanf((fConst6 * float(fHslider3)));
		float fSlow22 = (1.0f / fSlow21);
		float fSlow23 = (((fSlow22 + 0.333333343f) / fSlow21) + 1.0f);
		float fSlow24 = (fSlow20 / fSlow23);
		float fSlow25 = float(fHslider4);
		float fSlow26 = (fConst2 * (1.0f - fSlow25));
		float fSlow27 = float(fHslider5);
		float fSlow28 = float(fHslider6);
		float fSlow29 = ((fSlow3 * fabsf(fSlow28)) + 9.99999975e-05f);
		float fSlow30 = (fConst0 * fSlow29);
		float fSlow31 = (fConst1 / (fSlow29 + -9.99999975e-05f));
		float fSlow32 = (4.65661287e-10f * fSlow25);
		float fSlow33 = (1.0f / fSlow23);
		float fSlow34 = (((fSlow22 + -0.333333343f) / fSlow21) + 1.0f);
		float fSlow35 = (2.0f * (1.0f - (1.0f / faust_simple_drums_faustpower2_f(fSlow21))));
		float fSlow36 = (1.0f - fSlow20);
		float fSlow37 = tanf((fConst6 * float(fHslider7)));
		float fSlow38 = (1.0f / fSlow37);
		float fSlow39 = (((fSlow38 + 0.333333343f) / fSlow37) + 1.0f);
		float fSlow40 = (fSlow9 / fSlow39);
		float fSlow41 = (1.0f / fSlow39);
		float fSlow42 = (((fSlow38 + -0.333333343f) / fSlow37) + 1.0f);
		float fSlow43 = (2.0f * (1.0f - (1.0f / faust_simple_drums_faustpower2_f(fSlow37))));
		for (int i = 0; (i < count); i = (i + 1)) {
			fVec0[0] = fSlow1;
			iVec1[0] = 1;
			int iTemp0 = (((fSlow1 - fVec0[1]) == 1.0f) > 0);
			fRec0[0] = (iTemp0?0.0f:min(fSlow5, (fRec0[1] + 1.0f)));
			float fTemp1 = (fSlow1 * fRec0[0]);
			int iTemp2 = (fTemp1 < fSlow6);
			fRec2[0] = (iTemp0?0.0f:min(fSlow16, (fRec2[1] + 1.0f)));
			float fTemp3 = (fSlow1 * fRec2[0]);
			int iTemp4 = (fTemp3 < fConst3);
			fHbargraph0 = FAUSTFLOAT((fSlow14 * (iTemp4?((fTemp3 < 0.0f)?0.0f:(iTemp4?(fSlow18 * fRec2[0]):1.0f)):((fTemp3 < fSlow16)?((fSlow17 * (0.0f - (fTemp3 - fConst3))) + 1.0f):0.0f))));
			float fTemp5 = max((fSlow13 * (fHbargraph0 + 1.0f)), 23.4489498f);
			float fTemp6 = max(20.0f, fabsf(fTemp5));
			float fTemp7 = (fRec1[1] + (fConst1 * fTemp6));
			fRec1[0] = (fTemp7 - floorf(fTemp7));
			float fTemp8 = faust_simple_drums_faustpower2_f(((2.0f * fRec1[0]) + -1.0f));
			fVec2[0] = fTemp8;
			float fTemp9 = (((fTemp8 - fVec2[1]) * float(iVec1[1])) / fTemp6);
			fVec3[(IOTA & 4095)] = fTemp9;
			float fTemp10 = max(0.0f, min(2047.0f, (fConst5 / fTemp5)));
			int iTemp11 = int(fTemp10);
			float fTemp12 = floorf(fTemp10);
			iRec3[0] = ((1103515245 * iRec3[1]) + 12345);
			float fTemp13 = ((fSlow12 * ((fTemp9 - (fVec3[((IOTA - iTemp11) & 4095)] * (fTemp12 + (1.0f - fTemp10)))) - ((fTemp10 - fTemp12) * fVec3[((IOTA - (iTemp11 + 1)) & 4095)]))) + (fSlow19 * float(iRec3[0])));
			fRec6[0] = (iTemp0?0.0f:min(fSlow30, (fRec6[1] + 1.0f)));
			float fTemp14 = (fSlow1 * fRec6[0]);
			int iTemp15 = (fTemp14 < fConst3);
			fHbargraph1 = FAUSTFLOAT((fSlow28 * (iTemp15?((fTemp14 < 0.0f)?0.0f:(iTemp15?(fSlow18 * fRec6[0]):1.0f)):((fTemp14 < fSlow30)?((fSlow31 * (0.0f - (fTemp14 - fConst3))) + 1.0f):0.0f))));
			float fTemp16 = max((fSlow27 * (fHbargraph1 + 1.0f)), 23.4489498f);
			float fTemp17 = max(20.0f, fabsf(fTemp16));
			float fTemp18 = (fRec5[1] + (fConst1 * fTemp17));
			fRec5[0] = (fTemp18 - floorf(fTemp18));
			float fTemp19 = faust_simple_drums_faustpower2_f(((2.0f * fRec5[0]) + -1.0f));
			fVec4[0] = fTemp19;
			float fTemp20 = (((fTemp19 - fVec4[1]) * float(iVec1[1])) / fTemp17);
			fVec5[(IOTA & 4095)] = fTemp20;
			float fTemp21 = max(0.0f, min(2047.0f, (fConst5 / fTemp16)));
			int iTemp22 = int(fTemp21);
			float fTemp23 = floorf(fTemp21);
			float fTemp24 = ((fSlow26 * ((fTemp20 - (fVec5[((IOTA - iTemp22) & 4095)] * (fTemp23 + (1.0f - fTemp21)))) - ((fTemp21 - fTemp23) * fVec5[((IOTA - (iTemp22 + 1)) & 4095)]))) + (fSlow32 * float(iRec3[0])));
			fRec4[0] = (fTemp24 - (fSlow33 * ((fSlow34 * fRec4[2]) + (fSlow35 * fRec4[1]))));
			fRec7[0] = (fTemp13 - (fSlow41 * ((fSlow42 * fRec7[2]) + (fSlow43 * fRec7[1]))));
			output0[i] = FAUSTFLOAT((fSlow0 * ((iTemp2?((fTemp1 < 0.0f)?0.0f:(iTemp2?(fSlow8 * fRec0[0]):1.0f)):((fTemp1 < fSlow5)?((fSlow7 * (0.0f - (fTemp1 - fSlow6))) + 1.0f):0.0f)) * ((fSlow10 * fTemp13) + (((fSlow24 * (fRec4[2] + (fRec4[0] + (2.0f * fRec4[1])))) + (fSlow36 * fTemp24)) + (fSlow40 * (fRec7[2] + (fRec7[0] + (2.0f * fRec7[1])))))))));
			fVec0[1] = fVec0[0];
			iVec1[1] = iVec1[0];
			fRec0[1] = fRec0[0];
			fRec2[1] = fRec2[0];
			fRec1[1] = fRec1[0];
			fVec2[1] = fVec2[0];
			IOTA = (IOTA + 1);
			iRec3[1] = iRec3[0];
			fRec6[1] = fRec6[0];
			fRec5[1] = fRec5[0];
			fVec4[1] = fVec4[0];
			fRec4[2] = fRec4[1];
			fRec4[1] = fRec4[0];
			fRec7[2] = fRec7[1];
			fRec7[1] = fRec7[0];
			
		}
		
	}

	
};


#endif
